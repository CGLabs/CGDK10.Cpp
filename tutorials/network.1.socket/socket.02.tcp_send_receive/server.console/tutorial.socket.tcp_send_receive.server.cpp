#include "cgdk/sdk10/net.socket.h"
#include "../../define_message.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

// 1) socket 클래스를 정의한다.
class socket_tcp : public net::socket::tcp<>
{
	// (v) 접속 시 호출되는 함수
	virtual void on_connect() override;

	// (v) 접속 종료 시 호출되는 함수
	virtual void on_disconnect(uint64_t) override;

	// (v) 메시지를 수신했을 때 호출 되는 함수.
	virtual result_code on_message(sMESSAGE_NETWORK& _msg) override;
			void on_message_A(sMESSAGE_NETWORK& _msg);
			void on_message_B_1(sMESSAGE_NETWORK& _msg);
			void on_message_B_2(sMESSAGE_NETWORK& _msg);

	// 메시지를 전송하는 함수
			void send_message_MESSAGE_B_1();
			void send_message_MESSAGE_B_2();
			void send_message_MESSAGE_B_3();
};

void socket_tcp::on_connect()
{
	// trace)
	std::cout << " @ connected" << '\n';

	// (*) 'MESSAGE_A' message를 작성해 전송한다.
	//     - 기본형 구조체로 통채로 메시지를 작성해 전송하는 예제
	//     - 구조체를 사용해 간단히 작성가능하다.
	//     - 기본 자료형 뿐만 아니라 문자열, vector, list, map과 같은 복합 구조체도 가능하다.
	//     - 하지만 사용가능한 구조체 자체는 생성자가 정의되어 있거나 virtual 함수가 있어서는 안됀다.
	//       (생성자나 virtual 함수가 있는 구조체나 클래스의 경으 Ibuffer_serializable을 사용해 정의할 수 있다.)
	//     - 구조체를 사용한 다계층 구조체도 한번에 쓰고 읽을 수 있다.
	{
		sMESSAGE_A	message;
		//message.size = get_size_of<uint32_t>(message);
		message.type = eMESSAGE_TYPE::SEND_A;
		message.x			 = 0;
		message.y			 = 1;
		message.z			 = 10.0f;

		// - send!!
		send(make_shared_buffer(message));
	}

	// (*) 'MESSAGE_C' message를 작성해 전송한다. 
	//     - 구조체를 쓰지 않고 append만으로 메시지 작성하는 예제.
	//     - 구조체로 메시지를 작성하지 않더라도 append만으로 메시지를 작성할 수 있다.
	//     - 직접 메모리 버퍼를 할당해 append를 사용해 값을 써넣는다.
	//     - 제일 앞 4byte에 메시지의 길이를 써넣으야 하므로 메시지를
	//       모두 다 작성한 후 buf의 size()값을 front()함수를 사용해 써넣는다.
	{
		// - 100byte의 buffer를 할당받는다.
		auto buf = alloc_shared_buffer(100);

		// - append를 사용해 메시지를 작성해 넣는다.
		buf.append<uint32_t>();
		buf.append<uint32_t>(eMESSAGE_TYPE::SEND_C);
		buf.append<int>(200);
		buf.append<std::string_view>("test_message"sv);
		buf.append<std::wstring_view>(L"this is unicode"sv);

		// - 제일 앞 4byte에 메시지의 길이를 써넣는다.
		buf.front<uint32_t>() = static_cast<uint32_t>(buf.size()); // size 자리에 메시지 길이 넣는다.

		// - 작성된 메시지를 전송한다
		send(buf);
	}
}

void socket_tcp::on_disconnect(uint64_t)
{
	std::cout << " @ disconnected"sv << '\n';
}

result_code socket_tcp::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) message head를 읽습니다.
	auto msg_header = _msg.buf_message.front<sMESSAGE_HEADER>();

	// 2) message 종류에 따른 처리를 한다.
	switch (msg_header.type)
	{
	case	eMESSAGE_TYPE::SEND_A:
			on_message_A(_msg);
			break;

	case	eMESSAGE_TYPE::SEND_B:
			on_message_B_1(_msg);
			break;

	default:
			std::cout << " undefined message received"sv << '\n';
			break;
	}

	return eRESULT::DONE;
}

