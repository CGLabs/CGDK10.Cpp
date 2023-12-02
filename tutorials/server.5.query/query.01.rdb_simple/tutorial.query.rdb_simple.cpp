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

// option) Windows의 경우 Native를 사용할 것인가 oledb혹은 odbc를 사용할 것인가를 결정할 수 있다.
//         Linux의 경우 기본으로 odbc 밖에 사용할 수 없으므로 이 옵션은 무시된다.
#define _USE_ODBC

// option) SQL Server에 접속할 것인가? MySQL에 접속할 것인가? 주석처리하면 MySQL용 설정이된다.
#define _SQL_SERVER

#include <iostream>

// * CGDK header file
#include "cgdk/sdk10/server.query.rdb.h"

// * namespace CGDK
using namespace CGDK;


int main()
{
	// ------------------------------------------------------------------
	// 설명) CGDK.10의 db query 핵심 객체
	// 
	//   1) querier
	//      가장 먼저 생성해야 하는 객체로 odbc의 SQLHENV에 해당한다.
	//      초기화를 하게 되면 여러 개의 session을 생성해 보관하다 할당해준다.
	//      초기화를 위해 기본적으로 아래 parameter가 필요하다.
	// 
	//		- eDB_PROVIDER provider        : DB의 종류를 의미한다 MS SQL server 혹은 MySQL인지에 따라 설정한다.
	//                                       Mircosoft SQL Server => eDB_PROVIDER::SQL_SERVER
	//                                       MySQL => eDB_PROVIDER::MYSQL
	// 
	//		- std::string  data_source     : DB에 접속하기 위한 주소. 
	//        
	//		- std::string  user_id         : DB에 로그인하기 위한 id
	//		- std::string  password        : DB에 로그인 하기 위한 password
	//		- std::string  initial_catalog : DB catalog
	//      
	//   2) session
	//      - odbc의 SQLHDBC에 해당한다.
	//      - DB로 접속을 의미한다. 일반적으로 하나의 querier에 다수의 session을
	//        생성한다.
	//      - querier의 session을 alloc_session() 혹은 post_alloc_session()함수를 
	//        사용해 할당받을 수 있다.
	// 
	//   3) query 
	//      - ODBC의 statement(SQLHSTMT)에 해당한다.
	//      - session을 할당 다할당받은후 query 객체를 생성해 사용할 수 있다.
	//      - querier를 
	// 
	// 
	// ------------------------------------------------------------------
	// ------------------------------------------------------------------
	// A. querier 객체의 초기화
	//    1) querier는 provider, dsn, uid, pwd, catalog,option 등 6개의 
	//       파라미터로 각각 전달하여 초기화할 수도 있다.
	//    2) 초기화 문자열을 통채로 전달해 줄수도 있다.
	//    3) context를 사용해 초기화할 수도 있다.
	//   
	//    여기서는 1)번 방법으로 초기화하는 예제를 보여 준다.
	//
	// ------------------------------------------------------------------
	// @1) queirier 객체를 생성한다.
	own_ptr<query::rdb::querier_t> pquerier = make_own<query::rdb::querier_t>();

	// @2) querier 시작 - 파레미터를 넘겨서 초기화
	//
	//     - 첫번째 파라미터 => eDB_PROVIDER::SQL_SERVER, eDB_PROVIDER::MYSQL 등등...
	//     - 두번째 파라미터 => 접속할 DB의 주소 혹은 DSN
	//     - 세번째 파라미터 => user id 
	//     - 네번째 파라미터 => password
	//     - 다섯번째 파라미터 => initial_catalog 혹은 database
	//     - 여섯번째 파라미터 => options
	//
	try
	{
	#if defined(_SQL_SERVER)
		pquerier->start(eDB_PROVIDER::SQL_SERVER, "www.cgcii.co.kr"sv, "test_user"sv, "1234"sv, "test_db"sv); // microsoft SQL server
	#else
		pquerier->start(eDB_PROVIDER::MYSQL, "www.cgcii.co.kr"sv, "test_user"sv, "1234"sv, "test_db"sv); // MySQL
	#endif
	}
	catch (throwable::failure_ex& _e)
	{
		// 실패시 exception이 발생하며 절달되는 throwable::failure_ex에 오류 정보가 들어 있다.

		// @ stream으로 출력시키려고 할 경우 - stream 객체로 >> 해준다.
		_e >> std::cout;

		// @ log로 남기고 싶을 경우 - log 객체를 바로 얻어서 log로 남길 수 있다.
		_log(nullptr, _e.get_log_record());

		// return) 
		return 0;
	}


	// ------------------------------------------------------------------
	//
	// B. 기본적 쿼리
	//
	//    - 요청한 쿼리가 완료될 때까지 블록킹된다.
	//    - execute_query 함수를 사용해 요청할 수 있다.
	//
	// ------------------------------------------------------------------
	try
	{
		// @1) 동기식 query를 요청한다.
		auto pquery = pquerier->execute_query("SELECT * FROM test_table"sv);

		// @2) query 결과를 읽어 들인다.
		auto result = pquery->move_first();

		// - 완료될 때까지 반복한다.
		while (result == eRESULT::SUCCESS)
		{
			// @3) 결과는 get_value<T>(index) 함수를 사용해 얻을 수 있다.
			//     T는 해당 칼럼의 자료형으로 DB의 자료형과 맵핑되는 형태를 써넣어야 한다.
			//     index는 칼럼의 index값으로 1부터 시작한다. (0번은 일반적으로 bookmark에 할당된다.)
			auto value_01 = pquery->result().get_value<bool>(1);				// bool
			auto value_02 = pquery->result().get_value<std::string, char*>(2); // char
			auto value_03 = pquery->result().get_value<std::wstring_view, char16_t*>(3); // nchar
			auto value_04 = pquery->result().get_value<int32_t>(4);				// int
			auto value_05 = pquery->result().get_value<int64_t>(5);				// bigint
			auto value_06 = pquery->result().get_value<float>(6);				// float
			auto value_07 = pquery->result().get_value<double>(7);				// real
			auto value_08 = pquery->result().get_value<chrono::time::time_point>(8); // datatime2
			auto value_09 = pquery->result().get_value<chrono::time::time_point>(9); // timestamp

			// - print~
			std::cout << "value_01 "sv << value_01 << '\n';
			std::cout << "value_02 "sv << value_02 << '\n';
			std::wcout << L"value_03 "sv << value_03 << L'\n'; // linux에서는 std::cout와 std::wcout을 썩어 사용하면 한글이 제대로 출력 안됨.
			std::cout << "value_04 "sv << value_04 << '\n';
			std::cout << "value_05 "sv << value_05 << '\n';
			std::cout << "value_06 "sv << value_06 << '\n';
			std::cout << "value_07 "sv << value_07 << '\n';
			std::cout << "value_08 "sv << to_string<char>(value_08) << '\n';
			std::cout << "value_09 "sv << to_string<char>(value_09) << '\n';

			// - 다음 row로...
			result = pquery->move_next();
		}
	}
	catch (throwable::failure_ex& _e)
	{
		// - error string을 출력한다.
		_e >> std::cout;
	}

	// return)
	return 0;
}
