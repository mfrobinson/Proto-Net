#pragma once
#include "Proto/Net/Windows/WinsockInstance.h"


namespace proto::net {

	class Socket : public WinsockInstance {
	public:
		Socket();
		Socket(SOCKET socket_descriptor);
		Socket(Socket&& other);
		Socket(const Socket& other) = delete;
		Socket& operator=(Socket&& other);
		Socket& operator=(const Socket& other) = delete;
		~Socket();

		SOCKET native_handle();
		void close();
	protected:
		SOCKET socket_descriptor;
	private:
		inline void move_from(Socket& other);
		inline void cleanup();
	};

}