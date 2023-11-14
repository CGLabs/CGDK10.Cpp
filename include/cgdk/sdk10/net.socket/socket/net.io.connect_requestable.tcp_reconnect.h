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

//-----------------------------------------------------------------------------
//
// net::io::connect_requestable::Ntcp_reconnect (자동재접속 기능을 가진 TCP 연결자)
//
// 1. net::io::connective::Ntcp_reconnect이란!
//    1) 자동 재접속 기능이 있는 connect_requestable이다.
//    2) net::io::connect_requestable::Ntcp을 상속받아 접속 종료시 자동 재접속 기능을 추가
//       한 것이다.
//
// 2. 핵심 함수들.
//    1) 재접속은 기본적으로 connect()를 했을 때 하나의 주소에만 이루어진다.
//    2) 필요에 따라 여러 주소로 재접속을 수행할 수 있다.
//       - 접속이 종료되면 등록된 주소들에 차례대로 접속요구를 수행하게 된다.
//
//		 - 접속할 주소를 추가하고 삭제할 수 있다.
//			bool add_peer_address((const ::sockaddr* _paddress_peer);
//			bool remove_peer_address(const ::sockaddr* _paddress_peer);
//          void remove_all_peer_address();
//
//    3) 접속은 connect함수를 사용하여 수행한다.
//    4) Address를 넣지 않을 경우 등록된 peer주소로 접속을 시도한다.
//    5) 아래의 함수를 사용하여  재접속 기능을 켜거나 끌 수 있다.
//       
//       void enable_reconnect(bool _enable=true);
//       void disable_reconnect();
//
//       is_enable()함수를 사용하여 재접속 기능의 동작여부를 확인할 수 있다.
//
//       bool is_enable() const
//
//    6) 재접속 시도  시간을 조절하거나 얻을 수 있다.
//       재접속 시도는 마지막 접속을 성공한 시점에서 부터 계산이 된다.
//       따라서 접속한 이후 재접속 시도 시간을 초과해 접속이 종료되었을 경우
//       바로 재접속이 수행된다.
//
//       void			set_reconnect_interval(chrono::tick::duration p_tick);
//       chrono::tick::duration get_reconnect_interval() const;
//
//    7) 재접속 시 마다 어떠한 기능이 수행되어야 한다면 다음 virtual함수를
//       재정의하여 기능을 추가할 수 있다.
//
//       virtual void on_request_reconnect(net::io::Iconnective* _pconnective);
// 
//    
//    주의) 접속을 종료할 때는 반드시 아래와 같이 disable_reconnect()함수를 
//          먼저 호출하여 재접속 기능을 비활성화 한후 접속을 종료해야 한다.
//
//           psocket->disable_reconnection();
//           psocket->closesocket();
//
// 3. initialize/start String
//
//	  1) "reconnection"
//	     - "enable"				재접속 활성화
//       - "disable"			재접속 비활성화
//	     - "default"			기본값(비활성화)
//
//	  2) "reconnection_interval"
//	     재접속을 시도하는 간격. ms단위이다. 즉 1000은 1초를 의미한다.  
//
//    예)  객체명이 "foo"이라고 한다면....
//
//		   sMESSAGE msg_context;
//         context_setting["foo"]["reconnection"] = false;
//         context_setting["foo"]["reconnection_interval"] = 1000;
//
//-----------------------------------------------------------------------------
class CGDK::net::io::connect_requestable::Ntcp_reconnect :
// inherited classes) 
	public						net::io::connect_requestable::Ntcp,
	virtual public				net::io::Ireconnectable,
	virtual public				net::io::Iconnectable_notify
{
// constructor/destructor)
protected:
			Ntcp_reconnect() noexcept;
			Ntcp_reconnect(std::string_view _name);
	virtual	~Ntcp_reconnect() noexcept;

// framework)
protected:
	// 2) 재접속을 시도하기 전 호출되는 함수.
	virtual	void				on_request_reconnect(net::io::Iconnective* /*_pconnective*/) {}

// implementation) 
protected:
	// 3) request_connect
	virtual	bool				process_request_connecting(const net::sockaddr& _address_peer) override;
	virtual	void				process_complete_connecting(uintptr_t _result) override;
	virtual	void				process_connective_connect(net::io::Iconnectable* _pconnectable, uintptr_t _result) override;
	virtual	void				process_connective_disconnect(net::io::Iconnectable* _pconnectable) noexcept override;

	// 4) start/stop
	virtual result_code			process_start(context& _context) override;
	virtual result_code			process_stop() noexcept override;

public:
	// 5) Reconnect를 수행하는 함수이다.
			bool				process_wait_reconnect();
			void				process_request_reconnect();
			void				process_cancel_reconnector() noexcept;
public:
			class manager_reconnector;
private:
			object_ptr<manager_reconnector>	m_pmanager_reconnector;
public:
	static	void				detach_instance() noexcept;
};
