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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// 1. CG3D::TIME란!
//    1) Client에 사용되게 하기 위해 Performance보다는 Client와의 동기를 중요 
//       점을 두어 다른 Program이 동작하는 중간에 Run을 실행함으로써 각종 처리
//       를 할 수 있도록 한 것이다.
//    2) 기본적으로 이것은 Connect만 지원할 뿐 Listen은 지원하지 않는다.
//    3) 소량의 연결처리르 전제로 하였으므로 Socket Manager와 Socket Pool 등은
//       지원하지 않는다.
//    4) 그래도 과거에 비해 반응속도가 크게 증가하였고 각종 Pending현상으로 인한
//       Failure를 거의 없앴다.
//
//
// 2. CGNetRoot의 핵심! Function의 기능 설명
//    1) Run   접속을 시대해온 Socket을 처리하고 I/O를 처리하는 것이다.
//             이것을 Loop에 넣어서 일정 시간간격으로 처리를 해 주어야 한다.
//             자주 불러주면 그만큼 반응속도가 빨라진다.
//
// 3. 주의 사항
//  Run을 항상 일정 시간마다 실행을 시켜 I/O에 대한 처리를 반듯이 해주어야 한다.
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


