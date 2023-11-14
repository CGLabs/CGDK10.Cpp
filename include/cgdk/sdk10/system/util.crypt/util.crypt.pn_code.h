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
// crypt::pn_code
//
//
//-----------------------------------------------------------------------------
namespace crypt
{

class pn_code
{
public:
			shared_buffer		initialize_seed();
			void				initialize_seed(const_buffer_view _seed_info);
	
	[[nodiscard]] buffer_view	encode(buffer_view _dest, const_buffer_view _source);
	[[nodiscard]] shared_buffer	encode(const_buffer_view _source);

protected:
			std::array<uint8_t, 256> m_array_key;
			uint8_t				m_pos_out = 0;
			uint8_t				m_pos_get = 0;
};


}
}