//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              Utility Classes                              *
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
// definitions
//
//-----------------------------------------------------------------------------
namespace crypt
{
	// definitions) 
	const int		DIGEST_LENGTH_SHA224 = 28;
	const int		DIGEST_LENGTH_SHA256 = 32;
	const int		DIGEST_LENGTH_SHA384 = 48;
	const int		DIGEST_LENGTH_SHA512 = 64;

	bool			sha1				(buffer_view _out, const_buffer_view _source) noexcept;
	[[nodiscard]] shared_buffer	sha1	(const_buffer_view _source);

	bool			sha224				(buffer_view _out, const_buffer_view _source) noexcept;
	[[nodiscard]] shared_buffer	sha224	(const_buffer_view _source);

	bool			sha256				(buffer_view _out, const_buffer_view _source) noexcept;
	[[nodiscard]] shared_buffer	sha256	(const_buffer_view _source);

	bool			sha384				(buffer_view _out, const_buffer_view _source) noexcept;
	[[nodiscard]] shared_buffer	sha384	(const_buffer_view _source);

	bool			sha512				(buffer_view _out, const_buffer_view _source) noexcept;
	[[nodiscard]] shared_buffer	sha512	(const_buffer_view _source);
	

	buffer_view		hmac_md5			(buffer_view _out, const_buffer_view _key, const_buffer_view _source) noexcept;
	[[nodiscard]] shared_buffer	hmac_md5 (const_buffer_view _source, const_buffer_view _key);

	buffer_view		hmac_sha1			(buffer_view _out, const_buffer_view _key, const_buffer_view _source) noexcept;
	[[nodiscard]] shared_buffer	hmac_sha1 (const_buffer_view _source, const_buffer_view _key);

	buffer_view		hmac_sha224			(buffer_view _out, const_buffer_view _source, const_buffer_view _key) noexcept;
	[[nodiscard]] shared_buffer	hmac_sha224 (const_buffer_view _source, const_buffer_view _key);

	buffer_view		hmac_sha256			(buffer_view _out, const_buffer_view _key, const_buffer_view _source) noexcept;
	[[nodiscard]] shared_buffer	hmac_sha256 (const_buffer_view _source, const_buffer_view _key);

	buffer_view		hmac_sha384			(buffer_view _out, const_buffer_view _key, const_buffer_view _source) noexcept;
	[[nodiscard]] shared_buffer	hmac_sha384 (const_buffer_view _source, const_buffer_view _key);

	buffer_view		hmac_sha512			(buffer_view _out, const_buffer_view _key, const_buffer_view _source) noexcept;
	[[nodiscard]] shared_buffer	hmac_sha512 (const_buffer_view _source, const_buffer_view _key);
	
	struct aes_key
	{
		buffer_view	key;
		buffer_view iv;
	};

	// AES(GCM mode) encryption/decryption
		buffer_view	aes_encrypt			(buffer_view _out, buffer_view _tag, aes_key _key, const_buffer_view _source, const_buffer_view _source_add);
inline	buffer_view	aes_encrypt			(buffer_view _out, aes_key _key, const_buffer_view _source, const_buffer_view _source_add = const_buffer_view()) { return aes_encrypt(_out, buffer_view(), _key, _source, _source_add); }
		buffer_view	aes_decrypt			(buffer_view _out, buffer_view _tag, aes_key _key, const_buffer_view _source, const_buffer_view _source_add = const_buffer_view());
inline	buffer_view	aes_decrypt			(buffer_view _out, aes_key _key, const_buffer_view _source, const_buffer_view _source_add = const_buffer_view()) { return aes_decrypt(_out, buffer_view(), _key, _source, _source_add); }
}


#if !defined(__linux__)
buffer_view		_append_sha224		(buffer_view _source, const sha224& _data);
std::string		_extract_sha224		(buffer_view _source);
std::string		_front_sha224		(buffer_view _source, int& _offset);
buffer_view		_append_sha256		(buffer_view _source, const sha256& _data);
std::string		_extract_sha256		(buffer_view _source);
std::string		_front_sha256		(buffer_view _source, int& _offset);
buffer_view		_append_sha384		(buffer_view _source, const sha384& _data);
std::string		_extract_sha384		(buffer_view _source);
std::string		_front_sha384		(buffer_view _source, int& _offset);
buffer_view		_append_sha512		(buffer_view _source, const sha512& _data);
std::string		_extract_sha512		(buffer_view _source);
std::string		_front_sha512		(buffer_view _source, int& _offset);

