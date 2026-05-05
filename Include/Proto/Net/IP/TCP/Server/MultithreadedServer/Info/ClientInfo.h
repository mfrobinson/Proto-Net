#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/BaseClientInfo.h"
#include "Proto/ExtendStruct.h"
#include <list>
#include <memory>


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo>
	struct ClientInfo : public ExtendStruct<BaseClientInfo<TExtraClientInfo, typename std::list<std::weak_ptr<ClientInfo<TExtraClientInfo>>>::iterator>, TExtraClientInfo> {
	};

}