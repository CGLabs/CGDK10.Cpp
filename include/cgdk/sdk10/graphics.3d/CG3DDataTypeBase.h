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
//*                 ®œ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//*****************************************************************************
// Chosanghyun's Game Object!!!! v(` ~ `)v
//*****************************************************************************


//*****************************************************************************
//* head Files                                                                *
//*****************************************************************************
#include "CG3DDataTypeColor.h"

namespace CG3D
{
enum CULL {
    CULL_NONE		 = 1,
    CULL_CW			 = 2,
    CULL_CCW		 = 3,
    CULL_FORCE_DWORD = 0x7fffffff, /* force 32-bit size enum */
};

enum INTERPOLATION_METHOD
{
	INTERPOLATION_LERP,
	INTERPOLATION_SLERP,
	INTERPOLATION_SQUAD,
	INTERPOLATION_SPLINE
};

}

// 1) Render Type¿« ªÛ≈¬
#define	RENDERTYPE_RENDERATTRIBUTE	0x0001
#define	RENDERTYPE_VERTEXSHADER		0x0002
#define	RENDERTYPE_PIXELSHADER		0x0004
#define	RENDERTYPE_TEXTURE			0x0008
#define	RENDERTYPE_MESH				0x0010
#define	RENDERTYPE_SHADOWVOLUME		0x0020
#define	RENDERTYPE_GLOBALAMBIENT	0x0040

#define	RENDERTYPE_NORMAL			(RENDERTYPE_RENDERATTRIBUTE | RENDERTYPE_PIXELSHADER | RENDERTYPE_VERTEXSHADER | RENDERTYPE_MESH)
#define	RENDERTYPE_MESHONLY			(RENDERTYPE_VERTEXSHADER | RENDERTYPE_MESH)
#define	RENDERTYPE_ENVIROMENT		(RENDERTYPE_MESH)
#define	RENDERTYPE_CASTSHADOW		(RENDERTYPE_SHADOWVOLUME)

// Font creation flags
#define D3DFONT_BOLD        0x0001
#define D3DFONT_ITALIC      0x0002
#define D3DFONT_ZENABLE     0x0004

// Font rendering flags
#define D3DFONT_CENTERED_X  0x0001
#define D3DFONT_CENTERED_Y  0x0002
#define D3DFONT_TWOSIDED    0x0004
#define D3DFONT_FILTERED    0x0008
