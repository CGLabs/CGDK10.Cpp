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
// 1. net::io::send_request::CBase란!
//    1) send의 수행 과정중 전달역할을 하는 Class임.
//    2) send과정 중 변경하거나 처리해야할 것이 있으면 이 Class를 상속받아 변경
//       시킨다.
//
// 2. CGDK.net.socket의 핵심! Function의 기능 설명
//    1) request_send	request_send함수에서 process_sendable()함수를 호출하도록
//						되어 있다.
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