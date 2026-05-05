#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/RecvInfo.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Callbacks/RecvCallback.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraRecvInfo>
	RecvInfo<TExtraClientInfo, TExtraRecvInfo>* create_new_recv_info(const size_t number_of_bytes, RecvCallback<TExtraClientInfo, TExtraRecvInfo>& callback, const std::shared_ptr<ClientInfo<TExtraClientInfo>>& shared_client_info_ptr) {
		RecvInfo<TExtraClientInfo, TExtraRecvInfo>* recv_info = new RecvInfo<TExtraClientInfo, TExtraRecvInfo>;

		recv_info->type = IoType::RECV;
		recv_info->bytes.resize(number_of_bytes);
		recv_info->wsa_buffer.len = number_of_bytes;
		recv_info->wsa_buffer.buf = recv_info->bytes.data();
		recv_info->callback = std::move(callback);
		recv_info->client_info_ptr = shared_client_info_ptr;

		return recv_info;
	}
}