void socket_tcp::on_message_A(sMESSAGE_NETWORK& _msg)
{
	// - message를 읽어낸다.
	auto message = _msg.buf_message.front<sMESSAGE_A>();

	// trace) 
	std::cout << " 'eMESSAGE_TYPE::SEND_A' received"sv << message.x << '\n';

	// - echo 전송한다.(echo 전송은 받은 메시지를 그대로 전송하면 된다.)
	send(_msg.buf_message);
}

void socket_tcp::on_message_B_1(sMESSAGE_NETWORK& _msg)
{
	// 1) 전송되어온 메시지는 MSG 구조체의 buf_message에 들어 있습니다.
	auto buf_read = _msg.buf_message;

	// 2) 메시지의 길이를 읽어낸다. (4byte)
	auto size	 = buf_read.extract<uint32_t>();
	auto message = buf_read.extract<eMESSAGE_TYPE>();

	// 3) 메시지를 작성했던 순서와 동일하게 extrac<T>() 함수로 데이터들을 읽어냅니다.
	auto value_1 = buf_read.extract<int>(); // int형 값 100
	auto value_2 = buf_read.extract<std::string>(); // 문자열 "test_string"
	auto value_3 = buf_read.extract<std::vector<int>>(); // 10,20,30
	auto value_4 = buf_read.extract<std::map<int, std::string>>(); // 10,20,30


	// trace) 
	std::cout << " 'eMESSAGE_TYPE::SEND_B' received"sv << '\n';
	std::cout << "   size: "sv << size << '\n';
	std::cout << "   message: "sv << message << '\n';
	std::cout << "   value_1: "sv << value_1 << '\n';
	std::cout << "   value_2: "sv << value_2 << '\n';
	std::cout << "   value_3: {"sv; for(auto& iter: value_3) std::cout << iter << " "; std::cout << "}"sv << '\n';
	std::cout << "   value_4: {"sv; for (auto& iter: value_4) std::cout << "{"sv << iter.first << ","sv << iter.second << "},"sv; std::cout << "}"sv << '\n';

	// ----------------------------------------------
	//
	// result)
	// 
	// 'eMESSAGE_TYPE::SEND_B' received
	//   size: 78
	//   message: 33 
	//   value_1: 100
	//   value_2: test_string
	//   value_3: {10, 20, 30, }
	//   value_4: {{1,a}, {2,b}, {3,c}, }
	//
	// ----------------------------------------------
}

void socket_tcp::on_message_B_2(sMESSAGE_NETWORK& _msg)
{
	// ----------------------------------------------
	//
	//	struct sMESSAGE_HEADER
	//	{
	//		uint32_t			size;
	//		eMESSAGE_TYPE		type;
	//	
	//		ENABLE_STRUCT_SERIALIZABLE
	//	};
	//
	//	struct sMESSAGE_B : public sMESSAGE_HEADER
	//	{
	//		int							a = 0;
	//		std::string					b;
	//		std::vector<int>			c;
	//		std::map<int, std::string>	d;
	//	};
	//
	// ----------------------------------------------

	// 1) 전송되어온 메시지는 MSG 구조체의 buf_message에 들어 있습니다.
	auto buf_read = _msg.buf_message;

	// 2) 메시지를 구조체로 통으로 읽어낸다. (4byte)
	auto temp = buf_read.extract<sMESSAGE_B>();

	// trace) 
	std::cout << " 'eMESSAGE_TYPE::SEND_B' received"sv << '\n';
	std::cout << "   temp.size: "sv << temp.size << '\n';
	std::cout << "   temp.type: "sv << temp.type << '\n';
	std::cout << "   temp.a: "sv << temp.a << '\n';
	std::cout << "   temp.b: "sv << temp.b << '\n';
	std::cout << "   temp.c: {"sv; for(auto& iter: temp.c) std::cout << iter << ", "sv; std::cout << "}"sv << '\n';
	std::cout << "   temp.d: {"sv; for (auto& iter: temp.d) std::cout << "{"sv << iter.first << ","sv << iter.second << "},"sv; std::cout << "}"sv << '\n';

	// ----------------------------------------------
	//
	// result)
	// 
	// 'eMESSAGE_TYPE::SEND_B' received
	//   temp.size: 78
	//   temp.type: 33
	//   temp.a: 100
	//   temp.b: test_string
	//   temp.c: {10, 20, 30, }
	//   temp.d: {{1,a}, {2,b}, {3,c}, }
	//
	// ----------------------------------------------
}

