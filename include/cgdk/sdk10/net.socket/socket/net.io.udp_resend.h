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
// 1. net::io::Nudp_resend��!
//    1) �Ϲ����� UDP�� Sendeing ��ɿ� ������ ������ ����� �߰��� ���̴�.
//    2) ���� �� RELIABLE �÷��׸� �����Ͽ� ������ ��� �ش� �޽����� ���ؼ��� 
//       ������ ����� �����Ѵ�.
//    3) ������ ����̶� ���۵� �޽����� ���ؼ� ACK ��ȣ�� �������� ���� ��� ����
//       �ð� ���� ���������ִ� ����� �ǹ��Ѵ�.
//    4) �����ð� �������� �����ص� �����ۿ� �������� ���� ��� OnFailSend()�Լ���
//       ȣ���Ѵ�.
//
//    ����) ���� ��Ը��� �������� ������ ��� �� Ŭ�������ٴ� Reliable Ŭ������ 
//         ����ϱ� �����Ѵ�. ��Ը��� �������� ������ ��� ���� Cogestion control
//         �� �پ��� ������ �˰����� �߰��� Reliable Ŭ�������� ������ ���� ����
//         ����.
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