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
// 1. Event System�̶�?
//
//    1) ���� System�� �����ϴٺ��� �����ð����� ������ �ϰų� Ư���� �ð��� ����
//       �ؾ��ϴ� �͵��� ������ �ʿ䰡 �ִ�.
//       �̶� Ư���� �ð��̳�  Ư���� �ð����� �����ϵ��� �ϴ� �ý����� Event �ý����̴�.
//
//    2) Event System�� Event Object�� entity manager�� ����������.
//       - entity manager�� ��ϵ� EventObject�� ����Ͽ��ٰ� ������ �ð����� �������ִ�
//         �����ڸ� �ǹ��Ѵ�.
//       - Event Object�� entity manager�� ��ϵǾ� �����ϴ� ��ü�� �ʿ信 ����
//         �پ��� �������·� ���۵Ǿ��� �ִ�. 
//         ����� Event Object�� �Ʒ��� ���� �͵��� �ִ�.
//
//         @ time_event::object::once
//           ����� �ð��� �� 1ȸ�� ����Ǵ� ��ü
//
//         @ time_event::object::start_end
//           ����� ���۽ð��� ����ð��� ���� ������ �Լ��� ȣ���ϴ� ��ü
//
//         @ time_event::object::start_iteration_end
//           ����� ���۽ð��� ������ �Լ��� ȣ��Ǹ� ���Ŀ� ������ ���ݿ� ����
//           ������ �Լ��� ������ ����Ƚ����ŭ ȣ�����ִ� Event ��ü�̴�.
//           ����Ƚ����ŭ ȣ��� �� process_event_end()�Լ��� ȣ��ȴ�.
//
//         @ Ctime_eventIteration
//           ������ �ð� ���� ���� ������ �Լ��� ���ѹݺ������� �������ϴ�
//           Event��ü�̴�.
//
//    3) �� Event��ü���� Ư���� �ð��� ȣ��Ǿ����� virtual�Լ����� ���ǵǾ� �ִ�.
//       �� virtual�Լ��� �������Ͽ� �����ϰ����ϴ� ������ �ۼ��ϸ� �ȴ�.
//
//    4) Event��ü�� ���е��� �ʴ��� ���ظ��� �����ϹǷ� ���� ������ ������ �ʿ���
//       ��� Executable�̳� �ٸ� ����� ����ϱ⸦ �����Ѵ�.
//
//    5) Event System������ �ð��� ��� System Time�� ����ϰ� �ִ�. System Time��
//       Local Time�� �������� �ʱ� ������ ���� ���� �ð����� �ٸ� �� �����Ƿ� 
//       ������ �Ҷ��� �ݵ�� System Time���� ������ �ʿ䰡 �ִ�.
//
//
// 2. �ֿ��Լ�.
//    1) register_event()/unregister_event()/unregister_event_all()
//       ���� Event ��ü�� ����ϰų� ��������ϰų� Ȥ�� ��� Event object�� ���
//       �����ϴ� �Լ��̴�.
//       (*�Ϲ������� �� �Լ��� ���������� �ʰ� IEventObject�� register(), unregister()
//         �Լ��� �� ���� ����Ѵ�.)
//
//    2) begin()/end()
//       - entity manager�� ��ϵ� ��� Event��ü�� ����� �� �� ����ϴ� �Լ��̴�.
//       - �̶� �����ؾ��ϴ� ���� ������ ������ ���� �ݵ�� Lock�� �� ���Ŀ� 
//         begin()�Լ��� ȣ���Ͽ� Event Object�� �����϶�� ���̴�.
//
//    3) Delete Done Event Option
//       - �Ϸᰡ �� Event object�� ������ ���ΰ� �״�� ���ܵ� ���ΰ��� �����ϴ�
//         �ɼ��̴�.
//       - set_delete_done_event()�Լ��� ����� ������ �� �ִ�. true�� ������ ���
//         �Ϸ�� Event��ü�� List���� �ڵ����� �����ϰ� �ȴ�.
//       - �⺻ ����ġ�� true�̴�.
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