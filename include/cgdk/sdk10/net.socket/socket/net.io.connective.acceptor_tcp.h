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
// net::io::connective::acceptor::Ntcp
//
// 2. context paramters
//
//	  1) "local_endpoint" (�ʼ�)
//		listen�� �ּҿ� ��Ʈ�� �ǹ��Ѵ�.
//      �ݵ�� �ϵ��� ������ �ִ� �ּҿ��� �ϸ� �Ϲ������� �ּҴ� bind_any(0)���� ����ϸ�
//		port�� �����ϴ� ���·� ���� ���ȴ�.
//		�ּҸ� �������� ���� ��� bind_any(0)�� �����Ǹ� ���� ȣ��Ʈ�� ��� �ּҷκ��� ������ �޾Ƶ��δ�.
//
//		 - "address"			
//		 - "service" or "port"	
//		 - "flag" => "ai_passive", "ai_canonname", "ai_numberichost", "ai_v4mapped", "ai_all", "ai_addrconfig", "default"
// 
//	  2) "accept_endpoint" (optional)
//		 �ܺο��� ���Ӱ����� �ּҸ� ������ �� �ִ�. ���ۿ��� ���� ������ ��ġ�� �ʴ� �ܼ� ����� �������̰� �о� �� ���� �ִ�.
//		 NAT�� ���� ���� ���ܺ� �ּҰ� �ٸ� ��� ���� ������ �ּ� ������ �����ϴ� �ǹ̸� �ִ�.
//
//		 - "address"
//		 - "service" or "port"	port of accept
//		 - "flag" => "ai_passive", "ai_canonname", "ai_numberichost", "ai_v4mapped", "ai_all", "ai_addrconfig", "default"
//
//	  3) "prepare_on_start" (optional)
//		 listen�� ������ �� �̸� �غ��� ���� ������ ���ڸ� �ǹ��Ѵ�.
//		 ������ ���۰� ���ÿ� ���� ����ڰ� ���� ��� �� ���� ũ�� ���־� �ʱ� ���� ��ü ������ ��ȭ�� �� �ִ�.
// 	     �ʱ⿡ �غ��� ������ �����Ǹ� 'must_prepare'���Ϸ� �پ��� �������� ���ο� �������� �غ����� �ʴ´�.
//		 ���� �⺻��(0)���� ������ ��� CPU�� �ھ� ���� ����� �ڵ������� �����ȴ�.
//
//	  4) "must_prepare" (optional)
//		 ���� ����ų �ּ� ������ ���� �ǹ��Ѵ�.
//		 ���� �� �� ���Ϸ� ���� ��� ���� ���� �پ�� ��� �ű� ������ ������ ������ �ּ� �� ���� ������Ų��.
// 	     ���� ������ �޸� ��뷮�� ���� �� �ִ� �ݸ� �׸�ŭ ���� �ð��� �ִ� ���� ó�� �ɷ��� ������ �� �ִ�.
//		 ���� �⺻��(0)���� ������ ��� CPU�� �ھ� ���� ����� �ڵ������� �����ȴ�.
//
//    ��) ��뿹
//
//			auto pacceptor = make_own<net::acceptor<foo_socket>>("foo");
//
//			context param;
//			param["foo"]["local_endpoint"]["address"]  = "127.0.0.1";
//			param["foo"]["local_endpoint"]["port"]	   = 20000;
//			param["foo"]["prepare_on_start"]		   = 256;
//			param["foo"]["must_prepare"]			   = 32;
//
//			pacceptor->start(param);
//
// 3. struct paramters
// 	   context parameter�� ������ ���ڵ��� �̸� ���ǵ� START_PARAMETER ����ü�� ����� ������ �� �ִ�.
// 
//		struct START_PARAMETER
//		{
//			end_point_type		local_endpoint;
//			end_point_type		accept_endpoint;
//			std::size_t			prepare_on_start = 0;
//			std::size_t			must_prepare = 0;
//			uint64_t			flag_option = 0;
//		};
//		
// 	   �� ��� ������ context parameter�� ������ key�� ���� parameter�̴�.
// 
//    ��) ��뿹
//
//			auto pacceptor = make_own<net::acceptor<foo_socket>>("foo");
//
//			net::acceptor<foo_socket>::START_PARAMETER start_parameter;
//			start_parameter.local_endpoint	  = {make_address("127.0.0.1"), 20000};
//			start_parameter.prepare_on_start  = 256;
//			start_parameter.must_prepare      = 32;
//
//			pacceptor->start(param);
// 
// 
//-----------------------------------------------------------------------------
class net::io::connective::acceptor::Ntcp :
// inherited classes)
	virtual public				net::io::connective::Iacceptor,
	public						object::Nnameable,
	public                      object::Ninitializable_startable,
	virtual public				Imessage_transmitter
{
// constructor/destructor)
public:
			Ntcp() { register_connective(); }
			Ntcp(std::string_view _name) : Nnameable(_name) { register_connective(); }
	virtual	~Ntcp() { unregister_connective(); }

	// 1) start function
			result_code			start() { return this->object::Nstartable::start();}
			result_code			start(const START_PARAMETER& _parameter) { return this->object::Nstartable::start<START_PARAMETER>(_parameter); }
			result_code			start(const context& _context) { context context_copy(_context); return this->start(context_copy);}
	virtual	result_code			start(context& _context) override { return this->object::Ninitializable_startable::start(_context); }

// public)
public:
	// 2) socket status
	[[nodiscard]] virtual std::size_t allocated_socket_count() const noexcept override { return this->m_socket_count_allocated;}
	virtual void				set_max_socket_count(std::size_t _max_allocate) noexcept override { this->m_max_allocate= _max_allocate; }
	[[nodiscard]] virtual std::size_t max_socket_count() const noexcept override { return this->m_max_allocate; }
	[[nodiscard]] virtual std::size_t prepared_socket_count() const noexcept override { return this->m_socket_count_prepared_to_accept;}
	[[nodiscard]] virtual std::size_t must_prepare_socket_count() const noexcept override { return this->m_accept_count_must_prepare;}

	// 3) address
	[[nodiscard]] virtual end_point_type get_accept_endpoint() const noexcept override;
	virtual	void				set_accept_endpoint(const end_point_type& _accept_endpoint) noexcept override;
	virtual	void				reset_accept_endpoint() noexcept override;

// frameworks)
protected:
	//! @brief �ʱ�ȭ�Ǳ� �� ȣ��ȴ�.(on_destroy()�Լ��� ¦�Լ���.) @param _msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				on_initializing(context& /*_context*/) override {}
	virtual	void				on_initialize(context& /*_context*/) override {}
	virtual	void				on_destroying() override {}
	virtual	void				on_destroy() override {}

	//! @brief �ʱ�ȭ�Ǳ� �� ȣ��ȴ�.(on_destroy()�Լ��� ¦�Լ���.) @param _msg �ʱ�ȭ �Ҷ� ���޵� �޽���
	virtual	void				on_starting(context& /*_context*/) override {}
	virtual	void				on_start(context& /*_context*/) override {}
	virtual	void				on_stopping () override {}
	virtual	void				on_stop() override {}

	//! @brief Accept�� ��û���� �� ȣ��ȴ�. @param _pconnectable Aceept�� ���� ��ü
	virtual	void				on_request_accept(net::io::Iconnectable* /*_pconnectable*/) {}
	virtual	void				on_accept(net::io::Iconnectable* /*_pconnectable*/) {}
	virtual	void				on_fail_accept(net::io::Iconnectable* /*_pconnectable*/) {}

	//! @brief Accept�� Abort�Ǿ� ȸ���� �� ���� �Ǿ��� �� ȣ��ȴ�.
	virtual	void				on_accept_aborted() {}
	virtual	void				on_accept_recovered() {}
	virtual	void				on_prepare_socket() {}
	virtual	void				on_closesocket(uint64_t /*_disconnect_reason*/) {}

	//! @brief Accept �ޱ� ���� �ʿ��� Iconnectable ��ü�� �Ҵ� �޴� ���� �޽��(Factory Method) @ return �Ҵ�� Iconnectable ��ü
	[[nodiscard]] virtual object_ptr<Iconnectable> process_alloc_connectable () PURE;

	// 4) set parameters
	virtual void				process_set_parameters(context& _context);

	// 5) set default port
	[[nodiscard]] virtual uint16_t process_get_default_port() noexcept { return 0; }

// implementation) 
protected:
	// 6) start/stop Process
	virtual result_code			_process_starting (context& _context) override;
	virtual result_code			_process_start (context& _context) override;
	virtual result_code			_process_stopping () noexcept override;
	virtual result_code			_process_stop () noexcept override;

#if defined(_SYS_EPOLL_H)
	object_ptr<socket::Ntcp>	_process_starting_uds(const START_PARAMETER& _parameter);
#endif
	// 7) destroy
	virtual result_code			_process_destroy () noexcept override;

	// 8) enable/disable
	virtual	bool				process_set_enable(bool _is_state) override;
	virtual	bool				process_get_enable() const override;

	// 9) connect/disconnect Process
	virtual void				process_on_accept (Iconnectable* _pconnectable) { on_accept(_pconnectable);}
	virtual void				process_on_fail_accept(Iconnectable* _pconnectable) noexcept { try { on_fail_accept(_pconnectable); } catch (...) {} }
	virtual	void				process_connective_connect (Iconnectable* _pconnectable, uintptr_t _result) override;
	virtual	void				process_connective_disconnect (Iconnectable* _pconnectable) override;

	// 10) socket Process
	virtual	void				process_create_socket(ADDRESS_FAMILY _address_family) override;
	virtual	void				process_prepare_socket (ADDRESS_FAMILY _address_family) override;
	virtual void				process_dispose_socket() noexcept override;
	virtual	bool				process_close_socket (uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept override;

	// 11) Accept
	#if defined(_WINSOCK2API_)
			void				request_accept(ADDRESS_FAMILY _address_family);
			void				process_request_retry_accept();
			bool				_process_request_retry_accept();
			void				process_retry_accept();
			class executable_retry_request_accept;
			bool				m_retry_accept_now = false;
			lockable<>			m_lockable_retry_accept_now;
	#elif defined(_SYS_EPOLL_H)
			bool				request_accept(CGSOCKET _handle_socket, ADDRESS_FAMILY _address_family);
			void				process_connective_accept(uintptr_t _result);
	static	void				proceoss_closesocket_fail(net::io::Iconnectable* _pconnectable, uint64_t _disconnect_reason) noexcept;
	#endif

	// 12) member variable
			std::atomic<int>	m_is_enable = 0;
			std::size_t			m_accept_count_must_prepare = 0;
			std::atomic<size_t>	m_socket_count_prepared_to_accept = 0;
			std::atomic<size_t>	m_socket_count_allocated = 0;
			std::size_t			m_max_allocate = SIZE_MAX;
			end_point_type		m_listen_endpoint;
			end_point_type		m_accept_endpoint;
			bool				m_enable_progress_log = true;

	// 13) IP6 Option
			int					m_is_ip6_only = 0;

	// 14) executable
			class executable_connective;

	#if defined(_SYS_EPOLL_H)
			class executable_accept;
			object_ptr<Ireferenceable> m_pexecutable_accept;

			bool				m_enable_uds = false;

			object_ptr<socket::Ntcp> m_psocket_uds;
	#endif
};


}