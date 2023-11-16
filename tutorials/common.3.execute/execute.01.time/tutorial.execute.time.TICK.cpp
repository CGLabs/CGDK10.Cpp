//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                     tutorials common - object_pointer                     *
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
// 1) standard header file
#if defined(_WIN32)
	#include <conio.h>
#endif

// 2) CGDK header file
#include "cgdk/sdk10/system.object.h"

// 3) header files
#include <iostream>

// 4) namespace
using namespace CGDK;

//-----------------------------------------------------------------------------
//
// tutorial common - tick
//
//     1) 단일값(monotonic) 타이머로 
//     2) 절대 시간보다 시간 비교 및 연산을 목적으로 한다.
//     3) 비교적 정밀(밀리초 이하)하며 비용이 매우 적다.
//     5) thread나 executor 등의 실시간 처리용 타이머로 사용된다.
//     6) CGCII의 tick timer는 C++11를 그대로 따른다.
//
//-----------------------------------------------------------------------------
void tutorial_TICK()
{
	//-----------------------------------------------------------------------------
	//
	// 1. time_point => 특정 시간값
	//    duration   => time_point간의 차이
	// 
	//    - chrono::tick::time_point
	//      특정 시점의 시간을 표현하는 표현하는 형으로
	//      'std::chrono::stead_timer::time_point'와 동일하다.
	// 
	//    - chrono::tick::now()
	//      현재 시점의 시간을 얻을 수 있다.
	// 
	//    - chrono::tick::duration
	//      time_pointer간의 차이 즉 시간 차를 의미한다.
	//      다른 단위로 설정된 다양한 duration이 존재한다.
	//      std::chrono::duration'과 동일하다.
	// 
	//      1/1000초		chrono::tick::milliseconds (std::chrono::milliseconds)
	//      초			chrono::tick::seconds (std::chrono::seconds)
	//      분			chrono::tick::minutes (std::chrono::minutes)
	//      시			chrono::tick::hours (std::chrono::hours)
	//      일			chrono::tick::days
	//      주			chrono::tick::weeks
	//
	//-----------------------------------------------------------------------------
	// 1) 현재 tick 시간을 얻는다.
	chrono::tick::time_point tick_now = chrono::tick::now();

	// 출력) 시간을 출력한다. (tick 시간은 현재 시간을 정확히 나타내지는 못한다.)
	std::cout << "1) tick::now()   "sv << to_string<char>(tick_now) << std::endl;

	// 출력) 기원 이후 시간을 출력한다.
	std::cout << "time_since_epoch  "sv << tick_now.time_since_epoch().count() <<std::endl;


	//-----------------------------------------------------------------------------
	//
	//  chrono::tick::duration은 다른 단위의 chrono::tick::duration의 조합으로 얻을 수 있다.
	//
	//    예1) 2초 345밀리초
	//         chrono::tick::duration t1_1 = tick::seconds(2) + tick::milliseconds(345);
	//		   chrono::tick::duration t1_2 = std::chrono::seconds(2) + std::chrono::milliseconds(345); // C++ 표준 std::chrono도 그대로 사용가능
	//		   chrono::tick::duration t1_2 = 2s + 345ms; // C++ std::chrono_literal로도 표시 가능
	//
	//    예2) 3분 12초
	//         chrono::tick::duration t2_1 = tick::minutes(3) + tick::seconds(12)
	//		   chrono::tick::duration t2_2 = 2min + 345s;
	//
	//    예3) 1시간 0분 12초 200미리초
	//         chrono::tick::duration t3_1 = tick::hours(1) + tick::seconds(12) + tick::milliseconds(200)
	//		   chrono::tick::duration t3_2 = 1h + 12s + 200ms;
	//
	//-----------------------------------------------------------------------------
	// 2) duration을 2초 345ms로 설정한다.
	chrono::tick::duration tick_diff = 2s + 345ms;

	// 출력) duration을 Milliseond로 출력한다.
	std::cout << "2) [2s 345ms]  "sv <<std::chrono::duration_cast<chrono::tick::milliseconds>(tick_diff).count() << "ms"sv << std::endl;

	// Duration만큼 Sleep한다.
	api::sleep_for(tick_diff);

	// 3) 현재 시간에서 tick_now을 빼면 그 차이 만큼의 차이(duration)을 얻을 수 있다.
	chrono::tick::duration tick_diff_now = chrono::tick::now() - tick_now;

	// 출력) 
	std::cout << "3) Differ Time after Sleep [2s 345ms]  "sv <<std::chrono::duration_cast<chrono::tick::milliseconds>(tick_diff_now).count() << "ms"sv <<std::endl;


	//-----------------------------------------------------------------------------
	//
	// 2. chrono::tick::time_point와 chrono::tick::duration 연산.
	//
	//    - chrono::tick::time_point에 chrono::tick::duration을 더하면 chrono::tick::time_point 시점에서
	//      chrono::tick::duration 만큼의 시간이 더해진 chrono::tick::time_point(시점)을 얻을 수 있다.
	//
	//    - chrono::tick::time_point에서 다른 시점의 chrono::tick::time_point를 빼면 
	//      그 차이 chrono::tick::duration을 얻을 수 이다.
	//
	//-----------------------------------------------------------------------------
	// 4) 현재 시간에서 3분 12초 이후의 시간을 얻는다.
	chrono::tick::time_point tick_next = tick_now + 3min + 12s;

	// 출력)
	std::cout << "4) NOW(" <<tick_now.time_since_epoch().count() <<") + [3min 12s]   "sv <<tick_next.time_since_epoch().count() << "ms"sv <<std::endl;

	// 출력) 두줄띄기
	std::cout << std::endl << std::endl;


	//-----------------------------------------------------------------------------
	//
	// 4. duration_cast
	//
	//    - duration값을 밀리초/초/분/시/일 등의 일정 단위의 정수값으로 얻는 것을 말한다.
	//
	//-----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	//
	// 5. time_point와 duration의 출력
	//
	//-----------------------------------------------------------------------------
}
