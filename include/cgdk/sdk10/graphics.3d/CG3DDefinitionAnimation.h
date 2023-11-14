//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              CG3D D3D Classes                             *
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
// CGMSG
//
// 1. CGMSG는...
//    1) 렌더링을 위한 상황정보를 담고 있는 Class
//
//
//-----------------------------------------------------------------------------
namespace CG3D
{

//-----------------------------------------------------------------------------
// 1) Time Clip
//-----------------------------------------------------------------------------
struct TIMECLIP
{
	float				fClipStart;		// Byte 4 :  4 
	float				fClipEnd;		// Byte 4 :  8 
	float				fBlendSpeed;	// Byte 4 : 12 (0.0005f)
	float				fBlendFactor;	// Byte 4 : 16 (0.0f)

	TIMECLIP*			pNextClip;		// Byte 4 : 24 
};

//-----------------------------------------------------------------------------
// 2) Time Event
//-----------------------------------------------------------------------------
struct TIME_EVENT
{
	float	m_fTime;

	uint32_t	dwMessage;
	uint32_t	lParam;
	uint32_t	wParam;

};


}
