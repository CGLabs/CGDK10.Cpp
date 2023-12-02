//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                Redis Classes                              *
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
// 1. Definitions
//-----------------------------------------------------------------------------
// 1) 
namespace eMESSAGE::SERVER::QUERY
{
	const uint32_t	INIT_QUERIER_REDIS	 = (eMESSAGE::SERVER::QUERY::BASE | 10);
}


//-----------------------------------------------------------------------------
// 2. sMESSAGE- Window message¿ë
//-----------------------------------------------------------------------------
struct sMESSAGE_REDIS_RESPONSE
	: public sMESSAGE
{
public:
			sMESSAGE_REDIS_RESPONSE() : sMESSAGE(eMESSAGE::SYSTEM::NETWORK_RESP)	{}
public:
			object_ptr<query::redis::Iquery>	pquery;

			bool	is_success() const noexcept;
			bool	is_fail() const noexcept { return !is_success(); }
};


}