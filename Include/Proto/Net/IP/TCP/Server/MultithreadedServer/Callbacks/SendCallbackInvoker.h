#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/ClientInfo.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/SendInfo.h"
#include "Proto/Net/IP/TCP/DataSocket.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraSendInfo>
	void invoke_send_callback(DataSocket& socket, ClientInfo<TExtraClientInfo>* client_info, SendInfo<TExtraClientInfo, TExtraSendInfo>* send_info) {
		send_info->base.callback(socket, client_info->extension, send_info->extension);
		return;
	}

	template <typename TExtraClientInfo>
	void invoke_send_callback<TExtraClientInfo, void>(DataSocket& socket, std::vector<char>& bytes, ClientInfo<TExtraClientInfo>* client_info, SendInfo<TExtraClientInfo, void>* send_info) {
		send_info->base.callback(socket, bytes, client_info->extension);
		return;
	}

	template <typename TExtraRecvInfo>
	void invoke_send_callback<void, TExtraSendInfo>(DataSocket& socket, std::vector<char>& bytes, ClientInfo<void>* client_info, RecvInfo<void, TExtraSendInfo>* send_info) {
		send_info->base.callback(socket, bytes, send_info->extension);
		return;
	}

	void invoke_send_callback<void, void>(DataSocket& socket, std::vector<char>& bytes, ClientInfo<void>* client_info, SendInfo<void, void>* send_info) {
		send_info->base.callback(socket, bytes);
		return;
	}

}