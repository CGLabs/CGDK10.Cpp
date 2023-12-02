//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              Factory Classes                              *
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
//-----------------------------------------------------------------------------
//
// definitions for buffer
//
//-----------------------------------------------------------------------------
namespace CGDK
{

// crc)
class crc		
{
public:
	crc() noexcept : m_pcrc(&edc::default_crc) {}
	crc(edc::crc* _p) noexcept : m_pcrc(_p) {}
public:
	edc::crc*		m_pcrc;
};

// T) Compress
struct COMPRESS
{
public:
	const_buffer_view	m_buffer;

public:
	COMPRESS(const const_buffer_view& _buffer) noexcept : m_buffer(_buffer) {}
};

struct SET_LENGTH
{
};

struct END_MESSSAGE
{
};

struct SET_LENGTH_CRC : public crc
{
	SET_LENGTH_CRC() noexcept {}
	SET_LENGTH_CRC(edc::crc* p) noexcept : crc(p) {}
};

struct sha224
{
public:
	sha224() noexcept : str_source(nullptr) {}
	sha224(const char* _str_source) noexcept : str_source(_str_source) {}

public:
	const char*	str_source;
};

struct sha256
{
public:
	sha256() noexcept : str_source(nullptr) {}
	sha256(const char* _str_source) noexcept : str_source(_str_source) {}

public:
	const char*	str_source;
};

struct sha384
{
public:
	sha384() noexcept : str_source(nullptr) {}
	sha384(const char* _str_source) noexcept : str_source(_str_source) {}

public:
	const char* str_source;
};

struct sha512
{
public:
	sha512() noexcept : str_source(nullptr) {}
	sha512(const char* _str_source) noexcept : str_source(_str_source) {}

public:
	const char* str_source;
};

template <class X>
_buffer_view<X> _append_CRC(buffer& _dest, const crc& _crc)
{
	// check) 
	CGDK_ASSERT(_crc.m_pcrc != nullptr);

	// check) 
	CGD_THROW_IF(_crc.m_pcrc == nullptr, std::exception());

	// 1) get position
	auto l = _dest.size();

	// 2) add crc
	_dest.template _append<uint32_t>(_crc.m_pcrc->get_crc(const_cast<unsigned char*>(_dest.data<unsigned char>()), _dest.size()));

	// return) 
	return _buffer_view<X>(const_cast<X*>(_dest.data() + l), _dest.size() - l);
}

template <class X>
_buffer_view<X> _append_compress(buffer& _dest, const shared_buffer& _original)
{
	// check) 
	CGDK_ASSERT(_dest.data() != nullptr);

	// check) 
	CGDK_ASSERT(_original.data() != nullptr);

	// check) 
	if(_original.data() == nullptr) throw std::invalid_argument("buffer pointer is nullptr ");

	// declare)
	auto pos_now = _dest.data();

	// declare) 
	buffer_view buf_dest{ pos_now + _dest.size() + sizeof(COUNT_T) + sizeof(COUNT_T), reinterpret_cast<const char*>(_dest.get_upper_bound()) - (pos_now + sizeof(COUNT_T) + sizeof(COUNT_T)) };

	// 1) compress data
	auto result_buffer = compress::zip(buf_dest, _original);

	// check) 
	if(result_buffer.empty())
		throw std::domain_error("Compression fail!! ");

	// 2) get position
	auto l = _dest.size();
		
	// 3) append [compressed_size]
	*(COUNT_T*)pos_now = result_buffer.template size<COUNT_T>();
	pos_now += sizeof(COUNT_T);

	// 4) append [compressed_data]
	*(COUNT_T*)pos_now = static_cast<COUNT_T>(_original.template size<COUNT_T>());
	pos_now += sizeof(COUNT_T);

	// 5) add ptr and size
	_dest.set_data(pos_now);
	_dest.add_size(result_buffer.size() + sizeof(COUNT_T) + sizeof(COUNT_T));

	// return) 
	return _buffer_view<X>(const_cast<X*>(_dest.data() + l), _dest.size() - l);
}

template <class T>
shared_buffer _extract_compress(_buffer_view<T>& _source)
{
	// check)
	if((sizeof(uint32_t) + sizeof(uint32_t)) > _source.size()) throw std::length_error("buffer is too short!! [0] ");

	// Declar) 
	int64_t	temp_offset = 0;

	// 1) get [compressed_size]
	auto size_compressed = static_cast<std::size_t>(_source.template _front<uint32_t>(temp_offset));

	// check)
	if(size_compressed>_source.size()) throw std::length_error("buffer overflow!! [1] ");
	
	// 2) get [decompressed_size]
	auto size_original = static_cast<std::size_t>(_source.template _front<uint32_t>(temp_offset));

	// 3) allocate [decompressed_data_buffer] as size as [decompressed_size]
	shared_buffer dest = alloc_shared_buffer(size_original);
	auto length = dest.size();

	// 4) decompress to [decompressed_data_buffer]
	auto result = compress::unzip(const_cast<char*>(dest.data()), &length, _source._front(temp_offset), size_compressed);

	// check) 
	if(result != 0)
		throw std::domain_error("Uncompression fail!! ");

	// 5) Pop Front
	_source._extract_bytes(temp_offset+size_compressed);

	// 6) length Udpate
	dest.set_size(length);
	
	// return) 
	return	dest;
}

inline shared_buffer _front_compress(const buffer_view& _source, int64_t& _offset)
{
	// check)
	if((sizeof(uint32_t) + sizeof(uint32_t)) > _source.size())
	{
		throw std::length_error("buffer is too short!! [0] ");
	}

	// Declar) 
	int64_t	temp_offset	 = _offset;

	// 1) get [compressed_size]
	std::size_t size_compressed = static_cast<std::size_t>(_source.template _front<uint32_t>(temp_offset));

	// check) 
	if(size_compressed > _source.size()) throw std::length_error("buffer overflow!! [1] ");
	
	// 2) get [decompressed_size]
	std::size_t size_original = static_cast<std::size_t>(_source.template _front<uint32_t>(temp_offset));

	// 3) allocate [decompressed_data_buffer] as size as [decompressed_size]
	shared_buffer dest = alloc_shared_buffer(size_original);
	std::size_t length = dest.size();

	// 4) decompress to [decompressed_data_buffer]
	auto result = compress::unzip(dest, buffer_view(_source._front(temp_offset), size_compressed));

	// check)
	if(result.size() == 0)
		throw std::domain_error("Uncompression fail!! ");

	// 5) update _offset
	_offset = static_cast<int64_t>(temp_offset+size_compressed);

	// 6) length Udpate
	dest.set_size(length);

	// return) 
	return dest;
}

inline std::size_t _get_compressed_size(const COMPRESS& _data)
{
	// error) 
	CGASSERT_ERROR(false);

	// return) real compress and return compressed size
	return compress::zip(_data.m_buffer).size();
}

// class for PUSH_FRONT)
// class for PUSH_BACK)
template<class B> class serializer_append<B, crc>				{ public: using type = _buffer_view<typename B::element_t>;	template<class S> static type _do_append(S& _s, const crc& _data)			{ return _append_CRC<typename B::element_t>(_s, _data);}};
template<class B> class serializer_append<B, COMPRESS>			{ public: using type = _buffer_view<typename B::element_t>;	template<class S> static type _do_append(S& _s, const COMPRESS& _data)		{ return _append_compress<typename B::element_t>(_s, _data.m_buffer);}};
template<class B> class serializer_append<B, SET_LENGTH>		{ public: using type = void;								template<class S> static type _do_append(S& _s, const SET_LENGTH& )			{ int64_t pos = 0; _s.template _front<uint32_t>(pos)= static_cast<uint32_t>(_s.size());}};
template<class B> class serializer_append<B, END_MESSSAGE>		{ public: using type = void;								template<class S> static type _do_append(S& _s, const SET_LENGTH& )			{ int64_t pos = 0; _s.template _front<uint32_t>(pos)= static_cast<uint32_t>(_s.size());}};
template<class B> class serializer_append<B, SET_LENGTH_CRC>	{ public: using type = _buffer_view<typename B::element_t>;	template<class S> static type _do_append(S& _s, const SET_LENGTH_CRC& _data){ int64_t pos = 0; _s.template _front<uint32_t>(pos)= static_cast<uint32_t>(_s.size() + sizeof(SIZE_OF_CRC)); return _append_CRC<typename B::element_t>(_s, _data);}};
// class for POP_FRONT)											  		  
template<class B> class serializer_extract<B, CGDK::COMPRESS>	{ public: using type = shared_buffer;						template<class S> static type _do_extract(S& _s)							{ return _extract_compress(_s);}};
// class for front)
template<class B>	class serializer_peek<B, CGDK::COMPRESS>
					{	public:	using type = shared_buffer;
						template<class S> static type _do_peek(const S& _s, int& _offset)	{ return _front_compress(_s, _offset); }
					};
template<class B>	class serializer_size_of<B, CGDK::COMPRESS>
					{	public:
								static std::size_t  _get_append_size(const COMPRESS& _data) { return _get_compressed_size(_data); }
								template<class S> 
								static std::size_t  _get_extract_size(const S& _buffer, int64_t& _offset)	{ CGDK_ASSERT(false); return 0;}
					};

struct sMESSAGE_BUFFER : public sMESSAGE
{
public:
			sMESSAGE_BUFFER() noexcept : sMESSAGE() {}
			sMESSAGE_BUFFER(uint32_t _message) noexcept : sMESSAGE(_message) {}
			template<class TSOURCE>
			sMESSAGE_BUFFER(uint32_t _message, TSOURCE _psource) noexcept : sMESSAGE(_message, _psource) {}
			template<class TSOURCE>
			sMESSAGE_BUFFER(uint32_t _message, TSOURCE _psource, const shared_buffer& _buffer) noexcept : sMESSAGE(_message, _psource), buf_message(_buffer) {}
			sMESSAGE_BUFFER(uint32_t _message, const shared_buffer& _buffer) noexcept : sMESSAGE(_message), buf_message(_buffer) {}
			sMESSAGE_BUFFER(const shared_buffer& _buffer) noexcept : sMESSAGE(eMESSAGE::SYSTEM::BUFFER), buf_message(_buffer) {}

public:
			shared_buffer		buf_message;
};


}