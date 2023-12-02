//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                      tutorials query - http.simple                        *
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
#include "cgdk/sdk10/server.query.http.h"

// * CGDK
using namespace CGDK;


void output_result(query::http::query* _query);

int main()
{
	try
	{
		// ------------------------------------------------------------------
		// 1. http querier
		//    - http querier는 특별한 설정이나 파라메터는 필요 없다.
		// ------------------------------------------------------------------
		// 1) querier를 생성한다.
		auto pquerier = make_object<query::http::querier_t>();

		// 2) querier를 start한다. (특별한 파라미터는 필요 없다.)
		pquerier->start();


		// ------------------------------------------------------------------
		// 2. 동기적으로 query를 수행한다.
		// ------------------------------------------------------------------
		{
			// 1) query::http::querier객체에 query를 요청하면 query::http::Cquery 객체를 돌려준다.
			auto pquery = pquerier->execute_query<query::http::query_t>("https://www.google.com"sv);

			// check) 실패시 pquery는 nullptr이 된다.
			if (pquery.empty())
				throw throwable::failure(eRESULT::FAIL);

			// 2) 결과를 출력한다.
			output_result(pquery);

			// 3) query를 닫는다.
			pquery->close_query();
		}


		// ------------------------------------------------------------------
		// 3. 비동기적으로 Query를 수행한다.
		// 
		//    - 비동기적으로 http query를 요청한다.
		//    - 비동기 http query의 경우 처리가 완료되지 않아도 즉시 함수가
		//      종료되며 처리가 완료된 후 Lambda 함수가 호출된다.
		// 
		// ------------------------------------------------------------------
		{
			// 1) query::http::querier객체에 query를 비동기적으로 요청한다.
			pquerier->post_execute_query<query::http::query_t>("https://www.naver.com"sv,
				[](result_code _result, query::http::query_t* _pquery)
			{
				// check) 실패일 경우 끝낸다.
				if (_result != eRESULT::SUCCESS)
					return;

				// 2) 결과를 출력한다.
				output_result(_pquery);

				// !주의) _pquery를 다시 query 요청하면 안된다.
				// 만약 요청하면 exception을 던진다.
				// 다시 쿼리를 할 경우 반드시 새로운 query객체를 할당받은 후 진행해야 한다.
			});
		}


		// ------------------------------------------------------------------
		// 4. query 객체를 먼저 할당받은 후 요청하기
		// ------------------------------------------------------------------
		{
			// 1) CGWeb::CHTTPRequest 객체를 생성한다.
			auto pquery = pquerier->alloc_query();

			// 2) CGWeb::CHTTPRequest 객체에 접속을 위한 URL을 설정해준다.
			pquery->execute_query("https://www.google.com"sv, eHTTP_METHOD::POST_);

			// 3) body를 출력한다.
			output_result(pquery);

			// 4) query를 닫는다.
			pquery->close_query();
		}
	}
	catch (...)
	{
		std::cout << "error!"sv;
	}


	// 아무키나 입력하길 기다린다.
	_getch();

	// return)
	return 0;
}

void output_result(query::http::query_t* _query)
{
	// 1) get result
	auto& result = _query->result();

	// 2) header 정보를 한줄씩 출력한다.
	{
		auto buf_temp = result.buf_head;
		for (std::string_view pstr = buf_temp.extract_text<char>('\n', (char)NULL); pstr.empty() == false; pstr = buf_temp.extract_text<char>('\n', (char)NULL))
		{
			std::cout << pstr << std::endl;
		}
	}

	// 3) context 정보를 한줄씩 출력한다.
	if(result.contents.empty() == false)
	{
		for (const auto& iter : result.contents)
		{
			auto buf_temp = iter;
			for (std::string_view pstr = buf_temp.extract_text<char>('\n'); pstr.data() != nullptr; pstr = buf_temp.extract_text<char>('\n'))
			{
				std::cout << pstr << std::endl;
			}
		}
	}
}
