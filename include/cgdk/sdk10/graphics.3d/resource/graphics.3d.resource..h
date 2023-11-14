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
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//*****************************************************************************
// Chosanghyun's Game Object!!!! v(` ~ `)v
//*****************************************************************************


//*****************************************************************************
#define	SHADER_OFFSET_CMN								0

#define	SHADER_OFFSET_NRM_CMN							30
#define	SHADER_OFFSET_NRM_NOL							60
#define	SHADER_OFFSET_NRM_PVL							90
#define	SHADER_OFFSET_NRM_PPL							120

#define	SHADER_OFFSET_DFR_CMN							180
#define	SHADER_OFFSET_DFR_NOL							200
#define	SHADER_OFFSET_DFR_PPL							220


//***************************************************************************************
//
// Vertex Shader
//
//***************************************************************************************
// For Normal Common
#define	VS_CMN_SHADOWVOLUME_NORMAL						(SHADER_OFFSET_CMN+  0)
#define	VS_CMN_SHADOWVOLUME_SKINNED						(SHADER_OFFSET_CMN+  1)
#define	VS_CMN_FULL										(SHADER_OFFSET_CMN+  2)
#define	VS_CMN_QUAD										(SHADER_OFFSET_CMN+  3)
#define	VS_CMN_FULL_3									(SHADER_OFFSET_CMN+  4)

// For Normal NoLighting
#define	VS_NRM_NOL_SPRITE								(SHADER_OFFSET_NRM_NOL+  0)
#define	VS_NRM_NOL_RAY									(SHADER_OFFSET_NRM_NOL+  1)
#define	VS_NRM_NOL_SKYBOX								(SHADER_OFFSET_NRM_NOL+  2)
#define	VS_NRM_NOL_NORMAL_COLOR							(SHADER_OFFSET_NRM_NOL+  3)
#define	VS_NRM_NOL_NORMAL_COLOR_SKINNED					(SHADER_OFFSET_NRM_NOL+  4)
#define	VS_NRM_NOL_VERTEX_ONLY							(SHADER_OFFSET_NRM_NOL+  5)
#define	VS_NRM_NOL_VERTEX_ONLY_SKINNED					(SHADER_OFFSET_NRM_NOL+  6)
#define	VS_NRM_NOL_BILLBOARD							(SHADER_OFFSET_NRM_NOL+  7)
#define	VS_NRM_NOL_BILLBOARDAXIS						(SHADER_OFFSET_NRM_NOL+  8)
#define	VS_NRM_NOL_INSTANCE_LINE						(SHADER_OFFSET_NRM_NOL+  9)
#define	VS_NRM_NOL_POINTSPRITE							(SHADER_OFFSET_NRM_NOL+ 10)

// For Normal PVL
#define	VS_NRM_PVL_NORMAL_DEFAULT						(SHADER_OFFSET_NRM_PVL+  0)
#define	VS_NRM_PVL_SKINNED_DEFAULT						(SHADER_OFFSET_NRM_PVL+  1)
#define	VS_NRM_PVL_BUMP_NORMAL_DEFAULT					(SHADER_OFFSET_NRM_PVL+  2)
#define	VS_NRM_PVL_BUMP_SKINNED_DEFAULT					(SHADER_OFFSET_NRM_PVL+  3)
#define	VS_NRM_PVL_ENV_NORMAL_DEFAULT					(SHADER_OFFSET_NRM_PVL+  4)
#define	VS_NRM_PVL_ENV_SKINNED_DEFAULT					(SHADER_OFFSET_NRM_PVL+  5)
#define	VS_NRM_PVL_ENV_BUMP_NORMAL_DEFAULT				(SHADER_OFFSET_NRM_PVL+  6)
#define	VS_NRM_PVL_ENV_BUMP_SKINNED_DEFAULT				(SHADER_OFFSET_NRM_PVL+  7)

// For Normal PPL
#define	VS_NRM_PPL_NORMAL_DEFAULT						(SHADER_OFFSET_NRM_PPL+  0)
#define	VS_NRM_PPL_SKINNED_DEFAULT						(SHADER_OFFSET_NRM_PPL+  2)
#define	VS_NRM_PPL_BUMP_NORMAL_DEFAULT					(SHADER_OFFSET_NRM_PPL+  4)
#define	VS_NRM_PPL_BUMP_SKINNED_DEFAULT					(SHADER_OFFSET_NRM_PPL+  6)
#define	VS_NRM_PPL_ENV_NORMAL_DEFAULT					(SHADER_OFFSET_NRM_PPL+  8)
#define	VS_NRM_PPL_ENV_SKINNED_DEFAULT					(SHADER_OFFSET_NRM_PPL+ 10)
#define	VS_NRM_PPL_ENV_BUMP_NORMAL_DEFAULT				(SHADER_OFFSET_NRM_PPL+ 12)
#define	VS_NRM_PPL_ENV_BUMP_SKINNED_DEFAULT				(SHADER_OFFSET_NRM_PPL+ 14)

