//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                             web server classes                            *
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
// Prototype
// ----------------------------------------------------------------------------
// 1) ...
#define	CGDK_SERVER_WEB


namespace CGDK
{
	namespace server
	{
		namespace web
		{
			class Ientity;
			class Ientitable;

			namespace entity
			{
				class Inode;
				class Iresource;
				class Itext;
				class Iapplication;

				class folder;
				class text;
				class application;
				class resource;
			}
		}
	}

	namespace net
	{
		namespace socket
		{
			class web_server;
		}

		template <class TSOCKET = socket::web_server> class acceptor_web_server;
	}
}


//----------------------------------------------------------------------------
//
// standard head files
//
//----------------------------------------------------------------------------
// 1) CGDK base header files
#include "cgdk/sdk10/net.socket.http.h"
#include "cgdk/sdk10/server.group.h"

// 2) filesystem
#include <filesystem>

// 3) definitions
#include "cgdk/sdk10/server.web/web/server_web.definitions_message.h"
#include "cgdk/sdk10/server.web/web/server_web.definitions.h"

// 4) interfaces
#include "cgdk/sdk10/server.web/web/server_web.Ientity.h"
#include "cgdk/sdk10/server.web/web/server_web.Ientitable.h"

// 5) socket for web server
#include "cgdk/sdk10/server.web/web/server_web.socket.h"
#include "cgdk/sdk10/server.web/web/net.acceptor.web_server.h"

// 6) web entities
#include "cgdk/sdk10/server.web/web/server_web.entity.Itext.h"
#include "cgdk/sdk10/server.web/web/server_web.entity.text.h"

#include "cgdk/sdk10/server.web/web/server_web.entity.Iapplication.h"
#include "cgdk/sdk10/server.web/web/server_web.entity.application.h"

#include "cgdk/sdk10/server.web/web/server_web.entity.Iresource.h"
#include "cgdk/sdk10/server.web/web/server_web.entity.resource.h"

#include "cgdk/sdk10/server.web/web/server_web.entity.Inode.h"
#include "cgdk/sdk10/server.web/web/server_web.entity.folder.h"


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
				#pragma message("[CGDK10] 'CGDK10.server.web_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib,"cgdk/sdk10/windows/CGDK10.server.web_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.server.web_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib,"cgdk/sdk10/windows/CGDK10.server.web_Windows10.0_x64_Debug.lib")
			#endif
		// Error - No supported
		#else
			#error "[CGDK10] Not supported Windonws SDK version (Need Windows SDK 10.0 or higher)"
		#endif

	#else
		#error "[CGDK10] Not supported Platform toolset (Need Visual studio 2017 or higher)"
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

