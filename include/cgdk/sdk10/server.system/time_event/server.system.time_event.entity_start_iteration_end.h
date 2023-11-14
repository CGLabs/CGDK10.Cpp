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
// time_event::entity_start_iteration_end
//
// 1. time_event::entity_start_iteration_end이란?
//    1) 시작과 종료시 실행될 Event가 설정되며 그 사이에 기간 동안 일정 간격으로  
//       Event함수를 호출하는 객체이다.
//    2) 쉽게 말해서 CStartEnd와 CIteration를 합한 것이며 설정 함수 역시 두 클래스
//       와 동일하다.
//
//    주의!!!) 설정되는 시간은 모두 Local TIme이 아니라 System Time이다.
//
// ----------------------------------------------------------------------------
template <class TFUNCTION = EVENT_FUNCTION>
class time_event::entity_start_iteration_end : public time_event::Nentity_start_iteration_end
{
public:
			entity_start_iteration_end() { this->m_entity_setting.type = static_cast<uint64_t>(eTYPE::START_ITERATION_END); }

public:
			void				set_start_function(const TFUNCTION& _function) { this->m_function_start = _function;}
	[[nodiscard]] auto&		 	get_start_function() const { return this->m_function_start;}
																					  
			void				set_end_function(const TFUNCTION& _function) { this->m_function_end = _function;}
	[[nodiscard]] auto&		 	get_end_function() const { return this->m_function_end;}

			void				set_iteration_function(const TFUNCTION& _function) { this->m_function_iteration = _function;}
	[[nodiscard]] auto&			get_iteration_function() const noexcept { return this->m_function_iteration;}

protected:
	virtual	result_code			process_event_start(const chrono::time::utc::time_point& _time) { RETURN_IF(this->m_function_start == nullptr, eRESULT::NOT_EXIST); return this->m_function_start(_time);}
	virtual	result_code			process_event_end(const chrono::time::utc::time_point& _time) { RETURN_IF(this->m_function_end == nullptr, eRESULT::NOT_EXIST); return this->m_function_end(_time);}
	virtual	result_code			process_event_iteration(const chrono::time::utc::time_point& _time) override { RETURN_IF(this->m_function_iteration == nullptr, eRESULT::NOT_EXIST); return this->m_function_iteration(_time); }

			TFUNCTION			m_function_start;
			TFUNCTION			m_function_end;
			TFUNCTION			m_function_iteration;
};


}