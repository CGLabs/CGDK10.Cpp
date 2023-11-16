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

// definitions) 
class foo : virtual public Iexecutable
{
public:
	foo() = default;
	explicit foo(std::string&& _str_exp) : m_str_exp(_str_exp) {}

	virtual	intptr_t process_execute(intptr_t /*_return*/, size_t /*_param*/) override
	{
		std::cout << "["sv << m_str_exp << "]"sv << '\n';

		return 0;
	}

public:
	std::string		m_str_exp;
};

class goo : virtual public Ireferenceable
{
public:
	void print_string(const std::string& _string)
	{
		std::cout << "this is goo!! "sv << _string << '\n';
	}
};

void test_function_1()
{
	std::cout << "general function"sv << '\n';
}

void test_function_2(int _x, int _y)
{
	std::cout << "sum is"sv << _x + _y << '\n';
}

int main()
{
	// ------------------------------------------------------------------
	// 1. post() 함수!
	//    - system_executor의 post함수로 비동기 실행을 할 수 있다.
	//    - post() 함수는 반드시 Iexecutable 객체를 받아 비동기적으로
	//      Iexecutable::process_execute() 함수를 실행한다.
	// ------------------------------------------------------------------
	{
		// - executable을 생성한다.
		auto pexecutor_1 = make_object<foo>();

		// - 비동기적으로 pexecutor_1의 process_execute함수를 실행한다.
		system_executor::post(pexecutor_1);

		// - executable을 생성해서 바로 실행걸기
		system_executor::post(make_object<foo>());
	}
	//-----------------------------------------------------------------
	// 2. make_executable 함수
	//    - 일반 함수, lambda함수, std::bind 등등 실행가능한 모든 객체와
	//      함수들은 make_executable을 사용해 편리하게 Iexecutable 객체로
	//      만들어 준다.
	//    - make_executable 함수로 만들어진 Iexecutable 객체를 post 함수로
	//      비동기적으로 실행한다.
	//
	//     system_executor::post(make_executable([함수]));
	//     system_executor::post(make_executable([lambda 함수]));
	//     system_executor::post(make_executable([std::bind(...)]));
	// 
	//-----------------------------------------------------------------
	{
		// 1) 일반 함수(test_function_1)를 비동기적으로 실행한다.
		system_executor::post(make_executable(&test_function_1));

		// 2) lambda 함수를 비동기적으로 실행한다.
		system_executor::post(make_executable([=]()
			{
				std::cout << "lambda execution."sv;
			}));

		// 3)  std::bind도 비동기적으로 실행할 수 있다.
		system_executor::post(make_executable(std::bind(&test_function_2, 10, 20)));

		// 4) member함수를 비동기적으로 실행하기
		//    - 비동기적으로 호출되므로 객체의 소멸 시점을 주의할 필요가 있다.
		//      object_ptr<T>을 사용하면 자동적으로 호출이 완료될 때까지 객체를 해제하지는 않습니다.
		//    - std::bind()함수를 사용해 멤버함수도 비동기적으로 호출할 수 있다.
		{
			auto pobject = make_object<goo>();

			// - 위의 형이 아닐 경우 std::bind를 사용한다.
			system_executor::post(make_executable(std::bind(&goo::print_string, pobject, "std::bind!!"s)));
		}
	}
	//-----------------------------------------------------------------
	// 3. 일정시간 이후 실행하기
	//    - post함수의 두번째 인자로 실행 시간을 넣으면 해당 시간에
	//      실행할 수 있다.
	//    - chroho::duration를 두번째 인자로 넣으면 현재 시간에서 
	//      그 시간만쿠 후에 실행된다.
	//
	//     system_executor::post([Iexecutable], [시각(timc_duration)]);
	//     system_executor::post([Iexecutable], [시간(duration)]);
	// 
	//-----------------------------------------------------------------
	{
		// 1) 실행 객체들을 생성하여 추가한다. 
		//   ( 각각 1초후, 2초후, 5초 후에 foo객체의 process_execute()을 실행한다.)
		system_executor::post(make_object<foo>("after 1sec"s), chrono::tick::now() + 1s);
		system_executor::post(make_object<foo>("after 2sec"s), chrono::tick::now() + 2s);
		system_executor::post(make_object<foo>("after 5sec"s), 5s); // 현재에서 5초후 실행 'chrono::tick::now() + 5s'와 동일하다.

		// 2) lambda함수를 사용할 수도 있다.(1.5초 후에 실행된다. Lambda는 VS2010부터 지원된다.)
		system_executor::post(make_executable([]() {std::cout << "lambda execution. [after 1500ms]\n"sv; }), chrono::tick::now() + 1500ms);

		// 3) member함수를 실행 시킬 수도 있다.(10초 후 실행된다.)
		system_executor::post(make_executable(std::bind(&goo::print_string, make_object<goo>(), "std::bind!!"s)), chrono::tick::now() + 10s);

		// 4) 일반 함수를 실행시킬 수도 있다.
		system_executor::post(make_executable(&test_function_1), chrono::tick::now() + 4s); // (현재시각의 4초 후에 실행된다.)
	}
	// ------------------------------------------------------------------
	// 4. executor 직접 생성해 사용하기
	//    - system_executor가 아니라 사용자가 직접 생성한 executor을 생성해 
	//      실행할 수도 있다.
	//
	// ------------------------------------------------------------------
	{
		// (*) executor를 생성한다.
		auto pexecutor = make_own<executor::io_context_threads>();

		// 2) thread 2개를 시작한다.
		pexecutor->start({ 2 });

		// 3) executor에 post함수로 비동기 실행을 요청한다.
		pexecutor->post(make_executable([=]()
			{
				std::cout << "lambda execution."sv;
			}));
	}

	//-----------------------------------------------------------------
	//
	// 5. 키를 입력할 때마다 foo 객체를 만들어 비동기 실행을 건다.
	//
	//-----------------------------------------------------------------
	for (;;)
	{
		// 1) 키보드로부터 입력을 받는다.
		int	ch = _getch();

		// check) 받은 키입력이 ESC(VK_ESCAPE)라면 빠져나간다.
		BREAK_IF(ch == 0x1B);

		// 2) 새 실행 객체를 생성한다.
		auto pexecutor = make_object<foo>("key pressed"s);

		// 3) 기본 executor에 실행을 건다.
		//    (실행된 이후 자동으로 detach된다.)
		system_executor::post(pexecutor);
	}

	// return)
	return	0;
}
