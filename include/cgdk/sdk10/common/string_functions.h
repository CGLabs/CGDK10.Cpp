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
// 1. String Functions
//                                                                            
//                                                                            
//-----------------------------------------------------------------------------
#include <string>	// C++ STL string
#include <string.h>	// C++ Standard string functions
#include <locale>
//#include <cwchar>
#include <uchar.h>

#if defined(_MSC_VER)
	#include <codecvt>
	#include "Shlwapi.h"

#elif __linux__

#elif __ANDROID__

#elif __APPLE__

#endif



//-----------------------------------------------------------------------------
//                                                                            
// 1. Definition
//
//-----------------------------------------------------------------------------
#define	MAX_STRING_LENGTH	2048


//-----------------------------------------------------------------------------
//                                                                            
// 2. Character type
//
//-----------------------------------------------------------------------------
// 1) _CGTEXT
#define	__CGTEXT_CHAR_(quote)		quote
#define	__CGTEXT_WCHAR_(quote)		L##quote
#define	__CGTEXT_UTF8_(quote)		u8##quote
#define	__CGTEXT_CHAR16_(quote)		u##quote
#define	__CGTEXT_CHAR32_(quote)		U##quote

#define	_CGTEXT_CHAR(quote)			__CGTEXT_CHAR_(quote)
#define	_CGTEXT_WCHAR(quote)		__CGTEXT_WCHAR_(quote)
#define	_CGTEXT_UTF8(quote)			__CGTEXT_UTF8_(quote)
#define	_CGTEXT_CHAR16(quote)		__CGTEXT_CHAR16_(quote)
#define	_CGTEXT_CHAR32(quote)		__CGTEXT_CHAR32_(quote)

// check) 
#if !defined(INT64_MAX) || !defined(LLONG_MAX) || !defined(LONG_MAX)
	#error "[CGDK10] INT64_MAX or LLONG_MAX or LONG_MAX  is not defined"
#endif

// 2) Format string for int64_t and uint64_t
#if INT64_MAX == LLONG_MAX
	//#pragma message("[CGDK10] x64")
	#define FORMAT_STRING_INT64		"%lld"
	#define FORMAT_STRING_UINT64	"%llu"
#elif INT64_MAX == LONG_MAX
	//#pragma message("[CGDK10] x64")
	#define FORMAT_STRING_INT64		"%ld"
	#define FORMAT_STRING_UINT64	"%lu"
#else 
	#error "unsupported uint64 size"
#endif


//-----------------------------------------------------------------------------
//                                                                            
// 3. String functions 
//
//-----------------------------------------------------------------------------
#if defined(_WIN32)
	#include "cgdk/sdk10/common/string_functions.windows.h"
#elif defined(__ANDROID__)
	#include <sstream>
	#include "cgdk/sdk10/common/string_functions.android.h"
#elif defined(__APPLE__)
	#include <sstream>
	#include "cgdk/sdk10/common/string_functions.ios.h"
#elif defined(__linux__)
	#include <sstream>
	#include "cgdk/sdk10/common/string_functions.linux.h"
#else
	#error "CGDK Not supported platform"
#endif
