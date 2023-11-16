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
// step 1) object_ptr<T>의 Is-A 관계
//
//
//-----------------------------------------------------------------------------

// *1) object_ptr<T>를 사용하기 위해서는 T에 해당하는 객체는 반드시
//    Ireferenceable을 상속받아야 한다.
class bar : virtual public Ireferenceable
{
};

class kee : public bar
{
};

// *2-A) bar의 포인터를 인자로 받는 함수
void function(bar* _hoo)
{
	// * 포인터만 넘겨와도 object_ptr<T>에 대입이 가능하다.
	//   std::shared_ptr<T>의 경우 반드시 std::shared_ptr<T>&로 인자를 넘겨야 하지만
	//   object_ptr<T>는 그럴 필요 없다.
	object_ptr<bar>	x = _hoo;
}

void tutorial_step_2()
{
	// *3) kee형 객체 a
	object_ptr<kee>	a = make_object<kee>();

	// *2-B) 함수에 파라미터로 넘길 경우
	function(a);

	// declare) bar형 b~
	object_ptr<bar>	b;

	// *3) bar는 kee와 Is-A관계이므로 object_ptr<bar>형 변수 b에 a도 넣을 수 있다.
	b = a;
}
