#pragma once
#include "Proto/Net/IP/TCP/DataSocket.h"


namespace proto::net::ip::tcp {

	class IocpDataSocket;

	using BaseSendCallbackSignature = void(IocpDataSocket&);

}