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


template <class TTYPE>
struct case_insensitive_traits : std::char_traits<TTYPE>
{
	static TTYPE tolower(TTYPE _c) noexcept		{ return (_c>=TTYPE('A') && _c<= TTYPE('Z')) ? TTYPE(_c + (TTYPE('a') - TTYPE('A'))) : _c; }
	static bool eq(TTYPE c, TTYPE d) noexcept	{ return tolower(c) == tolower(d); }
	static bool lt(TTYPE c, TTYPE d) noexcept	{ return tolower(c) < tolower(d); }
	static int compare(const TTYPE* p, const TTYPE* q, size_t n) noexcept
	{
		while (n--) { if (!eq(*p, *q)) return lt(*p, *q) ? -1 : 1; ++p; ++q; }
		return 0;
	}
	static int comparei(const TTYPE* p, const TTYPE* q, size_t n) noexcept
	{
		while (n--) { if (!eq(*p, *q)) return lt(*p, *q) ? -1 : 1; ++p; ++q; }
		return 0;
	}
};

namespace CGDK
{
template <class T>
inline std::basic_string_view<T>				__strcat(T* _dest, size_t _max, std::basic_string_view<T> _source)
{
	// check) 
	CGASSERT_ERROR(_dest != nullptr);

	// check)
	if (_dest == nullptr)
		throw std::exception();

	// check) 
	CGASSERT_ERROR(_source.empty() == false);

	// 1) Get Dest length
	size_t count = std::char_traits<T>::length(_dest);

	// 2) Get Dest + Source length
	auto total_count = count;

	if (_source.empty() == false)
	{
		total_count += _source.size();
	}

	// check)
	if (count < _max && count != 0)
	{
		// check) Saturate _max
		if (total_count >= _max)
		{
			count = _max - 1;
		}

		// 3) copy _source to _dest
		memcpy(_dest + count, _source.data(), sizeof(T) * (total_count - count));
	}
	else
	{
	}

	// 4) append NULL
	_dest[total_count] = T(0);

	// return) 
	return std::basic_string_view<T>(_source.data(), total_count);
}


//-----------------------------------------------------------------------------
//                                                                            
// String functions for WIN32
//                                                                            
//                                                                            
//-----------------------------------------------------------------------------
// - strlen
inline size_t									__strlen	(const char*     _str, size_t _max = MAX_STRING_LENGTH)									{ CGASSERT_ERROR(_str != nullptr); return strnlen_s	(_str, _max);}
inline size_t									__strlen	(const wchar_t*  _str, size_t _max = MAX_STRING_LENGTH)									{ CGASSERT_ERROR(_str != nullptr); return wcsnlen_s	(_str, _max);}
inline size_t									__strlen	(const char16_t* _str, size_t _max = MAX_STRING_LENGTH)									{ _max; CGASSERT_ERROR(_str != nullptr); return std::u16string_view(_str).size();}
inline size_t									__strlen	(const char32_t* _str, size_t _max = MAX_STRING_LENGTH)									{ _max; CGASSERT_ERROR(_str != nullptr); return std::u32string_view(_str).size(); }
template<size_t I> inline size_t				__strlen	(const char     (&_str)[I])																{ return __strlen(_str, I);}
template<size_t I> inline size_t				__strlen	(const wchar_t  (&_str)[I])																{ return __strlen(_str, I);}
template<size_t I> inline size_t				__strlen	(const char16_t (&_str)[I])																{ return __strlen(_str, I);}
template<size_t I> inline size_t				__strlen	(const char32_t (&_str)[I])																{ return __strlen(_str, I);}

// - strcpy
inline std::string_view							__strcpy	(char*     _dest, size_t _max, std::string_view    _source)								{ CGASSERT_ERROR(_dest != nullptr); auto count = __select_min(_source.size(), _max - 1);  _source.copy(_dest, count); _dest[count] = 0; return std::string_view(_dest, count); }
inline std::wstring_view						__strcpy	(wchar_t*  _dest, size_t _max, std::wstring_view   _source)								{ CGASSERT_ERROR(_dest != nullptr); auto count = __select_min(_source.size(), _max - 1);  _source.copy(_dest, count); _dest[count] = 0; return std::wstring_view(_dest, count); }
inline std::u16string_view						__strcpy	(char16_t* _dest, size_t _max, std::u16string_view _source)								{ CGASSERT_ERROR(_dest != nullptr); auto count = __select_min(_source.size(), _max - 1);  _source.copy(_dest, count); _dest[count] = 0; return std::u16string_view(_dest, count); }
inline std::u32string_view						__strcpy	(char32_t* _dest, size_t _max, std::u32string_view _source)								{ CGASSERT_ERROR(_dest != nullptr); auto count = __select_min(_source.size(), _max - 1);  _source.copy(_dest, count); _dest[count] = 0; return std::u32string_view(_dest, count); }
template<size_t I> inline std::string_view		__strcpy	(char     (&_dest)[I], std::string_view    _source)										{ auto count = __select_min(_source.size(), I - 1); *(_dest + count) = 0; _source.copy(_dest, count); return std::string_view(_dest, count);}
template<size_t I> inline std::wstring_view		__strcpy	(wchar_t  (&_dest)[I], std::wstring_view   _source)										{ auto count = __select_min(_source.size(), I - 1); *(_dest + count) = 0; _source.copy(_dest, count); return std::wstring_view(_dest, count); }
template<size_t I> inline std::u16string_view	__strcpy	(char16_t (&_dest)[I], std::u16string_view _source)										{ auto count = __select_min(_source.size(), I - 1); *(_dest + count) = 0; _source.copy(_dest, count); return std::u16string_view(_dest, count); }
template<size_t I> inline std::u32string_view	__strcpy	(char32_t (&_dest)[I], std::u32string_view _source)										{ auto count = __select_min(_source.size(), I - 1); *(_dest + count) = 0; _source.copy(_dest, count); return std::u32string_view(_dest, count); }

// - strcmp
inline int32_t									__strcmp	(std::string_view    _str1, std::string_view    _str2)									{ return _str1.compare(_str2); }
inline int32_t									__strcmp	(std::wstring_view   _str1, std::wstring_view   _str2)									{ return _str1.compare(_str2); }
inline int32_t									__strcmp	(std::u16string_view _str1, std::u16string_view _str2)									{ return _str1.compare(_str2); }
inline int32_t									__strcmp	(std::u32string_view _str1, std::u32string_view _str2)									{ return _str1.compare(_str2); }

// - stricmp
inline int32_t									__stricmp	(std::string_view    _str1, std::string_view    _str2)									{ CGASSERT_ERROR(_str1.empty() == false); CGASSERT_ERROR(_str2.empty() == false); return _stricmp(_str1.data(), _str2.data());}
inline int32_t									__stricmp	(std::wstring_view   _str1, std::wstring_view   _str2)									{ CGASSERT_ERROR(_str1.empty() == false); CGASSERT_ERROR(_str2.empty() == false); return _wcsicmp(_str1.data(), _str2.data());}
inline int32_t									__stricmp	(std::u16string_view _str1, std::u16string_view _str2)									{ CGASSERT_ERROR(_str1.empty() == false); CGASSERT_ERROR(_str2.empty() == false); return case_insensitive_traits<char16_t>::compare(_str1.data(), _str2.data(), _str1.size());}
inline int32_t									__stricmp	(std::u32string_view _str1, std::u32string_view _str2)									{ CGASSERT_ERROR(_str1.empty() == false); CGASSERT_ERROR(_str2.empty() == false);return case_insensitive_traits<char32_t>::compare(_str1.data(), _str2.data(), _str1.size());}

// - strncmp
inline int32_t									__strncmp	(std::string_view    _str1, std::string_view    _str2, size_t _max = MAX_STRING_LENGTH)	{ CGASSERT_ERROR(_str1.empty() == false); CGASSERT_ERROR(_str2.empty() == false); return strncmp(_str1.data(), _str2.data(), _max);}
inline int32_t									__strncmp	(std::wstring_view   _str1, std::wstring_view   _str2, size_t _max = MAX_STRING_LENGTH)	{ CGASSERT_ERROR(_str1.empty() == false); CGASSERT_ERROR(_str2.empty() == false); return wcsncmp(_str1.data(), _str2.data(), _max);}
inline int32_t									__strncmp	(std::u16string_view _str1, std::u16string_view _str2, size_t _max = MAX_STRING_LENGTH)	{ CGASSERT_ERROR(_str1.empty() == false); CGASSERT_ERROR(_str2.empty() == false); return _str1.compare(0, _max, _str2);}
inline int32_t									__strncmp	(std::u32string_view _str1, std::u32string_view _str2, size_t _max = MAX_STRING_LENGTH)	{ CGASSERT_ERROR(_str1.empty() == false); CGASSERT_ERROR(_str2.empty() == false); return _str1.compare(0, _max, _str2);}

// - strnicmp																													  									  
inline int32_t									__strnicmp	(std::string_view    _str1, std::string_view    _str2, size_t _max = MAX_STRING_LENGTH)	{ CGASSERT_ERROR(_str1.empty() == false); CGASSERT_ERROR(_str2.empty() == false); return _strnicmp(_str1.data(), _str2.data(), _max);}
inline int32_t									__strnicmp	(std::wstring_view   _str1, std::wstring_view   _str2, size_t _max = MAX_STRING_LENGTH)	{ CGASSERT_ERROR(_str1.empty() == false); CGASSERT_ERROR(_str2.empty() == false); return _wcsnicmp(_str1.data(), _str2.data(), _max);}
inline int32_t									__strnicmp	(std::u16string_view _str1, std::u16string_view _str2, size_t _max = MAX_STRING_LENGTH)	{ CGASSERT_ERROR(_str1.empty() == false); CGASSERT_ERROR(_str2.empty() == false); return case_insensitive_traits<char16_t>::comparei(_str1.data(), _str2.data(), _max);}
inline int32_t									__strnicmp	(std::u32string_view _str1, std::u32string_view _str2, size_t _max = MAX_STRING_LENGTH)	{ CGASSERT_ERROR(_str1.empty() == false); CGASSERT_ERROR(_str2.empty() == false); return case_insensitive_traits<char32_t>::comparei(_str1.data(), _str2.data(), _max);}

// - strcat
inline std::string_view							__strcat	(char*     _dest, size_t _max, std::string_view    _source)								{ return __strcat<char>(_dest, _max, _source); }
inline std::wstring_view						__strcat	(wchar_t*  _dest, size_t _max, std::wstring_view   _source)								{ return __strcat<wchar_t>(_dest, _max, _source); }
inline std::u16string_view						__strcat	(char16_t* _dest, size_t _max, std::u16string_view _source)								{ return __strcat<char16_t>(_dest, _max, _source);}
inline std::u32string_view						__strcat	(char32_t* _dest, size_t _max, std::u32string_view _source)								{ return __strcat<char32_t>(_dest, _max, _source);}
template<size_t I> inline std::string_view		__strcat	(char      (&_dest)[I], std::string_view    _source)									{ return __strcat(_dest, I, _source);}
template<size_t I> inline std::wstring_view		__strcat	(wchar_t   (&_dest)[I], std::wstring_view   _source)									{ return __strcat(_dest, I, _source);}
template<size_t I> inline std::u16string_view	__strcat	(char16_t  (&_dest)[I], std::u16string_view _source)									{ return __strcat(_dest, I, _source);}
template<size_t I> inline std::u32string_view	__strcat	(char32_t  (&_dest)[I], std::u32string_view _source)									{ return __strcat(_dest, I, _source);}

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
inline int __sprintf(char    (&_dest)[I], const std::basic_string_view<char> _format, TARGS... _args)												{ return std::snprintf(_dest, I, _format.data(), _args...);}
template<size_t I, class... TARGS>																																			  		 
inline int __sprintf(wchar_t (&_dest)[I], const std::basic_string_view<wchar_t> _format, TARGS... _args)											{ return swprintf(_dest, I, _format.data(), _args...);}

// - vsprintf																																						  
template<class TDEST>																																				  
inline int __vsprintf(TDEST*   const _dest,	size_t const _bufferCount, const std::basic_string_view<TDEST> _format, va_list _arg)					{ CGASSERT_ERROR(false); return 0;}
template<class... TARGS>																																											  
inline int __vsprintf(char*    const _dest,	size_t const _bufferCount, const std::basic_string_view<char> _format, va_list _arg)					{ return _vsnprintf_s(_dest, _bufferCount, _TRUNCATE, _format.data(), _arg);}
template<class... TARGS>																																											  		 
inline int __vsprintf(wchar_t* const _dest,	size_t const _bufferCount, const std::basic_string_view<wchar_t> _format, va_list _arg)					{ return _vsnwprintf_s(_dest, _bufferCount, _TRUNCATE, _format.data(), _arg);}

template<class TDEST, size_t I, class... TARGS>																														  
inline int __vsprintf(TDEST   (&_dest)[I], const std::basic_string_view<TDEST> _format, va_list _arg)												{ CGASSERT_ERROR(false); return 0;}
template<size_t I, class... TARGS>																																					  
inline int __vsprintf(char    (&_dest)[I], const std::basic_string_view<char> _format, va_list _arg)												{ return _vsnprintf_s(_dest, I, _TRUNCATE, _format.data(), _arg);}
template<size_t I, class... TARGS>																																					  		 
inline int __vsprintf(wchar_t (&_dest)[I], const std::basic_string_view<wchar_t> _format, va_list _arg)												{ return _vsnwprintf_s(_dest, I, _TRUNCATE, _format.data(), _arg);}

template<class TDEST, class... TARGS>
inline int __sscanf(const TDEST* _dest, const std::basic_string_view<TDEST> _format, TARGS... _args)												{ CGASSERT_ERROR(false); return 0; }
template<class... TARGS>
inline int __sscanf(const char* _dest, const std::basic_string_view<char> _format, TARGS... _args)													{ return sscanf_s(_dest, _format.data(), _args...); }
template<class... TARGS>																																					 
inline int __sscanf(const wchar_t* _dest, const std::basic_string_view<wchar_t> _format, TARGS... _args)											{ return swscanf_s(_dest, _format.data(), _args...); }


//-----------------------------------------------------------------------------
// converting functions - Convert String(1)
//-----------------------------------------------------------------------------
// - mbs
inline std::wstring_view						encode_string(wchar_t* _dest, std::string_view _source, size_t _size = MAX_STRING_LENGTH)
{
	// check)
	CGASSERT_ERROR(_source.size() <= _size);

	// 1) multibyte를 wide char로 변경한다.
	auto result_length = MultiByteToWideChar(CP_ACP, 0, _source.data(), static_cast<int>(_source .size()), _dest, static_cast<int>(_size)); 

	// check) 결과가 0과 같거나 작으면 오류다.
	RETURN_IF(result_length < 0, std::wstring_view());

	// 2) add null
	_dest[result_length] = 0;

	// return) 결과값을 리턴한다.
	return std::wstring_view(_dest, result_length);
}
inline std::u16string_view						encode_string(char16_t* _dest, std::string_view _source, size_t _size = MAX_STRING_LENGTH)
{
	// declare) 
	std::mbstate_t ps{};
	
	// 1) 변환한다.
	auto result_length = mbrtoc16(_dest, _source.data(), _size, &ps);

	// check) 결과가 0과 같거나 작으면 오류다.
	RETURN_IF(result_length < 0, std::u16string_view());

	// 2) add null
	_dest[result_length] = 0;

	// return) 결과값을 리턴한다.
	return (result_length > 0) ? std::u16string_view(_dest, result_length) : std::u16string_view();
}
inline std::u32string_view						encode_string(char32_t* _dest, std::string_view _source, size_t _size = MAX_STRING_LENGTH)
{
	// declare) 
	mbstate_t ps{};
	
	// 1) 변환한다.
	auto result_length = mbrtoc32(_dest, _source.data(), _size, &ps);

	// check) 결과가 0과 같거나 작으면 오류다.
	RETURN_IF(result_length < 0, std::u32string_view());

	// 2) add null
	_dest[result_length] = 0;

	// return) 결과값을 리턴한다.
	return (result_length >0) ? std::u32string_view(_dest, result_length) : std::u32string_view();
}
template<size_t I> inline std::wstring_view		encode_string(wchar_t   (&_dest)[I], std::string_view _source)										{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u16string_view	encode_string(char16_t  (&_dest)[I], std::string_view _source)										{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u32string_view	encode_string(char32_t  (&_dest)[I], std::string_view _source)										{ return encode_string(_dest, _source, I);}

// - wcs
inline std::string_view							encode_string(char*     _dest, std::wstring_view _source, size_t _size = MAX_STRING_LENGTH)		
{
	// check)
	CGASSERT_ERROR(_source.size() < _size);

	// 1) wide char를 multibyte로 변경한다.
	auto result_length = WideCharToMultiByte(CP_ACP, 0, _source.data(), static_cast<int>(_source.size()), _dest, static_cast<int>(_size), nullptr, nullptr);

	// check) 결과가 0과 같거나 작으면 오류다.
	RETURN_IF(result_length < 0, std::string_view());

	// 2) add null
	_dest[result_length] = 0;

	// return) 결과값을 리턴한다.
	return std::string_view(_dest, result_length);
}
inline std::u16string_view						encode_string(char16_t* _dest, std::wstring_view _source, size_t _size = MAX_STRING_LENGTH)
{
	// check)
	CGASSERT_ERROR(sizeof(char16_t) == sizeof(wchar_t));

	// check)
	CGASSERT_ERROR(_source.size() <= _size)

	// check)
	THROW_IF(_source.size() > _size, std::length_error("buffser overflow 'encode_string(char16_t*, std::wstring_view)'"));

	auto length = _source.size();
	memcpy(_dest, _source.data(), length * sizeof(wchar_t));
	// 2) add null
	_dest[length] = 0;

	return std::u16string_view(_dest, length);
}
inline std::u32string_view						encode_string(char32_t* _dest, std::wstring_view _source, size_t _size = MAX_STRING_LENGTH)
{
	// check)
	CGASSERT_ERROR(sizeof(char16_t) == sizeof(wchar_t));

	// check)
	CGASSERT_ERROR(_source.size() <= _size)

	// check)
	THROW_IF(_source.size() > _size, std::length_error("buffser overflow 'encode_string(char32_t*, std::wstring_view)'"));

	auto length = _source.size();
	auto iter_dest = _dest;
	auto iter_src = _source.begin();
	auto iter_src_end = iter_src + length;
	for (; iter_src != iter_src_end; ++iter_src, ++iter_dest)
	{
		*iter_dest = static_cast<char32_t>(*iter_src);
	}
	// 2) add null
	*iter_dest = 0;

	return std::u32string_view(_dest, length);
}
template<size_t I> inline std::string_view		encode_string(char      (&_dest)[I], std::wstring_view _source)										{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u16string_view	encode_string(char16_t  (&_dest)[I], std::wstring_view _source)										{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u32string_view	encode_string(char32_t  (&_dest)[I], std::wstring_view _source)										{ return encode_string(_dest, _source, I);}

// - u8s
template<size_t I> inline std::string_view		encode_string(char      (&_dest)[I], std::u8string_view _source)									{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::wstring_view		encode_string(wchar_t   (&_dest)[I], std::u8string_view _source)									{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u32string_view	encode_string(char32_t  (&_dest)[I], std::u8string_view _source)									{ return encode_string(_dest, _source, I);}

// - u16s
inline std::string_view							encode_string(char*     _dest, std::u16string_view _source, size_t _size = MAX_STRING_LENGTH)
{
	char* dest = _dest;
	size_t remained = _size;

	mbstate_t mbs{};
	mbrlen (NULL,0,&mbs);

	for(auto iter: _source)
	{
		char temp_buffer[6];
		auto length = c16rtomb(temp_buffer,iter,&mbs);

		if ((length == 0) || (length > size_t(MB_CUR_MAX)) || remained < length) 
			break;

		for(size_t i=0;i<length;++i)
		{
			*(dest++) = *(temp_buffer +i);
		}

		remained -= length;
	}
	
	// 2) add null
	*dest = 0;

	return std::string_view(_dest, dest - _dest - 1);
}
inline std::wstring_view						encode_string(wchar_t*  _dest, std::u16string_view _source, size_t _size = MAX_STRING_LENGTH)
{
	// check)
	CGASSERT_ERROR(sizeof(char16_t) == sizeof(wchar_t));

	// check)
	CGASSERT_ERROR(_source.size() <= _size)

	// check)
	THROW_IF(_source.size() > _size, std::length_error("buffser overflow 'encode_string(wchar_t*, std::u16string_view)'"));

	auto length = _source.size();
	memcpy(_dest, _source.data(), length * sizeof(wchar_t));

	// 2) add null
	_dest[length] = 0;

	// return) 
	return std::wstring_view(_dest, length);
}
inline std::u32string_view						encode_string(char32_t* _dest, std::u16string_view _source, size_t _size = MAX_STRING_LENGTH)
{
	// check)
	CGASSERT_ERROR(sizeof(char16_t) == sizeof(wchar_t));

	// check)
	CGASSERT_ERROR(_source.size() <= _size)

	// check)
	THROW_IF(_source.size() > _size, std::length_error("buffser overflow 'encode_string(char32_t*, std::u16string_view)'"));

	// 1) encoding
	auto length = _source.size();
	auto iter_dest = _dest;
	auto iter_src = _source.begin();
	auto iter_src_end = iter_src + length;
	for (; iter_src != iter_src_end; ++iter_src, ++iter_dest)
	{
		*iter_dest = static_cast<char32_t>(*iter_src);
	}

	// 2) add null
	*iter_dest = 0;

	// return) 
	return std::u32string_view(_dest, length);
}
template<size_t I> inline std::string_view		encode_string(char      (&_dest)[I], std::u16string_view _source)									{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::wstring_view		encode_string(wchar_t   (&_dest)[I], std::u16string_view _source)									{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u32string_view	encode_string(char32_t  (&_dest)[I], std::u16string_view _source)									{ return encode_string(_dest, _source, I);}

// - u32s
inline std::string_view							encode_string(char*     _dest, std::u32string_view _source, size_t _size = MAX_STRING_LENGTH)
{
	char* dest = _dest;
	size_t remained = _size;

	mbstate_t mbs{};
	mbrlen (NULL,0,&mbs);

	// 1) encoding
	for(auto iter: _source)
	{
		char temp_buffer[6];
		auto length = c32rtomb(temp_buffer,iter,&mbs);

		if ((length == 0) || (length > size_t(MB_CUR_MAX)) || remained < length)
			break;

		for(size_t i=0;i<length;++i)
		{
			*(dest++) = *(temp_buffer + i);
		}

		remained-= length;
	}

	// 2) add null
	*dest = 0;

	return std::string_view(_dest, dest - _dest -1);
}
inline std::wstring_view						encode_string(wchar_t*  _dest, std::u32string_view _source, size_t _size = MAX_STRING_LENGTH)
{
	// check)
	CGASSERT_ERROR(sizeof(char16_t) == sizeof(wchar_t));

	// check)
	CGASSERT_ERROR(_source.size() <= _size)

	// check)
	THROW_IF(_source.size() > _size, std::length_error("buffser overflow 'encode_string(wchar_t*, std::u32string_view)'"));

	// 1) encoding
	auto length = _source.size();
	auto iter_dest = _dest;
	auto iter_src = _source.begin();
	auto iter_src_end = iter_src + length;
	for (; iter_src != iter_src_end; ++iter_src, ++iter_dest)
	{
		*iter_dest = static_cast<wchar_t>(*iter_src);
	}

	// 2) add null
	*iter_dest = 0;

	return std::wstring_view(_dest, length);
}
inline std::u16string_view						encode_string(char16_t* _dest, std::u32string_view _source, size_t _size = MAX_STRING_LENGTH)
{
	// check)
	CGASSERT_ERROR(sizeof(char16_t) == sizeof(wchar_t));

	// check)
	CGASSERT_ERROR(_source.size() <= _size)

	// check)
	THROW_IF(_source.size() > _size, std::length_error("buffser overflow 'encode_string(char16_t*, std::u32string_view)'"));

	// 1) encoding
	auto length = _source.size();
	auto iter_dest = _dest;
	auto iter_src = _source.begin();
	auto iter_src_end = iter_src + length;
	for (; iter_src != iter_src_end; ++iter_src, ++iter_dest)
	{
		*iter_dest = static_cast<char16_t>(*iter_src);
	}

	// 2) add null
	*iter_dest = 0;

	return std::u16string_view(_dest, length);
}
template<size_t I> inline std::string_view		encode_string(char      (&_dest)[I], std::u32string_view _source)			{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::wstring_view		encode_string(wchar_t   (&_dest)[I], std::u32string_view _source)			{ return encode_string(_dest, _source, I);}
template<size_t I> inline std::u16string_view	encode_string(char16_t  (&_dest)[I], std::u32string_view _source)			{ return encode_string(_dest, _source, I);}


//-----------------------------------------------------------------------------
// converting functions - Strings
//-----------------------------------------------------------------------------
// 1) __from_string
template<class TTYPE> inline TTYPE				__from_string			(std::string_view);
template<class TTYPE> inline TTYPE				__from_string			(std::wstring_view);
template<class TTYPE> inline TTYPE				__from_string			(std::u16string_view);
template<class TTYPE> inline TTYPE				__from_string			(std::u32string_view);
																															
template <> inline char							__from_string<char>		(std::string_view		_source)					{ return static_cast<char>(atoi(_source.data()));}
template <> inline char							__from_string<char>		(std::wstring_view		_source)					{ return static_cast<char>(wcstol(_source.data(), nullptr, 10));}
template <> inline char							__from_string<char>		(std::u16string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
template <> inline char							__from_string<char>		(std::u32string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
																															
template <> inline int8_t						__from_string<int8_t>	(std::string_view		_source)					{ return static_cast<int8_t>(atoi(_source.data()));}
template <> inline int8_t						__from_string<int8_t>	(std::wstring_view		_source)					{ return static_cast<int8_t>(wcstol(_source.data(), nullptr, 10));}
template <> inline int8_t						__from_string<int8_t>	(std::u16string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
template <> inline int8_t						__from_string<int8_t>	(std::u32string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
																															
template <> inline uint8_t						__from_string<uint8_t>	(std::string_view		_source)					{ return static_cast<uint8_t>(std::stoul(_source.data(), nullptr, 10));}
template <> inline uint8_t						__from_string<uint8_t>	(std::wstring_view		_source)					{ return static_cast<uint8_t>(wcstoul(_source.data(), nullptr, 10));}
template <> inline uint8_t						__from_string<uint8_t>	(std::u16string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
template <> inline uint8_t						__from_string<uint8_t>	(std::u32string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
																															
template <> inline int16_t						__from_string<int16_t>	(std::string_view		_source)					{ return static_cast<int16_t>(atoi(_source.data()));}
template <> inline int16_t						__from_string<int16_t>	(std::wstring_view		_source)					{ return static_cast<int16_t>(wcstol(_source.data(), nullptr, 10));}
template <> inline int16_t						__from_string<int16_t>	(std::u16string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
template <> inline int16_t						__from_string<int16_t>	(std::u32string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
																															
template <> inline uint16_t						__from_string<uint16_t>	(std::string_view		_source)					{ return static_cast<uint16_t>(std::stoul(_source.data(), nullptr, 10));}
template <> inline uint16_t						__from_string<uint16_t>	(std::wstring_view		_source)					{ return static_cast<uint16_t>(wcstoul(_source.data(), nullptr, 10));}
template <> inline uint16_t						__from_string<uint16_t>	(std::u16string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
template <> inline uint16_t						__from_string<uint16_t>	(std::u32string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
																															
template <> inline int32_t						__from_string<int32_t>	(std::string_view		_source)					{ return atoi(_source.data());}
template <> inline int32_t						__from_string<int32_t>	(std::wstring_view		_source)					{ return wcstol(_source.data(), nullptr, 10);}
template <> inline int32_t						__from_string<int32_t>	(std::u16string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
template <> inline int32_t						__from_string<int32_t>	(std::u32string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
																															
template <> inline uint32_t						__from_string<uint32_t>	(std::string_view		_source)					{ return std::stoul(_source.data(), nullptr, 10);}
template <> inline uint32_t						__from_string<uint32_t>	(std::wstring_view		_source)					{ return wcstoul(_source.data(), nullptr, 10);}
template <> inline uint32_t						__from_string<uint32_t>	(std::u16string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
template <> inline uint32_t						__from_string<uint32_t>	(std::u32string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
																															
template <> inline int64_t						__from_string<int64_t>	(std::string_view		_source)					{ return atoll(_source.data());}
template <> inline int64_t						__from_string<int64_t>	(std::wstring_view		_source)					{ return wcstoll(_source.data(), nullptr, 10);}
template <> inline int64_t						__from_string<int64_t>	(std::u16string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
template <> inline int64_t						__from_string<int64_t>	(std::u32string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
																															
template <> inline uint64_t						__from_string<uint64_t>	(std::string_view		_source)					{ return strtoull(_source.data(), nullptr, 10);}
template <> inline uint64_t						__from_string<uint64_t>	(std::wstring_view		_source)					{ return wcstoull(_source.data(), nullptr, 10);}
template <> inline uint64_t						__from_string<uint64_t>	(std::u16string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
template <> inline uint64_t						__from_string<uint64_t>	(std::u32string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
																															
template <> inline float						__from_string<float>	(std::string_view		_source)					{ return strtof(_source.data(), nullptr);}
template <> inline float						__from_string<float>	(std::wstring_view		_source)					{ return wcstof(_source.data(), nullptr);}
template <> inline float						__from_string<float>	(std::u16string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
template <> inline float						__from_string<float>	(std::u32string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
																															
template <> inline double						__from_string<double>	(std::string_view		_source)					{ return strtod(_source.data(), nullptr);}
template <> inline double						__from_string<double>	(std::wstring_view		_source)					{ return wcstod(_source.data(), nullptr);}
template <> inline double						__from_string<double>	(std::u16string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
template <> inline double						__from_string<double>	(std::u32string_view	_source)					{ _source; CGASSERT_ERROR(false); return 0;}
																																			  
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
template<class  STRING_T> inline STRING_T		__to_string	(long);
template<class  STRING_T> inline STRING_T		__to_string	(unsigned long);
template<class  STRING_T> inline STRING_T		__to_string	(float);
template<class  STRING_T> inline STRING_T		__to_string	(double);

inline std::string_view							__to_string	(char*     _dest, size_t _size, char _value)					{ _itoa_s(_value, _dest, _size, 10); return std::string_view(_dest);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		char _value)						{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, char _value)					{ _itow_s(_value, _dest, _size, 10); return std::wstring_view(_dest);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		char _value)						{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, char _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u16string_view();}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		char _value)						{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, char _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u32string_view();}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		char _value)						{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (char _value)													{ return std::to_string(_value);}
template<> inline std::basic_string<wchar_t>	__to_string (char _value)													{ return std::to_wstring(_value);}
template<> inline std::basic_string<char16_t>	__to_string (char _value)													{ _value; CGASSERT_ERROR(false); return std::basic_string<char16_t>();}
template<> inline std::basic_string<char32_t>	__to_string (char _value)													{ _value; CGASSERT_ERROR(false); return std::basic_string<char32_t>();}

inline std::string_view							__to_string	(char*     _dest, size_t _size, int8_t _value)					{ _itoa_s(_value, _dest, _size, 10); return std::string_view(_dest);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		int8_t _value)						{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, int8_t _value)					{ _itow_s(_value, _dest, _size, 10); return std::wstring_view(_dest);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		int8_t _value)						{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, int8_t _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u16string_view();}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		int8_t _value)						{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, int8_t _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u32string_view();}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		int8_t _value)						{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (int8_t _value)													{ return std::to_string(_value);}
template<> inline std::basic_string<wchar_t>	__to_string (int8_t _value)													{ return std::to_wstring(_value);}
template<> inline std::basic_string<char16_t>	__to_string (int8_t _value)													{ _value; CGASSERT_ERROR(false); return std::basic_string<char16_t>();}
template<> inline std::basic_string<char32_t>	__to_string (int8_t _value)													{ _value; CGASSERT_ERROR(false); return std::basic_string<char32_t>();}

inline std::string_view							__to_string	(char*     _dest, size_t _size, uint8_t _value)					{ _ultoa_s(_value, _dest, _size, 10); return std::string_view(_dest);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		uint8_t _value)						{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, uint8_t _value)					{ _ultow_s(_value, _dest, _size, 10); return std::wstring_view(_dest);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		uint8_t _value)						{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, uint8_t _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u16string_view();}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		uint8_t _value)						{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, uint8_t _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u32string_view();}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		uint8_t _value)						{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (uint8_t _value)												{ return std::to_string(_value);}
template<> inline std::basic_string<wchar_t>	__to_string (uint8_t _value)												{ return std::to_wstring(_value);}
template<> inline std::basic_string<char16_t>	__to_string (uint8_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char16_t>();}
template<> inline std::basic_string<char32_t>	__to_string (uint8_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char32_t>();}

inline std::string_view							__to_string	(char*     _dest, size_t _size, int16_t _value)					{ _itoa_s(_value, _dest, _size, 10); return std::string_view(_dest);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		int16_t _value)						{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, int16_t _value)					{ _itow_s(_value, _dest, _size, 10); return std::wstring_view(_dest);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		int16_t _value)						{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, int16_t _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u16string_view();}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		int16_t _value)						{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, int16_t _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u32string_view();}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		int16_t _value)						{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (int16_t _value)												{ return std::to_string(_value);}
template<> inline std::basic_string<wchar_t>	__to_string (int16_t _value)												{ return std::to_wstring(_value);}
template<> inline std::basic_string<char16_t>	__to_string (int16_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char16_t>();}
template<> inline std::basic_string<char32_t>	__to_string (int16_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char32_t>();}

inline std::string_view							__to_string	(char*     _dest, size_t _size, uint16_t _value)				{ _ultoa_s(_value, _dest, _size, 10); return std::string_view(_dest);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		uint16_t _value)					{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, uint16_t _value)				{ _ultow_s(_value, _dest, _size, 10); return std::wstring_view(_dest);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		uint16_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, uint16_t _value)				{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u16string_view();}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		uint16_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, uint16_t _value)				{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u32string_view();}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		uint16_t _value)					{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (uint16_t _value)												{ return std::to_string(_value);}
template<> inline std::basic_string<wchar_t>	__to_string (uint16_t _value)												{ return std::to_wstring(_value);}
template<> inline std::basic_string<char16_t>	__to_string (uint16_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char16_t>();}
template<> inline std::basic_string<char32_t>	__to_string (uint16_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char32_t>();}

inline std::string_view							__to_string	(char*     _dest, size_t _size, int32_t _value)					{ _itoa_s(_value, _dest, _size, 10); return std::string_view(_dest);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		int32_t _value)						{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, int32_t _value)					{ _itow_s(_value, _dest, _size, 10); return std::wstring_view(_dest);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		int32_t _value)						{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, int32_t _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u16string_view();}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		int32_t _value)						{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, int32_t _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u32string_view();}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		int32_t _value)						{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (int32_t _value)												{ return std::to_string(_value);}
template<> inline std::basic_string<wchar_t>	__to_string (int32_t _value)												{ return std::to_wstring(_value);}
template<> inline std::basic_string<char16_t>	__to_string (int32_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char16_t>();}
template<> inline std::basic_string<char32_t>	__to_string (int32_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char32_t>();}

inline std::string_view							__to_string	(char*     _dest, size_t _size, uint32_t _value)				{ _ultoa_s(_value, _dest, _size, 10); return std::string_view(_dest);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		uint32_t _value)					{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, uint32_t _value)				{ _ultow_s(_value, _dest, _size, 10); return std::wstring_view(_dest);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		uint32_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, uint32_t _value)				{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u16string_view();}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		uint32_t _value)					{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, uint32_t _value)				{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u32string_view();}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		uint32_t _value)					{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (uint32_t _value)												{ return std::to_string(_value);}
template<> inline std::basic_string<wchar_t>	__to_string (uint32_t _value)												{ return std::to_wstring(_value);}
template<> inline std::basic_string<char16_t>	__to_string (uint32_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char16_t>();}
template<> inline std::basic_string<char32_t>	__to_string (uint32_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char32_t>();}

inline std::string_view							__to_string	(char*     _dest, size_t _size, int64_t _value)					{ _i64toa_s(_value, _dest, _size, 10); return std::string_view(_dest);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],		int64_t _value)						{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, int64_t _value)					{ _i64tow_s(_value, _dest, _size, 10); return std::wstring_view(_dest);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],		int64_t _value)						{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, int64_t _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u16string_view();}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],		int64_t _value)						{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, int64_t _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u32string_view();}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],		int64_t _value)						{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (int64_t _value)												{ return std::to_string(_value);}
template<> inline std::basic_string<wchar_t>	__to_string (int64_t _value)												{ return std::to_wstring(_value);}
template<> inline std::basic_string<char16_t>	__to_string (int64_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char16_t>();}
template<> inline std::basic_string<char32_t>	__to_string (int64_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char32_t>();}

inline std::string_view							__to_string	(char*     _dest, size_t _size, uint64_t _value)				{ _ui64toa_s(_value, _dest, _size, 10); return std::string_view(_dest);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I], uint64_t _value)						{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, uint64_t _value)				{ _ui64tow_s(_value, _dest, _size, 10); return std::wstring_view(_dest);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I], uint64_t _value)						{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, uint64_t _value)				{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u16string_view();}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I], uint64_t _value)						{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, uint64_t _value)				{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u32string_view();}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I], uint64_t _value)						{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (uint64_t _value)												{ return std::to_string(_value);}
template<> inline std::basic_string<wchar_t>	__to_string (uint64_t _value)												{ return std::to_wstring(_value);}
template<> inline std::basic_string<char16_t>	__to_string (uint64_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char16_t>();}
template<> inline std::basic_string<char32_t>	__to_string (uint64_t _value)												{ _value; CGASSERT_ERROR(false); return std::basic_string<char32_t>();}

inline std::string_view							__to_string	(char*     _dest, size_t _size, long _value)					{ return __to_string(_dest, _size, (int32_t)_value);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I], long _value)							{ return __to_string<I>(_dest, (int32_t)_value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, long _value)					{ return __to_string(_dest, _size, (int32_t)_value);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I], long _value)							{ return __to_string<I>(_dest, (int32_t)_value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, long _value)					{ return __to_string(_dest, _size, (int32_t)_value);}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I], long _value)							{ return __to_string<I>(_dest, (int32_t)_value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, long _value)					{ return __to_string(_dest, _size, (int32_t)_value);}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I], long _value)							{ return __to_string<I>(_dest, (int32_t)_value);}
template<> inline std::basic_string<char>		__to_string (long _value)													{ return __to_string<std::basic_string<char>>((int32_t)_value);}
template<> inline std::basic_string<wchar_t>	__to_string (long _value)													{ return __to_string<std::basic_string<wchar_t>>((int32_t)_value);}
template<> inline std::basic_string<char16_t>	__to_string (long _value)													{ return __to_string<std::basic_string<char16_t>>((int32_t)_value);}
template<> inline std::basic_string<char32_t>	__to_string (long _value)													{ return __to_string<std::basic_string<char32_t>>((int32_t)_value);}

inline std::string_view							__to_string	(char*     _dest, size_t _size, unsigned long _value)			{ return __to_string(_dest, _size, (uint32_t)_value);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I], unsigned long _value)					{ return __to_string<I>(_dest, (uint32_t)_value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, unsigned long _value)			{ return __to_string(_dest, _size, (uint32_t)_value);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I], unsigned long _value)					{ return __to_string<I>(_dest, (uint32_t)_value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, unsigned long _value)			{ return __to_string(_dest, _size, (uint32_t)_value);}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I], unsigned long _value)					{ return __to_string<I>(_dest, (uint32_t)_value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, unsigned long _value)			{ return __to_string(_dest, _size, (uint32_t)_value);}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I], unsigned long _value)					{ return __to_string<I>(_dest, (uint32_t)_value);}
template<> inline std::basic_string<char>		__to_string (unsigned long _value)											{ return __to_string<std::basic_string<char>>((uint32_t)_value);}
template<> inline std::basic_string<wchar_t>	__to_string (unsigned long _value)											{ return __to_string<std::basic_string<wchar_t>>((uint32_t)_value);}
template<> inline std::basic_string<char16_t>	__to_string (unsigned long _value)											{ return __to_string<std::basic_string<char16_t>>((uint32_t)_value);}
template<> inline std::basic_string<char32_t>	__to_string (unsigned long _value)											{ return __to_string<std::basic_string<char32_t>>((uint32_t)_value);}

inline std::string_view							__to_string	(char*     _dest, size_t _size, float _value)					{ auto result=snprintf(_dest, _size, "%f", _value); return (result>=0) ? std::string_view(_dest, result) : std::string_view();}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I], float _value)							{ return __to_string(_dest, I, _value);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, float _value)					{ auto result = swprintf(_dest, _size, L"%f", _value); return (result >= 0) ? std::wstring_view(_dest, result) : std::wstring_view();}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I], float _value)							{ return __to_string(_dest, I, _value);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, float _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u16string_view();}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I], float _value)							{ return __to_string(_dest, I, _value);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, float _value)					{ _size; _value; CGASSERT_ERROR(false); _dest[0]=NULL; return std::u32string_view();}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I], float _value)							{ return __to_string(_dest, I, _value);}
template<> inline std::basic_string<char>		__to_string (float _value)													{ return std::to_string(_value);}
template<> inline std::basic_string<wchar_t>	__to_string (float _value)													{ return std::to_wstring(_value);}
template<> inline std::basic_string<char16_t>	__to_string (float _value)													{ _value; CGASSERT_ERROR(false); return std::basic_string<char16_t>();}
template<> inline std::basic_string<char32_t>	__to_string (float _value)													{ _value; CGASSERT_ERROR(false); return std::basic_string<char32_t>();}

