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
// 1. standard string lib
//
//-----------------------------------------------------------------------------
// 1) string
#include <string.h>
#include <string_view>
#include "cgdk/sdk10/containers/static_string"

// opt) char8_t
#ifndef __cpp_char8_t
typedef uint8_t	char8_t;

namespace std
{
	typedef basic_string<char8_t>		u8string;
	typedef basic_string_view<char8_t>	u8string_view;
}
#endif

// 2) string literals
using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

//-----------------------------------------------------------------------------
//                                                                            
// 2. Configure of character type
//
// - Wide char�� compiler�� platform�� ���� �ٸ� ���� �ִ�.
//   C++ǥ���� char16_t�� ����� ���������� �ʿ信 ���� wchar_t�� ����ص� �ȴ�.
//   (CGCII�� Default�� char16_t�� �����Ǿ� �ִ�.)
//
// - wchar_t�� clang������ 32bit�̸� Visual C++ compiler������ 16Bit�̴�.
//                                                                            
// 2. Character Set
//
//	  1) 	// 
//	  2) 
//	  3) 
//	  4) 
//
//-----------------------------------------------------------------------------
// 1) String Functions
#include "cgdk/sdk10/common/string_functions.h"

// 2) Default String format 
#if !defined(_USE_CHAR_STRING) && !defined(_USE_WCHAR_STRING) && !defined(_USE_CHAR16_STRING) && !defined(_USE_CHAR32_STRING)
	#define	_USE_CHAR_STRING
#endif

// 3) CGFUNCTION
#if defined(_WIN32)
	#define __CGFUNCTION__						"[" __FUNCTION__ "]"
#else
	#define __CGFUNCTION__						"[" << __FUNCTION__ << "]"
#endif


//-----------------------------------------------------------------------------
//                                                                            
// 3. char ���ڿ��� �⺻ �ڵ�
//
//	  _USE_CHAR_STRING
//	  _USE_WCHAR_STRING
//	  _USE_CHAR16_STRING
//	  _USE_CHAR32_STRING
//
//
// 4. char encoding
//
//    _USE_MBCS_ENCODING		Windows Multi-byte CP_949
//	  _USE_UNICODEWCHAR_STRING	Windows Unicode
//    _USE_UTF8_ENCODING		UTF-8
//    _USE_UCS16_ENCODING		UCS-16
//
//    char ���ڿ��� �⺻������ _USE_CHAR_STRING(CP_949)�� ����Ѵ�.
//
//-----------------------------------------------------------------------------
// 1) 
enum class eCHARACTER_SET
{
	NONE			 = 0,
	MBCS			 = 1,
	UTF8			 = 2,
	UCS2			 = 3,
	UCS4			 = 4,
	MAX_
};

// 2) 
enum class eEOL_TYPE
{
	NONE			 = 0,
	CRLF			 = 1,	// Windows default
	LF				 = 2,	// Linux default
	CR				 = 3,	// Mac OS
	NULL_			 = 4,
	CR_NULL			 = 5,
	MAX_
};

// 2) to_string functions
template <class T>	std::basic_string_view<T> to_string(eCHARACTER_SET _character_set) noexcept;
template <> std::string_view to_string<char>(eCHARACTER_SET _character_set) noexcept;
template <> std::wstring_view to_string<wchar_t>(eCHARACTER_SET _character_set) noexcept;

template <class T> std::basic_string_view<T> to_string(eEOL_TYPE _eol_code) noexcept;
template <> std::string_view to_string<char>(eEOL_TYPE _eol_code) noexcept;
template <> std::wstring_view to_string<wchar_t>(eEOL_TYPE _eol_code) noexcept;


//-----------------------------------------------------------------------------
//
// 5. Default character code
//
//-----------------------------------------------------------------------------
// 1) default character encoding
#define	_DEFAULT_CHAR_CHARACTER_SET		eCHARACTER_SET::MBCS
#define	_DEFAULT_WCHAR_CHARACTER_SET	eCHARACTER_SET::UCS2
#define	_DEFAULT_CHAR16_CHARACTER_SET	eCHARACTER_SET::UCS2
#define	_DEFAULT_CHAR32_CHARACTER_SET	eCHARACTER_SET::UCS4

// 2) File END OF LINE
#if defined(_WIN32)
	#define	_DEFAULT_FILE_EOL_TYPE		eEOL_TYPE::CRLF	// Windows
#elif defined(__linux__)
	#define	_DEFAULT_FILE_EOL_TYPE		eEOL_TYPE::LF	// Linux
#elif defined(__APPLE__)
	#define	_DEFAULT_FILE_EOL_TYPE		eEOL_TYPE::CR	// Mac OS
#elif defined(__ANDROID__)
	#define	_DEFAULT_FILE_EOL_TYPE		eEOL_TYPE::LF	// abdroid
#endif

// 3) char
#if defined(_USE_CHAR_STRING)
	using _CHAR = char;
	#define	_CGTEXT(quote)				__CGTEXT_CHAR_(quote)

// 4) wchar_t
#elif defined(_USE_WCHAR_STRING)
	using _CHAR = wchar_t;
	#define	_CGTEXT(quote)				__CGTEXT_WCHAR_(quote)

// 5) char16_t
#elif defined(_USE_CHAR16_STRING)
	using _CHAR = char16_t;
	#define	_CGTEXT(quote)				__CGTEXT_CHAR16_(quote)

// 6) char32_t
#elif defined(_USE_CHAR32_STRING)
	using _CHAR = char32_t;
	#define	_CGTEXT(quote)				__CGTEXT_CHAR32_(quote)
#else
	#error "CGCII String Set is NOT Defined"
#endif
