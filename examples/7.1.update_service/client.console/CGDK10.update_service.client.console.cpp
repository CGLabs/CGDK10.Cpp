#include "pch.h"


own_ptr<update::md5_caching> g_pmd5_caching;

int main()
{
	// trace) 
	std::cout << "start client [tut.update.01.simple_update.client]..."sv << '\n';

	g_pmd5_caching = make_own<update::md5_caching>();

	g_pmd5_caching->start("test_caching.cgx"sv);

	// 1) 접속을 시도할 'socket_tcp' 소켓 객체를 생성한다.
	auto psocket = make_own<socket_tcp>();

	// 2) 최대 메시지 크기를 늘려준다.
	psocket->maximum_message_buffer_size(16 * 1024 * 1024); // 16Mbyte

	// 2) 20000번 포트에서 접속을 시도한다. (ip::address나 resolver로 설정이 가능하다.)
	psocket->start({ { net::ip::address_v4::loopback(), 31000 } });

	// 3) ESC키를 누를 때까지 대기한다.
	while (_getch() != 27);

	// trace) 
	std::cout << "stop client [tut.update.01.simple_update.client]..."sv << '\n';

	// end) 종료
	return 0;
}
