#pragma once
#include "Proto/Net/Windows/Socket.h"


namespace proto::net {

	class DataSocket : public Socket {
	public:
		int send(const void* buffer, const size_t length);
		int peek(void* buffer, const size_t length);
		int receive(void* buffer, const size_t length);
	protected:
	private:
	};

}