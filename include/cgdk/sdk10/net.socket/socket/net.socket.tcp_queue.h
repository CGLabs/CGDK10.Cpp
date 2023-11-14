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
//  1) net::socket::tcp�� ��� ���� �����ϳ� receivable�� 
//     net::io::receivable::Nstream_queue�� ����� ���̴�.
//  2) �̴� receive�� message�� ó���� �ٸ� �۾��������� ó���� �ְ� �����ν�
//     �ð��� ���ŷ��� ���� ������ ���̴�.
//  3) ������ �⺻ ���ϰ� �ֱ� ������ ���ŷ��� ���� socket������ ������ �� ����
//     ���ϰ� ���� �� �ִ�.
//  4) ���� �� ������ �ַ� ���� socket���� ���� �����͸� �ۼ����ϴ� ���ӿ� ����
//     �� ���¶�� �� �� �ִ�.
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