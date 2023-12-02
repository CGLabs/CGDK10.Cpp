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

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// messsage Definitions
//
//-----------------------------------------------------------------------------
namespace eMESSAGE
{
	// 1) ...
	const uint32_t	DUMP						 = eMESSAGE::SYSTEM::EXECUTE;
	const uint32_t	THREAD_LIST					 = eMESSAGE::SYSTEM::EXECUTE + 1;
	const uint32_t	THREAD_LIST_UPDATE			 = eMESSAGE::SYSTEM::EXECUTE + 2;
	const uint32_t	THREAD_REGISTER				 = eMESSAGE::SYSTEM::EXECUTE + 3;
	const uint32_t	THREAD_UNREGISTER			 = eMESSAGE::SYSTEM::EXECUTE + 4;

	const uint32_t	EXECUTOR_LIST				 = eMESSAGE::SYSTEM::EXECUTE + 5;
	const uint32_t	EXECUTOR_LIST_UPDATE		 = eMESSAGE::SYSTEM::EXECUTE + 6;
	const uint32_t	EXECUTOR_REGISTER			 = eMESSAGE::SYSTEM::EXECUTE + 7;
	const uint32_t	EXECUTOR_UNREGISTER			 = eMESSAGE::SYSTEM::EXECUTE + 8;
	const uint32_t	EXECUTOR_UPDATE				 = eMESSAGE::SYSTEM::EXECUTE + 9;

	const uint32_t	SCHEDULABLE_LIST			 = eMESSAGE::SYSTEM::EXECUTE + 10;
	const uint32_t	SCHEDULABLE_LIST_UPDATE		 = eMESSAGE::SYSTEM::EXECUTE + 11;
	const uint32_t	SCHEDULABLE_REGISTER		 = eMESSAGE::SYSTEM::EXECUTE + 12;
	const uint32_t	SCHEDULABLE_UNREGISTER		 = eMESSAGE::SYSTEM::EXECUTE + 13;
	const uint32_t	SCHEDULABLE_UPDATE			 = eMESSAGE::SYSTEM::EXECUTE + 14;

	// 2) 
	const uint32_t	INIT_EXECUTOR_COMPLETIONPORT_THREAD	 = (CODE_TYPE::INIT | CODE_TYPE::TAIL_0 | 1);
}
}