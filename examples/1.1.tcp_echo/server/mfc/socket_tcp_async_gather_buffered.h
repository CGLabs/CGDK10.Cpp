//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          CGDK.10 example project                          *
//*                       tcp echo server (MFC controls)                      *
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
// ----------------------------------------------------------------------------
//
// socket_tcp_async_gather_buffered
//
// ----------------------------------------------------------------------------
class socket_tcp_async_gather_buffered :
	public net::io::socket::tcp::Ndefault,
	public net::io::connectable::tcp::Ndefault,
	public net::io::sendable::Ntcp_async_gather_buffered, // <- this
	public net::io::send_request::tcp::Ndefault,
	public net::io::sender::tcp::Ndefault<>,
	public net::io::receivable::tcp::Ndefault,
	public net::io::packetable::tcp::Ndefault<>,
	public net::io::messageable::tcp::Ndefault,
	public Npoolable<socket_tcp_async_gather_buffered>
{
protected:
	virtual result_code on_message(sMESSAGE_NETWORK & _msg) override
	{
		// check)
		RETURN_IF(g_disable_echo, eRESULT::DONE);

		// 1) echo send
		send(_msg.buf_message);

		// return) 
		return eRESULT::DONE;
	}
};