inline std::string_view							__to_string	(char*     _dest, size_t _size, double _value, int _digit=28)	{ _gcvt_s(_dest, _size, _value, _digit); return std::string_view(_dest);}
template<size_t I> inline std::string_view		__to_string	(char      (&_dest)[I],	double _value, int _digit=28)			{ _gcvt_s<I>(_dest, _value, _digit); return std::string_view(_dest);}
inline std::wstring_view						__to_string	(wchar_t*  _dest, size_t _size, double _value, int _digit=28)	{ char temp[64]; _gcvt_s(temp, 64, _value, _digit); return encode_string(_dest, temp, _size);}
template<size_t I> inline std::wstring_view		__to_string	(wchar_t   (&_dest)[I],	double _value, int _digit=28)			{ char temp[64]; _gcvt_s(temp, 64, _value, _digit); return encode_string(_dest, temp);}
inline std::u16string_view						__to_string	(char16_t* _dest, size_t _size, double _value, int _digit=28)	{ char temp[64]; _gcvt_s(temp, 64, _value, _digit); return encode_string(_dest, temp, _size);}
template<size_t I> inline std::u16string_view	__to_string	(char16_t  (&_dest)[I],	double _value, int _digit=28)			{ char temp[64]; _gcvt_s(temp, 64, _value, _digit); return encode_string(_dest, temp);}
inline std::u32string_view						__to_string	(char32_t* _dest, size_t _size, double _value, int _digit=28)	{ char temp[64]; _gcvt_s(temp, 64, _value, _digit); return encode_string(_dest, temp, _size);}
template<size_t I> inline std::u32string_view	__to_string	(char32_t  (&_dest)[I],	double _value, int _digit=28)			{ char temp[64]; _gcvt_s(temp, 64, _value, _digit); return encode_string(_dest, temp, 64);}
template<> inline std::basic_string<char>		__to_string (double _value)													{ return std::to_string(_value);}
template<> inline std::basic_string<wchar_t>	__to_string (double _value)													{ return std::to_wstring(_value); }
template<> inline std::basic_string<char16_t>	__to_string (double _value)													{ _value; CGASSERT_ERROR(false); return std::basic_string<char16_t>();}
template<> inline std::basic_string<char32_t>	__to_string (double _value)													{ _value; CGASSERT_ERROR(false); return std::basic_string<char32_t>();}

