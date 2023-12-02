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
//----------------------------------------------------------------------------
//
// definitions
//
//----------------------------------------------------------------------------
// 1) 
#define	CGDK_NET_SOCKET

// 2) 
#ifndef NDEBUG
	#define	_VALIDATE_SEND_MESSAGE
	#define	_VALIDATE_RECEIVE_MESSAGE
#endif

// 3) disable warning
#if defined(_MSC_VER)
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#pragma warning( disable : 4250)
#endif


//----------------------------------------------------------------------------
// prototypes
//----------------------------------------------------------------------------
namespace CGDK
{
	namespace api
	{
		class socket;
	}

	namespace net
	{
		class sockaddr;

		namespace io
		{
			class Isocket;
			class Ibinder;
			class Iaddress;
			class Iconnect_requestable;
			class Ireconnectable;
			class Iconnective;
			class Iconnectable;
			class Isendable;
			class Isend_request;
			class Isend_sub;
			class Isender;
			class Isender_mass;
			class Isender_datagram;
			class Isender_peer;
			class Isender_closser;
			class Ireceivable_stream;
			class Ireceivable_datagram;
			class Iconnectable_manager;
			class Ipacketable;

			class Naddress;

			class Irestorable;
			class Irestorable_server;
			class Nrestorable_client;
			class Irestore_server;
			template <class> class Nrestore_server;
			class restore_manager;

			namespace socket
			{
				class Nbase;
				class Ndummy;
				class Ntcp;
				class Nudp;

				class Nsocket_secure;
			}

			namespace connectable
			{
				class manager_disconnect;
				class Ntcp;
				class Ndummy;
			}

			namespace binder
			{
				class manager;
				class Ntcp;
				class Nudp;
			}

			namespace receivable
			{
				class Ndatagram;
				class Nstream;
				class Nstream_queue;
				class Nstream_crypt;

				class Nstream_rio;
			}

			namespace messageable
			{
				class Nbase;
			}

			namespace connect_requestable
			{
				class Ntcp;
				class Ntcp_reconnect;
			}

			namespace connective
			{
				class manager;
				class Iacceptor;
				class Iconnector;

				namespace acceptor
				{
					class Ntcp;
					class Ntcp_secure;
				}

				namespace connector
				{
					class Ntcp;
				}
			}

			namespace sendable
			{
				class Itcp_gather;
				class Ntcp_sync;
				class Ntcp_sync_buffered;
				class Ntcp_async;
				class Ntcp_async_gather;
				class Ntcp_async_gather_buffered;

				class Ntcp_async_rio;
				class Ntcp_async_gather_rio;
				class Ntcp_async_gather_buffered_rio;

				class Nudp;

				class Nproxy;

				class Ntcp_crypt;

				class executable_buffer;
				class executable_send;
				class executable_send_buffer;
				class executable_send_buffer_list;
			}

			namespace sender
			{
				template <class> class Ncontainer;

				class Ndatagram;
				class Ndatagram_address;
				class Ndatagram_null_address;
				class Ndatagram_proxy;

				class Nstream;
				template <class> class Nstream_proxy;
				template <class> class Nstream_static_proxy;
				class Nstream_protobuf;

				template <class,class> class Nheader;
				template <class> class Nstream_header;

				template<class> class group_set;
			}

			namespace send_request
			{
				class Nbase;
				class Nproxy;
				class Nudp_resend;
			}

			namespace packetable
			{
				class Ndatagram;
				class Ndatagram_response;

				template <class> struct PRIMITIVE;
				template <class> class Nstream;
				template <int> class Nstream_fixed;
				template <class> class Nstream_seperator;

				class Nstream_protobuf;
				class Nstream_json;
			}

			namespace messageable
			{
				class Nqueue;
				template <class> class Nproxy;
			}

			namespace connectable_manager
			{
				class connectable_manager;
				template <class> class list;
				template <class> class list_keep_alive_passive;
			}

			namespace add_on
			{
				class manager_socket_sustain;
				class Nsocket_sustain;
				class Nkeep_alive;
			}

			namespace statistics
			{
				class Nconnective;
				class Nsocket;
			}

			class executable_connect_requestable;
			class Nudp_resend;
			class Nretransferable;

			class Nsocket_secure;
			class Ntcp_client_crypt;
			class Ntcp_server_crypt;

			class Nhttp_server;
			class Nhttp_client;

			class Irestorable_server;
		}

		namespace ip
		{
			class address;
			class address_v4;
			class address_v6;
			template <class> class basic_endpoint;
		}

		template <class,class> class acceptor;
		template <class,class> class connector;

		namespace socket
		{
			template <class, class> class tcp;
			template <class, class> class tcp_queue;
			template <class, class, class> class tcp_restorable;
			template <class, class> class tcp_buffered;
			class tcp_protobuf;

