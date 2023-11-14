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
// net::io::Iconnect_requestable(�����)
//
// 1. Iconnect_requestable��~
//    1) Iconnectable�� ������ �������� �������� Client������ �� �� �ֵ��� ��
//       �ִ� Interface�̴�.
//    2) ���� connect�Լ��� ����Ͽ� connect�� ��û�� �� �ִ�.
//
// 2. ���� �Լ�.
//    1) process_request_connecting()
//       - ������ ��û�ϴ� ������ �����ϴ� Process�Լ��̴�.
//
//    2) process_reset_connector()
//       - �ʱ�ȭ�� ������ �� ȣ��Ǵ� �Լ��̴�.
//
//
//-----------------------------------------------------------------------------
class net::io::Iconnect_requestable :
	virtual public				object::Istartable
{
public:
	virtual bool				process_request_connecting( const net::sockaddr& _address) PURE;
	virtual	void				process_complete_connecting( uintptr_t _result) PURE;
	virtual	void				process_reset_connector() PURE;
};


}