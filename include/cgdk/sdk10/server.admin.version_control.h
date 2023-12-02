//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Admin Classes                            *
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
// Definitions
//----------------------------------------------------------------------------
#define	CGSERVER_ADMIN_CLASSES

class CWnd;
class ICGServerService;

// Definitions
#define	HUNSPELL_STATIC
#define	THESAURUS

#if !defined(NDEBUG)
	#define	SVN_DEBUG
#endif

namespace CGDK
{
namespace admin
{
	class ISVNCommand;
	class ISVNNotify;
	class SVN;
}
}


//----------------------------------------------------------------------------
// head Fileµé
//----------------------------------------------------------------------------
// 1) Base Classes
#include "cgdk/sdk10/CGServerAdminClasses.h"

// 2) 
#include "apr_version.h"
#include "apu_version.h"

#ifdef _WIN64
#include "openssl/opensslv.h"
#else
#include "openssl/opensslv.h"
#endif
#include "../../ext/zlib/zlib.h"

#define __WIN32__
//#include "boost/pool/object_pool.hpp"

#define USE_GDI_GRADIENT
#define HISTORYCOMBO_WITH_SYSIMAGELIST

#ifdef _WIN64
#   define APP_X64_STRING   "x64"
#else
#   define APP_X64_STRING ""
#endif

#define HAVE_APPUTILS

#pragma warning(push)
#include "apr_general.h"
#include "svn_pools.h"
#include "svn_client.h"
#include "svn_path.h"
#include "svn_wc.h"
#include "svn_utf.h"
#include "svn_config.h"
#include "svn_error_codes.h"
#include "svn_subst.h"
#include "svn_repos.h"
#include "svn_time.h"
#include "svn_props.h"
#pragma warning(pop)

// 3) Definitions
#include "cgdk/sdk10/Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerDefinitionsVersionControl.h"

// 4) SVN
#include "cgdk/sdk10/Server/ServerAdmin/CGServerAdminVersionControlClasses/ICGServerAdminSVNNotify.h"
#include "cgdk/sdk10/Server/ServerAdmin/CGServerAdminVersionControlClasses/ICGServerAdminSVN.h"

#include "cgdk/sdk10/Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerAdminSVN.h"

#include "cgdk/sdk10/Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerAdminSVNUpdate.h"
#include "cgdk/sdk10/Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerAdminSVNCheckOut.h"
#include "cgdk/sdk10/Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerAdminSVNSwitch.h"
#include "cgdk/sdk10/Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerAdminSVNInfo.h"
#include "cgdk/sdk10/Server/ServerAdmin/CGServerAdminVersionControlClasses/CGServerAdminSVNLog.h"


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

	#pragma comment(lib, "libsvn_tsvn32.lib")
	#pragma comment(lib, "libapr_tsvn.lib")
	#pragma comment(lib, "libsasl.lib")
	#pragma comment(lib, "libaprutil_tsvn.lib")
	#pragma comment(lib, "intl3_tsvn.lib")
	#pragma comment(lib, "intl3_tsvn.lib")


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
				#pragma message("[CGDK10] 'CGDK10.server.admin.version_control_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib,"CGDK10.server.admin.version_control_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.server.admin.version_control_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib,"CGDK10.server.admin.version_control_Windows10.0_x64_Debug.lib")
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
	#error "[CGDK10] Not supported Android Platform"

#elif defined(__APPLE__)
	#error "[CGDK10] Not supported APPLE Platform"

#elif defined(__linux__)

#else
	#error "[CGDK10] Not supported platform"
#endif
