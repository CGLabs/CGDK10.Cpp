#include "cgdk/sdk10/net.socket.http.h"
#include "../../define_message.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

// 
// 설명) SSL을 사용하지 않는 'http://'나 'ws://'는 80번 port가 기본포트이며
//      SSL을 사용하는 'https://'나 'wss://'는 443번 port가 기본 포트이다.
//      http와 websocket용 acceptor는 구분하지 않고 한번에 사용한다.
//      클라이언트가 websocket을 사용할 경우 websocket 메시지가 전달되며
//      그렇지 않을 경우 일반 http로 동작한다.
//
//  2. HTTP와 Websocket 구분하기
//     on_message에 sMESSAGE_HTTP_REQUEST에 전달되는 값으로 확인가능하다.
//      
//       _msg.protocol.type == eHTTP_PROTOCOL::WEBSOCKET_  => 웹소켓
//
//       _msg.protocol.type == eHTTP_PROTOCOL::HTTP_  => HTTP
//
//
//  3. Websocket로 전송받은 메시지 읽기
//     전송받은 메시지가 text형식인지 binary 형식인지는 _msg.method를 확인할 수 있다.
//
//      _msg.method == eHTTP_METHOD::TEXT_  => text 형식
//
//      _msg.method == eHTTP_METHOD::BINARY_  => binary 형식
//
//     전송되어온 메시지는 sMESSAGE_HTTP_REQUEST 구조체의 buf_message에 있다.
//
//
//  4. Websocket 메시지 전송하기
//     전달하고자 하는 메시지를 sWEBSOCKET_MESSAGE 구조체를  사용해 전달하면 된다ㅣ
//
//       send(make_shared_buffer(sWEBSOCKET_MESSAGE(std::string_view("test message")))); -> text 전송
//
//       send(make_shared_buffer(sWEBSOCKET_MESSAGE(temp_buffer)); -> binary 전송
// 
//       send(make_shared_buffer(sWEBSOCKET_MESSAGE(temp_buffer, eHTTP_METHOD::TEXT_)); -> buffer의 내용을 text로 인식해 전송
//
//

// 1) socket_web 클래스를 정의한다.
class socket_web : public net::socket::http_server
{
	virtual void		on_connect() override;
	virtual void		on_disconnect(uint64_t) override;
	virtual result_code	on_message(sMESSAGE_HTTP_REQUEST& _msg) override;
	virtual result_code	on_message(sMESSAGE_HTTP_WEBSOCKET& _msg) override;
};

int main()
{
	// trace) 
	std::cout << "start server [tut.socket.06.websocket.server]..."sv << '\n';

	// 1) 'socket_web'을 사용하는 "ws://"를 받는 acceptor 객체를 생성한다.
	auto pacceptor_ws = make_own<net::acceptor<socket_web>>();

	// 2) accept를 시작한다.
	//    (ws://의 기본 포트는 80번)
	pacceptor_ws->start();


	// 3) ssl context를 생성한다.
	//    - ssl을 사용하고자 할 경우 아래와 같이 ssl_conent를 생성 후 설정해서 사용해야 한다.
	//    - 인증서가 없거나 expire되었을 경우 신규 발급을 받는다.
	//    !주의) localhost에서 발급한 인증서로는 대부분의 웹브라우저에서 보안상 접속이 허용되지 않는다.
	//           따라서 internet explorer와 같은 구형 웹브라우저를 사용하거나 localhost 인증서를 허용하도록 브라우저 옵션을 변경해줘야 한다.
	auto pssl_context = make_object<crypt::ssl_context>("tutorial_server.crt"sv, "tutorial_server.key"sv);

	// 4) 'socket_web'을 사용하는 "wss://"를 받는 acceptor 객체를 생성한다.
	auto pacceptor_wss = make_own<net::acceptor<socket_web>>();

	// 5) accept를 시작한다.
	//    ("wss://"의 기본 포트는 443이다.)
	pacceptor_wss->start({{}, pssl_context });

	// 6) ESC키를 누를 때까지 대기한다.
	while(_getch() != 27);

	// trace) 
	std::cout << "stop server [tut.socket.06.websocket.server]..."sv << '\n';

	// end) 서버 종료
	return 0;
}


void socket_web::on_connect()
{
	std::cout << " @ connected"sv << '\n';

	send(make_shared_buffer(sWEBSOCKET_MESSAGE("okay~"sv)));
}

void socket_web::on_disconnect(uint64_t)
{
	std::cout << " @ disconnected"sv << '\n';
}

result_code socket_web::on_message(sMESSAGE_HTTP_REQUEST& _msg)
{
	// 설명) 일반적인 HTTP/HTTPS 프로토콜일 경우 여기가 호출된다.

	// 1) 전송되어어온 request를 출력한다.
	std::cout << " - protocol: " << to_string<char>(_msg.protocol) << " version: "sv << _msg.version << '\n';
	std::cout << " - method: " << to_string<char>(_msg.method) << '\n';
	std::cout << " - path: " << reinterpret_cast<const char*>(_msg.path.data()) << '\n';
	for (auto& iter : _msg.parameters)
	{
		std::cout << ' ' << iter.key << ": "sv << iter.value << '\n';
	}

	// 2) response를 작성한다.
	sMESSAGE_HTTP_RESPONSE msg_http_response;
	msg_http_response.version = _msg.version;
	msg_http_response.status_code = eHTTP_STATUS_CODE::OK_;
	msg_http_response.status_message = to_string<char>(msg_http_response.status_code);

	// 3) response 전송
	send(make_shared_buffer(msg_http_response));

	// return) 
	return eRESULT::DONE;
}

result_code socket_web::on_message(sMESSAGE_HTTP_WEBSOCKET& _msg)
{
	// 설명) websocket일 경우 여기가 호출된다.

	// check) TEXT일 경우만 진행...
	RETURN_IF(_msg.method != eHTTP_METHOD::TEXT_, eRESULT::BYPASS);

	// 1) 전송되어온 message를 얻는다.
	std::u8string_view str_message = _msg.buf_message;

	// trace)
	std::cout << ' ' << encode_string<char>(str_message) << '\n';

	// 2)  문자열을 전송한다.
	//     주의!) Web 문자열은 UTF-8로 변환되어서 전달되므로 그에 따른 변환이 필요로 한다.
	//     만약 UTF-8로 변환하지 않고 전송하고 싶을 때에는 그냥 shared_buffer로 전송하면 된다.
	send(make_shared_buffer(sWEBSOCKET_MESSAGE("테스트 메시지 전송"sv)));

	// 3) 일반 바이너리 데이터를 전송한다.
	//    전송할 데이터를 shared_buffer에 넣어서 전달한다.
	auto buf_binary = alloc_shared_buffer(1000);
	buf_binary.append<int>(100);
	buf_binary.append<int>(200);

	send(make_shared_buffer(sWEBSOCKET_MESSAGE(buf_binary)));

	// return) 
	return eRESULT::DONE;
}
