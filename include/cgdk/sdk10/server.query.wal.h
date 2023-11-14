//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Query Classes                            *
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
// CGDK10.server.query
//
//-----------------------------------------------------------------------------
// 1) 
#define	CGDK_SERVER_QUERY_WAL

// 2) 
#define _ATL_DISABLE_NOTHROW_NEW


// ----------------------------------------------------------------------------
// prototypes
// ----------------------------------------------------------------------------
namespace CGDK
{
	namespace wal
	{
		template <class> struct sCHUNK;
		template <class> struct sQUERY;
		struct sHEADER;

		template <class,class> class file;
		template <class> class querier;
		template <class> class Inotifiable;
		template <class, class> class Inotifiable_file;
	}
}

// ----------------------------------------------------------------------------
// head File
// ----------------------------------------------------------------------------
// 1) CGDK base header files
#include "cgdk/sdk10/system.object.h"

// 2) journaling system
#include "cgdk/sdk10/server.query/query/wal.Inotifiable.h"

#include "cgdk/sdk10/server.query/query/wal.file.h"
#include "cgdk/sdk10/server.query/query/wal.querier.h"
