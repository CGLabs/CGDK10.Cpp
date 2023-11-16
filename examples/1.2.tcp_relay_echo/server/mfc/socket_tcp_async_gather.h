//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / Release 2017.01.03                        *
//*                                                                           *
//*                      SocketClasses Sample Server (1)                      *
//*                      TCP Echo Server (MFC Controls)                       *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 (c) 2016 Cho Sanghyun All right reserved.                 *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
// socket_tcp_async_gather
//
// ----------------------------------------------------------------------------
class socket_tcp_async_gather :
	public net::io::socket::tcp::Ndefault,
	public net::io::connectable::tcp::Ndefault,
	public net::io::sendable::Ntcp_async_gather, // <- this
	public net::io::send_request::tcp::Ndefault,
	public net::io::sender::tcp::Ndefault<>,
	public net::io::receivable::tcp::Ndefault,
	public net::io::packetable::tcp::Ndefault<>,
	public net::io::messageable::tcp::Ndefault,
	public Npoolable<socket_tcp_async_gather>
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