			template <class, class> class tcp_client;
			template <class, class> class tcp_client_reconnect;

			template <class, class> class tcp_client_crypt;
			template <class, class> class tcp_server;
			template <class, class> class tcp_server_no_gather;
			template <class, class> class tcp_server_crypt;

			class udp;
			class udp_resend;
		}
	}

	namespace statistics
	{
		struct connective;
		struct traffic;
	}
}

#if !defined(_MSC_VER)
	#define	IPPROTO_RESERVED_MAX	261
#endif


//----------------------------------------------------------------------------
//
// head files
//
//----------------------------------------------------------------------------
// 1) socket header files
#if defined(_WIN32)
	#include <Ws2tcpip.h>
	#include <Mswsock.h>
	#include <mstcpip.h>

	#if !defined(_MSC_VER)
		#include <in6addr.h>
	#endif
#else
	// - socket
	#include <sys/socket.h>
	#include <sys/ioctl.h>
	#include <arpa/inet.h>
	#include <netinet/tcp.h>
	#include <netdb.h>
	#include <fcntl.h>

	// - epoll
	#include <sys/epoll.h>

	// - aio
	#include <aio.h>
	#include <linux/aio_abi.h>
#endif

// Undefinitions) 
#undef max

// 2) object system
#include "cgdk/sdk10/system.object.h"

// 3) definitionsr
#include "cgdk/sdk10/net.socket/socket/net.definitions.socket.protocol.h"
#include "cgdk/sdk10/net.socket/socket/net.definitions.socket.h"

// 4) ip
#include "cgdk/sdk10/net.socket/socket/net.ip.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.address_v4.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.address_v6.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.address.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.network_v4.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.network_v6.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.network.h"
#include "cgdk/sdk10/net.socket/socket/net.sockaddr.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.basic_endpoint.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.resolver_base.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.basic_resolver_entry.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.basic_resolver_result.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.basic_resolver.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.tcp.h"
#include "cgdk/sdk10/net.socket/socket/net.ip.udp.h"

#include "cgdk/sdk10/net.socket/socket/net.definitions.io.restorable.h"
#include "cgdk/sdk10/net.socket/socket/net.definitions.parameters.h"

// 5) statistics & API
#include "cgdk/sdk10/net.socket/socket/net.statistics.h"
#include "cgdk/sdk10/net.socket/socket/api.net.socket.h"

// 6) messages
#include "cgdk/sdk10/net.socket/socket/net.message.h"


//----------------------------------------------------------------------------
// interface classes
//----------------------------------------------------------------------------
// 1) interfaces
#include "cgdk/sdk10/net.socket/socket/net.io.Iaddress.h"
#include "cgdk/sdk10/net.socket/socket/net.io.Isocket.h"
#include "cgdk/sdk10/net.socket/socket/net.io.Iconnect_requestable.h"
#include "cgdk/sdk10/net.socket/socket/net.io.Ireconnectable.h"
#include "cgdk/sdk10/net.socket/socket/net.io.Iconnectable.h"
#include "cgdk/sdk10/net.socket/socket/net.io.Isend_request.h"
#include "cgdk/sdk10/net.socket/socket/net.io.Isendable.h"
#include "cgdk/sdk10/net.socket/socket/net.io.Isender.h"
#include "cgdk/sdk10/net.socket/socket/net.io.Ireceivable_stream.h"
#include "cgdk/sdk10/net.socket/socket/net.io.Ireceivable_datagram.h"
#include "cgdk/sdk10/net.socket/socket/net.io.Ipacketable.h"

// 2) managers
#include "cgdk/sdk10/net.socket/socket/net.io.binder.manager.h"
#include "cgdk/sdk10/net.socket/socket/net.io.connective.manager.h"
#include "cgdk/sdk10/net.socket/socket/net.io.connectable_manager.h"

// 3) binder
#include "cgdk/sdk10/net.socket/socket/net.io.Ibinder.h"

// 4) connective
#include "cgdk/sdk10/net.socket/socket/net.io.Iconnective.h"
#include "cgdk/sdk10/net.socket/socket/net.io.connective.Iacceptor.h"
#include "cgdk/sdk10/net.socket/socket/net.io.connective.Iconnector.h"


//----------------------------------------------------------------------------
// component classes
//----------------------------------------------------------------------------
// 1) address
#include "cgdk/sdk10/net.socket/socket/net.io.address.h"

// 2) socket
#include "cgdk/sdk10/net.socket/socket/net.io.socket.h"
#include "cgdk/sdk10/net.socket/socket/net.io.socket.tcp.h"
#include "cgdk/sdk10/net.socket/socket/net.io.socket.udp.h"

