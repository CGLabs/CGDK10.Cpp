#include "cgdk/sdk10/net.socket.h"
#include "../../define_message.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

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

int main()
{
	// trace) 
	std::cout << "start client []..."sv << '\n';

	// 2) 접속을 시도할 'socket_tcp_client' 소켓 객체를 생성한다.
	auto psocket = make_own<socket_tcp_client>();

	// 3) 20000번 포트에서 접속을 시도한다.
	psocket->start({{ net::ip::address_v4::loopback(), 20000 }});

	// comment)
	std::cout << " 'A' key: send message 'eMESSAGE_TYPE::SEND_A'"sv << '\n';
	std::cout << " 'B' key: send message 'eMESSAGE_TYPE::SEND_A'"sv << '\n';
	std::cout << " ESC key: terminate" << '\n';

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
			// - A키 누르면 Message B를 전송한다.
			else if(ch=='a' || ch=='A')
			{
				// - message
				sMESSAGE_A	message;
				message.size = get_size_of<uint32_t>(message);
				message.type = eMESSAGE_TYPE::SEND_A;
				message.x	 = 0;
				message.y	 = 1;
				message.z	 = 10.0f;

				// - send
				psocket->send(make_shared_buffer(message));
			}
			// - B키 누르면 Message B를 전송한다.
			else if(ch=='b' || ch=='B')
			{
				// - message
				sMESSAGE_B	message;
				message.type = eMESSAGE_TYPE::SEND_B;
				message.a	 = 10;
				message.b	 = "test message"s;
				message.c	 = {1,3,4,5,7,9};
				message.d	 = {{1, "pencil"s}, {2, "apple"s}, {3, "pineapple"s}};

				// - set message length (가변길이 메시지는 반드시 메시지를 다 작성한 후에 길이를 계산해 써넣어야 한다.)
				message.size = get_size_of<uint32_t>(message);

				// - send
				psocket->send(make_shared_buffer(message));
			}
		}

		// - 1ms 슬립한다. (CPU를 너무 많이 먹으므로...)
		std::this_thread::sleep_for(1ms);
	}

	// trace) 
	std::cout << "stop server []..."sv << '\n';

	// end) 종료
	return 0;
}
