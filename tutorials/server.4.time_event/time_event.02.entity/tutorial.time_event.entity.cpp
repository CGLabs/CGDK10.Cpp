#include "cgdk/sdk10/server.time_event.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;


// ----------------------------------------------------------------------------
// 1. Event System이란?
//
//    1) 각종 System을 제작하다보면 일정시간마다 실행을 하거나 특정한 시간에 실행
//       해야하는 것들을 설정할 필요가 있다.
//       이때 특정한 시간이나  특정한 시간마다 실행하도록 하는 시스템이 Event 시스템이다.
//
//    2) Event System은 Event object와 Event Manager로 나뉘어진다.
//       - Event Manager는 등록된 EventObject를 등록하였다가 정해진 시간마다 실행해주는
//         관리자를 의미한다.
//       - Event object는 Event Manager에 등록되어 동작하는 객체로 필요에 따라
//         다양한 실행형태로 제작되어져 있다. 
//         선언된 Event object는 아래와 같은 것들이 있다.
//
//         @ time_event::object::COnce
//           예약된 시간에 딱 1회만 실행되는 객체
//
//         @ time_event::object::start_end
//           예약된 시작시간과 종료시간에 각각 정해진 함수를 호출하는 객체
//
//         @ time_event::object::start_iteration_end
//           예약된 시작시간에 정해진 함수가 호출되며 이후에 정해진 간격에 따라
//           정해진 함수를 정해진 실행횟수만큼 호출해주는 Event 객체이다.
//           실행횟수만큼 호출된 후 process_event_end()함수가 호출된다.
//
//         @ CCGEventIteration
//           정해진 시간 간격 마다 정해진 함수를 무한반복적으로 실행해하는
//           Event객체이다.
//
//    3) 각 Event객체들은 특정한 시간에 호출되어지는 virtual함수들이 정의되어 있다.
//       이 virtual함수를 재정의하여 실행하고자하는 내용을 작성하면 된다.
//
//    4) Event객체의 정밀도는 초단위 수준만을 보장하므로 더욱 정밀한 실행이 필요할
//       경우 Executable이나 다른 방법을 사용하기를 권장한다.
//
//    5) Event System에서의 시간은 모두 System Time을 사용하고 있다. System Time은
//       Local Time과 동일하지 않기 때문에 실제 지역 시간과는 다를 수 있으므로 
//       설정을 할때는 반드시 System Time으로 설정할 필요가 있다.
//
//
// ----------------------------------------------------------------------------
// Event 1) time_event::entity_iteration
class foo_time_event_iteration : public time_event::Nentity_iteration
{
public:
	foo_time_event_iteration(std::string_view _name = std::string_view()) : time_event::Nentity_iteration(_name) {}
	virtual	result_code process_event_iteration(const chrono::time::utc::time_point& /*_time*/) override
	{ 
		std::cout << "foo_time_event_iteration executed ("sv
				  << to_string<char>(chrono::time::utc::now()) << ")"sv
				  << '\n';

		return eRESULT::SUCCESS;
	}
};																												  
																												  
// Event 2) time_event::entity_start_end	
class foo_time_event_start_end : public time_event::Nentity_start_end
{																												  
public: 
	foo_time_event_start_end(std::string_view _name = std::string_view()) : time_event::Nentity_start_end(_name) {}
	virtual	result_code process_event_start(const chrono::time::utc::time_point& /*_time*/) override
	{
		std::cout << "foo_time_event_start_end START executed ("sv
				  << to_string<char>(chrono::time::utc::now()) << ")"sv
				  << '\n';

		return eRESULT::SUCCESS;
	}
	virtual	result_code process_event_end(const chrono::time::utc::time_point& /*_time*/) override
	{
		std::cout << "foo_time_event_start_end END executed ("sv
				  << to_string<char>(chrono::time::utc::now()) << ")"sv
				  << '\n';

		return eRESULT::SUCCESS;
	}
};																												  
																												  
// Event 3) time_event::entity_start_iteration_end
class foo_time_event_start_iteration_end : public time_event::Nentity_start_iteration_end
{																												  
public: 
	foo_time_event_start_iteration_end(std::string_view _name = std::string_view()) : time_event::Nentity_start_iteration_end(_name) {}
	virtual	result_code process_event_start(const chrono::time::utc::time_point& /*_time*/) override
	{
		std::cout << "foo_time_event_start_iteration_end START executed ("sv
				  << to_string<char>(chrono::time::utc::now()) << ")"sv
				  << '\n';

		return eRESULT::SUCCESS;
	}
	virtual	result_code			process_event_iteration(const chrono::time::utc::time_point& /*_time*/) override
	{
		std::cout << "foo_time_event_start_iteration_end ITERATION executed ("sv
				  << to_string<char>(chrono::time::utc::now()) << ")"sv
				  << '\n';

		return eRESULT::SUCCESS;
	}
	virtual	result_code			process_event_end(const chrono::time::utc::time_point& /*_time*/) override
	{
		std::cout << "foo_time_event_start_iteration_end END executed ("sv
				  << to_string(chrono::time::utc::now()) << ")"sv
				  << '\n';

		return eRESULT::SUCCESS;
	}
};																											  
																											  

