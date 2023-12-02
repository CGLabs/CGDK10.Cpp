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
// net::io::send_request::Nproxy
//
// 1. net::io::send_request::Nproxy란!
//    1) 다른 send_request를 포인팅하고 있다가 Request가 수행되면 포인팅된
//		 send_request를 수행하는 class이다.
//    2) 음...
//
//
// 2. net::io::send_request::CProxy의 기능 설명
//    1) set_send_request/get_send_request
//		 Isend_request를 설정하고 얻어내는 함수이다.
//
//
//-----------------------------------------------------------------------------
class net::io::send_request::Nproxy :
// inherited classes)
	virtual public				net::io::Isend_request
{
// constructor/destructor)
protected:
			Nproxy() noexcept : m_psend_request(nullptr) {}
	virtual	~Nproxy() noexcept {}

// publics)
public:
	// 1) send할 때 부르는 함수.
	virtual	bool				request_send( const buffer_view* _array_buffer, std::size_t _count_buffer, Ireferenceable* _powner, std::size_t _count_message, const net::sockaddr& _paddress) override	{ return m_psend_request->request_send(_array_buffer, _count_buffer, _powner, _count_message, _paddress); }

	// 2) sendable 설정/얻기 함수.
			void				set_send_request( Isend_request* p_pSendRequest) noexcept { m_psend_request = p_pSendRequest;}
			Isend_request*		get_send_request() const noexcept { return m_psend_request;}

// implementations)
protected:
	virtual	void				reset_send_request() noexcept override { m_psend_request = nullptr;}

private:
			Isend_request*		m_psend_request;
};


}