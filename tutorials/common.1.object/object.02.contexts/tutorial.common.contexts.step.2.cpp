//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                         tutorials common - context                        *
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
// step 2) json 파일과 context의 연계
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
void tutorial_context_step_2_json_file()
{
	// Declare) 
	context	temp;

	// 1) JSON파일 읽기
	temp.read_from_json_file("test_setting.json"sv);

	// 2) 읽은 JSON 파일 활용하기.
	temp["Text"sv] = "Save this"sv;

	// 4) File로 저장한다.
	temp.write_to_json_file("test_setting_updated.json"sv);

	// 5) JSON을 스트링으로 저장한다.
	shared_buffer buf = temp.write_to_json_string<wchar_t>();

	// trace) 화면에 출력한다.
	std::cout << buf.data() << std::endl;
}
