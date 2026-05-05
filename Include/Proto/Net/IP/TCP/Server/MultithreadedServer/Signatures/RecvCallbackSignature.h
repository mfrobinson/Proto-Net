#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Signatures/BaseRecvCallbackSignature.h"
#include "Proto/AppendArgumentTypes.h"
#include "Proto/Reference.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo>
	using RecvCallbackSignature = AppendArgumentTypes<BaseRecvCallbackSignature, Reference<TExtraClientInfo>, Reference<TExtraRecvInfo>>;

}