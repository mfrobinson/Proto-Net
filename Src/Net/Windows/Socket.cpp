#include "Proto/Net/Windows/WindowsSocket.h"


namespace proto::net {

	Socket::Socket() : socket_descriptor(INVALID_SOCKET) {
		return;
	}

	Socket::Socket(SOCKET socket_descriptor) : socket_descriptor(socket_descriptor) {
		return;
	}

	Socket::Socket(Socket&& other) {
		this->move_from(other);
		return;
	}

	Socket& Socket::operator=(Socket&& other) {
		if (&other != this) {
			this->cleanup();
			this->move_from(other);
		}
		return *this;
	}

	Socket::~Socket() {
		this->cleanup();
		return;
	}

	SOCKET Socket::native_handle() {
		return this->socket_descriptor;
	}

	void Socket::close() {
		::shutdown(this->socket_descriptor, SD_BOTH);
		::closesocket(this->socket_descriptor);
		this->socket_descriptor = INVALID_SOCKET;
		return;
	}

	inline void Socket::move_from(Socket& other) {
		this->socket_descriptor = other.socket_descriptor;
		other.socket_descriptor = INVALID_SOCKET;
		return;
	}

	inline void Socket::cleanup() {
		this->close();
		return;
	}

}