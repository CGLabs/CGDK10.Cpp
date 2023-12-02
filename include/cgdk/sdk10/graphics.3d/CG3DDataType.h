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
// 1. Render Attribute
// ----------------------------------------------------------------------------
#define CGDEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) \
extern "C++" { \
inline ENUMTYPE		operator |	(ENUMTYPE a, ENUMTYPE b)	{ return ENUMTYPE(((uint32_t)a) | (uint32_t)b); } \
inline ENUMTYPE&	operator |= (ENUMTYPE& a, ENUMTYPE b)	{ return (ENUMTYPE &)(((uint32_t &)a) |= (uint32_t)b); } \
inline ENUMTYPE		operator &	(ENUMTYPE a, ENUMTYPE b)	{ return ENUMTYPE(((uint32_t)a) & (uint32_t)b); } \
inline ENUMTYPE&	operator &=	(ENUMTYPE& a, ENUMTYPE b)	{ return (ENUMTYPE &)(((uint32_t &)a) &= (uint32_t)b); } \
inline ENUMTYPE		operator ~	(ENUMTYPE a)				{ return ENUMTYPE(~((uint32_t)a)); } \
inline ENUMTYPE		operator ^	(ENUMTYPE a, ENUMTYPE b)	{ return ENUMTYPE(((uint32_t)a) ^ (uint32_t)b); } \
inline ENUMTYPE&	operator ^= (ENUMTYPE& a, ENUMTYPE b)	{ return (ENUMTYPE &)(((uint32_t &)a) ^= (uint32_t)b); } \
inline ENUMTYPE		operator |	(ENUMTYPE a, uint32_t b)	{ return ENUMTYPE(((uint32_t)a) | (uint32_t)b); } \
inline ENUMTYPE&	operator |= (ENUMTYPE& a, uint32_t b)	{ return (ENUMTYPE &)(((uint32_t &)a) |= (uint32_t)b); } \
inline ENUMTYPE		operator &	(ENUMTYPE a, uint32_t b)	{ return ENUMTYPE(((uint32_t)a) & (uint32_t)b); } \
inline ENUMTYPE&	operator &=	(ENUMTYPE& a, uint32_t b)	{ return (ENUMTYPE &)(((uint32_t &)a) &= (uint32_t)b); } \
inline ENUMTYPE		operator ^	(ENUMTYPE a, uint32_t b)	{ return ENUMTYPE(((uint32_t)a) ^ (uint32_t)b); } \
inline ENUMTYPE&	operator ^=	(ENUMTYPE& a, uint32_t b)	{ return (ENUMTYPE &)(((uint32_t &)a) ^= (uint32_t)b); } \
}

namespace CG3D
{

enum RENDERER_ATTRIBUTE
{
	RENDERER_ATTRIBUTE_NORMAL,
	RENDERER_ATTRIBUTE_SHADOW,
	RENDERER_ATTRIBUTE_BONE,
	RENDERER_ATTRIBUTE_LIGHT
};

// ----------------------------------------------------------------------------
// 2. Render Attribute
// ----------------------------------------------------------------------------
enum RENDER_TYPE
{
	RENDER_TYPE_NONE		 = 0x00000000,		// None
	RENDER_TYPE_DEPTHNORMAL	 = 0x00000001,		// Alpha가 있는 것을 의미함(Alpah의 경우 정렬을 한 다음에 Render해야 함.)
	RENDER_TYPE_GENERAL		 = 0x00000002,		// 일반적인 Renderer를 의미함.
	RENDER_TYPE_FORE		 = 0x00000002,		// Fore Rendering을 의미함.
	RENDER_TYPE_ALPHA		 = 0x00000004,		// Alpha가 있는 것을 의미함(Alpah의 경우 정렬을 한 다음에 Render해야 함.)
	RENDER_TYPE_SHADOW		 = 0x00000008,		// 그림자를 의미함.
	RENDER_TYPE_POST		 = 0x00000010,		// Post Effect Renderer임.
	RENDER_TYPE_EXTRA		 = 0x00000020,		// 일반적으로 광원의 영향을 받지 않는 것이나 Text나 보조선과 같은 Object
	RENDER_TYPE_PRELIGHTING	 = 0x00000040,		// Pre-Lighting
	RENDER_TYPE_MODIFY		 = 0x00000100,		// 
	RENDER_TYPE_APPLY		 = 0x00000200,		// 
	RENDER_TYPE_DEFAULT_ALL	 = 0x0000ffff,		// All Default