// 5) Format string
inline std::string			__format(const char* _message)		{	return	std::string(_message);}
template <class... TARGS>
inline std::string			__format(const char* _format, TARGS... _args)
{
	// declare) 
	char message[MAX_STRING_LENGTH]{};

	// 1) Generate trace Message
	_snprintf_s(reinterpret_cast<char*>(message), MAX_STRING_LENGTH, _TRUNCATE, _format, _args...);

	// return) 
	return std::string(message);
}

inline std::wstring			__format(const wchar_t* _message)		{	return	std::wstring(_message);}
template <class... TARGS>
inline std::wstring			__format(const wchar_t* _format, TARGS... _args)
{
	// declare) 
	wchar_t	message[MAX_STRING_LENGTH]{};

	// 1) Generate trace Message
	_snwprintf_s(reinterpret_cast<wchar_t*>(message), MAX_STRING_LENGTH, _TRUNCATE, _format, _args...);

	// return) 
	return std::wstring(message);
}

inline std::u16string		__format(const char16_t* _message)	{	return	std::u16string(_message);}
template <class... TARGS>
inline std::u16string		__format(const char16_t* _format, TARGS... _args)
{
	// declare) 
	char16_t message[MAX_STRING_LENGTH]{};

	// 1) Generate trace Message
	_snwprintf_s(reinterpret_cast<wchar_t*>(message), MAX_STRING_LENGTH, _TRUNCATE, _format, _args...);

	// return) 
	return std::u16string(message);
}

