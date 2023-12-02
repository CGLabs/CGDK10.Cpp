#include "cgdk/sdk10/net.socket.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

// 1) 재접속 가능한 socket 클래스를 정의한다.
class socket_tcp_client : public net::socket::tcp_client_reconnect<>
{
	// (v) 접속 시 호출되는 함수
	virtual void on_connect() override
	{
		std::cout << " @ connected"sv<< '\n';
	}

	// (v) 접속 실패시 호출되는 함수
	virtual void on_fail_connect(uint64_t /*_disconnect_reason*/) override
	{
		std::cout << " @ fail to connecting"sv << '\n';
	}

	// (v) 접속 실패시 호출되는 함수
	virtual void on_request_reconnect(net::io::Iconnective* /*_pconnective*/) override
	{
		std::cout << " @ try reconnectting"sv << '\n';
	}

	// (v) 접속 종료 시 호출되는 함수
	virtual void on_disconnect(uint64_t) override
	{
		std::cout << " @ disconnected"sv<< '\n';
	}

	// (v) 메시지를 수신했을 때 호출 되는 함수.
	virtual result_code on_message(sMESSAGE_NETWORK& /*_msg*/) override
	{
		// return)
		return eRESULT::DONE;
	}
};

int main()
{
	// trace) 
	std::cout << "start client [tut.socket.01.tcp_simple.client]..."sv << '\n';

	// comment)
	std::cout << " 'Z' key: closesocket"sv << '\n';
	std::cout << " 'X' key: closesocket with disable reconnecting"sv << '\n';
	std::cout << " 'ESC' key: terminate"sv << '\n';

	// 2) 접속을 시도할 'socket_tcp_client' 소켓 객체를 생성한다.
	auto psocket = make_own<socket_tcp_client>();

	// 3) 재접속을 enable한다.
	psocket->enable_reconnect(true); // 재접속 기능 활성화
	psocket->set_reconnect_interval(5s); // 재접속 간격은 5초

	// 3) 20000번 포트에서 접속을 시도한다. (ip::address나 resolver로 설정이 가능하다.)
	psocket->start({{ net::ip::address_v4::loopback(), 20000 }});

	// 4) 메시지 무한 루프~
	for(;;)
	{
		// - key 눌렀나?
		if(_kbhit())
		{
			// - Key를 읽는다.
			int	ch = _getch();

			// - ESC키를 누르면 접속을 종료한다.
			if (ch == 27)
			{
				break;
			}
			// - Z키 누르면 접속종료 요청합니다. (곧 재접속됩니다.)
			else if(ch=='z' || ch=='Z')
			{
				// - send
				psocket->closesocket();
			}
			// - X키 누르면 재접속기능을 끄고 접속종료 요청합니다.
			else if (ch == 'x' || ch == 'X')
			{
				// - 먼저 재접속 기능을 끈다.
				psocket->disable_reconnect();

				// - 접속종료
				psocket->closesocket();
			}
		}

		// - 1ms 슬립한다. (CPU를 너무 많이 먹으므로...)
		std::this_thread::sleep_for(1ms);
	}

	// 5) 먼저 재접속 기능을 끈다.
	psocket->disable_reconnect();

	// 6) socket을 close한다.
	psocket->closesocket();

	// trace) 
	std::cout << "stop client [tut.socket.01.tcp_simple.client]..."sv << '\n';

	// end) 종료
	return 0;
}
