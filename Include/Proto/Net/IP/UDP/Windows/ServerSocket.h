#pragma once
#include "Proto/Net/IP/UDP/Windows/DataSocket.h"
//#include "Proto/Net/IP/Concepts/ServerSocketConcept.h"
#include <string>
#include <vector>


namespace proto::net::ip::udp {

	class ServerSocket : public DataSocket {
	public:
		using Socket::Socket;

		bool bind(const in_addr& ipv4_addr, const u_short port);
		bool bind(const in6_addr& ipv6_addr, const u_short port);
		bool bind(const std::string& str_addr, const std::string& service);
	protected:
	private:
	};

	//	static_assert(ServerSocketConcept<ServerSocket>, "Windows ServerSocket must satisfy the ServerSocketConcept concept");

}