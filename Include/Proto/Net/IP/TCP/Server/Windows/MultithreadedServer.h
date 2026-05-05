#pragma once
#include "Declarations/Proto/Net/IP/TCP/Server/Windows/MultithreadedServer.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Windows/invoke_recv_callback.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Windows/invoke_send_callback.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::MultithreadedServer() : number_of_iocp_worker_threads(std::thread::hardware_concurrency()) {
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::~MultithreadedServer() {
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::execute() {
		this->completion_port = CreateIOCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);

		this->spawn_worker_threads();
		__super::execute();
		this->interrupt_worker_threads();
		this->thread_pool.join();

		this->disconnect_all_clients();
		this->cleanup_pending_operations();

		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::serve_client(DataSocket& client) {
		// Initialise ClientInfo structure as a std::shared_ptr
		std::shared_ptr<ClientInfo<TExtraClientInfo>> shared_client_info_ptr(new ClientInfo<TExtraClientInfo>(), std::bind_front(&MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::cleanup_client_info, this));
		shared_client_info_ptr->base.socket = std::move(client);
		// Push the new ClientInfo structure to the back of the vector of currently alive ClientInfo structures
		{
			std::lock_guard<std::mutex> client_infos_guard(this->client_infos_mutex);
			shared_client_info_ptr->base.registry_position = this->client_infos.insert(this->client_infos.end(), shared_client_info_ptr);
		}
		// Assocciate the socket handle with the IO Completion Port
		CreateIoCompletionPort(shared_client_info_ptr->base.socket.native_handle(), this->completion_port, (ULONG_PTR)(shared_client_info_ptr.get()), 0);
		// Wrap the ClientInfo structure so that the user is directed through the appropriate calls (WSARecv/WSASend)
		IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo> iocp_data_socket(shared_client_info_ptr);
		// Allow the user to determine what to do first (send or receive)
		this->initiate_communication(iocp_data_socket);
		// If the user failed to perform an operation on the socket, remove its corresponding ClientInfo structure from the alive ones
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::iocp_worker() {
		DWORD bytes_transferred;
		ULONG_PTR completion_key;
		LPOVERLAPPED overlapped;

		bool result = GetQueuedCompletionStatus(this->completion_port, &bytes_transferred, &completion_key, &overlapped, INFINITE);
		ClientInfo<TExtraClientInfo>* client_info = (ClientInfo<TExtraClientInfo>*)(completion_key);
		OperationInfo<TExtraClientInfo>* operation_info = (OperationInfo<TExtraClientInfo>*)(overlapped);

		while (result && completion_key != nullptr && overlapped != nullptr && bytes_transferred != 0 && this->should_run()) {
			switch (operation_info->type) {
				case IoType::RECV: {
					RecvInfo<TExtraClientInfo, TExtraRecvInfo>* recv_info = (RecvInfo<TExtraClientInfo, TExtraRecvInfo>*)(operation_info);
					IocpDataSocket iocp_data_socket(recv_info->client_info_ptr);
					invoke_recv_callback(iocp_data_socket, client_info_ptr, recv_info);
					delete recv_info;
					break;
				}
				case IoType::SEND: {
					SendInfo<TExtraClientInfo, TExtraSendInfo>* send_info = (SendInfo<TExtraClientInfo, TExtraSendInfo>*)(operation_info);
					IocpDataSocket iocp_data_socket(send_info->client_info_ptr);
					invoke_send_callback(iocp_data_socket, client_info_ptr, recv_info);
					delete send_info;
					break;
				}
				default: break;
			}
			result = GetQueuedCompletionStatus(this->completion_port, &bytes_transferred, &completion_key, &overlapped, INFINITE);
			client_info = (ClientInfo<TExtraClientInfo>*)(completion_key);
			operation_info = (OperationInfo<TExtraClientInfo>*)(overlapped);
		}
		if (operation_info != nullptr) this->cleanup_operation_info(operation_info);
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::spawn_worker_threads() {
		std::thread worker_thread;
		for (size_t i = 0; i < this->number_of_iocp_worker_threads; ++i) {
			worker_thread = std::thread(&MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::iocp_worker, this);
			this->thread_pool.assign(std::move(worker_thread));
		}
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::interrupt_worker_threads() {
		for (size_t i = 0; i < this->number_of_iocp_worker_threads; ++i) {
			PostQueuedCompletionStatus(this->completion_port, 0, nullptr, nullptr);
		}
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::disconnect_all_clients() {
		std::lock_guard<std::mutex> client_infos_guard(this->client_infos_mutex);
		for (auto& client_info : this->client_infos) {
			client_info->base.socket.close();
		}
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::cleanup_pending_operations() {
		DWORD bytes_transferred;
		ULONG_PTR completion_key;
		LPOVERLAPPED overlapped;
		
		while (this->client_infos.size() != 0) {
			GetQueuedCompletionStatus(this->completion_port, &bytes_transferred, &completion_key, &overlapped, INFINITE);
			if (overlapped != nullptr) this->cleanup_operation_info((OperationInfo<TExtraClientInfo>*)(overlapped));
		}
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::cleanup_client_info(ClientInfo<TExtraClientInfo>* ptr) {
		{
			std::lock_guard<std::mutex> client_infos_guard(this->client_infos_mutex);
			this->client_infos.erase(ptr->registry_position);
		}
		delete ptr;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::cleanup_operation_info(OperationInfo<TExtraClientInfo>* ptr) {
		switch (ptr->type) {
			case IoType::RECV: {
				RecvInfo<TExtraClientInfo, TExtraRecvInfo>* recv_info = (RecvInfo<TExtraClientInfo, TExtraRecvInfo>*)(ptr);
				delete recv_info;
				break;
			}
			case IoType::SEND: {
				SendInfo<TExtraClientInfo, TExtraSendInfo>* send_info = (SendInfo<TExtraClientInfo, TExtraSendInfo>*)(ptr);
				delete send_info;
				break;
			}
			default: throw std::runtime_error("Unknown IoType when cleaning up an instance of OperationInfo");
		}
		return;
	}

}