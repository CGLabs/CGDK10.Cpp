//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        Server System MFC Controls                         *
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
#define	CGDBMFC_CONTROLS

#ifdef _CGSERVERSYSTEMMFCCONTROLS_EXT
	#define CGSERVERSYSTEMMFCCONTROL_EXT_API		__declspec(dllexport)
	#define CGSERVERSYSTEMMFCCONTROL_EXT_CLASS		__declspec(dllexport)
	#define CGSERVERSYSTEMMFCCONTROL_EXT_DATA		__declspec(dllexport)
#else
	#define CGSERVERSYSTEMMFCCONTROL_EXT_API		__declspec(dllimport)
	#define CGSERVERSYSTEMMFCCONTROL_EXT_CLASS		__declspec(dllimport)
	#define CGSERVERSYSTEMMFCCONTROL_EXT_DATA		__declspec(dllimport)
#endif


//----------------------------------------------------------------------------
//  head Fileµé                                                               
//----------------------------------------------------------------------------
// 1) CGNetServerAdminClasees
#include "cgdk/sdk10/CGMFCControls.h"
#include "cgdk/sdk10/CGServerDOSSClasses.h"

// 2) Child Dialog
#include "cgdk/sdk10/Server/ServerSystem/CGServerSystemMFCControls/CGChildServerDOSSRepositoryList.h"
#include "cgdk/sdk10/Server/ServerSystem/CGServerSystemMFCControls/CGChildServerDOSSObjectList.h"

// 3) Dialog
#include "cgdk/sdk10/Server/ServerSystem/CGServerSystemMFCControls/CGDialogSystemRepositoryStatus.h"


// 3) Functions
CGSERVERSYSTEMMFCCONTROL_EXT_API CCGChildRepositoryList* WINAPI CGCreateChildRepositoryList(CGServerDOSS::ManagerRepository* _pRepositoryManager, CWnd* pParentWnd);


//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#ifndef _CGSERVERSYSTEMMFCCONTROLS_EXT

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
				#pragma message("[CGDK10] 'CGDK10.CGServerSystemMFCControls_Windows10.0_x64_Release_Dynamic_MultiByte.lib' will be linked")
				#pragma comment(lib,"CGServerSystemMFCControls_Windows10.0_x64_Release_Dynamic_MultiByte.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.CGServerSystemMFCControls_Windows10.0_x64_Debug_Dynamic_MultiByte.lib' will be linked")
				#pragma comment(lib,"CGServerSystemMFCControls_Windows10.0_x64_Debug_Dynamic_MultiByte.lib")
			#endif
		// Error - No supported
		#else
			#error "[CGDK10] Not supported Windonws SDK version (Need Windows SDK 10.0 or higher)"
		#endif

	#else
		#error "[CGDK10] Not supported Platform toolset (Need Visual studio 2015 or higher)"
	#endif
#endif