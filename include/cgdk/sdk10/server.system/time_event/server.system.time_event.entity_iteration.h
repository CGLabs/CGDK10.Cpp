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
// time_event::entity_iteration
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
template <class TFUNCTION = EVENT_FUNCTION>
class time_event::entity_iteration : public time_event::Nentity_iteration
{
public:
			entity_iteration() { this->m_entity_setting.type = static_cast<uint64_t>(eTYPE::ITERATION); }

public:
			void				set_event_function(const EVENT_FUNCTION& _function) noexcept { this->m_function_iteration = _function; }
	[[nodiscard]] const auto&	get_event_function() const noexcept { return this->m_function_iteration; }

protected:
	virtual	result_code			process_event_iteration(const chrono::time::utc::time_point& _time) override { RETURN_IF(this->m_function_iteration == nullptr, eRESULT::NOT_EXIST); return this->m_function_iteration(_time); }

			TFUNCTION			m_function_iteration;
};


}