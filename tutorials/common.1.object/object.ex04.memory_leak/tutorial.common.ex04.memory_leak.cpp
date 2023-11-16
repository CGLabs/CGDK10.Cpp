//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                     tutorials common.ex - memory keak                     *
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
// 1) CGDK header file
#include "cgdk/sdk10/system.object.h"

// 2) header files
#include <iostream>

// 3) namespace
using namespace CGDK;

// 4) DEBUG_NEW
#if defined(_DEBUG) && !defined(NDEBUG)
	#define new DEBUG_NEW
#endif


//-----------------------------------------------------------------------------
//
// tutorial common.ex04 - memory leak
//
//-----------------------------------------------------------------------------
class foo : virtual public Ireferenceable
{
public:
	~foo() {}

public:
	object_ptr<foo> ptr;
};

int main()
{
	// *1) memory leak이 출력되도록 설정한다.
#ifdef _WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// 2) 객체 생성
	auto a = make_object<foo>();
	auto b = make_object<foo>();

	// *3) 순환참조!! 이것 때문에 메모리 릭이 발생한다.
	a->ptr = b;
	b->ptr = a;

	// 설명) 출력되는 메모리 누수 정보가 소스와 연동되어 더블클릭하면 
	//       해당 객체를 생성한 소스의 위치를 바로 찾을 수 있다.
}
