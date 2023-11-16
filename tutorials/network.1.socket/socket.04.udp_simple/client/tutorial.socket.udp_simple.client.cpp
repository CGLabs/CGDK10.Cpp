#include "cgdk/sdk10/net.socket.h"
#include "../../define_message.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

// 1) socket 클래스를 정의한다.
class socket_udp : public net::socket::udp
{
	// (v) 메시지를 수신했을 때 호출 되는 함수.
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override
	{
		auto str_recv = _msg.buf_message.front<std::string_view>();

		// - 화면에 문자열 출력
		std::cout << ' ' << str_recv << '\n';

		// - echo 전송
		send_to(_msg.buf_message, _msg.address);

		// return) 
		return eRESULT::BYPASS;
	}
};

int main()
{
	// trace) 
	std::cout << "start client [tut.socket.04.udp_simple.client]..."sv << '\n';

	// 2) 'socket_udp'을 사용하는 acceptor 객체를 생성한다.
	auto psocket = make_own<socket_udp>();

	// 3) udp socket을 시작한다. (port를 설정하지 않으면 아무 port에 bind한다.)
	psocket->start({{net::ip::udp::v4(), 0}});

	// 4) send udp message
	psocket->send_to(make_shared_buffer("test udp string"sv), { net::ip::make_address_v4({127,0,0,1}), 22500 });

	// 5) ESC키를 누를 때까지 대기한다.
	while (_getch() != 27);

	// trace) 
	std::cout << "stop server [tut.socket.04.udp_simple.client]..."sv << '\n';

	// end) 종료
	return 0;
}
