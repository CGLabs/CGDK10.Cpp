#include "cgdk/sdk10/net.socket.h"
#include "cgdk/sdk10/server.log.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;


class socket_tcp : public net::socket::tcp<>
{
	// (v) 접속 시 호출되는 함수
	virtual void on_connect() override 
	{
		std::cout << " @ connected"sv << '\n'; 
	}

	// (v) 접속 종료 시 호출되는 함수
	virtual void on_disconnect(uint64_t /*_disconnect_reason*/) override 
	{
		std::cout << " @ disconnected"sv << '\n'; 
	}

	// (v) 메시지를 수신했을 때 호출 되는 함수.
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override
	{
		std::cout << " message received and echo sended!"sv << std::endl;
		send(_msg.buf_message);  

		return eRESULT::DONE;
	}
};

int main()
{
	// trace) 
	std::cout << "start client [tut.socket.ex08.socket_logger]..."sv << '\n';


	//-----------------------------------------------------------------------------
	//
	// 설명) socket logger란...
	//
	//  소켓의 송신과 수신 혹은 접속과 접속해제에 관한 정보를 상세히 로그 정보로 남
	//  길수 있다.
	//  일반적으로 소켓과 관련해서 접속과 접속 끊김 문제 혹은 메시지 송수신 과정에서
	//  발생하는 문제를 확인하기 위해서 많이 사용한다.
	//
	//  CGDK::net::io::socket_logger를 설정만 하면 해당 logger에 소켓 정보를 남긴다.
	// 
	//   CGDK::net::io::set_default::socket_logger([logger]);
	//
	//  함수를 사용해 logger를 설정하면 이후 생성되는 socket에서 자동 설정되여 log를
	// 	남긴다.
	//
	//-----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	//
	// 1. logger를 만들어 default socket logger로 설정한다.
	// 
	//-----------------------------------------------------------------------------
	{
		// 1) filelogger를 생성한다.
		auto plogger_file = make_object<logger_file>();

		// 2) logger를 초기화한다.
		plogger_file->initialize();

		// 3) logger를 생성해 default socket logger로 설정한다.
		net::io::set_default_socket_debug_logger(plogger_file);
	}

	//-----------------------------------------------------------------------------
	//
	//  2. 서버를 시작한다.
	// 
	//-----------------------------------------------------------------------------
	try
	{
		// 1) acceptor 객체를 생성한다.
		auto pacceptor = make_own<net::acceptor<socket_tcp>>();

		// 2) acceptor를 시작한다.(20000번 포트에서 listen을 시작한다.)
		pacceptor->start({{ net::ip::make_address("any"sv), 20000 }});

		// - ESC키를 누를 때까지 대기한다.
		while(_getch() != 27);
	}
	catch (...)
	{

	}

	// trace) 
	std::cout << "stop server [tut.socket.01.tcp_simple.server]..."sv << std::endl;

	// end) 서버 종료
	return 0;
}
