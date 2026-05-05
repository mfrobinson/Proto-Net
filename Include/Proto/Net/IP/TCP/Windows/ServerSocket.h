#pragma once
#include "Proto/Net/Windows/WindowsSocket.h"
#include "Proto/Net/IP/TCP/Windows/WindowsDataSocket.h"
//#include "Proto/Net/IP/Concepts/ServerSocketConcept.h"
#include <string>


namespace proto::net::ip::tcp {

	class ServerSocket : public Socket {
	public:
		using Socket::Socket;

		bool bind(const in_addr& ipv4_addr, const u_short port);
		bool bind(const in6_addr& ipv6_addr, const u_short port);
		bool bind(const std::string& str_addr, const std::string& service);

		bool listen(const size_t backlog);

		DataSocket accept();
	protected:
	private:
	};

//	static_assert(ServerSocketConcept<ServerSocket>, "Windows ServerSocket must satisfy the ServerSocketConcept concept");

}