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
// ----------------------------------------------------------------------------
//
// Vertex definitions
//
// ----------------------------------------------------------------------------
#include "CG3DDataTypeBase.h"

// 새로 추가한 FVF임 Normal Map용 BiNormal
#define D3DFVF_BINORMAL			0x2000


typedef	WORD	INDEX_SIZE, *LPINDEX_SIZE, &RPINDEX_SIZE;

namespace CG3D
{
namespace VERTEX
{

typedef struct _SHX
{
	DWORD		dwFlags;        /* Homogeneous clipping flags */
	VECTOR3		Position;
} HX, *LPHX, &RPHX;


typedef struct _SXCST
{
	enum { FVF = (D3DFVF_XYZ) };

	VECTOR3		Position;

	COLOR		Color;         /* Vertex color */
	COLOR		Specular;      /* Specular component of vertex */

	VECTOR2		Tex;

} XCST, *LPXCST, &RPXCST;






typedef struct _SX
{
	enum { FVF = (D3DFVF_XYZ) };

	VECTOR3		Position;
} X, *LPX, &RPX;


typedef struct _SXT1
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_TEX1) };

	VECTOR3		Position;

	VECTOR2		Tex;
} XT1, *LPXT1, &RPXT1;


typedef struct _SXC
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE) };

	VECTOR3		Position;

	COLOR		Color;
} XC, *LPXC, &RPXC;



typedef struct _SXW
{
	enum { FVF = (D3DFVF_XYZRHW) };

	VECTOR4		Position;
} XW, *LPXW, &RPXW;


typedef struct _SXWT1
{
	enum { FVF = (D3DFVF_XYZRHW | D3DFVF_TEX1) };

	VECTOR4		Position;

	VECTOR2		Tex;
} XWT1, *LPXWT1, &RPXWT1;


typedef struct _SXWC
{
	enum { FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE) };

	VECTOR4		Position;

	COLOR		Color;
} XWC, *LPXWC, &RPXWC;

typedef struct _SXWCT1
{
	enum { FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1) };

	VECTOR4		Position;

	COLOR		Color;

	VECTOR2		Tex;
} XWCT1, *LPXWCT1, &RPXWCT1;

typedef struct _SXWCT2
{
	enum { FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2) };

	VECTOR4		Position;

	COLOR		Color;

	VECTOR2		Tex[2];
} XWCT2, *LPXWCT2, &RPXWCT2;




typedef struct _SCube
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_TEX1) };

	VECTOR3		Position;

	VECTOR3		Tex;
} CUBE, *LPCUBE, &RPCUBE;

typedef struct _SSprite
{
	enum { FVF = (D3DFVF_XYZRHW | D3DFVF_LASTBETA_UBYTE4) };

	VECTOR4		Position;
	DWORD			VertexIndex;
} SPRITE, *LPSPRITE, &RPSPRITE;

//typedef struct _SRelight
//{
//	enum { FVF = (D3DFVF_XYZRHW | D3DFVF_TEX1) };
//
//	VECTOR4		Position;
//	VECTOR2		Tex;
//} RELIGHT, *LPRELIGHT, &RPRELIGHT;


typedef struct _SSpriteT1
{
	enum { FVF = (D3DFVF_XYZRHW | D3DFVF_TEX1) };

	VECTOR4		Position;
	VECTOR2		Tex;
} SPRITE_T1, *LPSPRITE_T1, &RPSPRITE_T1;

typedef struct _SRAY
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_TEX1) };

	VECTOR3		Position;
	DWORD			VertexIndex;
	VECTOR2		Tex;
} RAY, *LPRAY, &RPRAY;

typedef struct _SBILLBOARD
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX2) };

	VECTOR3		Position;

	COLOR		Color;

	VECTOR2		Tex;
	VECTOR2		Offset;
} BILLBOARD, *LPBILLBOARD, &RPBILLBOARD;

typedef struct _SBILLBOARDAXIS
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2) };

	VECTOR3		Position;	// Position

	VECTOR3		Axis;		// Normal대신임...

	COLOR		Color;		// Color

	VECTOR2		Tex;		// Texture좌표.
	VECTOR2		Offset;		// Offset
} BILLBOARDAXIS, *LPBILLBOARDAXIS, &RPBILLBOARDAXIS;

