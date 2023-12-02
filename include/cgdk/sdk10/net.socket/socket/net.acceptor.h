//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
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
// net::acceptor
//
//  1) �⺻������ net::io::acceptor::Ntcp�̴� ������ ���⿡ process_alloc_connectable()
//     �Լ��� �������� Template class�̴�.
//  
//  2) Accept�� ����� socket�� Class�� Template ���ڷ� ������ �ָ� �� socket
//     ���� Accept�� �����Ѵ�.
//  
//  3) �� Class�� ���� �� �� TSOCKET�� acceptor�� �����Ͽ� ����Ϸ��� socket�� 
//     ���� ������ acceptor�� ������ �ϰ� �Ǹ� T�� ������ socket�� �����Ͽ� 
//     Accept�� �ɾ acceptor�� �����Ѵ�.
//
//
//   4) initialize/start String
//
//      "[Name]/Address"
//	    "[Name]/Port"
//	    "[Name]/prepare on start"
//	    "[Name]/must prepare"
//
//-----------------------------------------------------------------------------
template <class TSOCKET, class FLAG = void>
class net::acceptor
{
};


}