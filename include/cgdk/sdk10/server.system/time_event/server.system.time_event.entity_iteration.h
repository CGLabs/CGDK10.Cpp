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
// 1. time_event::object::iteration��??
//    1) ������ �ð����� ������ Ƚ�� Ȥ�� ���Ѵ�� �����ϴ� ���̴�.
//    2) set_interval()�Լ��� ����Ͽ� ���ణ���� ������ �� �ִ�.
//    3) set_times()�Լ��� ����Ͽ� Ƚ���� ������ �� �ִ�.
//    4) ���� ������ �ð��� set_next_time()�� ����Ͽ� �����ؾ� �Ѵ�.(�ݵ�� ����� �Ѵ�!)
//
//    ����!!!) �����Ǵ� �ð��� ��� Local TIme�� �ƴ϶� System Time�Ƿ� �����ؾ� �Ѵ�.
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