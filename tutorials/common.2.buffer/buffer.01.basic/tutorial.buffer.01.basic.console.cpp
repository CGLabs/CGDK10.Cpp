//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                    tutorials buffer (1) - basic buffer                    *
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

// 2) header files
#include <iostream>

// 3) namespace
using namespace CGDK;

int main()
{
	// ------------------------------------------------------------------
	// 1. shared_buffer와 메모리 할당
	// ------------------------------------------------------------------
	{
		// 1) shared_buffer에 alloc_shared_buffer()함수를 사용해 메모리를 할당받습니다.
		//    - 1000 byte의 메모리를 할당받는다.
		//    - 그리고 data_값에 할당받은 메모리의 포인터를 넣는다.
		//    - size_(버퍼의 길이)는 0으로 초기화 한다.
		shared_buffer baz = alloc_shared_buffer(1000);

		// 2) data()는 버퍼의 버퍼의 포인터 size()는 쓰여진 버퍼의 크기를 의미한다.(여기서는 0이 된다.)
		std::cout << "data_ "sv << (uint64_t)baz.data() << "  size_: "sv << baz.size() << '\n';

		// 설명) shared_buffer는 스마트 포인터의 기능을 가지고 있어서
		//       이 블럭이 끝나면 baz에 할당받은 버퍼는 자동적으로 소멸된다.
	}

	// ------------------------------------------------------------------
	// 2. append<T>와 extract<T>
	// ------------------------------------------------------------------
	{
		// 1) 1000 byte할당아 buffer를 생성한다.
		auto baz = alloc_shared_buffer(1000);

		// - 먼저 baz의 data_값과 len값을 출력한다.
		std::cout << "mem allocated>  "<< "data_: "sv << (uint64_t)baz.data() << "  size_: "sv << baz.size() << '\n';

		// 1) append()함수를 사용해 baz에 값을 써넣는다.
		baz.append<int>(100);		// int형으로 100을 써넣는다.
		baz.append<float>(3.14f);	// float형으로 3.14f을 써넣는다.
		baz.append<uint64_t>(123);	// uint64_t형으로 123을 써넣는다.

		// check) 이렇게 append를 사용해 int(100)-4byte, float(3.14f)-4byte, uint64_t(123)-8byte을 써넣으면
		//   총 크기인 16byte만큼 size_값이 늘어나게 된다.
		std::cout << "data appended>  "<< "data_: "sv << (uint64_t)baz.data() << "  size_: "sv << baz.size() << '\n';

		// 2) extract()함수를 사용해 baz에서 값을 읽어낸다.
		//    써넣은 순서와 자료형 대로 값을 일어낸다.
		auto v1 = baz.extract<int>();
		auto v2 = baz.extract<float>();
		auto v3 = baz.extract<uint64_t>();

		// check) extract()함수를 사용해 써넣은 대로 값을 읽어내면 
		///  총크기인 16byte만큼 size_는 줄어들게 되며 포인터인 data값은 읽어낸 크기(16byte)만큼 증가하게 된다.
		std::cout << "data extracted> "sv << "data_: "sv << (uint64_t)baz.data() << "  size_: "sv << baz.size() << '\n';

		// check) 읽어낸 값 출력
		std::cout << "v1: " << v1 << "  v2: " << v2 << "  v3: " << v3 << '\n';
	}

	// ------------------------------------------------------------------
	// 3. 문자열 직렬화와 역직렬화
	// ------------------------------------------------------------------
	{
		// 1) 1000 byte할당아 buffer를 생성한다.
		auto baz = alloc_shared_buffer(1000);

		// 2) 문자열을 써넣는다.
		baz.append<std::string_view>("how are you?"sv);
		baz.append<std::string>("i'm fine, thank you and you?"s);
		baz.append<std::wstring_view>(L"dou you know kimchi?"sv);
		baz.append<std::wstring>(L"yes, i know psi too"s);
		baz.append<std::wstring_view>(L"이것 좀 테스트하게 해주세요."sv);
	#ifdef __cpp_char8_t
		baz.append<std::u8string_view>(u8"이것 좀 테스트하게 해주세요."sv);
	#endif
		baz.append<std::u16string_view>(u"これを試ためさせてください"sv);
		baz.append<std::u32string_view>(U"これを試ためさせてください"sv);

		// check)
		std::cout << "data appended>  "sv << "data_: "sv << (uint64_t)baz.data() << "  size_: "sv << baz.size() << '\n';


		// 3) extract<T>()함수를 사용해 값을 읽어낸다.
		auto v1 = baz.extract<std::string>();
		auto v2 = baz.extract<std::string_view>();
		auto v3 = baz.extract<std::wstring>();
		auto v4 = baz.extract<std::wstring_view>();
		auto v5 = baz.extract<std::wstring_view>();
	#ifdef __cpp_char8_t
		[[maybe_unused]] auto v6 = baz.extract<std::u8string_view>();
	#endif
		[[maybe_unused]] auto v7 = baz.extract<std::u16string_view>();
		[[maybe_unused]] auto v8 = baz.extract<std::u32string_view>();

		// check) 
		std::cout << "data extracted> "sv << "data_: "sv << (uint64_t)baz.data() << "  size_: "sv << baz.size() << '\n';

		// check) extract한 문자열을 출력해본다.
		std::cout << "v1 "sv << v1 << std::endl;
		std::cout << "v2 "sv << v2 << std::endl;
		std::wcout << L"v3 "sv << v3 << std::endl;
		std::wcout << L"v4 "sv << v4 << std::endl;
		std::wcout << L"v5 "sv << v5 << std::endl;
	}


	// ------------------------------------------------------------------
	// 4. 집합형 데이터 직렬화와 역직렬화
	//    - std::vector<T>, std::list<T>, std::map<T>와 같은 데이터의 직렬화
	//    
	// ------------------------------------------------------------------
	{
		std::vector<int>           s1{ 10, 20, 30 };
		std::list<std::string>     s2{ "a", "b", "c" };
		std::vector<std::vector<int>> s3{ {1,2},{3,4},{5,6} };
		std::map<std::string, int> s4{ {"x",10},{"y",20},{"z",30}};

		// 1) 1000 byte할당아 buffer를 생성한다.
		auto baz = alloc_shared_buffer(1000);

		// 3) 데이터들을 써넣는다. (append시 템플릿의 자료형 인자를 생략하면 데이터 형을 그대로 인식한다.)
		baz.append(s1);
		baz.append(s2);
		baz.append(s3);
		baz.append(s4);
		baz.append<std::string_view>("ok");

		// check)
		std::cout << "data appended>  " << "data_: "sv << (uint64_t)baz.data() << "  size_: "sv << baz.size() << '\n';

		// 4) extract<T>()함수를 사용해 값을 읽어낸다.
		auto v1 = baz.extract<std::vector<int>>();
		auto v2 = baz.extract<std::list<std::string>>();
		auto v3 = baz.extract<std::vector<std::vector<int>>>();
		auto v4 = baz.extract<std::map<std::string, int>>();
		auto v5 = baz.extract<std::string>();

		// check) 
		std::cout << "data extracted> " << "data_: "sv << (uint64_t)baz.data() << "  size_: "sv << baz.size() << '\n';

		// check) extract한 데이터들을 출력해본다.
		std::cout << "v1 "; for (auto& iter : v1) std::cout << iter << " "; std::cout << std::endl;
		std::cout << "v2 "; for (auto& iter : v2) std::cout << iter << " "; std::cout << std::endl;
		std::cout << "v3 "; for (auto& iter : v3) { std::cout << "{"sv; for (auto& iter2 : iter) std::cout << iter2; std::cout << "} "sv << std::endl; }
		std::cout << "v4 "; for (auto& iter : v4) std::cout << "{"sv << iter.first << ", " << iter.second << "} "sv ; std::cout << std::endl;
		std::cout << "v5 " << v5 << std::endl;
	}

	// ------------------------------------------------------------------
	// 5. 배열
	//
	// ------------------------------------------------------------------
	{
		// - append할 배열 데이터
		int s1[4]{ 1,2,3,4 };
		std::string s2[2]{ "first"s, "second"s };
		const char* s3[2]{ "first", "second" };

		// - 1000byte 버퍼를 생성함.
		auto baz = alloc_shared_buffer(1000);

		// 1) buffer를 추가함
		baz.append(s1);
		baz.append(s2);
		baz.append(s3);
		baz.append(s3);
		baz.append(s3);

		// 2) extaact한다.
		std::array<int, 4>				v1 = baz.extract<std::array<int, 4>>();
		std::array<std::string, 2>		v2 = baz.extract<std::array<std::string, 2>>();
		std::array<std::string_view, 2> v3 = baz.extract<std::array<std::string_view, 2>>();
		std::vector<std::string_view>   v4 = baz.extract<std::vector<std::string_view>>();
		std::vector<std::string_view>   v5 = baz.extract<char* []>();

		// 설명)
		//   배열인 const char* s3[2]를 append한 것을 std::array<std::string_view, 2>로도 extract해내고
		//   char*[]나 std::vector<std::string_view>로도 extract해냈다.
		//   이것은 선형 컨테이너끼리는 buffer에 저장되는 구조가 동일해 서로 호환되기 때문이다.
		//   즉, std::vector<T>로 append 한 것은 std::list<T>로 extract해 낼수 있다.
		//   std::array<T,N>로 append한 것 역시 std::vector<T>로 extract해 낼수 있다.
		//   std::vector<T>로 append한 것 역시 std::array<T,N>로 extract해 낼수 있으나
		//   extract해낼 std::array<T,N>가 append한 크기보다 작을 경우 exception을 던진다.

		// 출력)
		std::cout << "v1: {"; for (auto& iter : v1) std::cout << iter << ","sv; std::cout << "}"sv << '\n';
		std::cout << "v2: {"; for (auto& iter : v2) std::cout << iter << ","sv; std::cout << "}"sv << '\n';
		std::cout << "v3: {"; for (auto& iter : v3) std::cout << iter << ","sv; std::cout << "}"sv << '\n';
		std::cout << "v4: {"; for (auto& iter : v4) std::cout << iter << ","sv; std::cout << "}"sv << '\n';
		std::cout << "v5: {"; for (auto& iter : v5) std::cout << iter << ","sv; std::cout << "}"sv << '\n';
	}



	// ------------------------------------------------------------------
	// 6.1. front<T>로 읽기만 하기 (1)
	// ------------------------------------------------------------------
	{
		auto baz = alloc_shared_buffer(1000);
		baz.append<int>(100);
		baz.append<float>(3.14f);
		baz.append<uint64_t>(1234);

		std::cout << "before> "sv << "data_: " << baz.data() << "  size_: "sv << baz.size() << '\n';

		// (*) front()함수를 사용하면 offset값을 설정해 줄수가 있다.
		//     또 값만 읽어오고 data_와 size_값을 변경시키지 않는다.
		auto v1 = baz.front<int>(0);
		auto v2 = baz.front<float>(4);
		auto v3 = baz.front<uint64_t>(8);

		std::cout << "v1: "sv << v1 << "  v2: "sv << v2 << "  v3: "sv << v3 << '\n';

		// (*) data_값과 size_값은 변경되지 않는다.
		std::cout << "after>  "sv << "data_: " << baz.data() << "  size_: "sv << baz.size() << '\n';
	}

	// ------------------------------------------------------------------
	// 6.2. front<T>로 읽기만 하기 (2)
	// ------------------------------------------------------------------
	{
		auto baz = alloc_shared_buffer(1000);
		baz.append<int>(100);
		baz.append<float>(3.14f);
		baz.append<uint64_t>(123);

		// (*) offset 객체에 4를 설정한다.
		CGDK::offset pos(4);

		std::cout << "before> " << "data_: " << baz.data() << "  size_: " << baz.size() << "  pos.amount: " << pos.amount << '\n';

		// (*) front()함수에 offset객체를 사용해 offset값을 전달해 준다.
		//     또 값만 읽어오고 data_와 size_값을 변경시키지 않지만 offset객체의 값은 읽어낸만큼 변경해준다.
		auto v2 = baz.front<float>(pos);
		auto v3 = baz.front<uint64_t>(pos);

		std::cout << "v2: "sv << v2 << "  v3: "sv << v3 << '\n';

		// (*) data_값과 size_값은 변경되지 않는다. 하지만 offset객체의 amount값은 읽어낸 후의 위치로 변경된다.
		std::cout << "after>  " << "data_: "sv << baz.data() << "  size_: "sv << baz.size() << "  pos.amount: "sv << pos.amount << '\n';
	}

	// ------------------------------------------------------------------
	// 6.3. front<T>로 값써넣기
	// ------------------------------------------------------------------
	{
		auto baz = alloc_shared_buffer(1000);
		baz.append<int>(100);
		baz.append<float>(3.14f);
		baz.append<uint64_t>(123);

		std::cout << "before> " << "data_: "sv << baz.data() << "  size_: "sv << baz.size() << '\n';

		// (*) 기본 자료형(arithmetic type)의 경우 리턴값을 참조형으로 받을 수 있다.
		auto& ref_v2 = baz.front<float>(4);

		std::cout << "v2: "sv << ref_v2 << '\n';
		
		// (*) 1.0f값을 대입한다.
		ref_v2 = 1.0f;

		// (*) 다시 v2위치의 값을 읽어보면?
		auto& v2 = baz.front<float>(4);
		
		// (*) 값은 1.0f로 바뀌어 있다.
		std::cout << "v2: "sv << v2 << '\n';		
		std::cout << "after>  "sv << "data_: "sv << baz.data() << "sv  size_: " << baz.size() << '\n';
	}
	// ------------------------------------------------------------------
	// 7. enum형 자료형
	//
	// ------------------------------------------------------------------
	{
		enum class eTEST : int32_t
		{
			A = 1,
			B = 2
		};

		// - 1000byte 버퍼를 생성함.
		auto baz = alloc_shared_buffer(1000);

		// - enum형 데이터를 써넣는다.
		baz.append<eTEST>(eTEST::A);
		baz.append<eTEST>(eTEST::B);
		baz.append<std::u16string>(u"TEST"s);

		// - enum형 데이터를 읽어온다.
		/*auto value1 =*/ baz.extract<eTEST>();
		/*auto value2 =*/ baz.extract<eTEST>();
	}

	// ------------------------------------------------------------------
	// 8. 시간 자료형 (tm, std::chrono::time_point)
	//
	// ------------------------------------------------------------------
	{
		// - 임시로 time을 얻는다.
		auto t1 = std::chrono::system_clock::now(); // std::chrono::system_clock::time_point
		auto t2 = std::chrono::system_clock::to_time_t(t1); // std::time_t

		// - 1000byte 버퍼를 생성함.
		auto baz = alloc_shared_buffer(1000);

		// *1) chrono::time_point와 time_t를 직렬화한다.
		baz.append(t1);
		baz.append(t2);

		// - baz의 size_값을 출력한다. 
		std::cout << "size_: "sv << baz.size() << '\n';

		// *2) 이것을 extract해냄
		/*auto v1 =*/ baz.extract<std::chrono::system_clock::time_point>();
		/*auto v2 =*/ baz.extract<time_t>();
	}

	// ------------------------------------------------------------------
	// 9. std::initializer_list
	//
	//    - initializer_list를 사용하면 같은 데이터를 한꺼번에 여러개 append할 수 있다.
	//
	// ------------------------------------------------------------------
	{
		std::string s1 = "a";
		std::string s2 = "b";
		std::string s3 = "c";

		auto baz = alloc_shared_buffer(1000);

		// (*) std::initializer_list<T>로 append한다.
		baz.append({ s1, s2, s3 });

		// (*) std::initializer_list<T>는 각각을 append<T>한 것과 동일하므로 각각을 extract<T>해준다.
		auto v1 = baz.extract<std::string>();
		auto v2 = baz.extract<std::string>();
		auto v3 = baz.extract<std::string>();

		std::cout << "v1: "sv << v1 << ", v2: "sv << v2 << "v3: "sv << v3 << '\n';
	}

	// ------------------------------------------------------------------
	// 9. std::tuple과 std::tie (1)
	//
	//    - tuple/tie은 데이터를 묶어서 전송하거나 분리해서 전송할 때 아주 유용하다.
	//    - 구조체 등과의 처리에서도 매우 유용하게 쓸수 있다. (추후 설명)
	//
	// ------------------------------------------------------------------
	{
		int s1 = 10;
		std::string s2 = "test string"s;
		float s3 = 1.0f;
		
		auto baz = alloc_shared_buffer(1000);

		// (*) std::tuple로 값을 append한다.
		baz.append(std::tuple{ s1, s2, s3 });

		int v1;
		std::string v2;
		float v3;

		// (*) std::tie를 사용해 값을 얻어온다.
		std::tie ( v1, v2, v3 ) = baz.extract<std::tuple<int, std::string, float>>();

		std::cout << "v1: "sv << v1 << ", v2: "sv << v2 << "v3: "sv << v3 << '\n';
	}

	// ------------------------------------------------------------------
	// 9. std::tuple과 structred binding (2)
	//
	//    - structed binding과 함께 사용하면 일일이 변수선언하는 것을 피할수 있다.
	//    - 이 역시 tuple과 보다는 구조체를 사용한 extract에 더 많이 사용된다.
	//
	// ------------------------------------------------------------------
	{
		int s1 = 10;
		std::string s2 = "test string"s;
		float s3 = 1.0f;

		auto baz = alloc_shared_buffer(1000);

		baz.append(std::tuple{ s1, s2, s3 });

		// (*) std::time를 대신해 structred binding을 사용해서 extract한 값을 받는다.
		auto [ v1, v2, v3 ] = baz.extract<std::tuple<int, std::string, float>>();

		std::cout << "v1: "sv << v1 << ", v2: "sv << v2 << "v3: "sv << v3 << '\n';
	}

	// ------------------------------------------------------------------
	// 10. 버퍼
	//
	// ------------------------------------------------------------------
	{
		auto buf_temp = alloc_shared_buffer(32);
		buf_temp.append<int>(32);
		buf_temp.append<std::string_view>("test"sv);

		auto baz = alloc_shared_buffer(1000);

		// (*) 버퍼를 통체로 직렬화한다.
		baz.append(buf_temp);

		// (*) 버퍼를 역직렬화한다.
		/*auto v1 =*/ baz.extract<buffer_view>();
	}

	// ------------------------------------------------------------------
	// 11. 구조체 직렬화 (1)
	//    - 일반적인 구조체의 직렬화
	//    
	// ------------------------------------------------------------------
	{
		struct STEMP
		{
			int x;
			float y;
			uint64_t z;
		};

		STEMP temp;
		temp.x = 10;
		temp.y = 3.14f;
		temp.z = 123;

		auto baz = alloc_shared_buffer(1000);

		// (*) 일반적인 자료형처럼 append<T>함수로 직렬화한다.
		baz.append(temp);

		// check)
		std::cout << "data appended>  " << "data_: "sv << (uint64_t)baz.data() << "  size_: "sv << baz.size() << '\n';

		// (*) 일반적인 자료형처럼 extract<T>()함수를 역직렬화한다.
		auto v1 = baz.extract<STEMP>();

		std::cout << "data extracted> " << "data_: "sv << (uint64_t)baz.data() << "  size_: "sv << baz.size() << '\n';

		std::cout << "v1.x " << v1.x << std::endl;
		std::cout << "v1.y " << v1.y << std::endl;
		std::cout << "v1.z " << v1.z << std::endl;
	}


	// ------------------------------------------------------------------
	// 12. 구조체 직렬화 (2)
	//    - 
	//    
	// ------------------------------------------------------------------
	{
		struct STEMP
		{
			int x;
			float y;
			uint64_t z;
		};

		auto baz = alloc_shared_buffer(1000);

		// (*) 위치를 확보만 해 놓는다.
		auto& goo = baz.append<STEMP>();

		baz.append<int>(0);
		baz.append<std::string_view>("test_string"sv);


		STEMP temp;
		temp.x = 10;
		temp.y = 3.14f;
		temp.z = 123;

		// (*) 확보해 놓은 위치에 값을 써넣는다.
		goo = temp;
	}


	// ------------------------------------------------------------------
	// 13. 구조체 직렬화 (3)
	//    - 
	//    
	// ------------------------------------------------------------------
	{
		struct STEMP_1
		{
			int x;
			char y;
			uint64_t z;
		};

		struct STEMP_2
		{
			ENABLE_STRUCT_SERIALIZABLE // (*) 이것만 추가해주면!!!

			int x;
			char y;
			uint64_t z;
		};

		STEMP_1 temp_1;
		STEMP_2 temp_2;

		// (*) 'ENABLE_STRUCT_SERIALIZABLE'를 선언하면 sizeof(STEMP)는 16byte지만 get_size_of(STEMP)값은 13byte다.
		std::cout << "STEMP_1   sizeof: "sv << sizeof(temp_1) << "  get_size_of: "sv << get_size_of(temp_1) << '\n';
		std::cout << "STEMP_2   sizeof: "sv << sizeof(temp_2) << "  get_size_of: "sv << get_size_of(temp_2) << '\n';

		auto baz = alloc_shared_buffer(1000);

		// (*) 위치를 확보만 해 놓는다.
		baz.append<STEMP_2>(temp_2);
	}



	_getch();
}
