//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
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
// net::io::sender::Nstream
// 
//-----------------------------------------------------------------------------
class net::io::sender::Nstream : 
	virtual public				net::io::Isend_request,
	virtual public				net::io::Isender,
	virtual public				net::io::statistics::Nsocket
{
public:
	virtual	bool				process_send( shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option) override;
};

inline bool net::io::sender::Nstream::process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t /*_option*/)
{
	// check) _buffer->data_가 nullptr이 아닌가?
	RETURN_IF(_buffer.data() == nullptr, false)

	// check) _buffer->size_이 0이 아닌가?
	RETURN_IF(_buffer.size() == 0, false)

	// check) 버퍼가 Overflow되었는가?
	CGASSERT_ERROR(_buffer._is_buffer_overflow() == false);

	// debug)
#if !defined(NDEBUG)
	if (this->is_socket_debug_logging_enabled())
		net::io::_debug_log_socket_send_message(dynamic_cast<net::io::Isocket*>(this), _buffer);
#endif

	// declare)
	net::sockaddr address_peer;

	// 1) 전송한다.
	return this->request_send(_buffer, _buffer.move_out_source(), _count_message, address_peer);
}


} 