// class for PUSH_FRONT)
// class for PUSH_BACK)
template<class B> class serializer_append<B, sha224> { public: using type = _buffer_view<typename B::element_t>; template<class S> static type _do_append(S& _s, const sha224& _data) { return _append_sha224(_s, _data);} };
template<class B> class serializer_append<B, sha256> { public: using type = _buffer_view<typename B::element_t>; template<class S> static type _do_append(S& _s, const sha256& _data) { return _append_sha256(_s, _data);} };
template<class B> class serializer_append<B, sha384> { public: using type = _buffer_view<typename B::element_t>; template<class S> static type _do_append(S& _s, const sha384& _data) { return _append_sha384(_s, _data);} };
template<class B> class serializer_append<B, sha512> { public: using type = _buffer_view<typename B::element_t>; template<class S> static type _do_append(S& _s, const sha512& _data) { return _append_sha512(_s, _data);} };
// class for POP_FRONT)								   		  		   
template<class B> class serializer_extract<B, sha224> { public: using type = std::string; template<class S> static void _do_extract(type& _dest, S& _s) { _extract_sha224(_dest, _s);} };
template<class B> class serializer_extract<B, sha256> { public: using type = std::string; template<class S> static void _do_extract(type& _dest, S& _s) { _extract_sha256(_dest, _s);} };
template<class B> class serializer_extract<B, sha384> { public: using type = std::string; template<class S> static void _do_extract(type& _dest, S& _s) { _extract_sha384(_dest, _s);} };
template<class B> class serializer_extract<B, sha512> { public: using type = std::string; template<class S> static void _do_extract(type& _dest, S& _s) { _extract_sha512(_dest, _s);} };
// class for front)									   		  		   
template<class B> class serializer_peek<B, sha224> { public: using type = std::string; template<class S> static void _do_peek(type& _dest, const S& _s, int& _offset) { _front_compress(_dest, _s, _offset);} };
template<class B> class serializer_peek<B, sha256> { public: using type = std::string; template<class S> static void _do_peek(type& _dest, const S& _s, int& _offset) { _front_compress(_dest, _s, _offset);} };
template<class B> class serializer_peek<B, sha384> { public: using type = std::string; template<class S> static void _do_peek(type& _dest, const S& _s, int& _offset) { _front_compress(_dest, _s, _offset);} };
template<class B> class serializer_peek<B, sha512> { public: using type = std::string; template<class S> static void _do_peek(type& _dest, const S& _s, int& _offset) { _front_compress(_dest, _s, _offset);} };
													   		  
// class for get_size_of)								   		  
template<> class serializer_size_of<sha224> 
{ public:
	template <class T>
	constexpr static std::size_t _get_append_size(const _basic_buffer<T>&) { return crypt::DIGEST_LENGTH_SHA224 + sizeof(COUNT_T);}
	template<class S> 
	constexpr static std::size_t _get_extract_size(const S& _buffer, int64_t& _offset) { CGDK_ASSERT(false); return 0; }
};
template<> class serializer_size_of<sha256>
{ public:
	template <class T>
	constexpr static std::size_t _get_append_size(const _basic_buffer<T>&) { return crypt::DIGEST_LENGTH_SHA256 + sizeof(COUNT_T);}
	template<class S> 
	constexpr static std::size_t _get_extract_size(const S& _buffer, int64_t& _offset) { CGDK_ASSERT(false); return 0; }
};
template<> class serializer_size_of<sha384>
{ public:
	template <class T>
	constexpr static std::size_t _get_append_size(const _basic_buffer<T>&) { return crypt::DIGEST_LENGTH_SHA384 + sizeof(COUNT_T);}
	template<class S> 
	constexpr static std::size_t _get_extract_size(const S& _buffer, int64_t& _offset) { CGDK_ASSERT(false); return 0; }
};
template<> class serializer_size_of<sha512>
{ public: 
	template <class T>
	constexpr static std::size_t _get_append_size(const _basic_buffer<T>&) { return crypt::DIGEST_LENGTH_SHA512 + sizeof(COUNT_T);}
	template<class S> 
	constexpr static std::size_t _get_extract_size(const S& _buffer, int64_t& _offset) { CGDK_ASSERT(false); return 0; }
};

#endif


}