// For NoLighting
#define	VS_DFR_NOL_SPRITE								(SHADER_OFFSET_DFR_NOL+  0)
#define	VS_DFR_NOL_RAY									(SHADER_OFFSET_DFR_NOL+  1)
#define	VS_DFR_NOL_SKYBOX								(SHADER_OFFSET_DFR_NOL+  2)
#define	VS_DFR_NOL_VERTEXCOLOR							(SHADER_OFFSET_DFR_NOL+  3)
#define	VS_DFR_NOL_VERTEX_ONLY							(SHADER_OFFSET_DFR_NOL+  4)
#define	VS_DFR_NOL_VERTEX_ONLY_SKINNED					(SHADER_OFFSET_DFR_NOL+  5)



// For Defered (Stage 1- Normal Depth)
#define	VS_LIGHTINGPRE_NORMALDEPTH						(SHADER_OFFSET_DFR_PPL+  0)
#define	VS_LIGHTINGPRE_NORMALDEPTH_BUMP					(SHADER_OFFSET_DFR_PPL+  1)
#define	VS_LIGHTINGPRE_NORMALDEPTH_SKINNED				(SHADER_OFFSET_DFR_PPL+  2)
#define	VS_LIGHTINGPRE_NORMALDEPTH_SKINNED_BUMP			(SHADER_OFFSET_DFR_PPL+  3)
#define	VS_LIGHTINGPRE_NORMALDEPTH_BILLBOARD			(SHADER_OFFSET_DFR_PPL+  4)
#define	VS_LIGHTINGPRE_NORMALDEPTH_BILLBOARDAXIS		(SHADER_OFFSET_DFR_PPL+  5)
#define	VS_LIGHTINGPRE_NORMALDEPTH_RAY					(SHADER_OFFSET_DFR_PPL+  6)
#define	VS_LIGHTINGPRE_NORMALDEPTH_INSTANCING_POINT		(SHADER_OFFSET_DFR_PPL+  7)

// For Defered (Stage 2- Shadow map)
#define	VS_LIGHTINGPRE_SHADOWMAP						(SHADER_OFFSET_DFR_PPL+ 14)
#define	VS_LIGHTINGPRE_SHADOWMAP_SKINNED				(SHADER_OFFSET_DFR_PPL+ 15)
#define	VS_LIGHTINGPRE_SHADOWMAP_RAY					(SHADER_OFFSET_DFR_PPL+ 16)
#define	VS_LIGHTINGPRE_SHADOWMAP_BILLBOARD				(SHADER_OFFSET_DFR_PPL+ 17)
#define	VS_LIGHTINGPRE_SHADOWMAP_BILLBOARD_AXIS			(SHADER_OFFSET_DFR_PPL+ 18)
#define	VS_LIGHTINGPRE_SHADOWMAP_INSTANCING_POINT		(SHADER_OFFSET_DFR_PPL+ 19)

// For Defered (Stage 3- Lighting PrePass)
#define	VS_LIGHTINGPRE_LIGHTING							(SHADER_OFFSET_DFR_PPL+ 26)
#define	VS_LIGHTINGPRE_LIGHTING_INSTANCING				(SHADER_OFFSET_DFR_PPL+ 27)

// For Defered (Stage 4- Main Pass)
#define	VS_LIGHTINGPRE_FORE_MESH						(SHADER_OFFSET_DFR_PPL+ 30)
#define	VS_LIGHTINGPRE_FORE_MESH_BUMP					(SHADER_OFFSET_DFR_PPL+ 31)
#define	VS_LIGHTINGPRE_FORE_MESH_BUMP_ENV				(SHADER_OFFSET_DFR_PPL+ 32)
#define	VS_LIGHTINGPRE_FORE_MESH_ENV					(SHADER_OFFSET_DFR_PPL+ 33)
#define	VS_LIGHTINGPRE_FORE_MESHSKINNED					(SHADER_OFFSET_DFR_PPL+ 34)
#define	VS_LIGHTINGPRE_FORE_MESHSKINNED_BUMP			(SHADER_OFFSET_DFR_PPL+ 35)
#define	VS_LIGHTINGPRE_FORE_MESHSKINNED_BUMP_ENV		(SHADER_OFFSET_DFR_PPL+ 36)
#define	VS_LIGHTINGPRE_FORE_MESHSKINNED_ENV				(SHADER_OFFSET_DFR_PPL+ 37)
#define	VS_LIGHTINGPRE_FORE_BILLBOARD					(SHADER_OFFSET_DFR_PPL+ 38)
#define	VS_LIGHTINGPRE_FORE_BILLBOARD_AXIS				(SHADER_OFFSET_DFR_PPL+ 39)
#define	VS_LIGHTINGPRE_FORE_INSTANCING_LINE				(SHADER_OFFSET_DFR_PPL+ 40)
#define	VS_LIGHTINGPRE_FORE_INSTANCING_POINTSPRITE		(SHADER_OFFSET_DFR_PPL+ 41)
#define	VS_LIGHTINGPRE_FORE_INSTANCING_RAY				(SHADER_OFFSET_DFR_PPL+ 42)



