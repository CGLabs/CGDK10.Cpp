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
//  datagram(UDP)�� packetable�� ���� �����͸� �״�� process_message()�� �����Ѵ�.
//  �� �ƹ� ���ҵ� ���� packetable�̶�� �Ҽ� �ִ�.
// 	stream�� ��� �޽����� �߶��ִ� ������ ������ udp�� ��� �Ϲ������� �׷� �ʿ䰡
// 	���� ������ �� ������ ������ interface�� ���ߴ� ���Ҹ� �Ѵ�.
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