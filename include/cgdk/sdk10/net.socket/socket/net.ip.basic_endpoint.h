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

namespace CGDK
{
namespace net
{
namespace ip
{


template <typename TPROTOCOL>
class basic_endpoint
{
public:
		using protocol_type	 = TPROTOCOL;
		using data_type		 = net::sockaddr;
		using my_type		 = basic_endpoint<TPROTOCOL>;

public:
		constexpr basic_endpoint() noexcept : data_{} {}
		constexpr basic_endpoint( const TPROTOCOL& _protocol, unsigned short _port ) noexcept : data_{ _protocol, _port } {}
		constexpr basic_endpoint( const ip::address& _addr, unsigned short _port) noexcept : data_{ _addr, _port } {}
		constexpr basic_endpoint( const basic_endpoint& _copy ) noexcept : data_( _copy.data_ ) {}
		constexpr basic_endpoint( basic_endpoint&& _move ) noexcept : data_( _move.data_ ) {}
		constexpr basic_endpoint( const net::sockaddr& _sockaddr ) noexcept : data_(_sockaddr ) {}
		constexpr basic_endpoint( net::sockaddr&& _sockaddr ) noexcept : data_(_sockaddr ) {}

public:
		basic_endpoint&			operator = (const basic_endpoint& _rhs) noexcept { data_ = _rhs.data_; return *this; }
		basic_endpoint&			operator = (basic_endpoint&& _rhs) noexcept { data_ = _rhs.data_; return *this; }
		basic_endpoint&			operator = (const net::sockaddr& _rhs) { data_ = _rhs; return *this; }
		basic_endpoint&			operator = (net::sockaddr&& _rhs) { return operator=(_rhs); }

		[[nodiscard]] constexpr protocol_type protocol() const noexcept { return is_v4() ? TPROTOCOL::v4() : TPROTOCOL::v6(); }
		[[nodiscard]] data_type& data() noexcept { return data_; }
		[[nodiscard]] const data_type& data() const noexcept { return data_; }
		[[nodiscard]] constexpr std::size_t	size() const noexcept { return data_.length; }
		template<class T>
		[[nodiscard]] constexpr T size() const noexcept { return static_cast<T>(data_.length); }
		void					resize(std::size_t _new_size) { if (_new_size > sizeof(net::sockaddr)) throw std::invalid_argument(); data_.length = _new_size; }
		[[nodiscard]] constexpr auto capacity() const noexcept { return sizeof(data_); }
		[[nodiscard]] constexpr auto port() const noexcept { return data_.port(); }
		void					port(unsigned short _port) noexcept { data_.port(_port); }
		[[nodiscard]] constexpr ip::address	address() const { if(data_.is_v4()) return data_.to_address_v4(); else if(data_.is_v6()) return data_.to_address_v6(); else return ip::address(); }
		constexpr void			address(const ip::address& _addr) noexcept { data_ = _addr; }
		[[nodiscard]] constexpr bool is_v4() const noexcept { return data_.is_v4(); }
		[[nodiscard]] constexpr bool is_v6() const noexcept { return data_.is_v6(); }
		[[nodiscard]] constexpr sockaddr_in	v4() const noexcept { return data_.to_v4(); }
		[[nodiscard]] constexpr sockaddr_in6 v6() const noexcept { return data_.to_v6(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return data_.empty();}
		[[nodiscard]] constexpr bool exist() const noexcept { return data_.exist();}
		void					clear() noexcept { data_.clear();}

public:
		template <typename TPROTOCOL_NEST>
		friend bool operator <  (const basic_endpoint<TPROTOCOL_NEST>& _lhs, const basic_endpoint<TPROTOCOL_NEST>& _rhs) noexcept;
		template <typename TPROTOCOL_NEST>
		friend bool operator >  (const basic_endpoint<TPROTOCOL_NEST>& _lhs, const basic_endpoint<TPROTOCOL_NEST>& _rhs) noexcept;

private:
		net::sockaddr			data_;
};

template <typename TPROTOCOL>
[[nodiscard]] bool operator == (const basic_endpoint<TPROTOCOL>& _lhs, const basic_endpoint<TPROTOCOL>& _rhs) noexcept { return _lhs == _rhs; }
template <typename TPROTOCOL>
[[nodiscard]] bool operator != (const basic_endpoint<TPROTOCOL>& _lhs, const basic_endpoint<TPROTOCOL>& _rhs) noexcept { return !(_lhs == _rhs); }
template <typename TPROTOCOL>
[[nodiscard]] bool operator <  (const basic_endpoint<TPROTOCOL>& _lhs, const basic_endpoint<TPROTOCOL>& _rhs) noexcept { return _lhs.data_ < _rhs.data_; }
template <typename TPROTOCOL>
[[nodiscard]] bool operator >  (const basic_endpoint<TPROTOCOL>& _lhs, const basic_endpoint<TPROTOCOL>& _rhs) noexcept { return _rhs.data_ < _lhs.data_; }
template <typename TPROTOCOL>
[[nodiscard]] bool operator <= (const basic_endpoint<TPROTOCOL>& _lhs, const basic_endpoint<TPROTOCOL>& _rhs) noexcept { return !(_rhs < _lhs); }
template <typename TPROTOCOL>
[[nodiscard]] bool operator >= (const basic_endpoint<TPROTOCOL>& _lhs, const basic_endpoint<TPROTOCOL>& _rhs) noexcept { return !(_lhs < _rhs); }

}
}

template <class TPROTOCOL>
constexpr net::sockaddr::sockaddr(const net::ip::basic_endpoint<TPROTOCOL>& _end_point)
{
	if (_end_point.is_v4())
	{
		u_v4.sin_family = AF_INET;
		u_v4.sin_port = _end_point.v4().sin_port;
		u_v4.address_.S_addr = _end_point.v4().sin_addr.s_addr;
		*(uint64_t*)u_v4.zero = 0;
		length = sizeof(sockaddr_in);
	}
	else if (_end_point.is_v6())
	{
		u_v6.sin_family = AF_INET6;
		u_v6.sin_port = _end_point.v6().sin6_port;
		u_v6.sin6_flowinfo = _end_point.v6().sin6_flowinfo;
		u_v6.address_.sin6_addr = _end_point.v6().sin6_addr;
		u_v6.address_.sin6_scope_id = _end_point.v6().sin6_scope_id;
		length = sizeof(sockaddr_in6);
	}
	else if(_end_point.empty())
	{
		clear();
	}
	else
	{
		throw std::bad_cast();
	}
}

}