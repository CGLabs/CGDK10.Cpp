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
/**
*/
//-----------------------------------------------------------------------------
template<typename TTYPE> class Iregisterable;
//

//-----------------------------------------------------------------------------
/**

 @class		Iregisterable
 
*/
//-----------------------------------------------------------------------------
template <typename TTYPE>
class Iregisterable : virtual public Ireferenceable
{
public:
	virtual bool				process_register(TTYPE* _object) PURE;
	virtual bool				process_unregister(TTYPE* _object) PURE;
};


}