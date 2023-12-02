//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object Classes                               *
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
// CGDK10.system.object
//
//-----------------------------------------------------------------------------
// 1) ...
#define	CGDK_SYSTEM_OBJECT


//----------------------------------------------------------------------------
//
// definitions for configuration
//
//----------------------------------------------------------------------------
// 1) use DEBUG_NEW
#define _USE_DEBUG_NEW

#if defined(_USE_DEBUG_NEW) && !defined(NDEBUG) && (defined(_WIN32) || defined(__linux__))
	#define _ENABLE_DEBUG_NEW

	#if !defined(__ANDROID__)
		#define	_USE_DEBUG_NEW_REDEFINITION
	#endif
#endif

// 2) Factroies for All allocated objects by make_object<T> function
#define	_USE_CREATE_FACTORY_FOR_ALL_OBJECT

// 3) Disable Warning
#if defined(_WIN32)
	#pragma warning(disable:4250)
#endif

// 3) 기본 최대 로그 수 (!)변경금지
#define	DEFAULT_MAX_LOG_COUNT	2048


//----------------------------------------------------------------------------
//
// standard head files
//
//----------------------------------------------------------------------------
// 1) CGDK base header files
#include "cgdk/sdk10.system/common.system.h"

// 2) Exception
#include <exception>

// 3) Debug Help (for WIN32)
#if defined(_MSC_VER)
	#include <eh.h>
	#include <Dbghelp.h>
#endif

#if defined(_MSC_VER)
	#pragma warning(default:4091)
#endif

// 4) Linux or Android
#if !defined(_MSC_VER)
	#include <thread>
#endif

// 5) Thread (Linux or Mobile)
#if defined(__ANDROID__)
	#include <signal.h>
	#include <poll.h>
	#include <pthread.h>
	#include <sched.h>
	#include <unistd.h>

	#include <linux/input.h>
	#include <sys/epoll.h>

#elif defined(__linux__)
	#include <pthread.h>
	#include <unistd.h>
	//#include <linux/input.h>

	// - epoll
	#include <sys/epoll.h>

	//// - aio
	#include <signal.h>
	#include <aio.h>
	//#include <linux/aio_abi.h>

#elif defined (__APPLE__)
	#include <poll.h>
	#include <pthread.h>
	#include <sched.h>
	#include <unistd.h>

	#include <linux/input.h>
#endif


//----------------------------------------------------------------------------
// proto...
//----------------------------------------------------------------------------
namespace CGDK
{
	// 1) references
	class Ireferenceable;
	class Nreferenceable_no_act;
	template <class> class object_ptr;

	// 2) interfaces
	class Imemory;
	class Ipreceding_destroyable;
	class Imessage_transmitter;
	class Ilogger;
	class Iarchive;
	class Iexecutable;
	class Iexecutor;
	class Ischedulable;
	class Imessageable;

	namespace object
	{
		class Inameable;
		class Iidentifiable;

		class Istate;
		class Idestroyable;
		class Iinitializable;
		class Istartable;
		class Ipausable;
		class Iupdatable;
		class Ienable;
		template <class TTYPE> class Iattachable;

		class Nnameable;
		class Nstate;
		class Ninitializable;
		class Nstartable;
		class Npausable;
		class Ninitializable_startable;
		class Nenable;
		template <typename TTYPE, typename TCON = std::vector<object_ptr<TTYPE>>> class Nattachable;
	}

	// 3) exception
	class Ithrowable;

	// 4) log
	class LOG_RECORD;

	// 5) ...
	namespace resource
	{
		class manager;
	}

	// 6) factory
	class Ifactory;
	namespace factory
	{
		class manager;
		template<class> class Iobject;
		template<class> class object;
		template<class>	class object_pool;
		template<class>	class object_pool_tls;
		class memory_block;
	}
	template <class> class Npoolable;

	// 7) edc
	namespace edc
	{
		class crc;
		extern crc default_crc;
	}

	// 8) archive
	namespace archive
	{
		class file;
		class file_record;
	}

