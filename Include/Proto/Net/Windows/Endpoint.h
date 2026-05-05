#pragma once
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")


namespace proto::net {

	class Endpoint {
	public:
		Endpoint();
		Endpoint(Endpoint&& other);
		Endpoint(const Endpoint& other);
		Endpoint& operator=(Endpoint&& other);
		Endpoint& operator=(const Endpoint& other);
		~Endpoint();

		operator sockaddr*();
		operator const sockaddr* () const;
		INT size() const;
	protected:
	private:
		SOCKADDR_STORAGE address_store;

		inline void move(Endpoint& other);
		inline void copy(const Endpoint& other);
		inline void cleanup();
	};

}