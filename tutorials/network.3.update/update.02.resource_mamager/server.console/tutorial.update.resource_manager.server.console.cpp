#include "cgdk/sdk10/net.update.h"
using namespace CGDK;

#include "../define_message.h"
#include "socket_update.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif


own_ptr<update::resource_manager> g_presource_manager;

int main()
{
	// ------------------------------------------------------------------
	// 1. update.resource_manager
	//    resource_manager에 update resource를 등록해 놓았다가.
	//    필요할 경우 UPDATE_RESOURCE_ID로 update resource를 찾아 sender에 
	//    등록해 사용할 수 있습니다.
	// 
	// 2. 동작 설명
	//    1) 서버는 resource_manager를 생성합니다.
	//    2) json파일인 "configure/update_server_setting.json"에서 생성할
	//       update resource 리스트를 읽어 해당 update resource를 생성합니다.
	//    3) 각 update resource는 고유의 id를 가지고 있습니다.
	//    4) 클라이언트가 접속해 업데이트를 요청합니다.
	//       이때 update를 할 update resource id를 서버에 전달합니다.
	//    5) 서버는 클라이언트에서 전달받은 update resource id로 update resource를
	//       resource manager로 부터 얻습니다.
	//    6) 해당 update resource를 성공적으로 찾았다면 update sender를 생성한 후
	//       찾은 update resource를 추가합니다.
	//    7) 추가적인 설정을 한 후 update sender를 start()해 업데이트를 시작합니다.
	//    8) 완료가 된 후 클라이언트로 부터 eMESSAGE::UPDATE::COMPLETE 메시지가 
	//       전달되어 오면 sender를 제거합니다.
	//    9) client가 접속을 종료해도 sender를 제거합니다.
	// 
	// ------------------------------------------------------------------

	// trace) hide cursor
	std::cout << "\x1b[?25l"sv;

	try
	{
		// trace) 
		std::cout << "load resource..."sv << std::endl;

		// 1) resource manager
		g_presource_manager = make_own<update::resource_manager>();

		// declare)
		context cotext_initialize("configure/update_server_setting.json"sv);

		// 2) json 파일로 update resource 정보를 읽어들여 한번에 생성합니다.
		g_presource_manager->initialize(cotext_initialize);

		// trace) 
		std::cout << "start server [tut.update.01.tcp_simple.server]..."sv << std::endl;

		// 3) acceptor 객체를 생성한다.
		auto pacceptor = make_own<net::acceptor<socket_update>>();

		// 4) acceptor를 시작한다.(20000번 포트에서 listen을 시작한다.)
		pacceptor->start({ { net::ip::make_address("any"sv), 31000 } });

		// 5) ESC키를 누를 때까지 대기한다.
		while (_getch() != 27);
	}
	catch (...)
	{
		// trace) 
		std::cout << "fail to starting!!!"sv << std::endl;
	}

	// trace) 
	std::cout << "stop server [tut.update.01.tcp_simple.server]..."sv << std::endl;

	// trace) show cursor
	std::cout << "\x1b[?25h"sv;

	// end) 서버 종료
	return 0;
}
