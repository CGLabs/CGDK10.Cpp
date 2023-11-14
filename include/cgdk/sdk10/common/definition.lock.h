//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                  Common                                   *
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
// Definitions for Locked objects
//                                                                            
//                                                                            
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Configure)
//-----------------------------------------------------------------------------
#include <atomic>

#if defined(_WIN32)
	//#define	LOCKFREE_SELF_STACK		lockfree_self_stack
	#define	LOCKFREE_SELF_STACK		locked_self_stack
#elif defined(__ANDROID__)
	#define	LOCKFREE_SELF_STACK		locked_self_stack
#elif defined(__APPLE__)
	#define	LOCKFREE_SELF_STACK		locked_self_stack
#elif defined(__linux__)
	#define	LOCKFREE_SELF_STACK		locked_self_stack
#else
	#error "CGDK Not supported platform"
#endif


//-----------------------------------------------------------------------------
// Intrinsic
//-----------------------------------------------------------------------------
// 1) Include
#include <mutex>
#include <shared_mutex>

// 2) conditional variable
#include <condition_variable>

// 3) ...
#if defined(_MSC_VER)
	#include <intrin.h>
#else
	#include <pthread.h>

	#if defined (_M_X64)
	inline unsigned char _InterlockedCompareExchange128(__int64 volatile * _Destination, __int64 _ExchangeHigh, __int64 _ExchangeLow, __int64 * _ComparandResult)
	//inline __uint128_t InterlockedCompareExchange128(__uint128_t volatile * _Destination, __uint128_t _Comparand, __uint128_t with )
	{
	  __asm__ __volatile__
	  (
		  "lock cmpxchg16b %1"
		  : "+A" ( _ComparandResult )
		  , "+m" ( *_Destination )
		  : "b" ( (long long)_ExchangeLow )
		  , "c" ( (long long)_ExchangeHigh )
		  : "cc"
	  );

	  return _ExchangeLow==*_ComparandResult && _ExchangeHigh==*(_ComparandResult+1);
	}
	#else
		//#error "Not supported platform (_InterlockedCompareExchange128 is not defined)"
	#endif
#endif


//-----------------------------------------------------------------------------
// definitions)
//-----------------------------------------------------------------------------
// 1) critical section
#include "cgdk/sdk10/common/lockable.h"
#include "cgdk/sdk10/common/scoped_lock.h"

// 2) CGDK locked container
#include "cgdk/sdk10/common/locked_self_stack.h"
//#include "cgdk/sdk10/common/lockfree_self_stack.h"
//#include "cgdk/sdk10/common/lockfree_self_stack_64.h"
