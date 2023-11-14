#include "cgdk/sdk10/server.web.h"

#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

int main()
{
	// 1) 웹 acceptor를 생성한다./ create webserver
	auto pacceptor_web = make_own<net::acceptor_web_server<>>();

	// 2) 웹 서버용 구성물을 생성한다./ create web component
	auto pweb_entity = make_object<server::web::entity::folder>("test_web"sv);

	// 3) 웹 구성 요소를 설정한다./ add web component
	pacceptor_web->set_web_entity(pweb_entity);

	// 4) 웹서버를 시작한다./ start webserver
	pacceptor_web->start();

	// 5) ESC를 눌러 종료하기를 기다린다. / waiting ESC key and exit
	while (_getch() != 27);

	// return)
	return 0;
}
