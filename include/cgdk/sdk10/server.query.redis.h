//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        Server Query Redis Classes                         *
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
//-----------------------------------------------------------------------------
//
// CGDK10.server.query.redis
//
//-----------------------------------------------------------------------------
// 1) 
#define	CGDK_SERVER_QUERY_REDIS


// ----------------------------------------------------------------------------
// prototypes
// ----------------------------------------------------------------------------
namespace CGDK
{
	namespace query
	{
		namespace redis
		{
			class session;

			class Iquery;
			class query;
			class querier;
		}
	}

	namespace net
	{
		namespace io
		{
			namespace sender
			{
				class Nresp;
			}

			namespace packetable
			{
				class Nresp;
			}
		}
	}

	class resp_data;
}


// ----------------------------------------------------------------------------
// head File
// ----------------------------------------------------------------------------
// 1) CGDK base header files
#include "cgdk/sdk10/net.socket.h"
#include "cgdk/sdk10/server.query.h"

// 2) sockets
#include "cgdk/sdk10/server.query/redis/net.definitions.resp.h"
#include "cgdk/sdk10/server.query/redis/net.resp.data.h"
#include "cgdk/sdk10/server.query/redis/net.io.packetable.resp.h"
#include "cgdk/sdk10/server.query/redis/net.io.sender.resp.h"

// 3) buffers
#include "cgdk/sdk10/server.query/redis/server.query.redis.definitions.h"
#include "cgdk/sdk10/server.query/redis/server.query.redis.definitions.protocol.h"

// 4) redis Querier/Redis Socket
#include "cgdk/sdk10/server.query/redis/server.query.redis.Iquery.h"
#include "cgdk/sdk10/server.query/redis/server.query.redis.query.h"

#include "cgdk/sdk10/server.query/redis/server.query.redis.querier.h"
#include "cgdk/sdk10/server.query/redis/server.query.redis.session.h"

// 5) class alias
namespace CGDK::query::redis
{
	using querier_t = querier;
	using Iquery_t = Iquery;
	using query_t = query;
}


//----------------------------------------------------------------------------
//
// Libraries
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
				#pragma message("[CGDK10] 'CGDK10.server.query.redis_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.server.query.redis_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.server.query.redis_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.server.query.redis_Windows10.0_x64_Debug.lib")
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
	#error "[CGDK10] Not supported Android Platform"

#elif defined(__APPLE__)
	#error "[CGDK10] Not supported APPLE Platform"

#elif defined(__linux__)

#else
	#error "[CGDK10] Not supported platform"
#endif
