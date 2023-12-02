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

//-----------------------------------------------------------------------------
/**

 @class		object::Iidentifiable
 

*/
//-----------------------------------------------------------------------------
class CGDK::object::Iidentifiable
{
public:
	constexpr Iidentifiable() noexcept {}
	constexpr Iidentifiable(sOBJECT_TYPE _object_type) noexcept : m_object_type(_object_type) {}
	constexpr Iidentifiable(eOBJECT_TYPE _type, uint32_t _factory_id) noexcept : m_object_type(_type, _factory_id) {}
	constexpr Iidentifiable(const sOBJECT_ID& _object_id) noexcept : m_object_id(_object_id) {}
	constexpr virtual ~Iidentifiable() noexcept {}

	[[nodiscard]] constexpr const sOBJECT_ID& object_id() const noexcept { return this->m_object_id;}
	[[nodiscard]] constexpr eOBJECT_TYPE	object_type() const noexcept { return this->m_object_type.object_type;}
	[[nodiscard]] constexpr uint32_t		object_factory() const noexcept { return this->m_object_type.factory_id;}
	[[nodiscard]] constexpr sOBJECT_ID		object_serial() const noexcept { return this->m_object_id; }

protected:
	constexpr void				set_object_type(eOBJECT_TYPE _type) noexcept { this->m_object_type.object_type =_type;}
	constexpr void				set_object_type(sOBJECT_TYPE _type) noexcept { this->m_object_type = _type;}
	constexpr void				set_object_id(const sOBJECT_ID& _id) noexcept { this->m_object_id = _id; }

public:
			sOBJECT_TYPE		m_object_type;
			sOBJECT_ID			m_object_id;
};
