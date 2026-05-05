#pragma once
#include "Proto/Net/IP/TCP/DataSocket.h"
#include <mutex>


namespace proto::net::ip::tcp {

	struct BaseClientInfo {
		DataSocket socket;
		typename std::list<std::weak_ptr<ClientInfo<TExtraClientInfo>>>::iterator registry_position;
	};

}