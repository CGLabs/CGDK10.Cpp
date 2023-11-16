//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                     tutorials common - interface.01                       *
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
// step 1) CGDK::Idestroyable, CGDK::Iinitializable, CGDK::Istartable 인터페이스
//
// 
// 
// 
//
// 
// 
// 
// 
//
//-----------------------------------------------------------------------------
class foo : virtual public object::Idestroyable
{
public:
	virtual	result_code destroy() noexcept override
	{
		std::cout << "destroyed"sv << '\n';

		// return) 
		return eRESULT::SUCCESS;
	}
};

class goo : virtual public object::Iinitializable
{
public:
	virtual	result_code initialize(context& _context) override
	{
		// - param_1값을 읽어낸다.
		int			value_1 = _context["param_1"sv];
		std::string value_2 = _context["param_2"sv];

		// - param값을 출력한다.
		std::cout << "initialized "  << value_1 << " " << value_2 << '\n';

		// return)
		return  eRESULT::SUCCESS;
	}

	virtual	result_code destroy() noexcept override
	{
		std::cout << "destroyed"sv << '\n';

		// return) 
		return eRESULT::SUCCESS;
	}
};

class xoo : public goo, virtual public object::Istartable
{
public:
	virtual	result_code start(context& _context) override
	{
		// - param_1값을 읽어낸다.
		int			value_1 = _context["param_1"sv];
		std::string value_2 = _context["param_2"sv];

		// - param값을 출력한다.
		std::cout << "stared "sv << value_1 << " "sv << value_2 << '\n';

		// return)
		return eRESULT::SUCCESS;
	}

	virtual	result_code stop() noexcept
	{
		std::cout << "stopped"sv << '\n';

		// return)
		return eRESULT::SUCCESS;
	}
};

void tutorial_object_interface_2_step_1_interfaces()
{
	// 1) Idestroyable
	{
		// - own_ptr<T>를 사용하면 객체가 소멸시 destroy()함수를 자동으로 불러준다.
		auto pobject = make_own<foo>();
	}

	// 2) Iinitializable
	{
		// - own_ptr<T>를 사용해 객체를 생성한다.
		auto pobject = make_own<goo>();

		// * initialize에 전달할 context를 설정한다.
		context context_setting;
		context_setting["param_1"sv] = 100;
		context_setting["param_2"sv] = "hahaha"sv;

		// * initialize를 호출한다.
		pobject->initialize(context_setting);

	}

	// 3) Iinitializable & Istartable
	{
		// - own_ptr<T>를 사용해 객체를 생성한다.
		auto pobject = make_own<xoo>();

		// - initialize에 전달할 context를 설정한다.
		context context_setting;
		context_setting["param_1"sv] = 100;
		context_setting["param_2"sv] = "hahaha"sv;

		// - initialize를 호출한다.
		pobject->initialize(context_setting);

		// * start한다.
		pobject->start(context_setting);

		// *own_ptr<T>는 소멸될 때 stop과 destroy를 호출해 준다.
	}
}
