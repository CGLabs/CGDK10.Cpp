//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                     tutorials common.ex01 - file i/o                      *
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
// tutorial common.ex01 - archive::file
//
//-----------------------------------------------------------------------------
int main()
{
	// ---------------------------------------------------------------------
	// 1. archive file
	//    - 파일 객체로 start/stop interface를 공유한다.
	//      따라서 own_ptr을 사용할 경우 특별한 종료처리를 할 필요 없다.
	//    - 당연히 외부 json으로 설정이 가능하다.
	//
	// ---------------------------------------------------------------------
	// trace)
	std::cout << "start..."sv << std::endl;

	{
		// 1) ...
		auto parchive_file = make_own<archive::file>();

		// declare)
		archive::file::START_PARAMETER param;

		// 2) start를 위한 파라미터를 설정한다.
		param.filename = "test.txt"s;
		param.file_operation = eFILE_OPERATION::APPEND;

		// 3) start한다.
		parchive_file->start(param);

		// 4) 써넣는다.
		parchive_file->write("test_file_temp\n"sv);
		parchive_file->write("test_file_temp\n"sv);
		parchive_file->write("test_file_temp\n"sv);
		parchive_file->write("test_file_temp\n"sv);
		parchive_file->write("test_file_temp\n"sv);
		parchive_file->write("test_file_temp\n"sv);
		parchive_file->write("test_file_temp\n"sv);
		parchive_file->write("test_file_temp\n"sv);
		parchive_file->write("test_file_temp\n"sv);
		parchive_file->write("test_file_temp\n"sv);
		parchive_file->write("test_file_temp\n"sv);

		// 5) 블록이 끝나면 own_ptr<T>이므로 자동적으로 destroy가 호출된다.
	}

	// trace) 
	std::cout << "end..."sv << std::endl;


	// ---------------------------------------------------------------------
	// 2. file open/close/read/write로 직접 다루기
	// 	  - api를 직접 조작하여 수동으로 파일을 열고 닫을 수 있다.
	// ---------------------------------------------------------------------
	{
		// 1) ...
		auto pfile = api::file::open("test.txt"sv, eFILE_OPERATION::APPEND);

		// 2) 버퍼를 할당받고 저장할 내용을 써넣는다.
		auto buf_write = alloc_shared_buffer(1024);
		buf_write.append_text("test_file_temp\n"sv);
		buf_write.append_text("test_file_temp\n"sv);
		buf_write.append_text("test_file_temp\n"sv);
		buf_write.append_text("test_file_temp\n"sv);
		buf_write.append_text("test_file_temp\n"sv);
		buf_write.append_text("test_file_temp\n"sv);
		buf_write.append_text("test_file_temp\n"sv);
		buf_write.append_text("test_file_temp\n"sv);
		buf_write.append_text("test_file_temp\n"sv);
		buf_write.append_text("test_file_temp\n"sv);

		// 2) 써넣는다.
		api::file::write(pfile, buf_write);

		// 3) file을 닫는다.
		api::file::close(pfile);
	}


	// ---------------------------------------------------------------------
	// 3. 간단 파일 read/wirte
	//    - 파일을 그냥 통채로 읽어올때 혹은 통채로 저장할 때
	//      read()와 write() 함수만으로 간단히 처리할 수 있다.
	//    - open이나 close 등의 처리 필요 없이 함수 하나로 처리하는 것이 가능하다.
	// ---------------------------------------------------------------------
	{
		// 1) "test.txt"파일을 통채로 읽어 퍼에 넣어 리턴한다. 
		//    읽기 실패시 size()가 0이 된다.
		auto data_read = api::file::read("test.txt"sv);

		// 2) "test.txt"파일에 통체로 써넣는다.
		api::file::write("test.txt"sv, data_read);
	}


	// Return) 끝.
	return 0;
}
