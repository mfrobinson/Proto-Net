#pragma once
#include "Proto/Net/IP/TCP/DataSocket.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TIteratorPosition>
	struct BaseClientInfo {
		DataSocket socket;
		TIteratorPosition registry_position;
	};

}