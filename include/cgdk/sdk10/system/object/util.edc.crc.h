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
// CGDK::edc::crc
//
//-----------------------------------------------------------------------------
using CRC_T = uint32_t;
#define SIZE_OF_CRC	sizeof(CRC_T)

namespace edc
{

class crc
{
public:
			crc(uint32_t _key = 0x04c11db7L) noexcept : m_key() { if(_key != 0) { generate_crc_table(_key);}}
	virtual ~crc() noexcept {}

public:
	// 1) get crc
	[[nodiscard]] uint32_t		get_crc(buffer_view _buffer) const { return get_crc(_buffer.data<uint8_t>(), _buffer.size()); }
	[[nodiscard]] uint32_t		get_crc(const uint8_t* _pdata, size_t _data_length) const;

	// 2) get key or generate
	[[nodiscard]] uint32_t		key() const noexcept { return m_key;}
			void				generate_crc_table(uint32_t _key);

// implementation)
protected:
			uint32_t			m_key; // Table을 만든 CRCKey입니다.
			std::array<uint32_t, 256> m_table_CRC{}; // Key에 의해서 만들어진 CRCKey입니다.
};


}
}