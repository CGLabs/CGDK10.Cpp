//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                      tutorials query - redis.simple                       *
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
// * standard header file
#include <iostream>
#ifdef _WIN32
	#include <conio.h>
#endif

// * CGDK header file
#include "cgdk/sdk10/server.query.redis.h"

// * CGDK
using namespace CGDK;


void printf_redis_result(const resp_data& _result);

int main()
{
	//-----------------------------------------------------------------
	// 1. redis querier의 초기화.
	//-----------------------------------------------------------------
	// 1) redis querier를 생성한다.
	auto pquerier = make_object<query::redis::querier_t>();

	// 2) redis querier를 시작한다. (ip의 기본값은 'localhost:6379' 이다.)
	pquerier->start();

	// 설명) redis의 주소를 써넣으려면 socket과 동일하게 end_point를
	//       써넣으면 된다.
	//
	// 1. address만 설정하고 기본 포트로 접속하고자 할 경우.
	//
	//     // "127.0.0.1:6379"
	//     pquerier->start({ net::ip::make_address_v4("127.0.0.1") });
	//
	// 2. address와 port를 모두 설정할 경우
	//    
	//     // "127.0.0.1:1000"
	//     pquerier->start({ net::ip::make_address_v4("127.0.0.1"), 1000 });
	//

	//-----------------------------------------------------------------
	// 2. redis에 query를 동기적으로 요청한다.
	//-----------------------------------------------------------------
	try
	{
		// 1) 연결해서 또 쿼리를 한다.
		auto pquery = pquerier->execute_query("set users:1 world"sv);

		// 2) 결과 출력
		printf_redis_result(pquery->result());
	}
	catch (...)
	{
		std::cout << "redis query failed!"sv << '\n';
	}


	//-----------------------------------------------------------------
	// 3. redis에 query를 비동기적으로 처리한다.
	//-----------------------------------------------------------------
	try
	{
		// 1) 연결해서 또 쿼리를 한다.
		pquerier->post_execute_query("get users:1"sv, [=](auto _pquery)
		{
			printf_redis_result(_pquery->result());
		});
	}
	catch (...)
	{
		std::cout << "redis query failed!"sv << '\n';
	}



	//-----------------------------------------------------------------
	// 4. query 객체를 먼저 얻어서 처리하기.
	//    - execute_query나 post_execute_query를 할 경우 매번 다른 
	//      query sesssion을 얻게 된다. 따라서 같은 session을 유지해야 하는
	//      command일 경우 query 객체를 먼저 얻은 후 처리를 요청한다.
	//
	//    (!주의) 한번 query한 객체를 다시 쿼리하기 위해서는 반드시
	//            close_query를 호출해 닫아줘야 한다.
	//-----------------------------------------------------------------
	try
	{
		// 1) query 객체를 얻는다.
		auto pquery = pquerier->alloc_query();

		// 2) 첫번째 query를 실행한다.
		pquery->execute_query("set users:1 alloc_query_test!"sv);

		// 3) 결과 출력
		printf_redis_result(pquery->result());

		// 4) 첫번재 query를 닫는다.
		pquery->close_query();


		// 5) 두번째 query를 실행한다.
		pquery->execute_query("get users:1"sv);

		// 6) 결과 출력
		printf_redis_result(pquery->result());

		// 설명) 두번째 query는 close_query를 하지 않아도 자동 호출된다.
		//       query 객체가 할당 하제되면 close_query()는 자동 호출된다.
	}
	catch (...)
	{
		std::cout << "redis query failed!"sv << '\n';
	}


	//-----------------------------------------------------------------
	// 5. query 객체를 할당받아 query 객체를 먼저 비동기적으로 쿼리
	//    ( 쿼리 완료 후 다른 처리가 필요할 경우)
	//-----------------------------------------------------------------
	try
	{
		// 1) query 객체를 얻는다.
		auto pquery = pquerier->alloc_query();

		// 2) 비동기적으로  query를 실행한다.
		pquery->post_execute_query("set users:1 alloc_query_test!"sv, [=]()
		{
			printf_redis_result(pquery->result());
		});
	}
	catch (...)
	{
		std::cout << "redis query failed!"sv << '\n';
	}



	//-----------------------------------------------------------------
	// 6. query 객체를 할당받아 query 객체를 먼저 비동기적으로 쿼리
	//    - 쿼리 완료 후 다른 처리가 필요 없을 경우 람다함수만 넣지 않으면 된다.
	//-----------------------------------------------------------------
	try
	{
		// 1) query 객체를 얻는다.
		auto pquery = pquerier->alloc_query();

		// 2) 비동기적으로  query를 실행한다.
		pquery->post_execute_query("set users:1 alloc_query_test!"sv);
	}
	catch (...)
	{
		std::cout << "redis query failed!"sv << '\n';
	}



	//-----------------------------------------------------------------
	// 7. query 객체로 여러 비동기 요청 처리하기
	//    - 비동기적으로는 여러 쿼리를 연속적으로 처리할 수 있다.
	//-----------------------------------------------------------------
	try
	{
		// 1) query 객체를 얻는다.
		auto pquery = pquerier->alloc_query();

		// 2) 첫번째 query를 실행한다.
		pquery->post_execute_query("set users:3 alloc_query_test!"sv);

		// 3) 두번째 query를 실행한다.
		pquery->post_execute_query("get users:3"sv, [=]()
		{
			printf_redis_result(pquery->result());
		});

		// 4) 세번째 query를 실행한다.
		pquery->post_execute_query("get users:4"sv, [=]()
		{
			printf_redis_result(pquery->result());
		});
	}
	catch (...)
	{
		std::cout << "redis query failed!"sv << '\n';
	}



	//-----------------------------------------------------------------
	// 7. executor의 post를 사용해서 redis의 비동기 처리도 가능하다.
	//
	//-----------------------------------------------------------------
	system_executor::post(make_executable([=]()
	{
		// 1) query를 할당받는다.
		auto pquery = pquerier->alloc_query();

		// 2) 연결해서 또 쿼리를 한다.
		pquery->execute_query("set users:1 world"sv);

		// 3) 결과 출력
		printf_redis_result(pquery->result());

		// 4) query를 닫는다.
		pquery->close_query();


		// 5) 또 쿼리
		pquery->execute_query("get users:1"sv);

		// 6) 결과 출력
		printf_redis_result(pquery->result());
	}));


	// 아무키나 누를 때까지 대기한다.
	_getch();

	// return)
	return 0;
}

void printf_redis_result(const resp_data& _result)
{
	// check) 모두 비어 있으면 empty를 출력하게 한다.
	if(_result.is_failed())
	{
		std::cout << "(failed)\n"sv;
		return;
	}

	// 1) result를 출력한다.
	std::cout << _result.str_value << '\n';

	// 2) 전체 Result를 출력한다.
	for(auto& iter: _result.vector_child)
	{
		printf_redis_result(iter);
	}
}
