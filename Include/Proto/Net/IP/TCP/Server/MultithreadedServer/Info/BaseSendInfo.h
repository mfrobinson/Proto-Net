#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/OperationInfo.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Callbacks/SendCallback.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraSendInfo>
	struct BaseSendInfo : public OperationInfo<TExtraClientInfo> {
		SendCallback<TExtraClientInfo, TExtraSendInfo> callback;
	};

}