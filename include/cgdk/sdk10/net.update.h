//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network update classes                           *
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
	namespace resource
	{
		class Iupdatable;
		class Iupdatable_bundle;
		namespace updatable
		{
			class file;
			class file_stream;
			class folder;
		}
	}

	namespace update
	{
		class Ireceivable;
		class Ireceiver;
		class Isendable;
		class Isender;

		namespace receivable
		{
			class file;
			class folder;
		}

		namespace sendable
		{
			class file;
			class folder;
		}

		class Nreceiver;
		class receiver;
		class Nsender;
		class sender;
		class sender_lambda;

		class resource_manager;
		class md5_caching;
	}
}

//----------------------------------------------------------------------------
// head Fileµé
//----------------------------------------------------------------------------
// 1) base classes
#include "cgdk/sdk10/net.socket.h"


// 3) definitions
#include "cgdk/sdk10/net.update/update/net.definitions.update.h"
#include "cgdk/sdk10/net.update/update/net.definitions.update.protocol.h"

// 4) resource
#include "cgdk/sdk10/net.update/update/resource.Iupdatable.h"
#include "cgdk/sdk10/net.update/update/resource.updatable.file.h"
#include "cgdk/sdk10/net.update/update/resource.updatable.file_stream.h"
#include "cgdk/sdk10/net.update/update/resource.updatable.folder.h"


// 5) Interface classes
//#include "cgdk/sdk10/net.update/update/Iresource.transferable.h"
#include "cgdk/sdk10/net.update/update/net.update.Isendable.h"
#include "cgdk/sdk10/net.update/update/net.update.Ireceivable.h"

// 6) sender 
#include "cgdk/sdk10/net.update/update/net.update.Nsender.h"
#include "cgdk/sdk10/net.update/update/net.update.sender.h"
#include "cgdk/sdk10/net.update/update/net.update.sender_lambda.h"
#include "cgdk/sdk10/net.update/update/net.update.Nreceiver.h"
#include "cgdk/sdk10/net.update/update/net.update.receiver.h"
#include "cgdk/sdk10/net.update/update/net.update.receiver_lambda.h"

// 7) for sendable
#include "cgdk/sdk10/net.update/update/net.update.sendable.file.h"

// 8) for receiver
#include "cgdk/sdk10/net.update/update/net.update.receivable.file.h"

// 9) sender/receiver
//#include "cgdk/sdk10/net.update/update/net.io.update.sender.h"
//#include "cgdk/sdk10/net.update/update/net.io.update.receiver.h"

// 10)
#include "cgdk/sdk10/net.update/update/update.resource_manager.h"
#include "cgdk/sdk10/net.update/update/update.file_md5_caching..h"


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
	// * WinSDK
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
				#pragma message("[CGDK10] 'CGDK10.net.update_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib,"cgdk/sdk10/CGDK10.net.update_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.net.update_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib,"cgdk/sdk10/CGDK10.net.update_Windows10.0_x64_Debug.lib")
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
#elif defined(__linux__)
#elif defined(__APPLE__)
#else
	#error "[CGDK10] Not supported platform"
#endif
