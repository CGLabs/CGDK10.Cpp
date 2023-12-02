#include "pch.h"

//own_ptr<group_socket> g_pgroup_socket;

int main()
{
	// 1) [콘솔 로거] 객체를 생성한다.
	auto plogger_console = make_own<logger_console>();

	// 2) [콘솔 로거] 객체를 초기화한다.
	plogger_console->initialize();

	// 3) [콘솔 로거] 객체를 등록한다.
	service::get_logger()->register_log_targetable(plogger_console);

	try
	{
		// 4) [서비스] 객체를 생성한다.
		g_pservice = make_own<service>();

		// 5) [서비스]를 '준비'한다.('시작' 요청은 [콘트롤 서버]에서 한다.)
		g_pservice->initialize();

		// 임시)
		g_pservice->start();

		// 6) 종료 될때까지 대기한다. (1초 단위로 ctrl-X키의 입력을 확인한다.)
		while (g_pservice->wait_destroy(1s) == false)
		{
			// check) ctrl-X를 입력하면 종료한다.
			if (_kbhit())
			{
				auto ch = _getch();

				if (ch == 24)
				{
					break;
				}
				else if (ch == 'A' || ch == 'a')
				{
					// - object status
					factory::manager::print_statistics();
				}
				else if (ch == 'S' || ch == 's')
				{
					// - executor/thread status
					executor::manager::print_statistics();
				}
				else if (ch == 'D' || ch == 'd')
				{
					// - executor/thread status
					factory::manager::print_statistics();
				}
			}
		}
	}
	catch (...)
	{
	}

	// 7) [서비스] 객체를 종료한다.
	g_pservice.destroy();

	// return) 
	return 0;
}
