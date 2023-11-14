//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        network socket http classes                        *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// net::io::Nhttp_client
//
// 1. net::io::Nhttp_server은~
//     web client용 socket
//     http와 websocket를 지원한다.
//
//-----------------------------------------------------------------------------
class net::io::Nhttp_client :
// inherited classes)
	public						net::io::connect_requestable::Nhttp,
	public						net::io::socket::tcp::Ndefault,
	public						net::io::connectable::tcp::Ndefault,
	public						net::io::Nsocket_secure,
	public						net::io::send_request::tcp::Ndefault,
	public						net::io::sender::Nhttp,
	virtual public				net::io::Ipacketable,
	virtual protected			Imessageable
{
// public) 
public:
	// 1) for websocket
			bool				send(buffer_view _buffer, eHTTP_METHOD _method = eHTTP_METHOD::BINARY_);
			bool				send(const std::string_view _string);

	// 3) 
			bool				is_websocket() const noexcept { return m_msg_http_response.protocol == eHTTP_PROTOCOL::WEBSOCKET_; }

// implementation)
protected:
	virtual	result_code			on_message(sMESSAGE_HTTP_RESPONSE& _msg);
	virtual	result_code			on_message(sMESSAGE_HTTP_WEBSOCKET& _msg);
	virtual result_code			on_message(sMESSAGE_NETWORK& /*_msg*/) { return 0; }

// implementation)
protected:
	virtual	void				process_pre_message (sMESSAGE_NETWORK& /*_msg*/) {}
	virtual	void				process_reset_packetable () noexcept override { m_msg_http_response.reset();}
	virtual	size_t				process_packet ( shared_buffer& _buffer, const net::sockaddr& _address) override;
			size_t				process_packet_http( shared_buffer& _buffer, const net::sockaddr& _psocket_address);
			size_t				process_packet_websocket(shared_buffer& _buffer, const net::sockaddr& _psocket_address);
			size_t				process_parsing_http (shared_buffer _buffer);
			void				process_parsing_http_head (shared_buffer _buffer);
	virtual	result_code			process_message (sMESSAGE& _msg) override;

	virtual void				process_on_connect () override;
	virtual	void				process_on_fail_connect (uint64_t _disconnect_reason) override;
	virtual	void				process_on_disconnect (uint64_t _disconnect_reason, eSOCKET_STATE _socket_state) override;

protected:
			// declare) 
			sMESSAGE_HTTP_RESPONSE m_msg_http_response;
};


}