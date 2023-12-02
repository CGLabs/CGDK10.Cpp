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
// sMESSAGE_HTTP
//
//
// ----------------------------------------------------------------------------
struct sMESSAGE_HTTP : public sMESSAGE_NETWORK
{
public:
			sMESSAGE_HTTP() : sMESSAGE_NETWORK(eMESSAGE::SYSTEM::HTTP_RESPONSE) {}
			sMESSAGE_HTTP(uint32_t _message) : sMESSAGE_NETWORK(_message) {}
			sMESSAGE_HTTP(uint32_t _message, const shared_buffer& _buffer) : sMESSAGE_NETWORK(_message, _buffer) {}

public:
	// 1) header
			shared_buffer		buf_head;

			eHTTP_PROTOCOL		protocol = eHTTP_PROTOCOL::NOT_DEFINED_; // HTTP, WEBSOCKT, ...
			int32_t				version = 0;							 // 1.1, 2.0, ...
			eHTTP_METHOD		method = eHTTP_METHOD::NONE_;			 // GET, POST, ...
			char				websocket_key[64] {};
			std::vector<sHTTP_HEADER_ITEM> headers; // MAX:64

	// 2) status
			bool				is_completed = false;
			bool				is_chunked = false;

	// 3) context info
			std::string_view	content_type;
			std::vector<shared_buffer> contents;
			std::size_t			content_length_now = 0;
			bool				content_completed = false;

public:
	// 4) get_headers
			std::string_view	get_header(const std::string_view _str_parameter) const;
			void				reset() noexcept { buf_head.clear(); protocol = eHTTP_PROTOCOL::NOT_DEFINED_; version = 0; method = eHTTP_METHOD::NONE_; websocket_key[0] = 0; headers.clear(); is_completed = false; is_chunked = false; content_type = std::string_view(); contents.clear(); content_length_now = 0; content_completed = false; }

			int16_t				version_major() const noexcept { return (version >> 16); }
			int16_t				version_minor() const noexcept { return (version & 0xffff); }
};

inline bool __icompare(std::string_view _rhs, std::string_view _lhs)
{
	if (_rhs.size() != _lhs.size())
		return	false;

	auto iter_rhs	  = _rhs.begin();
	auto iter_rhs_end = _rhs.end();
	auto iter_lhs	  = _lhs.begin();

	while(iter_rhs != iter_rhs_end)
	{
		auto a = *iter_rhs++;
		auto b = *iter_lhs++;

		if (a >= 'A' && a <= 'Z')
			a -= 'A';

		if (b >= 'A' && b <= 'Z')
			b -= 'A';

		if (a != b)
			return	false;
	}

	return true;
}

inline std::string_view sMESSAGE_HTTP::get_header(const std::string_view _str_parameter) const
{
	for (auto& iter: headers)
	{
		if (__icompare(_str_parameter, iter.key))
		{
			return	iter.value;
		}
	}

	return	std::string_view();
}



}