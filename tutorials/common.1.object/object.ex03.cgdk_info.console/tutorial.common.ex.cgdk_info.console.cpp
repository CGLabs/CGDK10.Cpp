//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.01                        *
//*                                                                           *
//*                    tutorials common.ex03 - cgdk info                    *
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
#include "cgdk/sdk10/net.socket.h"

// 3) header files
#include <iostream>

// 4) namespace
using namespace CGDK;

class socket_temp : public CGDK::net::socket::tcp<>
{
};


//-----------------------------------------------------------------------------
//
// tutorial common.ex03 - cgdk component info
//
//-----------------------------------------------------------------------------
int main()
{
	// 1) net.socket library link를 위해 임시로 생성
	[[maybe_unused]] auto psocket = make_object<socket_temp>();

	// 2) component 정보를 얻는다.
    auto& component_info = CGDK::get_component_info();

	// 3) componenet 정보를 출력한다.
	for (auto& iter : component_info)
	{
		std::cout << iter.component_info.name << '\n';
		std::cout << " - version\t\t"sv << iter.component_info.version_package << "." << iter.component_info.version_sub << "." << iter.component_info.version_build << '\n';
		std::cout << " - build_time\t\t"sv << to_string<char>(iter.component_info.time_build) << '\n';
		std::cout << " - compiler\t\t"sv << to_string<char>(iter.component_info.compiler) << '\n';
		std::cout << " - platform\t\t"sv << to_string<char>(iter.component_info.platform) << '\n';
		std::cout << " - configuration\t"sv << to_string<char>(iter.component_info.configuration) << '\n';

		std::cout << '\n';
	}

}
