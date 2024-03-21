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
// definitions
//----------------------------------------------------------------------------
#define	CGSERVER_ADMIN_CLASSES

namespace CGDK
{
	namespace api
	{
		class service_handle;
		class server_status_handle;

		class manager_perfornamce_query;
		class performance_counter;
		class process_info;
	}

	namespace server_system
	{
		class Nstatic_service_logger;
		class Iservice;
		class Nservice;
		class service;
		class service_ex;
		class Nservice_application;
		template<class> class service_application;
		template<class> class service_ex_application;

		namespace admin_info
		{
			class factory;
			class time_event;
			class binder;
		}
	}

	namespace server_admin
	{
		struct sINSTANCE;
		struct sINSTANCE_HOST;
		struct sINSTANCE_SERVICE;
		class Isocket;
		class socket_to_admin;
	}

	namespace time_event
	{
		namespace object
		{
			class service_init;
			class service_destroy;
			class service_start;
			class service_stop;
		}

		namespace schedule
		{
			class service_init;
			class service_destroy;
			class service_start;
			class service_stop;
		}
	}
}


//----------------------------------------------------------------------------
// head Fileµé
//----------------------------------------------------------------------------
// 1) 
#include "cgdk/sdk10/system.object.h"
#include "cgdk/sdk10/net.socket.h"
#include "cgdk/sdk10/server.log.h"
#include "cgdk/sdk10/server.time_event.h"

namespace CGDK
{
	namespace server_system
	{
		object_ptr<Nservice> get_service() noexcept;
	}
}

// 2) api
#if defined(_WIN32)
	#include <Winsvc.h>
	#include <Psapi.h>
	#include <pdh.h>
#elif defined(__linux__)
#endif

// 2) definitions
#include "cgdk/sdk10/server.system/service/server.definitions.admin.h"
#include "cgdk/sdk10/server.system/service/server.definitions.admin.protocol.h"

// 3) api
#include "cgdk/sdk10/server.system/service/api.service.h"
#include "cgdk/sdk10/server.system/service/api.service_handle.h"
#include "cgdk/sdk10/server.system/service/api.manager_perfornamce_query.h"
#include "cgdk/sdk10/server.system/service/api.server_status_handle.h"
#include "cgdk/sdk10/server.system/service/api.performance_counter.h"
#include "cgdk/sdk10/server.system/service/api.process_info.h"

// 4) 
#include "cgdk/sdk10/server.system/service/server.admin_info.time_event.h"
#include "cgdk/sdk10/server.system/service/server.admin_info.connective.h"
#include "cgdk/sdk10/server.system/service/server.admin_Info.binder.h"
#include "cgdk/sdk10/server.system/service/server.admin_info.factory.h"

// 5) sockets
#include "cgdk/sdk10/server.system/service/server_admin.service_instance.h"
#include "cgdk/sdk10/server.system/service/server_admin.host_instance.h"
#include "cgdk/sdk10/server.system/service/server.Isocket.h"
#include "cgdk/sdk10/server.system/service/server.admin.socket.to_admin.h"

// 6) service
#include "cgdk/sdk10/server.system/service/server.Nstatic_service_logger.h"
#include "cgdk/sdk10/server.system/service/server.Iservice.h"
#include "cgdk/sdk10/server.system/service/server.Nservice.h"
#include "cgdk/sdk10/server.system/service/server.Nservice_application.h"
#include "cgdk/sdk10/server.system/service/server.service.h"
#include "cgdk/sdk10/server.system/service/server.service_ex.h"
#include "cgdk/sdk10/server.system/service/server.service_appilcation.h"

// 7) time_event
#include "cgdk/sdk10/server.system/service/server.time_event.object.service_init.h"
#include "cgdk/sdk10/server.system/service/server.time_event.object.service_destroy.h"
#include "cgdk/sdk10/server.system/service/server.time_event.object.service_start.h"
#include "cgdk/sdk10/server.system/service/server.time_event.object.service_stop.h"
#include "cgdk/sdk10/server.system/service/server.time_event.schedule.service_init.h"
#include "cgdk/sdk10/server.system/service/server.time_event.schedule.service_destroy.h"
#include "cgdk/sdk10/server.system/service/server.time_event.schedule.service_start.h"
#include "cgdk/sdk10/server.system/service/server.time_event.schedule.service_stop.h"


//----------------------------------------------------------------------------
//
// libraries
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

	#pragma comment(lib,"Psapi.lib")


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
				#pragma message("[CGDK10] 'CGDK10.server.service_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/windows/CGDK10.server.service_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.server.service_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/windows/CGDK10.server.service_Windows10.0_x64_Debug.lib")
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
