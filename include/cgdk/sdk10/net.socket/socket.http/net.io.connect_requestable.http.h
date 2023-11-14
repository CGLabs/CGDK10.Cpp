//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        network socket http classes                        *
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
// net::io::connect_requestable::Nhttp (Web용 연결자)
//
// 1. net::io::connect_requestable::Ntcp이란!
//    1) TCP socket을 Client 입장에서 접속을...
//    2) 
//    3) 기본적으로 Inameable을 상속받아 이름을 설정할 수 있다.
//
// 2. 중요 함수.
//    1) 일반적인 사용은 net::io::Iconnect_requestable에 정의된 다양한 형태의 connect(...)
//		 함수를 활용한다.
//    2) 만약 connect를 요청했을 때 처리되어야 하는 것이 있다면 다음의 함수를
//       재정의하여 구현할 수 있다.
//
//       virtual void on_request_connect( const net::sockaddr& _paddress_peer);
//
//    주의) Iexecutable을 상속받아 처리하므로 이 클래스를 상속받은 클래스에서
//          process_execute()를 재정의하면 접속처리가 되지 않을 수 있다.
// 
//
//-----------------------------------------------------------------------------
class net::io::connect_requestable::Nhttp :
// inherited classes) 
	public						net::io::connect_requestable::Ntcp_secure
{
// publics) 
public:
	// 1) connect 함수
	virtual	bool				connect(Ihttp_request* _prequest);
			bool				connect(const std::string_view _url);
	
// implementation) 
protected:
			lockable<object_ptr<Ihttp_request>>	m_prequest;

protected:
			void				set_request(Ihttp_request* _prequest) noexcept;
			void				reset_request() noexcept;
			object_ptr<Ihttp_request> move_request() noexcept;

protected:
	virtual	uint16_t			process_get_default_port() noexcept override { return (m_pssl_context.empty()) ? 80 : 443; }
};


}
