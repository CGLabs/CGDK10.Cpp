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
// CGRenderer::CPoints
//
// 1. crypt::CCSP��!
//    1) Windows���� �������ִ� ��ȣȭ API�� ������� Crypto class�Դϴ�. 
//
//
//-----------------------------------------------------------------------------
namespace crypt
{

[[nodiscard]] std::string encode_base64(const_buffer_view _source);
[[nodiscard]] shared_buffer decode_base64(const std::string_view _encoded);

}


}