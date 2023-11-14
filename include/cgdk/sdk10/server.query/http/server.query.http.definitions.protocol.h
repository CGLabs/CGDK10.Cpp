//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                Web Classes                                *
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
// ----------------------------------------------------------------------------
// 1) 
namespace eMESSAGE
{
	namespace SERVER
	{
		namespace QUERY
		{
			const uint32_t	INIT_QUERIER_HTTP	 = (CODE_TYPE::INIT | CODE_TYPE::TAIL_0 | 200);
		}
	}
}

struct sMESSAGE_INIT_QUERIER_HTTP : public sMESSAGE
{
public:
	sMESSAGE_INIT_QUERIER_HTTP(Iexecutor* _pexecutor=nullptr) : sMESSAGE(eMESSAGE::SERVER::QUERY::INIT_QUERIER_HTTP), pexecutor(_pexecutor)	{}
public:
	object_ptr<Iexecutor>			pexecutor;
};


}