#pragma once
#include "Proto/Net/IP/TCP/DataSocket.h"
#include <vector>


namespace proto::net::ip::tcp {

	class IocpDataSocket;

	using BaseRecvCallbackSignature = void(IocpDataSocket&, std::vector<char>&);

}