#include "cgdk/sdk10/net.socket.h"
#include "../../define_message.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;


class socket_tcp : public net::socket::tcp<>
{
private:
	virtual void		on_connect() override								{ std::cout << " @ connected"sv << '\n'; }
	virtual void		on_disconnect(uint64_t) override					{ std::cout << " @ disconnected"sv << '\n'; }
	virtual result_code	on_message(sMESSAGE_NETWORK& /*_msg*/) override		{ std::cout << " message received"sv << '\n'; return 0; }
};																	  
																	  
class socket_tcp_client : public net::socket::tcp_client<>
{
public:
	explicit socket_tcp_client(std::string_view _name) : net::socket::tcp_client<>(_name) {}

private:
	virtual void		on_request_connect(const net::sockaddr&) override	{ std::cout << " @ request connect"sv << '\n'; }
	virtual void		on_connect() override								{ std::cout << " @ connected"sv << '\n'; }
	virtual	void		on_fail_connect(uint64_t) override					{ std::cout << " @ fail to connecting"sv << '\n'; }
	virtual void		on_disconnect(uint64_t) override					{ std::cout << " @ disconnected"sv << '\n'; }
	virtual result_code	on_message(sMESSAGE_NETWORK& /*_msg*/) override		{ std::cout << " message received"sv << '\n'; return 0; }
};																	  

