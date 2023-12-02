//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        network socket http classes                        *
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
// Ihttp_request
//
//
// ----------------------------------------------------------------------------
class net::Ihttp_request :
// inherited classes) 
	virtual public				Ireferenceable
{
// public)
public:
	// definitions) 
			using RESPONSE_FUNCTION = std::function<void(sMESSAGE_HTTP_RESPONSE&)>;

	// 1) Request
	virtual	result_code			request() { return process_request();}
			
	// 2) process functioin
			void				set_process_function(const RESPONSE_FUNCTION& _function) noexcept { m_function_on_process = _function; }
			void				set_process_function(RESPONSE_FUNCTION&& _function) noexcept { m_function_on_process = std::move(_function); }

	// 3) response functioin
			void				set_request(const ip::tcp::endpoint& _address) noexcept { m_address_host = _address; }
			void				set_request(const shared_buffer& _buffer) noexcept { m_buffer_request = _buffer; }
			void				set_function(const RESPONSE_FUNCTION& _function) noexcept { m_function_on_response = _function; }
			void				set_function(RESPONSE_FUNCTION&& _function) noexcept { m_function_on_response = std::move(_function); }

	// 4) Get...
			auto				get_request_buffer() const noexcept { return m_buffer_request; }
			auto				get_response_buffer() const noexcept { return m_buffer_response; }
			auto&				get_response_function() const noexcept { return m_function_on_response; }

// framework)
public:
	virtual	result_code			process_request() PURE;
	virtual	int					process_response(sMESSAGE& _msg) PURE;

public:
			eHTTP_METHOD		m_http_method = eHTTP_METHOD::NONE_;
			ip::tcp::endpoint	m_address_host;
			shared_buffer		m_buffer_request;
			shared_buffer		m_buffer_response;
			RESPONSE_FUNCTION	m_function_on_process;
			RESPONSE_FUNCTION	m_function_on_response;
			static_string<24>	m_keys;
			bool				m_is_crypt = false;
};



}