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
// 1. definitions
//-----------------------------------------------------------------------------
enum class eRESP_DATA_TYPE : int
{
	NONE_			 = 0,
	SIMPLE_STRING_	 = '+',
	ERROR_			 = '-',
	INTEGER_		 = ':',
	BULK_STRING_	 = '$',
	ARRAY_			 = '*',
	PING_			 = 'P'
};


}