	// 9) api
	namespace api
	{
		class queue_executable;
#if defined(__ANDROID__) || defined(__linux__)
		class io_context_epoll;
		using io_context = io_context_epoll;
#elif defined(_IO_APISET_H_)
		class io_context_iocp;
		using io_context = io_context_iocp;
#else
	#error "Unsuppored API"
#endif

		class Nthread;
		class thread;
		class threads;

		class manager_thread;
	}

	// 10) executor
	namespace executor
	{
		class Iqueue;
		class Iio_context;
		class queue_list;
		class io_context;
		class io_context_threads;

		template <class T = Iexecutor> class list;
		class list_priority;

		template <class T = Iexecutor> class thread;

		class schedulable;
		class single_execute;

		class manager;
	}
	class system_executor;

	// 11) executable
	namespace executable
	{
		template <class> class list;

		template <class> class function;

		class Nbatch;
		template <class> class batch_function;
		template <class> class batch_notify;
		class batch_wait;
	}

	// 12) schedulable
	namespace schedulable
	{
		class Iexecutable;
		class Nexecutable;
		class Ninitializable_startable;
		template <class> class Nexecutable_list;
		template <class> class Nexecutable_function;
		class executable;
		template <class> class executable_function;
		class entity;

		namespace system
		{
			class exception_observer;
			class factory_sustain;
		}
	}

	// 13) updatable
	namespace updatable
	{
		class executable_batch;
	}

	// 14) throwable
	namespace throwable
	{
		class failure;
		class critical;
		class seh_exception;
	}

	// 15) factory
	namespace factory
	{
		class _traits_has_pool {};
		class _traits_system {};
		class _traits_memory {};
		class _traits_user {};

		class _traits_has_on_alloc {};
		class _traits_has_on_dealloc {};
	}

	template <class> class POOLABLE;
}


//-----------------------------------------------------------------------------
// External library
//-----------------------------------------------------------------------------
#if defined(__cpp_lib_format)
	#include <format>
	#define NFMT std
#else
	// 1) external libarary
	#if defined(_MSC_VER)
		#pragma warning(disable:26812)
		#pragma warning(disable:26446)
	#endif
	#include "cgdk/sdk10/system/object/fmt/format.h"
	#if defined(_MSC_VER)
		#pragma warning(default:26812)
		#pragma warning(default:26446)
	#endif
#define NFMT fmt
#endif

//----------------------------------------------------------------------------
//
// head files
//
//----------------------------------------------------------------------------
// 1) chrono
#include "cgdk/sdk10/system/object/chrono.h"
#include "cgdk/sdk10/system/object/chrono_tick.h"
#include "cgdk/sdk10/system/object/chrono_time.h"
#include "cgdk/sdk10/system/object/chrono_time_client.h"

// 2) object definitions
#include "cgdk/sdk10/system/object/definitions.result_code.h"
#include "cgdk/sdk10/system/object/definitions.object.h"


//----------------------------------------------------------------------------
// creation & reference counting
//----------------------------------------------------------------------------
// 1) traits
#include "cgdk/sdk10/system/object/object_traits.h"

// 2) disposable & reference counting
#include "cgdk/sdk10/system/object/Idisposable.h"
#include "cgdk/sdk10/system/object/Ireferenceable.h"
#include "cgdk/sdk10/system/object/object_ptr.h"
#include "cgdk/sdk10/system/object/any_ptr.h"


//----------------------------------------------------------------------------
// application interface
//----------------------------------------------------------------------------
// 1) system info
#include "cgdk/sdk10/system/object/api.system.h"

// 2) file
#include "cgdk/sdk10/system/object/api.file.h"


//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// 1) referenceable 
#include "cgdk/sdk10/system/object/referenceable.Nno_act.h"
#include "cgdk/sdk10/system/object/Nreferenceable.h"

// 2) destroyable
#include "cgdk/sdk10/system/object/object.Idestroyable.h"

