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

 @class		function


*///-----------------------------------------------------------------------------
template <class TEXECUTE = std::function<void()>>
class schedulable::Nexecutable_function :
	virtual public				schedulable::Iexecutable,
	public						CGDK::executable::function<TEXECUTE>
{
protected:
	explicit Nexecutable_function() { this->set_object_type(eOBJECT_TYPE::SCHEDULABLE_FUNCTION);}
	virtual ~Nexecutable_function() noexcept {}
};


}