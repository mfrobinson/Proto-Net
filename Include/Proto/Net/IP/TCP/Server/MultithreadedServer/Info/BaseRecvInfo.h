#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/OperationInfo.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Callbacks/RecvCallback.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo>
	struct BaseRecvInfo : public OperationInfo<TExtraClientInfo> {
		RecvCallback<TExtraClientInfo, TExtraRecvInfo> callback;
	};

}