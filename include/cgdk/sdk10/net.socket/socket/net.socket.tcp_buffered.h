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
// net::socket::tcp_buffered
//
//  1) 기본 tcp 소켓과 동일하나 sender만 버퍼를 사용한 모아 보내기를 지원한다.
//  2) 따라서 그냥 모아 보내기에 비해 메모리 복사가 많이 일어날 수 있다.
//  3) 큰 메시지의 메시지 혹은 연속된 데이터들을 빈번히 전송할 경우 적합하지 않다.
//
// ----------------------------------------------------------------------------
template <class RECEIVE_HEADER_T = uint32_t, class SEND_HEADER_T = RECEIVE_HEADER_T>
class net::socket::tcp_buffered :
	public						net::io::socket::tcp::Ndefault,
	public						net::io::connectable::tcp::Ndefault,
	public						net::io::sendable::Ntcp_async_gather_buffered, // (*)
	public				 		net::io::send_request::tcp::Ndefault,
	public						net::io::sender::tcp::Ndefault<SEND_HEADER_T>,
	public						net::io::receivable::tcp::Ndefault,
	public						net::io::packetable::tcp::Ndefault<RECEIVE_HEADER_T>,
	public						net::io::messageable::tcp::Ndefault
{
};


}