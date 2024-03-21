//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Event Classes                            *
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
//----------------------------------------------------------------------------
//
//
//  Definitions for Event Classes
//
//
//----------------------------------------------------------------------------
namespace eMESSAGE
{
	namespace SERVER
	{
		namespace TIME_EVENT
		{
			const uint32_t	EVENT_LIST			 = BASE   +1;
			const uint32_t	EVENT_LIST_UPDATE	 = BASE   +2;
			const uint32_t	EVENT_REGISTER		 = BASE   +3;
			const uint32_t	EVENT_UNREGISTER	 = BASE   +4;
			const uint32_t	EVENT_EXECUTE		 = BASE   +5;
			const uint32_t	EVENT_UPDATE		 = BASE   +6;
		}
	}
}


}