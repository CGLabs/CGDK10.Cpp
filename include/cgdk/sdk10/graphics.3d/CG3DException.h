//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              CG3D D3D Classes                             *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGMSG
//
// 1. CGMSG��...
//    1) �������� ���� ��Ȳ������ ��� �ִ� Class
//
//
//-----------------------------------------------------------------------------
namespace CGException
{

class CThrow_D3D : 
	public						std::exception,
	virtual public				ICGExceptionThrowable
{
public:
	CThrow_D3D() : std::exception(), ICGExceptionThrowable()		{	CGASSERT_ERROR_CRITICAL;}
	CThrow_D3D(const char *const& _What) : std::exception(_What), ICGExceptionThrowable()	{	CGASSERT_ERROR_CRITICAL;}

public:
	virtual	const _CHAR*		Description()							{	return _CGTEXT("");}

};
	

}
