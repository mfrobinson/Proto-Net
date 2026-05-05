#include "Proto/Net/IP/TCP/Windows/ServerSocket.h"
#include <stdexcept>


namespace proto::net::ip::tcp {

	bool ServerSocket::bind(const in_addr& ipv4_addr, const u_short port) {
		if ((this->socket_descriptor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return false;
		sockaddr_in addr;
		ZeroMemory(&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr = ipv4_addr;
		addr.sin_port = port;
		if (::bind(this->socket_descriptor, (const sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
			this->close();
			return false;
		}
		return true;
	}

	bool ServerSocket::bind(const in6_addr& ipv6_addr, const u_short port) {
		if ((this->socket_descriptor = ::socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return false;
		sockaddr_in6 addr;
		ZeroMemory(&addr, sizeof(addr));
		addr.sin6_family = AF_INET6;
		addr.sin6_addr = ipv6_addr;
		addr.sin6_port = port;
		if (::bind(this->socket_descriptor, (const sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
			this->close();
			return false;
		}
		return true;
	}

	bool ServerSocket::bind(const std::string& str_addr, const std::string& service) {
		struct addrinfo hints, * result;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		if (getaddrinfo(str_addr.c_str(), service.c_str(), &hints, &result) != 0) return false;

		for (struct addrinfo* ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
			if ((this->socket_descriptor = ::socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == INVALID_SOCKET) continue;
			if (::bind(this->socket_descriptor, ptr->ai_addr, ptr->ai_addrlen) != SOCKET_ERROR) {
				freeaddrinfo(result);
				return true;
			}
			this->close();
		}
		freeaddrinfo(result);
		return false;
	}

	bool ServerSocket::listen(const size_t backlog) {
		return ::listen(this->socket_descriptor, backlog) != SOCKET_ERROR;
	}

	DataSocket ServerSocket::accept() {
		SOCKET accepted_socket_descriptor;
		if ((accepted_socket_descriptor = ::accept(this->socket_descriptor, nullptr, nullptr)) == INVALID_SOCKET) throw std::runtime_error("accept failed");
		return DataSocket(accepted_socket_descriptor);
	}

}