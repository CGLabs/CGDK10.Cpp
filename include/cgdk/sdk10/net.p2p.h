//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            network p2p classes                            *
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
//  definitions
//----------------------------------------------------------------------------
namespace CGDK
{
	namespace net
	{
		namespace io
		{
			namespace send_request
			{
				class Nudp_reliable;
				class Nudp_sequenced;
				class Nudp_reliable;
				class Nudp_sequenced;
			}

			namespace send_sub
			{
				template <class TPEER> class Nmultiplexer;
			}

			namespace messageable
			{
				template <class TPEER> class Ndemultiplexer;
				template <class TPEER> class Ndemultiplexer_direct;
				template <class TPEER> class Ndemultiplexer_cross;
			}

			namespace packetable
			{
				class Ndatagram_sequenced;
			}

			namespace peer
			{
				class Nbase;
				class Naddress;

				class simple;
				class sequenced;
				class address_sequenced;
				class address;
			}

			class Nudp_sequenced;
			class Nudp_reliable_ordered;
			class Nudp_reliable;

			template <class TPEER> class Nmultiplexer_cross;
			template <class TPEER> class Nmultiplexer_direct;
		}

		namespace peer
		{
			class address;
			class address_sequenced;

			template <class TPEER> class address_multiplexer;
			template <class TPEER> class multiplexer;

			class simple;
			class sequenced;
			class reliable;
			class reliable_ordered;

			class udp_reliable;
			class udp_reliable_sequenced;
		}

		namespace socket_peer
		{
			class Nbase;
		}

		namespace socket
		{
			template <class TPEER> class udp_multiplexer_cross;
			template <class TPEER> class udp_multiplexer_direct;
			class udp_sequenced;
			class udp_reliable;
			class udp_reliable_ordered;
		}
	}
}

//----------------------------------------------------------------------------
//  head Fileµé                                                               
//----------------------------------------------------------------------------
// 1) base classes
#include "cgdk/sdk10/net.socket.h"

// 2) definitions
//#include "cgdk/sdk10/net.p2p/p2p/definitions.p2p.protocol.h"
//#include "cgdk/sdk10/net.p2p/p2p/definitions.p2p.h"

// 3) io component
//#include "cgdk/sdk10/net.p2p/p2p/net.io.packetable.datagram_sequenced.h"

//#include "cgdk/sdk10/net.p2p/p2p/net.io.messageable.multiplexer.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.io.messageable.multiplexer_direct.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.io.messageable.multiplexer_cross.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.io.send_sub.multiplexer.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.io.peer.base.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.io.peer.address.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.io.send_request.udp_sequenced.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.io.send_request.udp_reliable.h"

//#include "cgdk/sdk10/net.p2p/p2p/net.io.udp_sequenced.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.io.udp_reliable.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.io.udp_reliable_ordered.h"

//#include "cgdk/sdk10/net.p2p/p2p/net.io.multiplexer.direct.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.io.multiplexer.cross.h"

// 4) peer
//#include "cgdk/sdk10/net.p2p/p2p/net.peer.address.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.peer.address.sequenced.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.peer.address.multiplexer.h"

//#include "cgdk/sdk10/net.p2p/p2p/net.peer.udp.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.peer.sequenced.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.peer.reliable.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.peer.reliable_ordered.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.peer.multiplexer.h"

// 5) socket
//#include "cgdk/sdk10/net.p2p/p2p/net.socket.udp_multiplexer_direct.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.socket.udp_multiplexer_cross.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.socket.udp_sequenced.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.socket.udp_reliable.h"
//#include "cgdk/sdk10/net.p2p/p2p/net.socket.udp_reliable_ordered.h"

// 6) socket peer
//#include "cgdk/sdk10/net.p2p/p2p/socket.peer.base.h"


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
				#pragma message("[CGDK10] 'CGDK10.net.p2p_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.net.p2p_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.net.p2p_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.net.p2p_Windows10.0_x64_Debug.lib")
			#endif
		// Error - No supported
		#else
			#error "[CGDK10] Not supported Windonws SDK version (Need Windows SDK 10.0 or higher)"
		#endif

	#else
		#error "[CGDK10] Not supported Platform toolset (Need Visual studio 2019 or higher)"
	#endif

	#endif

#elif defined(__ANDROID__)
#elif defined(__APPLE__)
#elif defined(__linux__)
#else
	#error "[CGDK10] Not supported Platform"
#endif

