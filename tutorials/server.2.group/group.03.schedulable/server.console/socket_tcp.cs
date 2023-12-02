﻿//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                    for C# Ver 2.0 / Release 2019.12.11                    *
//*                                                                           *
//*             tutorials group - message_mediator.server.console             *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho sanghyun. sangducks@cgcii.co.kr        *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2008 Cho sanghyun. All right reserved.                 *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

using System;
using CGDK;
using CGDK.net;
using CGDK.server.group;

// ----------------------------------------------------------------------------
//
// socket_tcpClient
//
// ----------------------------------------------------------------------------
public class socket_tcp : CGDK.net.socket.tcp
{
	public socket_tcp()
	{
		m_groupable = new CGDK.server.Igroupable<socket_tcp>(this);
	}

	protected override void on_connect()
	{
		// trace) 
		Console.WriteLine(" @ connected");

		// 1) enter to group
		Program.pgroup.enter_member(m_groupable);
	}
    protected override void on_disconnect(ulong _disconnect_reason)
	{
		// 1) leave from group
		m_groupable.leave_group();

		// trace) 
		Console.WriteLine(" @ disconnected");
	}
    protected override int on_message(object _source, sMESSAGE _msg)
	{
		// 1) transmit message to message mediator
		m_message_transmitter.transmit_message(this, _msg);

		// return) 
		return 0;
	}

	// 4) Igroupable
	public CGDK.server.Igroupable<socket_tcp> m_groupable;
	// 5) message transmitter
	public CGDK.message_transmitter m_message_transmitter = new CGDK.message_transmitter();
	// 6) Member Serial
	protected int m_member_serial;
}