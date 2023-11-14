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

template<class TPROTOCOL>
class basic_resolver_entry
{
// definitions) 
public:
	// types:
	using protocol_type = TPROTOCOL;
	using endpoint_type = typename TPROTOCOL::endpoint;

// constructor/destructor) 21.14.1, constructors
public:
			basic_resolver_entry() noexcept {}
			basic_resolver_entry(const endpoint_type& _end_point, std::string_view _host, std::string_view _service) : m_endpoint{ _end_point }, m_hostname{ _host }, m_servicename{ _service } {}

// public) 21.14.2, members
public:
	[[nodiscard]] endpoint_type endpoint() const { return m_endpoint; }
	[[nodiscard]] operator endpoint_type() const { return m_endpoint; }

	template<class TALLOCATOR = allocator<char>>
	[[nodiscard]] std::basic_string<char, std::char_traits<char>, TALLOCATOR>
			host_name(const TALLOCATOR& _a = TALLOCATOR()) const { return std::basic_string<char, std::char_traits<char>, TALLOCATOR>(m_hostname); }

	template<class TALLOCATOR = allocator<char>>
	[[nodiscard]] std::basic_string<char, std::char_traits<char>, TALLOCATOR>
			service_name(const TALLOCATOR& _a = TALLOCATOR()) const { return std::basic_string<char, std::char_traits<char>, TALLOCATOR>(m_servicename); }

public:
			endpoint_type		m_endpoint;
			static_string<64>	m_hostname;		// max 253 bytes
			static_string<64>	m_servicename;	// max 253 bytes
};

// 21.14.3, basic_resolver_entry comparisons:
template<class TPROTOCOL>
[[nodiscard]] bool operator==(const basic_resolver_entry<TPROTOCOL>& _lhs, const basic_resolver_entry<TPROTOCOL>& _rhs)
{
	return _lhs.endpoint() == _rhs.endpoint() && _lhs.host_name() == _rhs.host_name() && _lhs.service_name() == _rhs.service_name();
}
template<class TPROTOCOL>
[[nodiscard]] bool operator!=(const basic_resolver_entry<TPROTOCOL>& _lhs, const basic_resolver_entry<TPROTOCOL>& _rhs)
{
	return !(_lhs == _rhs);
}


}