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
// 1. net::io::send_request::Nproxy��!
//    1) �ٸ� send_request�� �������ϰ� �ִٰ� Request�� ����Ǹ� �����õ�
//		 send_request�� �����ϴ� class�̴�.
//    2) ��...
//
//
// 2. net::io::send_request::CProxy�� ��� ����
//    1) set_send_request/get_send_request
//		 Isend_request�� �����ϰ� ���� �Լ��̴�.
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
	// 1) send�� �� �θ��� �Լ�.
	virtual	bool				request_send( const buffer_view* _array_buffer, std::size_t _count_buffer, Ireferenceable* _powner, std::size_t _count_message, const net::sockaddr& _paddress) override	{ return m_psend_request->request_send(_array_buffer, _count_buffer, _powner, _count_message, _paddress); }

	// 2) sendable ����/��� �Լ�.
			void				set_send_request( Isend_request* p_pSendRequest) noexcept { m_psend_request = p_pSendRequest;}
			Isend_request*		get_send_request() const noexcept { return m_psend_request;}

// implementations)
protected:
	virtual	void				reset_send_request() noexcept override { m_psend_request = nullptr;}

private:
			Isend_request*		m_psend_request;
};


}