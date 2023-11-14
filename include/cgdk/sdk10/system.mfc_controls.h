//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                               MFC Controls                                *
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
#define	CGDK_SYSTEM_MFC_CONTROLS

// 2) 
#ifdef _CGMFCCONTROLS_EXT
	#define CGMFCCONTROL_EXT_API	__declspec(dllexport)
	#define CGMFCCONTROL_EXT_CLASS	__declspec(dllexport)
	#define CGMFCCONTROL_EXT_DATA	__declspec(dllexport)
#else
	#define CGMFCCONTROL_EXT_API	__declspec(dllimport)
	#define CGMFCCONTROL_EXT_CLASS	__declspec(dllimport)
	#define CGMFCCONTROL_EXT_DATA	__declspec(dllimport)
#endif

// 5) ...
#define	CGUPDATE							1
#define	CGINIT								2


//----------------------------------------------------------------------------
//
// head files
//
//----------------------------------------------------------------------------
// 1) CGDK base header files
#include "cgdk/sdk10/system.object.h"

#define	CGDIALOG CDialogEx
#include "afxdialogex.h"

// 2) Definitions
#include "cgdk/sdk10/system/mfc_controls/static_graph.h"
#include "cgdk/sdk10/system/mfc_controls/listbox.h"
#include "cgdk/sdk10/system/mfc_controls/listbox_log.h"

// 3) Child Dialog
#include "cgdk/sdk10/system/mfc_controls/child_dialog.h"
#include "cgdk/sdk10/system/mfc_controls/child_thread_list.h"
#include "cgdk/sdk10/system/mfc_controls/child_reference_list.h"
#include "cgdk/sdk10/system/mfc_controls/child_schedulable_list.h"
#include "cgdk/sdk10/system/mfc_controls/child_executor_list.h"
#include "cgdk/sdk10/system/mfc_controls/dialog_CGDK_component_info.h"

// 4) Dialog
#include "cgdk/sdk10/system/mfc_controls/dialog_object_factory_info.h"
#include "cgdk/sdk10/system/mfc_controls/dialog_object_factory_status.h"
#include "cgdk/sdk10/system/mfc_controls/dialog_thread_status.h"
#include "cgdk/sdk10/system/mfc_controls/dialog_reference_status.h"

// 5) Functions
namespace CGDK
{
	CGMFCCONTROL_EXT_API CStatic_graph* WINAPI CGCreateControlStaticGraph(int _data_length, int _GridUnit);
	CGMFCCONTROL_EXT_API INT_PTR WINAPI	DoModalObjectFactoryStatus(factory::manager* p_pManager);
	CGMFCCONTROL_EXT_API INT_PTR WINAPI	DoModalThreadStatus(api::manager_thread* p_pManager);
	CGMFCCONTROL_EXT_API INT_PTR WINAPI	DoModalReferenceStatus(Ireferenceable* _object);
	CGMFCCONTROL_EXT_API INT_PTR WINAPI	DoModalCGDKComponentInfo(const std::vector<CGDK::sCOMPONENT>& _vectorCGDKComponents);
}


//----------------------------------------------------------------------------
//
// libraries
//
//----------------------------------------------------------------------------
#ifndef _CGMFCCONTROLS_EXT

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
				#pragma message("[CGDK10] 'CGDK10.system.mfc_controls_Windows10.0_x64_Release_Dynamic.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.system.mfc_controls_Windows10.0_x64_Release_Dynamic.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.system.mfc_controls_Windows10.0_x64_Debug_Dynamic.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.system.mfc_controls_Windows10.0_x64_Debug_Dynamic.lib")
			#endif
		// Error - No supported
		#else
			#error "[CGDK10] Not supported Windonws SDK version (Need Windows SDK 10.0 or higher)"
		#endif

	#else
		#error "[CGDK10] Not supported platform toolset (Need Visual studio 2017 or higher)"
	#endif
#endif