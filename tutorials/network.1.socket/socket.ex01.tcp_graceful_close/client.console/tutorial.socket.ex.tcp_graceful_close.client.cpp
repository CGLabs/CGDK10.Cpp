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
//
//  테스트 내용)
//
//    A => 접속된 소켓에 eMESSAGE_A를 10번 전송하고 abortive close 한다.
//         서버쪽에서는 eMESSAGE_A를 10번을 모두 받지 못하거나 전혀 받지 못하고 접속종료가 된다.
//
//    B =? 접속된 소켓에 eMESSAGE_A를 10번 전송하고 graceful close 한다.
//         서버쪽에서는 eMESSAGE_A를 10번을 모두 받고 난 후에 접속종료가 된다.
//
//

// 1) socket 클래스를 정의한다.
class socket_tcp_client : public net::socket::tcp_client<>
{
	// (v) 접속 시 호출되는 함수
	virtual void on_connect() override
	{
		std::cout << " @ connected"sv << '\n';
	}

	// (v) 접속 실패시 호출되는 함수
	virtual void on_fail_connect(uint64_t /*_disconnect_reason*/) override
	{
		std::cout << " @ fail to connecting"sv << '\n';
	}

	// (v) 접속 종료 시 호출되는 함수
	virtual void on_disconnect(uint64_t) override
	{
		std::cout << " @ disconnected"sv << '\n';
	}

	// (v) 메시지를 수신했을 때 호출 되는 함수.
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override
	{
		// 1) message head를 읽습니다.
		auto msg_header = _msg.buf_message.front<sMESSAGE_HEADER>();

		// 2) message 종류에 따른 처리를 한다.
		switch (msg_header.type)
		{
		case	eMESSAGE_TYPE::SEND_A:
				std::cout << " 'eMESSAGE_TYPE::SEND_A' received"sv << '\n';
				break;

		case	eMESSAGE_TYPE::SEND_B:
				std::cout << " 'eMESSAGE_TYPE::SEND_B' received"sv << '\n';
				break;
		default:
				std::cout << " undefined message received"sv << '\n';
				break;
		}

		return eRESULT::DONE;
	}
};

shared_buffer message_A()
{
	// - message
	sMESSAGE_A	message;

	message.size = get_size_of<uint32_t>(message);
	message.type = eMESSAGE_TYPE::SEND_A;
	message.x	 = 0;
	message.y	 = 1;
	message.z	 = 10.0f;

	// - make shared buffer
	auto buf_message = make_shared_buffer(message);

	// return)
	return buf_message;
}


int main()
{
	// trace) 
	std::cout << "start client [tut.socket.01.tcp_simple.client]..."sv << '\n';

	// 2) 접속을 시도할 'socket_tcp_client' 소켓 객체를 생성한다.
	auto psocket = make_own<socket_tcp_client>();

	// comment)
	std::cout << " 'A' key: send 10 messages and closesocket(abortive close)"sv << '\n';
	std::cout << " 'B' key: send 10 messages and disconnect(graceful close)"sv << '\n';
	std::cout << " 'C' key: connnect"sv << '\n' << '\n';
	std::cout << " 'ESC' key: terminate"sv << '\n' << '\n';

	// 3) 20000번 포트에서 접속을 시도한다. (ip::address나 resolver로 설정이 가능하다.)
	psocket->start({{ net::ip::address_v4::loopback(), 20000 }});

	// 4) 메시지 무한 루프~
	for(;;)
	{
		// - key 눌렀나?
		if (_kbhit())
		{
			// - Key를 읽는다.
			int	ch = _getch();

			// - ESC키를 누르면 접속을 종료한다.
			if (ch == 27)
			{
				break;
			}
			// - A key - send 10 messages and closesocket(abortive close)
			else if (ch == 'a' || ch == 'A')
			{
				// - make message
				auto buf_send = message_A();

				// - send message 10 times
				for (int i = 0; i < 10; ++i)
				{
					psocket->send(buf_send);
				}

				// - abortive close
				psocket->closesocket();
			}
			// - B key - send 10 messages and disconnect(graceful close)
			else if (ch == 'b' || ch == 'B')
			{
				// - make message
				auto buf_send = message_A();

				// - send message 10 times
				for (int i = 0; i < 10; ++i)
				{
					psocket->send(buf_send);
				}

				// - graceful close
				psocket->disconnect();
			}
			// - C key - connect new socket
			else if (ch == 'c' || ch == 'C')
			{
				// - close old socket
				psocket->closesocket();

				// - alloc new socket
				psocket = make_own<socket_tcp_client>();

				// - connect
				psocket->start({{ net::ip::address_v4::loopback(), 20000 }});
			}
		}

		// - 1ms 슬립한다. (CPU를 너무 많이 먹으므로...)
		std::this_thread::sleep_for(1ms);
	}

	// trace) 
	std::cout << "stop client [tut.socket.01.tcp_simple.client]..."sv << '\n';

	// end) 종료
	return 0;
}
