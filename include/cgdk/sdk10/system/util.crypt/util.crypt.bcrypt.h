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
// CGDK::crypt::rsa
//
//
//-----------------------------------------------------------------------------
namespace crypt
{
namespace bcrypt
{
    [[nodiscard]] std::string hash_password(const std::string_view _password, std::string_view _salt);
    [[nodiscard]] std::string generate_hash(const std::string_view _password, int _rounds = 10, char _minor = 'b');
    [[nodiscard]] bool check_password(const std::string_view _password, const std::string_view _hashed_password);
}
}

}
