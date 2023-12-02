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

 @class		Ischedulable
 

*///-----------------------------------------------------------------------------
class Ischedulable : virtual public object::Iidentifiable, virtual public Ireferenceable
{
public:
			Ischedulable() noexcept;
	virtual ~Ischedulable() noexcept {}

public:
			void				next_tick(const chrono::tick::time_point& _tick_next) { this->m_tick_next = _tick_next; }
	[[nodiscard]] auto			next_tick() const noexcept { return this->m_tick_next; }

	[[nodiscard]] auto			schedulable_manager() const noexcept { return this->m_pschedulable_manager; }
	[[nodiscard]] auto			executor() const noexcept { scoped_lock(this->m_cs_pexecutor) { return this->m_pexecutor; } }
			void				executor(const object_ptr<Iexecutor>& _pexecutor) noexcept { this->executor(object_ptr<Iexecutor>(_pexecutor)); }
			void				executor(object_ptr<Iexecutor>&& _pexecutor) noexcept { scoped_lock(this->m_cs_pexecutor) { this->m_pexecutor = std::move(_pexecutor); } }
	[[nodiscard]] bool			has_executor() const noexcept { scoped_lock(this->m_cs_pexecutor) { return this->m_pexecutor.exist(); } }

	[[nodiscard]] const auto&	statistics() const noexcept { return this->m_statistics_schedulable;}

public:
	virtual	bool				process_on_register() PURE;
	virtual	void				process_on_unregister() PURE;
	virtual	bool				process_schedule() PURE;

protected:
			lockable<>			m_cs_pexecutor;
			object_ptr<Iexecutor> m_pexecutor;

			object_ptr<schedulable::manager> m_pschedulable_manager;
			chrono::tick::time_point m_tick_next = (chrono::tick::max)();
			statistics::schedulable m_statistics_schedulable;

			friend class schedulable::manager;
};


}