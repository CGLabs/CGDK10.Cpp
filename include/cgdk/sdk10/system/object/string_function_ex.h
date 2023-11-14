//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            string function ex                             *
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
// string function ex
//
//-----------------------------------------------------------------------------
namespace CGDK
{
	
// - Convert String(2) - converting object
template<class TDEST, class TSOURCE> [[nodiscard]] inline std::basic_string<TDEST> encode_string(std::basic_string_view<TSOURCE> _source)
{
	// 1) 할당할 버퍼
	const std::size_t count_buffer = _source.size() * 4;

	// 2) 충분한 버퍼를 할당한다.
	auto buf = alloc_shared_buffer(count_buffer * sizeof(TDEST));

	// 3) convert한다.
	return std::basic_string<TDEST>(encode_string(buf.data<TDEST>(), _source, count_buffer));
}


// to_string with byte (1000)
template<class T, class S> std::basic_string_view<T> to_string_scaled(T* _buffer, size_t _size, S _value);
template<class T, class S> [[nodiscard]] std::basic_string<T> to_string_scaled(S _value);

template<> std::string_view to_string_scaled<char, int32_t>(char* _buffer, size_t _size, int32_t  _value);
template<> std::string_view to_string_scaled<char, uint32_t>(char* _buffer, size_t _size, uint32_t _value);
template<> std::string_view to_string_scaled<char, int64_t>(char* _buffer, size_t _size, int64_t  _value);
template<> std::string_view to_string_scaled<char, uint64_t>(char* _buffer, size_t _size, uint64_t _value);
template<> std::string_view to_string_scaled<char, float>(char* _buffer, size_t _size, float    _value);

template<> std::wstring_view to_string_scaled<wchar_t, int32_t>(wchar_t* _buffer, size_t _size, int32_t  _value);
template<> std::wstring_view to_string_scaled<wchar_t, uint32_t>(wchar_t* _buffer, size_t _size, uint32_t _value);
template<> std::wstring_view to_string_scaled<wchar_t, int64_t>(wchar_t* _buffer, size_t _size, int64_t  _value);
template<> std::wstring_view to_string_scaled<wchar_t, uint64_t>(wchar_t* _buffer, size_t _size, uint64_t _value);
template<> std::wstring_view to_string_scaled<wchar_t, float>(wchar_t* _buffer, size_t _size, float    _value);

template<> [[nodiscard]] std::string to_string_scaled<char, int32_t>(int32_t  _value);
template<> [[nodiscard]] std::string to_string_scaled<char, uint32_t>(uint32_t _value);
template<> [[nodiscard]] std::string to_string_scaled<char, int64_t>(int64_t  _value);
template<> [[nodiscard]] std::string to_string_scaled<char, uint64_t>(uint64_t _value);
template<> [[nodiscard]] std::string to_string_scaled<char, float>(float _value);

template<> [[nodiscard]] std::wstring to_string_scaled<wchar_t, int32_t>(int32_t  _value);
template<> [[nodiscard]] std::wstring to_string_scaled<wchar_t, uint32_t>(uint32_t _value);
template<> [[nodiscard]] std::wstring to_string_scaled<wchar_t, int64_t>(int64_t  _value);
template<> [[nodiscard]] std::wstring to_string_scaled<wchar_t, uint64_t>(uint64_t _value);
template<> [[nodiscard]] std::wstring to_string_scaled<wchar_t, float>(float _value);

// to_string with byte scaled (1024)
template<class T, class S> std::basic_string_view<T> to_string_scaled_byte(T* _buffer, size_t _size, S _value);
template<class T, class S> [[nodiscard]] std::basic_string<T> to_string_scaled_byte(S _value);

template<> std::string_view to_string_scaled_byte<char, int32_t>(char* _buffer, size_t _size, int32_t  _value);
template<> std::string_view to_string_scaled_byte<char, uint32_t>(char* _buffer, size_t _size, uint32_t _value);
template<> std::string_view to_string_scaled_byte<char, int64_t>(char* _buffer, size_t _size, int64_t  _value);
template<> std::string_view to_string_scaled_byte<char, uint64_t>(char* _buffer, size_t _size, uint64_t _value);
template<> std::string_view to_string_scaled_byte<char, float>(char* _buffer, size_t _size, float _value);

template<> std::wstring_view to_string_scaled_byte<wchar_t, int32_t>(wchar_t* _buffer, size_t _size, int32_t  _value);
template<> std::wstring_view to_string_scaled_byte<wchar_t, uint32_t>(wchar_t* _buffer, size_t _size, uint32_t _value);
template<> std::wstring_view to_string_scaled_byte<wchar_t, int64_t>(wchar_t* _buffer, size_t _size, int64_t  _value);
template<> std::wstring_view to_string_scaled_byte<wchar_t, uint64_t>(wchar_t* _buffer, size_t _size, uint64_t _value);
template<> std::wstring_view to_string_scaled_byte<wchar_t, float>(wchar_t* _buffer, size_t _size, float _value);

template<> [[nodiscard]] std::string to_string_scaled_byte<char, int32_t>(int32_t  _value);
template<> [[nodiscard]] std::string to_string_scaled_byte<char, uint32_t>(uint32_t _value);
template<> [[nodiscard]] std::string to_string_scaled_byte<char, int64_t>(int64_t  _value);
template<> [[nodiscard]] std::string to_string_scaled_byte<char, uint64_t>(uint64_t _value);
template<> [[nodiscard]] std::string to_string_scaled_byte<char, float>(float _value);

template<> [[nodiscard]] std::wstring to_string_scaled_byte<wchar_t, int32_t>(int32_t  _value);
template<> [[nodiscard]] std::wstring to_string_scaled_byte<wchar_t, uint32_t>(uint32_t _value);
template<> [[nodiscard]] std::wstring to_string_scaled_byte<wchar_t, int64_t>(int64_t  _value);
template<> [[nodiscard]] std::wstring to_string_scaled_byte<wchar_t, uint64_t>(uint64_t _value);
template<> [[nodiscard]] std::wstring to_string_scaled_byte<wchar_t, float>(float _value);

template<class TTCHAR, size_t I>
inline void						__to_lower(TTCHAR  (&_dest)[I], const TTCHAR* _source)
{
	TTCHAR* iter = _dest;
	const TTCHAR* end = _dest+I-1;

	for(;iter<end; ++_source, ++iter)
	{
		if(*_source == 0)
			break;

		*iter = static_cast<TTCHAR>(::tolower(*_source));
	}
	*iter = 0;

	// check)
	CGASSERT_ERROR(iter != end);
}
template<class TTCHAR>
[[nodiscard]] inline std::basic_string<TTCHAR>	__to_lower(std::basic_string_view<TTCHAR> _source)
{
	// declare) 
	std::basic_string<TTCHAR> str_dest;

	str_dest.resize(_source.size());

	auto iter_dest = str_dest.begin();
	auto iter_source = _source.begin();
	auto iter_source_end = _source.end();

	for (; iter_source != iter_source_end; ++iter_source, ++iter_dest)
	{
		*iter_dest = static_cast<TTCHAR>(::tolower(*iter_source));
	}

	// check) 
	CGASSERT_ERROR(iter_dest == str_dest.end());

	// return)
	return str_dest;
}


}