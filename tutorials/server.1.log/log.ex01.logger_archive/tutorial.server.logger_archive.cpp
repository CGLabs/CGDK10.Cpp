#include "cgdk/sdk10/server.log.h"
#include "cgdk/sdk10/net.socket.h"

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

	// 1) 콘솔창 [로그 대상 객체]를 생성한다.
	auto plogger_file_1 = make_own<logger_file>();

	// 2) 콘솔창 [로그 대상 객체]를 초기화한다.
	plogger_file_1->initialize({ "test_log_archive_1.log"sv });

	// 3) 파일 [로그 대상 객체]를 생성한다.
	auto plogger_file_2 = make_own<logger_file>();

	// 4) 파일 [로그 대상 객체]를 초기화한다.
	plogger_file_2->initialize({ "test_log_archive_2.log"sv });

	// 5) 부모 [로그 대상 객체]를 로그 객체를 생성한다.
	g_plogger = make_own<logger_hub_archive>();

	// 6) 부모 [로그 대상 객체]인 g_plogger에 plogger_file_1와 plogger_file_2를 자식 로그 객체로 연결한다.
	g_plogger->register_log_targetable(plogger_file_1);
	g_plogger->register_log_targetable(plogger_file_2);

	// 7) 시작한다.
	g_plogger->initialize();

	// 8) 대규모 log를 남긴다.
	for (int i = 0; i < 10000; ++i)
	{
		LOG(g_plogger, log_type_t::info) << "This paragraph is log"sv;
		LOG(g_plogger, log_type_t::info) << format("This paragraph is log with number [{}]"sv, 10);
		LOG(g_plogger, log_type_t::info) << format(L"This paragraph is log with string [{}]"sv, L"STRING"sv);
	}
	LOG(g_plogger, log_type_t::info) << "complete"sv;


	// ------------------------------------------------------------------
	// 2. Performance test
	// ------------------------------------------------------------------
	// 1) get time
	auto tick_start = chrono::tick::now();

	for (int i = 0; i < 10000; ++i)
	{
		LOG(g_plogger, log_type_t::info) << "test log output to hub"sv;
	}

	// 2) get time
	auto tick_diff = chrono::tick::now() - tick_start;

	// 3) 시간을 출력한다.
	std::cout << "elapsed time: "sv << std::chrono::duration_cast<std::chrono::milliseconds>(tick_diff).count() << "ms"sv << std::endl;


	// 4) wait input ESC key
	while (_getch() != 27);

	// return)
	return 0;
}
