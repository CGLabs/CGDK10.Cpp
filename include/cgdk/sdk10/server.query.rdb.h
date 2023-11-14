//*****************************************************************************
//*                                                                           *
//*                       Cho sanghyun's Game Classes II                      *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                             server.query.odbc                             *
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
//  1) windows -> oledb, odbc
//  2) linux   -> odbc only
//
//----------------------------------------------------------------------------
#if defined(_MSC_VER)
	#if defined (_USE_ODBC)
		#include "cgdk/sdk10/server.query.rdb.odbc.h"
	#elif defined(_USE_OLEDB)
		#include "cgdk/sdk10/server.query.rdb.oledb.h"
	#else
		#include "cgdk/sdk10/server.query.rdb.oledb.h"
	#endif
#elif defined(__ANDROID__)
	#include "cgdk/sdk10/server.query.rdb.odbc.h"
#elif defined(__APPLE__)
	#include "cgdk/sdk10/server.query.rdb.odbc.h"
#elif defined(__linux__)
	#include "cgdk/sdk10/server.query.rdb.odbc.h"
#else
	#error "[CGDK10] Not supported platform"
#endif
