#pragma once
#include "Proto/Net/IP/TCP/DataSocket.h"
#include <mutex>
#include <list>
#include <memory>


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo>
	class ClientInfo;

	template <typename TExtraClientInfo>
	struct BaseClientInfo {
		DataSocket socket;
		typename std::list<std::weak_ptr<ClientInfo<TExtraClientInfo>>>::iterator registry_position;
	};

}