// 3) object allocation
#include "cgdk/sdk10/system/object/obj.h"
#include "cgdk/sdk10/system/object/make_object.h"
#include "cgdk/sdk10/system/object/make_object_raw.h"
#include "cgdk/sdk10/system/object/make_own.h"
#include "cgdk/sdk10/system/object/debug_info_setter.h"
#include "cgdk/sdk10/system/object/throwable.h"

// 4) buffer
#include "cgdk/buffer"

// 5) 
#include "cgdk/sdk10/system/object/message.h"

// 6) attachable
#include "cgdk/sdk10/system/object/object.Iattachable.h"
#include "cgdk/sdk10/system/object/object.Nattachable.h"

// 7) registerable
#include "cgdk/sdk10/system/object/Iregisterable.h"
#include "cgdk/sdk10/system/object/Nregisterable.h"

// 8) registery
#include "cgdk/sdk10/system/object/depository.h"


//----------------------------------------------------------------------------
// messageable & dispatcher
//----------------------------------------------------------------------------
// 1) Imemory
#include "cgdk/sdk10/system/object/Imemory.h"
#include "cgdk/shared_buffer"
#include "cgdk/sdk10/system/object/make_shared_buffer.h"

// 2) string param
#include "cgdk/sdk10/system/object/definitions.string_function.h"
#include "cgdk/sdk10/system/object/basic_string_param.h"
#include "cgdk/sdk10/system/object/string_function_ex.h"

// 3) context
#include "cgdk/sdk10/system/object/context.h"

// 4) message definitions
#include "cgdk/sdk10/system/object/definitions.object_message.h"

// 5) messageable
#include "cgdk/sdk10/system/object/Imessageable.h"

// 6) messageable ...
#include "cgdk/sdk10/system/object/Nmessageable.h"

// 7) message_transmitter
#include "cgdk/sdk10/system/object/Imessage_transmitter.h"
#include "cgdk/sdk10/system/object/Nmessage_transmitter.h"
#include "cgdk/sdk10/system/object/Nmessage_transmitter_single.h"
#include "cgdk/sdk10/system/object/Nmessage_transmitter_static.h"

// ex) file
#include "cgdk/sdk10/system/object/api.file_ex.h"


//----------------------------------------------------------------------------
// object - nameable
//----------------------------------------------------------------------------
// 1) nameable
#include "cgdk/sdk10/system/object/object.Inameable.h"
#include "cgdk/sdk10/system/object/object.Nnameable.h"

// 2) Identifiable
#include "cgdk/sdk10/system/object/object.Iidentifiable.h"

// 3) Istate
#include "cgdk/sdk10/system/object/object.Istate.h"
#include "cgdk/sdk10/system/object/object.Istartable.h"
#include "cgdk/sdk10/system/object/object.Ipausable.h"
#include "cgdk/sdk10/system/object/object.Iinitializable.h"

// 4) Iupdatable
#include "cgdk/sdk10/system/object/object.Iupdatable.h"

// 5) Ienable
#include "cgdk/sdk10/system/object/object.Ienable.h"
#include "cgdk/sdk10/system/object/object.Nenable.h"

// 6) Object
#include "cgdk/sdk10/system/object/Iobject.h"


//-----------------------------------------------------------------------------
// own_ptr
//-----------------------------------------------------------------------------
#include "cgdk/sdk10/system/object/own_ptr.h"


//-----------------------------------------------------------------------------
// objects 
//-----------------------------------------------------------------------------
// 1) Objeect 
#include "cgdk/sdk10/system/object/object.Nstate.h"
#include "cgdk/sdk10/system/object/object.Nstartable.h"
#include "cgdk/sdk10/system/object/object.Npausable.h"
#include "cgdk/sdk10/system/object/object.Ninitializable.h"
#include "cgdk/sdk10/system/object/object.Nstartable.h"
#include "cgdk/sdk10/system/object/object.Ninitializable_startable.h"

// 2) resource
#include "cgdk/sdk10/system/object/Iresource.h"
#include "cgdk/sdk10/system/object/resource.manager.h"


