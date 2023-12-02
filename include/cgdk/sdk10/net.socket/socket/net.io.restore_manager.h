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
// net::io::restore_manager
//
// 1. binder은~
//    1) socket의 bind() 기능이 있는 클래스로 기본적으로 UDP의 bind를 위한 것이다.
//
//
//-----------------------------------------------------------------------------
class net::io::restore_manager :
	public						schedulable::Nexecutable,
	public						object::Nnameable,
	virtual public				object::Idestroyable
{
public:
			restore_manager();
	virtual	~restore_manager() noexcept;

public:
			void				restore_restorable(Irestore_server* _prestore_server, buffer_view _buffer);
			bool				suspend_restorable(Irestore_server* _prestore_server, uint64_t _disconnect_reason)  noexcept;

			void				set_suspend_timeout(chrono::tick::duration _tick_duration);
	[[nodiscard]] auto			get_suspend_timeout() const noexcept { return m_tick_timeout;}

public:
	// 1) Init Instance/run_executor
	static 	auto				instance() { if (m_pinstance.empty()) { initialize_instance(); } return object_ptr<restore_manager>(m_pinstance); }
	static	void				initialize_instance();
	static	void				set_instance(own_ptr<restore_manager>&& _pinstance) noexcept;
	static	void				reset_instance() noexcept;
	static	void				detach_instance() noexcept { m_pinstance.detach(); }

protected:
	// 2) destroy
	virtual	result_code			destroy() noexcept override;

	// 3) 새로운 Restorable을 할당한다.
	virtual	object_ptr<Irestorable_server> process_alloc_restorable();
			RESTORE_CLIENT_ID	process_generate_RESTORE_CLIENT_ID();

	// 4) on_execute
	virtual	void				on_execute() override;

	// 5) Restore Server ID
			RESTORE_SERVER_ID	m_id_restore_server;
			lockable<std::map<RESTORE_CLIENT_ID, object_ptr<Irestorable_server>>> m_map_restorable;

			chrono::tick::duration	m_tick_timeout;

	// 6) Instance
	static own_ptr<restore_manager> m_pinstance;
	static std::mutex			m_lockable_create;
};


}