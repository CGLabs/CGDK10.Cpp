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
// time_event::event
//
//
// ----------------------------------------------------------------------------
class time_event::event : virtual public time_event::Ievent
{
// public) 
public:
			event() noexcept {}
			event(const std::string_view _name) : event() { set_name(_name); }
			event(const sEVENT_SETTING& _entity_setting, const EVENT_FUNCTION& _event_function) : event()
			{
				event_setting() = _entity_setting;
				event_status().time_next = _entity_setting.time_execute;
				set_event_function(_event_function);
			}
			event(const sEVENT_SETTING& _entity_setting, EVENT_FUNCTION&& _event_function) : event()
			{
				event_setting() = _entity_setting;
				event_status().time_next = _entity_setting.time_execute;
				set_event_function(std::move(_event_function));
			}

public:
			void				set_event_function(const EVENT_FUNCTION& _event_function) noexcept { this->m_event_function = _event_function; }
			void				set_event_function(EVENT_FUNCTION&& _event_function) noexcept { this->m_event_function = std::move(_event_function); }
	[[nodiscard]] EVENT_FUNCTION get_event_function() const noexcept { return m_event_function; }

			event&				operator  = (const EVENT_FUNCTION& _event_function) noexcept { this->set_event_function(_event_function); return *this;}
			event&				operator  = (EVENT_FUNCTION&& _event_function) noexcept { this->set_event_function(std::move(_event_function)); return *this;}

public:
	virtual	void				process_reset() override;
	virtual	result_code			process_event(chrono::time::utc::time_point _time_now) override;

public:
			EVENT_FUNCTION		m_event_function = nullptr;
};

namespace time_event
{
	std::vector<own_ptr<Ievent>> make_event_once(chrono::time::utc::time_point _time_execute, EVENT_FUNCTION&& _event_function);
	std::vector<own_ptr<Ievent>> make_event_iteration(chrono::time::utc::time_point _time_first, chrono::time::duration _duraction, int _count, EVENT_FUNCTION&& _event_function);
	std::vector<own_ptr<Ievent>> make_event_start_stop(chrono::time::utc::time_point _time_start, chrono::time::utc::time_point _time_end, int _count, EVENT_FUNCTION&& _event_function);
	std::vector<own_ptr<Ievent>> make_event_start_iteration_stop(chrono::time::utc::time_point _time_start, chrono::time::duration _duraction, int _count, chrono::time::utc::time_point _time_end, EVENT_FUNCTION&& _event_function);
}

}
