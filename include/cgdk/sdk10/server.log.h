//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            Server Log Classes                             *
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
// Definitions
//----------------------------------------------------------------------------
#define	CGSERVER_LOG_CLASSES

namespace CGDK
{
	class Nlogger;
	class logger_acceptor;
	class logger_console;
	class logger_file;
	class logger_hub;
	class logger_hub_archive;
	class logger_slack;
	class logger_socket;
	class logger_buffer;
	class log_archive;

	class log_filter;
}



//----------------------------------------------------------------------------
// head Fileµé
//----------------------------------------------------------------------------
// 1) CGDK headers
#include "cgdk/sdk10/net.socket.h"

// 2) definitions
#include "cgdk/sdk10/server.system/log/server.definitions.log.h"
#include "cgdk/sdk10/server.system/log/server.definitions.log.protocol.h"

// 3) logger
#include "cgdk/sdk10/server.system/log/server.Nlogger.h"
#include "cgdk/sdk10/server.system/log/server.logger_acceptor.h"
#include "cgdk/sdk10/server.system/log/server.logger_console.h"
#include "cgdk/sdk10/server.system/log/server.logger_file.h"
#include "cgdk/sdk10/server.system/log/server.logger_hub.h"
#include "cgdk/sdk10/server.system/log/server.logger_hub_archive.h"
#include "cgdk/sdk10/server.system/log/server.logger_slack.h"
#include "cgdk/sdk10/server.system/log/server.logger_socket.h"
#include "cgdk/sdk10/server.system/log/server.logger_buffer.h"
#include "cgdk/sdk10/server.system/log/server.logger_syslog.h"

// 4) log filter
#include "cgdk/sdk10/server.system/log/server.log_filter.default.h"


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

	// 1) Windows Internet Library
	#pragma comment(lib,"Wininet.lib")


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
				#pragma message("[CGDK10] 'CGDK10.server.log_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/windows/CGDK10.server.log_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.server.log_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/windows/CGDK10.server.log_Windows10.0_x64_Debug.lib")
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
	#error "[CGDK10] Not supported Android Platform"

#elif defined(__APPLE__)
	#error "[CGDK10] Not supported APPLE Platform"

#elif defined(__linux__)

#else
	#error "[CGDK10] Not supported platform"
#endif

