#include "cgdk/sdk10/net.socket.h"
#include "../../define_message.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

// 1) socket 클래스를 정의한다.
class socket_tcp : public net::socket::tcp_client<>
{
	// (v) 접속 시 호출되는 함수
	virtual void on_connect() override
	{
		std::cout << "on_connect>> connected"sv << '\n';
	}

	// (v) 접속 종료 시 호출되는 함수
	virtual void on_disconnect(uint64_t) override
	{
		std::cout << "on_disconnect>> disconnected"sv << '\n';
	}

	// (v) 메시지를 수신했을 때 호출 되는 함수.
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override
	{
		// 1) message head를 읽습니다.
		auto msg_header = _msg.buf_message.front<sMESSAGE_HEAD>();

		// 2) message 종류에 따른 처리를 한다.
		switch (msg_header.message_type)
		{
		case	eMESSAGE_TYPE::ENTER_MEMBER:
				std::cout << "'on_message>> member entered"sv << '\n';
				break;

		case	eMESSAGE_TYPE::LEAVE_MEMBER:
				std::cout << "'on_message>> member leaved"sv << '\n';
				break;
		default:
				std::cout << "on_message>> undefined message"sv << '\n';
				break;
		}

		return eRESULT::DONE;
	}
};

int main()
{
	// 2) 'socket_tcp'을 사용하는 acceptor 객체를 생성한다.
	auto psocket = make_own<socket_tcp>();

	// 3) 20000번 포트에서 접속을 시도한다.
	psocket->start({{ net::ip::address_v4::loopback(), 20000 }});

	// 5) ESC를 눌러 종료하기를 기다린다. / wait for exit pressing ESC key
	while (_getch() != 27);

	// end) 서버 종료
	return 0;
}
