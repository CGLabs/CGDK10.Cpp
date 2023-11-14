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
// net::io::connect_requestable::Ntcp (TCP 연결자)
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
//    주의) Iexecutable을 상속받아 처리하므로 이 클래스를 상속받은 클래스에서
//          process_execute()를 재정의하면 접속처리가 되지 않을 수 있다.
// 
// 3. initialize/start string
//
//	  1) "remote_endpoint"
//	     - "address_format"	address format ("ipv4", "ipv6", "ipv6_prefer", "ipv4_prefer", "default") (optional:default="ipv4")
//       - "address"			접속할 주소
//	     - "port"				접속할 포트
//
//	  2) "local_endpoint" or "bind_endpoint"
//	     - "address_format"	address format ("ipv4", "ipv6", "ipv6_prefer", "ipv4_prefer", "default") (optional:default="ipv4")
//       - "address"			bind 주소
//	     - "port"				bind 포트
//
//	  3) "block_until_connecting_completed"
//	     - "true"				접속처리가 완료될 때까지 기다린다.(blocking한다.)
//       - "false"				기본값. 접속처리 완료를 기다리지 않고 바로 진행한다.(non-blocking)
//	     - "default"			기본값(false)
//
//    예)  객체명이 "foo"이라고 한다면....
//
//		   sMESSAGE msg_context;
//         context_setting["foo"][remote_endpoint]["address_format"] = "ipv6";	// "ipv4", "ipv4_prefer", "ipv6", "ipv6_prefer"
//         context_setting["foo"][remote_endpoint]["address"]		 = "192.168.0.100";
//         context_setting["foo"][remote_endpoint]["port"]			 = 20000;
//         context_setting["foo"][block_until_connecting_completed]			 = true;
//
//
//-----------------------------------------------------------------------------
class CGDK::net::io::connect_requestable::Ntcp :
	public						object::Nnameable,
	public						object::Ninitializable_startable,
	public						net::io::binder::Ntcp,
	virtual public				net::io::Iconnect_requestable,
	virtual public				net::io::Iconnectable,
	virtual public				Icryptable
{
public:
			using end_point_type = net::ip::tcp::endpoint;
			using START_PARAMETER = sSOCKET_CONNECT_REQUEST_PARAMETER;

protected:
			Ntcp();
			Ntcp(std::string_view _name);
	virtual	~Ntcp() noexcept;

public:
			result_code			start() { return this->object::Nstartable::start();}
			result_code			start(const START_PARAMETER& _parameter) { return this->object::Nstartable::start<START_PARAMETER>(_parameter); }
			result_code			start(const context& _context) { context context_copy(_context); return this->start(context_copy); }
	virtual	result_code			start(context& _context) override { return this->object::Ninitializable_startable::start(_context); }

			result_code			wait_complete_connecting(chrono::tick::duration _duration_wait= chrono::seconds(30));
			result_code			wait_complete_closed(chrono::tick::duration _duration_wait = chrono::seconds(30));

			void				enable_block_until_connecting_completed(bool _flag_enable = true) noexcept { this->m_enable_block_until_connecting_completed = _flag_enable; }
			void				disable_block_until_connecting_completed() noexcept { this->m_enable_block_until_connecting_completed = false; }
	[[nodiscard]] bool			block_until_connecting_completed() const noexcept { return this->m_enable_block_until_connecting_completed; }

			void				enable_block_until_disconnecting_completed(bool _flag_enable = true) noexcept { this->m_enable_block_until_disconnecting_completed = _flag_enable; }
			void				disable_block_until_disconnecting_completed() noexcept { this->m_enable_block_until_disconnecting_completed = false; }
	[[nodiscard]] bool			block_until_disconnecting_completed() const noexcept { return this->m_enable_block_until_disconnecting_completed; }

public:
	virtual	void				process_reset_connector() noexcept override;
	virtual bool				process_request_connecting(const net::sockaddr& _address) override;
	virtual	void				process_complete_connecting( uintptr_t _result) override;

	virtual	result_code			process_start(context& _context) override;
	virtual	result_code			process_stop() noexcept override;

	virtual	uint16_t			process_get_default_port() noexcept { return 0; }

protected:
			result_code			m_result_connecting = eRESULT::NOT_DEFINED;
			bool				m_enable_block_until_connecting_completed = false;
			bool				m_enable_block_until_disconnecting_completed = true;
			bool				m_enable_progress_log = true;
};

inline CGDK::object_ptr<CGDK::net::io::Iconnectable> CGDK::net::io::connective::Iconnector::request_connect(end_point_type _endpoint_remote, end_point_type _endpoint_bind)
{
	sSOCKET_CONNECT_REQUEST_PARAMETER parameter;
	parameter.remote_endpoint = _endpoint_remote;
	parameter.bind_endpoint = _endpoint_bind;

	context context_connect{ buffer_view((char*)&parameter, sizeof(parameter)) };
	return this->request_connect(context_connect);
}
inline bool CGDK::net::io::connective::Iconnector::request_connect(Iconnectable* _pconnectable, end_point_type _endpoint_remote, end_point_type _endpoint_bind)
{
	sSOCKET_CONNECT_REQUEST_PARAMETER parameter;
	parameter.remote_endpoint = _endpoint_remote;
	parameter.bind_endpoint = _endpoint_bind;

	context context_connect{ buffer_view((char*)&parameter, sizeof(parameter)) };
	return this->process_connecting(_pconnectable, context_connect);
}
