//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 6.1 / Release 2012.05.28                        *
//*                                                                           *
//*                           Data Template Classes                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangducks@gmail.com          *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                   (C) 2008 CGLabs All right reserved.                     *
//*                           http://www.CGDK.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGDK::flexible
//
// 1. CGDK::flexible란!
//    모든 타입으로 읽거나 쓰기가 가능한 데이타를 말한다.
//
// 2. 추가설명 or 사용예제
//
//
//-----------------------------------------------------------------------------
#include "cgdk/sdk10/containers/_definitions.h"

namespace CGDK
{

template <int ISIZE>
class flexible
{
// Constructor)
public:
	flexible() noexcept : m_Data{}						{}

// Member data)
private:
	char	m_Data[ISIZE];


// Public Interface)
public:
	char*						get()					{ return m_Data;}
	const char*					get() const				{ return m_Data;}
	template <typename TYPE>
	TYPE&						get()					{ CGDASSERT_ERROR(sizeof(TYPE)<=ISIZE); void* p=reinterpret_cast<void*>(m_Data); return *reinterpret_cast<TYPE*>(p);}
	template <typename TYPE>
	const TYPE&					get() const				{ CGDASSERT_ERROR(sizeof(TYPE)<=ISIZE); const void* p=reinterpret_cast<const void*>(m_Data); return *reinterpret_cast<const TYPE*>(p);}

	template <typename TYPE>
	TYPE&						get(int _offset)		{ CGDASSERT_ERROR((sizeof(TYPE)+_offset)<=ISIZE); void* p=reinterpret_cast<void*>(m_Data+_offset); return *reinterpret_cast<TYPE*>(p);}
	template <typename TYPE>
	const TYPE&					get(int _offset) const	{ CGDASSERT_ERROR((sizeof(TYPE)+_offset)<=ISIZE); const void* p=reinterpret_cast<const void*>(m_Data+_offset); return *reinterpret_cast<const TYPE*>(p);}

	int							size() const			{ return ISIZE;}
};


}