	RENDER_TYPE_USER_0		 = 0x00010000,		// 
	RENDER_TYPE_USER_1		 = 0x00020000,		// 
	RENDER_TYPE_USER_2		 = 0x00040000,		// 
	RENDER_TYPE_USER_3		 = 0x00080000,		// 
	RENDER_TYPE_USER_4		 = 0x00100000,		// 
	RENDER_TYPE_USER_5		 = 0x00200000,		// 
	RENDER_TYPE_USER_6		 = 0x00300000,		// 
	RENDER_TYPE_USER_7		 = 0x00400000,		// 

	RENDER_TYPE_ALL			 = 0x7fffffff
};
CGDEFINE_ENUM_FLAG_OPERATORS(RENDER_TYPE)

enum APPLIER_TYPE
{
	APPLIER_TYPE_NONE		 = 0x00000000,		// None
	APPLIER_TYPE_GENERAL	 = 0x00000001,		// 일반적인 Light
	APPLIER_TYPE_GLOBAL		 = 0x00000002,		// Global Light

	APPLIER_TYPE_ALL		 = 0xffffffff
};
CGDEFINE_ENUM_FLAG_OPERATORS(APPLIER_TYPE)

enum RENDER_PASS
{
	RENDER_PASS_FORE		 = 0,
	RENDER_PASS_DEPTHNORMAL	 = 1,
	RENDER_PASS_SHADOWMAP	 = 2,
	RENDER_PASS_PRELIGHTING	 = 3,
	RENDER_PASS_POST		 = 4,
	RENDER_PASS_MAX
};
CGDEFINE_ENUM_FLAG_OPERATORS(RENDER_PASS)

}

// ----------------------------------------------------------------------------
// 10. ETC
// ----------------------------------------------------------------------------
typedef	struct IDirect3DVertexBuffer9	D3DVERTEXBUFFER;
typedef	struct IDirect3DIndexBuffer9	D3DINDEXBUFFER;
typedef	struct IDirect3DVertexDeclaration9	D3DVERTEXDECL;

typedef struct IDirect3DVertexShader9	D3DVERTEXSHADER9;
typedef struct IDirect3DPixelShader9	D3DPIXELSHADER9;
typedef struct IDirect3DPixelShader9	D3DPIXELSHADER9;


typedef	D3DVIEWPORT9					USE_D3DVIEWPORT,		*USE_LPD3DVIEWPORT;
typedef	D3DSURFACE_DESC					USE_D3DSURFACEDESC;

