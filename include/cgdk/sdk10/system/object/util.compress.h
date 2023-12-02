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
// CGCompress
//
// 1. CGCompress��!
//    1) ������ �����ϴ� Function�̴�.
//    2) ���Լ��� ���������� ZLib�� �Լ��� ����ϰ� �ִ�.
//    3) ���� �� �Լ��� ����ϰ��� �Ѵٸ� Zlib�� �������ؼ� �߰������־���Ѵ�.
//
//  ���ǻ���) �⺻������ ZLib�� �����ϰ� ���� �ʴ�.
//            �ʿ�� �������̺귯���� ZLib�� ������ �������Ͽ� Link�����־��
//            �Ѵ�.
//  
//            #pragma comment(lib,"zlib.lib")
//
//
//-----------------------------------------------------------------------------
namespace compress
{
	[[nodiscard]] buffer_view zip(buffer_view _buf_dest, const_buffer_view _buf_source);
	[[nodiscard]] shared_buffer	zip(const_buffer_view _buf_source);
	[[nodiscard]] buffer_view unzip(buffer_view _buf_dest, const_buffer_view _buf_source);
	[[nodiscard]] shared_buffer unzip(const_buffer_view _buf_source);
}


}