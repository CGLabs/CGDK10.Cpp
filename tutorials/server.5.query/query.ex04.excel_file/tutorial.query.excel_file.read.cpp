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
//#define _USE_ODBC

#include <iostream>

// * CGDK header file
#include "cgdk/sdk10/server.query.rdb.h"

// * namespace CGDK
using namespace CGDK;


void tutorial_excel_file_read()
{
	// ------------------------------------------------------------------
	//
	// A. excel 파일 열기
	//
	//    - querier는 provider = eDB_PROVIDER::EXCEL로 설정하고
	//       두번째 파라미터에 파일이름을 써넣는다.
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
	pquerier->start(eDB_PROVIDER::EXCEL, ".\\test.xlsx"sv);


	// ------------------------------------------------------------------
	//
	// B. excel에서 값 읽기 (1)
	//
	//    - excel sheet의 제일 첫번째 줄은 필드명으로 인식한다.
	//    - SELECT 문 등에서 table 을 지정할 때는 반드시 $A1:D5와 같이 영역을
	//      정의해주어야 한다.
	//    - 각 필드의 자료형은 자동적으로 결정된다.
	//
	// ------------------------------------------------------------------
	try
	{
		// 1) query를 요청한다.
		auto pquery = pquerier->execute_query("SELECT * FROM [Sheet1$A1:D5]"sv);

		// 2) query 결과를 읽어 들인다.
		auto result = pquery->move_first();

		// 3) 완료될 때까지 반복한다.
		while (result == eRESULT::SUCCESS)
		{
			// - 결과는 get_value<T>(index) 함수를 사용해 얻을 수 있다.
			//   T는 해당 칼럼의 자료형으로 DB의 자료형과 맵핑되는 형태를 써넣어야 한다.
			//   index는 칼럼의 index값으로 1부터 시작한다. (0번은 일반적으로 bookmark에 할당된다.)
			auto value_01 = pquery->result().get_value<std::string>(1);
			auto value_02 = pquery->result().get_value<int>(2);
			auto value_03 = pquery->result().get_value<std::string>(3);
			auto value_04 = pquery->result().get_value<float>(4);

			// - print~
			std::cout << "value_01 "sv << value_01 << '\n';
			std::cout << "value_02 "sv << value_02 << '\n';
			std::cout << "value_03 "sv << value_03 << '\n';
			std::cout << "value_04 "sv << value_04 << '\n';
			std::cout << '\n';

			// - 다음 row로...
			result = pquery->move_next();
		}

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
	// C. excel에서 값 읽기 (2)
	//
	//    - 일반적인 sql 문과 동일하게 사용가능하다.
	//
	// ------------------------------------------------------------------
	try
	{
		// 1) query를 요청한다.
		auto pquery = pquerier->execute_query("SELECT No, Subject, Ratio, Score FROM [Sheet2$A1:D7] WHERE score > 50"sv);

		// 2) query 결과를 읽어 들인다.
		auto result = pquery->move_first();

		// 3) 완료될 때까지 반복한다.
		while (result == eRESULT::SUCCESS)
		{
			// - 결과는 get_value<T>(index) 함수를 사용해 얻을 수 있다.
			//   T는 해당 칼럼의 자료형으로 DB의 자료형과 맵핑되는 형태를 써넣어야 한다.
			//   index는 칼럼의 index값으로 1부터 시작한다. (0번은 일반적으로 bookmark에 할당된다.)
			auto value_01 = pquery->result().get_value<int>(1);
			auto value_02 = pquery->result().get_value<std::string>(2);
			auto value_03 = pquery->result().get_value<float>(3);
			auto value_04 = pquery->result().get_value<int>(4);

			// - print~
			std::cout << "value_01 "sv << value_01 << '\n';
			std::cout << "value_02 "sv << value_02 << '\n';
			std::cout << "value_03 "sv << value_03 << '\n';
			std::cout << "value_04 "sv << value_04 << '\n';
			std::cout << '\n';

			// - 다음 row로...
			result = pquery->move_next();
		}

	}
	catch (throwable::failure_ex& _e)
	{
		// 실패시 exception이 발생하며 절달되는 throwable::failure_ex에 오류 정보가 들어 있다.

		// @ stream으로 출력시키려고 할 경우 - stream 객체로 >> 해준다.
		_e >> std::cout;

		// @ log로 남기고 싶을 경우 - log 객체를 바로 얻어서 log로 남길 수 있다.
		_log(nullptr, _e.get_log_record());
	}


	// return)
	return;
}
