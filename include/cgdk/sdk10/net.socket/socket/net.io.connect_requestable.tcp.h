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
// net::io::connect_requestable::Ntcp (TCP ������)
//
// 1. net::io::connect_requestable::Ntcp�̶�!
//    1) TCP socket�� Client ���忡�� ������...
//    2) 
//    3) �⺻������ Inameable�� ��ӹ޾� �̸��� ������ �� �ִ�.
//
// 2. �߿� �Լ�.
//    1) �Ϲ����� ����� net::io::Iconnect_requestable�� ���ǵ� �پ��� ������ connect(...)
//		 �Լ��� Ȱ���Ѵ�.
//    2) ���� connect�� ��û���� �� ó���Ǿ�� �ϴ� ���� �ִٸ� ������ �Լ���
//       �������Ͽ� ������ �� �ִ�.
//
//    ����) Iexecutable�� ��ӹ޾� ó���ϹǷ� �� Ŭ������ ��ӹ��� Ŭ��������
//          process_execute()�� �������ϸ� ����ó���� ���� ���� �� �ִ�.
// 
// 3. initialize/start string
//
//	  1) "remote_endpoint"
//	     - "address_format"	address format ("ipv4", "ipv6", "ipv6_prefer", "ipv4_prefer", "default") (optional:default="ipv4")
//       - "address"			������ �ּ�
//	     - "port"				������ ��Ʈ
//
//	  2) "local_endpoint" or "bind_endpoint"
//	     - "address_format"	address format ("ipv4", "ipv6", "ipv6_prefer", "ipv4_prefer", "default") (optional:default="ipv4")
//       - "address"			bind �ּ�
//	     - "port"				bind ��Ʈ
//
//	  3) "block_until_connecting_completed"
//	     - "true"				����ó���� �Ϸ�� ������ ��ٸ���.(blocking�Ѵ�.)
//       - "false"				�⺻��. ����ó�� �ϷḦ ��ٸ��� �ʰ� �ٷ� �����Ѵ�.(non-blocking)
//	     - "default"			�⺻��(false)
//
//    ��)  ��ü���� "foo"�̶�� �Ѵٸ�....
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
