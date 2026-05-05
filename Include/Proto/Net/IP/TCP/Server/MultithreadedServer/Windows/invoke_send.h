#pragma once
#include "Proto/Net/IP/TCP/DataSocket.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Callbacks/SendCallback.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Windows/invoke_send.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraSendInfo>
	void invoke_send(DataSocket& socket, SendInfo<TExtraClientInfo, TExtraSendInfo>* send_info) {
		DWORD flags = 0;
		const auto send_result = WSASend(socket.native_handle(), &(send_info->base.wsa_buffer), 1, NULL, &flags, (OVERLAPPED*)(send_info), NULL);
		if (send_result != 0) {
			const auto error_code = WSAGetLastError();
			if (error_code != WSA_IO_PENDING) throw std::runtime_error("Async WSASend call failed");
		}
		return;
	}

}