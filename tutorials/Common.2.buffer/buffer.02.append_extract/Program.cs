﻿//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                    for C# Ver 2.0 / Release 2019.12.11                    *
//*                                                                           *
//*                     tutorials buffer - append/extarct                     *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho sanghyun. sangducks@cgcii.co.kr        *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2008 Cho sanghyun. All right reserved.                 *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

using System;
using System.Collections.Generic;
using CGDK;
using CGDK.factory;

namespace tutorial.buffer._01.basic.console
{
	class Program
	{
		static void Main(string[] args)
		{
			// ------------------------------------------------------------------
			// 1. 문자열
			// ------------------------------------------------------------------
			{
				// - 1000byte 버퍼를 생성함.
				var baz = memory.alloc_buffer(1000);

				baz.append<string>("test_stringn1");
				baz.append<string>("테스트 문자열");

				// - baz의 size_값을 출력한다. 
				Console.WriteLine("size_: " + baz.size);

				// *2) 문자열을 다시 extract해냄
				var v1 = baz.extract<string>();
				var v2 = baz.extract<string>();

				Console.WriteLine(v1);
				Console.WriteLine(v2);
			}

			// ------------------------------------------------------------------
			// 2. std::vector<T>/std::list<T>, std::map<K,V>의 append와 extract
			//
			//    std::vector<T>, std::list<T>, std::map<K,V>와 같은 집합 데이터들의
			//    append/extract도 지원한다.
			//  
			//    물론 vecot, list, map뿐만 아니라 기본 stl container는 지원한다.
			//    또 CGDK에서 자체적으로 지원하는 static_vector, circular_list 등도
			//    지원한다.
			//
			//    그럼 vector의 vecotr도 지원하는가? 당연히 지원한다.
			//
			// ------------------------------------------------------------------
			{
				// - 임시로 vector 객체를 만들고 값을 넣음.
				var s1 = new List<int> { 1, 2, 3, 4, 5, 6, 7 };
				var s2 = new Dictionary<string, int> { { "first",1}, { "second",2}, { "third",3}, { "forth",4} };

				// - 1000byte 버퍼를 생성함.
				var baz = memory.alloc_buffer(1000);

				// *1) buf에 std::vector와 std::map을 append함.
				baz.append(s1);
				baz.append(s2);

				// - baz의 size_값을 출력한다. 
				Console.WriteLine("size_: " + baz.size);

				// *2) 이것을 extract해냄
				var v1 = baz.extract<List<int>>();
				var v2 = baz.extract<Dictionary<string, int>> ();

				// - v1 출력
				foreach (var iter in v1)
					Console.Write(iter + ", ");
				Console.Write("\n\n");

				// - v2 출력
				foreach (var iter in v2)
					Console.WriteLine(iter.Key + ", " + iter.Value);
			}
		}
	}
}