int main()
{
	// trace) 
	std::cout << "start tutorial..." << std::endl;


	// ------------------------------------------------------------------
	// 1. time_event::entity_iteration
	//
	//    - 정해진 시간에 한번만 실행되는 Event객체이다.
	//    - set_event_time()으로 설정된 시간에 process_event()함수를 호출한다.
	//    - process_event()에 처리할 내용을 재정의합니다.
	//
	//    - 시작후 1초 후 최초 실행하며 3초마다 10회 재실행합니다.
	// ------------------------------------------------------------------
	// 1) time_event 객체를 생성한다.
	auto pentity_a = make_own<foo_time_event_iteration>();

	// 2) setting
	pentity_a->set_event_time(chrono::time::utc::now() + 1s);
	pentity_a->set_event_interval(3s);
	pentity_a->set_event_times(10);

	// 3) start
	pentity_a->start();


	// ------------------------------------------------------------------
	// 2. time_event::entity_start_end
	//
	//    - 시작 시간과 process_event_start()를 호출하고
	//      종료시간에 process_event_end()를 호출하는 time_event 객체이다.
	//
	//    - 시작후 5초 후 process_event_start()가 호출되며
	//      시작후 15초후 process_event_end()가 호출된다.
	// ------------------------------------------------------------------
	// 1) time_event 객체를 생성한다.
	auto pentity_b = make_own<foo_time_event_start_end>();

	// 2) setting
	pentity_b->set_event_start_time(chrono::time::utc::now() + 5s);
	pentity_b->set_event_end_time(chrono::time::utc::now() + 15s);

	// 3) start
	pentity_b->start();


	// ------------------------------------------------------------------
	// 3. time_event::entity_start_iteration_end
	//
	//    - 시작 시간과 process_event_start()를 호출하고
	//      time_interval 간격마다 process_event_iteration()함수를 호출한 후 
	//      종료시간에 process_event_end()를 호출하는 time_event 객체이다.
	//
	//    - 시작후 2초 후 process_event_start()가 호출된다.
	//      시작후 3초 간격으로 10번 process_event_iteration()가 호출되며
	//      그 5초 후 process_event_end()가 호출된다.
	// ------------------------------------------------------------------
	// 1) time_event 객체를 생성한다.
	auto pentity_c = make_own<foo_time_event_start_iteration_end>();

	// 2) setting
	pentity_c->set_event_start_time(chrono::time::utc::now() + 8s);
	pentity_c->set_event_interval(6s);
	pentity_c->set_event_end_time(chrono::time::utc::now() + 1min);

	// 3) start
	pentity_c->start();


	// ------------------------------------------------------------------
	// 4. JSON으로 설정하기
	//
	//    - 
	//    - 
	// ------------------------------------------------------------------
	{
		// 1) set params
		context param;

		param["event_0"sv]["time_execute"sv] = "now + 1s"sv;
		param["event_0"sv]["time_interval"sv] = "3s"sv;
		param["event_0"sv]["count_times"sv] = 10;

		param["event_1"sv]["time_start"sv] = "now + 5s"sv;
		param["event_1"sv]["time_end"sv] = "now + 15s"sv;

		param["event_2"sv]["time_start"sv] = "now + 3s"sv;
		param["event_2"sv]["time_end"sv] = "now + 1min"sv;
		param["event_2"sv]["time_interval"sv] = "6s"sv;

		// 2) create time event object
		auto pentity_x = make_own<foo_time_event_iteration>("event_0"sv);
		auto pentity_y = make_own<foo_time_event_start_end>("event_1"sv);
		auto pentity_z = make_own<foo_time_event_start_iteration_end>("event_2"sv);

		// 3) start
		pentity_x->start(param);
		pentity_y->start(param);
		pentity_z->start(param);
	}
	

	// ------------------------------------------------------------------
	// 4. 종료대기...
	// ------------------------------------------------------------------
	// 1) ESC를 누를 때까지 기다린다.
	while(_getch() != 27);


	// ------------------------------------------------------------------
	// 5. 뒷마무리 & 끝내기
	// ------------------------------------------------------------------
	// trace) 
	std::cout << "end tutorial..."sv << std::endl;


	// Return) 끝.
	return 0;
}
