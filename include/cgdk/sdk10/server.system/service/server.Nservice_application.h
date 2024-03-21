//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Admin Classes                            *
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
// Nservice_application
//
// 
//-----------------------------------------------------------------------------
class server_system::Nservice_application :
	public						Nstatic_service_logger,
	public						Iservice,
	public						object::Nnameable,
	public                      object::Ninitializable_startable,
	public						object::Npausable,
	virtual public				Imessageable,
	virtual public				Nmessage_transmitter,
	virtual public				Ilogger
{
protected:
			Nservice_application();
	virtual	~Nservice_application();

public:
			result_code			start() { return object::Nstartable::start(); }
	virtual	result_code			start(context& _context) override;
	virtual	result_code			stop() noexcept override;
	virtual	result_code			pause() override;
	virtual	result_code			resume() override;

	[[nodiscard]] virtual eOBJECT_STATE get_object_state() const noexcept override ;
	virtual	eOBJECT_STATE		set_object_state(eOBJECT_STATE _status) noexcept override;
	virtual	bool				set_object_state_if(eOBJECT_STATE _status_compare, eOBJECT_STATE _status) noexcept  override;

protected:
	virtual	void				on_service_setting (context& /*_context*/) {}

	virtual	void				on_initializing (context& /*_context*/) override {}
	virtual	void				on_initialize (context& /*_context*/) override {}
	virtual	void				on_destroying () override {}
	virtual	void				on_destroy () override {}

	virtual	void				on_starting (context& /*_context*/) override {}
	virtual	void				on_start (context& /*_context*/) override {}
	virtual	void				on_stopping () override {}
	virtual	void				on_stop () override {}

	virtual	void				on_pausing () override {}
	virtual	void				on_pause () override {}
	virtual	void				on_resuming () override {}
	virtual	void				on_resume () override {}

	virtual	void				on_process_interrogate (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_shutdown (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_param_change (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_net_bind_add (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_net_bind_remove (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_net_bind_enable (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_net_bind_disable (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_device_event (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_hardware_profile_change (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_power_event (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_session_change (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_pre_shutdown (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_time_change (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}
	virtual	void				on_process_trigger_event (uint32_t /*_type*/, void* /*_pevent_data*/, void* /*_pcontext*/) {}

	virtual result_code			process_message (sMESSAGE& /*_msg*/) override { return 0;}

	virtual	result_code			process_initialize (context& _context);
	virtual	result_code			process_destroy () noexcept;
	virtual	result_code			process_start (context& _context);
	virtual	result_code			process_stop () noexcept;

	virtual result_code			_process_initializing (context& _context) override;
	virtual result_code			_process_starting (context& _context) override;

	virtual	void				process_interrogate (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_shutdown (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_param_change (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_net_bind_add (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_net_bind_remove (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_net_bind_enable (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_net_bind_disable (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_device_event (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_hardware_profile_change (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_power_event (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_session_change (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_pre_shutdown (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_time_change (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_trigger_event (uint32_t _type, void* _pevent_data, void* _pcontext);

	virtual	int					process_service_main (int _argc, char** _pargv, __callback LPHANDLER_FUNCTION_EX _lp_handler_proc);
	virtual	uint32_t			process_service_handler (uint32_t _dwControl, uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_service_start (context& _context);
	virtual	void				process_service_stop ();
	virtual	void				process_service_pause (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_service_continue (uint32_t _type, void* _pevent_data, void* _pcontext);
	virtual	void				process_service_run ();

#if defined(__linux__)
	static	void				process_signal_stop(int _signal);
	static  void				process_signal_pause(int _signal);
	static	void				process_signal_continue(int _signal);
	static	void				process_signal_hup(int _signal);
	static	void				process_signal_interrupt(int _signal);
	static	void				process_signal_quit(int _signal);
	static	void				process_signal_segment_fault(int _signal);
#endif
	virtual	void				process_state_changed(eOBJECT_STATE _state_new, eOBJECT_STATE _state_old) override;

	virtual	void				process_log(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) override;

			int					process_run(int _argc = 0, char** _pargv = nullptr);

#if defined(_WIN32)
	static	uint32_t CALLBACK	fservice_main(int _argc, char** _pargv);
	static	DWORD	CALLBACK	fservice_handler(DWORD _Control, DWORD _type, LPVOID _pevent_data, LPVOID _pcontext);
	static	bool				process_service_parpare(int _argc, char** _ppargv, Nservice_application* _pservice);
#elif defined(__linux__)
	static	bool				process_service_parpare(int _argc, char** _ppargv);
#else
#endif
			OBJ<api::server_status_handle>	m_handle_server_status;
			std::atomic<eOBJECT_STATE>		m_status_object;

			std::mutex						m_lock_complete;
			std::condition_variable			m_cv_complete;

	static	own_ptr<Nservice_application> m_pinstance;
	static	lockable<>			m_lockable_create;
};


}