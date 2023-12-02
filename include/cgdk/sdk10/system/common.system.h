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
//  _MSC_VER
//
//  1300 : Visual C++ .NET
//  1310 : Visual C++ .NET 2003
//  1400 : Visual C++ .NET 2005
//  1500 : Visual C++ .NET 2008
//  1600 : Visual C++ .NET 2010
//  1700 : Visual C++ .NET 2012
//  1800 : Visual C++ .NET 2013
//  1900 : Visual C++ .NET 2015
//  1910 : Visual C++ .NET 2017
//  1920 : Visual C++ .NET 2019
//-----------------------------------------------------------------------------
#define	_MSC_VER_2001	1300
#define	_MSC_VER_2003	1310
#define	_MSC_VER_2005	1400
#define	_MSC_VER_2008	1500
#define	_MSC_VER_2010	1600
#define	_MSC_VER_2012	1700
#define	_MSC_VER_2013	1800
#define	_MSC_VER_2015	1900
#define	_MSC_VER_2017	1910
#define	_MSC_VER_2019	1920

// 1) 
// if defined(__clang__)	// for Clang
// __clang_major__
// __clang_minor__
// __clang_patchlevel__
// __clang_version__

// 2) 
// if defined(__GNUG__)		// gcc/g++
// __GNUC_MINOR__
// __GNUC_PATCHLEVEL__

// 3) NDEBUG가 설정되어 있지 않고 _DEBUG가 설정되어 있지 않으면 _DEBUG를 설정한다.
//    - 일반적으루 NDEBUG는 C컴파일러가 제공하는 기본 Definition인데 반해 _DEBUG는
//      기본적으로 제공하는 Macro가 아니다. 따라서 NDEBUG가 설정되어 있지 않으면
//      _DEBUG를 따로 설정해 주어야 한다.
#if !defined(NDEBUG) && !defined(_DEBUG)
	#define	_DEBUG
#endif

// 4) STL secure level
#ifdef NDEBUG
	#ifndef _SECURE_SCL
		#define	_SECURE_SCL	0
	#endif

	#ifndef _HAS_ITERATOR_DEBUGGING
		#define _HAS_ITERATOR_DEBUGGING 0
	#endif
#endif

// 5) Settings
#define	_CGD_TIME

// 6) 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다(WIN32용)
#define WIN32_LEAN_AND_MEAN

// 7) CGDK
#define _CGDK	10

// 8) 
#if defined(__GNUC__)
#define __ATTRIBUTE_PRIORITY(value)	 __attribute__((init_priority(value)))
#else
#define __ATTRIBUTE_PRIORITY(value)
#endif

#define __STATIC_PRIORITY_LEVEL1	10000
#define __STATIC_PRIORITY_LEVEL2	11000
#define __STATIC_PRIORITY_LEVEL3	12000
#define __STATIC_PRIORITY_LEVEL4	13000
#define __STATIC_PRIORITY_LEVEL5	14000


//-----------------------------------------------------------------------------
// Basic)
//-----------------------------------------------------------------------------
// 1) for Min/Max Disable
#ifndef NOMINMAX
	#define NOMINMAX
#endif

// 2) ...
#include <functional>
#include <type_traits>
#include <climits>

#if defined(_WIN32)
	//#include <intsafe.h>
#endif


// ----------------------------------------------------------------------------
//
// Debug make_object
//
// ----------------------------------------------------------------------------
#ifdef _MSC_VER
	#include <new.h>
#endif

// Debug)
#ifndef NDEBUG
	#if defined(_MSC_VER)
		#define _CRTDBG_MAP_ALLOC
		#define _INC_MALLOC
		#include <stdlib.h>
		#include <crtdbg.h>
	#endif
#endif


//-----------------------------------------------------------------------------
// Configuration
//-----------------------------------------------------------------------------
// 1) Platform

// 2) tick clock
//#define		_USE_TICK_CLOCK_HIGH_RESOLUTION
//#define		_USE_TICK_CLOCK_MONOTONIC
//#define		_USE_TICK_CLOCK_SYSTEM
#define		_USE_TICK_CLOCK_STEADY

// 3) time clock
#define		_USE_TIME_CLOCK_LINUX_STANDARD
//#define		_USE_TIME_CLOCK_WWINDOWS_STANDARD
//#define		_USE_TIME_CLOCK_WWINDOWS_SYSTEMTIME

// 3) String
#define		_USE_CHAR_STRING	// CP_949
//#define		_USE_WCHAR_STRING
//#define		_USE_CHAR16_STRING
//#define	_USE_CHAR32_STRING

// 5) Lock
#define		_USE_NATIVE_LOCK


//-----------------------------------------------------------------------------
// STL & Containers
//-----------------------------------------------------------------------------
// 1) STL linear
#include <array>
#include <vector>
#include <list>

// 2) STL associated
#include <map>
#include <set>

// 3) 
#include <any>

// 4) CGCII containers
#include "cgdk/containers/static_vector"
#include "cgdk/containers/circular_list"
#include "cgdk/containers/flexible.h"


//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------
// 1) fundamental definitions
#include "cgdk/common/definitions.h"

// 2) definition for Debug
#include "cgdk/common/definitions.assert.h"

// 3) Type Definitions
#include "cgdk/common/definitions.types.h"

// 4) definitions for String
#include "cgdk/common/definition.string.h"

// 5) definitions for locked object
#include "cgdk/common/definition.lock.h"

// 6) definitions for Timer
#include "cgdk/common/definition.timer.h"

// 7) definitions for System 
#include "cgdk/common/definitions.system.h"

// 8) message
#include "cgdk/common/definitions.message.h"
#include "cgdk/common/message_map.h"
