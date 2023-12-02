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
void tutorial_step_1();
void tutorial_step_2();
void tutorial_step_3();
void tutorial_step_4();
void tutorial_step_ex1();

int main()
{
	// step 1) CGDK::Ireferenceable와 CGDK::object_ptr<T>와 CGDK::make_object<T>()
	tutorial_step_1();

	// step 2) CGDK::object_ptr<T>의 인자 전달과 대입
	tutorial_step_2();

	// step 3) pool과 CGDK::Npoolable<T>
	tutorial_step_3();

	// step 4) CGDK::own_ptr<T>와 CGDK::make_own<T>()
	tutorial_step_4();

	// step ex1) object pool
	tutorial_step_ex1();

	// Return)
	return	0;
}
