//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
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
/**

  class basic_string_param

*/
//-----------------------------------------------------------------------------
template <class T = char>
class basic_string_param
{
public:
			basic_string_param() {}
			basic_string_param(const std::basic_string<T>& _string) : buf_string{ { _string.data(), _string.size()} } {}
			basic_string_param(std::basic_string<T>&& _string) : buf_string{ { _string.data(), _string.size()} } {}
			template<class X>
			basic_string_param(const std::basic_string<X>& _string CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) : buf_string() { buf_string = _mem_alloc((_string.size() + 1) * sizeof(T) CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING); auto result = encode_string(const_cast<T*>(buf_string.data()), _string, _string.size() + 1); buf_string.set_size(result.size()); }
			template<class X>
			basic_string_param(std::basic_string<X>&& _string CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) : buf_string() { buf_string = _mem_alloc((_string.size() + 1) * sizeof(T) CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING); auto result = encode_string(const_cast<T*>(buf_string.data()), _string, _string.size() + 1); buf_string.set_size(result.size()); }

			basic_string_param(const std::basic_string_view<T>& _string) : buf_string{{ _string.data(), _string.size()}} {}
			basic_string_param(std::basic_string_view<T>&& _string) : buf_string{ { _string.data(), _string.size()} } {}
			template<class X>
			basic_string_param(const std::basic_string_view<X>& _string CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) : buf_string() { buf_string = _mem_alloc((_string.size() + 1) * sizeof(T) CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING); auto result = encode_string(const_cast<T*>(buf_string.data()), _string, _string.size() + 1); buf_string.set_size(result.size()); }
			template<class X>
			basic_string_param(std::basic_string_view<X>&& _string CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) : buf_string() { buf_string = _mem_alloc((_string.size() + 1) * sizeof(T) CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING); auto result = encode_string(const_cast<T*>(buf_string.data()), _string, _string.size() + 1); buf_string.set_size(result.size()); }

			template <std::size_t N>
			basic_string_param(const basic_static_string<T,N>& _string) : buf_string{ { _string.c_str(), _string.size()} } {}
			template <std::size_t N>
			basic_string_param(basic_static_string<T, N>&& _string) : buf_string{ { _string.c_str(), _string.size()} } {}
			template<class X, std::size_t N>
			basic_string_param(const basic_static_string<X, N>& _string CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) : buf_string() { buf_string = _mem_alloc((_string.size() + 1) * sizeof(T) CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING); auto result = encode_string(const_cast<T*>(buf_string.c_str()), _string, _string.size() + 1); buf_string.set_size(result.size()); }
			template<class X, std::size_t N>
			basic_string_param(basic_static_string<X, N>&& _string CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) : buf_string() { buf_string = _mem_alloc((_string.size() + 1) * sizeof(T) CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING); auto result = encode_string(const_cast<T*>(buf_string.c_str()), _string, _string.size() + 1); buf_string.set_size(result.size()); }

			basic_string_param(const T* _string) : buf_string()
			{
				if (_string == nullptr) return;
				std::basic_string_view<T> temp_string(_string);
				buf_string ^= _buffer_view<const T>{ temp_string.data(), temp_string.size() };
			}
			template<class X>
			basic_string_param(const X* _string CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT) : buf_string()
			{
				if (_string == nullptr) return;
				std::basic_string_view<X> temp_string(_string);
				buf_string = _mem_alloc((temp_string.size() + 1) * sizeof(T) CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
				buf_string.set_size(temp_string.size());
				auto result = encode_string(const_cast<T*>(buf_string.data()), temp_string, temp_string.size() + 1);
			}

public:
	[[nodiscard]] auto			empty() const noexcept { return buf_string.empty(); }
	[[nodiscard]] auto			exist() const noexcept { return !empty(); }
	[[nodiscard]] auto			data() const noexcept { return buf_string.template data<T>(); }
			template <class ELEMENT_T>
	[[nodiscard]] constexpr auto data() const noexcept { return buf_string.template data<ELEMENT_T>(); }
	[[nodiscard]] auto			size() const noexcept { return buf_string.size(); }
			template <class CAST_SIZE_T>
	[[nodiscard]] constexpr auto size() const noexcept { return buf_string.template size<CAST_SIZE_T>(); }

			operator std::basic_string_view<T>() const noexcept { return std::basic_string_view<T>{ buf_string.template data<T>(), buf_string.size() }; }
public:
			_shared_buffer<_buffer_view<const T>> buf_string;
};

template <class T> [[nodiscard]] bool operator == (basic_string_param<T> _lhs, std::string_view _rhs) { return static_cast<std::string_view>(_lhs.buf_string) == _rhs; }
template <class T> [[nodiscard]] bool operator >  (basic_string_param<T> _lhs, std::string_view _rhs) { return static_cast<std::string_view>(_lhs.buf_string) > _rhs; }
template <class T> [[nodiscard]] bool operator <  (basic_string_param<T> _lhs, std::string_view _rhs) { return  (_rhs >  _lhs); }
template <class T> [[nodiscard]] bool operator != (basic_string_param<T> _lhs, std::string_view _rhs) { return !(_lhs == _rhs); }
template <class T> [[nodiscard]] bool operator >= (basic_string_param<T> _lhs, std::string_view _rhs) { return !(_rhs >  _lhs); }
template <class T> [[nodiscard]] bool operator <= (basic_string_param<T> _lhs, std::string_view _rhs) { return !(_lhs >  _rhs); }

template <class T> [[nodiscard]] bool operator == (std::string_view _lhs, basic_string_param<T> _rhs) { return _rhs == _lhs; }
template <class T> [[nodiscard]] bool operator >  (std::string_view _lhs, basic_string_param<T> _rhs) { return _rhs <  _lhs; }
template <class T> [[nodiscard]] bool operator <  (std::string_view _lhs, basic_string_param<T> _rhs) { return _rhs >  _lhs; }
template <class T> [[nodiscard]] bool operator != (std::string_view _lhs, basic_string_param<T> _rhs) { return _rhs != _lhs; }
template <class T> [[nodiscard]] bool operator >= (std::string_view _lhs, basic_string_param<T> _rhs) { return _rhs <= _lhs; }
template <class T> [[nodiscard]] bool operator <= (std::string_view _lhs, basic_string_param<T> _rhs) { return _rhs >= _lhs; }

using string_param = basic_string_param<char>;
using wstring_param = basic_string_param<wchar_t>;
using u8string_param = basic_string_param<char8_t>;
using u16string_param = basic_string_param<char16_t>;
using u32string_param = basic_string_param<char32_t>;

}