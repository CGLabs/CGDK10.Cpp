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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

//-----------------------------------------------------------------------------
//
// 설명)
//
//    - AccountID : 계정의 고유 번호:DB에 저장된 번호며 영원 불변
//    - LoginID   : 로긴 때마다 부여되는 ID로 해당 로긴에서만 유효하다.
//    - CheckinID : 체크인 할때 마다 부여되는 ID로 해당 서버에서만 유효한 ID이다.
//    - TransactableID : 요청때마다 할당되는 ID로 Transactable을 구분하기 위해 사용된다.
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

		// 2) 서버간 xhdtlstl 사용되는 메시지
		const message_t	REQUEST_CERTIFY					 = BASE | 10;
		const message_t	RESPONSE_CERTIFY				 = BASE | 11;
		const message_t	REQUEST_RECOVER					 = BASE | 12;
		const message_t	SEND_ACK						 = BASE | 13;
		

		// 3) transaction Command 메시지들
		//    - Check-In 요청 시 LoginID를 가지고 있으면 그것을 발행한 쪽에서 강제 이행 받을 수 있다.
		//    - Check-In 요청 시 LoginID를 가지고 있지 않으면 중복 접속시 Reject된다.
		//    - Request-ID의 신규 발행은 Log-In시에만 된다.
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