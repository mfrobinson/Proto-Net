#pragma once


namespace proto::net {

	class Socket {
	public:
		Socket();
		Socket(Socket&& other);
		Socket(const Socket& other);
		Socket& operator=(Socket&& other);
		Socket& operator=(const Socket& other);
		~Socket();

		int native_handle();
		void close();
	protected:
		int socket_descriptor;
	private:
		inline void move_from(Socket& other);
		inline void copy_from(const Socket& other);
		inline void cleanup();
	};

}