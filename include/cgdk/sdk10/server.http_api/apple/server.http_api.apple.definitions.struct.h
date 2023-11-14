//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          server.http_api.apple                            *
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

namespace CGDK::http_api::apple
{
	
//-----------------------------------------------------------------------------
//
// Login(로그인)
//
//  기본적으로 OAuth 2.0의 기준을 따른다.
//  따라서 로그인처리는 'Authorize'를 통해 'authorize_code(인증 코드)'를 받은 후
//  'token'을 통해 'access_token'을 받아 이 'access_token'으로 각종 조작을 수행한다.

//
//   1) Authorize (코드 받기)
//   2) Token (사용자 토큰 갱신)
//   3) Logout (로그 아웃)
//   4) Signup (앱 연결)
//   5) Unlink (앱 연결 해제)
//   6) Me (사용자 정보 요청)
//   7) UPDATE_PROFILE (사용자 정보 저장)
//   8) IDS (사용자 리스트 요청)
//   9) ACCESS_TOKEN_INFO (사용자 토큰 유효성 검사 및 정보 얻기)
//  10) memo/default/send (동적 동의)
//
// ----------------------------------------------------------------------------

}
