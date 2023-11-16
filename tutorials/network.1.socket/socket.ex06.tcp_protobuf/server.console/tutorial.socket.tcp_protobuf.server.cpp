// 주의) protobuf header 파일은 반드시 CGDK10 헤더파일보다 앞에 와야 한다.
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
class socket_tcp : public net::socket::tcp<>
{
	// (v) 접속 시 호출되는 함수
	virtual void on_connect() override;

	// (v) 접속 종료 시 호출되는 함수
	virtual void on_disconnect(uint64_t) override;

	// (v) 메시지를 수신했을 때 호출 되는 함수.
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override;
			void on_message_SEND_A(sMESSAGE_NETWORK& _msg);
			void on_message_SEND_B(sMESSAGE_NETWORK& _msg);
			void on_message_SEND_C(sMESSAGE_NETWORK& _msg);
};

void socket_tcp::on_connect()
{
	// trace)
	std::cout << " @ connected"sv << '\n';
}

void socket_tcp::on_disconnect(uint64_t)
{
	std::cout << " @ disconnected"sv << '\n';
}

result_code socket_tcp::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) 메시지 타입을 얻는다.
	auto message_type = _msg.buf_message.front<eMESSAGE_TYPE>(4);

	// 2) 메시지 종류에 따라 처리 함수를 호출한닫.
	switch (message_type)
	{
	case	eMESSAGE_TYPE::SEND_A:
			on_message_SEND_A(_msg);
			break;

	case	eMESSAGE_TYPE::SEND_B:
			on_message_SEND_B(_msg);
			break;

	case	eMESSAGE_TYPE::SEND_C:
			on_message_SEND_C(_msg);
			break;

	default:
			break;
	}

	// return) 
	return eRESULT::DONE;
}

void socket_tcp::on_message_SEND_A(sMESSAGE_NETWORK& _msg)
{
	// ----------------------------------------------
	//
	//	message SendA
	//	{
	//		int32				TestValue	 = 2;
	//	}
	//
	// ----------------------------------------------

	// 1) offset 8Byte를 주어 MESSAGEE_SEND_A를 읽어낸다.
	auto message = _msg.buf_message.front<tutorial::SendA>(8);

	// 2) 읽은 값을 출력한닫.
	std::cout << " 'eMESSAGE_TYPE::SEND_A' received"sv << '\n';
	std::cout << "   temp.TestValue: "sv << message.testvalue() << '\n';

	// 3) echo 전송한다.(echo 전송은 받은 메시지를 그대로 전송하면 된다.)
	send(_msg.buf_message);
}

void socket_tcp::on_message_SEND_B(sMESSAGE_NETWORK& _msg)
{
	// ----------------------------------------------
	//
	//	message SendB
	//	{
	//		int32				TestValue1	 = 2;
	//		uint32				TestValue2	 = 3;
	//		float				TestValue3	 = 4;
	//	}
	//
	// ----------------------------------------------

	// 1) offset 8Byte를 주어 MESSAGEE_SEND_B를 읽어낸다.
	auto message = _msg.buf_message.front<tutorial::SendB>(8);

	// 2) 읽은 값을 출력한닫.
	std::cout << " 'eMESSAGE_TYPE::SEND_B' received"sv << '\n';
	std::cout << "   temp.TestValue1: "sv << message.testvalue1() << '\n';
	std::cout << "   temp.TestValue2: "sv << message.testvalue2() << '\n';
	std::cout << "   temp.TestValue3: "sv << message.testvalue3() << '\n';

	// 3) echo 전송한다.(echo 전송은 받은 메시지를 그대로 전송하면 된다.)
	send(_msg.buf_message);
}

void socket_tcp::on_message_SEND_C(sMESSAGE_NETWORK& _msg)
{
	// ----------------------------------------------
	//
	//	message SendC
	//	{
	//		int32				TestValue1	 = 2;
	//		string				TestValue2	 = 3;
	//		repeated int32		TestValue3	 = 4;
	//	}
	//
	// ----------------------------------------------

	// 1) offset 8Byte를 주어 MESSAGEE_SEND_C를 읽어낸다.
	auto message = _msg.buf_message.front<tutorial::SendC>(8);

	// 2) 읽은 값을 출력한닫.
	std::cout << " 'eMESSAGE_TYPE::SEND_C' received"sv << '\n';
	std::cout << "   temp.TestValue1: "sv << message.testvalue1() << '\n';
	std::cout << "   temp.TestValue2: "sv << message.testvalue2() << '\n';
	std::cout << "   temp.TestValue3: "sv;
	for(auto& iter: message.testvalue3())
		std::cout << iter << " "sv;
	std::cout << '\n';

	// 3) echo 전송한다.(echo 전송은 받은 메시지를 그대로 전송하면 된다.)
	send(_msg.buf_message);
}

int main()
{
	// trace) 
	std::cout << "start server [tut.socket.02.tcp_protobuf.server]..."sv << '\n';

	// 2) 'socket_tcp'을 사용하는 acceptor 객체를 생성한다.
	auto pacceptor = make_own<net::acceptor<socket_tcp>>();

	// 3) 20000번 포트에서 listen을 시작한다. (기본설정은 IPv4과 IPv6 동시 지원이다.)
	pacceptor->start({{net::ip::tcp::v6(), 20000}});

	// - ESC키를 누를 때까지 대기한다.
	while(_getch() != 27);

	// trace) 
	std::cout << "stop server [tut.socket.02.tcp_send_receive.server]..."sv << '\n';

	// end) 서버 종료
	return 0;
}

