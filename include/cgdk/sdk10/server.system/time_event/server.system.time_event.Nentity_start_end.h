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
// time_event::Nentity_start_end
//
// 1. time_event::Nentity_start_end
//    1) ������ start()�ð��� process_event_start()�Լ��� ȣ��ǰ�
//       ������ End�ð��� ProecssEventEnd()�Լ��� ȣ��Ǵ� Event��ü�̴�.
//    2) End���Ŀ��� ��ü�� �ڵ� detach�ȴ�.
//    3) set_event_start_time()�� set_event_end_time()�Լ��� ����Ͽ� ���۽ð��� ���ð���
//       ������ �� �ִ�.
//
//    ����!!!) �����Ǵ� �ð��� ��� Local TIme�� �ƴ϶� System Time�̴�.
//
// ----------------------------------------------------------------------------
class time_event::Nentity_start_end : virtual public time_event::Ientity
{
public:
			Nentity_start_end();
			Nentity_start_end(const std::string_view _name);
	virtual	~Nentity_start_end() noexcept;

public:
			void				set_event_start_time(const chrono::time::utc::time_point& _time) noexcept;
	[[nodiscard]] auto&			event_start_time() const noexcept { return this->m_time_event_start;}

			void				set_event_end_time(const chrono::time::utc::time_point& _time) noexcept;
	[[nodiscard]] auto&			event_end_time() const noexcept { return this->m_time_event_terminate;}

protected:
	virtual	result_code			process_event_start(const chrono::time::utc::time_point& _time) PURE;
	virtual	result_code			process_event_end(const chrono::time::utc::time_point& _time) PURE;

protected:
	virtual result_code			_process_starting(context& _context) override;
	virtual result_code			_process_start(context& _context) override;
	virtual result_code			_process_stopping() noexcept override;
	virtual result_code			_process_stop() noexcept override;

	virtual	intptr_t			process_execute(intptr_t _return, size_t _param) override;

protected:
			chrono::time::utc::time_point m_time_event_start;
			bool				m_is_event_start = true;

			chrono::time::utc::time_point m_time_event_terminate;
			bool				m_is_event_terminate = true;
};


}