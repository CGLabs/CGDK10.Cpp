#include "cgdk/sdk10/net.socket.h"
#include "../../define_message.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

// 
// 설명) 접속을 종료처리하는 부분은 client(tut.socket.ex01.tcp_graceful_close.client)쪽 확인
//       
//       graceful close -> 정상적인 접속 종료. 
//                         데이터를 모두 송수신후 정상적인 접속 종료 처리를 한다.
//                         소켓의 접속 종료를 요청하더라도 즉시 처리되지 않을 수 있다. 
//
//                         psocket->disconnect();
//
//
//       abortive close -> 비정상접속 종료 처리. 
//                         송수신중이 데이터가 있다해도 즉각 접속 종료처리를 한다.
//                         소켓은 즉각 해제된다.
//
//                         psocket->closesocket();
//

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
	virtual result_code on_message(sMESSAGE_NETWORK& /*_msg*/) override
	{
		std::cout << " - message received"sv << '\n';
		return eRESULT::DONE;
	}
};

int main()
{
	// 1) acceptor 객체를 생성한다.
	auto pacceptor = make_own<net::acceptor<socket_tcp>>();

	// 2) acceptor를 시작한다.(20000번 포트에서 listen을 시작한다.)
	pacceptor->start({{ net::ip::make_address("any"sv), 20000 }});

	// - ESC키를 누를 때까지 대기한다.
	while(_getch() != 27);

	// end) 서버 종료
	return 0;
}
