#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Signatures/SendCallbackSignature.h"
#include <functional>


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraSendInfo>
	using SendCallback = std::function<SendCallbackSignature<TExtraClientInfo, TExtraSendInfo>>;

}