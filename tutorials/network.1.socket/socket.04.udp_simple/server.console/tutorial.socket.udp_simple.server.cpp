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
	//     - 화면에 출력하고 바로 echo 전송하도록 작성.
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override
	{
		// - 받은 데이터를 문자열로 
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
	std::cout << "start server [tut.socket.04.udp_simple.server]..."sv << '\n';

	// 2) udp socket을 생성한다.
	auto psocket = make_own<socket_udp>();

	// 3) 22500번 포트에 bind한다.
	psocket->start({{ net::ip::address_v4::any(), 22500 }});

	// 4) ESC키를 누를 때까지 대기한다.
	while (_getch() != 27);

	// trace) 
	std::cout << "stop server [tut.socket.04.udp_simple.server]..."sv << '\n';

	// end) 서버 종료
	return 0;
}
