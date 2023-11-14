//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                             Archive Classes                               *
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
// class Iarchive
//
//-----------------------------------------------------------------------------
#define	CGARCHIVE_STATUS_LOADING		0x01
#define	CGARCHIVE_STATUS_SAVING			0x02
#define	CGARCHIVE_STATUS_PRE_SAVING		0x03
#define	CGARCHIVE_STATUS_POST_LOADING	0x04

class Iarchive : 
	virtual public				Ireferenceable
{
public:
	[[nodiscard]] virtual uint32_t get_status() const PURE;
	virtual	uint32_t			set_status(uint32_t _status) PURE;
	virtual size_t				size()  const noexcept PURE;

protected:
	virtual bool				process_read(shared_buffer& _buffer) PURE;
	virtual bool				process_write(shared_buffer& _buffer) PURE;

public:
	// 1) Read
			bool				read(shared_buffer& _buffer) { return this->process_read(_buffer);}
			shared_buffer		read() { auto file_size = this->size(); RETURN_IF(file_size <= 0, shared_buffer()); shared_buffer buf_temp = alloc_shared_buffer(file_size) ^ file_size; this->process_read(buf_temp); return buf_temp; }
			template<class TTYPE>
			bool				read(TTYPE& _data) { shared_buffer temp(buffer{reinterpret_cast<char*>(&_data), static_cast<uint32_t>(sizeof(TTYPE))}, nullptr); return this->process_read(temp); }

	// 2) write
			bool				write(shared_buffer& _buffer) { return this->process_write(_buffer);}
			bool				write(shared_buffer&& _buffer) { return this->process_write(_buffer); }
			template <class T, class... TPARAM>
			constexpr std::enable_if_t<is_string_type<T>::value, bool>
				write(std::basic_string_view<T> _format, TPARAM&&... _param) 
			{
				// check)
				CGASSERT_ERROR(!_format.empty());

				// check)
				RETURN_IF(_format.empty(), false);

				// declare) 
				shared_buffer temp_buffer = alloc_shared_buffer(MAX_TRACE_STRING_LENGTH * sizeof(T));

				// 1) append text
				temp_buffer.append_text(_format, _param...);

				// 2) write to file
				return this->write(temp_buffer);
			}
};



}