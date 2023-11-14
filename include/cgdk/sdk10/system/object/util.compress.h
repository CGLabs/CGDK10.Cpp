//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              Utility Classes                              *
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

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// CGCompress
//
// 1. CGCompress란!
//    1) 압축을 수행하는 Function이다.
//    2) 이함수는 내부적으로 ZLib의 함수를 사용하고 있다.
//    3) 만약 이 함수를 사용하고자 한다면 Zlib를 컴파일해서 추가시켜주어야한다.
//
//  주의사항) 기본적으로 ZLib를 포함하고 있지 않다.
//            필요시 공개라이브러리인 ZLib을 구한후 컴파일하여 Link시켜주어야
//            한다.
//  
//            #pragma comment(lib,"zlib.lib")
//
//
//-----------------------------------------------------------------------------
namespace compress
{
	[[nodiscard]] buffer_view zip(buffer_view _buf_dest, const_buffer_view _buf_source);
	[[nodiscard]] shared_buffer	zip(const_buffer_view _buf_source);
	[[nodiscard]] buffer_view unzip(buffer_view _buf_dest, const_buffer_view _buf_source);
	[[nodiscard]] shared_buffer unzip(const_buffer_view _buf_source);
}


}