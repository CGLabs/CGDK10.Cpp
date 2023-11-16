#include "cgdk/sdk10/net.socket.http.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

// 1) socket_web_client 클래스를 정의한다.
class socket_web_client : public net::socket::http_client
{
	virtual void on_connect() override
	{
		std::cout << " @ connected"sv << '\n';

		send(" okay~"sv);
	}

	virtual void on_fail_connect(uint64_t) override
	{
		std::cout << " @ fail to connect"sv << '\n';
	}

	virtual void on_disconnect(uint64_t) override
	{
		std::cout << " @ disconnected"sv << '\n';
	}

	virtual result_code on_message(sMESSAGE_HTTP_WEBSOCKET& _msg) override
	{
		// 
		// 설명) on_meessage는 일반적인 http일수도 있고 websocket일수도 있다.
		//      따라서 _msg.method를 확인으로 알수 있다.
		//
		//      _msg.method값이 eHTTP_METHOD::TEXT_ 혹은 eHTTP_METHOD::BINARY_이면
		//      websocket이다.
		// 
		
		// check) TEXT 형식일 경우만 진행...
		RETURN_IF(_msg.method != eHTTP_METHOD::TEXT_, eRESULT::BYPASS);

		// - text형식이므로 전송받은 버퍼를 std::string_view형으로 변환한다.
		//   주의!) 1.다중 라인일 경우 '\r\n'을 터미널 문자로 사용하므로 extract_web을 사용해 읽어내면 된다.
		//   주의!) 2. TEXT형은 무조건 UTF-8형 문자열이다! 따라서 변환해서 출력해야 한다.
		std::u8string_view str_message = _msg.buf_message;

		// trace) mbcs 문자열로 변환해서 출력한다.
		std::cout << ' ' << encode_string<char>(str_message) << '\n';

		// return)
		return eRESULT::BYPASS;
	}
};

int main()
{
	// trace) 
	std::cout << "start client [tut.socket.06.websocket.client]..."sv << '\n';

	// 1) 'socket_tcp'을 사용하는 acceptor 객체를 생성한다.
	auto psocket = make_own<socket_web_client>();

	// 2) ws로 접속을 시도한다.
	psocket->connect("wss://127.0.0.1");

	// 3) ESC키를 누를 때까지 대기한다.
	while (_getch() != 27);

	// trace) 
	std::cout << "stop server [tut.socket.06.websocket.client]..."sv << '\n';

	// end) 종료
	return 0;
}
