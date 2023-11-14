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
// net::socket::tcp_client_reconnect
//
//  1) 기본 tcp 소켓에 자동 재접속 기능을 가진 connect를 추가한 것이다.
//
//-----------------------------------------------------------------------------
template <class RECEIVE_HEADER_T = uint32_t, class SEND_HEADER_T = RECEIVE_HEADER_T>
class net::socket::tcp_client_reconnect :
	public						net::io::connect_requestable::Ntcp_reconnect,
	public						net::socket::tcp<RECEIVE_HEADER_T, RECEIVE_HEADER_T>
{
public:
			tcp_client_reconnect() {}
			tcp_client_reconnect(std::string_view _name) : net::io::connect_requestable::Ntcp_reconnect(_name) {}
};


}