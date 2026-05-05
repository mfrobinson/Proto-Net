#pragma once
#include "Proto/Net/Socket.h"
#include "Proto/Net/Endpoint.h"
#include <vector>


namespace proto::net::ip::udp {

	class DataSocket : public Socket {
	public:
		using Socket::Socket;

		int recv_from(std::vector<char>& bytes, Endpoint& endpoint);
		int send_to(const std::vector<char>& bytes, const Endpoint& endpoint);
	protected:
	private:
	};

}