//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                      tutorials query - oledb.simple                       *
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

// option) Windows의 경우 Native를 사용할 것인가 혹은 ODBC를 사용할 것인가를 결정할 수 있다.
//         Linux의 경우 기본으로 ODBC를 사용하므로 이 옵션은 무시된다.
#define _USE_ODBC

#include <iostream>

// * CGDK header file
#include "cgdk/sdk10/server.query.rdb.h"

// * namespace CGDK
using namespace CGDK;


void tutorial_excel_file_create_write()
{
	// ------------------------------------------------------------------
	//
	// A. excel 파일 열기
	//
	//    - querier는 provider = eDB_PROVIDER::EXCEL로 설정하고
	//      두번째 파라미터에 파일이름을 써넣는다.
	//   
	//      * 첫번째 파라미터 => eDB_PROVIDER::EXCEL
	//      * 두번째 파라미터 => 파일명
	//
	//    - excel 파일의 경우 id, password, initial_catalog를 넣을 필요 없다. 
	//
	// ------------------------------------------------------------------

	// 1) create queirier object
	auto pquerier = make_own<query::rdb::querier_t>();

	// 2) start querier
	pquerier->start(eDB_PROVIDER::EXCEL, ".\\test_create.xls"sv);


	// ------------------------------------------------------------------
	//
	// B. 테이블 생성하기
	//
	// ------------------------------------------------------------------
	try
	{
		// 1) request query
		pquerier->execute_query("CREATE TABLE [test_sheet](Id NUMBER, Name TEXT, Score NUMBER)"sv);
	}
	catch (throwable::failure_ex& _e)
	{
		// 실패시 exception이 발생하며 절달되는 throwable::failure_ex에 오류 정보가 들어 있다.

		// @ stream으로 출력시키려고 할 경우 - stream 객체로 >> 해준다.
		_e >> std::cout;

		// @ log로 남기고 싶을 경우 - log 객체를 바로 얻어서 log로 남길 수 있다.
		_log(nullptr, _e.get_log_record());
	}


	// ------------------------------------------------------------------
	//
	// C. excel에서 값 써넣기
	//
	//    1) 일반적인 sql 문과 동일하게 사용가능하다.
	//
	// ------------------------------------------------------------------
	try
	{
		// 1) query를 요청한다.
		auto pquery = pquerier->execute_query("INSERT INTO [test_sheet] (id, Name, Score) VALUES(1, 'test_name', 100)"sv);
	}
	catch (throwable::failure_ex& _e)
	{
		// 실패시 exception이 발생하며 절달되는 throwable::failure_ex에 오류 정보가 들어 있다.

		// @ stream으로 출력시키려고 할 경우 - stream 객체로 >> 해준다.
		_e >> std::cout;

		// @ log로 남기고 싶을 경우 - log 객체를 바로 얻어서 log로 남길 수 있다.
		_log(nullptr, _e.get_log_record());
	}
}
