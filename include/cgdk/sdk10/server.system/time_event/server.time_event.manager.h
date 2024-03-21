//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Event Classes                            *
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
// ----------------------------------------------------------------------------
// 1. Event System이란?
//
//    1) 각종 System을 제작하다보면 일정시간마다 실행을 하거나 특정한 시간에 실행
//       해야하는 것들을 설정할 필요가 있다.
//       이때 특정한 시간이나  특정한 시간마다 실행하도록 하는 시스템이 Event 시스템이다.
//
//    2) Event System은 Event Object와 entity manager로 나뉘어진다.
//       - entity manager는 등록된 EventObject를 등록하였다가 정해진 시간마다 실행해주는
//         관리자를 의미한다.
//       - Event Object는 entity manager에 등록되어 동작하는 객체로 필요에 따라
//         다양한 실행형태로 제작되어져 있다. 
//         선언된 Event Object는 아래와 같은 것들이 있다.
//
//         @ time_event::object::once
//           예약된 시간에 딱 1회만 실행되는 객체
//
//         @ time_event::object::start_end
//           예약된 시작시간과 종료시간에 각각 정해진 함수를 호출하는 객체
//
//         @ time_event::object::start_iteration_end
//           예약된 시작시간에 정해진 함수가 호출되며 이후에 정해진 간격에 따라
//           정해진 함수를 정해진 실행횟수만큼 호출해주는 Event 객체이다.
//           실행횟수만큼 호출된 후 process_event_end()함수가 호출된다.
//
//         @ Ctime_eventIteration
//           정해진 시간 간격 마다 정해진 함수를 무한반복적으로 실행해하는
//           Event객체이다.
//
//    3) 각 Event객체들은 특정한 시간에 호출되어지는 virtual함수들이 정의되어 있다.
//       이 virtual함수를 재정의하여 실행하고자하는 내용을 작성하면 된다.
//
//    4) Event객체의 정밀도는 초단위 수준만을 보장하므로 더욱 정밀한 실행이 필요할
//       경우 Executable이나 다른 방법을 사용하기를 권장한다.
//
//    5) Event System에서의 시간은 모두 System Time을 사용하고 있다. System Time은
//       Local Time과 동일하지 않기 때문에 실제 지역 시간과는 다를 수 있으므로 
//       설정을 할때는 반드시 System Time으로 설정할 필요가 있다.
//
//
// 2. 주요함수.
//    1) register_event()/unregister_event()/unregister_event_all()
//       각각 Event 객체를 등록하거나 등록해제하거나 혹은 모든 Event object를 등록
//       해제하는 함수이다.
//       (*일반적으로 이 함수를 직접쓰지는 않고 IEventObject의 register(), unregister()
//         함수를 더 많이 사용한다.)
//
//    2) begin()/end()
//       - entity manager에 등록된 모든 Event객체를 얻고자 할 때 사용하는 함수이다.
//       - 이때 주의해야하는 것은 안전한 실행을 위해 반드시 Lock을 건 이후에 
//         begin()함수를 호출하여 Event Object에 접근하라는 것이다.
//
//    3) Delete Done Event Option
//       - 완료가 된 Event object를 제거할 것인가 그대로 남겨둘 것인가를 설정하는
//         옵션이다.
//       - set_delete_done_event()함수를 사용해 설정할 수 있다. true로 설정할 경우
//         완료된 Event객체는 List에서 자동으로 제거하게 된다.
//       - 기본 설정치는 true이다.
//
// ----------------------------------------------------------------------------
class time_event::entity_manager : 
	public						Nexecutor,
	protected					api::threads,
	public						CGDK::object::Ninitializable_startable,
	virtual public				CGDK::object::Iupdatable,
	public						CGDK::object::Iattachable<Ientity>,
	virtual public				Nmessage_transmitter
{
public:
	using iterator_t		 = std::set<object_ptr<time_event::Ientity> >::iterator;
	using const_iterator_t = std::set<object_ptr<time_event::Ientity> >::const_iterator;

protected:
			entity_manager();
	virtual ~entity_manager() noexcept;

public:
			bool				register_entity(const object_ptr<Ientity>& _pentity) { return this->process_attach(object_ptr<Ientity>(_pentity));}
			bool				register_entity(object_ptr<Ientity>&& _pentity) { return this->process_attach(std::move(_pentity));}
			bool				unregister_entity(Ientity* _pentity) noexcept { return this->process_detach(_pentity); }
			object_ptr<Ientity>	unregister_entity(uint64_t _id_entity) noexcept;
			void				unregister_event_all() noexcept;
	[[nodiscard]] object_ptr<Ientity> find_event(uint64_t _id_event) const noexcept;
	[[nodiscard]] bool			is_exist(Ientity* _pentity) const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<std::set<object_ptr<Ientity>>>&>(this->m_set_time_entity)); return this->_is_exist(_pentity); }
	[[nodiscard]] bool			is_exist(uint64_t _id_entity) const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<std::set<object_ptr<Ientity>>>&>(this->m_set_time_entity)); return this->_is_exist(_id_entity); }

			bool				register_class(std::string_view _class_name, std::function<own_ptr<time_event::Ientity>()>& _f_register);
			bool				unregister_class(std::string_view _class_name);

			void				enable_delete_done_entity(bool _status = true) noexcept { this->m_is_delete_done_entity = _status; }
			void				disable_delete_done_entity() noexcept { this->m_is_delete_done_entity = false;}
	[[nodiscard]] bool			is_delete_done_entity() const noexcept { return this->m_is_delete_done_entity;}

	[[nodiscard]] size_t		size() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<std::set<object_ptr<Ientity>>>&>(this->m_set_time_entity)); return this->m_set_time_entity.size(); }
	[[nodiscard]] bool			empty() const noexcept { return this->size() == 0; }
	[[nodiscard]] bool			exist() const noexcept { return this->size() != 0; }

	[[nodiscard]] auto			begin() noexcept { return this->m_set_time_entity.begin();}
	[[nodiscard]] auto			begin() const noexcept { return this->m_set_time_entity.begin();}
	[[nodiscard]] auto			end() noexcept { return this->m_set_time_entity.end();}
	[[nodiscard]] auto			end() const noexcept { return this->m_set_time_entity.end();}
	[[nodiscard]] auto&			get_lockable() noexcept { return this->m_set_time_entity;}
	[[nodiscard]] const auto&	get_lockable() const noexcept { return this->m_set_time_entity;}
	[[nodiscard]] 				operator lock_object&() noexcept { return this->get_lockable();}
	[[nodiscard]] 				operator const lock_object& () const noexcept { return this->get_lockable(); }

	[[nodiscard]] auto			executor() const noexcept { scoped_lock(m_cs_pexecutor) { return this->m_pexecutor; } }
			void				executor(const object_ptr<Iexecutor>& _pexecutor) noexcept { this->executor(object_ptr<Iexecutor>(_pexecutor)); }
			void				executor(object_ptr<Iexecutor>&& _pexecutor) noexcept { scoped_lock(m_cs_pexecutor) { this->m_pexecutor = std::move(_pexecutor); } }

	static	auto				instance() { if(m_pinstance.empty()){ initialize_instance();} return object_ptr<entity_manager>(m_pinstance);}
	static	void				initialize_instance();
	static	void				initialize_instance(context& _context);
	static	void				set_instance(own_ptr<entity_manager>&& _pinstance) noexcept;
	static	void				reset_instance() noexcept;
	static	void				detach_instance() noexcept { m_pinstance.detach(); }

