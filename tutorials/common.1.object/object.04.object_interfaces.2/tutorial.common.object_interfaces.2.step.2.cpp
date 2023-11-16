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
// step 2) CGDK::Nobject_state, CGDK::Ninitializable, CGDK::Nstartable 인터페이스
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
class bar :
	public object::Nstate,
	public object::Ninitializable,
	public object::Nstartable
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


void tutorial_object_interface_2_step_2_Nobject()
{
	// * initialize에 전달할 context를 설정한다.
	context context_setting;
	context_setting["param_1"sv] = 100;
	context_setting["param_2"sv] = "hahaha"sv;

	// 1) 기본 동작 initialize -> start -> stop -> destroy
	{
		// - own_ptr<T>를 사용해 객체를 생성한다.
		auto pobject = make_own<bar>();

		// * initialize를 호출한다.
		pobject->initialize(context_setting);

		// * start한다.
		pobject->start(context_setting);

		// * stop한다.
		pobject->stop();

		// * destroy한다.
		pobject->destroy();
	}

	// 2) 자동 호출 - 1
	{
		// - own_ptr<T>를 사용해 객체를 생성한다.
		auto pobject = make_own<bar>();

		// * start만 해도 initialize는 자동 하출된다.
		pobject->start(context_setting);

		// * stop과 destroy는 own_ptr<T>에서 자동적으로 호출해준다.
	}

	// 3) 자동 호출 - 2
	{
		// - own_ptr<T>를 사용해 객체를 생성한다.
		auto pobject = make_own<bar>();

		// - start한다.
		pobject->start(context_setting);

		// * destroy만 호출해도 start되었다면 stop이 먼저 호출된후 destroy가 처리한다.
		pobject->destroy();
	}

	// 4) 중복 호출
	{
		// - own_ptr<T>를 사용해 객체를 생성한다.
		auto pobject = make_own<bar>();

		// - start한다.
		pobject->start(context_setting);

		// * start를 한번 더해도 두번 호출되지 않는다.
		pobject->start(context_setting);

		// * initialize를 호출해도 start호출시 이미 호출되었으므로 호출되지 않느다.
		pobject->initialize(context_setting);
	}
}
