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
//#define _SQL_SERVER

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
	// 설명 parameter 
	//
	//  1. BIND SQL문을 사용한 query
	//    query 문장을 직접 작성하는 것보다 ?로 값을 BIND하여 전달하는 방식의
	//    쿼리입니다.
	// 
	//    - 빈번히 사용되는 쿼리의 경우 매번 구조적으로는동일하며 일부
	//      파라미터에 해당하는 값만 다른 쿼리라도 Literal SQL문으로
	//      작성할 경우 성능에 많은 손실을 가져올 수 있습니다.
	//      soft parsing의 이익의 얻어 성능의 최적화를 위해서는 SQL 원문이 
	//      문자적으로 동일해야 합니다.
	//      따라서 SQL문을 매번 직접 작성하는 liberal SQL방식은 soft parsing을
	//      적용 받을 가능성이 낮아집니다.
	//      빈번한 쿼리는 직접 SQL문을 넣는 것보다 BIND SQL방식의 query가
	//      훨씬 좋은 효율을 낼 수 있습니다.
	//      특히 작고 빈번한 SQL의 경우 BIND SQL 방식은 더욱 효율적일 수 있습니다.
	//
	//  2. BIND SQL 방법
	//     - 본쿼리를 하기전에 일반 query문을 먼저 prepare_query()로 준비요청합니다.
	//     - prepare_query()가 성공하면 set_param()함수로 인자와 값을 BIND해줍니다.
	//     - query문 장 중에 ?의 만큼 set_param함수를 호출해 값을 설정해줍니다.
	//     - 인자의 설정이 끝나면 execute()함수를 호출해 쿼리를 실행합니다.
	//     - query가 성공적으로 완료되었다면 output 인자는 get_param함수를 사용해
	//       값을 얻어올 수 있습니다.
	//   
	// ------------------------------------------------------------------

	// ------------------------------------------------------------------
	//
	// A. 동기식 쿼리
	//
	//    - 요청한 쿼리가 완료될 때까지 블록킹된다.
	//    - execute_query 함수를 사용해 요청할 수 있다.
	//
	// ------------------------------------------------------------------
	try
	{
		// @1) 먼저 query를 repare한다.
	#if defined(_SQL_SERVER)
		auto pquery = pquerier->prepare_query<query::rdb::query_param_t>("{CALL test_procedure (?,?,?)}"sv); // SQL server의 경우: procedure call을 위해 {}를 해줘야 한다.
	#else
		auto pquery = pquerier->prepare_query<query::rdb::query_param_t>("CALL test_procedure (?,?,?)"sv); // MySQL의 경우: procedure call에 {}가 있으면 안됀다.
	#endif

		// @2) parameter를 설정한다.
		pquery->set_param<int>				(1, 40);		// 첫번째 parameter
		pquery->set_param<std::string_view>	(2, "apple"sv);	// 두번째 parameter
		pquery->set_param<float>			(3, 0.10f);		// 세번째 parameter

		// @3) query를 얻는다.
		pquery->execute_query();

		// @4) 완료될 때까지 반복한다.
		for (auto iter : *pquery)
		{
			auto value_01 = iter.get_value<bool>(1);
			auto value_02 = iter.get_value<std::string, char*>(2);
			auto value_03 = iter.get_value<std::wstring_view, char16_t*>(3);
			auto value_04 = iter.get_value<int32_t>(4);
			auto value_05 = iter.get_value<int64_t>(5);
			auto value_06 = iter.get_value<float>(6);
			auto value_07 = iter.get_value<double>(7);
			auto value_08 = iter.get_value<chrono::time::time_point>(8);
			auto value_09 = iter.get_value<chrono::time::time_point>(9);

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
		}
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
	// B. 비동기식 쿼리
	//
	//    - 쿼리를 요쳥하면 비동기적으로 쿼리를 한 후 결과는 비동기적으로
	//      처리된다.
	//
	//    - 쿼리가 완료된 후 파라미터로 전달한 호출될 람다 함수를 설정한다.
	//    
	// ------------------------------------------------------------------
	// @1) 먼저 query를 할당 받는다.
	pquerier->post_alloc_session([=](query::rdb::session_t* _psession)
	{
		// check)
		RETURN_IF(_psession == nullptr,);

		// 1) query 객체를 할당 받는다.
		auto pquery = _psession->alloc_query<query::rdb::query_param_t>();

		try
		{
			// @2) 먼저 query를 repare한다.
		#if defined(_SQL_SERVER)
			pquery->prepare_query("{CALL test_procedure (?,?,?) }"sv);
		#else
			pquery->prepare_query("CALL test_procedure (?,?,?) "sv);
		#endif

			// @3) parameter를 설정한다.
			pquery->set_param<int> (1, 50);						// 첫번째 parameter
			pquery->set_param<std::string_view> (2, "apple"sv);	// 두번째 parameter
			pquery->set_param<float> (3, 0.1f);					// 세번째 parameter

			// @4) query를 얻는다.
			pquery->execute_query();

			// @5) 결과를 읽어들인다.
			for (auto iter : *pquery)
			{
				auto value_01 = iter.get_value<bool>(1);
				auto value_02 = iter.get_value<std::string, char*>(2);
				auto value_03 = iter.get_value<std::wstring_view, char16_t*>(3);
				auto value_04 = iter.get_value<int32_t>(4);
				auto value_05 = iter.get_value<int64_t>(5);
				auto value_06 = iter.get_value<float>(6);
				auto value_07 = iter.get_value<double>(7);
				auto value_08 = iter.get_value<chrono::time::time_point>(8);
				auto value_09 = iter.get_value<chrono::time::time_point>(9);

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
			}
		}
		catch (throwable::failure_ex& _e)
		{
			// - error string을 출력한다.
			_e >> std::cout;
		}
	});

	// return)
	return 0;
}
