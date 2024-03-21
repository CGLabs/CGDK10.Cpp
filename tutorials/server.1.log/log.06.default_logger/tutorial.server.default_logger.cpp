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

// 1) socket 클래스를 정의한다.
class socket_tcp : public net::socket::tcp<>
{
	// (v) 접속 시 호출되는 함수
	virtual void on_connect() override
	{
		// log) 
		LOG(log_type_t::info) << " @ connected"sv;
	}

	// (v) 접속 종료 시 호출되는 함수
	virtual void on_disconnect(uint64_t /*_disconnect_reason*/) override
	{
		// log) 
		LOG(log_type_t::info) << " @ disconnected"sv;
	}

	// (v) 메시지를 수신했을 때 호출 되는 함수.
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override
	{
		// log) 
		LOG(log_type_t::info) << "   - message received and echo sended!"sv;

		// - echo send
		send(_msg.buf_message);  
		
		// return) 
		return eRESULT::DONE;
	}
};

int main()
{
	// ------------------------------------------------------------------
	// 설명)
	//
	//  LOG(...)로 [로그 대상 객체]를 파라메터로 넘겨주어야 한다.
	//  하지만 생략하거나 nullptr을 전달할 경우 기본 [로그 대상 객체]에
	//  로그를 전달하게 된다.
	//  기본 [로그 대상 객체]는 set_default_logger()함수를 사용해서 설정할 수 있다.
	//
	//  또 기본 [로그 대상 객체]를 설정하면 엔진 내부적으로 발생하는 로그를
	//  기본 [로그 대상 객체]로 출력받을 수 있다.
	//
	// ------------------------------------------------------------------

	// 1) [로그 대상 객체]를 생성한다.
	auto plog = make_own<logger_console>();

	// 2) 시작
	plog->initialize();

	// *3) 기본 [로구 대상 객체]로 설정한다.
	set_default_logger(plog);

	// * 여기서부터 내부적으로 생성되는 LOG 메시지들이 기본 로그 객체에 찍힌다.
	// trace) 
	LOG(log_type_t::system) << log_level_t::higher() << "-----------------------------------------------------------------"sv;
	LOG(log_type_t::system) << log_level_t::higher() << " "sv;
	LOG(log_type_t::system) << log_level_t::higher() << "                  tutoral.server.default_log"sv;
	LOG(log_type_t::system) << log_level_t::higher() << " "sv;
	LOG(log_type_t::system) << log_level_t::higher() << "-----------------------------------------------------------------"sv;

	// 4) acceptor 객체를 생성한다.
	auto pacceptor = make_own<net::acceptor<socket_tcp>>();

	// 5) acceptor를 시작한다.
	pacceptor->start({{ net::ip::make_address("any"sv), 20000 }});

	// 6) [로그 대상 객체]를 생략하면 기본 [로그 대상 객체]에 전달한다.
	LOG(log_type_t::progress) << "start server [tut.socket.01.tcp_simple.server]..."sv;
	LOG(log_type_t::info) << "This paragraph is log"sv;
	LOG(log_type_t::info) << format("This paragraph is log with number [{}]"sv, 10);
	LOG(log_type_t::info) << format("This paragraph is log with string [{}]"sv, "STRING"sv);

	// *7) 기본 객체를 제거한다. (reset으로 종료하지 않아도 자동 제거되긴 한다.)
	reset_default_logger();

	// 8) wait input ESC key
	while (_getch() != 27);

	// return)
	return 0;
}
