#include "pch.h"

own_ptr<update::md5_caching> g_pmd5_caching;

int main()
{
	// trace) 
	std::cout << "start client [tut.update.01.simple_update.client]..."sv << '\n';

	// 1) md5 캐싱 파일을 생성하고 읽어 들인다.
	{
		// - caching 파일 객체를 생성한다.
		g_pmd5_caching = make_own<update::md5_caching>();

		// - md5 캐싱 파일을 읽어 들인다.
		g_pmd5_caching->start("destination/update_caching.info"sv);
	}

	// 2) socket 객체를 새성한다.
	auto psocket = make_own<socket_tcp>();

	// 3) socket의 최대 메시지 크기를 충분히 늘려준다.
	psocket->maximum_message_buffer_size(16 * 1024 * 1024); // 16Mbyte

	// 4) socket을 'localhost:20000'로 접속을 시도한다. (ip::address나 resolver로 설정이 가능하다.)
	psocket->start({ { net::ip::address_v4::loopback(), 31000 } });

	// 5) ESC키를 누를 때까지 대기한다.
	while (_getch() != 27);

	// trace) 
	std::cout << "stop client [tut.update.01.simple_update.client]..."sv << '\n';

	// end) 종료
	return 0;
}
