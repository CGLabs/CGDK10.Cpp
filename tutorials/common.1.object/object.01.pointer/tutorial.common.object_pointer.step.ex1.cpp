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

// ------------------------------------------------------------------
//
// ex) pool의 부가적인 기능들
// 
// 1) factory::pool_object는 객체들을 미리 생성해 놓는 prepare()함수나 
//    저장된 여분 객체를 소멸시키는 shrink()와 같은 부수적 함수들이 있다.
// 2) 기타 pool의 각종 통계에 관련된 정보들도 얻을 수 있다.
//
// ------------------------------------------------------------------
// definition) 
class koo : public Npoolable<koo>
{
public:
			koo() 		{ std::cout << "'koo' created!"sv << std::endl; }
	virtual	~koo()		{ std::cout << "'koo' destroyed"sv << std::endl; }

	void	on_alloc()	{ std::cout << "'koo' allocated"sv << std::endl; }
	void	on_free()	{ std::cout << "'koo' freed"sv << std::endl; }
};

void tutorial_step_ex1()
{
	// 1. prepare하기.
	//
	//    1) 위에 예제에서 pool을 제일처럼 만들었을 때는 해당 객체가 
	//       하나도 할당되어 있지 않는다.
	//
	//    2) 성능의 향상을 위해 생성 직후 생성과 할당해제를 하지 않더라도 
	//       미리 일정수의 재고 객체를 미리 만들어 쌓아두기 위해 prepare() 
	//       함수를 사용할 수 있다.
	//
	//    3) prepare()함수는 넘겨진 갯수만큼 추가로 재고 객체를 확보한다.
	//       만약 숫자보다 재고량이 많다면 특별히 더 할당하지 않는다.
	//
	koo::get_factory()->prepare(100);

	// 설명) prepare(100)을 하게 되면 지금 pool안에는 할당이 안된 객체가
	//       100개가 마련되어 있다. 따라서 100개이상 연속적으로 alloc_object
	//       하기전에는 새로 객체가 새로 할당되는 일은 없을 것이다.
	//    
	//       일반적으로 동작 중 사용되는 객체의 수가 일정하다면 사전에
	//       prepare()함수를 통해 미리 객체를 만들어 놓은 다음 동작을
	//       시킨다면 동작 초기 많은 성능향상을 꽤할 수 있다.

	// 2. shrink하기.
	//
	//    1) Pool을 사용할 경우 객체를 한꺼번에 할당을 많이 했다가 해제될 
	//       경우 너무 많은 여분의 객체를 보관하고 있을 수 있다. 이는 과도한
	//       메모리를 사용하는 원인이 될수 있다.
	//
	//    2) 이때 인위적으로 보관되어 있는 여분 객체를 delete하는 것이 
	//       shrink()함수이다.
	//
	//    참고) 따로 shrink()를 하지 않아도 내부적으로 적절한 여분 량을 계산
	//          하여 필요 이상이 저장될 경우 delete하는 처리과정을 가지고 있다.
	//          따라서 일반적인 경우 shrink()함수를 호출할 일은 없다.
	//
	koo::get_factory()->shrink(100);

	// 설명) shrink(100)을 하게 저장되어 있는 여분의 객체 100개를 할당해제한다.
}
