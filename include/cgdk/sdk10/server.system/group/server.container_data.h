//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          Group Template Classes                           *
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

 @class		array
 @brief		멤버별 데이터를 저장할 데이터
 @todo		
 @ref		
 @details	\n
 멤버별 데이터를 임시 저장하는 용도로 사용되는 것이다.
       
*///-----------------------------------------------------------------------------
template <class _TOBJECT>
struct container::OBJECT_SET
{
public:
			object_ptr<_TOBJECT> pobject;

public:
	[[nodiscard]] bool			operator==(const _TOBJECT* _rhs) const noexcept { return pobject == _rhs;}
	[[nodiscard]] bool			operator!=(const _TOBJECT* _rhs) const noexcept { return pobject != _rhs;}
	[[nodiscard]] bool			operator>=(const _TOBJECT* _rhs) const noexcept { return pobject >= _rhs;}
	[[nodiscard]] bool			operator> (const _TOBJECT* _rhs) const noexcept { return pobject >  _rhs;}
	[[nodiscard]] bool			operator<=(const _TOBJECT* _rhs) const noexcept { return pobject <= _rhs;}
	[[nodiscard]] bool			operator< (const _TOBJECT* _rhs) const noexcept { return pobject <  _rhs;}

	[[nodiscard]] bool			operator==(const OBJECT_SET<_TOBJECT>& _rhs) const noexcept { return pobject == _rhs.pobject;}
	[[nodiscard]] bool			operator!=(const OBJECT_SET<_TOBJECT>& _rhs) const noexcept { return pobject != _rhs.pobject;}
	[[nodiscard]] bool			operator>=(const OBJECT_SET<_TOBJECT>& _rhs) const noexcept { return pobject >= _rhs.pobject;}
	[[nodiscard]] bool			operator> (const OBJECT_SET<_TOBJECT>& _rhs) const noexcept { return pobject >  _rhs.pobject;}
	[[nodiscard]] bool			operator<=(const OBJECT_SET<_TOBJECT>& _rhs) const noexcept { return pobject <= _rhs.pobject;}
	[[nodiscard]] bool			operator< (const OBJECT_SET<_TOBJECT>& _rhs) const noexcept { return pobject <  _rhs.pobject;}

public:
			OBJECT_SET() : pobject() {}
			OBJECT_SET(_TOBJECT* _pobject, typename _TOBJECT::TOBJECT_CHANNEL _ocid) : pobject(_pobject) {}
};


//-----------------------------------------------------------------------------
//
// Iobserver::OBJECT_SET_ARRAY
//
// Array형 Group의 MemberData
//
//-----------------------------------------------------------------------------
template <class _TOBJECT, class _TOBJECT_DATA>
struct container::OBJECT_SET_DATA : public OBJECT_SET<_TOBJECT>
{
public:
			_TOBJECT_DATA		object_data;
public:
			OBJECT_SET_DATA() : OBJECT_SET<_TOBJECT>(), object_data() {}
			OBJECT_SET_DATA(_TOBJECT* _pobject) : OBJECT_SET<_TOBJECT>(_pobject), object_data() {}
			OBJECT_SET_DATA(_TOBJECT* _pobject, const _TOBJECT_DATA& _object_data) : OBJECT_SET<_TOBJECT>(_pobject), object_data(_object_data) {}
};


}