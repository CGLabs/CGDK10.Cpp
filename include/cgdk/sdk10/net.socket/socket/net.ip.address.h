//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
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

namespace CGDK::net::ip
{

//-----------------------------------------------------------------------------
//
// net::ip::address
//
//
//-----------------------------------------------------------------------------
class address
{
// contructor) 
public:
	constexpr					address() noexcept : type_(ip_type::v4), ipv4_address_(), ipv6_address_() {}
	constexpr					address(const address& _copy) noexcept : type_(_copy.type_), ipv4_address_(_copy.ipv4_address_), ipv6_address_(_copy.ipv6_address_) {}
	constexpr					address(const address_v4& _addr_v4) noexcept : type_(ip_type::v4), ipv4_address_(_addr_v4), ipv6_address_() {}
	constexpr					address(const address_v6& _addr_v6) noexcept : type_(ip_type::v6), ipv4_address_(), ipv6_address_(_addr_v6) {}

// assignment) 
public:
			address&			operator=(const address& _rhs) noexcept { type_ = _rhs.type_; ipv4_address_ = _rhs.ipv4_address_; ipv6_address_ = _rhs.ipv6_address_; return *this; }
			address&			operator=(address&& _rhs) noexcept { type_ = _rhs.type_; ipv4_address_ = _rhs.ipv4_address_; ipv6_address_ = _rhs.ipv6_address_; return *this; }
			address&			operator=(const address_v4& _rhs) noexcept { type_ = ip_type::v4; ipv4_address_ = _rhs; ipv6_address_ = address_v6(); return *this; }
			address&			operator=(address_v4&& _rhs) noexcept { type_ = ip_type::v4; ipv4_address_ = _rhs; ipv6_address_ = address_v6(); return *this; }
			address&			operator=(const address_v6& _rhs) noexcept { type_ = ip_type::v6; ipv4_address_ = address_v4(); ipv6_address_ = _rhs; return *this; }
			address&			operator=(address_v6&& _rhs) noexcept { type_ = ip_type::v6; ipv4_address_ = address_v4(); ipv6_address_ = _rhs; return *this; }

// members) 
public:
	[[nodiscard]] constexpr bool is_v4() const noexcept { return type_ == ip_type::v4; }
	[[nodiscard]] constexpr bool is_v6() const noexcept { return type_ == ip_type::v6; }
	[[nodiscard]] constexpr auto to_v4() const { if (type_ != ip_type::v4) throw std::bad_cast(); return ipv4_address_; }
	[[nodiscard]] constexpr auto to_v6() const { if (type_ != ip_type::v6) throw std::bad_cast(); return ipv6_address_; }
	[[nodiscard]] constexpr bool is_unspecified() const noexcept { return (type_ == ip_type::v4) ? ipv4_address_.is_unspecified() : ((type_ == ip_type::v6) ? ipv6_address_.is_unspecified() : false); }
	[[nodiscard]] constexpr bool is_loopback() const noexcept { return (type_ == ip_type::v4) ? ipv4_address_.is_loopback() : ((type_ == ip_type::v6) ? ipv6_address_.is_loopback() : false);}
	[[nodiscard]] constexpr bool is_multicast() const noexcept { return (type_ == ip_type::v4) ? ipv4_address_.is_multicast() : ((type_ == ip_type::v6) ? ipv6_address_.is_multicast() : false); }

	template<class T = char, class Allocator = allocator<T>>
	[[nodiscard]] std::basic_string<T, std::char_traits<T>, Allocator> 
								to_string(const Allocator& _allocator = Allocator()) const;

public:
			enum class ip_type {v4,v6};
			ip_type				type_;
			address_v4			ipv4_address_;
			address_v6			ipv6_address_;
};

// 21.4.4, address comparisons:
[[nodiscard]] constexpr bool operator==(const address& _lhs, const address& _rhs) noexcept
{
	if (_lhs.type_ != _rhs.type_)
		return false;

	if (_lhs.type_ == address::ip_type::v6)
		return _lhs.ipv6_address_ == _rhs.ipv6_address_;

	return _lhs.ipv4_address_ == _rhs.ipv4_address_;
}
[[nodiscard]] constexpr bool operator!=(const address& _lhs, const address& _rhs) noexcept { return !(_lhs == _rhs); }
[[nodiscard]] constexpr bool operator< (const address& _lhs, const address& _rhs) noexcept
{
	if (_lhs.type_ < _rhs.type_)
		return true;

	if (_lhs.type_ > _rhs.type_)
		return false;

	if (_lhs.type_ == address::ip_type::v6)
		return _lhs.ipv6_address_ < _rhs.ipv6_address_;

	return _lhs.ipv4_address_ < _rhs.ipv4_address_;
}
[[nodiscard]] constexpr bool operator> (const address& _lhs, const address& _rhs) noexcept { return _rhs < _lhs; }
[[nodiscard]] constexpr bool operator<=(const address& _lhs, const address& _rhs) noexcept { return !(_rhs < _lhs); }
[[nodiscard]] constexpr bool operator>=(const address& _lhs, const address& _rhs) noexcept { return !(_lhs < _rhs); }
																			 
// [21.4.5] address creation:
[[nodiscard]] inline address make_address(std::string_view _str, std::error_code& _error_code) noexcept
{
	address a;
	address_v6 v6a = make_address_v6(_str, _error_code);
	if (!_error_code)
		a = v6a;
	else
	{
		std::error_code error_code;
		address_v4 v4a = make_address_v4(_str, error_code);
		if (!error_code)
			a = v4a;
		else
			_error_code = error_code;
	}

	return a;
}
[[nodiscard]] inline address make_address(std::string_view _str) { std::error_code error_code; return make_address(_str, error_code); }

// [21.4.6] address I/O:
template<class CharT, class Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const address& _addr);

template<class T, class Allocator>
std::basic_string<T, std::char_traits<T>, Allocator>
address::to_string(const Allocator& _allocator) const
{
	switch(type_)
	{
	case	ip_type::v4:
			return ipv4_address_.to_string<T, Allocator>(_allocator);

	case	ip_type::v6:
			return ipv6_address_.to_string<T, Allocator>(_allocator);

	default:
			throw throwable::failure(eRESULT::BAD_EXCEPTION);
	}
}


}