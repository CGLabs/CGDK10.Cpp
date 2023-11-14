//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              license Classes                              *
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
// Class Definition
//-----------------------------------------------------------------------------
#define	CGDK_SYSTEM_LICENSE


//----------------------------------------------------------------------------
// Proto...
//----------------------------------------------------------------------------
// 1) common
#include "cgdk/sdk10/system.object.h"


//----------------------------------------------------------------------------
// Proto...
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Header Files
//----------------------------------------------------------------------------
// 1) ...



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
				#pragma message("[CGDK10] 'system.license_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.system.license_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'system.license_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.system.license_Windows10.0_x64_Debug.lib")
			#endif
		// Error - No supported
		#else
			#error "[CGDK10] Not supported platform toolset (Need Visual studio 2019 or higher)"
		#endif

	#else
		#error "[CGDK10] Not supported platform toolset (Need Visual studio 2019 or higher)"
	#endif

	#endif


#elif defined(__ANDROID__)
	#if !defined(_LIB) || defined(_CONSOLE)
	//----------------------------------------------------------------------------
	// * ARM
	//----------------------------------------------------------------------------
	//// Case) ARM64
	//#if !defined(__arm__)
	//	//1) DLL version老 锭
	//	//#ifdef _DLL 
	//		#ifdef NDEBUG
	//			#pragma comment(lib,"CGObjectClasses_ARM64_Clang_3_8_release_dynamic")
	//		#else
	//			#pragma comment(lib,"CGObjectClasses_ARM64_Clang_3_8_debug_dynamic")
	//		#endif

	//	//2) Static Library老 版快
	//	#else
	//		#ifdef NDEBUG
	//			#pragma comment(lib,"CGObjectClasses_ARM64_Clang_3_8_Release")
	//		#else
	//			#pragma comment(lib,"CGObjectClasses_ARM64_Clang_3_8_Debug")
	//		#endif
	//	#endif
	//// Case) ARM
	//#else
	//	//#ifdef _DLL 
	//		#ifdef NDEBUG
	//			#pragma comment(lib,"CGObjectClasses_ARM_Clang_3_8_release_dynamic")
	//		#else
	//			#pragma comment(lib,"CGObjectClasses_ARM_Clang_3_8_debug_dynamic")
	//		#endif

	//	//2) Static Library老 版快
	//	#else
	//		#ifdef NDEBUG
	//			#pragma comment(lib,"CGObjectClasses_ARM_Clang_3_8_Release")
	//		#else
	//			#pragma comment(lib,"CGObjectClasses_ARM_Clang_3_8_Debug")
	//		#endif
	//	#endif
	//#endif

	#endif
#elif defined(__APPLE__)
	#if !defined(_LIB) || defined(_CONSOLE)
	//----------------------------------------------------------------------------
	// * IOS
	//----------------------------------------------------------------------------

	#endif

#elif defined(__linux__)
	////1) DLL 老 版快
	//#ifdef _DLL 
	//	#ifdef NDEBUG
	//		#pragma message("[CGDK10] lib file [libCGObjectClasses_Linux_Generic_x64_release_dynamic.so] will be linked")
	//		#pragma comment(lib,"CGObjectClasses_Linux_Generic_x64_release_dynamic")
	//	#else
	//		#pragma message("[CGDK10] lib file [libCGObjectClasses_Linux_Generic_x64_debug_dynamic.so] will be linked")
	//		#pragma comment(lib,"CGObjectClasses_Linux_Generic_x64_debug_dynamic")
	//	#endif

	////2) Static Library老 版快
	//#else
	//	#ifdef NDEBUG
	//		#pragma message("[CGDK10] lib file [libCGObjectClasses_Linux_Generic_x64_Release.a] will be linked")
	//		#pragma comment(lib,"libCGObjectClasses_Linux_Generic_x64_Release.a")
	//	#else
	//		#pragma message("[CGDK10] lib file [libCGObjectClasses_Linux_Generic_x64_Debug.a] will be linked")
	//		#pragma comment(lib,"libCGObjectClasses_Linux_Generic_x64_Debug.a")
	//	#endif
	//#endif

#else
		#error "[CGDK10] Not supported platform"
#endif

