//*****************************************************************************
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

// 2)... 
int main()
{
	// 1) service를 생성한다.
	g_pservice = make_own<service>();

	// 2) service를 시작한다.
	g_pservice->start();

	// 3) ESC Key를 누를 때까지 
	while (_getch() != 0x1b);

	// 4) service를 닫는다. (own_ptr이므로 reset하는 것만으로 destroy가 호출된다.)
	g_pservice.reset();

	// return) 
	return 0;
}
