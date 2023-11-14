//*****************************************************************************
//*                                                                           *
//*                      Cho SangHyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                             CG Object Classes                             *
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
// 1. CG3D::TIME��!
//    1) Client�� ���ǰ� �ϱ� ���� Performance���ٴ� Client���� ���⸦ �߿� 
//       ���� �ξ� �ٸ� Program�� �����ϴ� �߰��� Run�� ���������ν� ���� ó��
//       �� �� �� �ֵ��� �� ���̴�.
//    2) �⺻������ �̰��� Connect�� ������ �� Listen�� �������� �ʴ´�.
//    3) �ҷ��� ����ó���� ������ �Ͽ����Ƿ� Socket Manager�� Socket Pool ����
//       �������� �ʴ´�.
//    4) �׷��� ���ſ� ���� �����ӵ��� ũ�� �����Ͽ��� ���� Pending�������� ����
//       Failure�� ���� ���ݴ�.
//
//
// 2. CGNetRoot�� �ٽ�! Function�� ��� ����
//    1) Run   ������ �ô��ؿ� Socket�� ó���ϰ� I/O�� ó���ϴ� ���̴�.
//             �̰��� Loop�� �־ ���� �ð��������� ó���� �� �־�� �Ѵ�.
//             ���� �ҷ��ָ� �׸�ŭ �����ӵ��� ��������.
//
// 3. ���� ����
//  Run�� �׻� ���� �ð����� ������ ���� I/O�� ���� ó���� �ݵ��� ���־�� �Ѵ�.
//
//-----------------------------------------------------------------------------

namespace CG3D
{

typedef	uint32_t	COLOR;
typedef	VALUE3		COLOR3;
typedef	VALUE4		COLOR4;


}

#define	CG3D_RGB(r, g, b)			((g_BytePerPixel==4) ? CG3D_RGB32(r,g,b,0) : (g_BytePerPixel==3) ? CG3D_RGB24(r,g,b) : (*(DWORD*)g_PixelRMask & 0x00008000) ? CG3D_RGB16_565(r,g,b): CG3D_RGB16_555(r,g,b))
#define	CG3D_RGB16_555(r,g,b)		(((unsigned short)r & 0x00f8)<<7 | ((unsigned short)g & 0x00f8)<<2 | ((unsigned short)b & 0x00f8)>>3)
#define	CG3D_RGB16_565(r,g,b)		(((unsigned short)r & 0x00f8)<<8 | ((unsigned short)g & 0x00fc)<<3 | ((unsigned short)b & 0x00f8)>>3)
#define	CG3D_RGB24(r,g,b)			((unsigned long)r<<16 | (unsigned long)g<<8 | (unsigned long)b)
#define	CG3D_RGB32(r,g,b,alpha)		((unsigned long)r<<16 | (unsigned long)g<<8 | (unsigned long)b | (unsigned long)alpha<<24)
#define CG3D_RGBA(r, g, b, a)		((COLOR) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))


