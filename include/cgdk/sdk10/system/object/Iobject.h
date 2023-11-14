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

 @class		Iobject
 
*/
//-----------------------------------------------------------------------------
class Iobject : 
	public						object::Iidentifiable,
	virtual public				object::Inameable,
	virtual public				Imessageable
{
public:
			Iobject() noexcept {}
			Iobject(uint64_t _type) noexcept : object::Iidentifiable(_type) {}
			Iobject(eOBJECT_TYPE _object_type, uint32_t _factory) noexcept : object::Iidentifiable(_object_type, _factory) {}
			Iobject(const sOBJECT_ID& _id) noexcept : object::Iidentifiable(_id) {}
	virtual ~Iobject() noexcept {}
};


}