namespace CG3D
{

struct BLEND_INFO
{
	float				EffectorWeight;	// Byte  4 :  4
	MATRIX*				Effector;
};

// (Allign 8)
struct VIEW_INFO
{
	float				FOV;			// Byte  4 : 4
	float				fDist;			// Byte  4 : 8
};

// Texture Attribute
enum TEXATTR_MAP
{
	TEXTURE_ATTRIBUTE_MAP_GENERIC,
	TEXTURE_ATTRIBUTE_MAP_AMBIENT,
	TEXTURE_ATTRIBUTE_MAP_DIFFUSE,
	TEXTURE_ATTRIBUTE_MAP_SPECULAR_COLOR,
	TEXTURE_ATTRIBUTE_MAP_SPECULAR_LEVEL,
	TEXTURE_ATTRIBUTE_MAP_SPECULAR_POWER,
	TEXTURE_ATTRIBUTE_MAP_OPACITY,
	TEXTURE_ATTRIBUTE_MAP_BUMP,
	TEXTURE_ATTRIBUTE_MAP_REFLECT,
	TEXTURE_ATTRIBUTE_MAP_REFRACT,
	TEXTURE_ATTRIBUTE_MAP_MONOCHROMELIGHT,
	TEXTURE_ATTRIBUTE_MAP_COLORLIGHT,
	TEXTURE_ATTRIBUTE_MAP_SPECULARLIGHT,
	TEXTURE_ATTRIBUTE_MAP_DIFFUSELIGHT,
	TEXTURE_ATTRIBUTE_MAP_SELFILLUM,
	TEXTURE_ATTRIBUTE_MAP_DISPLACEMENT,
	TEXTURE_ATTRIBUTE_MAP_NORMAL,
	TEXTURE_ATTRIBUTE_MAP_MIP,
	TEXTURE_ATTRIBUTE_OTHER=255
};

struct TEXATTR
{
	// Stage) 
	int					Stage;	// Byte  4 : 40 Texcoord의 Index

	// Texture Type) 
	TEXATTR_MAP			iType;			// Byte  4 : 36 Texture의 Type임
	int					TextureAddress;	// Byte  4 :  8 Texture의 Address임.

	// Amount) 
	VECTOR4				v4Amount;

	int					idxTexture;		// Byte  4 : 56 Texture임.
};


}


#define	CG3DOBJECT_TYPE_MASK		0xff0000

// 1) Resource
#define		CGOBJECTTYPE_RESOURCE							 0x410000
#define		CGOBJECTTYPE_RESOURCE_BUFFER					 (CGOBJECTTYPE_RESOURCE | 0x0000)
#define		CGOBJECTTYPE_RESOURCE_VERTEXBUFFER				 (CGOBJECTTYPE_RESOURCE_BUFFER | 0)
#define		CGOBJECTTYPE_RESOURCE_INDEXBUFFER				 (CGOBJECTTYPE_RESOURCE_BUFFER | 1)
#define		CGOBJECTTYPE_RESOURCE_SHADER					 (CGOBJECTTYPE_RESOURCE | 0x0100)
#define		CGOBJECTTYPE_RESOURCE_VERTEXSHADER				 (CGOBJECTTYPE_RESOURCE_SHADER | 0)
#define		CGOBJECTTYPE_RESOURCE_PIXELSHADER				 (CGOBJECTTYPE_RESOURCE_SHADER | 1)
#define		CGOBJECTTYPE_RESOURCE_MESH						 (CGOBJECTTYPE_RESOURCE | 0x0200)
#define		CGOBJECTTYPE_RESOURCE_MESH_PRIMITIVE			 (CGOBJECTTYPE_RESOURCE_MESH | 0)
#define		CGOBJECTTYPE_RESOURCE_MESH_INDEXEDPRIMITIVE		 (CGOBJECTTYPE_RESOURCE_MESH | 1)
#define		CGOBJECTTYPE_RESOURCE_MESH_TRIPATCH				 (CGOBJECTTYPE_RESOURCE_MESH | 2)
#define		CGOBJECTTYPE_RESOURCE_MESH_RECTPATCH			 (CGOBJECTTYPE_RESOURCE_MESH | 3)
#define		CGOBJECTTYPE_RESOURCE_MESH_DISPLACEMENT			 (CGOBJECTTYPE_RESOURCE_MESH | 4)
#define		CGOBJECTTYPE_RESOURCE_MESH_TERRAIN				 (CGOBJECTTYPE_RESOURCE_MESH | 5)
#define		CGOBJECTTYPE_RESOURCE_TEXTURE					 (CGOBJECTTYPE_RESOURCE | 0x0300)
#define		CGOBJECTTYPE_RESOURCE_SURFACE					 (CGOBJECTTYPE_RESOURCE | 0x0400)
#define		CGOBJECTTYPE_RESOURCE_VERTEXDECL				 (CGOBJECTTYPE_RESOURCE | 0x0500)
#define		CGOBJECTTYPE_RESOURCE_FONT						 (CGOBJECTTYPE_RESOURCE | 0x0600)
#define		CGOBJECTTYPE_RESOURCE_BONEINFO					 (CGOBJECTTYPE_RESOURCE | 0x0700)
#define		CGOBJECTTYPE_RESOURCE_SPRITE					 (CGOBJECTTYPE_RESOURCE | 0x0800)
#define		CGOBJECTTYPE_RESOURCE_SPRITEBUNDLE				 (CGOBJECTTYPE_RESOURCE | 0x0900)
#define		CGOBJECTTYPE_RESOURCE_KEYFRAME					 (CGOBJECTTYPE_RESOURCE | 0x0a00)
#define		CGOBJECTTYPE_RESOURCE_KEYFRAME_TRANSFORM		 (CGOBJECTTYPE_RESOURCE_KEYFRAME)
#define		CGOBJECTTYPE_RESOURCE_KEYFRAME_TRANSFORM_PRESET	 (CGOBJECTTYPE_RESOURCE_KEYFRAME | 1)
#define		CGOBJECTTYPE_RESOURCE_KEYFRAME_VECTOR3			 (CGOBJECTTYPE_RESOURCE_KEYFRAME | 2)
#define		CGOBJECTTYPE_RESOURCE_KEYFRAME_VECTOR4			 (CGOBJECTTYPE_RESOURCE_KEYFRAME | 3)
#define		CGOBJECTTYPE_RESOURCE_KEYFRAME_LIGHT			 (CGOBJECTTYPE_RESOURCE_KEYFRAME | 4)
#define		CGOBJECTTYPE_RESOURCE_KEYFRAME_VIEW				 (CGOBJECTTYPE_RESOURCE_KEYFRAME | 5)
#define		CGOBJECTTYPE_RESOURCE_TIMESET					 (CGOBJECTTYPE_RESOURCE | 0x0b00)
#define		CGOBJECTTYPE_RESOURCE_TIMESET_ARRAY				 (CGOBJECTTYPE_RESOURCE | 0x0c00)
#define		CGOBJECTTYPE_RESOURCE_PLANELIST					 (CGOBJECTTYPE_RESOURCE | 0x0d00)
#define		CGOBJECTTYPE_RESOURCE_SCENEINFO					 (CGOBJECTTYPE_RESOURCE | 0x0e00)

