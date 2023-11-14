//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                  MFC Controls for Network Socket Classes                  *
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
// 1) 
#define	CGDK_NET_SOCKET_MFC_CONTROLS

// 2) 
#ifdef _CGNETSOCKETMFCCONTROLS_EXT
	#define CGNETSOCKETMFCCONTROL_EXT_API	__declspec(dllexport)
	#define CGNETSOCKETMFCCONTROL_EXT_CLASS	__declspec(dllexport)
	#define CGNETSOCKETMFCCONTROL_EXT_DATA	__declspec(dllexport)
#else
	#define CGNETSOCKETMFCCONTROL_EXT_API	__declspec(dllimport)
	#define CGNETSOCKETMFCCONTROL_EXT_CLASS	__declspec(dllimport)
	#define CGNETSOCKETMFCCONTROL_EXT_DATA	__declspec(dllimport)
#endif


//----------------------------------------------------------------------------
//  head File들                                                               
//----------------------------------------------------------------------------
// 1) CGCII Header files
#include "cgdk/sdk10/system.mfc_controls.h"
#include "cgdk/sdk10/net.socket.h"

// 2) Definitions
#include "cgdk/sdk10/net.socket/mfc_controls/combobox_connective.h"

// 3) Child Dialog
#include "cgdk/sdk10/net.socket/mfc_controls/child_connectable_manager.h"
#include "cgdk/sdk10/net.socket/mfc_controls/child_connective_list.h"
#include "cgdk/sdk10/net.socket/mfc_controls/child_binder_control.h"
#include "cgdk/sdk10/net.socket/mfc_controls/child_connective_info.h"
#include "cgdk/sdk10/net.socket/mfc_controls/child_connective_info_mini.h"
#include "cgdk/sdk10/net.socket/mfc_controls/child_connective_connector_control.h"
#include "cgdk/sdk10/net.socket/mfc_controls/child_connector_control.h"
#include "cgdk/sdk10/net.socket/mfc_controls/child_connector_control_ex.h"
//#include "cgdk/sdk10/net.socket/mfc_controls/child_connector_list.h"
#include "cgdk/sdk10/net.socket/mfc_controls/child_traffic_info.h"
#include "cgdk/sdk10/net.socket/mfc_controls/child_traffic_info_mini.h"
#include "cgdk/sdk10/net.socket/mfc_controls/child_traffic_info_brief_receive.h"
#include "cgdk/sdk10/net.socket/mfc_controls/child_traffic_info_brief_send.h"

// 4) Dialog
#include "cgdk/sdk10/net.socket/mfc_controls/dialog_connective_status.h"
#include "cgdk/sdk10/net.socket/mfc_controls/dialog_connectable_status.h"

// 5) 후순위...(AcceptorControl은 DialogConnectiveStatus가 필요함. 그래서 뒤에 따로...)
#include "cgdk/sdk10/net.socket/mfc_controls/child_acceptor_control.h"

// 6) Functions
namespace CGDK
{
	CGNETSOCKETMFCCONTROL_EXT_API	INT_PTR WINAPI	DoModal_connective_status(net::io::connective::manager* p_pmangerConnective);
	CGNETSOCKETMFCCONTROL_EXT_API	INT_PTR WINAPI	DoModal_connectable_status(net::io::Iconnectable* _pconnectable);
}


//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#ifndef _CGNETSOCKETMFCCONTROLS_EXT

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
				#pragma message("[CGDK10] 'CGDK10.net.socket.mfc_controls_Windows10.0_x64_Release_Dynamic.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.net.socket.mfc_controls_Windows10.0_x64_Release_Dynamic.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.net.socket.mfc_controls_Windows10.0_x64_Debug_Dynamic.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.net.socket.mfc_controls_Windows10.0_x64_Debug_Dynamic.lib")
			#endif
		// Error - No supported
		#else
			#error "[CGDK10] Not supported Windonws SDK version (Need Windows SDK 10.0 or higher)"
		#endif

	#else
			#error "[CGDK10] Not supported platform toolset (require visual studio 2019 or higher)"
	#endif
#endif