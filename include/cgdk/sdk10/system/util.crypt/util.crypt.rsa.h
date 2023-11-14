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
//
//-----------------------------------------------------------------------------
namespace crypt
{
struct rsa_public_key
{
	std::string_view	key;
};

struct rsa_private_key
{
	std::string_view 	key;
};

[[nodiscard]] shared_buffer encrypt_rsa(rsa_public_key _encryption_key, buffer_view _source);
[[nodiscard]] shared_buffer encrypt_rsa(shared_buffer _dest, rsa_public_key _encryption_key, buffer_view _source);
[[nodiscard]] shared_buffer encrypt_rsa(rsa_private_key _encryption_key, buffer_view _source);
[[nodiscard]] shared_buffer encrypt_rsa(shared_buffer _dest, rsa_private_key _encryption_key, buffer_view _source);

[[nodiscard]] shared_buffer decrypt_rsa(rsa_public_key _decryption_key, buffer_view _source);
[[nodiscard]] shared_buffer decrypt_rsa(shared_buffer _dest, rsa_public_key _decryption_key, buffer_view _source);
[[nodiscard]] shared_buffer decrypt_rsa(rsa_private_key _decryption_key, buffer_view _source);
[[nodiscard]] shared_buffer decrypt_rsa(shared_buffer _dest, rsa_private_key _decryption_key, buffer_view _source);


}


}