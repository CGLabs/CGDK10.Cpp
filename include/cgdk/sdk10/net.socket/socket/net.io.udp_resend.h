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
// net::io::Nudp_resend
//
// 1. net::io::Nudp_resend란!
//    1) 일반적인 UDP의 Sendeing 기능에 선택적 재전송 기능을 추가한 것이다.
//    2) 전송 시 RELIABLE 플래그를 설정하여 전송할 경우 해당 메시지에 대해서만 
//       재전송 기능이 동작한다.
//    3) 재전송 기능이란 전송된 메시지에 대해서 ACK 신호가 도착하지 않을 경우 일정
//       시간 동안 재전송해주는 기능을 의미한다.
//    4) 일정시간 재전송을 수행해도 재전송에 성공하지 못할 경우 OnFailSend()함수를
//       호출한다.
//
//    주위) 만약 대규모의 재전송을 수행할 경우 이 클래스보다는 Reliable 클래스를 
//         사용하길 권장한다. 대규모의 재전송을 수행할 경우 각종 Cogestion control
//         및 다양한 재전송 알고리즘이 추가된 Reliable 클래스보다 성능이 많이 떨어
//         진다.
//
//-----------------------------------------------------------------------------
#define	MAX_RECEIVEPACKET_QUEUE		1024

class net::io::Nudp_resend :
	public						net::io::send_request::Nudp_resend,
	public						net::io::packetable::Ndatagram_response,
	virtual public				Imessageable,
	virtual public				net::io::statistics::Nsocket
{
public:
	virtual	std::size_t			process_packet( shared_buffer& _buffer, const net::sockaddr& _address) override;
	virtual	void				process_reset_packetable() noexcept override {}
};


}