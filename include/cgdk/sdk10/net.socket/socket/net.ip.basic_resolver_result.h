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

template<class InternetProtocol>
class basic_resolver_results
{
// defintions)
public:
	using protocol_type		 = InternetProtocol;
	using endpoint_type		 = typename protocol_type::endpoint;
	using value_type		 = basic_resolver_entry<protocol_type>;
	using const_reference	 = const value_type&;
	using reference			 = value_type&;
	using container_type	 = std::vector<value_type>;
	using const_iterator	 = typename container_type::const_iterator;
	using iterator			 = typename container_type::iterator;
	using difference_type	 = ptrdiff_t;
	using size_type			 = size_t;

// constructor/destructor) 21.14.1, constructors
public:
	// [21.15.1] construct / copy / destroy:
			basic_resolver_results() noexcept {}
			basic_resolver_results(const basic_resolver_results& _rhs) noexcept {}
			basic_resolver_results(basic_resolver_results&& _rhs) noexcept : m_vector_result{std::move(_rhs.m_vector_result)}  {}
			template<class T>
			basic_resolver_results(container_type&& _rhs) noexcept : m_vector_result(std::move(_rhs)) {}
			~basic_resolver_results() noexcept {}
// public) 
public:
	// [21.15.3] size:
	[[nodiscard]] size_type		size() const noexcept { return m_vector_result.size(); }
	[[nodiscard]] size_type		max_size() const noexcept { return m_vector_result.max_size(); }
	[[nodiscard]] bool			empty() const noexcept { return m_vector_result.empty(); }

	// [21.15.4] element access:
	[[nodiscard]] const_iterator begin() const noexcept { return m_vector_result.begin(); }
	[[nodiscard]] const_iterator end() const noexcept { return m_vector_result.end(); }
	[[nodiscard]] const_iterator cbegin() const noexcept { return m_vector_result.cbegin(); }
	[[nodiscard]] const_iterator cend() const noexcept { return m_vector_result.cend(); }

	// [21.15.5] swap
			void				swap(basic_resolver_results& that) noexcept {}

	// [21.15.2]
			basic_resolver_results&	operator = (const basic_resolver_results& _rhs) { m_vector_result = _rhs.m_vector_result; return *this; }
			basic_resolver_results&	operator = (basic_resolver_results&& _rhs) noexcept { m_vector_result = std::move(_rhs.m_vector_result); return *this; }
	[[nodiscard]] 				operator endpoint_type() const { return (m_vector_result.empty()==false) ? m_vector_result.front() : endpoint_type(); }

	// [extra]
	[[nodiscard]] const_reference at(size_t _index) const	{ return m_vector_result.at(_index);}
	[[nodiscard]] const_iterator operator [] (size_t _index) { if (_index >= m_vector_result.size()) throw std::out_of_range(); return m_vector_result.at(_index); }

protected:
			container_type		m_vector_result;

public:
			template<class T> friend class basic_resolver;
};

// 21.15.6) basic_resolver_results comparisons:
template<class InternetProtocol>
[[nodiscard]] bool operator==(const basic_resolver_results<InternetProtocol>& _lhs, const basic_resolver_results<InternetProtocol>& _rhs)
{
	return _lhs.m_vector_result = _rhs.m_vector_result;
}

template<class InternetProtocol>
[[nodiscard]] bool operator!=(const basic_resolver_results<InternetProtocol>& _lhs, const basic_resolver_results<InternetProtocol>& _rhs)
{
	return !operator == (_lhs, _rhs);
}


}