//***************************************************************************************
//
// Pixel Shader
//
//***************************************************************************************
// For Normal Common
#define	PS_CMN_GLOW_FIRST								(SHADER_OFFSET_CMN+  0)
#define	PS_CMN_GLOW_PASS								(SHADER_OFFSET_CMN+  1)
#define	PS_CMN_GLOW_LAST								(SHADER_OFFSET_CMN+  2)
#define	PS_CMN_SSAO										(SHADER_OFFSET_CMN+  3)

// For Normal NoLighting
#define	PS_NRM_NOL_RAY									(SHADER_OFFSET_NRM_NOL+  0)
#define	PS_NRM_NOL_LINE									(SHADER_OFFSET_NRM_NOL+  1)
#define	PS_NRM_NOL_VERTEXCOLOR							(SHADER_OFFSET_NRM_NOL+  2)
#define	PS_NRM_NOL_SPRITE								(SHADER_OFFSET_NRM_NOL+  3)
#define	PS_NRM_NOL_CONSTANT								(SHADER_OFFSET_NRM_NOL+  4)
#define	PS_NRM_NOL_SKYBOX								(SHADER_OFFSET_NRM_NOL+  5)
#define	PS_NRM_NOL_PARTICLE								(SHADER_OFFSET_NRM_NOL+  6)

// For Normal PVL
#define	PS_NRM_PVL_NORMAL_T0							(SHADER_OFFSET_NRM_PVL+  0)
#define	PS_NRM_PVL_NORMAL_T1							(SHADER_OFFSET_NRM_PVL+  1)
#define	PS_NRM_PVL_NORMAL_T0TLightmap					(SHADER_OFFSET_NRM_PVL+  2)
#define	PS_NRM_PVL_NORMAL_T1TLightmap					(SHADER_OFFSET_NRM_PVL+  3)
#define	PS_NRM_PVL_BUMP_T0								(SHADER_OFFSET_NRM_PVL+  4)
#define	PS_NRM_PVL_BUMP_T1								(SHADER_OFFSET_NRM_PVL+  5)
#define	PS_NRM_PVL_ENV_T0								(SHADER_OFFSET_NRM_PVL+  6)
#define	PS_NRM_PVL_ENV_T1								(SHADER_OFFSET_NRM_PVL+  7)
#define	PS_NRM_PVL_BUMPENV_T0							(SHADER_OFFSET_NRM_PVL+  8)
#define	PS_NRM_PVL_BUMPENV_T1							(SHADER_OFFSET_NRM_PVL+  9)

// For Normal PPL
#define	PS_NRM_PPL_NORMAL_T0							(SHADER_OFFSET_NRM_PPL+  0)
#define	PS_NRM_PPL_NORMAL_T1							(SHADER_OFFSET_NRM_PPL+  2)
#define	PS_NRM_PPL_NORMAL_T0TLightmap					(SHADER_OFFSET_NRM_PPL+  4)
#define	PS_NRM_PPL_NORMAL_T1TLightmap					(SHADER_OFFSET_NRM_PPL+  6)
#define	PS_NRM_PPL_BUMP_T0								(SHADER_OFFSET_NRM_PPL+  8)
#define	PS_NRM_PPL_BUMP_T1								(SHADER_OFFSET_NRM_PPL+ 10)
#define	PS_NRM_PPL_ENV_T0								(SHADER_OFFSET_NRM_PPL+ 12)
#define	PS_NRM_PPL_ENV_T1								(SHADER_OFFSET_NRM_PPL+ 14)
#define	PS_NRM_PPL_BUMPENV_T0							(SHADER_OFFSET_NRM_PPL+ 16)
#define	PS_NRM_PPL_BUMPENV_T1							(SHADER_OFFSET_NRM_PPL+ 18)
#define	PS_NRM_PPL_NORMALSPECULAR_T0					(SHADER_OFFSET_NRM_PPL+ 20)
#define	PS_NRM_PPL_NORMALSPECULAR_T1					(SHADER_OFFSET_NRM_PPL+ 22)
#define	PS_NRM_PPL_BUMPSPECULAR_T0						(SHADER_OFFSET_NRM_PPL+ 24)
#define	PS_NRM_PPL_BUMPSPECULAR_T1						(SHADER_OFFSET_NRM_PPL+ 26)
#define	PS_NRM_PPL_ENVSPECULAR_T0						(SHADER_OFFSET_NRM_PPL+ 28)
#define	PS_NRM_PPL_ENVSPECULAR_T1						(SHADER_OFFSET_NRM_PPL+ 30)
#define	PS_NRM_PPL_BUMPENVSPECULAR_T0					(SHADER_OFFSET_NRM_PPL+ 32)
#define	PS_NRM_PPL_BUMPENVSPECULAR_T1					(SHADER_OFFSET_NRM_PPL+ 34)
#define	PS_NRM_PPL_EMISSIVE_ONLY						(SHADER_OFFSET_NRM_PPL+ 35)



