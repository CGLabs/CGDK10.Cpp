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
// CGWeb::CRequest
//
//
// ----------------------------------------------------------------------------
class net::http_request :
// inherited classes) 
	virtual public				Ihttp_request
{
// public) 
public:
	// 1) set request (url)
			void				set_request(
											std::string_view _url,
											eHTTP_METHOD _type = eHTTP_METHOD::DEFAULT_
										);

	// 2) set request (shared_buffer)
			void				set_request(
											const net::sockaddr&			_address_host,
											const shared_buffer&			_buffer
										);

	// 3) set request (parameters)
			void				set_request(
											eHTTP_METHOD					_method_type,
											const std::string_view			_host_name,
											uint16_t						_host_port,
											const std::string_view			_version,
											const std::string_view			_object,
											const std::string_view			_referer,
											const std::vector<std::string_view>& _vector_header,
											const buffer_view				_buffer_optinal,
											const std::vector<std::string_view>& _vector_accept,
											bool							_flag
										);

	// 4) Event
			auto&				get_condition_variable() noexcept { return this->m_cv_complete;}
			template <class TLOCK>								  
			void				wait(typename _unique_lock<TLOCK>::type& _cs) { this->m_cv_complete.wait(_cs); return; }
			void				wait() { std::unique_lock<lockable<>> cs(this->m_lockable_wait); this->m_cv_complete.wait(cs); return; }
// framework)
public:
	virtual	result_code			process_request();
	virtual	int					process_response(sMESSAGE& _msg);

			std::condition_variable_any m_cv_complete;
			lockable<>			m_lockable_wait;
};


}