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
// net::io::Iconnect_requestable(연결기)
//
// 1. Iconnect_requestable은~
//    1) Iconnectable에 스스로 연결기능을 제공해줘 Client역할을 할 수 있도록 해
//       주는 Interface이다.
//    2) 각종 connect함수를 사용하여 connect을 요청할 수 있다.
//
// 2. 가상 함수.
//    1) process_request_connecting()
//       - 접속을 요청하는 과정을 정의하는 Process함수이다.
//
//    2) process_reset_connector()
//       - 초기화를 수행할 때 호출되는 함수이다.
//
//
//-----------------------------------------------------------------------------
class net::io::Iconnect_requestable :
	virtual public				object::Istartable
{
public:
	virtual bool				process_request_connecting( const net::sockaddr& _address) PURE;
	virtual	void				process_complete_connecting( uintptr_t _result) PURE;
	virtual	void				process_reset_connector() PURE;
};


}