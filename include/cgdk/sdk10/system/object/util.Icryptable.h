//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              Utility Classes                              *
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
// cryptBase
//
// 1. cryptBase��!
//    1) �Ϻ�ȣȭ�� ���õ�...
//
//
//-----------------------------------------------------------------------------
class Icryptable : 
// inherited classes)
	virtual	public				Ireferenceable
{
// constructor/destructor)
protected:
			Icryptable() noexcept {}
	virtual	~Icryptable() noexcept {}

// public)
public:
			object_ptr<Icrypt>	m_pcrypt;
};


}