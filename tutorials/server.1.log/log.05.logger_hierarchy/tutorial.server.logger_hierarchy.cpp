#include "cgdk/sdk10/server.log.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

#if defined(__cpp_lib_format)
	using std::format;
#else
	using fmt::format;
#endif

own_ptr<logger_hub> g_plogger;

int main()
{
	// ------------------------------------------------------------------
	//
	// 1. [로그 대상 객체]를 계층적으로 구성하면 한번의 LOG()함수 호출로
	//    여러 [로그 대상 객체]에 모두 로그를 전달할 수 있다.
	//    
	//    예를 들면 로그를 파일로도 남기고 콘솔화면으로도 남기고 싶다면
	//    먼저 부모 [로그 객체]를 생성한 후 
	//    파일로 남기는 [로그 객체]와 콘솔창에 로그를 남기는 [로그 객체]를 
	//    이 부모 로그 객체의 자식 로그로 붙이게 되면 부모 [로그 객체]에 
	//    로그를 전달하는 것만으로 자식 로그 객체 모두에게 전달된다.
	//
	// ------------------------------------------------------------------

	// 1) 콘솔창 [로그 대상 객체]을 생성한다.
	auto plogger_console = make_own<logger_console>();

	// 2) 콘솔창 [로그 대상 객체]을 초기화한다.
	plogger_console->initialize();

	// 3) 파일 [로그 대상 객체]를 생성한다.
	auto plogger_file = make_own<logger_file>();

	// 4) 파일 [로그 대상 객체]를 초기화한다.
	plogger_file->initialize({ "./test_log_hierarchy.log"sv });

	// 5) 부모 [로그 대상 객체]를 로그 객체를 생성한다.
	g_plogger = make_own<logger_hub_archive>();

	// 6) 부모 [로그 대상 객체]인 g_plogger에 plogger_console와 plogger_file를 자식 로그 객체로 연결한다.
	g_plogger->register_log_targetable(plogger_console);
	g_plogger->register_log_targetable(plogger_file);
	
	// 7) 시작한다.
	g_plogger->initialize();

	// 8) 이제 부모 [로그 대상 객체]인 g_plogger에 로그를 전달하면
	//    자식 [로그 대상 객체]인 plogger_console과 plogger_file에게도 로그가 전달 된다.
	LOG(g_plogger, log_type_t::info) << "This paragraph is log"sv;
	LOG(g_plogger, log_type_t::info) << format("This paragraph is log with number [{}]"sv, 10);
	LOG(g_plogger, log_type_t::info) << format(L"This paragraph is log with string [{}]"sv, L"STRING"sv);


	// 9) wait input ESC key
	while (_getch() != 27);

	// return)
	return 0;
}
