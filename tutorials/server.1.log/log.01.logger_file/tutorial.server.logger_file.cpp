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

own_ptr<logger_file> g_plogger_file;

int main()
{
	// ------------------------------------------------------------------
	// 설명)
	//
	//  CGCII에서 Log를 남기는 방법으로는 LOG(...)객체를 사용한다.
	//  또 로그를 남길 대상인 [로그 객체]를 생성해야한다.
	//  쉽게 말해서 남길 로그를 [로그 객체]로 전달해주는 함수가 LOG(...)함수이다.
	//
	//  [로그 객체]는 파일, 콘솔창, MFC콘트롤창, 네트워크, Slack과 같은 메신저 등
	//  다양한 것이 있을 수 있다.
	//  따라서 로그를 남기고 싶은 [로그 대상 객체]를 생성하고 초기화를 해야한다.
	//  그리고 LOG(...)함수를 사용해 [로그 대상 객체]에 로그를 남길 수 있다.
	// 
	//  LOG는 내부적으로 _log(...)함수를 사용한 것으로 함수 프로토타입은 다음과 같다.
	//  
	//    LOG( _dispatcher, _log_type, _log__level)
	// 
	//     1) _dispatcher	  로그를 전달할 [로그 대상 객체] (Ilog_targetable*를 상속받은 객체)
	//	   2) _log_type		  로그의 형식, 로그의 형식은 다음과 같다.
	//
	//						  log_type_t::progress	 = 1
	//						  log_type_t::debug		 = 2
	//						  log_type_t::fatal		 = 3
	//						  log_type_t::error		 = 4
	//						  log_type_t::user		 = 5
	//						  log_type_t::system	 = 6
	//
	//
	//     3) _log_level	  로그의 레벨이다. int형이므로 int값의 범위를 가진다.
	//						  하지만 자주 사용되는 레벨 값을 enum으로 설정해 놓은 값은 다음과 같다.
	//						
	//						  log_level_t::LOWEST	 = INT_MIN(약 -21억)
	//						  log_level_t::lower()		 = -256
	//						  log_level_t::normal()	 = 0
	//						  log_level_t::higher()	 = 256
	//						  log_level_t::highest()	 = INT_MAX(약 -21억)
	//
	// ------------------------------------------------------------------
	// ------------------------------------------------------------------
	// 1. 먼저 [로그 대상 객체]를 생성한다.
	// ------------------------------------------------------------------
	// 1) file에 로그를 남기는 [로그 대상 객체]를 생성한다.
	g_plogger_file = make_own<logger_file>();

	// 2) logger_file 객체의 파일명을 파라메터로 주어 초기화한다.
	auto result = g_plogger_file->initialize({ "./test_log_file.log"sv });

	// check) 만약 실패했다면 종료
	if(result != eRESULT::SUCCESS)
	{
		// view) 
		std::cout << "Fail to creating LOG file"sv << std::endl;

		// 아무키나 누를 때까지 대기한다.
		_getch();

		// return) 
		return 0;
	}

	// 3) 출력할 로그파일의 문자 인코딩을 결정한다.
	//    - log의 문자인코딩과 파일의 출력 문자인코딩이 다르면 변환하여 출력한다.
	//    - 따라서 Log의 문자 인코딩과 출력할 파일의 문자 인코딩이 동일하다면 
	//      가장 효율이 좋을 것이다.
	g_plogger_file->character_encoding(eCHARACTER_SET::MBCS);	// Multibye character encoding
	//g_plogger_file->character_encoding(eCHARACTER_SET::UCS2);	// Default
	//g_plogger_file->character_encoding(eCHARACTER_SET::UTF8);	// UTF-8 character encodeing


	// ------------------------------------------------------------------
	// 2. LOG()함수를 사용하여 로그를 출력한다.
	//    (로그 대상 객체를 g_plogger_file로 한다.)
	// ------------------------------------------------------------------

	// 1) 기본적인 로그 남기기
	LOG(g_plogger_file, log_type_t::info) << "[A] This paragraph is log"sv;

	// 2) 포맷 스트링이 필요할 때 fmt::format를 사용한다.
	LOG(g_plogger_file, log_type_t::info) << format("[A] This paragraph is log with number [{}]"sv, 10);
	LOG(g_plogger_file, log_type_t::info) << format("[A] This paragraph is log with string [{}]"sv, "STRING"sv);
	LOG(g_plogger_file, log_type_t::info) << format("[A] 이 문장은 멀티바이트 한글 문자열 로그 [{}]"sv, "STRING"sv);
	LOG(g_plogger_file, log_type_t::info) << format(L"[A] 이 문장은 유니코드 한글 문자열 로그 [{}]"sv, L"STRING"sv);

	// 3) 다중라인 (multi-line) - log_endl을 사용한다.
	LOG(g_plogger_file, log_type_t::info) << L"[B] 첫줄 문장은 유니코드 한글 문자열 로그 ["sv << L"STRING"sv << "]"sv << log_endl
									   << L"[B] 두째줄 문장은 유니코드 한글 문자열 로그 ["sv << L"STRING"sv << "]";


	// ------------------------------------------------------------------
	// 3. Performance test
	// ------------------------------------------------------------------
	// 1) get time
	auto tick_start = chrono::tick::now();

	for (int i = 0; i < 10000; ++i)
	{
		LOG(g_plogger_file, log_type_t::info) << "test log output to file"sv;
	}

	// 2) get time
	auto tick_diff = chrono::tick::now() - tick_start;

	// 3) 시간을 출력한다.
	std::cout << "elapsed time: "sv << std::chrono::duration_cast<std::chrono::milliseconds>(tick_diff).count() << "ms"sv << std::endl;

	// return) 끝.
	return 0;
}