int main()
{
	// trace) 
	std::cout << "start server [tut.socket.03.tcp_configure.server]..." << '\n';

	// ------------------------------------------------------------------
	//
	// 1. 기본적인 방법 (basic Method)
	//
	//   Istartable 인터페이스를 가진 객체들은 
	//   start함수에 바로 context를 사용한 파라메터를 넣어서 초기화 할 수 있다.
	//
	// ------------------------------------------------------------------
	{
		// trace)
		std::cout << " example 01...start"sv << '\n';

		// 1) 각 객체에 이름을 설정하여 생성한다.
		auto pacceptor = make_own<net::acceptor<socket_tcp>>();

		// 2) acceptor의 파라메터를 설정한다.
		context	param;
		param["local_endpoint"sv]["port"sv] = 20000;

		// 3) start한다.
		pacceptor->start(param);

		// 4) 아무키나 누를 때까지 대기한다.
		_getch();

		// trace)
		std::cout << " example 01...end"sv << '\n';
	}


	// ------------------------------------------------------------------
	//
	// 2. 동시에 여러 객체 초기화하기
	//
	//  context를 사용해 한꺼번에 여러 객체를 초기화할 수 있다.
	//  계층 구조를 가진 객체도 한번에 값을 전달해 초기화할 수 있다.
	//
	// ------------------------------------------------------------------
	{
		// trace)
		std::cout << " example 02...start"sv << '\n';

		// 1) 각 객체에 이름을 설정하여 생성한다.
		auto pacceptor_a = make_own<net::acceptor<socket_tcp>>("bar"sv);
		auto pacceptor_b = make_own<net::acceptor<socket_tcp>>("foz"sv);
		auto psocket_client_c = make_own<socket_tcp_client>("taz"sv);

		// declare) 설정값을 전달할 sMESSAGE_CONTEXT 객체를 선언한다.
		context	param;

		// 2) "baz", "foz", "taz"에 전달할 파라미터를 설정한다.
		param["bar"sv]["local_endpoint"sv]["port"sv]	 = 22010;

		param["foz"sv]["local_endpoint"sv]["address"sv]	 = "127.0.0.1"sv;
		param["foz"sv]["local_endpoint"sv]["port"sv]	 = 22020;
		param["foz"sv]["prepare_on_start"sv]			 = 256;

		param["taz"sv]["remote_endpoint"sv]["address"sv] = "127.0.0.1"sv;
		param["taz"sv]["remote_endpoint"sv]["port"sv]	 = 22020;

		// 3) context를 start시 전달해 start한다.
		pacceptor_a->start(param);
		pacceptor_b->start(param);
		psocket_client_c->start(param);

		// 4) 아무키나 누를 때까지 대기한다.
		_getch();

		// trace)
		std::cout << " example 02...end"sv << '\n';
	}


	// ------------------------------------------------------------------
	//
	// 3. JSON 포맷을 사용해 초기화하기
	//    
	//    JSON을 사용해 context에 값을 설정하는 기능을 제공해준다.
	// ------------------------------------------------------------------
	{
		// trace)
		std::cout << " example 03...start"sv << '\n';

		// 1) 각 객체에 이름을 설정하여 생성한다.
		auto pacceptor_a  = make_own<net::acceptor<socket_tcp>>("bar"sv);
		auto pacceptor_b  = make_own<net::acceptor<socket_tcp>>("foz"sv);
		auto psocket_client_c = make_own<socket_tcp_client>("taz"sv);

		// 2) 설정할 JSON 내용
		// definitions) JSON string
		//
		// {
		//   "bar": {
		//     "local_endpoint": {
		//       "port": 22010
		//     }
		//   },
		// 
		//   "foz": {
		//     "local_endpoint": {
		//       "address": "127.0.0.1",
		//       "port": 22020
		//     },
		//     "prepare_on_start": 256
		//   },
		// 
		//   "taz": {
		//     "connection": {
		//       "x1": {
		//         "remote_endpoint": {
		//           "address": "127.0.0.1",
		//           "port": 22020
		//         }
		//       },
		// 
		//       "x2": {
		//         "remote_endpoint": {
		//           "address": "127.0.0.1",
		//           "port": 22030
		//         }
		//       }
		//     }
		//   }
		// }
		//
		std::string_view str_json = "{\"bar\": {\"local_endpoint\": {\"port\": 22010}},\"foz\": {\"local_endpoint\": {\"address\": \"127.0.0.1\",\"port\" : 22020},\"prepare_on_start\" : 256},\"taz\": {\"connection\": {\"x1\": {\"remote_endpoint\": {\"address\": \"127.0.0.1\",\"port\" : 22030}},\"x2\": {\"remote_endpoint\": {\"address\": \"127.0.0.1\",\"port\" : 22040}}}}}"sv;

		// declare)
		context	param;

		// 2) jsoin string에서 설정을 읽어들여 context 객체에 넣는다.
		param.read_from_json_string(str_json);

		// 3) context로 여러 객체의 파라미터값을 전달해 start한다.
		pacceptor_a->start(param);
		pacceptor_b->start(param);
		psocket_client_c->start(param);

		// 4) 아무키나 누를 때까지 대기한다.
		_getch();

		// trace)
		std::cout << " example 03...end"sv << '\n';
	}


	// ------------------------------------------------------------------
	//
	// 4. context를 사용한 통합 초기화 (4) - JSON file
	//
	// ------------------------------------------------------------------
	{
		// trace)
		std::cout << " example 04...start"sv << '\n';

		// 1) 각 객체에 이름을 설정하여 생성한다.
		auto pacceptor_a = make_own<net::acceptor<socket_tcp>>("bar"sv);
		auto pacceptor_b = make_own<net::acceptor<socket_tcp>>("foz"sv);
		auto psocket_client_c = make_own<socket_tcp_client>("taz"sv);

		// Declare)
		context	param;

		// 2) JSON 파일에서 읽어 들인다.
		param.read_from_json_file("param.json"sv);

		// 3) msg_context에 설정된 내용대로 start한다.
		pacceptor_a->start(param);
		pacceptor_b->start(param);
		psocket_client_c->start(param);

		// 4) 아무키나 누를 때까지 대기한다.
		_getch();

		// trace)
		std::cout << " example 04...end"sv << '\n';
	}

	// trace) 
	std::cout << "stop server [tut.socket.03.tcp_configure.server]..."sv << '\n';

	// Return) 종료
	return 0;
}
