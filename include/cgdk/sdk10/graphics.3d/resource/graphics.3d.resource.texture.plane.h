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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGResource::Texture::CPlane
//
// 1. CGResource::Texture::CPlane��...
//    1) ����...
//    2) Linked List����� Ȥ�� Array�� ������ ü������ �ʴ´�! ������ Modify��
//
//
// 2. CGResource::Texture::CPlane�� ��� ����
//    1) ()	�ܺο��� Render�� �䱸�� �� ȣ���ϴ� �Լ��̴�.
//								���������� ()�Լ��� ȣ���ϵ��� �Ǿ� �ִ�.
//    2) ()	Rendering�� ������ �����ϴ� �Լ��̴�.
//								�� class�� ��ӹ޾� �� �Լ��� �������ϴ� ���� �ٽ��̴�.
//	  3) Renderable Status �Լ���
//		 - Renderable�� Enable/Disble�ϴ� �Լ��̴�. �� �� ���¸� ���� �� �ִ�
//         �Լ����̴�.
//
//
//-----------------------------------------------------------------------------
namespace CGResource
{
namespace Texture
{

class CPlane : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGResource::ITexture					// (I) Texture Base
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CPlane();
			CPlane(const CPlane& p_rPlane);
	virtual ~CPlane();

public:
			CPlane(UINT p_Width, UINT p_Height, UINT p_Level=0, DWORD p_Usage=0, D3DFORMAT p_Format=D3DFMT_X8R8G8B8, D3DPOOL p_Pool=D3DPOOL_MANAGED);
			CPlane(_In_z_ const _CHAR* p_FileName);
			CPlane(_In_z_ const _CHAR_SUB* p_FileName);
			CPlane(LPCVOID p_SrcData, UINT p_SrcDataSize, UINT p_Width, UINT p_Height, UINT p_MipLevels, DWORD p_Usage, D3DFORMAT p_Format, D3DPOOL p_Pool, DWORD p_Filter, DWORD p_MipFilter, D3DCOLOR p_ColorKey);


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) ������ �ı�
			void				Create(UINT p_Width, UINT p_Height, UINT p_Level, DWORD p_Usage, D3DFORMAT p_Format=D3DFMT_X8R8G8B8, D3DPOOL p_Pool=D3DPOOL_MANAGED);
			void				Create(LPCVOID p_SrcData, UINT p_SrcDataSize);
			void				CreateFromMemory(LPCVOID p_SrcData, UINT p_SrcDataSize, UINT p_Width, UINT p_Height, UINT p_MipLevels, DWORD p_Usage, D3DFORMAT p_Format, D3DPOOL p_Pool, DWORD p_Filter, DWORD p_MipFilter, D3DCOLOR p_ColorKey);
			void				CreatePlaneTextureFromFile(_In_z_ const _CHAR* p_strFileName, UINT p_Width, UINT p_Height, UINT p_MipLevels, DWORD p_Usage, D3DFORMAT p_eFormat, D3DPOOL p_Pool, DWORD p_Filter, DWORD p_MipFilter, D3DCOLOR p_ColorKey);
			void				CreatePlaneTextureFromFile(_In_z_ const _CHAR_SUB* p_strFileName, UINT p_Width, UINT p_Height, UINT p_MipLevels, DWORD p_Usage, D3DFORMAT p_eFormat, D3DPOOL p_Pool, DWORD p_Filter, DWORD p_MipFilter, D3DCOLOR p_ColorKey);
			void				CreateAsRenderTarget(UINT p_Width, UINT p_Height, DWORD p_dwUsage=0, D3DFORMAT p_Format=D3DFMT_A32B32G32R32F)	{	return Create(p_Width, p_Height, 0, D3DUSAGE_RENDERTARGET | p_dwUsage, p_Format, D3DPOOL_DEFAULT);}
			void				CreateAsRenderTargetAsFloat4(UINT p_Width, UINT p_Height, DWORD p_dwUsage=0)	{	return CreateAsRenderTarget(p_Width, p_Height, p_dwUsage, D3DFMT_A32B32G32R32F);}
			void				CreateAsRenderTargetAsGeneral(UINT p_Width, UINT p_Height, DWORD p_dwUsage=0)	{	return CreateAsRenderTarget(p_Width, p_Height, p_dwUsage, D3DFMT_X8R8G8B8);}
			void				Duplicate(const CGResource::Texture::CPlane& p_rTexturePlane);

	// 2) Apply to Render Target
			void				ApplyToRenderTarget(int p_iLayer);

	// 3) Blit function
			void				Blt(const CGResource::Texture::CPlane* p_pSrcTexture);

	// 4) �Ӽ� �� ����
			LPDIRECT3DTEXTURE9	GetD3DTexture() const					{	return (LPDIRECT3DTEXTURE9)m_pD3DTexture;}

	// 5) Texture Functions
			CGPTR<SURFACE>		GetSurface(UINT p_dwLevel) const;
			void				GetLevelDesc(UINT p_dwLevel, D3DSURFACE_DESC* p_pDesc) const;

	// 6) DirtyRect
			void				AddDirtyRect(const ::RECT* p_pDirtyRect);

	// 7) Lock & Unlock
			void				LockRect(UINT p_dwLevel, D3DLOCKED_RECT* p_pLockedRect, const ::RECT* p_pRect, DWORD p_dwFlags);
			void				UnlockRect(UINT p_dwLevel);

	// 8) Operator overriding
			CPlane&				operator=(const CPlane& p_rhs)			{	Duplicate(p_rhs); return *this;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
private:
	// 1) Restorable
	virtual BOOL				Restore();
};


}
}