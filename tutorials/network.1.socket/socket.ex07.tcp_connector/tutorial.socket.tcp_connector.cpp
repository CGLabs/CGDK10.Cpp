#include "cgdk/sdk10/net.socket.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

// 1) socket 클래스를 정의한다.
class socket_tcp_client : public net::socket::tcp_client<>
{
	// (v) 접속 시 호출되는 함수
	virtual void on_connect() override
	{
		std::cout << " @ connected"sv << '\n';
	}

	// (v) 접속 실패시 호출되는 함수
	virtual void on_fail_connect(uint64_t /*_disconnect_reason*/) override
	{
		std::cout << " @ fail to connecting"sv << '\n';
	}

	// (v) 접속 종료 시 호출되는 함수
	virtual void on_disconnect(uint64_t) override
	{
		std::cout << " @ disconnected"sv << '\n';
	}

	virtual result_code on_message(sMESSAGE_NETWORK& /*_msg*/) override
	{
		return eRESULT::DONE;
	}
};

int main()
{
	// trace) 
	std::cout << "start client [tut.socket.ex07.tcp_connector]..."sv << '\n';


	//-----------------------------------------------------------------------------
	//
	// 1. net::conntector<T>란...
	//
	//  대규모 접속을 해야할 경우 사용하는 객체이다.
	//  connector 객체를 생성후 request_connect를 호출하면 내부적으로 새로운 socket
	//  객체를 생성후 접속을 시도한다.
	//  connector 객체는 자신이 생성한 socket 객체를 관리하고 관련 통계 정보를 작성
	//  한다.
	//  
	//
	//  기본적인 사용 법은..
	// 
	// 	   1) connector객체에 템플릿 파라미터로 socket class를 인자로 넣어 생성한다.
	// 	      이 socket class는 접속 시도시 생성되는 socket 객체의 타입니다.
	//
	// 	   2) connector를 start()한다. 
	// 	      - start()한 이후부터 connector 객체를 사용할 수 있다.
	// 
	// 	   3) connector의 request_connect()함수를 사용해 접속을 시도한다.
	//        - 리턴값으로 접속시도하한 socket 객체가 돌아온다.
	// 
	// 	   4) connector를 파괴한다.
	// 	      - connector가 파괴될 때 모든 socket 객체의 접속 종료가 호출되고
	// 	        모든 socket 객체의 할당해제가 된후 종료된다.
	//
	//-----------------------------------------------------------------------------
	{
		// 1) 접속을 시도할 'socket_tcp_client' 소켓 객체를 생성한다.
		auto pconnector = make_own<net::connector<socket_tcp_client>>();

		// 2) connector를 시작한다.
		pconnector->start();

		// 3) 100개의 socket을 접속한다.
		for (int i = 0; i < 100; ++i)
		{
			// - connector에 접속을 요청한다.
			pconnector->request_connect({ net::ip::address_v4::loopback(), 20000 });
		}

		// 3) connector의 모든 socket을 닫는다.
		pconnector->close_connectable_all();

		// 4) connector를 파괴한다.
		pconnector->destroy();
	}
	//-----------------------------------------------------------------------------
	//
	// 2. context를 사용한 초기화.
	// 
	//  connector 객체의 start()시 접속할 주소를 리스트로 전달하면 start()시
	// 	바로 접속을 싣도하도록 할수 있다.
	// 	start()시 전달할 JSON에 "connection_list" 항목에 접속할 대상 이름과 그 주소를 나열하면 
	// 	start()시 접속 시도 된다.
	//
	// 	<<< "setting.json" 파일 >>>
	// 
	//	{
	//	  "connection_list": {
	//	    "socket.1": {
	//	      "remote_endpoint": {
	//	        "address": "127.0.0.1",
	//	        "port": 20000
	//	      }
	//	    },
	//	    "socket.2": {
	//	      "remote_endpoint": {
	//	        "address": "127.0.0.1",
	//	        "port": 20000
	//	      }
	//	    },
	//	    "socket.3": {
	//	      "remote_endpoint": {
	//	        "address": "127.0.0.1",
	//	        "port": 20010
	//	      }
	//	    }
	//	  }
	//	}
	//  
	//
	//-----------------------------------------------------------------------------
	{
		// 1) 접속을 시도할 'socket_tcp_client' 소켓 객체를 생성한다.
		auto pconnector = make_own<net::connector<socket_tcp_client>>();

		// 2) context에 접속 리스트를 전달하여 접속한다.
		context context_connector("setting.json"sv);

		// 3) connector를 시작한다.
		pconnector->start(context_connector);

		// ... 필요한 처리를 한다.

		// 4) 종료
		pconnector->destroy();
	}


	// 5) 아무 입력을 기다린다.
	_getch();

	// trace) 
	std::cout << "stop server [tut.socket.ex07.tcp_connector]..."sv << '\n';

	// end) 종료
	return 0;
}
