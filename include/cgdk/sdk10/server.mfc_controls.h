//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                         Server Admin MFC Controls                         *
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
#define	CGSERVERMFCCONTROL_CONTROLS

#ifdef _CGSERVERMFCCONTROL_EXT
	#define CGSERVERMFCCONTROL_EXT_API		__declspec(dllexport)
	#define CGSERVERMFCCONTROL_EXT_CLASS	__declspec(dllexport)
	#define CGSERVERMFCCONTROL_EXT_DATA		__declspec(dllexport)
#else
	#define CGSERVERMFCCONTROL_EXT_API		__declspec(dllimport)
	#define CGSERVERMFCCONTROL_EXT_CLASS	__declspec(dllimport)
	#define CGSERVERMFCCONTROL_EXT_DATA		__declspec(dllimport)
#endif


//----------------------------------------------------------------------------
//  head Fileµé                                                               
//----------------------------------------------------------------------------
// 1) CGServerAdminClasees
#include "cgdk/sdk10/server.log.h"
#include "cgdk/sdk10/server.time_event.h"
#include "cgdk/sdk10/server.service.h"
#include "cgdk/sdk10/system.mfc_controls.h"

// 2) Child Dialog
#include "cgdk/sdk10/server.system/mfc_controls/child_event_list.h"
#include "cgdk/sdk10/server.system/mfc_controls/child_logger_view.h"
#include "cgdk/sdk10/server.system/mfc_controls/child_logger_view_ex.h"

// 3) ...
#include "cgdk/sdk10/server.system/mfc_controls/time_event_info_dlg.h"


//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#ifndef _CGSERVERMFCCONTROL_EXT

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
				#pragma message("[CGDK10] 'CGDK10.server.mfc_controls_Windows10.0_x64_Release_Dynamic.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/windows/CGDK10.server.mfc_controls_Windows10.0_x64_Release_Dynamic.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.server.mfc_controls_Windows10.0_x64_Debug_Dynamic.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/windows/CGDK10.server.mfc_controls_Windows10.0_x64_Debug_Dynamic.lib")
			#endif
		// Error - No supported
		#else
			#error "[CGDK10] Not supported Windonws SDK version (Need Windows SDK 10.0 or higher)"
		#endif

	#else
		#error "[CGDK10] Not supported Platform toolset (Need Visual studio 2019 or higher)"
	#endif
#endif