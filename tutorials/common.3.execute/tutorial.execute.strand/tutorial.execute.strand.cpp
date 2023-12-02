//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                   tutorials common - scheduled execute                    *
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
// 1) standard header file
#if defined(_WIN32)
	#include <conio.h>
#endif

// 2) CGDK header file
#include "cgdk/sdk10/system.object.h"

// 3) header files
#include <iostream>

// 4) namespace
using namespace CGDK;


//-----------------------------------------------------------------------------
//
// tutorial.05.strand
//
//
//-----------------------------------------------------------------------------

int main()
{
	// ------------------------------------------------------------------
	//  설명)
	// 
	//  일반적인 executor를 사용해 비동기 처리 요청을 하게 되면 
	//  다중 쓰레드에서 동시에 처리가 될 수가 있다.
	//  따라서 thread safe 처리를 위해 lock 처리를 해야 하는 경우가 많으며
	//  제대로 하지 않으면 심각한 오류를 발생시킬 수가 있다.
	// 
	//  executor::strand를 사용해 비동기  처리를 하게 되면 다중 쓰레드를
	//  사용해서 처리가 되지만 순서대로 처리가 된다.
	//  따라서 thread safe 처리가 비교적 수월해지며 lock의 사용을 최소화할 수 있다.
	//  
	// ------------------------------------------------------------------

	// ------------------------------------------------------------------
	// 1. system_executor에서 비동기 실행했을 경우
	//    - system_executor의 경우 동시에 처리가 될수도 있으며 처리 순서도 보장되지 않는다.
	//    - 따라서 post로 요청한 출력이 마구 섞여서 출력된다.
	// ------------------------------------------------------------------
	{
		std::cout << ">> executor with no strand " << std::endl;

		// 1) post 하기
		system_executor::post(make_executable([] {
			for(int i=0;i<4;++i)
				std::cout << "test1" << std::endl;
			}));

		system_executor::post(make_executable([] {
			for (int i = 0; i < 4; ++i)
				std::cout << "test2" << std::endl;
			}));

		system_executor::post(make_executable([] {
			for (int i = 0; i < 4; ++i)
				std::cout << "test3" << std::endl;
			}));

		system_executor::post(make_executable([] {
			for (int i = 0; i < 4; ++i)
				std::cout << "test4" << std::endl;
			}));

		// 2) ESC 키를 입력할 때까지 기다린다.
		_getch();
	}

	// ------------------------------------------------------------------
	// 2. strand를 사용해서 비동기 실행을 할 경우
	//    - post를 요청한 순서대로 실행되는 것을 보장해 준다.
	//      또 동시에 실행되지도 않는 것도 보장해 준다.
	//    - 따라서 post로 요청한 출력이 차례대로 출력된다.
	// ------------------------------------------------------------------
	{
		std::cout << ">> executor with strand" << std::endl;

		// 1) executor.strand를 만든다.
		auto pexecutor_strand = make_own<executor::strand>();

		// 2) executor.strand 시작
		pexecutor_strand->start();

		// 3) post 하기
		pexecutor_strand->post(make_executable([] {
			for (int i = 0; i < 4; ++i)
				std::cout << "test1" << std::endl;
			}));

		pexecutor_strand->post(make_executable([] {
			for (int i = 0; i < 4; ++i)
				std::cout << "test2" << std::endl;
			}));

		pexecutor_strand->post(make_executable([] {
			for (int i = 0; i < 4; ++i)
				std::cout << "test3" << std::endl;
			}));

		pexecutor_strand->post(make_executable([] {
			for (int i = 0; i < 4; ++i)
				std::cout << "test4" << std::endl;
			}));

		// 3) ESC 키를 입력할 때까지 기다린다.
		_getch();
	}

	// return)
	return	0;
}