// 3) bindable
#include "cgdk/sdk10/net.socket/socket/net.io.binder.tcp.h"
#include "cgdk/sdk10/net.socket/socket/net.io.binder.udp.h"

// 4) connect_requestable
#include "cgdk/sdk10/net.socket/socket/net.io.connect_requestable.tcp.h"
#include "cgdk/sdk10/net.socket/socket/net.io.connect_requestable.tcp_reconnect.h"
#include "cgdk/sdk10/net.socket/socket/net.io.executable.connect_requestable.h"

// 5) connectable
#include "cgdk/sdk10/net.socket/socket/net.io.connectable.tcp.h"

// 6) connectable manager
#include "cgdk/sdk10/net.socket/socket/net.io.connectable_manager.list.h"

// 7) acceptor
#include "cgdk/sdk10/net.socket/socket/net.io.connective.acceptor_tcp.h"
#include "cgdk/sdk10/net.socket/socket/net.io.connective.connector_tcp.h"

// 8) sendable
#if defined(_WINSOCK2API_)
	#include "cgdk/sdk10/net.socket/socket/net.io.sendable.executable_send_buffer_list.h"
#endif
#include "cgdk/sdk10/net.socket/socket/net.io.sendable.Itcp_gather.h"
#include "cgdk/sdk10/net.socket/socket/net.io.sendable.tcp_sync.h"
#include "cgdk/sdk10/net.socket/socket/net.io.sendable.tcp_sync_buffered.h"
#include "cgdk/sdk10/net.socket/socket/net.io.sendable.tcp_async.h"
#include "cgdk/sdk10/net.socket/socket/net.io.sendable.tcp_async_gather.h"
#include "cgdk/sdk10/net.socket/socket/net.io.sendable.tcp_async_gather_buffered.h"
#include "cgdk/sdk10/net.socket/socket/net.io.sendable.tcp_crypt.h"
#include "cgdk/sdk10/net.socket/socket/net.io.sendable.udp.h"
#if defined(_WINSOCK2API_)
	#include "cgdk/sdk10/net.socket/socket/net.io.sendable.tcp_async.rio.h"
	#include "cgdk/sdk10/net.socket/socket/net.io.sendable.tcp_async_gather.rio.h"
	//#include "cgdk/sdk10/net.socket/socket/net.io.sendable.tcp_async_gather_buffered.rio.h"
#endif

// 9) send requestor
#include "cgdk/sdk10/net.socket/socket/net.io.send_request.h"
#include "cgdk/sdk10/net.socket/socket/net.io.send_request.udp_resend.h"

// 10) sender
#include "cgdk/sdk10/net.socket/socket/net.io.sender.stream.h"
#include "cgdk/sdk10/net.socket/socket/net.io.sender.stream_header.h"
#include "cgdk/sdk10/net.socket/socket/net.io.sender.datagram.h"
#include "cgdk/sdk10/net.socket/socket/net.io.sender.group.h"

// 11) receivable
#include "cgdk/sdk10/net.socket/socket/net.io.receivable.stream.h"
#include "cgdk/sdk10/net.socket/socket/net.io.receivable.datagram.h"
#include "cgdk/sdk10/net.socket/socket/net.io.receivable.stream_queue.h"
#include "cgdk/sdk10/net.socket/socket/net.io.receivable.stream_crypt.h"
#if defined(_WINSOCK2API_)
	#include "cgdk/sdk10/net.socket/socket/net.io.receivable.stream.rio.h"
#endif

// 12) packetable
#include "cgdk/sdk10/net.socket/socket/net.io.packetable.stream.h"
#include "cgdk/sdk10/net.socket/socket/net.io.packetable.stream_json.h"
#include "cgdk/sdk10/net.socket/socket/net.io.packetable.datagram.h"
#include "cgdk/sdk10/net.socket/socket/net.io.packetable.datagram_response.h"

// 13) messageable
#include "cgdk/sdk10/net.socket/socket/net.io.messageable.h"
#include "cgdk/sdk10/net.socket/socket/net.io.messageable.queue.h"

// 14) add_on
#include "cgdk/sdk10/net.socket/socket/net.io.add_on.socket_sustain.h"
#include "cgdk/sdk10/net.socket/socket/net.io.add_on.keep_alive.h"

// 15) i/o package
#include "cgdk/sdk10/net.socket/socket/net.io.udp_resend.h"

// 16) composition
#include "cgdk/sdk10/net.socket/socket/net.io.retransferable.h"
#include "cgdk/sdk10/net.socket/socket/net.io.tcp_client.crypt.h"
#include "cgdk/sdk10/net.socket/socket/net.io.tcp_server.crypt.h"
#include "cgdk/sdk10/net.socket/socket/net.io.socket_secure.h"

