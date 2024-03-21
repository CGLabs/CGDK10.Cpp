#include "cgdk/sdk10/net.socket.http.h"
#include "../../define_message.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

// 1) socket_web 클래스를 정의한다.
class socket_web : public net::socket::http_server
{
	// (v) 메시지를 수신했을 때 호출 되는 함수.
	virtual result_code on_message(sMESSAGE_HTTP_REQUEST& _msg) override;
};

int main()
{
	// trace) 
	std::cout << "start server [tut.socket.05.http.server]..."sv << '\n';

	// 2) 'socket_web'을 사용하는 acceptor 객체를 생성한다.
	auto pacceptor = make_own<net::acceptor<socket_web>>();

	// 3) 20000번 포트에서 listen을 시작한다. (기본설정은 IPv4과 IPv6 동시 지원이다.)
	pacceptor->start({ {{net::ip::tcp::v6(), 10000}}, nullptr });

	// 4) ESC키를 누를 때까지 대기한다.
	while(_getch() != 27);

	// trace) 
	std::cout << "stop server [tut.socket.05.http.server]..."sv << '\n';

	// end) 서버 종료
	return 0;
}

result_code socket_web::on_message(sMESSAGE_HTTP_REQUEST& _msg)
{
	// 1) 전송받은 요청 메시지의 헤더 정보를 출력한다.
	std::cout << " - protocol: "sv << to_string<char>(_msg.protocol) << " version: "sv << _msg.version_major() << "."sv << _msg.version_minor() << '\n';
	std::cout << " - method: "sv << to_string<char>(_msg.method) << '\n';
	std::cout << " - path: "sv << reinterpret_cast<const char*>(_msg.path.data()) << '\n';
	for (auto& iter : _msg.parameters)
	{
		std::cout << ' ' << iter.key << ": "sv << iter.value << '\n';
	}

	// 2) 응답 메시지를 작성해 전송한다.
	sMESSAGE_HTTP_RESPONSE msg_http_response;
	msg_http_response.version		 = _msg.version;
	msg_http_response.status_code	 = eHTTP_STATUS_CODE::OK_;
	msg_http_response.status_message = to_string<char>(msg_http_response.status_code);
	msg_http_response.headers.push_back({ "Access-Control-Allow_Origin"sv, "www.cgcii.co.kr"sv });

	// 설명) _msg.path에 따라 다른 응답을 하도록 작성한다.
	//       _msg.path는 브라우즈(클라이언트)에서 url에 입력한  문자열 중 접속 주소 이후 '/' 부터 값이다.
	//
	//          "http://127.0.0.1/abcd"  => _msg.path = "/abcd"
	//          "http://127.0.0.1/xyze/sss/bcdd"  => _msg.path = "/xyze/sss/bcdd"
	//

	// case) "http://127.0.0.1/a" 일 경우
#if defined(_WIN32)
	if(_msg.path == u8"/a") // 
#else
	if (_msg.path == reinterpret_cast<const char8_t*>("/a")) // 
#endif
	{
		msg_http_response.contents.push_back(make_shared_buffer(text("<html><body><h1>welcone</h1></body></html>\r\n"sv)));
	}
	// case) "http://127.0.0.1/b" 일 경우
#if defined(_WIN32)
	else if(_msg.path == u8"/b")
#else
	else if (_msg.path == reinterpret_cast<const char8_t*>("/b"))
#endif
	{
		msg_http_response.contents.push_back(make_shared_buffer(text("<html><body><h1>nice to meet you CGCII</h1></body></html>\r\n"sv)));
	}
	// case) 기타
	else
	{
		msg_http_response.contents.push_back(make_shared_buffer(text("<html><body><h1>hellow CGCII</h1></body></html>\r\n"sv)));
	}

	this->send(make_shared_buffer(msg_http_response));

	// return) 
	return eRESULT::DONE;
}
