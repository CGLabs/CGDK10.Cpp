//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                     tutorials common - interface.03                       *
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
// tutorial common - object pointer
//
// CGDK에서 객체의 생성과 파괴 혹은 각종 기능의 수행의 공통된 처리를 위해 여러
// Inteface class를 사용하고 있습니다.
// 이것들에 대한 설명입니다.
//
//  1) 메시지 처리 관련 interface class
//
//       - CGDK::Imessageable	(+CGDK::Ireferenceable)
//       - CGDK::Imessage_transmitter	(+CGDK::Iattachable<Imessageable>)
//
//  
//-----------------------------------------------------------------------------
class foo : 
	public	object::Nstate,
	public	object::Ninitializable,
	public	object::Nstartable
{
public:
	// 1) 생성자와  소멸자
			foo()				{ std::cout << "@ Contructor..."sv << std::endl; }
	virtual	~foo()				{ std::cout << "@ Destructor..."sv << std::endl; }

	// 2) Ninitializable
	virtual	void				on_initializing(context& /*_msg*/) override	{ std::cout << "  on_initializing..."sv << std::endl; }
	virtual	void				on_initialize(context& /*_msg*/) override	{ std::cout << "  on_initialize..."sv << std::endl; }
	virtual	void				on_destroying() override					{ std::cout << "  on_destroying..."sv << std::endl; }
	virtual	void				on_destroy() override						{ std::cout << "  on_destroy..."sv << std::endl; }

	// 3) Nstartable
	virtual	void				on_starting(context& /*_msg*/) override		{ std::cout << "  on_starting..."sv << std::endl; }
	virtual	void				on_start(context& /*_msg*/) override		{ std::cout << "  on_start..."sv << std::endl; }
	virtual	void				on_stopping() override						{ std::cout << "  on_stopping..."sv << std::endl; }
	virtual	void				on_stop() override							{ std::cout << "  on_stop..."sv << std::endl; }
};

int main()
{
	// trace)
	std::cout << "start..."sv << std::endl;

	// trace)
	std::cout << "End..."sv << std::endl;

	// - getch
	_getch();

	// Return) 끝.
	return 0;
}
