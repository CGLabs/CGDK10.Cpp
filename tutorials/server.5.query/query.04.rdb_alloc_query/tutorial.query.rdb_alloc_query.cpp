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

	try
	{
		// ------------------------------------------------------------------
		//
		// 2. alloc_session()는 왜 필요한가?
		//    - querier에 직접 execute_query를 수행하면 내부적으로 session을 
		//      할당받은 후 query객체를 생성하여 query를 수행할 수 있습니다.
		//    - session을 직접 할당받으면 할당 받은 session에서 qeury를 할당
		//      받아 query를 수행할 수 있다.
		//    - 한번의 session 할당으로 여러 개의 query 객체를 생성할 수 
		//      있으며 여러 번의 query를 수행할 수 있습니다.
		//    - 하나의 query 객체는 execute_query()를 요청 후 close_query()함수를
		//      사용해 query를 닫은 후 다시 execute_query()를 호출해 query를
		//      수행할 수 있습니다.
		//
		// ------------------------------------------------------------------
		{
			// 1) session을 할당받는다.
			auto psession = pquerier->alloc_session();

			// 2) query객체를 생성한다.
			auto pquery = psession->alloc_query();

			// 3) query를 수행한다.
			//    (실패하면 내부에서 exception을 던지므로 따로 리턴값을 검사할 필요는 없다.)
			pquery->execute_query("SELECT * FROM test_table"sv);

			// 4) for문을 사용해 query결과를 차례로 읽어들인다.
			for (auto& iter : *pquery)
			{
				// - Index로 Column값을 읽어들인다.(Column은 1부터 시작)
				auto value_1 = iter.get_value<bool>(1);
				auto value_2 = iter.get_value<char*>(2);
				auto value_3 = iter.get_value<wchar_t*>(3);

				// - print~
				std::cout << "value_1 "sv << value_1 << '\n';
				std::cout << "value_2 "sv << value_2 << '\n';
				std::wcout << L"value_3 "sv << value_3 << L'\n';
			}

			// 5) 처리가 끝냈으면 닫는다.
			pquery->close_query();

			// 6) 다음 query를 요청한다.
			pquery->execute_query("SELECT * FROM test_table"sv);

			// 7) for문을 사용해 query결과를 차례로 읽어들인다.
			for (auto& iter : *pquery)
			{
				// - Index로 Column값을 읽어들인다.(Column은 1부터 시작)
				auto value_1 = iter.get_value<bool>(1);
				auto value_2 = iter.get_value<char*>(2);
				auto value_3 = iter.get_value<wchar_t*>(3);

				// - print~
				std::cout << "value_1 "sv << value_1 << '\n';
				std::cout << "value_2 "sv << value_2 << '\n';
				std::wcout << L"value_3 "sv << value_3 << L'\n';
			}

			// 7) 쿼리를 닫는다.
			pquery->close_query();

			// 설명) query 객체가 소멸되면 자동적으로 할당 해제처리가 된다.
			//       session 객체는 생성한 모든 query객체가 할당 해제되고 
			//       자신이 할당해제되면 다시 querier로 돌아가 다음 할당을
			//       대기하게 된다.
		}


		// ------------------------------------------------------------------
		//
		// 3. 비동기식 post_alloc_session()
		//    - 비동기식 session 할당을 통해 다중 쓰레드 처리를 할수 있다.
		//    - poat_aaloc_session()을 호출할 경우 비동기식으로 session을
		//      할당 받은 후 설정된 lambda함수를 호출한다.
		//    - 많은 session의 할당 요구를 할 경우 session pool에 존재하는
		//      모든 session 객체가 모두 할당되는 경우 
		//      alloc_session()함수로 session 객체를 할당 요구할 경우 여유 session이
		//      다시 생기기 까지 대기해야 하는데 이때 blocking이 발생하게 된다.
		//      이런 경우 post_alloc_session을 사용하여 비동기적으로 할당받으면
		//      더욱 효율을 높일 수 있다.
		//
		// ------------------------------------------------------------------
		// 1) 비동기식 query 할당을 요구한다.
		pquerier->post_alloc_session([=](query::rdb::session_t* _psession)
		{
			// check) 할당받지 못했으면 _psession가 nullptr이 된다.
			RETURN_IF(_psession == nullptr,);

			// 1) alloc_query
			auto pquery = _psession->alloc_query<query::rdb::query_t>();
		
			// 2) query를 요청한다. (실패하면 내부에서 exception을 던진다.)
			pquery->execute_query("SELECT * FROM test_table"sv);

			// 3) for문을 사용해 Query결과를 차례로 읽어들인다.
			for (auto& iter : *pquery)
			{
				// - Index로 Column값을 읽어들인다.(Column은 1부터 시작)
				auto value_1 = iter.get_value<bool>(1);
				auto value_2 = iter.get_value<char*>(2);
				auto value_3 = iter.get_value<wchar_t*>(3);

				// - print~
				std::cout << "value_1 "sv << value_1 << '\n';
				std::cout << "value_2 "sv << value_2 << '\n';
				std::wcout << L"value_3 "sv << value_3 << L'\n';
			}

			// 4) 처리가 끝냈으면 닫는다.
			pquery->close_query();

			// 5) 다시 다른 query를 요청한다.
			pquery->execute_query("SELECT * FROM test_table"sv);

			// 6) for문을 사용해 Query결과를 차례로 읽어들인다.
			for (auto& iter : *pquery)
			{
				// - Index로 Column값을 읽어들인다.(Column은 1부터 시작)
				auto value_1 = iter.get_value<bool>(1);
				auto value_2 = iter.get_value<char*>(2);
				auto value_3 = iter.get_value<wchar_t*>(3);

				// - print~
				std::cout << "value_1 "sv << value_1 << '\n';
				std::cout << "value_2 "sv << value_2 << '\n';
				std::wcout << L"value_3 "sv << value_3 << L'\n';
			}

			// 7) 쿼리를 닫는다.
			pquery->close_query();
		});
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
