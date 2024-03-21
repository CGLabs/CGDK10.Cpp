#include "cgdk/sdk10/server.time_event.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;


// ----------------------------------------------------------------------------
// 1. Function을 호출하게 하는 Event 객체.
//
//    1) time_event::object::COnce, time_event::object::CStartEnd, 등등의 클래스는
//       실행을 정의하기 위해 반드시 상속받아 해당 process_event~()함수를 재정의하여
//       실행내용을 작성해야 했다. 
//       간단한 처리 내용을 작성하기 위해 Class를 정의하는 것이 부담될 경우 사용하는
//       Event 객체라고 할수 있다.
//
//    2) 주요 Function을 호출하는 Event객체는 아래와 같다.
//
//       @ time_event::entity_iteration_function<TFUNCTION>
//         - 일정시간마다 실행되는 
//         - 예약된 시간에 딱 1회만 실행되는 객체
//
//       @ time_event::object::start_end_function<TFUNCTION>
//         - time_event::object::CStartEnd와 동작 동일
//         - 예약된 시작시간과 종료시간에 각각 정해진 함수를 호출하는 객체
//
//       @ time_event::object::start_iteration_end_function<TFUNCTION>
//         - time_event::object::CStartIterationEnd와 동작 동일하다.
//         - 예약된 시작시간에 정해진 함수가 호출되며 이후에 정해진 간격에 따라
//           정해진 함수를 정해진 실행횟수만큼 호출해주는 Event 객체이다.
//           실행횟수만큼 호출된 후 process_event_end()함수가 호출된다.
//
//       @ time_event::object::iteration_function<TFUNCTION>
//         - time_event::object::CIteration와 동작 동일하다.
//         - 정해진 시간 간격 마다 정해진 함수를 무한반복적으로 실행해하는
//           Event객체이다.
//
//    3) 실행함수는 일반적인 Function 혹은 lambda 함수 모두 사용이 가능하다.
//
//       @ 일반함수를 사용할 경우 template 인자에 EVENT_FUNCTION를 사용하면 된다.
//         다만 이 인자는 디폴트로 설정되어 있으므로 굳이 설정하지 않아도 된다.
//
//         time_event::object::once_function<EVENT_FUNCTION>
//         time_event::object::once_function<>
//
//       @ 람다함수를 사용할 경우 template 인자에 EVENT_LAMBDA를 사용하면 된다.
//         다만 람다함수를 사용하는 것은 Visual C++ 2010부터 사용가능하다.
//
//         time_event::object::once_function<EVENT_LAMBDA>
//
//
// ----------------------------------------------------------------------------
int main()
{
	// trace) 
	std::cout << "start tutorial..."sv << std::endl;


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
	auto pentity_a = make_own<time_event::entity_iteration<>>();

	// 2) setting
	pentity_a->set_event_time(chrono::time::utc::now() + chrono::seconds(1));
	pentity_a->set_event_interval(chrono::seconds(3));
	pentity_a->set_event_times(10);

	// 3) set functions
	pentity_a->set_event_function([=](chrono::time::utc::time_point /*_time*/)
	{
		std::cout << "event1(time_event::entity_iteration) executed ("sv
				  << to_string<char>(chrono::time::utc::now()) << ")"sv
				  << '\n';

		return eRESULT::SUCCESS;
	});

	// 4) start
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
	auto pentity_b = make_own<time_event::entity_start_end<>>();

	// 2) setting
	pentity_b->set_event_start_time(chrono::time::utc::now() + chrono::seconds(5));
	pentity_b->set_event_end_time(chrono::time::utc::now() + chrono::seconds(15));

	// 3) set functions
	pentity_b->set_start_function([=](chrono::time::utc::time_point /*_time*/)
	{
		std::cout << "event2(time_event::entity_start_end) START executed ("sv
				  << to_string<char>(chrono::time::utc::now()) << ")"sv
				  << '\n';

		return eRESULT::SUCCESS;
	});

	pentity_b->set_end_function([=](chrono::time::utc::time_point /*_time*/)
	{
		std::cout << "event2(time_event::entity_start_end) END executed ("sv
				  << to_string<char>(chrono::time::utc::now()) << ")"sv
				  << '\n';

		return eRESULT::SUCCESS;
	});

	// 4) start
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
	auto pentity_c = make_own<time_event::entity_start_iteration_end<>>();

	// 2) setting
	pentity_c->set_event_start_time(chrono::time::utc::now());
	pentity_c->set_event_interval(chrono::seconds(6));
	pentity_c->set_event_end_time(chrono::time::utc::now() + chrono::minutes(1));

	// 3) set functions
	pentity_c->set_start_function([=](chrono::time::utc::time_point /*_time*/)
	{
		std::cout << "event3(time_event::entity_start_iteration_end) START executed ("sv
				  << to_string<char>(chrono::time::utc::now()) << ")"sv
				  << '\n';

		return eRESULT::SUCCESS;
	});

	pentity_c->set_iteration_function([=](chrono::time::utc::time_point /*_time*/)
	{
		std::cout << "event3(time_event::entity_start_iteration_end) ITERATION executed ("sv
				  << to_string<char>(chrono::time::utc::now()) << ")"sv
				  << '\n';

		return eRESULT::SUCCESS;
	});

	pentity_c->set_end_function([=](chrono::time::utc::time_point /*_time*/)
	{
		std::cout << "event3(time_event::entity_start_iteration_end) END executed ("sv
				  << to_string<char>(chrono::time::utc::now()) << ")"sv
				  << '\n';

		return eRESULT::SUCCESS;
	});

	// 4) start
	pentity_c->start();


	// ------------------------------------------------------------------
	// 4. 종료대기...
	// ------------------------------------------------------------------
	// 1) ESC를 누를 때까지 기다린다.
	while (_getch() != 27);

	// trace) 
	std::cout << "end tutorial..."sv << std::endl;


	// return) 끝.
	return 0;
}
