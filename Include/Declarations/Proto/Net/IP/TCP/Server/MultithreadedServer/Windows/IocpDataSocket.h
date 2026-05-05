#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Callbacks/RecvCallback.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Callbacks/SendCallback.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/ClientInfo.h"
#include <type_traits>
#include <vector>
#include <memory>


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	class IocpDataSocket {
	public:
		IocpDataSocket(std::shared_ptr<ClientInfo<TExtraClientInfo>>& shared_client_info_ptr);
		IocpDataSocket(IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>&& other);
		IocpDataSocket(const IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& other);
		IocpDataSocket& operator=(IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>&& other);
		IocpDataSocket& operator=(const IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& other);
		~IocpDataSocket();

		template <typename = typename std::enable_if<std::is_void<TExtraRecvInfo>::value>::type>
		void recv(const size_t number_of_bytes, RecvCallback<TExtraClientInfo, TExtraRecvInfo>& callback);

		template <typename = typename std::enable_if<!std::is_void<TExtraRecvInfo>::value>::type>
		void recv(const size_t number_of_bytes, RecvCallback<TExtraClientInfo, TExtraRecvInfo>& callback, TExtraRecvInfo extra_recv_info);

		template <typename = typename std::enable_if<std::is_void<TExtraSendInfo>::value>::type>
		void send(const std::vector<char>& bytes, SendCallback<TExtraClientInfo, TExtraSendInfo>& callback);

		template <typename = typename std::enable_if<!std::is_void<TExtraSendInfo>::value>::type>
		void send(const std::vector<char>& bytes, SendCallback<TExtraClientInfo, TExtraSendInfo>& callback, TExtraSendInfo extra_send_info);

		void close();
	protected:
	private:
		std::shared_ptr<ClientInfo<TExtraClientInfo>> shared_client_info_ptr;

		inline void move(IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& other);
		inline void copy(const IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& other);
		inline void cleanup();
	};

}