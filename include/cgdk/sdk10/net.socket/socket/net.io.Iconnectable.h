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
// net::io::Iconnectable
//
// 1. net::io::Iconnectable은~
//    1) 접속이 필요한 socket에 필요한 connectable이다.
//    2) 일반적으로 TCP socket이나 Reliable UDP에 사용된다.
//    3) TCP socket의 경우 Server측이나 Client측이나 모두 접속이 필요하므로 
//       TCP socket은 모두 ICGConnectable을 상속받은 것이다.
//    4) 접속 후 처리 과정을 작성하는 클래스로 아래와 같은 주요 함수가 있다.
//
//       - bool process_complete_connect(uintptr_t _result);
//         접속 완료 후 처리과정을 정의하는 함수이다.
//
//       - bool process_complete_disconnect();
//         접속 종료 후 접속 종료처리과정을 정의하는 함수이다.
//
//       - bool disconnect();
//         접속 종료 요구의 처리를 정의하는 함수이다.
//
//    5) ICGConnectable은 접속이 성립되거나 혹은 접속 처리가 실패한 후 처리 과정을
//       정의하는 클래스이다. 
//       접속을 요구하는 클래스는 Iconnect_requestable와 connective::Iacceptor를 사용해야
//       한다.
// 
// 
//-----------------------------------------------------------------------------
class net::io::Iconnectable : 
	virtual	public				net::io::Isocket,
	virtual public				net::io::statistics::Nsocket
{
public:
			Iconnectable() noexcept {}
	virtual ~Iconnectable() noexcept {}

public:
	// 1) disconnect를 수행할 때 부르는 함수이다.(Graceful)
	virtual	bool				disconnect(uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept PURE;

public:
	// 1) reset할때 호출하는 함수.(기본은 빈것...)
	virtual	void				process_reset_connectable() noexcept PURE;
	// 2) Accept/connect를 요청할 때
	virtual	void				process_request_connect (const net::sockaddr& _address) PURE;
	// 3) CompleteConnect
	virtual	bool				process_complete_connect (uintptr_t _result) PURE;
	virtual	bool				process_complete_disconnect () PURE;

public:
	// 4) connective
			Iconnectable_notify* m_pconnectable_notify = nullptr;
			flexible<32>		m_flexible;
			circular_list<Iconnectable*>::iterator	m_iter_connectable;
			void				set_as_client_socket() noexcept { this->m_is_client_socket = true; }
}
;


}