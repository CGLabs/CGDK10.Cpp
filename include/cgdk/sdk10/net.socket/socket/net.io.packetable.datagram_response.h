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
/*!
 * @class Ndatagram_response
 *
 * @ingroup net::io::packetable
 *
 * @brief Ndatagram_response�� ACK ���� ����� �߰��� ���̴�.
 *
 *  Ndatagram�� ���� ���� �����͸� �״�� process_message()�� ������ ���ش�.
 *  �� Reliable �޽����� �޾��� �� ACK�� ���� �������ִ� ����� ���� ���̴�. 
 *
 */
 //-----------------------------------------------------------------------------
class net::io::packetable::Ndatagram_response : 
// inherited classes)
	virtual public				net::io::Ipacketable,
	virtual public				Imessageable,
	virtual public				net::io::Isend_request,
	virtual public				net::io::statistics::Nsocket
{
// public)
public:
			bool				send_ack( uint32_t _Serial, const net::sockaddr& _address);

// implementation)
public:
	virtual	std::size_t			process_packet( shared_buffer& _buffer, const net::sockaddr& _address) override;
	virtual	void				process_reset_packetable() noexcept override { this->reset_message_history();}
};


}