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

 @class		Cschedulable
 @brief		ICGScheduable 겍체를 실행해주는 executor로 시스템 내부용으로 사용된다.
 @todo		
 @ref		
 @details	\n
 execute()함수는 등록된 Ischedulable 객체를 실행해 준다.
 일반적으로 Ischedulable에서는 일정시간마다 

*///-----------------------------------------------------------------------------
class schedulable::manager :
	public						CGDK::Nexecutor,
	public						api::threads,
	public						object::Iattachable<Ischedulable>,
	public						factory::_traits_system
{
public:
	manager() noexcept;
	manager(std::string_view _name) noexcept;
	virtual ~manager() noexcept;

public:
			using CONTAINER = std::set<object_ptr<Ischedulable>>;
			struct START_PARAMETER
			{
			};

public:
			result_code			start() { context _context; return this->start(_context);}
			result_code			start(const START_PARAMETER& _parameter) { context temp(buffer_view((char*)&_parameter, sizeof(START_PARAMETER))); return this->start(temp); }
			result_code			start(const context& _context) { context context_copy(_context); return this->start(context_copy);}
	virtual	result_code			start(context& _context) override;
	virtual	result_code			stop() noexcept override;

			bool				register_schedulable(object_ptr<Ischedulable>&& _pschedulable) { return this->process_attach(std::move(_pschedulable));}
			bool				unregister_schedulable(Ischedulable* _pschedulable) noexcept { return this->process_detach(_pschedulable) != 0;}

	[[nodiscard]] ITERATOR		get_iterator() noexcept;
	[[nodiscard]] size_t		size() const noexcept { return this->m_set_schedulable.size(); }
	[[nodiscard]] bool			empty() const noexcept { return this->size() == 0; }
	[[nodiscard]] bool			exist() const noexcept { return this->size() != 0; }
	[[nodiscard]] auto			begin() { return this->m_set_schedulable.begin();}
	[[nodiscard]] auto			begin() const { return this->m_set_schedulable.begin();}
	[[nodiscard]] auto			end() { return this->m_set_schedulable.end();}
	[[nodiscard]] auto			end() const { return this->m_set_schedulable.end();}
	[[nodiscard]] auto&			get_lockable() noexcept { return this->m_lockable_set_schedulable; }
	[[nodiscard]] const auto&	get_lockable() const noexcept { return this->m_lockable_set_schedulable; }
	[[nodiscard]] 				operator std::shared_mutex&() noexcept{ return this->get_lockable();}
	[[nodiscard]] 				operator const std::shared_mutex& () const noexcept { return this->get_lockable(); }
			void				print_statistics() noexcept;

protected:
	virtual	bool				process_post(object_ptr<CGDK::Iexecutable>&& _executable) override;
	virtual	bool				process_execute(chrono::tick::duration _ticks_wait, intptr_t _option) override;

	virtual	bool				process_attach(object_ptr<Ischedulable>&& _pschedulable) override;
	virtual	bool				process_detach(Ischedulable* _pschedulable) noexcept override;

			void				process_execute_schedulable(object_ptr<Ischedulable>&& _pschedulable);
			void				process_cancel_schedulable_all() noexcept;

			void				_push_schedulable(object_ptr<Ischedulable>&& _pschedulable);
			void				_pop_schedulable() noexcept;

private:
			std::atomic<int>	m_flag_run;
			std::shared_mutex	m_lockable_set_schedulable;
			std::set<object_ptr<Ischedulable>> m_set_schedulable;
			std::vector<Ischedulable*> m_priorityqueue_schedulable;
			std::mutex				m_lockable_priorityqueue;
			std::condition_variable	m_cv_priorityqueue_exist;
			std::condition_variable	m_cv_priorityqueue_in_time;

			class executable_schedulable;
			friend class executable_schedulable;

protected:
	static	uint32_t			fn_thread(schedulable::manager* _this);
};


}