//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
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
// net::acceptor
//
//  1) 기본적으로 net::io::acceptor::Ntcp이다 하지만 여기에 process_alloc_connectable()
//     함수를 재정의한 Template class이다.
//  
//  2) Accept때 사용할 socket의 Class만 Template 인자로 설정해 주면 그 socket
//     으로 Accept를 수행한다.
//  
//  3) 이 Class를 선언 할 때 TSOCKET에 acceptor가 생성하여 사용하려는 socket만 
//     집어 넣으면 acceptor를 접속을 하게 되면 T로 설정한 socket을 생성하여 
//     Accept를 걸어서 acceptor로 동작한다.
//
//
//   4) initialize/start String
//
//      "[Name]/Address"
//	    "[Name]/Port"
//	    "[Name]/prepare on start"
//	    "[Name]/must prepare"
//
//-----------------------------------------------------------------------------
template <class TSOCKET, class FLAG = void>
class net::acceptor
{
};


}