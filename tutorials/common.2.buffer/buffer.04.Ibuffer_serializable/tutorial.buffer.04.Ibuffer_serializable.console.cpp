//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                  tutorials buffer (4) - buffer serialize                  *
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
// 1) standard header file
#if defined(_WIN32)
	#include <conio.h>
#endif

// 2) CGDK header file
#include "cgdk/sdk10/system.object.h"

// 3) header files
#include <iostream>

// 4) namespace
using namespace CGDK;

enum class eMESSAGE_TYPE : int32_t
{
	NONE = 0,
	A = 1,
	B = 2
};

int main()
{
	// ------------------------------------------------------------------
	//
	// 1. Ibuffer_serializable을 사용한 직렬화
	//
	//    Ibuffer_serializable을 상속받아 직렬화를 직접 정의할 수 있다.
	//    Ibuffer_serializable을 상속받은 후 다음 3개의 virtual 함수를 정의한다.
	//    
	//    (v) process_serialize_in
	//        - extract할 때 호출되는 함수로 전달되어오는 _buffer로부터 값을 
	//          읽어내어 값을 저장하도록 한다.
	//
	//    (v) process_serialize_out
	//        - append를 할 때 호출되는 함수로 전달된 _buffer에 데이터를 써넣
	//          것을 정의한다.
	//
	//    (v) process_serialize_in
	//        - get_size_of()가 호출되었을 때 호출되는 함수로 append시 필요한
	//          크기를 리턴한다.
	// 
	// ------------------------------------------------------------------
	{
		{
			shared_buffer a = alloc_shared_buffer(16);
			shared_buffer b = alloc_shared_buffer(16);

			buffer_view c = a; // ok~

			b = a; // ok~

			b = c; // exception!



			//shared_buffer a = alloc_shared_buffer(16);

			//a.append<uint64_t>(0);
			//a.append<uint64_t>(0);
			//a.append<uint64_t>(0);
			//a.append<uint64_t>(0);
			//buffer b;
			//buffer_view c;

			//b = a; // 가능
			//c = a; // 가능
			//c = b; // 가능
		}

		struct foo : public Ibuffer_serializable
		{
			int					a = 0;
			eMESSAGE_TYPE		b = eMESSAGE_TYPE::NONE;
			std::string			c;
			short				d = 0;
			std::vector<int>	e;

			virtual	void		process_serialize_in(buffer_view& _buffer) override
			{
				a = _buffer.extract<int>();
				b = _buffer.extract<eMESSAGE_TYPE>();
				c = _buffer.extract<std::string>();
				e = _buffer.extract<std::vector<int>>();

				std::cout << "process_serializae_in...\n"sv;
			}
			virtual	void		process_serialize_out(buffer& _buffer) override
			{
				_buffer.append<int>(a);
				_buffer.append<eMESSAGE_TYPE>(b);
				_buffer.append<std::string>(c);
				_buffer.append<std::vector<int>>(e);

				std::cout << "process_serializae_out...\n"sv;
			}
			virtual std::size_t	process_size_of() const override
			{
				size_t temp = 0;

				temp += get_size_of(a);
				temp += get_size_of(b);
				temp += get_size_of(c);
				temp += get_size_of(e);

				std::cout << "process_size_of...\n"sv;

				return temp;
			}
		};

		// - DATA형 변수 s1
		foo s1;
		s1.a = 1;
		s1.b = eMESSAGE_TYPE::A;
		s1.c = "test string"s;
		s1.d = 0;
		s1.e = std::vector{ 10,20,30 };

		// *1) get_size_of<T>(...)직렬화시의 데이터 크기를 얻을 수 있다.
		const auto size = get_size_of(s1);

		// - s1의 직렬화시 크기를 출력한다.
		std::cout << "size_of s1 is "sv << size << " bytes\n"sv;

		// - size만큼의 버퍼를 할당받는다.
		auto bar = alloc_shared_buffer(size);

		// *2) buf에 DATA형 변수 s1을 append한다.
		bar.append(s1);

		// - bar의 size_값을 출력한다. 
		std::cout << "foo.size_ "sv << bar.size() << " bytes\n"sv;

		// *3) foo형을 extract해서 읽어낸다.
		auto v1 = bar.extract<foo>();

		// - foo를 출력한다.
		std::cout << "a: "sv << v1.a << '\n';
		std::cout << "b: "sv << static_cast<int32_t>(v1.b) << '\n';
		std::cout << "c: "sv << v1.c << '\n';
		std::cout << "d: "sv << v1.d << '\n';
		std::cout << "e: "sv;
		for(auto iter: v1.e)
			std::cout << iter << " "sv;
		std::cout << '\n' << '\n';
	}


	// ------------------------------------------------------------------
	// 2. DEFINE_BUFFER_SERIALIZE을 사용한 hetrogenous append/extract (1)
	//
	//    Ibuffer_serializable 관련 함수를 'DEFINE_BUFFER_SERIALIZE'를 사용해
	//    간단히 정의할 수 있다.
	//
	//    get_size_of<T>(...) 함수를 사용해 직렬화 크기를 얻을 수 있다.
	//
	// ------------------------------------------------------------------

	// Ibuffer_serialzable을 정의한다!
	// - DEFINE_BUFFER_SERIALIZE를 사용하면 손쉽게 정의가 가능하다.
	struct foo : public Ibuffer_serializable
	{
	public:
		int					a = 0;
		eMESSAGE_TYPE		b = eMESSAGE_TYPE::NONE;
		std::string			c;
		short				d = 0;
		std::vector<int>	e;

		DEFINE_BUFFER_SERIALIZE(a,b,c,e); // (!) 이거!!
	};

	{
		// - DATA형 변수 s1
		foo s1;
		s1.a = 1;
		s1.b = eMESSAGE_TYPE::A;
		s1.c = "test string"s;
		s1.d = 0;
		s1.e = std::vector{ 10,20,30 };

		// *1) get_size_of<T>(...)직렬화시의 데이터 크기를 얻을 수 있다.
		const auto size = get_size_of(s1);

		// - s1의 직렬화시 크기를 출력한다.
		std::cout << "size_of s1 is "sv << size << " bytes\n"sv;

		// - size만큼의 버퍼를 할당받는다.
		auto bar = alloc_shared_buffer(size);

		// *2) buf에 DATA형 변수 s1을 append한다.
		bar.append(s1);

		// - bar의 size_값을 출력한다. 
		std::cout << "foo.size_ "sv << bar.size() << '\n';

		// *3) foo형을 extract해서 읽어낸다.
		auto v1 = bar.extract<foo>();

		// - foo를 출력한다.
		std::cout << "a: "sv << v1.a << '\n';
		std::cout << "b: "sv << static_cast<int32_t>(v1.b) << '\n';
		std::cout << "c: "sv << v1.c << '\n';
		std::cout << "d: "sv << v1.d << '\n';
		std::cout << "e: "sv; for (auto iter : v1.e) std::cout << iter << " ";
		std::cout << '\n' << '\n';
	}
}
