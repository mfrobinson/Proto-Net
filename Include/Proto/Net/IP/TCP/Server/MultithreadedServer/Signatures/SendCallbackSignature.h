#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Signatures/BaseSendCallbackSignature.h"
#include "Proto/AppendArgumentTypes.h"
#include "Proto/Reference.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraSendInfo>
	using SendCallbackSignature = AppendArgumentTypes<BaseSendCallbackSignature, Reference<TExtraClientInfo>, Reference<TExtraSendInfo>>;

}