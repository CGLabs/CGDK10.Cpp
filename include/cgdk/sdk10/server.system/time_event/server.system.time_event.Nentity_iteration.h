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
// time_event::Nentity_iteration
//
// 1. time_event::object::iteration란??
//    1) 일정한 시간마다 정해진 횟수 혹은 무한대로 수행하는 것이다.
//    2) set_interval()함수를 사용하여 실행간격을 설정할 수 있다.
//    3) set_times()함수를 사용하여 횟수를 설정할 수 있다.
//    4) 최초 실행할 시간은 set_next_time()를 사용하여 설정해야 한다.(반드시 해줘야 한다!)
//
//    주의!!!) 설정되는 시간은 모두 Local TIme이 아니라 System Time므로 주의해야 한다.
//
// ----------------------------------------------------------------------------
class time_event::Nentity_iteration : virtual public time_event::Ientity
{
public:
			Nentity_iteration();
			Nentity_iteration(const std::string_view _name);
	virtual	~Nentity_iteration() noexcept;

public:
			void				set_event_time(const chrono::time::utc::time_point& _time) noexcept;
	[[nodiscard]] const auto&	get_event_time() const noexcept { return this->entity_status().time_next;}

			void				set_event_interval(const chrono::time::duration& _duration) noexcept;
	[[nodiscard]] const auto&	get_event_interval() const noexcept { return this->m_time_diff_interval;}

			void				set_event_times(int _times) noexcept;
	[[nodiscard]] const auto&	get_event_times() const noexcept { return this->m_times;}

protected:
	virtual	result_code			process_event_iteration(const chrono::time::utc::time_point& _time) PURE;

protected:
	virtual result_code			_process_starting(context& _context) override;
	virtual result_code			_process_start(context& _context) override;
	virtual result_code			_process_stopping() noexcept override;
	virtual result_code			_process_stop() noexcept override;

	virtual	intptr_t			process_execute(intptr_t _return, size_t _param) override;

			int					m_times = time_event::infinite; // 반복 횟수 (time_event::infinite == 무한대 == -1)
			chrono::time::duration m_time_diff_interval = chrono::time::duration::zero(); // 반복 간격
};


}