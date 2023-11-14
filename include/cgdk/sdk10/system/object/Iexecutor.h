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

 @class		Iexecutor
 

*///-----------------------------------------------------------------------------
class thread_list
{
public:
	~thread_list() { CGASSERT_ERROR(this->m_vector_thread.empty()); }

public:
	using ITERATOR = std::vector<object_ptr<api::thread>>::iterator;
	using CONST_ITERATOR = std::vector<object_ptr<api::thread>>::const_iterator;

			auto				begin() { return this->m_vector_thread.begin();}
			auto				begin() const { return this->m_vector_thread.begin();}
			auto				end() { return this->m_vector_thread.end();}
			auto				end() const { return this->m_vector_thread.end();}
			auto&				get_lockable() noexcept { return this->m_vector_thread; }
			const auto&			get_lockable() const noexcept { return this->m_vector_thread; }
			auto				reserved_size() const noexcept { return this->m_vector_thread.size(); }
								operator lock_object&() noexcept { return this->get_lockable();}
								operator const lock_object&() const noexcept { return this->get_lockable(); }
protected:
	lockable<std::vector<object_ptr<api::thread>>> m_vector_thread;
};

class Iexecutor : 
	virtual public				thread_list,
	virtual public				object::Iidentifiable,
	virtual public				object::Inameable,
	virtual public				object::Istartable
{
public:
	virtual ~Iexecutor() noexcept {}

public:
			bool				post(object_ptr<Iexecutable>&& _pexecutable) { return this->process_post(std::move(_pexecutable)); }
			bool				post(const object_ptr<Iexecutable>& _pexecutable) { return this->process_post(object_ptr<Iexecutable>(_pexecutable)); }
			bool				execute(chrono::tick::duration _tick_diff, intptr_t _option = 0) { return this->process_execute(_tick_diff, _option); }
			bool				control(uint64_t _command, uint64_t _param) noexcept { return this->process_control(_command, _param); }
	[[nodiscard]] const auto&	statistics() const noexcept { return this->m_statistics;}


protected:
	virtual	bool				process_post(object_ptr<Iexecutable>&& _pexecutable) PURE;
	virtual	bool				process_execute(chrono::tick::duration _ticks_wait, intptr_t _option) PURE;
	virtual	bool				process_control(uint64_t /*_command*/, uint64_t /*_param*/) noexcept { return false; }
	virtual	void				process_idle() noexcept;
			void				process_reset_statistics() noexcept;

			void				process_register_executor();
			void				process_unregister_executor() noexcept;

			lockable<>			m_lock_manager;
			object_ptr<executor::manager> m_pmanager;

			statistics::executor m_statistics;
			statistics::unit_executor_snap m_statistics_snap;

			friend class executor::manager;
			friend class system_executor;
};


}