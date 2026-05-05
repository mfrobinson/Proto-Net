#pragma once
#include "Proto/Net/IP/UDP/DataSocket.h"


namespace proto::net::ip::udp {

	int DataSocket::recv_from(std::vector<char>& bytes, Endpoint& endpoint) {
		return ::recvfrom(this->socket_descriptor, bytes.data(), bytes.size(), 0, endpoint, endpoint.size());
	}

	int DataSocket::send_to(const std::vector<char>& bytes, const Endpoint& endpoint) {
		return ::sendto(this->socket_descriptor, bytes.data(), bytes.size(), 0, endpoint, endpoint.size());
	}

}