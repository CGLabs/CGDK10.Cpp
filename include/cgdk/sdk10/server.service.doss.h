//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / release 2019.12.11                       *
//*                                                                           *
//*                 Distributed Object Storage System Classes                 *
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
#define	CGSERVER_SERVICE_DOSS_CLASSES

namespace CGDK
{
	namespace doss
	{
		class Itransactable;
		class Ientity;

		class Irepository;
		class manager_repository;

		template <class> struct sCOMMAND;
		template <class> struct sSESSION;
		template <class,class> class entity_transactable;

		template <class> class Nrepository;
		namespace repository
		{
			template <class, class> class rdb;
			template <class, class> class remote;
			template <class, class> class orm;
			template <class> class Nhub;
		}

		class Idepot;
		class Ndepot;
		class depot;

		namespace statistics
		{
			struct transactable;
			struct entity;
			struct repository;

			class Nrepository;
		}

		class Isession;
		template <class> class session;
	}
}

// ----------------------------------------------------------------------------
// head Fileµé                                                               
// ----------------------------------------------------------------------------
// 1) base classes
#include "cgdk/sdk10/net.socket.h"
#include "cgdk/sdk10/server.group.h"
#include "cgdk/sdk10/server.query.h"

// 2) definitions
#include "cgdk/sdk10/server.service/doss/server.service.doss.definition_protocol.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.definitions.h"

// 3) statistics
#include "cgdk/sdk10/server.service/doss/server.service.doss.statistics.h"

// 3) transactable
#include "cgdk/sdk10/server.service/doss/server.service.doss.Itransactable.h"

// 4) ...
#include "cgdk/sdk10/server.service/doss/server.service.doss.manager_repository.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.Irepository.h"

// 6) messages
#include "cgdk/sdk10/server.service/doss/server.service.doss.messages.h"

// 7) Interface classes
#include "cgdk/sdk10/server.service/doss/server.service.doss.Isession.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.Ientity.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.entity_session.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.entity_transactable.h"

// 8) session
#include "cgdk/sdk10/server.service/doss/server.service.doss.session.h"

// 9) depot
#include "cgdk/sdk10/server.service/doss/server.service.doss.Idepot.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.depot_restore.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.depot.socket.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.depot.group_socket_immigration.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.Ndepot.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.depot.h"

// 10) repository 
#include "cgdk/sdk10/server.service/doss/server.service.doss.Nrepository.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.repository.orm.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.repository.rdb.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.repository.remote.h"
#include "cgdk/sdk10/server.service/doss/server.service.doss.repository.Nhub.h"


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
				#pragma message("[CGDK10] 'CGDK10.server.service.doss_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/windows/CGDK10.server.service.doss_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.server.service.doss_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/windows/CGDK10.server.service.doss_Windows10.0_x64_Debug.lib")
			#endif
		// Error - No supported
		#else
			#error "[CGDK10] Not supported Windonws SDK version (Need Windows SDK 10.0 or higher)"
		#endif

	#else
		#error "[CGDK10] Not supported Platform toolset (Need Visual studio 2015 or higher)"
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

