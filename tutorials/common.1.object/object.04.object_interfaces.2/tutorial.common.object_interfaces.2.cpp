//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                     tutorials common - interface.02                       *
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

//-----------------------------------------------------------------------------
//
// tutorial common - interface 2
//
// CGDK에서 객체의 생성과 파괴 혹은 각종 기능의 수행의 공통된 처리를 위해 여러
// Inteface class를 사용하고 있습니다.
// 이것들에 대한 설명입니다.
//
//  1) 객체의 초기화 소멸 처리 관련 interface class
// 
//       - CGDK::Iinitializable	(+CGDK::Idestroyable)
//       - CGDK::Idestroyable	(+CGDK::Ireferenceable)
//       - CGDK::Ipoolable		(+CGDK::Ireferenceable)
//       - CGDK::Idesposable
//      
//       - CGDK::Istartable		(+CGDK::Ireferenceable)
//       - CGDK::Ienable		(+CGDK::Ireferenceable)
//
//  2) Ninitializable, Nstartable, Nobject_state
//
//  3) Nobject_startable
//  
//-----------------------------------------------------------------------------
void tutorial_object_interface_2_step_1_interfaces();
void tutorial_object_interface_2_step_2_Nobject();
void tutorial_object_interface_2_step_ex1_Nobject_startable();

int main()
{
	// 1) Iinitializable 인터페이스
	tutorial_object_interface_2_step_1_interfaces();

	// 2) Istartable 인터페이스
	tutorial_object_interface_2_step_2_Nobject();

	// 3) Nobject
	tutorial_object_interface_2_step_ex1_Nobject_startable();

	// return)
	return 0;
}
