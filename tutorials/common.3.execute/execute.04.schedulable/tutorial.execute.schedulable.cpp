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
// tutorial.04.schedulable
//
//
//-----------------------------------------------------------------------------
class bar : public schedulable::Nexecutable
{
	virtual	void on_execute() override
	{
		std::cout << "'bar' executed"sv << '\n';
	}
};

class buk : virtual public Ireferenceable
{
public:
	void process_function()
	{
		std::cout << "buk's member function executed"sv << '\n';
	}
};

void process_function()
{
	std::cout << "'process_function' executed"sv << '\n';
}

int main()
{
	// ------------------------------------------------------------------
	// 1. schedulable::executable_function - lambda function
	//    - lambda 함수를 설정한 시간 마다 한번씩 호출한다.
	//
	// ------------------------------------------------------------------
	{
		std::cout << "1. schedulable::executable_function - lambda function"sv << '\n';

		// 1) schedulable를 생성한다.
		auto pschedulable = make_own<schedulable::executable_function<>>();

		// 2) lambda 함수를 설정한다.
		pschedulable->start({ [=]()
			{
				std::cout << "lambda function executed"sv << '\n';
			},
			500ms });

		// 3) ESC 키를 입력할 때까지 기다린다.
		while (_getch() != 27);

		// !) pscheedualbe은 own_ptr<T> 므로 블록이 끝나면 자동적으로
		//    destroy()가 호출된다. 만약 own_ptr<T>가 아니라면 직접
		//    destroy()를 호출해줘야 한다.
	}

	// ------------------------------------------------------------------
	// 2. schedulable::executable_function - static function
	//    - 일반 함수를 설정한 시간 마다 한번씩 호출한다.
	//
	// ------------------------------------------------------------------
	{
		std::cout << "2. schedulable::executable_function - static function"sv << '\n';

		// 1) schedulable를 생성한다.
		auto pschedulable = make_own<schedulable::executable_function<>>();

		// 2) 일반 함수를 설정한다.
		pschedulable->start({ process_function, 500ms });

		// 3) ESC 키를 입력할 때까지 기다린다.
		while (_getch() != 27);

		// !) pscheedualbe은 own_ptr<T> 므로 블록이 끝나면 자동적으로
		//    destroy()가 호출된다. 만약 own_ptr<T>가 아니라면 직접
		//    destroy()를 호출해줘야 한다.
	}

	// ------------------------------------------------------------------
	// 3. schedulable::executable_function - member function
	// 	  - std::bind를 사용한다.
	//    - 멤버 함수를 설정한 시간 마다 한번씩 호출한다.
	//
	// ------------------------------------------------------------------
	{
		std::cout << "3. schedulable::executable_function - member function"sv << '\n';

		// 1) schedulable를 생성한다.
		auto pschedulable = make_own<schedulable::executable_function<>>();

		// 2) buk 객체를 생성한다.
		auto pobject = make_object<buk>();

		// 3) 멤버 함수로 실행할 수 있습니다. (std::bind를 사용)
		pschedulable->start({ std::bind(&buk::process_function, pobject), 500ms });

		// 4) ESC 키를 입력할 때까지 기다린다.
		while (_getch() != 27);

		// !) pscheedualbe은 own_ptr<T> 므로 블록이 끝나면 자동적으로
		//    destroy()가 호출된다. 만약 own_ptr<T>가 아니라면 직접
		//    destroy()를 호출해줘야 한다.
	}

	// ------------------------------------------------------------------
	// 4. schedulable::Nexecutable
	//    - schedulable::Nexecutable을 상속받아 구현한다.
	//    - 가상함수 on_execute() 함수를 재정의하여 사용한다.
	// 	  - start()함수가 아니라 executor에 register함으로서 시작한다.
	// 	    
	//
	// ------------------------------------------------------------------
	{
		std::cout << "4. schedulable::Nexecutable"sv << '\n';

		// 1) bar 객체를 생성한다.
		auto pschedulable = make_object<bar>();

		// 2) 1초에 2번(500ms) on_execute가 실행되도록 설정한다.
		pschedulable->execute_interval(500ms);

		// 3) system_executor에 등록한다.
		system_executor::register_schedulable(pschedulable);

		// 4) ESC 키를 입력할 때까지 기다린다.
		while (_getch() != 27);

		// 5) schedulable객체들을 unregister한다.
		//    - 이 순간부터 더이상 호출되지 않는다.
		system_executor::unregister_schedulable(pschedulable);
	}

	// ------------------------------------------------------------------
	// 5. all together
	//
	// ------------------------------------------------------------------
	{
		std::cout << "5. all together"sv << '\n';

		// 1.1) schedulable를 생성한다.
		auto pschedulable_a = make_own<schedulable::executable_function<>>();

		// 1.2) 500ms마다 한번씩
		pschedulable_a->start({ [=]()
			{
				std::cout << "lambda function executed"sv << '\n';
			},
			500ms });


		// 2.1) schedulable를 생성한다.
		auto pschedulable_b = make_own<schedulable::executable_function<>>();

		// 2.2) 1초마다 한번씩
		pschedulable_b->start({ process_function, 1s });


		// 3,1) schedulable를 생성한다.
		auto pschedulable_c = make_own<schedulable::executable_function<>>();

		// 3.2) buk 객체를 생성한다.
		auto pobject = make_object<buk>();

		// 3.3) 2초마다 한번씩
		pschedulable_c->start({ std::bind(&buk::process_function, pobject), 2s });


		// 4.1) bar 객체를 생성한다.
		auto pschedulable_d = make_object<bar>();

		// 4.2) 5초마다 1번씩
		pschedulable_c->execute_interval(5s);

		// 4.3) system_executor에 등록한다.
		system_executor::register_schedulable(pschedulable_d);


		// 5) ESC 키를 입력할 때까지 기다린다.
		while (_getch() != 27);

		// 6) schedulable객체들을 unregister한다.
		//    - pschedulable_a
		//      pschedulable_b
		//      pschedulable_c는 
		//      자동적으로 destroy()함수가 호출된다.;
		//
		//    - pschedulable는 직접 unregister해줘야 한다.
		//    - 이 순간부터 더이상 호출되지 않는다.
		system_executor::unregister_schedulable(pschedulable_d);
	}

	// return)
	return	0;
}
