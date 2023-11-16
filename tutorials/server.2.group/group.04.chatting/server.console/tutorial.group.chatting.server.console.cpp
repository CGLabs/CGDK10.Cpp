#include "pch.h"


int main()
{
	// trace) 
	std::cout << "CGCII tutorial.group.server 04..."sv << std::endl;

	// 1) 대기실 group을 만든다.
	g_pgroup_immigration = make_own<group_immigration>();

	// 2) group에 입장 가능하게 설정한다 / enable entering of group object
	g_pgroup_immigration->enable_member_enter();

	// 3) Acceptor 객체를 생성한다 / create acceptor object
	g_pacceptor = make_own<CGDK::net::acceptor<socket_user>>();

	// 4) 20000번 포트에 Listen을 시작한다 / start listening on 20000 port
	g_pacceptor->start({{ CGDK::net::ip::tcp::v6(), 20000 }});

	// 5) ESC를 눌러 종료하기를 기다린다. / wait for exit pressing ESC key
	while(_getch() != 27);

	// 6) Acceptor를 닫는다 / close acceptor
	g_pacceptor->stop();

	return 0;
}
