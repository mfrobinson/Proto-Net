#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/BaseSendInfo.h"
#include "Proto/ExtendStruct.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraSendInfo>
	using SendInfo = ExtendStruct<BaseSendInfo<TExtraClientInfo, TExtraSendInfo>, TExtraSendInfo>;

}