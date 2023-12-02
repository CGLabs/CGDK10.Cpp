//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                 Distributed Object Storage System Classes                 *
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
// ����)
//
//    - AccountID : ������ ���� ��ȣ:DB�� ����� ��ȣ�� ���� �Һ�
//    - LoginID   : �α� ������ �ο��Ǵ� ID�� �ش� �α信���� ��ȿ�ϴ�.
//    - CheckinID : üũ�� �Ҷ� ���� �ο��Ǵ� ID�� �ش� ���������� ��ȿ�� ID�̴�.
//    - TransactableID : ��û������ �Ҵ�Ǵ� ID�� Transactable�� �����ϱ� ���� ���ȴ�.
//
//-----------------------------------------------------------------------------
namespace CGDK
{
namespace eMESSAGE
{
namespace SERVER
{
	namespace DOSS
	{
		// 1) manager
		const message_t	REGISTER						 = BASE | 1;
		const message_t	UNREGISTER						 = BASE | 2;

		// 2) ������ xhdtlstl ���Ǵ� �޽���
		const message_t	REQUEST_CERTIFY					 = BASE | 10;
		const message_t	RESPONSE_CERTIFY				 = BASE | 11;
		const message_t	REQUEST_RECOVER					 = BASE | 12;
		const message_t	SEND_ACK						 = BASE | 13;
		

		// 3) transaction Command �޽�����
		//    - Check-In ��û �� LoginID�� ������ ������ �װ��� ������ �ʿ��� ���� ���� ���� �� �ִ�.
		//    - Check-In ��û �� LoginID�� ������ ���� ������ �ߺ� ���ӽ� Reject�ȴ�.
		//    - Request-ID�� �ű� ������ Log-In�ÿ��� �ȴ�.
		const message_t	COMMAND_REQUEST					 = BASE | 30;
		const message_t	COMMAND_RESPONSE				 = BASE | 31;
		const message_t	COMMAND_FAIL					 = BASE | 32;
		const message_t	COMMAND_REQUEST_CHECKIN			 = BASE | 33;
		const message_t	COMMAND_REQUEST_CHECKOUT		 = BASE | 34;
		const message_t	COMMAND_REQUEST_UPDATE			 = BASE | 35;
		const message_t	COMMAND_REQUEST_COMMAND			 = BASE | 36;
		const message_t	COMMAND_REQUEST_CREATE			 = BASE | 37;
		const message_t	COMMAND_REQUEST_REMOVE			 = BASE | 38;
		const message_t	COMMAND_CANCEL					 = BASE | 39;
		const message_t	CONTROL_REQUEST					 = BASE | 40;
		const message_t	CONTROL_RESPONSE				 = BASE | 41;

	}
}
}
}