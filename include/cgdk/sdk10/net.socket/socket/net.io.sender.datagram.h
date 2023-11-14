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
// net::io::sender::Ncontainer
//
// 1. net::io::sender::CDatagram은~
//    Datagram용 send함수이다. send_to()함수를 Interface로 가지고 있다.
//
// 2. 함수.
//    1) send_to()
//       Datagram용 Address로 Packet을 날리는 Interface함수.
//
//
//-----------------------------------------------------------------------------
class net::io::sender::Ndatagram : 
	virtual public				net::io::Isend_request,
	virtual public				net::io::Isender_datagram,
	virtual public				net::io::statistics::Nsocket
{
public:
	// 1) process send
	virtual	bool				process_send( shared_buffer&& _buffer, std::size_t _count_message, const net::sockaddr& _address, uint64_t _option = 0) override;
};


inline bool net::io::sender::Ndatagram::process_send( shared_buffer&& _buffer, std::size_t _count_message, const net::sockaddr& _address, [[maybe_unused]] uint64_t _option)
{
	// check) _buffer->data_가 nullptr이 아닌가?
	CGASSERT(_buffer.data() != nullptr, false)

	// check) _buffer.size_이 0이 아닌가?
	CGASSERT(_buffer.size() != 0, false)

	// check) 버퍼가 Overflow되었는가?
	CGASSERT(_buffer._is_buffer_overflow()==false, false);

	// 1) request send
	return this->request_send(_buffer, _buffer.move_out_source(), _count_message, _address);
}


}