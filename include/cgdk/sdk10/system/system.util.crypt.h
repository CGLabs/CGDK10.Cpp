//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object Classes                               *
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
#define	CGDK_SYSTEM_UTIL_CRYPT


//----------------------------------------------------------------------------
// prototypes
//----------------------------------------------------------------------------
namespace CGDK
{
	namespace crypt
	{
		class ssl_manager;
		class ssl_context;
		class ssl;
	}
}

struct ssl_method_st;
using SSL_METHOD = struct ssl_method_st;
struct ssl_st;
using SSL = struct ssl_st;
struct ssl_ctx_st;
using SSL_CTX = struct ssl_ctx_st;
struct bio_st;
using BIO = struct bio_st;


//----------------------------------------------------------------------------
//
// head files
//
//----------------------------------------------------------------------------
// 1) CGDK base header files
#include "cgdk/sdk10/system.object.h"

// 2) definitions
#include "cgdk/sdk10/system/util.crypt/definitions.util.h"

// 3) cryto
#include "cgdk/sdk10/system/util.crypt/util.crypt.pn_code.h"
#include "cgdk/sdk10/system/util.crypt/util.crypt.rsa.h"
#include "cgdk/sdk10/system/util.crypt/util.crypt.bcrypt.h"

// 4) open ssl
#include "cgdk/sdk10/system/util.crypt/util.crypt.ssl.h"
#include "cgdk/sdk10/system/util.crypt/util.crypt.ssl.context.h"
#include "cgdk/sdk10/system/util.crypt/util.crypt.ssl.manager.h"


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

	#pragma comment(lib, "openssl/libcrypto.lib")
	#pragma comment(lib, "openssl/libssl.lib")
	//#pragma comment(lib, "openssl/libeay32.lib")
	//#pragma comment(lib, "openssl/ssleay32.lib")

	//----------------------------------------------------------------------------
	// * Windws
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
				#pragma message("[CGDK10] 'CGDK10.system.util.crypt_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.system.util.crypt_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.system.util.crypt_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.system.util.crypt_Windows10.0_x64_Debug.lib")
			#endif
		// Error - No supported
		#else
			#error "[CGDK10] Not supported Windonws SDK version (Need Windows SDK 10.0 or higher)"
		#endif
	#endif

	#endif

#elif defined(__ANDROID__)
#elif defined(__APPLE__)
#elif defined(__linux__)
#else
		#error "[CGDK10] Not supported platform"
#endif

