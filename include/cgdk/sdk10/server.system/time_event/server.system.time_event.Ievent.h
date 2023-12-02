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
// time_event::Ievent
//
//
// ----------------------------------------------------------------------------
class time_event::Ievent :
	virtual public				CGDK::object::Inameable,
	virtual public				Ireferenceable
{
public:
	virtual ~Ievent() noexcept {}

public:
	[[nodiscard]] auto&			event_setting() noexcept { return this->m_event_setting;}
	[[nodiscard]] const auto&	event_setting() const noexcept { return this->m_event_setting;}
	[[nodiscard]] auto&			event_status() noexcept { return this->m_event_status;}
	[[nodiscard]] const auto&	event_status() const noexcept { return this->m_event_status;}
			void				set_next_time(chrono::time::utc::time_point _time_next) noexcept;
			void				unregister_event() noexcept;

	virtual	void				process_reset();
	virtual	result_code			process_event(chrono::time::utc::time_point _time_now);

	[[nodiscard]] virtual bool	process_is_this(std::string_view _name) const noexcept { return this->m_event_setting.name == _name; }
	[[nodiscard]] virtual std::string_view process_get_name() const noexcept { return this->m_event_setting.name; }
	virtual	void				process_set_name(std::string_view _name) {this->m_event_setting.name = _name; }

public:
			sEVENT_SETTING		m_event_setting;
			sEVENT_STATUS		m_event_status;
			object_ptr<entity>	m_pentity;
			void				set_next_event_after_now();
};


}
