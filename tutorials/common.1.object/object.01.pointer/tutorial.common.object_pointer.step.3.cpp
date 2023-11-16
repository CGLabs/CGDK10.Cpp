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
// step 2) pool을 사용한 객체 할당
//
// 1) alloc_object<T>()
//    간단히 pool을 사용해 객체를 생성할 수 있다.
//    alloc_object<T>()는 객체를 풀에서 할당받게 하는 것이다.
//    또 풀에서 상속받은 객체는 참조계수가 0이 되면 자동으로 풀로 돌아간다.
//
// 2) Npoolable<T> 클래스
//    Npoolable<T>를 상속받으면 alloc_object<T>를 사용하지 않고 
//    amke_object<T>나 make_own<T>를 사용해도 자동적으로 pool에서 할당받게
//    해준다.
//
//-----------------------------------------------------------------------------
// 1) 
class bar : virtual public Ireferenceable
{
public:
			bar()		{ std::cout << "'bar' created!"sv << std::endl; }
	virtual	~bar()		{ std::cout << "'bar' destroyed"sv << std::endl; }

	void	on_alloc()	{ std::cout << "'bar' allocated"sv << std::endl; }
	void	on_free()	{ std::cout << "'bar' freed"sv << std::endl; }
};

// 2) 
class qux : public Npoolable<qux>
{
public:
			qux()		{ std::cout << "'qux' created!"sv << std::endl; }
	virtual	~qux()		{ std::cout << "'qux' destroyed"sv << std::endl; }

	void	on_alloc()	{ std::cout << "'qux' allocated"sv << std::endl; }
	void	on_free()	{ std::cout << "'qux' freed"sv << std::endl; }
};

void tutorial_step_3()
{
	// 1) make_object<T> 대신 alloc_object<T>를 풀에서 객체를 할당받는다.
	object_ptr<bar> pobject_a = alloc_object<bar>();

	// 2) Irefenceable 대신 Npoolable<T>를 상속받으면 make_object<T>해도
	//    자동으로 pool에서 할당받게 된다.
	object_ptr<qux> pobject_b = make_object<qux>();

	// 3) 참조계수가 0이 되여 할당 해제되면 자동으로 할당을 했던 pool로 돌아간다.
}
