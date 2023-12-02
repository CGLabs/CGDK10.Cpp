//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                    tutorials query.ex - rdb transaction                   *
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
	// ------------------------------------------------------------------
	//
	// 설명 transaction
	//
	//   
	// ------------------------------------------------------------------

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

		// 1) query를 할당 받는다. (이때 session을 할당받는게 중요하다.)
		auto psession = pquerier->alloc_session();

		// check)
		CGASSERT_ERROR(psession.exist());

		// 2) scoped transaction
		scoped_transaction(psession)
		{
			auto pquery = psession->alloc_query();

			// - query를 실행한다.
			pquery->execute_query("INSERT INTO test(a,b,c) VALUES (1,2,3)");

			// - 또다른 query르 싫행한다.
			pquery->execute_query("INSERT INTO test(a,b,c) VALUES (4,5,6)");

			// 3) 완료! 
			commit;
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

