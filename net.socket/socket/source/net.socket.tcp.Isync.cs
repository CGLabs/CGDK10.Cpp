﻿//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                    for C# Ver 2.0 / Release 2019.12.11                    *
//*                                                                           *
//*                          Network socket Classes                           *
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
using System.Net;
using System.Net.Sockets;

//----------------------------------------------------------------------------
//  class CGDK.net.socket.Itcp_sync
//
//----------------------------------------------------------------------------
namespace CGDK.net.socket
{
	public class Itcp_sync :
		Itcp
	{
	// Definitions) 
		private class executable_socket_on_connect : Iexecutable
		{
			public Itcp_sync pSocket;
			public SocketAsyncEventArgs	Args;

			public long process_execute(ulong _return, ulong _param)
			{
				// 1) call 'process_complete_connect_post'
				try
				{
					pSocket.process_complete_connect_post(Args);
				}
				catch(System.Exception)
				{
				}

				// 2) add_ref for hold
				pSocket.release();

				// return) 
				return 0;
			}
		}
		private class executable_socket_on_receive : Iexecutable
		{
			public Itcp_sync pSocket;
			public SocketAsyncEventArgs	Args;

			public long process_execute(ulong _return, ulong _param)
			{
				// 1) call 'process_complete_receive_post'
				try
				{
					pSocket.process_complete_receive_post(Args);
				}
				catch(System.Exception)
				{
				}

				// 2) add_ref for hold
				pSocket.release();

				// return) 
				return 0;
			}
		}

	// constructors) 
		public Itcp_sync()
		{
			m_io_queue = executable_queue.default_queue;
		}

	// implementation)
		public override bool	process_complete_connect(SocketAsyncEventArgs _args)
		{
			// 1) alloc i/o object for queuing
			var pevent = new executable_socket_on_connect();
			pevent.pSocket = this;
			pevent.Args = _args;

			// 2) add_ref for hold
			add_ref();

			// 3) queuing event
			try
			{
				lock (m_io_queue)
				{
					m_io_queue.enqueue(pevent);
				}
			}
			catch(System.Exception)
			{
				// - release for hold
				release();

				// reraise)
				throw;
			}

			//return)
			return true;
		}
		public void				process_complete_connect_post(SocketAsyncEventArgs _args)
		{
			base.process_complete_connect(_args);
		}

		protected override void process_complete_receive(SocketAsyncEventArgs _args)
		{
			// 1) alloc i/o object for queuing
			var	pevent = new executable_socket_on_receive();
			pevent.pSocket = this;
			pevent.Args = _args;

			// 2) add_ref for hold
			add_ref();

			// 3) queuing event
			try
			{
				lock (m_io_queue)
				{
					m_io_queue.enqueue(pevent);
				}
			}
			catch(System.Exception)
			{
				// - release for hold
				release();

				// reraise)
				throw;
			}
		}
		protected void			process_complete_receive_post(SocketAsyncEventArgs _args)
		{
			base.process_complete_receive(_args);
		}

		public executable_queue io_queue
		{
			get { lock(m_io_queue) { return m_io_queue;} }
			set { lock(m_io_queue) { m_io_queue = value;} }
		}

		private executable_queue m_io_queue;
	}
}