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
// net::io::connectable::Ntcp
//
// 1. net::io::connectable::Ntcp이란!
//    1) TCP용 Iconnectable을 정의한 클래스이다.
//    2) TCP로 접속을 시도하여 접속처리가 완료되었을 때(성공했을때나 실패했을 때나)
//       이 클래스가 이후 처리과정을 정의하게 된다.
//    3) 이 클래스는 Overlapped I/O를 사용한 receive를 처리하도록 정의되었으므로
//       접속 후 receive()를 걸도록 작성되었다.
//    4) 접속이 성공할 경우 on_connect()함수를 호출하고 실패했을 경우 on_fail_connect()를
//       호출한다.
//    5) 접속이 종료되었을 때 on_disconnect()함수를 호출하도록 정의되어 있다.
//    6) 접속을 종료를 요구할 때 disconnect()함수를 호출하면 되며 이는 Graceful
//       close를 수행하게 된다.
//       주의) 만약 Abortive close를 사용하고자 한다면 Isocket의 closesocket()함수를
//             사용하도록 한다.
//
//
//-----------------------------------------------------------------------------
class net::io::connectable::Ndummy :
// inherited classes)
	virtual public				net::io::Iconnectable,
	virtual public				net::io::Ireceivable_stream
{
// publics) 
// - 사용자가 이 socket을 사용자가 조작하기 위한 함수.
public:
	// 1) disconnect.(Graceful)
	virtual	bool				disconnect (uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept override;

// frameworks)
// - 이 함수들을 재정의 함으로써 프로그래밍을 한다.
// - 어떠한 작업이 수행되었을 때 불려지는 함수이다.
protected:
	//! @brief 접속이 되었을 때 호출된다. @param _pconnective 접속을 요청한 connective
	virtual void				on_request_connect (const net::sockaddr& /*_address*/) {}
	virtual void				on_connect (net::io::Iconnective* /*_pconnective*/) {}
	virtual void				on_disconnect (uint64_t /*_disconnect_reason*/) {}
	virtual void				on_fail_connect (net::io::Iconnective* /*_pconnective*/, uint64_t /*_disconnect_reason*/) {}

// implementation) 
protected:
	// 1) connect관련
	virtual	void				process_request_connect (const net::sockaddr& _address) override;
	virtual bool				process_complete_connect (net::io::Iconnective* _pconnective, uintptr_t _result) override;// 1) 접속되었을 때의 처리 절차를 정의하는 함수.
	virtual bool				process_complete_disconnect () override;// 2) 종료되었을 때의 처리 절차를 정의하는 함수.

	virtual void				process_on_connect (net::io::Iconnective* _pconnective) { on_connect(_pconnective); }
	virtual	void				process_on_disconnect (uint64_t _disconnect_reason, eSOCKET_STATE /*_socket_state*/) { on_disconnect(_disconnect_reason); }
	virtual	void				process_on_fail_connect (net::io::Iconnective* _pconnective, uint64_t _disconnect_reason) { on_fail_connect(_pconnective, _disconnect_reason); }

	// 3) reset할때 호출하는 함수.
	virtual	void				process_reset_connectable () noexcept override;
};


}