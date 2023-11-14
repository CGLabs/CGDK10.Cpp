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
// net::io::connective::connector::Ntcp
//
//-----------------------------------------------------------------------------
class net::io::connective::connector::Ntcp :
	virtual public				net::io::connective::Iconnector,
	public						object::Nnameable,
	public                      object::Ninitializable_startable
{
public:
			Ntcp() {}
			Ntcp(std::string_view _name) : Nnameable(_name) {}

public:
	[[nodiscard]] virtual object_ptr<Iconnectable> alloc_connectable() override;

	[[nodiscard]] virtual std::size_t allocated_socket_count() const noexcept override { return m_socket_count_allocated;}
	[[nodiscard]] virtual std::size_t max_socket_count () const noexcept override { return m_max_allocate;}
	virtual void				set_max_socket_count (std::size_t _max_allocate) noexcept override { m_max_allocate = _max_allocate; }
	[[nodiscard]] virtual end_point_type get_default_endpoint() const noexcept override { return m_default_endpoint; };
	virtual void				set_default_endpoint(const end_point_type& _default_endpoint) override { m_default_endpoint = _default_endpoint; }

	// 3) executor
	virtual void				io_context (executor::Iio_context* _pio_context) noexcept override { m_pio_context = _pio_context;}
	[[nodiscard]] virtual object_ptr<executor::Iio_context> io_context () const noexcept override { return m_pio_context;}

protected:
	virtual void				on_alloc_connectable (net::io::Iconnectable* /*_pconnectable*/) {}
	virtual	void				on_request_connect (net::io::Iconnectable* /*_pconnectable*/, context& /*_context_connect*/) {}
	virtual	void				on_connect (net::io::Iconnectable* /*_pconnectable*/)	{}
	virtual	void				on_disconnect (net::io::Iconnectable* /*_pconnectable*/, uint64_t /*_disconnect_reason*/)	{}
	virtual	void				on_fail_connect (net::io::Iconnectable* /*_pconnectable*/, uint64_t /*_disconnect_reason*/) {}

protected:
	virtual result_code			_process_starting (context& _context) override;
	virtual result_code			_process_stopping () noexcept override;
	virtual result_code			_process_stop () noexcept override;
	virtual result_code			_process_destroy () noexcept override;

			void				_process_disable_reconnectable ();
			void				_process_connectable_connective_set(Iconnectable* _pconnectable) noexcept;
			void				_process_connectable_connective_reset(Iconnectable* _pconnectable) noexcept;
	virtual	void				process_connective_connect (net::io::Iconnectable* _pconnectable, uintptr_t _result) override;
	virtual	void				process_connective_disconnect (net::io::Iconnectable* _pconnectable) override;

	[[nodiscard]] virtual object_ptr<Iconnectable> process_alloc_connectable() PURE;

	virtual	bool				process_set_enable(bool _is_state) override;
	virtual	bool				process_get_enable() const override;

	virtual	object_ptr<Iconnectable> process_request_connect (context& _context_connect) override;
	virtual	bool				process_connecting (Iconnectable* _pconnectable, context& _context_connect) override;

			std::atomic<int>	m_is_enable = 0;
			std::atomic<size_t>	m_socket_count_allocated = 0;
			std::size_t			m_max_allocate = SIZE_MAX;
			end_point_type		m_default_endpoint;
			bool				m_enable_progress_log = true;

			object_ptr<executor::Iio_context> m_pio_context;

			class executable_connective;

		#if defined(_SYS_EPOLL_H)
		#endif
};


}