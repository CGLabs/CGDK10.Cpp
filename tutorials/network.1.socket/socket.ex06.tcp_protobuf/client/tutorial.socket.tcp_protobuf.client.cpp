// 주의) protobuf header 파일은 반ㄷ드시 CGDK10 헤더파일보다 앞에 와야 한다.
#if defined(_MSC_VER)
	#pragma warning(disable:4251)
	#pragma warning(disable:4127)
	#pragma warning(disable:5054)
#endif

#include <iostream>
#include "../common/messages.pb.h"
#if defined(_MSC_VER)
	#pragma warning(default:4251)
	#pragma warning(default:4127)
	#pragma warning(default:5054)

	#include <conio.h>
#endif

#include "cgdk/sdk10/net.socket.h"
#include "../../define_message.h"


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

		case	eMESSAGE_TYPE::SEND_C:
				std::cout << " 'eMESSAGE_TYPE::SEND_C' received"sv << '\n';
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
	std::cout << " 'B' key: send message 'eMESSAGE_TYPE::SEND_B'"sv << '\n';
	std::cout << " 'C' key: send message 'eMESSAGE_TYPE::SEND_C'"sv << '\n';
	std::cout << " ESC key: terminate"sv << '\n';

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
			// ----------------------------------------------
			// - A키 누르면 Message B를 전송한다.
			// ----------------------------------------------
			else if(ch=='a' || ch=='A')
			{
				// - protobuf message
				tutorial::SendA	message;
				message.set_testvalue(100);

				// - write protobuf messagee to buffer
				auto buf_send = alloc_shared_buffer(8 + message.ByteSizeLong());
				buf_send.append<uint32_t>();
				buf_send.append<eMESSAGE_TYPE>(eMESSAGE_TYPE::SEND_A);
				buf_send.append(message);
				buf_send.front<uint32_t>() = buf_send.size<uint32_t>();

				// - send buffer
				psocket->send(buf_send);
			}
			// ----------------------------------------------
			// - B키 누르면 Message B를 전송한다.
			// ----------------------------------------------
			else if(ch=='b' || ch=='B')
			{
				// - protobuf message
				tutorial::SendB	message;
				message.set_testvalue1(100);
				message.set_testvalue2(100);
				message.set_testvalue3(100);

				// - write protobuf messagee to buffer
				auto buf_send = alloc_shared_buffer(8 + message.ByteSizeLong());
				buf_send.append<uint32_t>();
				buf_send.append<eMESSAGE_TYPE>(eMESSAGE_TYPE::SEND_B);
				buf_send.append(message);
				buf_send.front<uint32_t>() = buf_send.size<uint32_t>();

				// - send buffer
				psocket->send(buf_send);
			}
			// ----------------------------------------------
			// - C키 누르면 Message B를 전송한다.
			// ----------------------------------------------
			else if(ch=='c' || ch=='C')
			{
				// - protobuf message
				tutorial::SendC	message;
				message.set_testvalue1(100);
				message.set_testvalue2("test_string"s);
				message.add_testvalue3(10);
				message.add_testvalue3(20);
				message.add_testvalue3(30);
				message.add_testvalue3(40);
				message.add_testvalue3(50);

				// - write protobuf messagee to buffer
				auto buf_send = alloc_shared_buffer(8 + message.ByteSizeLong());
				buf_send.append<uint32_t>();
				buf_send.append<eMESSAGE_TYPE>(eMESSAGE_TYPE::SEND_C);
				buf_send.append(message);
				buf_send.front<uint32_t>() = buf_send.size<uint32_t>();

				// - send buffer
				psocket->send(buf_send);
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
