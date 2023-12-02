//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                     tutorials common - object_pointer                     *
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


//-----------------------------------------------------------------------------
//
// step 1) CGDK::Ireferenceable & object_ptr<T> & make_object<T>
//
// std::shared_ptr와 같은 기능의 스마트 포인터를 위한 것.
// CGDK는 Ireferenceable을 상속받아 자체적임 참조계수를 가지도록 함.
// CGDK는 std의 다음과 거의 동일하다.
//
//  std::shared_ptr<T>  => CGDK::object_ptr<T> 
//  std::make_shared<T> => CGDK::make_object<T>
//
//  기본적인 동작방법은 std::함수와 거의 동일하다.
//
//-----------------------------------------------------------------------------

// *1) object_ptr<T>를 사용하기 위해서는 T에 해당하는 객체는 반드시
//    Ireferenceable을 상속받아야 한다.
class foo : virtual public Ireferenceable
{
public:
	foo& operator =(foo&&) { return *this; } // for warning
};

void tutorial_step_1()
{
	// *2) object_ptr<foo>는 std::shared_ptr<T>와 거의 동일한 클래스다.
	object_ptr<foo>	b;

	// *3) make_object<T>는 make_shared<T>와 동일하게 객체를 생성하는 함수다.
	object_ptr<foo>	a = make_object<foo>();

	// *4) auto를 사용해도 당연히 된다. (c는 object_ptr<foo>형 이다.)
	auto c = make_object<foo>();

	// *5) foo나 goo는 Irefenceable이 구현되지 않은 상태라 지역변수로 선언을 할 수 없다.
	//     이러면 d는 동적 객체가 아니므로 참조계수에 따라 소멸되지 않으며 지역변수로 동작한다.ㄴ
	// foo		d;	// error가 난다.
	OBJ<foo>	d;	// ok! OBJ<T>를 사용하면 된다.

	// 6) 이 블록이 끝나면 참조계수가 0이 되어 a와 b 객체는 자동 소멸될 것이다.
}
