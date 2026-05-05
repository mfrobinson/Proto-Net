#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Windows/IocpDataSocket.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/RecvInfo.h"

namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo, typename TExtraSendInfo>
	void invoke_recv_callback(IocpDataSocket<TExtraClientInfo, TExtraRecvInfo, TExtraSendInfo>& socket, ClientInfo<TExtraClientInfo> client_info, RecvInfo<TExtraClientInfo, TExtraRecvInfo>* recv_info) {
		recv_info->base.callback(socket, recv_info->base.bytes, client_info->extension, recv_info->extension);
		return;
	}

	template <typename TExtraClientInfo, typename TExtraSendInfo>
	void invoke_recv_callback<TExtraClientInfo, void, TExtraSendInfo>(IocpDataSocket<TExtraClientInfo, void, TExtraSendInfo>& socket, ClientInfo<TExtraClientInfo>* client_info, RecvInfo<TExtraClientInfo, void>* recv_info) {
		recv_info->base.callback(socket, recv_info->base.bytes, client_info->extension);
		return;
	}

	template <typename TExtraRecvInfo, typename TExtraSendInfo>
	void invoke_recv_callback<void, TExtraRecvInfo, TExtraSendInfo>(IocpDataSocket<void, TExtraRecvInfo, TExtraSendInfo>& socket, ClientInfo<void>* client_info, RecvInfo<void, TExtraRecvInfo>* recv_info) {
		recv_info->base.callback(socket, recv_info->base.bytes, recv_info->extension);
		return;
	}

	template <typename TExtraSendInfo>
	void invoke_recv_callback<void, void, TExtraSendInfo>(IocpDataSocket<void, void, TExtraSendInfo>& socket, ClientInfo<void>* client_info, RecvInfo<void, void>* recv_info) {
		recv_info->base.callback(socket, recv_info->base.bytes);
		return;
	}

}