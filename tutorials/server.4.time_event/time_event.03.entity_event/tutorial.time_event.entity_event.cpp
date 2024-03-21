#include "cgdk/sdk10/server.time_event.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;


// ----------------------------------------------------------------------------
// 1. time_event::entity란?
//
//    1) 이전의 다른 Event 객체들은 시작시간과 종료시간 혹은 일정시간마다 반복되는
//       경우에만 사용가능한 Event 객체였다.
//       하지만 정해진 시간에 실행되어야 하는 Event가 있을 경우 그 사용이 힘들었다.
//       이 schedule Event 객체는 임의의 시간을 등록하여 등록된 시간에 스케쥴에
//       따라 실행될 수 있도록 하는 Event 객체이다.
//
//    2) time_event::entity의 주요 사항
//       - 실행시간은 EVENT_SCHEDULE 구조체를 사용하여 등록한다.
//       - EVENT_SCHEDULE을 사용하여 다음 실행될 시간 (설정될 때 기준으로는 최초
//         실행 시간)과 반복실행할 경우 반복할 간격과 횟수를 설정해 줄수 있다.
//       - 1회만 실행될 경우 반복횟수를 1로 설정해 주면 된다.
//       - 설정된 EVENT_SCHEDULE를 add_schedule()함수를 사용하여 설정할 수 있다.
//
//
// ----------------------------------------------------------------------------
int main()
{
	// trace) 
	std::cout << "start tutorial..."sv << std::endl;


	// ------------------------------------------------------------------
	// 1. entity event (1)
	//
	//    - 정해진 시간에 한번만 실행되는 Event객체이다.
	//    - set_event_time()으로 설정된 시간에 process_event()함수를 호출한다.
	//    - 따라서 Event의 동작 시 처리해야할 내용을 process_event()에
	//      작성하면 된다.
	//    - 시작후 7초후 실행되도록 설정했다.
	//
	// ------------------------------------------------------------------
	{
		// 1) create event entity
		auto pentity = make_own<time_event::entity>("event_0"sv);

		// 2) 2020년 10월 9일 7시 51분 0초에 실행한다.
		{
			time_event::sEVENT_SETTING setting;
			setting.name		  = "A"sv;
			setting.type		  = time_event::eTYPE::NONE;
			setting.time_execute  = chrono::from_date_time<chrono::time::utc::time_point>({2020, 10, 9, 14, 17, 0});
			setting.time_interval = chrono::time::duration::zero();
			setting.count_times	  = 1;

			*pentity += make_own<time_event::event>(setting,
				[=](chrono::time::utc::time_point /*_time_now*/)
			{
				std::cout << "event_0 executed A ("sv
					<< to_string<char>(chrono::time::utc::now()) << ")"sv
					<< '\n';

				return eRESULT::SUCCESS;
			});
		}

		// 3) 2020년 10월 9일 7시 51분 5초에 실행한다.
		{
			time_event::sEVENT_SETTING setting;
			setting.name = "A"sv;
			setting.type = time_event::eTYPE::NONE;
			setting.time_execute = chrono::from_date_time<chrono::time::utc::time_point>({ 2020, 10, 9, 14, 17, 5 });
			setting.time_interval = chrono::time::duration::zero();
			setting.count_times = 1;

			*pentity += make_own<time_event::event>(setting,
				[=](chrono::time::utc::time_point /*_time_now*/)
			{
				std::cout << "event_0 executed B ("sv
					<< to_string<char>(chrono::time::utc::now()) << ")"sv
					<< '\n';

				return eRESULT::SUCCESS;
			});
		}

		// 4) 2020년 10월 9일 7시 52분 0초에 실행한다.
		{
			time_event::sEVENT_SETTING setting;
			setting.name = "A"sv;
			setting.type = time_event::eTYPE::NONE;
			setting.time_execute = chrono::from_date_time<chrono::time::utc::time_point>({ 2020, 10, 9, 14, 18, 0 });
			setting.time_interval = chrono::time::duration::zero();
			setting.count_times = 1;

			*pentity += make_own<time_event::event>(setting,
				[=](chrono::time::utc::time_point /*_time_now*/)
			{
				std::cout << "event_0 executed C ("sv
					<< to_string<char>(chrono::time::utc::now()) << ")"sv
					<< '\n';

				return eRESULT::SUCCESS;
			});
		}

		// 5) 시작한다.
		pentity->start();

		// 6) ESC를 누를 때까지 기다린다.
		while (_getch() != 27);
	}


	// ------------------------------------------------------------------
	// 2. entity event (2)
	//
	//    - 정해진 시간에 한번만 실행되는 Event객체이다.
	//    - set_event_time()으로 설정된 시간에 process_event()함수를 호출한다.
	//    - 따라서 Event의 동작 시 처리해야할 내용을 process_event()에
	//      작성하면 된다.
	//    - 시작후 7초후 실행되도록 설정했다.
	//
	// ------------------------------------------------------------------
	{
		// 1) create event entity
		auto pentity = make_own<time_event::entity>("event_1"sv);

		// 2) iteration 처리되도록 event를 설정해 추가한다.
		{
			time_event::sEVENT_SETTING setting;
			setting.name		  = "iteration"sv;
			setting.type		  = time_event::eTYPE::NONE;
			setting.time_execute  = chrono::time::utc::now() + chrono::seconds(1);
			setting.time_interval = chrono::seconds(3);
			setting.count_times   = 10;

			*pentity += make_own<time_event::event>(setting,
				[=](chrono::time::utc::time_point /*_time_now*/)
				{
					std::cout << "event_1 executed ITERATION ("sv
							  << to_string<char>(chrono::time::utc::now()) << ")"sv
							  << '\n';

					return eRESULT::SUCCESS;
				});
		}

		// 4) 시작한다.
		pentity->start();

		// 4) ESC를 누를 때까지 기다린다.
		while (_getch() != 27);
	}


	// ------------------------------------------------------------------
	// 3. entity event (3)
	//
	//    - 정해진 시간에 한번만 실행되는 Event객체이다.
	//    - set_event_time()으로 설정된 시간에 process_event()함수를 호출한다.
	//    - 따라서 Event의 동작 시 처리해야할 내용을 process_event()에
	//      작성하면 된다.
	//    - 시작후 7초후 실행되도록 설정했다.
	//
	// ------------------------------------------------------------------
	{
		// 1) create event entity
		auto pentity = make_own<time_event::entity>("event_2"sv);

		// 2) start event를 생성해서 추가한다.
		{
			time_event::sEVENT_SETTING setting;
			setting.name		  = "start"sv;
			setting.time_execute  = chrono::time::utc::now() + 5s;
			setting.time_interval = chrono::time::duration::zero();
			setting.count_times   = 1;

			*pentity += make_own<time_event::event>(setting,
				[=](chrono::time::utc::time_point /*_time_now*/)
				{
					std::cout << "event_2 executed START ("sv
							  << to_string<char>(chrono::time::utc::now()) << ")"sv
							  << '\n';

					return eRESULT::SUCCESS;
				});
		}

		// 3) end event를 생성해서 추가한다.
		{
			time_event::sEVENT_SETTING setting;
			setting.name		  = "end"sv;
			setting.time_execute  = chrono::time::utc::now() + 15s;
			setting.time_interval = chrono::time::duration::zero();
			setting.count_times   = 1;

			*pentity += make_own<time_event::event>(setting, 
				[=](chrono::time::utc::time_point /*_time_now*/)
				{
					std::cout << "event_2 executed END ("sv
							  << to_string<char>(chrono::time::utc::now()) << ")"sv
							  << '\n';

					return eRESULT::COMPLETE; // eRESULT::COMPLETE를 리턴하면 time_event entity를 종료한다.
				});
		}

		// 4) 시작한다.
		pentity->start();

		// 4) ESC를 누를 때까지 기다린다.
		while (_getch() != 27);
	}


	// ------------------------------------------------------------------
	// 4. entity event (4)
	//
	//    - 정해진 시간에 한번만 실행되는 Event객체이다.
	//    - set_event_time()으로 설정된 시간에 process_event()함수를 호출한다.
	//    - 따라서 Event의 동작 시 처리해야할 내용을 process_event()에
	//      작성하면 된다.
	//    - 시작후 7초후 실행되도록 설정했다.
	//
	// ------------------------------------------------------------------
	{
		// 1) create event entity
		auto pentity = make_own<time_event::entity>("event_3"sv);

		// 2) start event를 생성해서 추가한다.
		{
			time_event::sEVENT_SETTING setting;
			setting.name		  = "start"sv;
			setting.time_execute  = chrono::time::utc::now() + 8s;
			setting.time_interval = chrono::time::duration::zero();
			setting.count_times   = 1;

			*pentity += make_own<time_event::event>(setting,
				[=](chrono::time::utc::time_point /*_time_now*/)
				{
					std::cout << "event_3 executed START ("sv
							  << to_string<char>(chrono::time::utc::now()) << ")"sv
							  << '\n';

					return eRESULT::SUCCESS;
				});
		}

		// 3) iteration event를 생성해서 추가한다.
		{
			time_event::sEVENT_SETTING setting;
			setting.name		  = "iteration"sv;
			setting.time_execute  = chrono::time::utc::now() + 14s;
			setting.time_interval = chrono::seconds(6);
			setting.count_times	  = time_event::infinite;

			*pentity += make_own<time_event::event>(setting,
				[=](chrono::time::utc::time_point /*_time_now*/)
			{
				std::cout << "event_3 executed ITERATION ("sv
					<< to_string<char>(chrono::time::utc::now()) << ")"sv
					<< '\n';

				return eRESULT::SUCCESS;
			});
		}

		// 4) end event를 생성해서 추가한다.
		{
			time_event::sEVENT_SETTING setting;
			setting.name		  = "end"sv;
			setting.time_execute  = chrono::time::utc::now() + 1min;
			setting.time_interval = chrono::time::duration::zero();
			setting.count_times   = 1;

			*pentity += make_own<time_event::event>(setting, 
				[=](chrono::time::utc::time_point /*_time_now*/)
				{
					std::cout << "event_3 executed END ("sv
							  << to_string<char>(chrono::time::utc::now()) << ")"sv
							  << '\n';

					return eRESULT::COMPLETE; // eRESULT::COMPLETE를 리턴하면 time_event entity를 종료한다.
				});
		}

		// 5) 시작한다.
		pentity->start();

		// 6) ESC를 누를 때까지 기다린다.
		while (_getch() != 27);
	}


	// ------------------------------------------------------------------
	// 5. entity event (5)
	//
	//    - 정해진 시작 시간과 종료시간에 각각 한번씩 process_event_start()
	//      와 process_event_end()를 호출하는 Event 객체이다.
	//    - 정해진 시작 시간에 process_event_start()를 호출하고 
	//    - 정해진 종료 시간에 process_event_end()를 호출한다.
	//    - 시작후 5초 후 process_event_start()가 호출되며
	//      시작후 20초후 process_event_end()가 호출된다.
	//
	// ------------------------------------------------------------------
	{
		// 1) create event entity
		auto pentity = make_own<time_event::entity>("event_4"sv);

		// 2) 시작한 후 3초 실행하는 event 객체를 추가한다.
		*pentity += CGDK::time_event::make_event_once(chrono::time::utc::now() + chrono::seconds(3),
			[=](chrono::time::utc::time_point /*_time_now*/)
			{
				std::cout << "event_4 executed ONCE ("sv
						  << to_string<char>(chrono::time::utc::now()) << ")"sv
						  << '\n';

				return result_code(eRESULT::SUCCESS);
			});

		// 3) 시작한 직후 5초마다 5번 식행하는 event 객체를 추가한다.
		*pentity += CGDK::time_event::make_event_iteration(chrono::time::utc::now(), chrono::seconds(5), 5,
			[=](chrono::time::utc::time_point /*_time_now*/)
			{
				std::cout << "event_4 executed ITERATION ("sv
						  << to_string<char>(chrono::time::utc::now()) << ")"sv
						  << '\n';

				return result_code(eRESULT::SUCCESS);
			});

		pentity->start();

		// 4) ESC를 누를 때까지 기다린다.
		while (_getch() != 27);
	}


	// ------------------------------------------------------------------
	// 4. 뒷마무리 & 끝내기
	// ------------------------------------------------------------------
	// trace) 
	std::cout << "end tutorial..."sv << std::endl;


	// return)
	return 0;
}
