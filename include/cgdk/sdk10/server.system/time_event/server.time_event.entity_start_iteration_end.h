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
// 1. time_event::entity_start_iteration_end�̶�?
//    1) ���۰� ����� ����� Event�� �����Ǹ� �� ���̿� �Ⱓ ���� ���� ��������  
//       Event�Լ��� ȣ���ϴ� ��ü�̴�.
//    2) ���� ���ؼ� CStartEnd�� CIteration�� ���� ���̸� ���� �Լ� ���� �� Ŭ����
//       �� �����ϴ�.
//
//    ����!!!) �����Ǵ� �ð��� ��� Local TIme�� �ƴ϶� System Time�̴�.
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