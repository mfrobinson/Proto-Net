#pragma once
#include "Proto/Net/IP/TCP/Windows/DataSocket.h"
//#include "Proto/Net/IP/Concepts/ClientSocketConcept.h"


namespace proto::net::ip::tcp {

	class ClientSocket : public DataSocket {
	public:
		using DataSocket::DataSocket;

		bool connect(const in_addr& ipv4_addr, u_short port);
		bool connect(const in6_addr& ipv6_addr, u_short port);
		bool connect(const std::string& str_addr, const std::string& service);
	protected:
	private:
	};

//	static_assert(ClientSocketConcept<ClientSocket>, "Windows ClientSocket must satisfy the ClientSocketConcept concept");

}