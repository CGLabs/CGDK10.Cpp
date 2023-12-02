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
//
// time_event::entity
//
//
// ----------------------------------------------------------------------------
class time_event::entity :
	virtual public				time_event::Ientity
{
public:
			entity() noexcept;
			entity(const std::string_view _name, int64_t _type = 0);
	virtual ~entity() noexcept;

public:
			void				register_event(own_ptr<Ievent>&& _pevent);
			void				unregister_event(Ievent* _pentity) noexcept;
			void				unregister_event_all() noexcept;
	[[nodiscard]] std::size_t	get_event_count() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<std::vector<own_ptr<time_event::Ievent>>>&>(this->m_vector_event)); return this->m_vector_event.size(); }
	[[nodiscard]] auto			get_front_next_time() noexcept { return (this->m_queue_event.empty() == false) ? this->m_queue_event.front()->event_status().time_next : chrono::time::utc::time_point(chrono::time::duration::zero()); }

			entity&				operator  = (own_ptr<Ievent>&& _pevent);
			entity&				operator  = (std::vector<own_ptr<Ievent>>&& _vector_event);
			entity&				operator += (own_ptr<Ievent>&& _pevent);
			entity&				operator += (std::vector<own_ptr<Ievent>>&& _pevent);
			entity&				operator -= (Ievent* _pevent); 

			void				process_notify_next_time_changed(time_event::Ievent* _pendity);

protected:
	virtual intptr_t			process_execute(intptr_t _return, size_t _param) override;

	virtual void				_process_start_request(context& _context) override;
	virtual result_code			_process_starting(context& _context) override;
	virtual result_code			_process_start(context& _context) override;
	virtual void				_process_stop_request() noexcept override;
	virtual result_code			_process_stopping() noexcept override;
	virtual result_code			_process_stop() noexcept override;

	virtual void				_process_pause_request() override;
	virtual void				_process_pauseing() override;
	virtual void				_process_pause() override;
	virtual void				_process_resume_request() override;
	virtual void				_process_resuming() override;
	virtual void				_process_resume() override;

protected:
			lockable<std::vector<own_ptr<time_event::Ievent>>> m_vector_event;
			std::vector<object_ptr<time_event::Ievent>> m_queue_event;

			void				_pop_heap() noexcept;
			void				_push_heap(time_event::Ievent* _schecule);
			bool				_process_erase_event_from_heap(time_event::Ievent* _pevent) noexcept;
};																				  

inline void time_event::Ievent::unregister_event() noexcept
{
	auto pentity = this->m_pentity;
	
	RETURN_IF(pentity.empty());
	
	pentity->unregister_event(this);
}


}