// For Defered (Stage 1- Normal Depth)
#define	PS_LIGHTINGPRE_NORMALDEPTH						(SHADER_OFFSET_DFR_PPL+  0)
#define	PS_LIGHTINGPRE_NORMALDEPTH_BUMP					(SHADER_OFFSET_DFR_PPL+  1)

// For Defered (Stage 2- Shadow map)
#define	PS_LIGHTINGPRE_SHADOWMAP						(SHADER_OFFSET_DFR_PPL+  2)

// For Defered (Stage 3- Light PrePass)
#define	PS_LIGHTINGPRE_LIGHTING_DIRECTIONAL				(SHADER_OFFSET_DFR_PPL+  3)
#define	PS_LIGHTINGPRE_LIGHTING_POINT					(SHADER_OFFSET_DFR_PPL+  4)
#define	PS_LIGHTINGPRE_LIGHTING_SPOT					(SHADER_OFFSET_DFR_PPL+  5)
#define	PS_LIGHTINGPRE_LIGHTING_INSTANCING_DIRECTIONAL	(SHADER_OFFSET_DFR_PPL+  6)
#define	PS_LIGHTINGPRE_LIGHTING_INSTANCING_POINT_SPOT	(SHADER_OFFSET_DFR_PPL+  7)

// For Defered (Stage 4- Main Pass)
#define	PS_LIGHTINGPRE_FORE_T0							(SHADER_OFFSET_DFR_PPL+  8)
#define	PS_LIGHTINGPRE_FORE_T1							(SHADER_OFFSET_DFR_PPL+  9)
#define	PS_LIGHTINGPRE_FORE_BUMP_T0						(SHADER_OFFSET_DFR_PPL+ 10)
#define	PS_LIGHTINGPRE_FORE_BUMP_T1						(SHADER_OFFSET_DFR_PPL+ 11)
#define	PS_LIGHTINGPRE_FORE_BUMPENV_T0					(SHADER_OFFSET_DFR_PPL+ 12)
#define	PS_LIGHTINGPRE_FORE_BUMPENV_T1					(SHADER_OFFSET_DFR_PPL+ 13)
#define	PS_LIGHTINGPRE_FORE_BUMPENVSPECULAR_T0			(SHADER_OFFSET_DFR_PPL+ 14)
#define	PS_LIGHTINGPRE_FORE_BUMPENVSPECULAR_T1			(SHADER_OFFSET_DFR_PPL+ 15)
#define	PS_LIGHTINGPRE_FORE_BUMPSPECULAR_T0				(SHADER_OFFSET_DFR_PPL+ 16)
#define	PS_LIGHTINGPRE_FORE_BUMPSPECULAR_T1				(SHADER_OFFSET_DFR_PPL+ 17)
#define	PS_LIGHTINGPRE_FORE_ENV_T0						(SHADER_OFFSET_DFR_PPL+ 18)
#define	PS_LIGHTINGPRE_FORE_ENV_T1						(SHADER_OFFSET_DFR_PPL+ 19)
#define	PS_LIGHTINGPRE_FORE_ENVSPECULAR_T0				(SHADER_OFFSET_DFR_PPL+ 20)
#define	PS_LIGHTINGPRE_FORE_ENVSPECULAR_T1				(SHADER_OFFSET_DFR_PPL+ 21)
#define	PS_LIGHTINGPRE_FORE_SPECULAR_T0					(SHADER_OFFSET_DFR_PPL+ 22)
#define	PS_LIGHTINGPRE_FORE_SPECULAR_T1					(SHADER_OFFSET_DFR_PPL+ 23)
#define	PS_LIGHTINGPRE_FORE_LIGHTMAP_T0					(SHADER_OFFSET_DFR_PPL+ 24)
#define	PS_LIGHTINGPRE_FORE_LIGHTMAP_T1					(SHADER_OFFSET_DFR_PPL+ 25)
