#pragma once
#include "Proto/Net/IP/TCP/Server.h"
#include "Proto/Net/Windows/IOCPManager.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/ClientInfo.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/RecvInfo.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/SendInfo.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Windows/IocpDataSocket.h"
#include <list>
#include <memory>


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	class MultithreadedServer : public Server {
	public:
		MultithreadedServer();
		MultithreadedServer(MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>&& other) = delete;
		MultithreadedServer(const MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& other) = delete;
		MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& operator(MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>&& other) = delete;
		MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& operator(const MultithreadedServer<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& other) = delete;
		~MultithreadedServer();
	protected:
		virtual void execute() override;
		virtual void serve_client(DataSocket& client) override;
		virtual void initiate_communication(IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& client) = 0;
	private:
		size_t number_of_iocp_worker_threads;
		Threadpool thread_pool;

		std::list<std::weak_ptr<ClientInfo<TExtraClientInfo>>> client_infos;
		std::mutex client_infos_mutex;

		void iocp_worker();

		inline void spawn_worker_threads();
		inline void interrupt_worker_threads();

		inline void disconnect_all_clients();
		inline void cleanup_pending_operations();

		inline void remove_recv_info(RecvInfo<TExtraClientInfo, TExtraRecvInfo>* recv_info);
		inline void remove_send_info(SendInfo<TExtraClientInfo, TExtraSendInfo>* send_info);

		void cleanup_client_info(ClientInfo<TExtraClientInfo>* ptr);
		void cleanup_operation_info(OperationInfo<TExtraClientInfo>* ptr);
	};

}