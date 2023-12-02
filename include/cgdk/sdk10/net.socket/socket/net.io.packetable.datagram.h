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
// net::io::packetable::Ndatagram
// 
//  datagram(UDP)용 packetable로 받은 데이터를 그대로 process_message()로 전달한다.
//  즉 아무 역할도 없는 packetable이라고 할수 있다.
// 	stream의 경우 메시지를 잘라주는 역할을 하지만 udp의 경우 일반적으로 그런 필요가
// 	없기 때문에 할 역할이 없으며 interface를 맞추는 역할만 한다.
// 
//-----------------------------------------------------------------------------
class net::io::packetable::Ndatagram : 
// inherited classes)
	virtual public				net::io::Ipacketable,
	virtual public				Imessageable,
	virtual public				net::io::Isend_request,
	virtual public				net::io::statistics::Nsocket
{
// implementation)
public:
	virtual	std::size_t			process_packet( shared_buffer& _buffer, const net::sockaddr& _psockAddr) override;
	virtual	void				process_reset_packetable() noexcept override { this->reset_message_history();}
};


}