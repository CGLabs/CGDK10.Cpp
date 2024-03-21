#include "cgdk/sdk10/server.log.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;


int main()
{
	// ------------------------------------------------------------------
	// 1. 로그 필터 (Log Filter)
	//    1) [로그 필터링 객체]는 특정 로그만 필터링해낼 수 있도록 해준다.
	//    2) [로그 필터링 객체]를 생성하여 [로그 대상 객체]에 설정해 줌으로써 동작한다.
	//    3) [로그 필터링 객체]를 사용하기 위해서는 다음과 같은 작업을 수행해야 한다.
	//       - 먼저 [로그 필터 객체]를 생성한다.
	//       - 생성한 [로그 필터 객체]의 필터링 정보를 설정한다.
	//       - [로그 필터링 객체]를 [로그 대상 객체]에 설정한다.
	//
	//    4) [로그 필터 객체]의 필터링 정보는 [로그 형태]별로 가능하다.
	//       - enable_log() 멤버 함수를 사용하여 특정 [로그 형태]의 필터링 가능 여부를 설정한다.
	//       - enable_filtering_by_level_range()를 사용하여 레벨 정보로 필터링할 것임을 설정해야 한다.
	//       - set_filtering_range_by_level()함수를 사용하여 통과할 레벨 정보를 설정해야 한다.
	//
	//       주의) 필터링 정보는 Level, Source, Destination, Location 등이 있지만 현재는 Level만 사용한다.
	//
	//    5) set_filtering_range_by_level()함수를 사용해 필터링 레벨 범위를 설정할 수 있다.
	//       Level값은 int형이므로 -21억에서 21억 정도의 범위를 가진다.
	//       하지만 일반적으로 많이 사용하는 값을 enum으로 설정해 놓았다.
	//
	//			log_level_t::LOWEST		 = INT_MIN,
	//			log_level_t::lower()		 = -256,
	//			log_level_t::normal()	 = 0,
	//			log_level_t::higher()	 = 256,
	//			log_level_t::highest()	 = INT_MAX,
	//
	//      Log Level 값은 꼭 enum으로 설정된 log_level_t값이 아니라도 
	//      임의의 값을 설정할 수 있다.
	//       
	// ------------------------------------------------------------------
	// 1) [로그 필터](log filter) 객체를 생성한다.
	auto plog_filter = make_own<log_filter>();

	// 2) 각 로그 종류(log_type_t) 마다 필터링을 할지 하지 않을 지 설정할 수 있다.
	//    - 필터링을 원하는 로그 종류는 enable해 준다.
	//    - 레벨 범위에 따른 필터링을 할지 하지 않을 지 설정한다.
	//      필터링할 로그 레벨 범위를 설정해준다.
	plog_filter->enable_log							(log_type_t::info);
	plog_filter->enable_filtering_by_level_range	(log_type_t::info);
	plog_filter->set_filtering_range_by_level		(log_type_t::info, log_level_t::higher(), log_level_t::highest());

	// 3) PROGRESS Log type에 대해서 filtering을 enable한다.
	//    PROGRESS Log type은 log_level_t::normal()이상 log_level_t::highest()이하일 때만 출력한다.
	plog_filter->enable_log							(log_type_t::progress);
	plog_filter->enable_filtering_by_level_range	(log_type_t::progress);
	plog_filter->set_filtering_range_by_level		(log_type_t::progress, log_level_t::normal(), log_level_t::highest());

	// 4) Exception Log는 enable합니다.
	plog_filter->enable_log(log_type_t::debug,		false);
	plog_filter->enable_log(log_type_t::fatal,		true);
	plog_filter->enable_log(log_type_t::error,		true);
	plog_filter->enable_log(log_type_t::user,		false);
	plog_filter->enable_log(log_type_t::system,		true);

	// 
	// 여기서 enable되지 않은 로그형(LOG TYPE)에 대해서는 아무런 Filtering을 하지 않게 된다.
	// 즉 log_type_t::INFO와 log_type_t::progress만 filtering을 수행하며 나머지는 그냥 출력한다.
	//
	//	log_type_t::info        => LEVEL값이 log_level_t::HIGH이상 log_level_t::highest()이하일 때만 출력한다.
	//	log_type_t::progress	=> LEVEL값이 log_level_t::normal()이상 log_level_t::highest()이하일 때만 출력한다.
	//	log_type_t::debug		=> 무조건 출력하지 않음.
	//	log_type_t::fatal		=> 무조건 출력함.
	//	log_type_t::error		=> 무조건 출력함.
	//	log_type_t::user		=> 무조건 출력력하지 않음.
	//	log_type_t::system		=> 무조건 출력함.
	// 


	// ------------------------------------------------------------------
	// 1. Log File을 open한다.
	// ------------------------------------------------------------------
	// 1) [로그 대상 객체]를 생성한다.
	auto plogger_console = make_own<logger_console>();

	// 2) [로그 필터링 객체]를 [로그 대상 객체]에 설정한다.
	plogger_console->set_filter(plog_filter);

	// 3) 시작한다.
	plogger_console->initialize();

	// view) 
	std::cout << "Log Filter 예제를 시작합니다."sv << std::endl;

	// 4) log를 출력한다.
	LOG(plogger_console, log_type_t::info)		<< log_level_t::lower()		<< "Type:INFO, Level:log_level_t::lower()"sv;
	LOG(plogger_console, log_type_t::info)		<< log_level_t::normal()	<< "Type:INFO, Level:log_level_t::normal()"sv;
	LOG(plogger_console, log_type_t::info)		<< log_level_t::higher()	<< "Type:INFO, Level:log_level_t::higher()"sv;
	LOG(plogger_console, log_type_t::info)		<< log_level_t::highest()	<< "Type:INFO, Level:log_level_t::highest()"sv;
	std::cout << std::endl;

	LOG(plogger_console, log_type_t::progress)	<< log_level_t::lower()		<< "Type:PROGRESS, Level:log_level_t::lower()"sv;
	LOG(plogger_console, log_type_t::progress)	<< log_level_t::normal()	<< "Type:PROGRESS, Level:log_level_t::normal()"sv;
	LOG(plogger_console, log_type_t::progress)	<< log_level_t::higher()	<< "Type:PROGRESS, Level:log_level_t::higher()"sv;
	LOG(plogger_console, log_type_t::progress)	<< log_level_t::highest()	<< "Type:PROGRESS, Level:log_level_t::highest()"sv;
	std::cout << std::endl;

	LOG(plogger_console, log_type_t::debug)		<< log_level_t::lower()		<< "Type:DEBUG, Level:log_level_t::lower()"sv;
	LOG(plogger_console, log_type_t::debug)		<< log_level_t::normal()	<< "Type:DEBUG, Level:log_level_t::normal()"sv;
	LOG(plogger_console, log_type_t::debug)		<< log_level_t::higher()	<< "Type:DEBUG, Level:log_level_t::higher()"sv;
	LOG(plogger_console, log_type_t::debug)		<< log_level_t::highest()	<< "Type:DEBUG, Level:log_level_t::highest()"sv;
	std::cout << std::endl;

	LOG(plogger_console, log_type_t::fatal)		<< log_level_t::lower()		<< "Type:FATAL, Level:log_level_t::lower()"sv;
	LOG(plogger_console, log_type_t::fatal)		<< log_level_t::normal()	<< "Type:FATAL, Level:log_level_t::normal()"sv;
	LOG(plogger_console, log_type_t::fatal)		<< log_level_t::higher()	<< "Type:FATAL, Level:log_level_t::higher()"sv;
	LOG(plogger_console, log_type_t::fatal)		<< log_level_t::highest()	<< "Type:FATAL, Level:log_level_t::highest()"sv;
	std::cout << std::endl;

	LOG(plogger_console, log_type_t::error)		<< log_level_t::lower()		<< "Type:ERROR, Level:log_level_t::lower()"sv;
	LOG(plogger_console, log_type_t::error)		<< log_level_t::normal()	<< "Type:ERROR, Level:log_level_t::normal()"sv;
	LOG(plogger_console, log_type_t::error)		<< log_level_t::higher()	<< "Type:ERROR, Level:log_level_t::higher()"sv;
	LOG(plogger_console, log_type_t::error)		<< log_level_t::highest()	<< "Type:ERROR, Level:log_level_t::highest()"sv;
	std::cout << std::endl;

	LOG(plogger_console, log_type_t::user)		<< log_level_t::lower()		<< "Type:USER, Level:log_level_t::lower()"sv;
	LOG(plogger_console, log_type_t::user)		<< log_level_t::normal()	<< "Type:USER, Level:log_level_t::normal()"sv;
	LOG(plogger_console, log_type_t::user)		<< log_level_t::higher()	<< "Type:USER, Level:log_level_t::higher()"sv;
	LOG(plogger_console, log_type_t::user)		<< log_level_t::highest()	<< "Type:USER, Level:log_level_t::highest()"sv;
	std::cout << std::endl;

	LOG(plogger_console, log_type_t::system)	<< log_level_t::lower()		<< "Type:SYSTEM, Level:log_level_t::lower()"sv;
	LOG(plogger_console, log_type_t::system)	<< log_level_t::normal()	<< "Type:SYSTEM, Level:log_level_t::normal()"sv;
	LOG(plogger_console, log_type_t::system)	<< log_level_t::higher()	<< "Type:SYSTEM, Level:log_level_t::higher()"sv;
	LOG(plogger_console, log_type_t::system)	<< log_level_t::highest()	<< "Type:SYSTEM, Level:log_level_t::highest()"sv;
	std::cout << std::endl;

	// return)
	return 0;
}
