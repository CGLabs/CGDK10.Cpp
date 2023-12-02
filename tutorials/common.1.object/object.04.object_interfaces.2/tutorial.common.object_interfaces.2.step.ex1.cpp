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
// step ex1) CGDK::Nobject_startable
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
// 설명) CGDK::Nobject_startable은 CGDK::Nobject_state + CGDK::Ninitializable + CGDK::Nstartable를 상속받은 것이다.
//       따라서 3개를 상속받을 필요 없이 하나로 끝~
class baz :
	public object::Ninitializable_startable	// CGDK::Nobject_startable은 CGDK::Nobject_state + CGDK::Ninitializable + CGDK::Nstartable
{
public:
	virtual	void				on_initialize_request(context& /*_context*/){ std::cout << "on_initialize_request"sv << '\n'; }
	virtual	void				on_initializing(context& /*_context*/)		{ std::cout << "on_initializing"sv << '\n'; }
	virtual	void				on_initialize(context& /*_context*/)		{ std::cout << "on_initialize"sv << '\n'; }

	virtual	void				on_start_request(context& /*_context*/)		{ std::cout << "on_start_request"sv << '\n'; }
	virtual	void				on_starting(context& /*_context*/)			{ std::cout << "on_starting"sv << '\n'; }
	virtual	void				on_start(context& /*_context*/)				{ std::cout << "on_start"sv << '\n'; }

	virtual	void				on_stop_request()	{ std::cout << "on_stop_request"sv << '\n'; }
	virtual	void				on_stopping()		{ std::cout << "on_stopping"sv << '\n'; }
	virtual	void				on_stop()			{ std::cout << "on_stop"sv << '\n'; }

	virtual	void				on_destroy_request(){ std::cout << "on_destroy_request"sv << '\n'; }
	virtual	void				on_destroying()		{ std::cout << "on_destroying"sv << '\n'; }
	virtual	void				on_destroy()		{ std::cout << "on_destroy"sv << '\n'; }
};

void tutorial_object_interface_2_step_ex1_Nobject_startable()
{
	// - initialize에 전달할 context를 설정한다.
	context context_setting;
	context_setting["param_1"sv] = 100;
	context_setting["param_2"sv] = "hahaha"sv;

	// - own_ptr<T>를 사용해 객체를 생성한다.
	auto pobject = make_own<baz>();

	// * start한다.
	pobject->start(context_setting);


}
