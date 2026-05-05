#pragma once
#include "Proto/Runnable.h"
#include "Proto/Net/IP/TCP/DataSocket.h"
#include <string>


namespace proto::net::ip::tcp {

	class Server : public Runnable {
	public:
		Server(Server&& other) = delete;
		Server(const Server& other) = delete;
		Server& operator=(Server&& other) = delete;
		Server& operator=(const Server& other) = delete;

		void set_address(const std::string& address);
		void set_service(const std::string& service);
	protected:
		virtual void execute() override;
		virtual void serve_client(DataSocket& client) = 0;
	private:
		std::string address;
		std::string service;
	};

}