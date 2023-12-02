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
// CGResource::Texture::CCube
//
// 1. CGResource::Texture::CCube는...
//    1) 이음...
//    2) Linked List라든지 혹은 Array의 구조는 체택하지 않는다! 이유는 Modify와
//
//
// 2. CGResource::Texture::CCube의 기능 설명
//    1) ()	외부에서 Render를 요구할 때 호출하는 함수이다.
//								내주적으로 ()함수를 호출하도록 되어 있다.
//    2) ()	Rendering의 절차를 정의하는 함수이다.
//								이 class를 상속받아 이 함수를 재정의하는 것이 핵심이다.
//	  3) Renderable Status 함수들
//		 - Renderable을 Enable/Disble하는 함수이다. 또 그 상태를 얻을 수 있는
//         함수들이다.
//
//
//-----------------------------------------------------------------------------
namespace CGResource
{
namespace Texture
{

class CCube : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGResource::ITexture					// (I) Texture Base
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCube();
			CCube(const CCube& p_rCube);
	virtual ~CCube();

public:
			CCube(UINT p_dwEdgeLength, UINT p_dwLevels=0, DWORD p_dwUsage=0, D3DFORMAT p_eFormat=D3DFMT_X8R8G8B8, D3DPOOL p_ePool=D3DPOOL_MANAGED);
			CCube(LPCVOID p_pSrcData, UINT p_dwSrcDataSize, UINT p_dwEdgeLength, UINT p_dwMipLevels, DWORD p_dwUsage, D3DFORMAT p_eFormat, D3DPOOL p_ePool, DWORD p_dwFilter, DWORD p_dwMipFilter, D3DCOLOR p_ColorKey);
			CCube(_In_z_ const _CHAR* p_strFileName);
			CCube(_In_z_ const _CHAR_SUB* p_strFileName);
			CCube(_In_z_ const _CHAR* p_strFileName, UINT p_EdgeLength, UINT p_MipLevels, DWORD p_Usage, D3DFORMAT p_eFormat, D3DPOOL p_Pool, DWORD p_Filter, DWORD p_MipFilter, D3DCOLOR p_ColorKey);
			CCube(_In_z_ const _CHAR_SUB* p_strFileName, UINT p_EdgeLength, UINT p_MipLevels, DWORD p_Usage, D3DFORMAT p_eFormat, D3DPOOL p_Pool, DWORD p_Filter, DWORD p_MipFilter, D3DCOLOR p_ColorKey);


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) 생성과 파괴
			void				Create(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool);
			void				Create(LPCVOID p_SrcData, UINT p_SrcDataSize);
			void				CreateFromMemory(LPCVOID p_SrcData, UINT p_SrcDataSize, UINT p_EdgeLength, UINT p_MipLevels, DWORD p_Usage, D3DFORMAT p_Format, D3DPOOL p_Pool, DWORD p_Filter, DWORD p_MipFilter, D3DCOLOR p_ColorKey);
			void				CreateFromFile(_In_z_ const _CHAR* p_FileName);
			void				CreateFromFile(_In_z_ const _CHAR_SUB* p_FileName);
			void				CreateFromFile(_In_z_ const _CHAR* p_strFileName, UINT p_EdgeLength, UINT p_MipLevels, DWORD p_Usage, D3DFORMAT p_eFormat, D3DPOOL p_Pool, DWORD p_Filter, DWORD p_MipFilter, D3DCOLOR p_ColorKey);
			void				CreateFromFile(_In_z_ const _CHAR_SUB* p_strFileName, UINT p_EdgeLength, UINT p_MipLevels, DWORD p_Usage, D3DFORMAT p_eFormat, D3DPOOL p_Pool, DWORD p_Filter, DWORD p_MipFilter, D3DCOLOR p_ColorKey);

	// 2) Load와 Save
			void				LoadCubeTexture(D3DCUBEMAP_FACES p_eFace, UINT p_iLevel, _In_z_ const _CHAR* p_FileName, const ::RECT* p_pDestRect = NULL, const ::RECT* p_pSrcRect = NULL, DWORD p_dwFilter = D3DX_DEFAULT, D3DCOLOR p_colorKey = 0, D3DXIMAGE_INFO* p_pSrcInfo = NULL);
			void				LoadCubeTexture(D3DCUBEMAP_FACES p_eFace, UINT p_iLevel, _In_z_ const _CHAR_SUB* p_FileName, const ::RECT* p_pDestRect = NULL, const ::RECT* p_pSrcRect = NULL, DWORD p_dwFilter = D3DX_DEFAULT, D3DCOLOR p_colorKey = 0, D3DXIMAGE_INFO* p_pSrcInfo = NULL);
			void				LoadCubeTexture(_In_ const _CHAR** p_FileName, UINT p_iLevel = 0);
			void				LoadCubeTexture(_In_ const _CHAR_SUB** p_FileName, UINT p_iLevel = 0);
			void				LoadCubeTexture(_In_z_ const _CHAR* p_FileName0, _In_z_ const _CHAR* p_FileName1, _In_z_ const _CHAR* p_FileName2, _In_z_ const _CHAR* p_FileName3, _In_z_ const _CHAR* p_FileName4, _In_z_ const _CHAR* p_FileName5, _In_ UINT p_iLevel = 0);
			void				LoadCubeTexture(_In_z_ const _CHAR_SUB* p_FileName0, _In_z_ const _CHAR_SUB* p_FileName1, _In_z_ const _CHAR_SUB* p_FileName2, _In_z_ const _CHAR_SUB* p_FileName3, _In_z_ const _CHAR_SUB* p_FileName4, _In_z_ const _CHAR_SUB* p_FileName5, _In_ UINT p_iLevel = 0);

	// 3) Blit function
			void				Blt(const TEXTUREBASE* p_pSrcTexture);

	// 4) 속성 및 정보
			LPDIRECT3DCUBETEXTURE9	GetD3DCubeTexture() const			{	return (LPDIRECT3DCUBETEXTURE9)m_pD3DTexture;}

			CGPTR<SURFACE>		GetSurface(D3DCUBEMAP_FACES p_eFace, UINT p_iLevel) const;
			void				GetLevelDesc(UINT p_iLevel, D3DSURFACE_DESC* p_pDesc) const;

	// 5) DirtyRect
			void				AddDirtyRect(D3DCUBEMAP_FACES p_eFacetype, const ::RECT* p_pDirtyRect);

	// 6) Lock & Unlock
			void				LockRect(D3DCUBEMAP_FACES p_eFacetype, UINT p_dwLevel, D3DLOCKED_RECT* p_pLockedRect, const ::RECT* p_pRect, DWORD p_dwFlags);
			void				UnlockRect(D3DCUBEMAP_FACES p_eFacetype, UINT p_dwLevel);

	// 7) Operator overriding
			CCube&				operator=(const CCube& p_rhs)			{	Duplicate(p_rhs); return *this;}
			CCube&				operator=(const TEXTUREBASE& p_rhs)		{	Duplicate(p_rhs); return *this;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
private:
	// 1) Restorable
	virtual BOOL				Restore();
};


}
}