inline std::u32string		__format(const char32_t* _message)	{	return	std::u32string(_message);}
template <class... TARGS>
inline std::u32string		__format(const char32_t* _format, TARGS... _args)
{
	// Error) Dont support char32_t
	CGASSERT_ERROR(false);

	// return) 
	return std::u32string();
}


//-----------------------------------------------------------------------------
//                                                                            
// memory functions
//                                                                            
//                                                                            
//-----------------------------------------------------------------------------
inline void	__zero_memory(void* _dest, size_t _size) noexcept
{
	ZeroMemory(_dest, _size);
}


//void _from_unicode_to_utf8(unsigned int code, char chars[5]) {
//	if (code <= 0x7F) {
//		chars[0] = (code & 0x7F); chars[1] = '\0';
//	}
//	else if (code <= 0x7FF) {
//		// one continuation byte
//		chars[1] = 0x80 | (code & 0x3F); code = (code >> 6);
//		chars[0] = 0xC0 | (code & 0x1F); chars[2] = '\0';
//	}
//	else if (code <= 0xFFFF) {
//		// two continuation bytes
//		chars[2] = 0x80 | (code & 0x3F); code = (code >> 6);
//		chars[1] = 0x80 | (code & 0x3F); code = (code >> 6);
//		chars[0] = 0xE0 | (code & 0xF); chars[3] = '\0';
//	}
//	else if (code <= 0x10FFFF) {
//		// three continuation bytes
//		chars[3] = 0x80 | (code & 0x3F); code = (code >> 6);
//		chars[2] = 0x80 | (code & 0x3F); code = (code >> 6);
//		chars[1] = 0x80 | (code & 0x3F); code = (code >> 6);
//		chars[0] = 0xF0 | (code & 0x7); chars[4] = '\0';
//	}
//	else {
//		// unicode replacement character
//		chars[2] = 0xEF; chars[1] = 0xBF; chars[0] = 0xBD;
//		chars[3] = '\0';
//	}
//}


