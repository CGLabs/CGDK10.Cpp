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
// tutorial common - TIME
//
//    - 시간을 년/달/시/분/초 단위로 구분되어 저장되므로 바로 이 값들을
//      출력가능하다.
//    - tick에 비해 크기가 크며 처리 속도가 많이 떨어진다.
//    - 큰 단위의 시간을 처리할 때 주료 사용된다.
//    - TIME은 local Time과 utc time(GMT시간)으로 구분된다.
//-----------------------------------------------------------------------------
void tutorial_TIME()
{
	// 1) 현재의 utc(GMT) 시간을 얻는다.
	chrono::time::utc::time_point time_utc_now = chrono::time::utc::now();

	// 출력) 시간을 출력한다.
	std::cout <<"1) chrono::time::utc::now()"sv << std::endl;

	// 2) 년월일시분초로 변환하려면 to_data_time함수를 호출해줘야 한다.
	{
		auto temp = chrono::to_date_time(time_utc_now);
		std::cout << temp.t_year << '-' << temp.t_month << '-' << temp.t_day << ' ' << temp.t_hour << ':' << temp.t_minute << ':' << temp.t_second << '.' << temp.t_fraction << '\n';
	}

	// 3) duration을 설정한다
	chrono::time::duration time_duration = chrono::days(20) + chrono::hours(10) + chrono::seconds(11);

	// 4) 현재 utc(GMT)시간에서 20일 10시간 11초 이후의 시간을 구한다.
	chrono::time::utc::time_point time_utc_new = time_utc_now + time_duration;

	// 출력) 시간을 출력한다.
	std::cout <<"3) chrono::time::utc::now()+(20d 10h 11s)"sv << std::endl;
	std::cout << to_string<char>(time_utc_new) << std::endl;
	std::cout << std::endl;

	// 5) local 시간을 구한다.
	chrono::time::local::time_point	time_local_now = chrono::time::local::now();

	// 출력) 시간을 출력한다.
	std::cout <<"5) chrono::time::local::now()"sv <<std::endl;
	std::cout << to_string<char>(time_local_now) << std::endl;

	// 6) 현재 local시간에서 20일 10시간, 11초 이후의 시간을 구한다.
	chrono::time::local::time_point	time_local_new = time_local_now+time_duration;

	// 출력) 시간을 출력한다.
	std::cout <<"6) chrono::time::local::now()+(20d 10h 11s)"sv <<std::endl;
	std::cout << to_string<char>(time_local_new) << std::endl;
	std::cout << std::endl;

	// 7) utc 시간을 local 시간에 대입하면 자동 변환된다.
	chrono::time::local::time_point	time_local_temp = time_utc_now;

	// 출력) 시간을 출력한다.
	std::cout <<"7) chrono::time::utc::time_point to chrono::local::time_point"sv <<std::endl;
	std::cout << to_string<char>(time_local_temp) << std::endl;
}
