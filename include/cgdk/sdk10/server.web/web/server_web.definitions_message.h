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
//    - C4250�� ���� ����� virtual ��ӵ� interface�� ���ؼ� � ���� ����
//      �ߴ����� ���ؼ� ǥ�����ִ� Warnning�̴�. �� �κп� ���� ǥ�ð�
//      �ʿ� �����Ƿ� �� �κ��� Disable�Ѵ�.
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 1. CGMSG- Network��
//-----------------------------------------------------------------------------
inline shared_buffer message_web_error(uint32_t _error_code, std::string_view _strErrorMessage)
{
	// 1) buffer�� �Ҵ�޴´�.
	auto temp_buffer = alloc_shared_buffer(4096);

	// 2) append http header
	temp_buffer.append_text("HTTP/1.1 {} {}\r\n", _strErrorMessage.data(), _error_code);	// Protocol ���� �� �����ڵ�
	temp_buffer.append_text("Server: CGCII/9.0.0\r\n");		// Web Server Bannder ����
	temp_buffer.append_text("Content-type:text/html\r\n");	// MIME Ÿ��
	temp_buffer.append_text("Content-length:0\r\n");		// http body ũ��
	temp_buffer.append_text("\r\n");						// html ��

	// return) 
	return temp_buffer;
}


}