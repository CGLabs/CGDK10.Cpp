//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              Factory Classes                              *
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
// Definitions for buffer
//
//-----------------------------------------------------------------------------
namespace CGDK
{
	
[[nodiscard]] std::u8string_view	encode_string (char8_t* _dest, std::string_view _source, size_t _size = MAX_STRING_LENGTH);
[[nodiscard]] std::u8string_view	encode_string (char8_t* _dest, std::wstring_view _source, size_t _size = MAX_STRING_LENGTH);
[[nodiscard]] std::string_view		encode_string_to_utf8 (char* _dest, std::wstring_view _source, size_t _size = MAX_STRING_LENGTH);
[[nodiscard]] std::u8string_view	encode_string (char8_t* _dest, std::u16string_view _source, size_t _size = MAX_STRING_LENGTH);
[[nodiscard]] std::u8string_view	encode_string (char8_t* _dest, std::u32string_view _source, size_t _size = MAX_STRING_LENGTH);

[[nodiscard]] std::string_view		encode_string (char* _dest, std::u8string_view _source, size_t _size = MAX_STRING_LENGTH);
[[nodiscard]] std::wstring_view		encode_string (wchar_t* _dest, std::u8string_view _source, size_t _size = MAX_STRING_LENGTH);
[[nodiscard]] std::wstring_view		encode_string_from_utf8	(wchar_t* _dest, std::string_view _source, size_t _size = MAX_STRING_LENGTH);
[[nodiscard]] std::u16string_view	encode_string (char16_t* _dest, std::u8string_view _source, size_t _size = MAX_STRING_LENGTH);
[[nodiscard]] std::u32string_view	encode_string (char32_t* _dest, std::u8string_view _source, size_t _size = MAX_STRING_LENGTH);

void				__convert_unicode_to_mbcs (shared_buffer& _dest, const_buffer_view _source);
void				__convert_unicode_to_utf8 (shared_buffer& _dest, const_buffer_view _source);
void				__convert_mbcs_to_unicode (shared_buffer& _dest, const_buffer_view _source);
void				__convert_utf8_to_unicode (shared_buffer& _dest, const_buffer_view _source);
void				__convert_mbcs_to_utf8 (shared_buffer& _dest, const_buffer_view _source);
void				__convert_utf8_to_mbcs (shared_buffer& _dest, const_buffer_view _source);

template <class CHAR_T, class CHAR_T_DEST>
std::basic_string<CHAR_T> to_string(std::basic_string_view<CHAR_T_DEST> _source);

template <>
[[nodiscard]] inline std::wstring	to_string<wchar_t, char>(std::string_view _source)			{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(wchar_t));	return std::wstring(encode_string(buf_temp.data<wchar_t>(), _source)); }
template <>																							  
[[nodiscard]] inline std::u8string	to_string<char8_t, char>(std::string_view _source)			{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * 4);				return std::u8string(encode_string(buf_temp.data<char8_t>(), _source)); }
template <>
[[nodiscard]] inline std::u16string	to_string<char16_t, char>(std::string_view _source)			{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(char16_t));	return std::u16string(encode_string(buf_temp.data<char16_t>(), _source)); }
template <>																							  
[[nodiscard]] inline std::u32string	to_string<char32_t, char>(std::string_view _source)			{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(char32_t));	return std::u32string(encode_string(buf_temp.data<char32_t>(), _source)); }

template <>																							  
[[nodiscard]] inline std::string	to_string<char, wchar_t>(std::wstring_view _source)			{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(char));		return std::string(encode_string(buf_temp.data<char>(), _source)); }
template <>																								  
[[nodiscard]] inline std::u8string	to_string<char8_t, wchar_t>(std::wstring_view _source)		{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * 4);				return std::u8string(encode_string(buf_temp.data<char8_t>(), _source)); }
[[nodiscard]] inline std::string	to_utf8_string(std::wstring_view _source)					{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * 4);				return std::string(encode_string_to_utf8(buf_temp.data<char>(), _source, buf_temp.size())); }
template <>
[[nodiscard]] inline std::u16string	to_string<char16_t, wchar_t>(std::wstring_view _source)		{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(char16_t)); return std::u16string(encode_string(buf_temp.data<char16_t>(), _source)); }
template <>																								  
[[nodiscard]] inline std::u32string	to_string<char32_t, wchar_t>(std::wstring_view _source)		{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(char32_t)); return std::u32string(encode_string(buf_temp.data<char32_t>(), _source)); }
template <>																								  
[[nodiscard]] inline std::string	to_string<char, char8_t>(std::u8string_view _source)		{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(char));		return std::string(encode_string(buf_temp.data<char>(), _source)); }
template <>																							  
[[nodiscard]] inline std::wstring	to_string<wchar_t, char8_t>(std::u8string_view _source)		{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(wchar_t));	return std::wstring(encode_string(buf_temp.data<wchar_t>(), _source)); }
[[nodiscard]] inline std::wstring	to_string_from_utf8(std::string_view _source)				{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(wchar_t));	return std::wstring(encode_string(buf_temp.data<wchar_t>(), _source, buf_temp.size())); }

template <>																							  
[[nodiscard]] inline std::u16string	to_string<char16_t, char8_t>(std::u8string_view _source)	{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(char16_t)); return std::u16string(encode_string(buf_temp.data<char16_t>(), _source)); }
template <>																							  
[[nodiscard]] inline std::u32string	to_string<char32_t, char8_t>(std::u8string_view _source)	{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(char32_t)); return std::u32string(encode_string(buf_temp.data<char32_t>(), _source)); }

template <>																							  
[[nodiscard]] inline std::string	to_string<char, char16_t>(std::u16string_view _source)		{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(char));		return std::string(encode_string(buf_temp.data<char>(), _source)); }
template <>																							  
[[nodiscard]] inline std::wstring	to_string<wchar_t, char16_t>(std::u16string_view _source)	{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(wchar_t));	return std::wstring(encode_string(buf_temp.data<wchar_t>(), _source)); }
template <>																							  
[[nodiscard]] inline std::u8string	to_string<char8_t, char16_t>(std::u16string_view _source)	{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * 4);				return std::u8string(encode_string(buf_temp.data<char8_t>(), _source)); }
template <>																							  
[[nodiscard]] inline std::u32string	to_string<char32_t, char16_t>(std::u16string_view _source)	{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(char32_t)); return std::u32string(encode_string(buf_temp.data<char32_t>(), _source)); }

template <>																							  
[[nodiscard]] inline std::string	to_string<char, char32_t>(std::u32string_view _source)		{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(char));		return std::string(encode_string(buf_temp.data<char>(), _source)); }
template <>																							  
[[nodiscard]] inline std::wstring	to_string<wchar_t, char32_t>(std::u32string_view _source)	{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(wchar_t));	return std::wstring(encode_string(buf_temp.data<wchar_t>(), _source)); }
template <>																							  
[[nodiscard]] inline std::u8string	to_string<char8_t, char32_t>(std::u32string_view _source)	{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * 4);				return std::u8string(encode_string(buf_temp.data<char8_t>(), _source)); }
template <>																							  
[[nodiscard]] inline std::u16string	to_string<char16_t, char32_t>(std::u32string_view _source)	{ auto buf_temp = alloc_shared_buffer((_source.size() + 1) * sizeof(char16_t)); return std::u16string(encode_string(buf_temp.data<char16_t>(), _source)); }


}