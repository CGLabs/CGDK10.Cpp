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
// CGDK::edc functions
//
//-----------------------------------------------------------------------------
namespace edc
{

[[nodiscard]] uint32_t get_checksum8(uint8_t* _pdata, uint32_t _data_length);
[[nodiscard]] uint32_t get_checksum16(uint16_t* _pdata, uint32_t _data_length);
[[nodiscard]] uint32_t get_checksum32(uint32_t* _pdata, uint32_t _data_length);


}


}