typedef struct _SPOINTSPRITE
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE) };

	VECTOR3		Position;	// Position

	float		PSize;		// Point Size...

	COLOR		Color;		// Color
} POINTSPRITE, *LPPOINTSPRITE, &RPPOINTSPRITE;







// Have No SkinningInfo
// Have No Color
typedef struct _SXN
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL) };

	VECTOR3		Position;

	VECTOR3		Normal;
} XN, *LPXN, &RPLPXN;

typedef struct _SXNT1
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) };

	VECTOR3		Position;

	VECTOR3		Normal;

	VECTOR2		Tex;
} XNT1, *LPXNT1, &RPLPXNT1;

typedef struct _SXNT2
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2) };

	VECTOR3		Position;

	VECTOR3		Normal;

	VECTOR2		Tex[2];
} XNT2, *LPXNT2, &RPXNT2;

typedef struct _SXNT3
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX3) };

	VECTOR3		Position;

	VECTOR3		Normal;

	VECTOR2		Tex[3];
} XNT3, *LPXNT3, &RPXNT3;

typedef struct _SXNT4
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX4) };

	VECTOR3		Position;

	VECTOR3		Normal;

	VECTOR2		Tex[4];
} XNT4, *LPXNT4, &RPXNT4;

typedef struct _SXNT5
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX5) };

	VECTOR3		Position;

	VECTOR3		Normal;

	VECTOR2		Tex[5];
} XNT5, *LPXNT5, &RPXNT5;



// Have BiNormal
typedef struct _SXNBT1
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_BINORMAL | D3DFVF_TEX1) };

	VECTOR3		Position;

	VECTOR3		Normal;
	VECTOR3		BiNormal;

	VECTOR2		Tex;
} XNBT1, *LPXNBT1, &RPLPXNBT1;

typedef struct _SXNBT2
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_BINORMAL | D3DFVF_TEX2) };

	VECTOR3		Position;

	VECTOR3		Normal;
	VECTOR3		BiNormal;

	VECTOR2		Tex[2];
} XNBT2, *LPXNBT2, &RPXNBT2;

typedef struct _SXNBT3
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_BINORMAL | D3DFVF_TEX3) };

	VECTOR3		Position;

	VECTOR3		Normal;
	VECTOR3		BiNormal;

	VECTOR2		Tex[3];
} XNBT3, *LPXNBT3, &RPXNBT3;


typedef struct _SXNC
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE) };

	VECTOR3		Position;

	VECTOR3		Normal;

	COLOR		Color;
} XNC, *LPXNC, &RPLPXNC;



// Have No SkinningInfo
// Have Color

typedef struct _SXNCT1
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) };

	VECTOR3		Position;

	VECTOR3		Normal;

	COLOR		Color;

	VECTOR2		Tex;
} XNCT1, *LPXNCT1, &RPLPXNCT1;


typedef struct _SXNCT2
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2) };

	VECTOR3		Position;

	VECTOR3		Normal;

	COLOR		Color;

	VECTOR2		Tex[2];
} XNCT2, *LPXNCT2, &RPXNCT2;

typedef struct _SXNCT3
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX3) };

	VECTOR3		Position;

	VECTOR3		Normal;

	COLOR		Color;

	VECTOR2		Tex[3];
} XNCT3, *LPXNCT3, &RPXNCT3;

typedef struct _SXNCT4
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX4) };

	VECTOR3		Position;

	VECTOR3		Normal;

	COLOR		Color;

	VECTOR2		Tex[4];
} XNCT4, *LPXNCT4, &RPXNCT4;

typedef struct _SXNCT5
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX5) };

	VECTOR3		Position;

	VECTOR3		Normal;

	COLOR		Color;

	VECTOR2		Tex[5];
} XNCT5, *LPXNCT5, &RPXNCT5;


