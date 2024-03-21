//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          Server DB MFC Controls                           *
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
// CGDK10.server.query.mfc_controls
//
//-----------------------------------------------------------------------------
// 1) 
#define	CGDK_SERVER_QUERY_MFC_CONTROLS

// 2) 
#ifdef _CGSERVERQUERYMFCCONTROLS_EXT
	#define CGSERVERQUERYMFCCONTROL_EXT_API		__declspec(dllexport)
	#define CGSERVERQUERYMFCCONTROL_EXT_CLASS	__declspec(dllexport)
	#define CGSERVERQUERYMFCCONTROL_EXT_DATA	__declspec(dllexport)
#else
	#define CGSERVERQUERYMFCCONTROL_EXT_API		__declspec(dllimport)
	#define CGSERVERQUERYMFCCONTROL_EXT_CLASS	__declspec(dllimport)
	#define CGSERVERQUERYMFCCONTROL_EXT_DATA	__declspec(dllimport)
#endif


//----------------------------------------------------------------------------
//  head files
//----------------------------------------------------------------------------
// 1) CGDK base header files
#include "cgdk/sdk10/server.mfc_controls.h"
#include "cgdk/sdk10/server.query.h"

// 2) Child Dialog
#include "cgdk/sdk10/server.query/mfc_controls/child_querier_list.h"

// 3) functions
namespace CGDK
{
	CGSERVERQUERYMFCCONTROL_EXT_API CChild_querier_list* WINAPI create_child_querier_list(query::manager_querier* _pquerier_manager, CWnd* _pparent_wnd);
}


//----------------------------------------------------------------------------
//
// libraries
//
//----------------------------------------------------------------------------
#ifndef _CGSERVERQUERYMFCCONTROLS_EXT

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
				#pragma message("[CGDK10] 'CGDK10.server.query.mfc_controls_Windows10.0_x64_Release_Dynamic.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/windows/CGDK10.server.query.mfc_controls_Windows10.0_x64_Release_Dynamic.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.server.query.mfc_controls_Windows10.0_x64_Debug_Dynamic.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/windows/CGDK10.server.query.mfc_controls_Windows10.0_x64_Debug_Dynamic.lib")
			#endif
		// Error - No supported
		#else
			#error "[CGDK10] Not supported Windonws SDK version (Need Windows SDK 10.0 or higher)"
		#endif

	#else
			#error "[CGDK10] Not supported platform toolset (require visual studio 2019 or higher)"
	#endif
#endif
