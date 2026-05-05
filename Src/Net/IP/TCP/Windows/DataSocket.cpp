#include "Proto/Net/IP/TCP/Windows/DataSocket.h"


namespace proto::net {

	int DataSocket::send(const void* buffer, const size_t length) {
		return ::send(this->socket_descriptor, (const char*)buffer, length, 0);
	}

	int DataSocket::peek(void* buffer, const size_t length) {
		return ::recv(this->socket_descriptor, (char*)buffer, length, MSG_PEEK);
	}

	int DataSocket::receive(void* buffer, const size_t length) {
		return ::recv(this->socket_descriptor, (char*)buffer, length, 0);
	}

}