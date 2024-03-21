//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Event Classes                            *
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
#define	CGSERVER_EVENT_CLASSES

namespace CGDK
{
	namespace time_event
	{
		class entity_manager;

		class Ientity;
		class Ievent;

		class entity;
		class Nentity_iteration;
		template <class TFUNCTION>
		class entity_iteration;
		class Nentity_start_end;
		template <class TFUNCTION>
		class entity_start_end;
		class Nentity_start_iteration_end;
		template <class TFUNCTION>
		class entity_start_iteration_end;

		class event;
	}
}


//----------------------------------------------------------------------------
// head Fileµé
//----------------------------------------------------------------------------
// 1) execute
#include "cgdk/sdk10/system.object.h"

// 2) event system
#include "cgdk/sdk10/server.system/time_event/server.definitions.time_event.h"
#include "cgdk/sdk10/server.system/time_event/server.definitions.time_event.protocol.h"

// 3) time event - interfaces
#include "cgdk/sdk10/server.system/time_event/server.time_event.Ievent.h"
#include "cgdk/sdk10/server.system/time_event/server.time_event.Ientity.h"

// 4) time event - entity
#include "cgdk/sdk10/server.system/time_event/server.time_event.event.h"
#include "cgdk/sdk10/server.system/time_event/server.time_event.entity.h"
#include "cgdk/sdk10/server.system/time_event/server.time_event.Nentity_iteration.h"
#include "cgdk/sdk10/server.system/time_event/server.time_event.entity_iteration.h"
#include "cgdk/sdk10/server.system/time_event/server.time_event.Nentity_start_end.h"
#include "cgdk/sdk10/server.system/time_event/server.time_event.entity_start_end.h"
#include "cgdk/sdk10/server.system/time_event/server.time_event.Nentity_start_iteration_end.h"
#include "cgdk/sdk10/server.system/time_event/server.time_event.entity_start_iteration_end.h"

// 5) time event - manager
#include "cgdk/sdk10/server.system/time_event/server.time_event.manager.h"


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
				#pragma message("[CGDK10] 'CGDK10.server.time_event_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/windows/CGDK10.server.time_event_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.server.time_event_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/windows/CGDK10.server.time_event_Windows10.0_x64_Debug.lib")
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

