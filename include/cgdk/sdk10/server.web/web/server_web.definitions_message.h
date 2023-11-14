//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / Release 2017.01.03                        *
//*                                                                           *
//*                           Network Base Classes                            *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 (c) 2016 Cho Sanghyun All right reserved.                 *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//----------------------------------------------------------------------------
//  Disable Warnning
//
// 1) Warnning C4250 Disable
//    - C4250은 다중 상속의 virtual 상속된 interface에 대해서 어떤 것을 선택
//      했는지에 대해서 표시해주는 Warnning이다. 이 부분에 대한 표시가
//      필요 없으므로 이 부분은 Disable한다.
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 1. CGMSG- Network용
//-----------------------------------------------------------------------------
inline shared_buffer message_web_error(uint32_t _error_code, std::string_view _strErrorMessage)
{
	// 1) buffer를 할당받는다.
	auto temp_buffer = alloc_shared_buffer(4096);

	// 2) append http header
	temp_buffer.append_text("HTTP/1.1 {} {}\r\n", _strErrorMessage.data(), _error_code);	// Protocol 버전 및 응답코드
	temp_buffer.append_text("Server: CGCII/9.0.0\r\n");		// Web Server Bannder 정보
	temp_buffer.append_text("Content-type:text/html\r\n");	// MIME 타입
	temp_buffer.append_text("Content-length:0\r\n");		// http body 크기
	temp_buffer.append_text("\r\n");						// html 끝

	// return) 
	return temp_buffer;
}


}