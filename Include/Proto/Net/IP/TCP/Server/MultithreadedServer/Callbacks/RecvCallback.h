#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Signatures/RecvCallbackSignature.h"
#include <functional>


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo>
	using RecvCallback = std::function<RecvCallbackSignature<TExtraClientInfo, TExtraRecvInfo>>;

}