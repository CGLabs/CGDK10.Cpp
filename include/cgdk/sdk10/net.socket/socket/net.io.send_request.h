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
// net::io::send_request::CBase
//
// 1. net::io::send_request::CBase��!
//    1) send�� ���� ������ ���޿����� �ϴ� Class��.
//    2) send���� �� �����ϰų� ó���ؾ��� ���� ������ �� Class�� ��ӹ޾� ����
//       ��Ų��.
//
// 2. CGDK.net.socket�� �ٽ�! Function�� ��� ����
//    1) request_send	request_send�Լ����� process_sendable()�Լ��� ȣ���ϵ���
//						�Ǿ� �ִ�.
//
//
//-----------------------------------------------------------------------------
class net::io::send_request::Nbase :
	virtual public				net::io::Isendable,
	virtual public				net::io::Isend_request
{
public:
	virtual ~Nbase() noexcept {}
	virtual	bool				request_send(const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _paddress) override
								{
									return	this->process_sendable(_buffer, std::move(_powner), _count_message, _paddress);
								}
	virtual	void				reset_send_request() noexcept override {}
};


}