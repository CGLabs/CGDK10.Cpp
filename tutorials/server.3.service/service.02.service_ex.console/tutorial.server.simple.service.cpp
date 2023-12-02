﻿//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                        tutorials service - simple                         *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************
// 1) include files
#include "include.h"

int main()
{
	// *1) console용 log 객체를 생성한다.
	auto plogger_console = make_own<logger_console>();

	// *2) logger를 초기화한다.
	plogger_console->initialize();

	// *3) console용 log 객체를 등록한다.
	service::get_logger()->register_log_targetable(plogger_console);

	// 4) service를 생성한다.
	g_pservice = make_own<service>();

	// 5) service를 시작한다.
	g_pservice->start();

	// 6) destroy될 때까지 대기한다.
	while (g_pservice->wait_destroy(1s) == false)
	{
		// check) ESC를 입력하면 종료한다.
		if (_kbhit() && _getch() == 0x1b)
		{
			break;;
		}
	}

	// 7) service를 닫는다. (own_ptr이므로 reset하는 것만으로 destroy가 호출된다.)
	g_pservice.reset();

	// return) 
	return 0;
}
