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

 @class		Default
 @brief		내부적으로 자동 생성되는 기본 executor이다.
 @todo		
 @ref		
 @details	\n
 내부적으로 사용되는 모든 실행처리에 사용되는 싱글턴 executor이다.
 내부적으로 다중 쓰레드 executor와 SingleExecutor와 schedulable_manager를 가지고 있다.
 기본적으로는 자동생성되나 초기화기 필요할 경우 initialize_instance()를 호출해 초기화할 수도 있다.
 실행요청은 post(...)함수로 가능하며 register_schedulable로 Scheudler에 등록할 수도 있다.
 소멸처리도 자동으로 되기 때문에 다른 처리를 해줄 필요도 없다.


  configure
			"thread_count" => "default", "auto", "no thread", number
			"enable_thread_observer" => "default", "enable", "disable"

*///-----------------------------------------------------------------------------
class system_executor : 
	public						object::Nnameable,
	public						object::Nstate,
	public						object::Ninitializable,
	public						Idisposable::Nno_act,
	public						factory::_traits_system
{
public:
	using schedulable_manager_t = schedulable::manager;
	using executable_scheduler_t = executor::scheduler;
	using factory_sustain_t = schedulable::system::factory_sustain;
	using thread_observer_t = schedulable::system::exception_observer;

protected:
			system_executor() noexcept;
	virtual ~system_executor() noexcept;

public:
	static	void				initialize_instance(size_t _count_thread = CGEXECUTOR_AUTO);
	static	void				initialize_instance(context& _context);
	static	void				destroy_instance() noexcept;
	static	void				detach_instance() noexcept;
	static	system_executor*	instance() { if(m_s_instance.m_pexecutable_scheduler.empty()) initialize_instance(); return &m_s_instance;}
	static	system_executor*	peek_instance() noexcept { if (m_s_instance.m_pexecutable_scheduler.empty()) return nullptr; return &m_s_instance; }

	static	auto				executor() { if(m_s_instance.m_psystem_executor.empty()) initialize_instance(); return object_ptr<executor::Iio_context>(m_s_instance.m_psystem_executor); }
	static	auto				schedulable_manager() { if(m_s_instance.m_pschedulable_manager.empty()) initialize_instance(); return object_ptr<schedulable_manager_t>(m_s_instance.m_pschedulable_manager);}
	static	auto				scheduler() { if(m_s_instance.m_pexecutable_scheduler.empty()) initialize_instance(); return object_ptr<executable_scheduler_t>(m_s_instance.m_pexecutable_scheduler);}
	[[nodiscard]] static size_t	thread_count() noexcept;					  
		
	static	void				run_executor();

	static	bool				start_factory_garbage_collection();
	static	bool				stop_factory_garbage_collection() noexcept;
	static	bool				start_thread_observer();
	static	bool				stop_thread_observer() noexcept;

	static	bool				post(object_ptr<Iexecutable>&& _pexecutable) { return executor()->post(std::move(_pexecutable)); }
	static	bool				post(const object_ptr<Iexecutable>& _pexecutable) { return post(object_ptr<Iexecutable>(_pexecutable)); }

	static	bool				post(object_ptr<Iexecutable>&& _pexecutable, chrono::tick::time_point _tick_execute) { return scheduler()->post_at(std::move(_pexecutable), _tick_execute); }
	static	bool				post(object_ptr<Iexecutable>&& _pexecutable, chrono::tick::duration _duration) { return scheduler()->post_at(std::move(_pexecutable), _duration); }
	static	bool				post(const object_ptr<Iexecutable>& _pexecutable, chrono::tick::time_point _tick_execute) { return post(object_ptr<Iexecutable>(_pexecutable), _tick_execute); }
	static	bool				post(const object_ptr<Iexecutable>& _pexecutable, chrono::tick::duration _duration) { return post(object_ptr<Iexecutable>(_pexecutable), _duration); }

	static	bool				register_schedulable(object_ptr<Ischedulable>&& _pschedulable);
	static	bool				register_schedulable(const object_ptr<Ischedulable>& _pschedulable) { return register_schedulable(object_ptr<Ischedulable>(_pschedulable)); }
	static	bool				unregister_schedulable(Ischedulable* _pschedulable) noexcept;

private:
	static std::mutex			m_s_lockable_create;
	static system_executor		m_s_instance;

public:
	[[nodiscard]] auto			_executor() noexcept { return object_ptr<executor::Iio_context>(this->m_psystem_executor); }
	[[nodiscard]] auto			_schedulable_manager() noexcept { return object_ptr<schedulable_manager_t>(this->m_pschedulable_manager); }
	[[nodiscard]] auto			_scheduler_singly() noexcept { return object_ptr<executable_scheduler_t>(this->m_pexecutable_scheduler); }

private:
	virtual	result_code			process_initialize(context& _context) override;
	virtual	result_code			process_destroy() noexcept override;
			void				process_detach() noexcept;
	virtual	result_code			destroy() noexcept override { return object::Ninitializable::destroy();}

			own_ptr<executor::Iio_context> m_psystem_executor;
			own_ptr<executable_scheduler_t> m_pexecutable_scheduler;
			own_ptr<schedulable_manager_t> m_pschedulable_manager;
			object_ptr<factory_sustain_t> m_pschedulable_factory_garbage_collection;
			object_ptr<thread_observer_t> m_pschedulable_thread_observer;
			std::recursive_mutex m_lockable_lock;
			size_t				m_init_param = CGEXECUTOR_AUTO;
};


}
