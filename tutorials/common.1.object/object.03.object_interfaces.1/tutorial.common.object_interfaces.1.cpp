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

//-----------------------------------------------------------------------------
//
// tutorial common - object pointer
//
// CGDK에서 객체의 생성과 파괴 혹은 각종 기능의 수행의 공통된 처리를 위해 여러
// Inteface class를 사용하고 있습니다.
// 이것들에 대한 설명입니다.
//
//  1) 참조계수
//
//     * CGDK::Ireferenceable
//
//  2) 객체 속성 관련 inteface
//
//       - CGDK::Iobject_identifiable
//       - CGDK::Inameable
//       - CGDK::Iattachable	(+CGDK::Ireferenceable)
//       - CGDK::Iobject		(+CGDK::Iobject_identifiable, +CGDK::Imessageable, +CGDK::Inameable)
//       - CGDK::Iobject_state	(+CGDK::Nattachable<Iobject_state>)
//       - CGDK::Iresource		(+CGDK::Iobject, +CGDK::Idestroyable)
//
//  
//-----------------------------------------------------------------------------
void tutorial_object_interface_1_step_1_Inameable();
void tutorial_object_interface_1_step_2_object_hierarchy();
void tutorial_object_interface_1_step_ex1_Nobject_startable();

int main()
{
	// 1) Nnameable 인터페이스
	tutorial_object_interface_1_step_1_Inameable();

	// 2) object hierarchy 인터페이스
	tutorial_object_interface_1_step_2_object_hierarchy();

	// ex.1) object::Ninitializable_startable 인터페이스
	tutorial_object_interface_1_step_ex1_Nobject_startable();

	// return)
	return 0;
}