protected:
	virtual	void				on_initializing(context& _context) override;
	virtual	void				on_initialize(context& _context) override;
	virtual	void				on_destroying() override;
	virtual	void				on_destroy() override;

	virtual	void				on_starting(context& _context) override;
	virtual	void				on_start(context& _context) override;
	virtual	void				on_stopping() override;
	virtual	void				on_stop() override;

	virtual	result_code			process_update(context& _context) override;

public:
	virtual	bool				process_post(object_ptr<Iexecutable>&& _pexecutable) override;
	virtual	bool				process_execute(chrono::tick::duration _ticks_wait, intptr_t _option) override;

			void				process_notify_next_time_changed(time_event::Ientity* _ptime_entity);

	virtual	bool				process_attach(object_ptr<Ientity>&& _pentity) override;
	virtual	bool				process_detach(Ientity* _pentity) noexcept override;

			void				_push_time_entity(Ientity* _pentity);
			void				_pop_time_entity() noexcept;
			bool				_process_detach(Ientity* _pentity) noexcept;
			bool				_is_exist(Ientity* _pentity) const noexcept;
			bool				_is_exist(uint64_t _id_entity) const noexcept;

public:
			bool				m_is_delete_done_entity;

private:
			std::atomic<int>	m_flag_run;
			lockable<>			m_cs_pexecutor;
			object_ptr<Iexecutor> m_pexecutor;
			lockable<std::map<std::string, std::function<own_ptr<time_event::Ientity>()>>> m_map_time_class;
			lockable<std::set<object_ptr<Ientity>>> m_set_time_entity;
			std::vector<Ientity*>	m_priorityqueue_time_entity;
			std::mutex				m_lock_priorityqueue;
			std::condition_variable	m_cv_priorityqueue_exist;
			std::condition_variable	m_cv_priorityqueue_in_time;

			class executable_time_entity;
			friend class executable_time_entity;
			friend class Ientity;

	static	uint32_t			fn_thread(time_event::entity_manager* _this);

protected:
	static own_ptr<entity_manager> m_pinstance;
	static lockable<>			m_lockable_create;
};


}