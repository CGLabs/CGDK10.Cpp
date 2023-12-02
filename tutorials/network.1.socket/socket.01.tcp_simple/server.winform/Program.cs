//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                    for C# Ver 2.0 / Release 2019.12.11                    *
//*                                                                           *
//*               tutorials socket - tcp_simple.server.winform                *
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
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

// ----------------------------------------------------------------------------
//
// tutorial socket. - tcp simple.winform
//
// tutorial socket - tcp_simple�� ������ Ʃ�͸����̴�. �ٸ� �÷����� UI�� winform����
// �� ������ �Ӵ�.
// 
// ----------------------------------------------------------------------------
namespace tutorial_socket_01_tcp_simple_server_winform
{
	static class Program
	{
		[STAThread]
		static void Main()
		{
			try
			{
				// 1) create acceptor
				var acceptor_test = new CGDK.net.acceptor<socket_tcp>();

				// 2) listen on 20000 port
				acceptor_test.start(20000);

				// 3) wait until input 'ESC key'
				while (Console.ReadKey().Key != ConsoleKey.Escape) ;

				// 4) close acceptor
				acceptor_test.stop();
			}
			catch (Exception e)
			{
				Console.WriteLine(e.ToString());
			}
		}
	}
}
