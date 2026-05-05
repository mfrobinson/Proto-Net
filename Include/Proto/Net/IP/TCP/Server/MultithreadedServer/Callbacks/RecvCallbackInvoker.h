#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/ClientInfo.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/RecvInfo.h"
#include "Proto/Net/IP/TCP/DataSocket.h"
#include <vector>


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo>
	void invoke_recv_callback(DataSocket& socket, std::vector<char>& bytes, ClientInfo<TExtraClientInfo>* client_info, RecvInfo<TExtraClientInfo, TExtraRecvInfo>* recv_info) {
		recv_info->base.callback(socket, bytes, client_info->extension, recv_info->extension);
		return;
	}

	template <typename TExtraClientInfo>
	void invoke_recv_callback<TExtraClientInfo, void>(DataSocket& socket, std::vector<char>& bytes, ClientInfo<TExtraClientInfo>* client_info, RecvInfo<TExtraClientInfo, void>* recv_info) {
		recv_info->base.callback(socket, bytes, client_info->extension);
		return;
	}

	template <typename TExtraRecvInfo>
	void invoke_recv_callback<void, TExtraRecvInfo>(DataSocket& socket, std::vector<char>& bytes, ClientInfo<void>* client_info, RecvInfo<void, TExtraRecvInfo>* recv_info) {
		recv_info->base.callback(socket, bytes, recv_info->extension);
		return;
	}

	void invoke_recv_callback<void, void>(DataSocket& socket, std::vector<char>& bytes, ClientInfo<void>* client_info, RecvInfo<void, void>* recv_info) {
		recv_info->base.callback(socket, bytes);
		return;
	}

}