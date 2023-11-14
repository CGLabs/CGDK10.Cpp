//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                      Ver 10.0 / Release 2019.12.11                        *
//*                                                                           *
//*                           server.query.rdb.oledb                          *
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
// CGDK10.server.query.rdb.oledb
//
//-----------------------------------------------------------------------------
// 1) 
#define	CGDK_SERVER_QUERY_RDB_OLEDB

// 2) disable warning (for OLE-DB)
#if defined(_MSC_VER)
	#pragma warning(disable:6001)
#endif


// ----------------------------------------------------------------------------
// prototypes
// ----------------------------------------------------------------------------
namespace CGDK::query::rdb::oledb
{
	class data_source;
	class session;

	class querier;

	class Iquery;
	template<class, template<class> class, class> class Cquery;
	template<class, template<class> class, class> class Nquery;
	template<class, template <class> class, class> class _query;
	template<class, template <class> class, class> class _query_dynamic;
	template<class, template <class> class, class> class _query_dynamic_parameter;

	class transaction_guard;
}


// ----------------------------------------------------------------------------
// head File
// ----------------------------------------------------------------------------
// 1) CGDK base header files
#include "cgdk/sdk10/server.query.h"

// ...)
#pragma warning(push, 1)

// 2) sql
#include <sql.h>
#include <sqlext.h>

#if defined(_MSC_VER)
	//#define OLE2ANSI
	#include <atldbcli.h>
	#include <atlconv.h>
#else
	#error "oledb is not supported!"
#endif

// ...)
#pragma warning(pop)

// 3) string param
#include "cgdk/sdk10/server.query/rdb.oledb/basic_string_param.h"

// 4) definitions
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.definitions.h"
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.definitions.protocol.h"

// 5) interfaces
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.data_source.h"
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.session.h"

// 6) query
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.query_GET_VALUE.h"
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.query_GET_PARAM.h"
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.query_SET_PARAM.h"

#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.Iquery.h"
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.functions.h"
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.Nquery.h"
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.query.h"
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.query_dynamic.h"
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.query_dynamic_parameter.h"
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.Cquery.h"

// 7) class alias
namespace CGDK::query::rdb
{
	using querier_t = oledb::querier;
	using Iquery_t = oledb::Iquery;
	using query_t = oledb::Cquery<ATL::CDynamicAccessor>;
	using query_param_t = oledb::Cquery<ATL::CDynamicParameterAccessor>;
}

// 8) querier
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.querier.h"

// 9) scoped transaction
#include "cgdk/sdk10/server.query/rdb.oledb/server.query.rdb.oledb.transaction_guard.h"


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

	#pragma comment(lib, "odbc32.lib")


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
				#pragma message("[CGDK10] 'CGDK10.server.query.rdb.oledb_Windows10.0_x64_Release.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.server.query.rdb.oledb_Windows10.0_x64_Release.lib")
			#else
				#pragma message("[CGDK10] 'CGDK10.server.query.rdb.oledb_Windows10.0_x64_Debug.lib' will be linked")
				#pragma comment(lib, "cgdk/sdk10/CGDK10.server.query.rdb.oledb_Windows10.0_x64_Debug.lib")
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
	#error "[CGDK10] Not supported Android Platform"

#elif defined(__APPLE__)
	#error "[CGDK10] Not supported APPLE Platform"

#elif defined(__linux__)

#else
	#error "[CGDK10] Not supported platform"
#endif
