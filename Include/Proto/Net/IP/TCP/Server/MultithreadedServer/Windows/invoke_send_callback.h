#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Windows/IocpDataSocket.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/SendInfo.h"

namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void invoke_send_callback(IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& socket, ClientInfo<TExtraClientInfo> client_info, SendInfo<TExtraClientInfo, TExtraSendInfo>* send_info) {
		send_info->base.callback(socket, client_info->extension, send_info->extension);
		return;
	}

	template <typename TExtraClientInfo, typename TExtraRecvInfo>
	void invoke_send_callback<TExtraClientInfo, TExtraRecvInfo, void>(IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, void>& socket, ClientInfo<TExtraClientInfo>* client_info, RecvInfo<TExtraClientInfo, void>* send_info) {
		send_info->base.callback(socket, client_info->extension);
		return;
	}

	template <typename TExtraRecvInfo, typename TExtraSendInfo>
	void invoke_send_callback<void, TExtraRecvInfo, TExtraSendInfo>(IocpDataSocket<void, TExtraRecvInfo, TExtraSendInfo>& socket, ClientInfo<void>* client_info, SendInfo<void, TExtraSendInfo>* send_info) {
		send_info->base.callback(socket, send_info->extension);
		return;
	}

	template <typename TExtraRecvInfo>
	void invoke_send_callback<void, TExtraRecvInfo, void>(IocpDataSocket<void, TExtraRecvInfo, void>& socket, ClientInfo<void>* client_info, SendInfo<void, void>* send_info) {
		send_info->base.callback(socket);
		return;
	}

}