//-----------------------------------------------------------------------------
// factory
//-----------------------------------------------------------------------------
// 1) utils
#include "cgdk/sdk10/system/object/util.edc.crc.h"
#include "cgdk/sdk10/system/object/util.compress.h"
#include "cgdk/sdk10/system/object/util.crypt.base64.h"
#include "cgdk/sdk10/system/object/util.query_performance.h"

#if defined(_MSC_VER)
	// warning C4344: behavior change: use of explicit template arguments results in call to ...
	//    - Causes in front function
	#pragma warning(disable:4344)
#else
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wvarargs"
#endif

// 2) definitions for factory
#include "cgdk/sdk10/system/object/definitions.factory.h"
#include "cgdk/sdk10/system/object/definitions.factory.protocol.h"

// 3) factory
#include "cgdk/sdk10/system/object/Ifactory.h"
#include "cgdk/sdk10/system/object/factory.manager.h"

#if defined(_MSC_VER)
	#pragma warning(default:4344)
#else
	#pragma GCC diagnostic pop
#endif

// 4) pre definitions
#include "cgdk/sdk10/system/object/definitions.factory.pool.memory_block.h"


//-----------------------------------------------------------------------------
// log
//-----------------------------------------------------------------------------
// 1) log 
#include "cgdk/sdk10/system/object/log.definitions.h"
#include "cgdk/sdk10/system/object/log.record.h"
#include "cgdk/sdk10/system/object/log.functions.h"
#include "cgdk/sdk10/system/object/log.functions.definitions.h"

#include "cgdk/sdk10/system/object/Ilog_filter.h"
#include "cgdk/sdk10/system/object/Ilogger.h"
#include "cgdk/sdk10/system/object/Ilog_source.h"

#include "cgdk/sdk10/system/object/log.stream.h"
#include "cgdk/sdk10/system/object/log.archive.h"


//-----------------------------------------------------------------------------
// pool & factroy
//-----------------------------------------------------------------------------
// 1) Interfaces
#include "cgdk/sdk10/system/object/Ipoolable.h"

// 2) object pool
#include "cgdk/sdk10/system/object/factory.Iobject.h"
#include "cgdk/sdk10/system/object/factory.object.h"
#include "cgdk/sdk10/system/object/factory.object.pool.h"
#include "cgdk/sdk10/system/object/factory.object.pool_tls.h"

// 3) Npoolable
#include "cgdk/sdk10/system/object/Npoolable.h"

// 4) memory block pool
#include "cgdk/sdk10/system/object/factory.memory_block.h"

// 5) Definitions for buffer
#include "cgdk/sdk10/system/object/definitions.buffer.h"


//-----------------------------------------------------------------------------
// header files
//-----------------------------------------------------------------------------
// 1) definitions
#include "cgdk/sdk10/system/object/definitions.execute.protocol.h"
#include "cgdk/sdk10/system/object/definitions.execute.h"
#include "cgdk/sdk10/system/object/definitions.schedulable.h"

// 2) dump manager
#include "cgdk/sdk10/system/object/dump_manager.h"

// 3) interface class
#include "cgdk/sdk10/system/object/Iexecutor.h"
#include "cgdk/sdk10/system/object/Iexecutable.h"
#include "cgdk/sdk10/system/object/Ischedulable.h"

// 4) api
#include "cgdk/sdk10/system/object/api.manager_thread.h"
#include "cgdk/sdk10/system/object/api.thread.h"
#include "cgdk/sdk10/system/object/api.threads.h"
#include "cgdk/sdk10/system/object/api.io_context_iocp.h"
#include "cgdk/sdk10/system/object/api.io_context_epoll.h"
#include "cgdk/sdk10/system/object/api.queue_executable.h"

