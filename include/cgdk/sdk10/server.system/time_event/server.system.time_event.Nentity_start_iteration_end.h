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
// time_event::Nentity_start_iteration_end
//
// 1. time_event::Nentity_start_iteration_end�̶�?
//    1) ���۰� ����� ����� Event�� �����Ǹ� �� ���̿� �Ⱓ ���� ���� ��������  
//       Event�Լ��� ȣ���ϴ� ��ü�̴�.
//    2) ���� ���ؼ� CStartEnd�� CIteration�� ���� ���̸� ���� �Լ� ���� �� Ŭ����
//       �� �����ϴ�.
//
//    ����!!!) �����Ǵ� �ð��� ��� Local TIme�� �ƴ϶� System Time�̴�.
//
// ----------------------------------------------------------------------------
class time_event::Nentity_start_iteration_end : public time_event::Nentity_start_end
{
public:
			Nentity_start_iteration_end();
			Nentity_start_iteration_end(const std::string_view _name);
	virtual	~Nentity_start_iteration_end() noexcept;

public:
			void				set_event_time(const chrono::time::utc::time_point& _time) noexcept;
	[[nodiscard]] const auto&	get_event_time() const noexcept { return this->entity_status().time_next;}

			void				set_event_interval(const chrono::time::duration& _duration) noexcept;
	[[nodiscard]] const auto&	get_event_interval() const noexcept { return this->m_time_diff_interval;}

			void				set_event_times(int _times) noexcept;
	[[nodiscard]] const auto&	get_event_times() const noexcept { return m_times;}

protected:
	virtual	result_code			process_event_iteration(const chrono::time::utc::time_point& _time) PURE;

protected:
	virtual result_code			_process_starting(context& _context) override;
	virtual result_code			_process_start(context& _context) override;
	virtual result_code			_process_stopping() noexcept override;
	virtual result_code			_process_stop() noexcept override;

	virtual	intptr_t			process_execute(intptr_t _return, size_t _param) override;
			void				process_execute_start(const chrono::time::utc::time_point& _time_now);
			void				process_execute_iteration(const chrono::time::utc::time_point& _time_now);
			void				process_execute_end(const chrono::time::utc::time_point& _time_now);

protected:
			int					m_times_remained = time_event::infinite; // ���� ���� �ִ� �ݺ� Ƚ�� (infinite = -1 = ���Ѵ�)
			int					m_times = time_event::infinite; // ��ǥ �ݺ� Ƚ�� (infinite = -1 = ���Ѵ�)
			chrono::time::duration m_time_diff_interval = chrono::time::duration::zero(); // �ݺ� ����
};


}