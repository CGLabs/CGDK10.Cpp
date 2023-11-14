//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
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

#define __CGDK_IMEMORY

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// Imemory
//
//
//-----------------------------------------------------------------------------
class Imemory : 
	public						_buffer_view<char>,
	virtual public				Ireferenceable
{
public:
			Imemory() noexcept {}
			Imemory(char* _data, std::size_t _size) noexcept : _buffer_view<char>(_data, _size) {}
			Imemory(const _buffer_view<char>& _buffer) noexcept : _buffer_view<char>(_buffer) {}
	virtual	~Imemory() noexcept {}

	[[nodiscard]] auto get_lower_bound() const noexcept { return data_;};
	[[nodiscard]] auto get_upper_bound() const noexcept { return data_ + size_;};
	[[nodiscard]] auto get_bound() const noexcept { return buffer_bound{ get_lower_bound(), get_upper_bound() }; };
};


object_ptr<Imemory> _mem_alloc(size_t _size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS);
_shared_buffer<buffer> _alloc_shared_buffer(std::size_t _size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS);


}