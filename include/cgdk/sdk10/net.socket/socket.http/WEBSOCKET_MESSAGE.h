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
// sWEBSOCKET_MESSAGE
//
//
// ----------------------------------------------------------------------------
struct sWEBSOCKET_MESSAGE
{
public:
	sWEBSOCKET_MESSAGE() : method() {}
	sWEBSOCKET_MESSAGE(buffer_view _buffer, eHTTP_METHOD _method = eHTTP_METHOD::BINARY_) : method(_method) { add_buffer(_buffer); }
	sWEBSOCKET_MESSAGE(std::string_view _string) { add_text(_string); }
	sWEBSOCKET_MESSAGE(std::u8string_view _string) { add_text(_string); }

public:
	void			add_buffer(const buffer_view& _buffer) { method = eHTTP_METHOD::BINARY_; messages.emplace_back(shared_buffer(_buffer)); }
	void			add_buffer(buffer_view&& _buffer) { method = eHTTP_METHOD::BINARY_; messages.emplace_back(std::move(_buffer)); }
	void			add_buffer(const shared_buffer& _buffer) { method = eHTTP_METHOD::BINARY_; messages.emplace_back(_buffer); }
	void			add_buffer(shared_buffer&& _buffer) { method = eHTTP_METHOD::BINARY_; messages.emplace_back(std::move(_buffer)); }
	void			reset_buffer() noexcept {}
	void			add_text(std::string_view _string) noexcept;
	void			add_text(std::u8string_view _string) noexcept;

	buffer_view		process_prepend(buffer& _buffer) const;
	buffer_view		process_append(buffer& _buffer) const;
	void			process_extract(buffer_view& _buffer) const;
	void			process_front(buffer_view& _buffer, int& _offset) const;
	std::size_t		process_get_size_of() const noexcept;

public:
					operator shared_buffer() const	{ return make_shared_buffer(*this);}

public:
	eHTTP_METHOD	method = eHTTP_METHOD::NONE_;
	std::vector<shared_buffer> messages;
};

template<class B>
class serializer_prepend<B, sWEBSOCKET_MESSAGE, void>
{
	public: using type = buffer_view;
	template<class S> static type _do_prepend(S& _s, const sWEBSOCKET_MESSAGE& _data) { return _data.process_prepend(_s); }
};
template<class B>
class serializer_append<B, sWEBSOCKET_MESSAGE, void>
{
	public: using type = buffer_view;
	template<class S> static type _do_append(S& _s, const sWEBSOCKET_MESSAGE& _data) { return _data.process_append(_s); }
};
template<class B>
class serializer_extract<B, sWEBSOCKET_MESSAGE, void>
{
	public: using type = sWEBSOCKET_MESSAGE;
	template<class S> static type _do_extract(S& _s) { sWEBSOCKET_MESSAGE data; data.process_extract(_s); return data; }
	template<class D, class S> static void _do_extract(D& _dest, S& _s) { _dest.process_extract(_s); }
};
template<class B>
class serializer_peek<B, sWEBSOCKET_MESSAGE, void>
{
	public: using type = sWEBSOCKET_MESSAGE;
	template<class S> static type _do_peek(const S& _s, int& _offset) { sWEBSOCKET_MESSAGE data; data.process_front(_s, _offset); return data; }
	template<class D, class S> static void _do_peek(D& _dest, const S& _s, int& _offset) { _dest.process_front(_s, _offset); }
};
template<>
class serializer_size_of<sWEBSOCKET_MESSAGE, void>
{	public:
			static std::size_t  _get_append_size(const sWEBSOCKET_MESSAGE& _data) { return _data.process_get_size_of(); }
			template<class S> 
			static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset) { CGDK_ASSERT(false); return 0; }
};



}