//void _from_unicode_to_utf8(unsigned int code, char chars[5])
//{
//    if (code <= 0x7F)
//	{
//        chars[0] = (code & 0x7F);
//        chars[1] = '\0';
//    } else if (code > 0x10FFFF) {
//        // unicode replacement character
//        chars[0] = 0xEF;
//        chars[1] = 0xBF;
//        chars[2] = 0xBD;
//        chars[3] = '\0';
//    } else
//	{
//        int count;
//        if (code <= 0x7FF)
//		{
//            // one continuation byte
//            count = 1;
//        } else if (code <= 0xFFFF)
//		{
//            // two continuation bytes
//            count = 2;
//        } else
//		{
//            // three continuation bytes
//            count = 3;
//        }
//        for (int i = 0; i < count; ++i)
//		{
//            chars[count-i] = 0x80 | (code & 0x3F);
//            code >>= 6;
//        }
//        chars[0] = (0x1E << (6-count)) | (code & (0x3F >> count));
//        chars[1+count] = '\0';
//    }
//}
//
//void _from_unicode_to_utf16(unsigned int code, unsigned short chars[2])
//{
//    if ( ((code >= 0x0000) && (code <= 0xD7FF)) ||
//        ((code >= 0xE000) && (code <= 0xFFFF)) )
//    {
//        chars[0] = 0x0000;
//        chars[1] = (unsigned short) code;
//    }
//    else if ((code >= 0xD800) && (code <= 0xDFFF))
//    {
//        // unicode replacement character
//        chars[0] = 0x0000;
//        chars[1] = 0xFFFD;
//    }
//    else
//    {
//        // surrogate pair
//        code -= 0x010000;
//        chars[0] = 0xD800 + (unsigned short)((code >> 10) & 0x3FF);
//        chars[1] = 0xDC00 + (unsigned short)(code & 0x3FF);
//    }
//}

}