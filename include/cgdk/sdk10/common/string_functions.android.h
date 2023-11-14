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

namespace CGDK
{
//-----------------------------------------------------------------------------
//                                                                            
// String functions for Android
//                                                                            
//                                                                            
//-----------------------------------------------------------------------------
// 1) String operation
// - strlen
inline size_t									__strlen	(const char*     _str, size_t _max = MAX_STRING_LENGTH)									{ return strlen	(_str); }
inline size_t									__strlen	(const wchar_t*  _str, size_t _max = MAX_STRING_LENGTH)									{ return wcslen	(_str); }
inline size_t									__strlen	(const char16_t* _str, size_t _max = MAX_STRING_LENGTH)									{ return std::u16string_view(_str).size(); }
inline size_t									__strlen	(const char32_t* _str, size_t _max = MAX_STRING_LENGTH)									{ return std::u32string_view(_str).size(); }
template<size_t I> inline size_t				__strlen	(const char     (&_str)[I])																{ return __strlen(_str, I); }
template<size_t I> inline size_t				__strlen	(const wchar_t  (&_str)[I])																{ return __strlen(_str, I); }
template<size_t I> inline size_t				__strlen	(const char16_t (&_str)[I])																{ return __strlen(_str, I); }
template<size_t I> inline size_t				__strlen	(const char32_t (&_str)[I])																{ return __strlen(_str, I); }

// - strcpy
inline std::string_view							__strcpy	(char*     _dest, size_t _max, std::string_view    _source)								{ auto count = __select_min(_source.size(), _max - 1);  _source.copy(_dest, count); _dest[count] = 0; return std::string_view(_dest, count); }
inline std::wstring_view						__strcpy	(wchar_t*  _dest, size_t _max, std::wstring_view   _source)								{ auto count = __select_min(_source.size(), _max - 1);  _source.copy(_dest, count); _dest[count] = 0; return std::wstring_view(_dest, count); }
inline std::u16string_view						__strcpy	(char16_t* _dest, size_t _max, std::u16string_view _source)								{ auto count = __select_min(_source.size(), _max - 1);  _source.copy(_dest, count); _dest[count] = 0; return std::u16string_view(_dest, count); }
inline std::u32string_view						__strcpy	(char32_t* _dest, size_t _max, std::u32string_view _source)								{ auto count = __select_min(_source.size(), _max - 1);  _source.copy(_dest, count); _dest[count] = 0; return std::u32string_view(_dest, count); }
template<size_t I> inline std::string_view		__strcpy	(char     (&_dest)[I], std::string_view    _source)										{ auto count = __select_min(_source.size(), I - 1);     _source.copy(_dest, count); _dest[count] = 0; return std::string_view(_dest, count); }
template<size_t I> inline std::wstring_view		__strcpy	(wchar_t  (&_dest)[I], std::wstring_view   _source)										{ auto count = __select_min(_source.size(), I - 1);     _source.copy(_dest, count); _dest[count] = 0; return std::wstring_view(_dest, count); }
template<size_t I> inline std::u16string_view	__strcpy	(char16_t (&_dest)[I], std::u16string_view _source)										{ auto count = __select_min(_source.size(), I - 1);     _source.copy(_dest, count); _dest[count] = 0; return std::u16string_view(_dest, count); }
template<size_t I> inline std::u32string_view	__strcpy	(char32_t (&_dest)[I], std::u32string_view _source)										{ auto count = __select_min(_source.size(), I - 1);     _source.copy(_dest, count); _dest[count] = 0; return std::u32string_view(_dest, count); }

// - strcmp
inline int32_t									__strcmp	(std::string_view    _str1, std::string_view    _str2)									{ return _str1.compare(_str2); }
inline int32_t									__strcmp	(std::wstring_view   _str1, std::wstring_view   _str2)									{ return _str1.compare(_str2); }
inline int32_t									__strcmp	(std::u16string_view _str1, std::u16string_view _str2)									{ return _str1.compare(_str2); }
inline int32_t									__strcmp	(std::u32string_view _str1, std::u32string_view _str2)									{ return _str1.compare(_str2); }

// - stricmp
inline int32_t									__stricmp	(std::string_view    _str1, std::string_view    _str2)									{ return std::equal(_str1.begin(), _str1.end(), _str2.begin(), _str2.end(), [](char a, char b) {return tolower(a) == tolower(b); }); }
inline int32_t									__stricmp	(std::wstring_view   _str1, std::wstring_view   _str2)									{ return std::equal(_str1.begin(), _str1.end(), _str2.begin(), _str2.end(), [](char a, char b) {return tolower(a) == tolower(b); }); }
inline int32_t									__stricmp	(std::u16string_view _str1, std::u16string_view _str2)									{ return std::equal(_str1.begin(), _str1.end(), _str2.begin(), _str2.end(), [](char a, char b) {return tolower(a) == tolower(b); }); }
inline int32_t									__stricmp	(std::u32string_view _str1, std::u32string_view _str2)									{ return std::equal(_str1.begin(), _str1.end(), _str2.begin(), _str2.end(), [](char a, char b) {return tolower(a) == tolower(b); }); }

// - strncmp
inline int32_t									__strncmp	(std::string_view    _str1, std::string_view    _str2, size_t _max=MAX_STRING_LENGTH)	{ return _str1.compare(0, _max, _str2); }
inline int32_t									__strncmp	(std::wstring_view   _str1, std::wstring_view   _str2, size_t _max=MAX_STRING_LENGTH)	{ return _str1.compare(0, _max, _str2); }
inline int32_t									__strncmp	(std::u16string_view _str1, std::u16string_view _str2, size_t _max=MAX_STRING_LENGTH)	{ return _str1.compare(0, _max, _str2); }
inline int32_t									__strncmp	(std::u32string_view _str1, std::u32string_view _str2, size_t _max=MAX_STRING_LENGTH)	{ return _str1.compare(0, _max, _str2); }

// - strnicmp
inline int32_t									__strnicmp	(std::string_view    _str1, std::string_view    _str2, size_t _max=MAX_STRING_LENGTH)	{ return strncasecmp(_str1.data(), _str2.data(), _max);}
inline int32_t									__strnicmp	(std::wstring_view   _str1, std::wstring_view   _str2, size_t _max=MAX_STRING_LENGTH)	{ return wcsncasecmp(_str1.data(), _str2.data(), _max);}
inline int32_t									__strnicmp	(std::u16string_view _str1, std::u16string_view _str2, size_t _max=MAX_STRING_LENGTH)	{ CGASSERT_ERROR(false); return 0;}
inline int32_t									__strnicmp	(std::u32string_view _str1, std::u32string_view _str2, size_t _max=MAX_STRING_LENGTH)	{ CGASSERT_ERROR(false); return 0;}

// - strcat
inline std::string_view							__strcat	(char*     _dest, size_t _max, std::string_view    _source)								{ return strcat	(_dest, _source.data());}
inline std::wstring_view						__strcat	(wchar_t*  _dest, size_t _max, std::wstring_view   _source)								{ return wcscat	(_dest, _source.data());}
inline std::u16string_view						__strcat	(char16_t* _dest, size_t _max, std::u16string_view _source)								{ CGASSERT_ERROR(false); return 0;}
inline std::u32string_view						__strcat	(char32_t* _dest, size_t _max, std::u32string_view _source)								{ CGASSERT_ERROR(false); return 0;}
template<size_t I> inline std::string_view		__strcat	(char      (&_dest)[I], std::string_view    _source)									{ return __strcat(_dest, I, _source.data());}
template<size_t I> inline std::wstring_view		__strcat	(wchar_t   (&_dest)[I], std::wstring_view   _source)									{ return __strcat(_dest, I, _source.data());}
template<size_t I> inline std::u16string_view	__strcat	(char16_t  (&_dest)[I], std::u16string_view _source)									{ return __strcat(_dest, I, _source.data());}
template<size_t I> inline std::u32string_view	__strcat	(char32_t  (&_dest)[I], std::u32string_view _source)									{ return __strcat(_dest, I, _source.data());}

// - sprintf
template<class TDEST, class... TARGS>
inline int __sprintf(TDEST*   const _dest,	size_t const _bufferCount, const std::basic_string_view<TDEST> _format, TARGS... _args)					{ CGASSERT_ERROR(false); return 0;}
template<class... TARGS>																																										  
inline int __sprintf(char*    const _dest,	size_t const _bufferCount, const std::basic_string_view<char> _format, TARGS... _args)					{ return snprintf(_dest, _bufferCount, _format.data(), _args...);}
template<class... TARGS>																																										  
inline int __sprintf(wchar_t* const _dest,	size_t const _bufferCount, const std::basic_string_view<wchar_t> _format, TARGS... _args)				{ return swprintf(_dest, _bufferCount, _format.data(), _args...);}
																																														  
template<class TDEST, size_t I, class... TARGS>																														  
inline int __sprintf(TDEST   (&_dest)[I], const std::basic_string_view<TDEST> _format, TARGS... _args)												{ CGASSERT_ERROR(false); return 0;}
template<size_t I, class... TARGS>																																					  
inline int __sprintf(char    (&_dest)[I], const std::basic_string_view<char> _format, TARGS... _args)												{ return snprintf(_dest, I, _format.data(), _args...);}
template<size_t I, class... TARGS>																																			  
inline int __sprintf(wchar_t (&_dest)[I], const std::basic_string_view<wchar_t> _format, TARGS... _args)											{ return swprintf(_dest, I, _format.data(), _args...);}
																																												  
// - vsprintf																																						  
template<class TDEST>																																				  
inline int __vsprintf(TDEST*   const _dest,	size_t const _bufferCount, const std::basic_string_view<TDEST> _format, va_list _arg)					{ CGASSERT_ERROR(false); return 0;}
template<class... TARGS>																																											  
inline int __vsprintf(char*    const _dest,	size_t const _bufferCount, const std::basic_string_view<char> _format, va_list _arg)					{ return vsnprintf(_dest, _bufferCount, _format.data(), _arg);}
template<class... TARGS>																																											  
inline int __vsprintf(wchar_t* const _dest,	size_t const _bufferCount, const std::basic_string_view<wchar_t> _format, va_list _arg)					{ return vswprintf(_dest, _bufferCount, _format.data(), _arg);}
																																									  
template<class TDEST, size_t I, class... TARGS>																														  
inline int __vsprintf(TDEST   (&_dest)[I], const std::basic_string_view<TDEST> _format, va_list _arg)												{ CGASSERT_ERROR(false); return 0;}
template<size_t I, class... TARGS>																																						  
inline int __vsprintf(char    (&_dest)[I], const std::basic_string_view<char> _format, va_list _arg)												{ return vsnprintf(_dest, I, _format.data(), _arg);}
template<size_t I, class... TARGS>																																						  
inline int __vsprintf(wchar_t (&_dest)[I], const std::basic_string_view<wchar_t> _format, va_list _arg)												{ return vswprintf(_dest, I, _format.data(), _arg);}

template<class TDEST, class... TARGS>
inline int __sscanf(const TDEST* _dest, const std::basic_string_view<TDEST> _format, TARGS... _args)												{ CGASSERT_ERROR(false); return 0; }
template<class... TARGS>
inline int __sscanf(const char* _dest, const std::basic_string_view<char> _format, TARGS... _args)													{ return sscanf(_dest, _format.data(), _args...); }
template<class... TARGS>
inline int __sscanf(const wchar_t* _dest, const std::basic_string_view<wchar_t> _format, TARGS... _args)											{ return swscanf(_dest, _format.data(), _args...); }


//-----------------------------------------------------------------------------
// converting functions - Convert String(1)
//-----------------------------------------------------------------------------
// - mbs
inline std::wstring_view						encode_string(wchar_t*  _dest, std::string_view _source, size_t _size = MAX_STRING_LENGTH)		{ mbstowcs(_dest, _source.data(), _size); return _dest;}	// mbtowc
inline std::u16string_view						encode_string(char16_t* _dest, std::string_view _source, size_t _size = MAX_STRING_LENGTH)		{ mbstate_t ps{}; auto result=mbrtoc16(_dest, _source.data(), _size, &ps); return (result>0) ? _dest : nullptr;}
inline std::u32string_view						encode_string(char32_t* _dest, std::string_view _source, size_t _size = MAX_STRING_LENGTH)		{ mbstate_t ps{}; auto result=mbrtoc32(_dest, _source.data(), _size, &ps); return (result>0) ? _dest : nullptr;}
template<size_t I> inline std::wstring_view		encode_string(wchar_t   (&_dest)[I], std::string_view _source)									{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u16string_view	encode_string(char16_t  (&_dest)[I], std::string_view _source)									{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u32string_view	encode_string(char32_t  (&_dest)[I], std::string_view _source)									{ return encode_string(_dest, _source, I);}

// - wcs
inline std::string_view							encode_string(char*     _dest, std::wstring_view _source, size_t _size = MAX_STRING_LENGTH)		{ wcstombs(_dest, _source.data(), _size); return _dest;}	// wctomb
inline std::u16string_view						encode_string(char16_t* _dest, std::wstring_view _source, size_t _size = MAX_STRING_LENGTH)		{ CGASSERT_ERROR(false); return _dest;}
inline std::u32string_view						encode_string(char32_t* _dest, std::wstring_view _source, size_t _size = MAX_STRING_LENGTH)		{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::string_view		encode_string(char      (&_dest)[I], std::wstring_view _source)									{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u16string_view	encode_string(char16_t  (&_dest)[I], std::wstring_view _source)									{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u32string_view	encode_string(char32_t  (&_dest)[I], std::wstring_view _source)									{ return encode_string(_dest, _source, I);}

// - u16s
inline std::string_view							encode_string(char*     _dest, std::u16string_view _source, size_t _size = MAX_STRING_LENGTH)
{
	const char16_t*	source	 = _source;
	char* 			dest	 = _dest;
	size_t			remained = _size;

	mbstate_t mbs{};
	mbrlen (NULL,0,&mbs);

	while(*source)
	{
		char	temp_buffer[6];
		auto	length = c16rtomb(temp_buffer,*source,&mbs);

		if ((length==0)||(length>MB_CUR_MAX) || remained<length) 
			break;

		for(size_t i=0;i<length;++i)
		{
			*(dest++)	 = temp_buffer[i];
		}

		remained	-= length;
		++source;
	}

	// 2) add null
	*dest = 0;

	return _dest;
}
inline std::wstring_view						encode_string(wchar_t*  _dest, std::u16string_view _source, size_t _size = MAX_STRING_LENGTH)	{ CGASSERT_ERROR(false); return _dest;}
inline std::u32string_view						encode_string(char32_t* _dest, std::u16string_view _source, size_t _size = MAX_STRING_LENGTH)	{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::string_view		encode_string(char      (&_dest)[I], std::u16string_view _source)								{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::wstring_view		encode_string(wchar_t   (&_dest)[I], std::u16string_view _source)								{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u32string_view	encode_string(char32_t  (&_dest)[I], std::u16string_view _source)								{ return encode_string(_dest, _source, I);}

// - u32s
inline std::string_view							encode_string(char*     _dest, std::u32string_view _source, size_t _size = MAX_STRING_LENGTH)
{
	const char32_t*	source	 = _source;
	char* 			dest	 = _dest;
	size_t			remained = _size;

	mbstate_t mbs{};
	mbrlen (NULL,0,&mbs);

	while(*source)
	{
		char	temp_buffer[6];
		auto	length = c32rtomb(temp_buffer,*source,&mbs);

		if ((length==0)||(length>MB_CUR_MAX) || remained<length) 
			break;

		for(size_t i=0;i<length;++i)
		{
			*(dest++)	 = temp_buffer[i];
		}

		remained	-= length;
		++source;
	}

	// 2) add null
	*dest = 0;

	return _dest;
}
inline std::wstring_view						encode_string(wchar_t*  _dest, std::u32string_view _source, size_t _size = MAX_STRING_LENGTH)	{ CGASSERT_ERROR(false); return _dest;}
inline std::u16string_view						encode_string(char16_t* _dest, std::u32string_view _source, size_t _size = MAX_STRING_LENGTH)	{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::string_view		encode_string(char      (&_dest)[I], std::u32string_view _source)		{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::wstring_view		encode_string(wchar_t   (&_dest)[I], std::u32string_view _source)		{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u16string_view	encode_string(char16_t  (&_dest)[I], std::u32string_view _source)		{ return encode_string(_dest, _source, I);}


//-----------------------------------------------------------------------------
// Strings
//-----------------------------------------------------------------------------
// 1) __from_string
template<class TTYPE> inline TTYPE				__from_string			(std::string_view);
template<class TTYPE> inline TTYPE				__from_string			(std::wstring_view);
template<class TTYPE> inline TTYPE				__from_string			(std::u16string_view);
template<class TTYPE> inline TTYPE				__from_string			(std::u32string_view);
																														  
template <> inline char							__from_string<char>		(std::string_view		_source)				{ return static_cast<char>(atoi(_source.data()));}
template <> inline char							__from_string<char>		(std::wstring_view		_source)				{ return static_cast<char>(wcstol(_source.data(), nullptr, 10));}
template <> inline char							__from_string<char>		(std::u16string_view	_source)				{ int value; std::basic_istringstream<char16_t> os(_source.data()); os>>value; return static_cast<char>(value);}
template <> inline char							__from_string<char>		(std::u32string_view	_source)				{ int value; std::basic_istringstream<char32_t> os(_source.data()); os>>value; return static_cast<char>(value);}
																															  
template <> inline int8_t						__from_string<int8_t>	(std::string_view		_source)				{ return static_cast<int8_t>(atoi(_source.data()));}
template <> inline int8_t						__from_string<int8_t>	(std::wstring_view		_source)				{ return static_cast<int8_t>(wcstol(_source.data(), nullptr, 10));}
template <> inline int8_t						__from_string<int8_t>	(std::u16string_view	_source)				{ int value; std::basic_istringstream<char16_t> os(_source.data()); os>>value; return static_cast<int8_t>(value);}
template <> inline int8_t						__from_string<int8_t>	(std::u32string_view	_source)				{ int value; std::basic_istringstream<char32_t> os(_source.data()); os>>value; return static_cast<int8_t>(value);}
																															  
template <> inline uint8_t						__from_string<uint8_t>	(std::string_view		_source)				{ return static_cast<uint8_t>(std::stoul(_source.data(), nullptr, 10));}
template <> inline uint8_t						__from_string<uint8_t>	(std::wstring_view		_source)				{ return static_cast<uint8_t>(wcstoul(_source.data(), nullptr, 10));}
template <> inline uint8_t						__from_string<uint8_t>	(std::u16string_view	_source)				{ int value; std::basic_istringstream<char16_t> os(_source.data()); os>>value; return static_cast<uint8_t>(value);}
template <> inline uint8_t						__from_string<uint8_t>	(std::u32string_view	_source)				{ int value; std::basic_istringstream<char32_t> os(_source.data()); os>>value; return static_cast<uint8_t>(value);}
																															  
template <> inline int16_t						__from_string<int16_t>	(std::string_view		_source)				{ return static_cast<int16_t>(atoi(_source.data()));}
template <> inline int16_t						__from_string<int16_t>	(std::wstring_view		_source)				{ return static_cast<int16_t>(wcstol(_source.data(), nullptr, 10));}
template <> inline int16_t						__from_string<int16_t>	(std::u16string_view	_source)				{ int16_t value; std::basic_istringstream<char16_t> os(_source.data()); os>>value; return value;}
template <> inline int16_t						__from_string<int16_t>	(std::u32string_view	_source)				{ int16_t value; std::basic_istringstream<char32_t> os(_source.data()); os>>value; return value;}
																															  
template <> inline uint16_t						__from_string<uint16_t>	(std::string_view		_source)				{ return static_cast<uint16_t>(std::stoul(_source.data(), nullptr, 10));}
template <> inline uint16_t						__from_string<uint16_t>	(std::wstring_view		_source)				{ return static_cast<uint16_t>(wcstoul(_source.data(), nullptr, 10));}
template <> inline uint16_t						__from_string<uint16_t>	(std::u16string_view	_source)				{ uint16_t value; std::basic_istringstream<char16_t> os(_source.data()); os>>value; return value;}
template <> inline uint16_t						__from_string<uint16_t>	(std::u32string_view	_source)				{ uint16_t value; std::basic_istringstream<char32_t> os(_source.data()); os>>value; return value;}
																															  
template <> inline int32_t						__from_string<int32_t>	(std::string_view		_source)				{ return atoi(_source.data());}
template <> inline int32_t						__from_string<int32_t>	(std::wstring_view		_source)				{ return wcstol(_source.data(), nullptr, 10);}
template <> inline int32_t						__from_string<int32_t>	(std::u16string_view	_source)				{ int32_t value; std::basic_istringstream<char16_t> os(_source.data()); os>>value; return value;}
template <> inline int32_t						__from_string<int32_t>	(std::u32string_view	_source)				{ int32_t value; std::basic_istringstream<char32_t> os(_source.data()); os>>value; return value;}
																															  
template <> inline uint32_t						__from_string<uint32_t>	(std::string_view		_source)				{ return strtoul(_source.data(), nullptr, 10);}
template <> inline uint32_t						__from_string<uint32_t>	(std::wstring_view		_source)				{ return wcstoul(_source.data(), nullptr, 10);}
template <> inline uint32_t						__from_string<uint32_t>	(std::u16string_view	_source)				{ uint32_t value; std::basic_istringstream<char16_t> os(_source.data()); os>>value; return value;}
template <> inline uint32_t						__from_string<uint32_t>	(std::u32string_view	_source)				{ uint32_t value; std::basic_istringstream<char32_t> os(_source.data()); os>>value; return value;}
																															  
template <> inline int64_t						__from_string<int64_t>	(std::string_view		_source)				{ return atoll(_source.data());}
template <> inline int64_t						__from_string<int64_t>	(std::wstring_view		_source)				{ return wcstoll(_source.data(), nullptr, 10);}
template <> inline int64_t						__from_string<int64_t>	(std::u16string_view	_source)				{ int64_t value; std::basic_istringstream<char16_t> os(_source.data()); os>>value; return value;}
template <> inline int64_t						__from_string<int64_t>	(std::u32string_view	_source)				{ int64_t value; std::basic_istringstream<char32_t> os(_source.data()); os>>value; return value;}
																															  
template <> inline uint64_t						__from_string<uint64_t>	(std::string_view		_source)				{ return strtoull(_source.data(), nullptr, 10);}
template <> inline uint64_t						__from_string<uint64_t>	(std::wstring_view		_source)				{ return wcstoull(_source.data(), nullptr, 10);}
template <> inline uint64_t						__from_string<uint64_t>	(std::u16string_view	_source)				{ uint64_t value; std::basic_istringstream<char16_t> os(_source.data()); os>>value; return value;}
template <> inline uint64_t						__from_string<uint64_t>	(std::u32string_view	_source)				{ uint64_t value; std::basic_istringstream<char32_t> os(_source.data()); os>>value; return value;}
																															  
template <> inline float						__from_string<float>	(std::string_view		_source)				{ return strtof(_source.data(), nullptr);}
template <> inline float						__from_string<float>	(std::wstring_view		_source)				{ return wcstof(_source.data(), nullptr);}
template <> inline float						__from_string<float>	(std::u16string_view	_source)				{ float value; std::basic_istringstream<char16_t> os(_source.data()); os>>value; return value;}
template <> inline float						__from_string<float>	(std::u32string_view	_source)				{ float value; std::basic_istringstream<char32_t> os(_source.data()); os>>value; return value;}
																															  
template <> inline double						__from_string<double>	(std::string_view		_source)				{ return strtod(_source.data(), nullptr);}
template <> inline double						__from_string<double>	(std::wstring_view		_source)				{ return wcstod(_source.data(), nullptr);}
template <> inline double						__from_string<double>	(std::u16string_view	_source)				{ double value; std::basic_istringstream<char16_t> os(_source.data()); os>>value; return value;}
template <> inline double						__from_string<double>	(std::u32string_view	_source)				{ double value; std::basic_istringstream<char32_t> os(_source.data()); os>>value; return value;}
																															  
// 2) __to_string																											  
template<class  STRING_T> inline STRING_T		__to_string	(char);
template<class  STRING_T> inline STRING_T		__to_string	(int8_t);
template<class  STRING_T> inline STRING_T		__to_string	(uint8_t);
template<class  STRING_T> inline STRING_T		__to_string	(int16_t);
template<class  STRING_T> inline STRING_T		__to_string	(uint16_t);
template<class  STRING_T> inline STRING_T		__to_string	(int32_t);
template<class  STRING_T> inline STRING_T		__to_string	(uint32_t);
template<class  STRING_T> inline STRING_T		__to_string	(int64_t);
template<class  STRING_T> inline STRING_T		__to_string	(uint64_t);
template<class  STRING_T> inline STRING_T		__to_string	(long long);
template<class  STRING_T> inline STRING_T		__to_string	(unsigned long long);
template<class  STRING_T> inline STRING_T		__to_string	(float);
template<class  STRING_T> inline STRING_T		__to_string	(double );
																																					  
inline std::string_view							__to_string	(char*     _dest, size_t _size, char _value)				{ snprintf(_dest, _size, "%d", _value); return _dest;}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		char _value)					{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, char _value)				{ swprintf(_dest, _size, L"%d", _value); return _dest;}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		char _value)					{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, char _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		char _value)					{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, char _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		char _value)					{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (char _value)												{ std::basic_ostringstream<char> os; os<<_value; return os.str();}
template<> inline std::basic_string<wchar_t>	__to_string (char _value)												{ std::basic_ostringstream<wchar_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char16_t>	__to_string (char _value)												{ std::basic_ostringstream<char16_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char32_t>	__to_string (char _value)												{ std::basic_ostringstream<char32_t> os; os<<_value; return os.str();}
																																					  
inline std::string_view							__to_string	(char*     _dest, size_t _size, int8_t _value)				{ snprintf(_dest, _size, "%d", _value); return _dest;}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		int8_t _value)					{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, int8_t _value)				{ swprintf(_dest, _size, L"%d", _value); return _dest;}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		int8_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, int8_t _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		int8_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, int8_t _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		int8_t _value)					{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (int8_t _value)												{ std::basic_ostringstream<char> os; os<<_value; return os.str();}
template<> inline std::basic_string<wchar_t>	__to_string (int8_t _value)												{ std::basic_ostringstream<wchar_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char16_t>	__to_string (int8_t _value)												{ std::basic_ostringstream<char16_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char32_t>	__to_string (int8_t _value)												{ std::basic_ostringstream<char32_t> os; os<<_value; return os.str();}
																																					  
inline std::string_view							__to_string	(char*     _dest, size_t _size, uint8_t _value)				{ snprintf(_dest, _size, "%u", _value); return _dest;}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		uint8_t _value)					{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, uint8_t _value)				{ swprintf(_dest, _size, L"%u", _value); return _dest;}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		uint8_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, uint8_t _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		uint8_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, uint8_t _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		uint8_t _value)					{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (uint8_t _value)											{ std::basic_ostringstream<char> os; os<<_value; return os.str();}
template<> inline std::basic_string<wchar_t>	__to_string (uint8_t _value)											{ std::basic_ostringstream<wchar_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char16_t>	__to_string (uint8_t _value)											{ std::basic_ostringstream<char16_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char32_t>	__to_string (uint8_t _value)											{ std::basic_ostringstream<char32_t> os; os<<_value; return os.str();}
																																					  
inline std::string_view							__to_string	(char*     _dest, size_t _size, int16_t _value)				{ snprintf(_dest, _size, "%d", _value); return _dest;}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		int16_t _value)					{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, int16_t _value)				{ swprintf(_dest, _size, L"%d", _value); return _dest;}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		int16_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, int16_t _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		int16_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, int16_t _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		int16_t _value)					{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (int16_t _value)											{ std::basic_ostringstream<char> os; os<<_value; return os.str();}
template<> inline std::basic_string<wchar_t>	__to_string (int16_t _value)											{ std::basic_ostringstream<wchar_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char16_t>	__to_string (int16_t _value)											{ std::basic_ostringstream<char16_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char32_t>	__to_string (int16_t _value)											{ std::basic_ostringstream<char32_t> os; os<<_value; return os.str();}
																																					  
inline std::string_view							__to_string	(char*     _dest, size_t _size, uint16_t _value)			{ snprintf(_dest, _size, "%u", _value); return _dest;}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		uint16_t _value)				{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, uint16_t _value)			{ swprintf(_dest, _size, L"%u", _value); return _dest;}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		uint16_t _value)				{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, uint16_t _value)			{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		uint16_t _value)				{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, uint16_t _value)			{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		uint16_t _value)				{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (uint16_t _value)											{ std::basic_ostringstream<char> os; os<<_value; return os.str();}
template<> inline std::basic_string<wchar_t>	__to_string (uint16_t _value)											{ std::basic_ostringstream<wchar_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char16_t>	__to_string (uint16_t _value)											{ std::basic_ostringstream<char16_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char32_t>	__to_string (uint16_t _value)											{ std::basic_ostringstream<char32_t> os; os<<_value; return os.str();}
																																					  
inline std::string_view							__to_string	(char*     _dest, size_t _size, int32_t _value)				{ snprintf(_dest, _size, "%d", _value); return _dest;}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		int32_t _value)					{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, int32_t _value)				{ swprintf(_dest, _size, L"%d", _value); return _dest;}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		int32_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, int32_t _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		int32_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, int32_t _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		int32_t _value)					{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (int32_t _value)											{ std::basic_ostringstream<char> os; os<<_value; return os.str();}
template<> inline std::basic_string<wchar_t>	__to_string (int32_t _value)											{ std::basic_ostringstream<wchar_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char16_t>	__to_string (int32_t _value)											{ std::basic_ostringstream<char16_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char32_t>	__to_string (int32_t _value)											{ std::basic_ostringstream<char32_t> os; os<<_value; return os.str();}
																															  
inline std::string_view							__to_string	(char*     _dest, size_t _size, uint32_t _value)			{ snprintf(_dest, _size, "%u", _value); return _dest;}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		uint32_t _value)				{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, uint32_t _value)			{ swprintf(_dest, _size, L"%u", _value); return _dest;}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		uint32_t _value)				{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, uint32_t _value)			{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		uint32_t _value)				{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, uint32_t _value)			{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		uint32_t _value)				{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (uint32_t _value)											{ std::basic_ostringstream<char> os; os<<_value; return os.str();}
template<> inline std::basic_string<wchar_t>	__to_string (uint32_t _value)											{ std::basic_ostringstream<wchar_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char16_t>	__to_string (uint32_t _value)											{ std::basic_ostringstream<char16_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char32_t>	__to_string (uint32_t _value)											{ std::basic_ostringstream<char32_t> os; os<<_value; return os.str();}
																																					  
inline std::string_view							__to_string	(char*     _dest, size_t _size, int64_t _value)				{ snprintf(_dest, _size, _CGTEXT_CHAR(FORMAT_STRING_INT64), static_cast<long long>(_value)); return _dest;}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		int64_t _value)					{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, int64_t _value)				{ swprintf(_dest, _size, _CGTEXT_WCHAR(FORMAT_STRING_INT64), static_cast<long long>(_value)); return _dest;}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		int64_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, int64_t _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		int64_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, int64_t _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		int64_t _value)					{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (int64_t _value)											{ std::basic_ostringstream<char> os; os<<_value; return os.str();}
template<> inline std::basic_string<wchar_t>	__to_string (int64_t _value)											{ std::basic_ostringstream<wchar_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char16_t>	__to_string (int64_t _value)											{ std::basic_ostringstream<char16_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char32_t>	__to_string (int64_t _value)											{ std::basic_ostringstream<char32_t> os; os<<_value; return os.str();}
																																					  
inline std::string_view							__to_string	(char*     _dest, size_t _size, uint64_t _value)			{ snprintf(_dest, _size, _CGTEXT_CHAR(FORMAT_STRING_UINT64), static_cast<unsigned long long>(_value)); return _dest;}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		uint64_t _value)				{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, uint64_t _value)			{ swprintf(_dest, _size, _CGTEXT_WCHAR(FORMAT_STRING_UINT64), static_cast<unsigned long long>(_value)); return _dest;}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		uint64_t _value)				{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, uint64_t _value)			{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		uint64_t _value)				{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, uint64_t _value)			{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		uint64_t _value)				{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (uint64_t _value)											{ std::basic_ostringstream<char> os; os<<_value; return os.str();}
template<> inline std::basic_string<wchar_t>	__to_string (uint64_t _value)											{ std::basic_ostringstream<wchar_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char16_t>	__to_string (uint64_t _value)											{ std::basic_ostringstream<char16_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char32_t>	__to_string (uint64_t _value)											{ std::basic_ostringstream<char32_t> os; os<<_value; return os.str();}
																																				  
inline std::string_view							__to_string	(char*     _dest, size_t _size, long long _value)			{ return __to_string(_dest, _size, (int64_t)_value);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I], long long _value)					{ return __to_string<I>(_dest, (int64_t)_value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, long long _value)			{ return __to_string(_dest, _size, (int64_t)_value);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I], long long _value)					{ return __to_string<I>(_dest, (int64_t)_value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, long long _value)			{ return __to_string(_dest, _size, (int64_t)_value);}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I], long long _value)					{ return __to_string<I>(_dest, (int64_t)_value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, long long _value)			{ return __to_string(_dest, _size, (int64_t)_value);}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I], long long _value)					{ return __to_string<I>(_dest, (int64_t)_value);}
template<> inline std::basic_string<char>		__to_string (long long _value)											{ return __to_string<std::basic_string<char>>((int64_t)_value);}
template<> inline std::basic_string<wchar_t>	__to_string (long long _value)											{ return __to_string<std::basic_string<wchar_t>>((int64_t)_value);}
template<> inline std::basic_string<char16_t>	__to_string (long long _value)											{ return __to_string<std::basic_string<char16_t>>((int64_t)_value);}
template<> inline std::basic_string<char32_t>	__to_string (long long _value)											{ return __to_string<std::basic_string<char32_t>>((int64_t)_value);}

inline std::string_view							__to_string	(char*     _dest, size_t _size, unsigned long long _value)	{ return __to_string(_dest, _size, (uint64_t)_value);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I], unsigned long long _value)			{ return __to_string<I>(_dest, (uint64_t)_value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, unsigned long long _value)	{ return __to_string(_dest, _size, (uint64_t)_value);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I], unsigned long long _value)			{ return __to_string<I>(_dest, (uint64_t)_value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, unsigned long long _value)	{ return __to_string(_dest, _size, (uint64_t)_value);}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I], unsigned long long _value)			{ return __to_string<I>(_dest, (uint64_t)_value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, unsigned long long _value)	{ return __to_string(_dest, _size, (uint64_t)_value);}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I], unsigned long long _value)			{ return __to_string<I>(_dest, (uint64_t)_value);}
template<> inline std::basic_string<char>		__to_string (unsigned long long _value)									{ return __to_string<std::basic_string<char>>((uint64_t)_value);}
template<> inline std::basic_string<wchar_t>	__to_string (unsigned long long _value)									{ return __to_string<std::basic_string<wchar_t>>((uint64_t)_value);}
template<> inline std::basic_string<char16_t>	__to_string (unsigned long long _value)									{ return __to_string<std::basic_string<char16_t>>((uint64_t)_value);}
template<> inline std::basic_string<char32_t>	__to_string (unsigned long long _value)									{ return __to_string<std::basic_string<char32_t>>((uint64_t)_value);}

inline std::string_view							__to_string	(char*     _dest, size_t _size, float _value)				{ snprintf(_dest, _size, "%f", _value); return _dest;}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		float _value)					{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, float _value)				{ swprintf(_dest, _size, L"%f", _value); return _dest;}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		float _value)					{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, float _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		float _value)					{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, float _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		float _value)					{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (float _value)												{ std::basic_ostringstream<char> os; os<<_value; return os.str();}
template<> inline std::basic_string<wchar_t>	__to_string (float _value)												{ std::basic_ostringstream<wchar_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char16_t>	__to_string (float _value)												{ std::basic_ostringstream<char16_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char32_t>	__to_string (float _value)												{ std::basic_ostringstream<char32_t> os; os<<_value; return os.str();}
																																					  
inline std::string_view							__to_string	(char*     _dest, size_t _size, double _value)				{ snprintf(_dest, _size, "%f", _value); return _dest;}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		double _value)					{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, double _value)				{ swprintf(_dest, _size, L"%f", _value); return _dest;}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		double _value)					{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, double _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		double _value)					{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, double _value)				{ CGASSERT_ERROR(false); return _dest;}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		double _value)					{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (double _value)												{ std::basic_ostringstream<char> os; os<<_value; return os.str();}
template<> inline std::basic_string<wchar_t>	__to_string (double _value)												{ std::basic_ostringstream<wchar_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char16_t>	__to_string (double _value)												{ std::basic_ostringstream<char16_t> os; os<<_value; return os.str();}
template<> inline std::basic_string<char32_t>	__to_string (double _value)												{ std::basic_ostringstream<char32_t> os; os<<_value; return os.str();}



// 5) Format string
inline std::string			__format(const char* _message)			{ return std::string(_message);}
template <class... TARGS>
inline std::string			__format(const char* _format, TARGS... _args)
{
	// declare) 
	char	message[MAX_STRING_LENGTH]{};

	// 1) Generate trace Message
	snprintf(reinterpret_cast<char*>(message), MAX_STRING_LENGTH, _format, _args...);

	// return) 
	return	std::string(message);
}

inline std::wstring			__format(const wchar_t* _message)		{ return std::wstring(_message);}
template <class... TARGS>
inline std::wstring			__format(const wchar_t* _format, TARGS... _args)
{
	// declare) 
	wchar_t	message[MAX_STRING_LENGTH]{};

	// 1) Generate trace Message
	snwprintf(reinterpret_cast<wchar_t*>(message), MAX_STRING_LENGTH, _format, _args...);

	// return) 
	return	std::wstring(message);
}

inline std::u16string		__format(const char16_t* _message)		{ return std::u16string(_message);}
template <class... TARGS>
inline std::u16string		__format(const char16_t* _format, TARGS... _args)
{
	// declare) 
	char16_t	message[MAX_STRING_LENGTH]{};

	// 1) Generate trace Message
	_snwprintf_s(reinterpret_cast<wchar_t*>(message), MAX_STRING_LENGTH, _format, _args...);

	// return) 
	return	std::u16string(message);
}

inline std::u32string		__format(const char32_t* _message)		{ return std::u32string(_message);}
template <class... TARGS>
inline std::u32string		__format(const char32_t* _format, TARGS... _args)
{
	// Error) Dont support char32_t
	CGASSERT_ERROR(false);

	// return) 
	return	std::u32string();
}

template<class TTCHAR, size_t I>
inline void					__to_lower(TTCHAR  (&_dest)[I], const TTCHAR* _source)
{
	TTCHAR*			iter = _dest;
	const TTCHAR*	end	 = _dest+I-1;

	for(;iter<end; ++_source, ++iter)
	{
		if(*_source==0)
			break;

		*iter = static_cast<TTCHAR>(::tolower(*_source));
	}
	*iter	 = 0;

	// check)
	CGASSERT_ERROR(iter!=end);
}



//-----------------------------------------------------------------------------
//                                                                            
// memory functions
//                                                                            
//                                                                            
//-----------------------------------------------------------------------------
inline void	__zero_memory(void* _dest, size_t _size) noexcept
{
	bzero(_dest, _size);
}


}