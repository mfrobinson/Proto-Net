#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/BaseRecvInfo.h"
#include "Proto/ExtendStruct.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo>
	using RecvInfo = ExtendStruct<BaseRecvInfo<TExtraClientInfo, TExtraRecvInfo>, TExtraRecvInfo>;

}