// 2) Modifier
#define		CGOBJECTTYPE_MODIFIER							 0x420000
#define		CGOBJECTTYPE_MODIFIER_LOCALTM					 (CGOBJECTTYPE_MODIFIER | 0x0000)
#define		CGOBJECTTYPE_MODIFIER_KEYFRAME					 (CGOBJECTTYPE_MODIFIER | 0x0100)
#define		CGOBJECTTYPE_MODIFIER_KEYFRAME_LIGHT			 (CGOBJECTTYPE_MODIFIER_KEYFRAME | 0)
#define		CGOBJECTTYPE_MODIFIER_KEYFRAME_TRANSFORM		 (CGOBJECTTYPE_MODIFIER_KEYFRAME | 1)
#define		CGOBJECTTYPE_MODIFIER_KEYFRAME_VIEW				 (CGOBJECTTYPE_MODIFIER_KEYFRAME | 2)
#define		CGOBJECTTYPE_TIMER								 (CGOBJECTTYPE_MODIFIER | 0x0200)
#define		CGOBJECTTYPE_MODIFIER_CONSTRAINT_IK				 (CGOBJECTTYPE_MODIFIER | 0x0300)

// 3) Applier
#define		CGOBJECTTYPE_APPLIER							 0x430000
#define		CGOBJECTTYPE_APPLIER_CAMERA						 (CGOBJECTTYPE_APPLIER | 0x0000)
#define		CGOBJECTTYPE_APPLIER_EFFECT						 (CGOBJECTTYPE_APPLIER | 0x0100)
#define		CGOBJECTTYPE_APPLIER_LIGHT						 (CGOBJECTTYPE_APPLIER | 0x0200)
#define		CGOBJECTTYPE_APPLIER_MATERIAL					 (CGOBJECTTYPE_APPLIER | 0x0300)
#define		CGOBJECTTYPE_APPLIER_TEXTURE					 (CGOBJECTTYPE_APPLIER | 0x0400)
#define		CGOBJECTTYPE_APPLIER_BONEINFO					 (CGOBJECTTYPE_APPLIER | 0x0500)
#define		CGOBJECTTYPE_APPLIER_RENDERTARGET				 (CGOBJECTTYPE_APPLIER | 0x0600)
#define		CGOBJECTTYPE_APPLIER_VERTEXSTREAM				 (CGOBJECTTYPE_APPLIER | 0x0700)
#define		CGOBJECTTYPE_APPLIER_STATEBLOCK					 (CGOBJECTTYPE_APPLIER | 0x0800)
#define		CGOBJECTTYPE_APPLIER_SCENEINFO					 (CGOBJECTTYPE_APPLIER | 0x0900)

