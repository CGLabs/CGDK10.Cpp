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
// net::socket::tcp_client_crypt
//
//  1) 암호송수신 기능을 가진 클라이언트용 tcp socket 이다.
//
//-----------------------------------------------------------------------------
template <class RECEIVE_HEADER_T = uint32_t, class SEND_HEADER_T = RECEIVE_HEADER_T>
class net::socket::tcp_client_crypt :
	public						net::io::connect_requestable::tcp::Ndefault,
	public						net::io::socket::Ntcp,
	public						net::io::send_request::Nbase,
	public						net::io::sender::Nstream,
	public						net::io::packetable::Nstream<RECEIVE_HEADER_T>,
	public						net::io::Ntcp_client_crypt
{
};


}