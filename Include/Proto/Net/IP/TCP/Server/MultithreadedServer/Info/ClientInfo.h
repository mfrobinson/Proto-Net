#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/BaseClientInfo.h"
#include "Proto/ExtendStruct.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo>
	using ClientInfo = ExtendStruct<BaseClientInfo, TExtraClientInfo>;

}