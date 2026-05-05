#include "Proto/Net/Windows/WinsockInstance.h"
#include <stdexcept>


namespace proto::net {

	WSAData WinsockInstance::data;

	WinsockInstance::WinsockInstance() {
		if (WSAStartup(MAKEWORD(2, 2), &WinsockInstance::data) != 0) throw std::runtime_error("WSAStartup failed");
		return;
	}

	WinsockInstance::~WinsockInstance() {
		WSACleanup();
	}

}