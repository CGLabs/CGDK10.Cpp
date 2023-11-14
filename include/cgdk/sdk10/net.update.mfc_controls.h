//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                      MFC Controls for Update Classes                      *
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
//  Prototype
//----------------------------------------------------------------------------
#define	CGNET_SOCKET_MFC_CONTROLS

#ifdef _CGNETSOCKETMFCCONTROLS_EXT
	#define CGNETUPDATEMFCCONTROL_EXT_API	__declspec(dllexport)
	#define CGNETUPDATEMFCCONTROL_EXT_CLASS	__declspec(dllexport)
	#define CGNETUPDATEMFCCONTROL_EXT_DATA	__declspec(dllexport)
#else
	#define CGNETUPDATEMFCCONTROL_EXT_API	__declspec(dllimport)
	#define CGNETUPDATEMFCCONTROL_EXT_CLASS	__declspec(dllimport)
	#define CGNETUPDATEMFCCONTROL_EXT_DATA	__declspec(dllimport)
#endif


//----------------------------------------------------------------------------
//  head Fileµé                                                               
//----------------------------------------------------------------------------
// 1) CGCII Header files
#include "cgdk/sdk10/CGMFCControls.h"
#include "cgdk/sdk10/CGNetUpdateClasses.h"

// 2) Child Dialog
#include "cgdk/sdk10/Network/Update/CGNetUpdateMFCControls/CGChildTransferControl.h"


//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#ifndef _CGNETUPDATEMFCCONTROLS_EXT

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

		// check) 
		#ifndef _UNICODE 
			#error "[CGDK10] No Multibyte character set. use UNICODE character set"
		#endif

		// WinSDK 10
		#if WDK_NTDDI_VERSION >= NTDDI_WIN10
			#ifdef NDEBUG
				#pragma message("[CGDK10] 'CGDK10.net.update.mfc_controls_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib,"CGDK10.net.update.mfc_controls_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.net.update.mfc_controls_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib,"CGDK10.net.update.mfc_controls_Windows10.0_x64_Debug.lib")
			#endif
		// Error - No supported
		#else	
			#error "[CGDK10] Not supported Windonws SDK version (Need Windows SDK 10.0 or higher)"
		#endif

	#else
		#error "[CGDK10] Not supported Platform toolset (Need Visual studio 2019 or higher)"
	#endif
#endif