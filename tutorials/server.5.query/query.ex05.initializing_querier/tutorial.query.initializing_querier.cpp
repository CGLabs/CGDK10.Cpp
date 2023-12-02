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
	// A. querier - 인자별로 전달
	//    1) provider, dsn, uid, pwd, catalog,option 등 6개의 
	//       파라미터로 각각 전달하여 초기화할 수도 있다.
	// ------------------------------------------------------------------
	{
		// @1) queirier 객체를 생성한다.
		auto pquerier = make_own<query::rdb::querier_t>();

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
	}

	// ------------------------------------------------------------------
	// 2. querier - 초기화 문자열 사용
	//    1) 모든 정보를 하나의 문자열로 전달한다.
	// ------------------------------------------------------------------
	{
		// @1) queirier 객체를 생성한다.
		auto pquerier = make_own<query::rdb::querier_t>();

		// @2) querier 시작 - 파레미터를 넘겨서 초기화
		//     - 첫번째 파라미터 => eDB_PROVIDER::SQL_SERVER, eDB_PROVIDER::MYSQL 등등...
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
	}

}
