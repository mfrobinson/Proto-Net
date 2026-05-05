#pragma once
#include "Declarations/Proto/Net/IP/TCP/Server/MultithreadedServer/Windows/IocpDataSocket.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Windows/recv.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Windows/send.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::IocpDataSocket(std::shared_ptr<ClientInfo<TExtraClientInfo>>& shared_client_info_ptr) : shared_client_info_ptr(std::move(shared_client_info_ptr)) {
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::IocpDataSocket(IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>&& other) {
		this->move(other);
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::IocpDataSocket(const IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& other) {
		this->copy(other);
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	IocpDataSocket& IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::operator=(IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>&& other) {
		if (&other != this){
			this->cleanup();
			this->move(other);
		}
		return *this;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	IocpDataSocket& IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::operator=(const IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& other) {
		if (&other != this) {
			this->cleanup();
			this->copy(other);
		}
		return *this;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::~IocpDataSocket() {
		this->cleanup();
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	template <typename = typename std::enable_if<std::is_void<TExtraRecvInfo>::value>::type>
	void IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::recv(const size_t number_of_bytes, RecvCallback<TExtraClientInfo, TExtraRecvInfo>& callback) {
		RecvInfo<TExtraClientInfo, void>* recv_info = create_new_recv_info(number_of_bytes, callback, this->shared_client_info_ptr);
		invoke_recv(socket, recv_info);
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	template <typename = typename std::enable_if<!std::is_void<TExtraRecvInfo>::value>::type>
	void IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::recv(const size_t number_of_bytes, RecvCallback<TExtraClientInfo, TExtraRecvInfo>& callback, TExtraRecvInfo extra_recv_info) {
		RecvInfo<TExtraClientInfo, TExtraRecvInfo>* recv_info = create_new_recv_info(number_of_bytes, callback, this->shared_client_info_ptr);
		recv_info->extension = std::move(extra_recv_info);
		invoke_recv(socket, recv_info);
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	template <typename = typename std::enable_if<std::is_void<TExtraSendInfo>::value>::type>
	void IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::send(const std::vector<char>& bytes, SendCallback<TExtraClientInfo, TExtraSendInfo>& callback) {
		SendInfo<TExtraClientInfo, TExtraSendInfo>* send_info = create_new_send_info(bytes, callback, this->shared_client_info_ptr);
		invoke_send(socket, send_info);
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	template <typename = typename std::enable_if<!std::is_void<TExtraSendInfo>::value>::type>
	void IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::send(const std::vector<char>& bytes, SendCallback<TExtraClientInfo, TExtraSendInfo>& callback, TExtraSendInfo extra_send_info) {
		SendInfo<TExtraClientInfo, TExtraSendInfo>* send_info = create_new_send_info(bytes, callback, this->shared_client_info_ptr);
		send_info->extension = std::move(extra_send_info);
		invoke_send(socket, send_info);
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::close() {
		this->shared_client_info_ptr->base.socket.close();
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::move(IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& other) {
		this->shared_client_info_ptr = std::move(other.shared_client_info_ptr);
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::copy(const IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& other) {
		this->shared_client_info_ptr = other.shared_client_info_ptr;
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>::cleanup() {
		return;
	}

}