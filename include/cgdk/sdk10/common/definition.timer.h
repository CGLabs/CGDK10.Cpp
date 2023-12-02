//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                  Common                                   *
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
//-----------------------------------------------------------------------------
// Include)
//-----------------------------------------------------------------------------
// 1) Standard Files
#include <chrono>
#include <ctime>
#include <ratio>

#if defined(_WIN32)
	#include <time.h>
#elif defined(__linux__)

#include <sys/time.h>
//#include <linux/time.h>

inline uint64_t GetTickCount64()
{
	timeval	tick;
    gettimeofday (&tick, nullptr);
    return (static_cast<uint64_t>(tick.tv_sec)*1000 + static_cast<uint64_t>(tick.tv_usec)/1000);
}
#endif

constexpr bool is_leap_year(int _year)
{
	return _year % 4 == 0 && (_year % 100 != 0 || _year % 400 == 0);
}

constexpr int get_day_of_year(int _year, int _month, int _day)
{
	// Static)				      0    1    2    3    4    5    6    7    8    9   10   11   12  13  
	constexpr int	t[2 * 14] = { 0,   0,  31,  59,  90, 120, 151, 181, 212, 243, 273, 304, 334, 0,
								  0,   0,  31,  60,  91, 121, 152, 182, 213, 244, 274, 305, 335, 0 };

	return	*(t + static_cast<size_t>(is_leap_year(_year)) * 14 + _month) + _day;
}

constexpr int get_day_of_week(int _year, int _month, int _day)
{
	// Explanation)
	//    0 - Sunday
	//    1 - Monday
	//    2 - Tuesday
	//    3 - Wednesday
	//    4 - Thursday
	//    5 - Friday
	//    6 - Saturday

	// Static) 
	constexpr int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

	// 1) 2월 을 초과하지 않았을 경우 1을 뺀다.
	_year -= _month < 3;

	// 2) 요일을 리턴한다.
	return (_year + _year/4 - _year/100 + _year/400 + *(t + (static_cast<size_t>(_month) - 1)) + _day) % 7;
}
