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

		// return) 
		return eRESULT::BYPASS;
	}
};

int main()
{
	// trace) 
	std::cout << "start client [tut.socket.01.tcp_simple.client]..."sv << '\n';

	// ---------------------------------------------------------------------
	// 1A. 접속시도의 정석적 방법
	//    - client socket에 start()함수를 호출하여 접속시도를 할수 있다.
	//    - 이때 가장 정석적인 전달 구조체인 START_PARAMETER를 사용하는 방법이다.
	// 	   
	//      struct START_PARAMETER
	//      {
	//      	net::ip::tcp::endpoint remote_endpoint;
	//      	net::ip::tcp::endpoint endpoint_bind;
	//      };
	// 
	// 	    -> remote_endpoint는 접속할 주소다. address와 port를 몯두 정확히 기입해야 한다.
	//      -> endpoint_bind는 현 host에서 bind할 주소를 의미한다. 일반적으로 설정할 필요 없다.
	// 	       설정하지 않으면 현 host의 모든 네트워크 카드에 bind되며 포트는 자동 설정된다.
	// 	    
	// ---------------------------------------------------------------------
	// 1) 접속을 시도할 'socket_tcp_client' 소켓 객체를 생성한다.
	auto psocket = make_own<socket_tcp_client>();

	// 2) 20000번 포트에서 접속을 시도한다. (ip::address나 resolver로 설정이 가능하다.)
	psocket->start({{ net::ip::address_v4::loopback(), 20000 }});

	// ---------------------------------------------------------------------
	// 1B. START_PARAMETER를 사용해 정식적으로 설정하기
	//     - START_PARAMETER는 remote_endpoint뿐만 아니라
	//       bind_endpoint까지 지정이 가능합니다.
	// ---------------------------------------------------------------------
	//// declare) START_PARAMETER를 설정한다.
	//socket_tcp_client::START_PARAMETER parameter;

	//// 1) START_PARAMETER에서 remote_endpoint만 설정해주면 된다.
	//parameter.remote_endpoint.address(net::ip::address_v4::loopback()); // loopback = localhost = 127.0.0.1
	//parameter.remote_endpoint.port(20000);

	//// 3) parameter를 사용해서 접속시도한다.
	//psocket->start(parameter);

	// ---------------------------------------------------------------------
	// 1C. C++ aggregrations을 사용해 간단히 접속하기.
	//    - 구조체를 일일이 선언할 필요 없이 중괄호({})만으로 묶어서 간단히
	//      설정이 가능핟다.
	// 	   - CGCII의 net::address는 기본적으로 C++ 표준안인 Network.TS를
	// 	     따르고 있습니다. 
	// 	     이는 차기 C++의 network 차기 표준의 유력한 안으로 boost::asio와
	// 	     거의 흡사한 규정입니다.
	// ---------------------------------------------------------------------
	// 1) ex1. 더 간편하게 접속주소 설정하기
	// 	 - aggregration 초기화를 통해 간단히 초기화가 가능합니다.
	//psocket->start({{ net::ip::address_v4::loopback(), 20000 }});

	// ---------------------------------------------------------------------
	// 1D. ip숫자 직접 집어넣기
	// ---------------------------------------------------------------------
	// 1) ex1. 간단히 v4 혹은 v6인지만 결정한후 숫자를 직접 입력해주면 된다.
	// 	 
	//psocket->start({{net::ip::address_v4({127,0,0,1}), 20000 }});

	// ---------------------------------------------------------------------
	// 1E. 문자열로 된 주소로 접속하기.
	//    - ip를 문자열로 표현 경우(도메인 네임이 아닌 진짜 ip)
	//      make_address를 사용해 간단히 접속이 가능합니다.
	// ---------------------------------------------------------------------
	//psocket->start({ { net::ip::make_address_v4("127.0.0.1"), 20000} });

	// ---------------------------------------------------------------------
	// 1F. 도메인 네임으로 접속하기
	//    - 도메인 네임으로 접속하기 위해서는 도메인 네임으로 ip을 얻는
	//      과정이다. 
	// 	  - resolve를 통해 이것을 구현할 수 있다.
	// ---------------------------------------------------------------------
	// 1) domain으로 접속하기 위해서는 resolver를 사용해야 합니다.
	//psocket->start({ net::ip::tcp::resolver().resolve("localhost", "20000")});
	//psocket->start({ net::ip::tcp::resolver().resolve("127.0.0.1", "20000")});

	// comment)
	std::cout << " 'A' key: send message 'eMESSAGE_TYPE::SEND_A'"sv << '\n';
	std::cout << " 'B' key: send message 'eMESSAGE_TYPE::SEND_A'"sv << '\n';
	std::cout << " 'ESC' key: terminate"sv << '\n';

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
			// - A키 누르면 Message A를 전송한다.
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

				// - set message length (가변길이 메시지는 반드시 메시지 내용을 다 작성한 후에 길이를 계산해 써넣어야 한다.)
				message.size = get_size_of<uint32_t>(message);

				// - send
				psocket->send(make_shared_buffer(message));
			}
			// - C키 누르면 접속을 종료한다.
			else if (ch == 'c' || ch == 'C')
			{
				psocket->disconnect();
			}
		}

		// - 1ms 슬립한다. (CPU를 너무 많이 먹으므로...)
		std::this_thread::sleep_for(1ms);
	}

	// 5) socket을 close한다.
	psocket->closesocket();

	// trace) 
	std::cout << "stop client [tut.socket.01.tcp_simple.client]..."sv << '\n';

	// end) 종료
	return 0;
}