/*
#define MAX_NUM_VERTICES 50*6
struct FONT2DVERTEX { D3DXVECTOR4 p;   DWORD color;     FLOAT tu, tv; };
struct FONT3DVERTEX { D3DXVECTOR3 p;   D3DXVECTOR3 n;   FLOAT tu, tv; };

#define D3DFVF_FONT2DVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define D3DFVF_FONT3DVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)
inline FONT2DVERTEX InitFont2DVertex( const D3DXVECTOR4& p, D3DCOLOR color,
                                      FLOAT tu, FLOAT tv )
{
    FONT2DVERTEX v;   v.p = p;   v.color = color;   v.tu = tu;   v.tv = tv;
    return v;
}

inline FONT3DVERTEX InitFont3DVertex( const D3DXVECTOR3& p, const D3DXVECTOR3& n,
                                      FLOAT tu, FLOAT tv )
{
    FONT3DVERTEX v;   v.p = p;   v.n = n;   v.tu = tu;   v.tv = tv;
    return v;
}
//*/

// Have Skinning Info
// Have No Color Info
typedef struct _SXB4
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4)};

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;
} XB4, *LPXB4, &RPXB4;

typedef struct _SXB4C
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_DIFFUSE)};

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	COLOR		Color;
} XB4C, *LPXB4C, &RPXB4C;



typedef struct _SXB4NT1
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_TEX1) };

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	VECTOR3		Normal;

	VECTOR2		Tex;
} XB4NT1, *LPXB4NT1, &RPXB4NT1;


typedef struct _SXB4NT2
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_TEX2) };

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	VECTOR3		Normal;

	VECTOR2		Tex[2];
} XB4NT2, *LPXB4NT2, &RPXB4NT2;

typedef struct _SXB4NT3
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_TEX3) };

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	VECTOR3		Normal;

	VECTOR2		Tex[3];
} XB4NT3, *LPXB4NT3, &RPXB4NT3;

typedef struct _SXB4NT4
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_TEX4) };

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	VECTOR3		Normal;

	VECTOR2		Tex[4];
} XB4NT4, *LPXB4NT4, &RPXB4NT4;

typedef struct _SXB4NT5
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_TEX5) };

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	VECTOR3		Normal;

	VECTOR2		Tex[5];
} XB4NT5, *LPXB4NT5, &RPXB4NT5;



// Have BiNormal
typedef struct _SXB4NBT1
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_BINORMAL | D3DFVF_TEX1) };

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	VECTOR3		Normal;
	VECTOR3		BiNormal;

	VECTOR2		Tex;
} XB4NBT1, *LPXB4NBT1, &RPXB4NBT1;

typedef struct _SXB4NBT2
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_BINORMAL | D3DFVF_TEX2) };

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	VECTOR3		Normal;
	VECTOR3		BiNormal;

	VECTOR2		Tex[2];
} XB4NBT2, *LPXB4NBT2, &RPXB4NBT2;





// Have Skinning Info
// Have Color Info
typedef struct _SXB4NCT1
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_TEX1) };

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	VECTOR3		Normal;

	COLOR		Color;

	VECTOR2		Tex;
} XB4NCT1, *LPXB4NCT1, &RPXB4NCT1;

typedef struct _SXB4NCT2
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_TEX2) };

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	VECTOR3		Normal;

	COLOR		Color;

	VECTOR2		Tex[2];
} XB4NCT2, *LPXB4NCT2, &RPXB4NCT2;

typedef struct _SXB4NCT3
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_TEX3) };

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	VECTOR3		Normal;

	COLOR		Color;

	VECTOR2		Tex[3];
} XB4NCT3, *LPXB4NCT3, &RPXB4NCT3;

typedef struct _SXB4NCT4
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_TEX4) };

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	VECTOR3		Normal;

	COLOR		Color;

	VECTOR2		Tex[4];
} XB4NCT4, *LPXB4NCT4, &RPXB4NCT4;

typedef struct _SXB4NCT5
{
	enum { FVF = (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_TEX5) };

	VECTOR3		Position;
	float			Weight[3];
	DWORD			BoneIndex;

	VECTOR3		Normal;

	COLOR		Color;

	VECTOR2		Tex[5];
} XB4NCT5, *LPXB4NCT5, &RPXB4NCT5;


struct PRELIGHTING
{
	VECTOR3	v3Position;

	struct _LIGHT
	{
		VECTOR3	v3Para[7];
	} sLight;
};


}
}