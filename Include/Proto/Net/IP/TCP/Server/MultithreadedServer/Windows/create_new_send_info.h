#pragma once
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Info/SendInfo.h"
#include "Proto/Net/IP/TCP/Server/MultithreadedServer/Callbacks/SendCallback.h"


namespace proto::net::ip::tcp {

	template <typename TExtraClientInfo, typename TExtraSendInfo>
	SendInfo<TExtraClientInfo, TExtraSendInfo>* create_new_send_info(const std::vector<char>& bytes, SendCallback<TExtraClientInfo, TExtraSendInfo>& callback, const std::shared_ptr<ClientInfo<TExtraClientInfo>>& shared_client_info_ptr) {
		SendInfo<TExtraClientInfo, TExtraSendInfo>* send_info = new SendInfo<TExtraClientInfo, TExtraSendInfo>;

		send_info->type = IoType::SEND;
		send_info->bytes = bytes;
		send_info->wsa_buffer.len = bytes.size();
		send_info->wsa_buffer.buf = send_info->bytes.data();
		send_info->callback = std::move(callback);
		send_info->client_info_ptr = shared_client_info_ptr;

		return send_info;
	}
}