// 5) executor/thread
#include "cgdk/sdk10/system/object/Nexecutor.h"
#include "cgdk/sdk10/system/object/executor.manager.h"
#include "cgdk/sdk10/system/object/executor.Iqueue.h"
#include "cgdk/sdk10/system/object/executor.Iio_context.h"
#include "cgdk/sdk10/system/object/executor.queue_list.h"
#include "cgdk/sdk10/system/object/executor.io_context.h"
#include "cgdk/sdk10/system/object/executor.io_context_threads.h"
#include "cgdk/sdk10/system/object/executor.single_execute.h"
#include "cgdk/sdk10/system/object/executor.list_priority.h"
#include "cgdk/sdk10/system/object/executor.scheduler.h"

// 6) executable
#include "cgdk/sdk10/system/object/executable.h"
#include "cgdk/sdk10/system/object/executable.function.h"
#include "cgdk/sdk10/system/object/executable.batch.h"
#include "cgdk/sdk10/system/object/executable.batch_wait.h"
#include "cgdk/sdk10/system/object/executable.batch_notify.h"
#include "cgdk/sdk10/system/object/executable.batch_function.h"
#include "cgdk/sdk10/system/object/executable.list.h"

// 7) schedulable.1
#include "cgdk/sdk10/system/object/Nschedulable.h"
#include "cgdk/sdk10/system/object/schedulable.Iexecutable.h"
#include "cgdk/sdk10/system/object/schedulable.Nexecutable.h"
#include "cgdk/sdk10/system/object/schedulable.Nexecutable_function.h"
#include "cgdk/sdk10/system/object/schedulable.Nexecutable_list.h"

// 8) system executors
#include "cgdk/sdk10/system/object/schedulable.system.factory_sustain.h"
#include "cgdk/sdk10/system/object/schedulable.system.exception_observer.h"
#include "cgdk/sdk10/system/object/executor_system.h"

// 9) schedulable.2
#include "cgdk/sdk10/system/object/schedulable.Nobject_startable.h"
#include "cgdk/sdk10/system/object/schedulable.executable.h"
#include "cgdk/sdk10/system/object/schedulable.executable_function.h"

// 10) schedulable.3
#include "cgdk/sdk10/system/object/schedulable.entity.h"

// 11) executable batch
#include "cgdk/sdk10/system/object/updatable.executable_batch.h"


//-----------------------------------------------------------------------------
// archive
//-----------------------------------------------------------------------------
// 1) 
#include "cgdk/sdk10/system/object/Iarchive.h"
#include "cgdk/sdk10/system/object/Iserializable.h"
#include "cgdk/sdk10/system/object/archive.file.h"
#include "cgdk/sdk10/system/object/archive.file_write.h"


//----------------------------------------------------------------------------
// util
//----------------------------------------------------------------------------
// 1) edc
#include "cgdk/sdk10/system/object/util.edc.check_sum.h"
#include "cgdk/sdk10/system/object/util.edc.md5.h"

// 3) crytor
#include "cgdk/sdk10/system/object/util.Icrypt.h"
#include "cgdk/sdk10/system/object/util.Icryptable.h"


//----------------------------------------------------------------------------
// CGDK
//----------------------------------------------------------------------------
// 1) CGDK
#include "cgdk/sdk10/system/object/definitions.cgdk.h"


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

	#pragma comment(lib,"Dbghelp.lib")
	#pragma comment(lib,"winmm.lib")
	#pragma comment(lib,"iphlpapi.lib")
	#pragma comment(lib,"Psapi.lib")


	//----------------------------------------------------------------------------
	// * WinSDK 11
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
				#pragma message("[CGDK10] 'CGDK10.system.object_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.system.object_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.system.object_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.system.object_Windows10.0_x64_Debug.lib")
			#endif
		// Error - No supported
		#else
			#error "[CGDK10] Not supported Windonws SDK version (Need Windows SDK 10.0 or higher)"
		#endif

	#else
		#error "[CGDK10] Not supported platform toolset (require visual studio 2019 or higher)"
	#endif

	#endif

#elif defined(__ANDROID__)
#elif defined(__APPLE__)
#elif defined(__linux__)
#else
		#error "[CGDK10] Not supported platform"
#endif

