#if defined(_WIN32)
	#include <conio.h>
#endif

// @ CGCII header files
#include "cgdk/sdk10/net.socket.h"

// @ header files
#include <iostream>

// @ namespace
using namespace CGDK;

// @) socket 클래스 정의
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
		this->send(_msg.buf_message);

		return eRESULT::DONE;
	}
};

int main()
{
	// trace) 
	std::cout << "start server [tut.socket.01.tcp_simple.server]..."sv << std::endl;

	try
	{
		// 1) acceptor 객체를 생성한다.
		auto pacceptor = make_own<net::acceptor<socket_tcp>>();

		// 2) acceptor를 시작한다.(20000번 포트에서 listen을 시작한다.)
		//    - bind할 address를 직접 넣어도 된다. 아래와 같이 하면 bind_any, 20000포트로 접속을 받는다.
		//    - net::ip::tcp::v4()로 설정하면 ipv4만 접속을 받으며
		//    - net::ip::tcp::v6()로 설정하면 ipv4와 ipv6 모두 접속을 받는다.
		//    - net::ip::make_address를 사용해 직접 값을 써넣을 수도 있다.
		//pacceptor->start({net::ip::tcp::v6(), 20000});
		pacceptor->start({{ net::ip::make_address("any"sv), 20000 }});

		// 3) ESC키를 누를 때까지 대기한다.
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
