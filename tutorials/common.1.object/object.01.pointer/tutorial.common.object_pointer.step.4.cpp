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
// step 3) CGDK::own_ptr<T> & CGDK::make_own<T>
//
// 1) CGDK는 std::weak_ptr<T>와 std::unique_ptr<T>를 제공하지 않는다.
//    대신 성격은 좀 다른 own_ptr<T>를 제공한다.
//
// 2) CGDK::own_ptr<T>는 독점 소유권을 가진 것으로 std::unique_ptr<T>와
//    비슷한 개념이지만 좀 많이 다르다.
//    CGDK::own_ptr<T>의 독점권은 CGDK::own_ptr<T>간에만 독점적일 뿐
//    CGDK::object_ptr<T>는 얼마든지 참조될 수 있다.
//    이 특징을 정리하자면 다음과 같다.
//
//    - CGDK::own_ptr<T>에는 대입을 할수 없다.
//    - CGDK::own_ptr<T>에는 오직 CGDK::own_ptr<T>간의 이동(move)만 값을
//      넣을 수 있다.
//    - CGDK::make_object<T> 대신 CGDK::make_own<T> 함수를 사용해야 한다.
//    - CGDK::own_ptr<T>에서 CGDK::object_ptr<T>로 대입은 가능하나 반대로는
//      안됀다.
//    - CGDK::own_ptr<T>에서 CGDK::Idestroyable 인터페이스를 상속받은 
//      객체가 제거되면 해당 객체의 destroy()함수를 호출해준다.
//      CGDK::Idestroyable 인터페이스를 상속받지 않았다면 호출되지 않는다.
//      CGDK::Istartable 인터페이스만 상속받았다면 stop()함수를 호출한다.
//      CGDK::Istartable과 CGDK::Idestroyable을 모두 상속받았다면 stop()과 
//      destroy()를 차례로 호출해준다.
//
// 3) CGDK::own_ptr<T>는 해당 객체를 제거할 때 해당 객체의 destroy()를
//    호출해주며 객체의 종료를 위한 처리를 해준다.
//    따라서 CGDK::own_ptr<T>는 순환 참조를 해결하는 역할을 한다.
//
// 4) CGDK::own_ptr<T>는 그 객체를 생성하고 파괴를 책임져야 하는 곳에서는 
//    CGDK::object_ptr<T>대신 사용하여 객체의 stop()이나 destroy()함수를
//    호출해 줄수 있게 해준다.
// 
// ------------------------------------------------------------------
class bat : virtual public Ireferenceable, virtual public object::Idestroyable
{
public:
			bat() noexcept { std::cout << "'bat c'tor'"sv; }
	virtual ~bat() noexcept { std::cout << "'bat d.tor'"sv; }

	virtual	result_code	destroy() noexcept override { std::cout << "''bat::destroy' called!!'"sv; return eRESULT::SUCCESS; }
};

void tutorial_step_4()
{
	// 1) 그냥 make_object<T>로 생성한 객체...
	object_ptr<bat>	temp_1 = make_object<bat>();

	// 2) 반면 own_ptr<T>는 make_own으로 생성해야 한다.
	own_ptr<bat> temp_2 = make_own<bat>();

	// 3) 당연히 auto로도 쓸수 있다.
	auto temp_2_x = make_own<bat>(); // temp_2_x는 own_ptr<bat>형이다.

	// 4) own_ptr<T>과 object_ptr<T>간의 대입
	//temp_2 = temp_1;	// error own_ptr<T>에는 object_ptr<T>를 대입할 수 없다.
	temp_1 = temp_2;	// ok~! own_ptr<T>에는 object_ptr<T>를 대입할 수 있다.

	// declare) 
	own_ptr<bat> temp_3;

	// 4) 복사
	//temp_3 = temp_2; // Error!!  own_ptr<T> 객체간에 copy는 불가능하다.
	temp_3 = std::move(temp_2);	// ok~~! own_ptr<T> 간에는 move만 가능하다.

	// 5) own_ptr<T>는 reset될 때 stop(), destroy()가 호출된다.
	//    destory()의 호출은 on_final_release를 의미하지 않는다.
	//    즉 destroy만 호출될 뿐 객체 자체가 소멸되지는 않는다.
	//    move가 아닌 방법으로 own_ptr<T>에서 떠나는 객체는 
	//    destroy()를 호출한다.
	temp_3.reset();
}
