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
// net::socket::tcp_queue
//
//  1) net::socket::tcp와 모든 것은 동일하나 receivable을 
//     net::io::receivable::Nstream_queue로 사용한 것이다.
//  2) 이는 receive와 message의 처리를 다른 작업단위에서 처리할 있게 함으로써
//     시간당 수신량을 대폭 증가한 것이다.
//  3) 하지만 기본 부하가 있기 때문에 수신량이 적은 socket에서는 오히려 더 많은
//     부하가 있을 수 있다.
//  4) 따라서 이 버전은 주로 단일 socket으로 많은 데이터를 송수신하는 접속에 적합
//     한 형태라고 할 수 있다.
//
//-----------------------------------------------------------------------------
template <class RECEIVE_HEADER_T = uint32_t, class SEND_HEADER_T = RECEIVE_HEADER_T>
class net::socket::tcp_queue :
	public						net::io::socket::tcp::Ndefault,
	public						net::io::connectable::tcp::Ndefault,
	public						net::io::sendable::Ntcp_async_gather_buffered,
	public				 		net::io::send_request::tcp::Ndefault,
	public						net::io::sender::tcp::Ndefault<SEND_HEADER_T>,
	public						net::io::receivable::Nstream_queue,
	public						net::io::packetable::tcp::Ndefault<RECEIVE_HEADER_T>,
	public						net::io::messageable::tcp::Ndefault
{
};


}