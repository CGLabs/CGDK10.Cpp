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
// definitions.factory.protocol
//
//
//-----------------------------------------------------------------------------
namespace eMESSAGE
{
	namespace FACTORY
	{
		const uint32_t	BASE						 = eMESSAGE::SYSTEM::FACTORY +  1;

		const uint32_t	ENABLE_SUSTAIN				 = BASE +  1;
		const uint32_t	DISABLE_SUSTAIN				 = BASE +  2;
		const uint32_t	IS_ALL_RELEASED				 = BASE +  3;
		const uint32_t	IS_SUSTAIN_ENABLE			 = BASE +  4;

		const uint32_t	FACTORY_PREPARE				 = BASE +  5;
		const uint32_t	FACTORY_SHRINK				 = BASE +  6;
		const uint32_t	FACTORY_SUSTAIN				 = BASE +  7;
		const uint32_t	FACTORY_IS_ENABLE_SUSTAIN	 = BASE +  8;
		const uint32_t	FACTORY_ENABLE_SUSTAIN		 = BASE +  9;

		const uint32_t	FACTORY_LIST				 = BASE + 10;
		const uint32_t	FACTORY_LIST_UPDATE			 = BASE + 11;
		const uint32_t	FACTORY_REGISTER			 = BASE + 12;
		const uint32_t	FACTORY_UNREGISTER			 = BASE + 13;
		const uint32_t	FACTORY_UPDATE				 = BASE + 14;

		namespace ATTRIBUTE
		{
			const uint32_t	BASE					 = eMESSAGE::ATTRIBUTE::BASE | CODE_TYPE::TAIL_SUB_1;

			const uint32_t	ALL_FACTORY_NAME		 = BASE +  1;
			const uint32_t	ALL_FACTORY_INFO		 = BASE +  2;
			const uint32_t	FACTORY_INFO			 = BASE +  3;
			const uint32_t	FACTORY_INFO_ADD		 = BASE +  4;
			const uint32_t	FACTORY_INFO_REMOVE		 = BASE +  5;
		}
	}
}

#define	CGATTRIBUTE_TYPE_NAME						101
#define	CGATTRIBUTE_TYPE_ID							102
#define	CGATTRIBUTE_OBJECT_NAME						103
#define	CGATTRIBUTE_OBJECT_ID						104

#define	CGATTRIBUTE_FACTORY_COUNT					502
#define	CGATTRIBUTE_FACTORY_OBJECT_SIZE				503
#define	CGATTRIBUTE_FACTORY_STACKED_COUNT			504
#define	CGATTRIBUTE_FACTORY_EXISTING_LIMITS			505
#define	CGATTRIBUTE_FACTORY_STATISTICS				506
#define	CGATTRIBUTE_FACTORY_STATISTICS_CREATED		507
#define	CGATTRIBUTE_FACTORY_STATISTICS_DELETED		508
#define	CGATTRIBUTE_FACTORY_STATISTICS_ALLOCATED	509
#define	CGATTRIBUTE_FACTORY_STATISTICS_FREED		510
#define	CGATTRIBUTE_FACTORY_STATISTICS_EXISTING		511
#define	CGATTRIBUTE_FACTORY_STATISTICS_INUSING		512


}