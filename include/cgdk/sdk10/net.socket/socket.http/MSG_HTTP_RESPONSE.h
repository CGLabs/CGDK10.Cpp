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
// sMESSAGE_HTTP_RESPONSE
//
//
// ----------------------------------------------------------------------------
struct sMESSAGE_HTTP_RESPONSE : public sMESSAGE_HTTP
{
public:
			sMESSAGE_HTTP_RESPONSE() : sMESSAGE_HTTP(eMESSAGE::SYSTEM::HTTP_RESPONSE) {}
			sMESSAGE_HTTP_RESPONSE(const shared_buffer& _buffer) : sMESSAGE_HTTP(eMESSAGE::SYSTEM::HTTP_RESPONSE, _buffer) {}

public:
	// 2) request line - path
			std::string_view	path;

	// 3) status (result)
			eHTTP_STATUS_CODE	status_code = eHTTP_STATUS_CODE::NOT_DEFINED_;
			std::string_view	status_message;
public:
	// 4) ...
			void				reset() noexcept { sMESSAGE_HTTP::reset(); path= std::string_view(); status_code = eHTTP_STATUS_CODE::NOT_DEFINED_; status_message = std::string_view();  }

	// 5) result
			bool				is_success() const noexcept { return is_completed == true && status_code == eHTTP_STATUS_CODE::OK_; }
			bool				is_failed() const noexcept { return !is_success(); }
								operator bool() const noexcept { return is_success(); }
};


// 2) shared_buffer functions
buffer_view	prepend_MESSAGE_HTTP(buffer& _buffer, const sMESSAGE_HTTP_RESPONSE& _data);
buffer_view	append_MESSAGE_HTTP(buffer& _buffer, const sMESSAGE_HTTP_RESPONSE& _data);
std::size_t get_size_of_MESSAGE_HTTP(const sMESSAGE_HTTP_RESPONSE& _data);

// 3) definiions shared_buffer operation 
template<class B>
class serializer_prepend<B, sMESSAGE_HTTP_RESPONSE, void>
{
public: using type = buffer_view;
	template<class S> static type _do_prepend(S& _s, const sMESSAGE_HTTP_RESPONSE& _data) { return prepend_MESSAGE_HTTP(_s, _data); }
};


template<class B>
class serializer_append<B, sMESSAGE_HTTP_RESPONSE, void>
{
public: using type = buffer_view;
	template<class S> static type _do_append(S& _s, const sMESSAGE_HTTP_RESPONSE& _data) { return append_MESSAGE_HTTP(_s, _data); }
	template<class S> static type _do_append(S& _s, sMESSAGE_HTTP_RESPONSE&& _data) { return append_MESSAGE_HTTP(_s, _data); }
};

template<>
class serializer_size_of<sMESSAGE_HTTP_RESPONSE, void>
{	public:
			static std::size_t  _get_append_size(const sMESSAGE_HTTP_RESPONSE& _data) { return get_size_of_MESSAGE_HTTP(_data); }
			template<class S> 
			static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) { CGDK_ASSERT(false); return 0; }
};


}