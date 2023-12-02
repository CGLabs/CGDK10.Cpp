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

   result_code
 
*///-----------------------------------------------------------------------------
template <class T> struct is_result_code_enum : std::false_type {};

class result_code
{
public:
	using type = int32_t;

public:
	constexpr result_code() noexcept {}
	constexpr result_code(type _value) noexcept : m_result_code(_value) {}
	template <class ENUM_T, std::enable_if_t<is_result_code_enum<ENUM_T>::value, int> = 0>
	constexpr result_code(ENUM_T _enum_code) noexcept : m_result_code(static_cast<type>(_enum_code)) {}

public:
	constexpr void				assign(type _value) noexcept { m_result_code = _value; }
	constexpr void				clear() noexcept { m_result_code = 0; }
	[[nodiscard]] constexpr type value() const noexcept { return m_result_code; }
	template<class ENUM_T>
	[[nodiscard]] constexpr ENUM_T value() const noexcept { return static_cast<ENUM_T>(m_result_code); }

	template <class ENUM_T, std::enable_if_t<is_result_code_enum<ENUM_T>::value, int> = 0>
	constexpr result_code&		operator = (ENUM_T _enum_code) noexcept	{ m_result_code = static_cast<uint64_t>(_enum_code);;return *this; }

	[[nodiscard]] constexpr explicit operator bool() const noexcept { return value() != 0; }
	[[nodiscard]] constexpr		operator type() const noexcept { return m_result_code; }
	template <class ENUM_T, std::enable_if_t<is_result_code_enum<ENUM_T>::value, int> = 0>
	[[nodiscard]] constexpr		operator const ENUM_T() const noexcept { return static_cast<const ENUM_T>(m_result_code); }

private:
			type				m_result_code = 0;
};

[[nodiscard]] inline bool			operator == (const result_code& _lhs, const result_code& _rhs) noexcept { return _lhs.value() == _rhs.value(); }
[[nodiscard]] inline bool			operator != (const result_code& _lhs, const result_code& _rhs) noexcept { return !(_lhs == _rhs); }
[[nodiscard]] inline bool			operator <  (const result_code& _lhs, const result_code& _rhs) noexcept { return _lhs.value() < _rhs.value(); }
[[nodiscard]] inline bool			operator >  (const result_code& _lhs, const result_code& _rhs) noexcept { return _rhs < _lhs; }
[[nodiscard]] inline bool			operator <= (const result_code& _lhs, const result_code& _rhs) noexcept { return !(_lhs > _rhs); }
[[nodiscard]] inline bool			operator >= (const result_code& _lhs, const result_code& _rhs) noexcept { return !(_lhs < _rhs); }

[[nodiscard]] inline result_code	operator |  (const result_code& _lhs, const result_code& _rhs) noexcept { return result_code(_lhs.value() | _rhs.value()); }
[[nodiscard]] inline result_code	operator &  (const result_code& _lhs, const result_code& _rhs) noexcept { return result_code(_lhs.value() & _rhs.value()); }
[[nodiscard]] inline result_code	operator ^  (const result_code& _lhs, const result_code& _rhs) noexcept { return result_code(_lhs.value() ^ _rhs.value()); }


}


