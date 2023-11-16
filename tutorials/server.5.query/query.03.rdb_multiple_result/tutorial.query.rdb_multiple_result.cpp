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

// option) SQL Server에 접속할 것인가? MySQL에 접속할 것인가?
#define _SQL_SERVER

#include <iostream>

// * CGDK header file
#include "cgdk/sdk10/server.query.rdb.h"

// * namespace CGDK
using namespace CGDK;


int main()
{
	// 1) alloc querier object
	auto pquerier = make_own<query::rdb::querier_t>();

	// 2) start querier
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
		// - error string을 출력한다.
		_e >> std::cout;

		// return) 
		return 0;
	}


	// ------------------------------------------------------------------
	//
	// A. 다중 쿼리 와 다중 result 읽어내기
	//
	//    - 한번의 쿼리로 여러개의 결과가 전달되는 경우를 말한다.
	//
	//    - 다중 쿼리는 일반적으로 프로시져에서 결과가 여러개가 나올 경우
	//      혹은 여러 문장을 한번에 쿼리할 경우를 말한다.
	//
	//    - 다중 쿼리 문장을 사용하고자 할 경우에는 ms sqlserver의 경우 
	//      기본 기능이고 mysql일 경우 odbc에서 다중결과를 허용하게 옵션을
	//      설정해줘야 한다.
	//
	// ------------------------------------------------------------------
	try
	{
		// @3) 동기식 query를 요청한다.
		auto pquery = pquerier->execute_query("SELECT * FROM test_table; SELECT * FROM test_table; SELECT * FROM test_table;"sv);

		// @3) 첫번째 result를 읽어낸다.
		for(auto iter : *pquery)
		{
			auto value_01 = iter.get_value<bool>(1);
			auto value_02 = iter.get_value<std::string_view>(2);
			auto value_03 = iter.get_value<std::wstring_view>(3);

			// - print~
			std::cout << "value_01 "sv << value_01 << '\n';
			std::cout << "value_02 "sv << value_02.data() << '\n';
			std::wcout << L"value_03 "sv << value_03.data() << L'\n';
		}

		// @4) 두번째 result로~
		pquery->get_next_result();

		// @5) 두번째 result를 얻는다.
		for(auto iter : *pquery)
		{
			auto value_02 = iter.get_value<char*>(1);
			auto value_03 = iter.get_value<int>(2);

			// - print~
			std::cout << "value_02 "sv << value_02 << '\n';
			std::cout << "value_03 "sv << value_03 << '\n';
		}

		// @6) 세번째 result로~
		pquery->get_next_result();

		// @7) 두번째 result를 얻는다.
		for (auto iter : *pquery)
		{
			auto value_01 = iter.get_value<int>(1);
			auto value_02 = iter.get_value<chrono::time::time_point>(2);
			auto value_03 = iter.get_value<std::string_view>(3);

			// - print~
			std::cout << "value_01 "sv << value_01 << '\n';
			std::cout << "value_02 "sv << to_string<char>(value_02) << '\n';
			std::cout << "value_03 "sv << value_03 << '\n';
		}
	}
	catch (throwable::failure_ex& _e)
	{
		// - error string을 출력한다.
		_e >> std::cout;

		// return) 
		return 0;
	}

	// return)
	return 0;
}
