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
// net::io::Nrestorable_client
//
// 1. net::io::Nrestorable_client는~
//    1) Restore 기능을 제공하는 socket용 Client쪽 Component이다.
//
//
//    2) 주요 기능은...
//
//       - 접속이 상대에 의해 종료되었을 경우 재접속시 복원 가능하도록 한다.
//       - 다만 주의할 점은 접속이 종료된 socket으로 다시 재접속 요청해야
//         복원 기능이 작동된다.
//
//
//    3) Hook 함수들
//
//       - on_connecting()
//         실제 물리적으로 접속이 되었을 때 호출된다.
//
//       - on_connect()
//         물리적 접속 이후 복원까지 모두 되었을 때 호출된다.
//
//       - on_suspend()
//         접속이 상대에 의해 끊김 처리 이후에 호출된다.
//
//       - on_restoring()
//         재접속후 복원 과정이 시작될 때 호출된다.
//         만약 처음 접속시나 복원 정보가 유실되어 reset된 경우 호출되지 않는다.
//
//       - on_restore()
//         재접속 후 복원이 완료되었을 때 호출된다.
//
//       - OnDisconnecting()
//         물리적으로 접속 종료되었을 때 호출된다.
//
//       - on_disconnect()
//         접속이 종료되었을 때 호출된다.
//
//
//    4) 동작
//
//       - 물리적으로 처음 접속을 하게 되면 무조건 on_connecting이 호출된다.
//
//       - 클라이언트 측에서의 요청에 의해 접속이 종료된 것이 아니라면 
//         on_disconnect가 바로 호출되지 않고 나중에 재접속 시 복원을 준비하며
//         on_disconnect대신 on_suspend()함수가 호출된다.
//
//       - 추후 재접속이 되게 되면 on_restoring()과 on_restore()함수가 호출된다.
//
//       - 클라이언트 쪽에서 closesocket()이나 disconnect()를 호출할 때는
//         바로 suspend에 들어가지 않고 바로 on_disconnect()가 호출된다.
//
//       - suspend 상태에서 closesocket이나 disconnect()를 호출할 때도
//         on_disconnect()가 호출된다.
//         
//       - on_disconnect()가 호출되면 이후로는 재접속 되더라도 복원(Restore)가
//         되지 않는다.
//
//
//    5) 함수의 pairing 처리
//
//       - on_connecting()함수가 호출 된 이후 접속이 종료되더라도 on_disconnect()
//         함수는 호출되지 않는다.
//
//       - on_restoring()함수가 호출되다 Exception이 발생되거나 더이상 처리하지
//         못할 경우 바로 on_disconnect()가 호출된다.
//       - on_restore()함수가 호출되던 중 Exception이 발생하게 되었을 때도
//         on_disconnect()가 호출된다 따라서 on_restore()함수중 오류가 발생되면
//         on_restoring에서 처리된 것도 복원해야 한다.
//
//       - on_suspend()함수가 호출되다 Exception이 발생하면 on_disconnect()함수가
//         호출된다.
//
//
//-----------------------------------------------------------------------------
class net::io::Nrestorable_client : 
	public						net::io::connect_requestable::Ntcp_reconnect,
	public						net::io::connectable::Ntcp,
	virtual public				Irestorable
{
protected:
	virtual	void				on_socket_connect() { request_io_restore();}
	virtual	void				on_socket_disconnect() {}

	virtual	void				on_connect () override {}
	virtual	void				on_suspend (uint64_t /*_disconnect_reason*/) {}
	virtual	void				on_restoring () {}
	virtual	void				on_restore () {}
	virtual	void				on_disconnect (uint64_t /*_disconnect_reason*/) override	{}

protected:
	virtual void				process_on_connect () override;
	virtual	void				process_on_disconnect (uint64_t _disconnect_reason, eSOCKET_STATE _socket_state) override;
	virtual	void				process_on_fail_connect (uint64_t _disconnect_reason) override;

	virtual	void				process_on_restoring ();
	virtual	void				process_on_restore ();
	virtual	bool				process_on_suspend (uint64_t _disconnect_reason);

	virtual	void				process_request_io_restore	(result_code _result, SEQUENCE_ID _ack_received) override;
	virtual	void				process_response_io_restore	(result_code _result, SEQUENCE_ID _ack_received) override;
	virtual	void				process_complete_io_restore	(result_code _result) override;
};


}