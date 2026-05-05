#include "Proto/Net/Windows/Endpoint.h"
#include <utility>


namespace proto::net {

	Endpoint::Endpoint() {
		this->address_store.ss_family = AF_UNSPEC;
		return;
	}

	Endpoint::Endpoint(Endpoint&& other) {
		this->move(other);
		return;
	}

	Endpoint::Endpoint(const Endpoint& other) {
		this->copy(other);
		return;
	}

	Endpoint& Endpoint::operator=(Endpoint&& other) {
		if (&other != this) {
			this->cleanup();
			this->move(other);
		}
		return *this;
	}

	Endpoint& Endpoint::operator=(const Endpoint& other) {
		if (&other != this) {
			this->cleanup();
			this->copy(other);
		}
		return *this;
	}

	Endpoint::~Endpoint() {
		this->cleanup();
		return;
	}

	Endpoint::operator sockaddr* () {
		return (sockaddr*)(&this->address_store);
	}

	Endpoint::operator const sockaddr* () const {
		return (sockaddr*)(&this->address_store);
	}

	INT Endpoint::size() const {
		return sizeof(this->address_store);
	}

	void Endpoint::move(Endpoint& other) {
		this->address_store = std::move(other.address_store);
		return;
	}

	void Endpoint::copy(const Endpoint& other) {
		this->address_store = other.address_store;
		return;
	}

	void Endpoint::cleanup() {
		return;
	}

}