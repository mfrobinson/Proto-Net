#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/IoType.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/ClientInfo.h"
#include <vector>
#include <Windows.h>


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo>
	struct OperationInfo : public OVERLAPPED {
		IoType type;
		std::vector<char> bytes;
		WSABUF wsa_buffer;
		std::shared_ptr<ClientInfo<TExtraClientInfo>> client_info_ptr;
	};

}