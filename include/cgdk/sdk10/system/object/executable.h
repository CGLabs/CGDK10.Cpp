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

 @class		NBatch
 @brief		�Ѳ����� ���� ���� Executable ��ü�� ť���� �ɾ��ִ� Executable�̴�. 
 @todo		
 @ref		CList<TEXECUTABLE>
 @details	\n
 ���� ���� Executable ��ü�� ť���� �������ش�. 
 ���� ������ �ɾ��ְ� �Ǹ� ť�׵� Executable ��ü���� ���ŵȴ�.

*///-----------------------------------------------------------------------------
class Nexecutable :	virtual public Iexecutable
{
public:
	virtual ~Nexecutable() noexcept {}

protected:
	virtual	void				on_execute() PURE;

public:
	virtual intptr_t			process_execute(intptr_t /*_return*/, size_t /*_param*/) override { on_execute(); return 0;}
};


}
