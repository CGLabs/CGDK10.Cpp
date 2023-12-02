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

// option) Windows�� ��� Native�� ����� ���ΰ� oledbȤ�� odbc�� ����� ���ΰ��� ������ �� �ִ�.
//         Linux�� ��� �⺻���� odbc �ۿ� ����� �� �����Ƿ� �� �ɼ��� ���õȴ�.
#define _USE_ODBC

// option) SQL Server�� ������ ���ΰ�? MySQL�� ������ ���ΰ�? �ּ�ó���ϸ� MySQL�� �����̵ȴ�.
#define _SQL_SERVER

#include <iostream>

// * CGDK header file
#include "cgdk/sdk10/server.query.rdb.h"

// * namespace CGDK
using namespace CGDK;


int main()
{
	// ------------------------------------------------------------------
	// ����) CGDK.10�� db query �ٽ� ��ü
	// 
	//   1) querier
	//      ���� ���� �����ؾ� �ϴ� ��ü�� odbc�� SQLHENV�� �ش��Ѵ�.
	//      �ʱ�ȭ�� �ϰ� �Ǹ� ���� ���� session�� ������ �����ϴ� �Ҵ����ش�.
	//      �ʱ�ȭ�� ���� �⺻������ �Ʒ� parameter�� �ʿ��ϴ�.
	// 
	//		- eDB_PROVIDER provider        : DB�� ������ �ǹ��Ѵ� MS SQL server Ȥ�� MySQL������ ���� �����Ѵ�.
	//                                       Mircosoft SQL Server => eDB_PROVIDER::SQL_SERVER
	//                                       MySQL => eDB_PROVIDER::MYSQL
	// 
	//		- std::string  data_source     : DB�� �����ϱ� ���� �ּ�. 
	//        
	//		- std::string  user_id         : DB�� �α����ϱ� ���� id
	//		- std::string  password        : DB�� �α��� �ϱ� ���� password
	//		- std::string  initial_catalog : DB catalog
	//      
	//   2) session
	//      - odbc�� SQLHDBC�� �ش��Ѵ�.
	//      - DB�� ������ �ǹ��Ѵ�. �Ϲ������� �ϳ��� querier�� �ټ��� session��
	//        �����Ѵ�.
	//      - querier�� session�� alloc_session() Ȥ�� post_alloc_session()�Լ��� 
	//        ����� �Ҵ���� �� �ִ�.
	// 
	//   3) query 
	//      - ODBC�� statement(SQLHSTMT)�� �ش��Ѵ�.
	//      - session�� �Ҵ� ���Ҵ������ query ��ü�� ������ ����� �� �ִ�.
	//      - querier�� 
	// 
	// 
	// ------------------------------------------------------------------
	// ------------------------------------------------------------------
	// A. querier ��ü�� �ʱ�ȭ
	//    1) querier�� provider, dsn, uid, pwd, catalog,option �� 6���� 
	//       �Ķ���ͷ� ���� �����Ͽ� �ʱ�ȭ�� ���� �ִ�.
	//    2) �ʱ�ȭ ���ڿ��� ��ä�� ������ �ټ��� �ִ�.
	//    3) context�� ����� �ʱ�ȭ�� ���� �ִ�.
	//   
	//    ���⼭�� 1)�� ������� �ʱ�ȭ�ϴ� ������ ���� �ش�.
	//
	// ------------------------------------------------------------------
	// @1) queirier ��ü�� �����Ѵ�.
	own_ptr<query::rdb::querier_t> pquerier = make_own<query::rdb::querier_t>();

	// @2) querier ���� - �ķ����͸� �Ѱܼ� �ʱ�ȭ
	//
	//     - ù��° �Ķ���� => eDB_PROVIDER::SQL_SERVER, eDB_PROVIDER::MYSQL ���...
	//     - �ι�° �Ķ���� => ������ DB�� �ּ� Ȥ�� DSN
	//     - ����° �Ķ���� => user id 
	//     - �׹�° �Ķ���� => password
	//     - �ټ���° �Ķ���� => initial_catalog Ȥ�� database
	//     - ������° �Ķ���� => options
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
		// ���н� exception�� �߻��ϸ� ���޵Ǵ� throwable::failure_ex�� ���� ������ ��� �ִ�.

		// @ stream���� ��½�Ű���� �� ��� - stream ��ü�� >> ���ش�.
		_e >> std::cout;

		// @ log�� ����� ���� ��� - log ��ü�� �ٷ� �� log�� ���� �� �ִ�.
		_log(nullptr, _e.get_log_record());

		// return) 
		return 0;
	}


	// ------------------------------------------------------------------
	//
	// B. �⺻�� ����
	//
	//    - ��û�� ������ �Ϸ�� ������ ���ŷ�ȴ�.
	//    - execute_query �Լ��� ����� ��û�� �� �ִ�.
	//
	// ------------------------------------------------------------------
	try
	{
		// @1) ����� query�� ��û�Ѵ�.
		auto pquery = pquerier->execute_query("SELECT * FROM test_table"sv);

		// @2) query ����� �о� ���δ�.
		auto result = pquery->move_first();

		// - �Ϸ�� ������ �ݺ��Ѵ�.
		while (result == eRESULT::SUCCESS)
		{
			// @3) ����� get_value<T>(index) �Լ��� ����� ���� �� �ִ�.
			//     T�� �ش� Į���� �ڷ������� DB�� �ڷ����� ���εǴ� ���¸� ��־�� �Ѵ�.
			//     index�� Į���� index������ 1���� �����Ѵ�. (0���� �Ϲ������� bookmark�� �Ҵ�ȴ�.)
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
			std::wcout << L"value_03 "sv << value_03 << L'\n'; // linux������ std::cout�� std::wcout�� ��� ����ϸ� �ѱ��� ����� ��� �ȵ�.
			std::cout << "value_04 "sv << value_04 << '\n';
			std::cout << "value_05 "sv << value_05 << '\n';
			std::cout << "value_06 "sv << value_06 << '\n';
			std::cout << "value_07 "sv << value_07 << '\n';
			std::cout << "value_08 "sv << to_string<char>(value_08) << '\n';
			std::cout << "value_09 "sv << to_string<char>(value_09) << '\n';

			// - ���� row��...
			result = pquery->move_next();
		}
	}
	catch (throwable::failure_ex& _e)
	{
		// - error string�� ����Ѵ�.
		_e >> std::cout;
	}

	// return)
	return 0;
}
