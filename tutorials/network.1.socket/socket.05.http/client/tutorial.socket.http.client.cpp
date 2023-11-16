#include "cgdk/sdk10/net.socket.http.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

int main()
{
	// trace) 
	std::cout << "start client [tut.socket.05.http.client]..."sv << '\n';

	// 1) http requet 객체를 생성한다.
	auto phttp_request = make_object<net::http_request>();

	// 2) http request 내용을 설정한다.
	//phttp_request->set_request("https://www.naver.com"sv);
	//phttp_request->set_request("http://www.google.com"sv);
	//phttp_request->set_request("https://127.0.0.1"sv);
	//phttp_request->set_request("ws://127.0.0.1"sv);
	phttp_request->set_request("http://127.0.0.1"sv);

	// 3) http response 함수를 설정한다.
	phttp_request->set_function([](sMESSAGE_HTTP_RESPONSE& _response)
	{
		// 설명) chunked 응답일 경우 이 함수는 여러번 호출 될 수 있다.

		// - 성공 실패 여부를 출력한다.
		std::cout << " http response : "sv << _response.status_message << '\n';

		// - contents를 출력한다.
		for(const auto& iter: _response.contents)
			std::cout << ' ' << std::string_view(iter);

		// - ...
		std::cout << '\n';
	});

	// 4) http 접속 요청! (비동기 처리이므로 완료까지 대기하려면 wait()함수를 사용하면 된다.)
	phttp_request->request();

	// 5) ESC키를 누를 때까지 대기한다.
	while (_getch() != 27);

	// trace) 
	std::cout << "stop server [tut.socket.05.http.client]..."sv << '\n';

	// end) 종료
	return 0;
}
