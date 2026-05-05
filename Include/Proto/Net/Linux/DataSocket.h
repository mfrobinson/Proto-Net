#pragma once
#include "Proto/Net/Linux/Socket.h"
#include <sys/types.h>


namespace proto::net {

	class DataSocket : public Socket {
	public:
		ssize_t send(const void* buffer, const size_t length);
		ssize_t peek(void* buffer, const size_t length);
		ssize_t receive(void* buffer, const size_t length);
	protected:
	private:
	};

}