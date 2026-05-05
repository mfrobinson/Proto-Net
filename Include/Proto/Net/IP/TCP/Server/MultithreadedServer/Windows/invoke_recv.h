#pragma once
#include "Proto/Net/IP/TCP/DataSocket.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Callbacks/RecvCallback.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Windows/invoke_recv.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo>
	void invoke_recv(DataSocket& socket, RecvInfo<TExtraClientInfo, TExtraRecvInfo>* recv_info) {
		DWORD flags = 0;
		const auto recv_result = WSARecv(socket.native_handle(), &(recv_info->base.wsa_buffer), 1, NULL, &flags, (OVERLAPPED*)(recv_info), NULL);
		if (recv_result != 0) {
			const auto error_code = WSAGetLastError();
			if (error_code != WSA_IO_PENDING) throw std::runtime_error("Async WSARecv call failed");
		}
		return;
	}

}