#include "Proto/Net/IP/TCP/Server.h"
#include "Proto/Net/IP/TCP/ServerSocket.h"


namespace proto::net::ip::tcp {

	void Server::set_address(const std::string& address) {
		this->address = address;
		return;
	}

	void Server::set_service(const std::string& service) {
		this->service = service;
		return;
	}

	void Server::execute() {
		ServerSocket server_socket;
		if (!server_socket.bind(this->address, this->service)) return;
		if (!server_socket.listen(SOMAXCONN)) return;
		while (this->should_run()) {
			DataSocket client = server_socket.accept();
			this->serve_client(client);
		}
		server_socket.close();
		return;
	}

}