// 4) Renderer
#define		CGOBJECTTYPE_RENDERER							 0x440000
#define		CGOBJECTTYPE_RENDERER_MESH						 (CGOBJECTTYPE_RENDERER | 0x0000)
#define		CGOBJECTTYPE_RENDERER_WIRE						 (CGOBJECTTYPE_RENDERER | 0x0100)
#define		CGOBJECTTYPE_RENDERER_TEXT						 (CGOBJECTTYPE_RENDERER | 0x0200)
#define		CGOBJECTTYPE_RENDERER_BILLBOARD					 (CGOBJECTTYPE_RENDERER | 0x0300)
#define		CGOBJECTTYPE_RENDERER_PARTICLE					 (CGOBJECTTYPE_RENDERER | 0x0400)
#define		CGOBJECTTYPE_RENDERER_RAY						 (CGOBJECTTYPE_RENDERER | 0x0500)
#define		CGOBJECTTYPE_RENDERER_SKYBOX					 (CGOBJECTTYPE_RENDERER | 0x0600)
#define		CGOBJECTTYPE_RENDERER_VIEW						 (CGOBJECTTYPE_RENDERER | 0x0700)

// 5) Scenenode
#define		CGOBJECTTYPE_SCENENODE							 0x450000
#define		CGOBJECTTYPE_SCENENODE_VIEW						 (CGOBJECTTYPE_SCENENODE | 0x0100)
#define		CGOBJECTTYPE_SCENENODE_PORTAL					 (CGOBJECTTYPE_SCENENODE | 0x0200)
#define		CGOBJECTTYPE_SCENENODE_GRAPH					 (CGOBJECTTYPE_SCENENODE | 0x0400)
#define		CGOBJECTTYPE_SCENENODE_TREE						 (CGOBJECTTYPE_SCENENODE | 0x0800)

// 6) UI
#define		CGOBJECTTYPE_UI									 0x460000
#define		CGOBJECTTYPE_UI_STATIC							 (CGOBJECTTYPE_UI | 0x0100)
#define		CGOBJECTTYPE_UI_EDIT							 (CGOBJECTTYPE_UI | 0x0200)
#define		CGOBJECTTYPE_UI_BUTTON							 (CGOBJECTTYPE_UI | 0x0300)
#define		CGOBJECTTYPE_UI_LIST							 (CGOBJECTTYPE_UI | 0x0400)
#define		CGOBJECTTYPE_UI_SCROLLBAR						 (CGOBJECTTYPE_UI | 0x0500)
#define		CGOBJECTTYPE_UI_SLIDER							 (CGOBJECTTYPE_UI | 0x0600)
#define		CGOBJECTTYPE_UI_COMBO							 (CGOBJECTTYPE_UI | 0x0700)
#define		CGOBJECTTYPE_UI_FORM							 (CGOBJECTTYPE_UI | 0x0800)