// 17) etc
#include "net.socket/socket/message.remote_request.h"

// 18) restore
#include "cgdk/sdk10/net.socket/socket/net.io.Irestorable.h"
#include "cgdk/sdk10/net.socket/socket/net.io.Irestore_server.h"
#include "cgdk/sdk10/net.socket/socket/net.io.restorable_client.h"
#include "cgdk/sdk10/net.socket/socket/net.io.restorable_server.h"
#include "cgdk/sdk10/net.socket/socket/net.io.restore_manager.h"


//----------------------------------------------------------------------------
// templates
//----------------------------------------------------------------------------
// 1) acceptor
#include "cgdk/sdk10/net.socket/socket/net.acceptor.h"
#include "cgdk/sdk10/net.socket/socket/net.acceptor.normal.h"

// 2) connector
#include "cgdk/sdk10/net.socket/socket/net.connector.h"
#include "cgdk/sdk10/net.socket/socket/net.connector.normal.h"

// 3) socket - tcp
#include "cgdk/sdk10/net.socket/socket/net.socket.tcp.h"
#include "cgdk/sdk10/net.socket/socket/net.socket.tcp_queue.h"
#include "cgdk/sdk10/net.socket/socket/net.socket.tcp_retransferable.h"
#include "cgdk/sdk10/net.socket/socket/net.socket.tcp_buffered.h"
#include "cgdk/sdk10/net.socket/socket/net.socket.tcp_client.crypt.h"

// 3) socket - tcp client (connect_requestable socket)
#include "cgdk/sdk10/net.socket/socket/net.socket.tcp_client.h"
#include "cgdk/sdk10/net.socket/socket/net.socket.tcp_client_reconnect.h"
#include "cgdk/sdk10/net.socket/socket/net.socket.tcp_client.crypt.h"

// 5) socket - udp
#include "cgdk/sdk10/net.socket/socket/net.socket.udp.h"
#include "cgdk/sdk10/net.socket/socket/net.socket.udp_resend.h"


//----------------------------------------------------------------------------
//
// libraries
//
//----------------------------------------------------------------------------
#if defined(_MSC_VER)

	#if !defined(_MSC_PLATFORM_TOOLSET)
		#if _MSC_VER>=_MSC_VER_2022
			#define	_MSC_PLATFORM_TOOLSET	143
		#elif _MSC_VER>=_MSC_VER_2019
			#define	_MSC_PLATFORM_TOOLSET	142
		#elif _MSC_VER>=_MSC_VER_2017
			#define	_MSC_PLATFORM_TOOLSET	141
		#elif _MSC_VER>=_MSC_VER_2015
			#define	_MSC_PLATFORM_TOOLSET	140
		#elif _MSC_VER>=_MSC_VER_2013
			#define	_MSC_PLATFORM_TOOLSET	120
		#elif _MSC_VER>=_MSC_VER_2012
			#define	_MSC_PLATFORM_TOOLSET	110
		#elif _MSC_VER>=_MSC_VER_2010
			#define	_MSC_PLATFORM_TOOLSET	100
		#elif _MSC_VER>=_MSC_VER_2008
			#define	_MSC_PLATFORM_TOOLSET	90
		#else
			#define	_MSC_PLATFORM_TOOLSET	80
		#endif
	#endif

	#if !defined(_LIB) || defined(_CONSOLE)

	// 1) Default socket 
	#pragma comment(lib,"ws2_32.lib")


	//----------------------------------------------------------------------------
	// * WinSDK 10
	//----------------------------------------------------------------------------
	#if defined(WDK_NTDDI_VERSION)

		// check) 
		#if !defined(_M_X64)
			#error "[CGDK10] No WIN32-x86. Please use x64"
		#endif

		// check) 
		#ifndef _DLL 
			#error "[CGDK10] No Multi-Thread(/MT) or Multi-Thread Debug(/MTd). use Multi-thread DLL(/MD) or Multi-thread DLL Debug(/MDd)"
		#endif

		// WinSDK 10
		#if WDK_NTDDI_VERSION >= NTDDI_WIN10
			#ifdef NDEBUG
				#pragma message("[CGDK10] 'CGDK10.net.socket_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.net.socket_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.net.socket_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.net.socket_Windows10.0_x64_Debug.lib")
			#endif
		// Error - No supported
		#else
			#error "[CGDK10] Not supported Windonws SDK version (Need Windows SDK 10.0 or higher)"
		#endif

	#else
		#error "[CGDK10] Not supported platform toolset (require visual studio 2019 or higher)"
	#endif

	#endif

#elif defined(__ANDROID__)
#elif defined(__APPLE__)
#elif defined(__linux__)
#else
	#error "[CGDK10] Not supported Platform"
#endif