void socket_tcp::send_message_MESSAGE_B_1()
{
	// temporary)
	std::vector<int> vec_test{ 10,20,30 };
	std::map<int, std::string> map_test{ {1, "a"s}, {2, "b"s}, {3, "c"s} };

	// 1) 200byte buffer를 할당받는다.
	auto buf_temp = alloc_shared_buffer(200);

	// 2) 메시지 헤더 4byte는 비워놓는다.
	buf_temp.append<uint32_t>();
	buf_temp.append<eMESSAGE_TYPE>(SEND_B);

	// 3) 메시지를 붙혀 넣는다.
	buf_temp.append<int>(100);
	buf_temp.append("test_string"s);
	buf_temp.append(vec_test);
	buf_temp.append(map_test);

	// 4) 비워 놓았던 제일 앞의 4byte에 버퍼의 길이를 써넣는다.
	buf_temp.front<uint32_t>() = static_cast<uint32_t>(buf_temp.size());

	// 5) 전송한다.
	send(buf_temp);
}

void socket_tcp::send_message_MESSAGE_B_2()
{
	// ----------------------------------------------
	//
	//	struct sMESSAGE_HEADER
	//	{
	//		uint32_t			size;
	//		eMESSAGE_TYPE		type;
	//	
	//		ENABLE_STRUCT_SERIALIZABLE
	//	};
	//
	//	struct sMESSAGE_B : public sMESSAGE_HEADER
	//	{
	//		int							a = 0;
	//		std::string					b;
	//		std::vector<int>			c;
	//		std::map<int, std::string>	d;
	//	};
	//
	// ----------------------------------------------

	// temporary)
	std::vector<int> vec_test{ 10,20,30 };
	std::map<int, std::string> map_test{ {1, "a"s}, {2, "b"s}, {3, "c"s} };

	// 1) 200byte buffer를 할당받는다.
	auto buf_temp = alloc_shared_buffer(200);

	// 2) 구조체를 선언하고 값을 써넣는다.
	sMESSAGE_B temp;
	//temp.size는 그냥 비워놓습니다.
	temp.type = SEND_B;
	temp.a = 100;
	temp.b = "test_string"s;
	temp.c = vec_test;
	temp.d = map_test;

	// 3) 구조체를 append로 buf_temp 버퍼에 써넣는다.
	buf_temp.append(temp);

	// 4) 제일 앞의 4byte(size)에 메시지 길이를 써넣습니다.
	buf_temp.front<uint32_t>() = static_cast<uint32_t>(buf_temp.size());

	// 5) 전송한다.
	send(buf_temp);
}

void socket_tcp::send_message_MESSAGE_B_3()
{
	// ----------------------------------------------
	//
	//	struct sMESSAGE_HEADER
	//	{
	//		uint32_t			size;
	//		eMESSAGE_TYPE		type;
	//	
	//		ENABLE_STRUCT_SERIALIZABLE
	//	};
	//
	//	struct sMESSAGE_B : public sMESSAGE_HEADER
	//	{
	//		int							a = 0;
	//		std::string					b;
	//		std::vector<int>			c;
	//		std::map<int, std::string>	d;
	//	};
	//
	// ----------------------------------------------

	// temporary)
	std::vector<int> vec_test{ 10,20,30 };
	std::map<int, std::string> map_test{ {1, "a"s}, {2, "b"s}, {3, "c"s} };

	// 2) 구조체를 선언하고 값을 써넣는다.
	sMESSAGE_B temp;
	//temp.size는 그냥 비워놓습니다.
	temp.type = SEND_B;
	temp.a = 100;
	temp.b = "test_string"s;
	temp.c = vec_test;
	temp.d = map_test;

	// 3) 구조체로 바로 버퍼를 생성해 데이터를 append해 넣습니다.
	auto buf_temp = make_shared_buffer(temp);

	// 4) 전송한다.
	send(buf_temp);
}


int main()
{
	// trace) 
	std::cout << "start server [tut.socket.02.tcp_send_receive.server]..."sv << '\n';

	// 2) 'socket_tcp'을 사용하는 acceptor 객체를 생성한다.
	auto pacceptor = make_own<net::acceptor<socket_tcp>>();

	// 3) 20000번 포트에서 listen을 시작한다. (기본설정은 IPv4과 IPv6 동시 지원이다.)
	pacceptor->start({{net::ip::tcp::v6(), 20000}});

	// - ESC키를 누를 때까지 대기한다.
	while(_getch() != 27);

	// trace) 
	std::cout << "stop server [tut.socket.02.tcp_send_receive.server]..."sv << '\n';

	// end) 서버 종료
	return 0;
}

