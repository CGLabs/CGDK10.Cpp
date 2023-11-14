//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
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
/**

 @class		manager_thread


*///-----------------------------------------------------------------------------
class api::manager_thread :
// inherited classes)
	public						object::Nnameable,
	virtual public				Nmessage_transmitter,
	virtual public				object::Idestroyable,
	virtual public				Ischedulable,
	public						factory::_traits_system

{
public:
		using TCONTAINER = std::vector<Nthread*>;
		using ITERATOR = TCONTAINER::iterator;
		using CONST_ITERATOR = TCONTAINER::const_iterator;

public:
			manager_thread() noexcept;
	virtual ~manager_thread() noexcept;

// public)
public:
			void				start_deadlock_observing(chrono::tick::duration _tick_threshold = 2s);
			void				stop_deadlock_observing() noexcept;
			void				check_deadlock();

			auto				deadlock_threshold() const noexcept	{ return m_tick_diff_deadlock_threshold;}
			void				deadlock_threshold(chrono::tick::duration _tick) noexcept {	m_tick_diff_deadlock_threshold=_tick;}

			auto				observing_interval() const noexcept	{ return m_tick_differ_observing;}
			void				observing_interval(chrono::tick::duration _tick) noexcept {	m_tick_differ_observing=_tick;}

	[[nodiscard]] size_t		size() const noexcept { return m_list_thread.size(); }
	[[nodiscard]] bool			empty() const noexcept { return m_list_thread.empty(); }
	[[nodiscard]] bool			exist() const noexcept { return !empty(); }
	[[nodiscard]] auto			begin() noexcept { return m_list_thread.begin();}
	[[nodiscard]] auto			begin() const noexcept { return m_list_thread.begin(); }
	[[nodiscard]] auto			end() noexcept { return m_list_thread.end();}
	[[nodiscard]] auto			end() const noexcept { return m_list_thread.end(); }
	[[nodiscard]] auto&			get_lockable() noexcept { return m_lockable_list_thread;}
	[[nodiscard]] const auto&	get_lockable() const noexcept { return m_lockable_list_thread;}
	[[nodiscard]]				operator std::shared_mutex&() noexcept { return m_lockable_list_thread;}
	[[nodiscard]]				operator const std::shared_mutex& () const noexcept { return m_lockable_list_thread; }

	static 	auto				instance() { if (m_s_pinstance.empty()) { initialize_instance(); } return object_ptr<manager_thread>(m_s_pinstance); }
	static	void				initialize_instance();
	static	void				set_instance(own_ptr<manager_thread>&& _instance) noexcept;
	static	void				reset_instance() noexcept;
	static	void				detach_instance() noexcept { m_s_pinstance.detach(); }

	static	object_ptr<Nthread>	get_default_thread_object() { return instance()->m_pthread_default;}

private:
			bool				register_thread(Nthread* _pthread);
			bool				unregister_thread(Nthread* _pthread);

	virtual	bool				process_on_register() override { return true;}
	virtual	void				process_on_unregister() override {}
	virtual	bool				process_schedule() override;

private:
			std::shared_mutex	m_lockable_list_thread;
			TCONTAINER			m_list_thread;

			object_ptr<Nthread> m_pthread_default;

			chrono::tick::time_point m_tick_observing_last;
			chrono::tick::duration m_tick_differ_observing;
			chrono::tick::duration m_tick_diff_deadlock_threshold;
			std::atomic<int>	m_enable_observing_deadlock;

	static std::mutex			m_s_lockable_create;
	static own_ptr<manager_thread> m_s_pinstance;

	friend	class Nthread;

private:
	virtual	result_code			destroy() noexcept override;
};


}