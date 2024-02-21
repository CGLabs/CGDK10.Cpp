//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                tutorials query.ex - rdb.initialize_querier                *
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
	// 1. querier 객체의 초기화
	// ------------------------------------------------------------------
	own_ptr<query::rdb::querier_t> pquerier = make_own<query::rdb::querier_t>();

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
		_e >> std::cout;
		_log(nullptr, _e.get_log_record());
		return 0;
	}

	// ------------------------------------------------------------------
	//
	// 2. 구조체 get_value
	//
	//    1) 구조체를 이용해 한번에 하나의 row를 통으로 읽어낼 수 있다.
	//      그러기 위해서는    
	// 
	//      - 읽어낼 각 colume에 맞춰 구조체를 정의한다.
	//      - 구조체에 'ENABLE_STRUCT_SERIALIZABLE'를  추가한다.
	//      - get_value에 템플릿 인자로 그 구조체를 넣어 row를 읽어낸다.
	//    
	// ------------------------------------------------------------------

	// @ query 결과 row에 맞춰 정의한 구조체!
	struct TEST_RESULT
	{
		ENABLE_STRUCT_SERIALIZABLE

		bool					 v1;
		std::string				 v2;
		std::wstring			 v3;
		int32_t					 v4;
		int64_t					 v5;
		float					 v6;
		double					 v7;
		chrono::time::time_point v8;
		chrono::time::time_point v9;
	};

	try
	{
		// 1) 동기식 query를 요청한다.
		auto pquery = pquerier->execute_query("SELECT * FROM test_table"sv);

		// 2) query 결과를 읽어 들인다.
		auto result = pquery->move_first();

		// 3) get_value로 결과를 읽어낸다.
		while (result == eRESULT::SUCCESS)
		{
			// @ 결과는 get_value<TEST_RESULT>(1) 로 읽어낸다.
			//   ordinal 값은 시작하는 colume의 위치로 1로 설정하면 제일 앞에서 부터 읽어낸다.
			auto value = pquery->result().get_value<TEST_RESULT>(1);

			// - print~
			std::cout << "value_01 "sv << value.v1 << '\n';
			std::cout << "value_02 "sv << value.v2 << '\n';
			std::wcout << L"value_03 "sv << value.v3 << L'\n'; // linux에서는 std::cout와 std::wcout을 썩어 사용하면 한글이 제대로 출력 안됨.
			std::cout << "value_04 "sv << value.v4 << '\n';
			std::cout << "value_05 "sv << value.v5 << '\n';
			std::cout << "value_06 "sv << value.v6 << '\n';
			std::cout << "value_07 "sv << value.v7 << '\n';
			std::cout << "value_08 "sv << to_string<char>(value.v8) << '\n';
			std::cout << "value_09 "sv << to_string<char>(value.v9) << '\n';

			// - 다음 row로...
			result = pquery->move_next();
		}
	}
	catch (throwable::failure_ex& _e)
	{
		// - error string을 출력한다.
		_e >> std::cout;
	}

	// ------------------------------------------------------------------
	//
	// B. get_result
	//
	//    1) get_result와 구조체를 사용해 전체 row들을 통채로 읽을 수 있다.
	//    2) 결과는 std;;vector<T>로 리턴된다.
	//
	// ------------------------------------------------------------------
	try
	{
		// 1) 동기식 query를 요청한다.
		auto pquery = pquerier->execute_query("SELECT * FROM test_table"sv);

		// @2) row들은 std::vector<TEST_RESULT>에 넣어져 리턴한다.
		auto values = pquery->get_result<TEST_RESULT>();

		// - print
		for(auto iter: values)
		{
			// - print~
			std::cout << "value_01 "sv << iter.v1 << '\n';
			std::cout << "value_02 "sv << iter.v2 << '\n';
			std::wcout << L"value_03 "sv << iter.v3 << L'\n'; // linux에서는 std::cout와 std::wcout을 썩어 사용하면 한글이 제대로 출력 안됨.
			std::cout << "value_04 "sv << iter.v4 << '\n';
			std::cout << "value_05 "sv << iter.v5 << '\n';
			std::cout << "value_06 "sv << iter.v6 << '\n';
			std::cout << "value_07 "sv << iter.v7 << '\n';
			std::cout << "value_08 "sv << to_string<char>(iter.v8) << '\n';
			std::cout << "value_09 "sv << to_string<char>(iter.v9) << '\n';
		}
	}
	catch (throwable::failure_ex& _e)
	{
		// - error string을 출력한다.
		_e >> std::cout;
	}

}
