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
// 1. CGResource::CSurface��!
//    1) D3D�� Surface ���� Class�̴�.
//    2) ��ü������ Surface�� �����ϰų� Texture�� ���� ���� Surface�� �����Ѵ�.
//    3) �ҷ��� ����ó���� ������ �Ͽ����Ƿ� Socket Manager�� Socket Pool ����
//    4) Surface�� RenderTarget�̳� DepthStencil Buffer�� Apply��ų �� �ִ�.
//
// 2. CGResource::CSurface
//    1) Ư���� ���� ����...
//
// 3. ���� ����
//    * Ư���� ����.
//
//-----------------------------------------------------------------------------
namespace CGResource
{

class CSurface : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGResource,							// (I) Resource Base
	public						CGNameable::NString,					// (@) Nameable	
	virtual public				CGResource::IRestorable,				// (I) Restorable
	public						ICGDeviceGraphic						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CSurface();
			CSurface(const CSurface& p_rSurface);
	virtual	~CSurface();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) ������ �ı�
			void				Create(int p_iWidth, int p_iHeight);
			void				CreateAsRendertarget(int p_iWidth, int p_iHeight, D3DFORMAT Format=D3DFMT_X8R8G8B8, D3DMULTISAMPLE_TYPE MultiSample=D3DMULTISAMPLE_NONE, DWORD MultisampleQuality=0, BOOL Lockable=FALSE);
			void				CreateAsDepthStencil(int p_iWidth, int p_iHeight, D3DFORMAT Format=D3DFMT_D24S8, D3DMULTISAMPLE_TYPE MultiSample=D3DMULTISAMPLE_NONE, DWORD MultisampleQuality=0, BOOL Discard=FALSE);
			void				Duplicate(const CSurface& p_rSurface);
	virtual	void				Destroy();

	// 2) Load�� Save
			void				SaveToFile(_In_z_ const _CHAR* p_strFileName, D3DXIMAGE_FILEFORMAT p_FileType = D3DXIFF_BMP, const ::RECT* p_pSrcRect = NULL);
			void				SaveToFile(_In_z_ const _CHAR_SUB* p_strFileName, D3DXIMAGE_FILEFORMAT p_FileType = D3DXIFF_BMP, const ::RECT* p_pSrcRect = NULL);
			void				SaveToFileInMemory(LPD3DXBUFFER* p_ppDestBuf, D3DXIMAGE_FILEFORMAT p_FileType=D3DXIFF_BMP, const ::RECT* p_pSrcRect=NULL);
			void				LoadFromFile(_In_z_ const _CHAR* p_strFileName, const ::RECT* p_pDestRect=NULL, const ::RECT* p_pSrcRect=NULL, DWORD p_dwFilter=D3DX_DEFAULT, D3DCOLOR p_colorKey=0, D3DXIMAGE_INFO* p_pSrcInfo=NULL);
			void				LoadFromFile(_In_z_ const _CHAR_SUB* p_strFileName, const ::RECT* p_pDestRect = NULL, const ::RECT* p_pSrcRect = NULL, DWORD p_dwFilter = D3DX_DEFAULT, D3DCOLOR p_colorKey = 0, D3DXIMAGE_INFO* p_pSrcInfo = NULL);
			void				LoadFromFileInMemory(LPCVOID p_pSrcData, UINT p_SizeSrcData, const ::RECT* p_pDestRect=NULL, const ::RECT* pSrcRect=NULL, DWORD p_dwFilter=D3DX_DEFAULT, D3DCOLOR p_colorKey=0, D3DXIMAGE_INFO* p_pSrcInfo=NULL);
			void				LoadFromMemory(LPCVOID p_pSrcMemory, D3DFORMAT p_SrcFormat, UINT p_dwSrcPitch, const ::RECT* p_pDestRect=NULL, const ::RECT* p_pSrcRect=NULL, DWORD p_dwFilter=D3DX_DEFAULT, D3DCOLOR p_colorKey=0);

	// 3) ����
			void				Blt(const POINT* p_pDestPoint, const CSurface* p_pSrcSurface, const ::RECT* p_pSrcRect=NULL) const;
			void				Blt(int p_X, int p_Y, const CSurface* p_pSrcSurface, const ::RECT* p_pSrcRect=NULL) const	{	POINT tempPoint={p_X,p_Y}; return Blt(&tempPoint, p_pSrcSurface, p_pSrcRect);}
			void				Blt(const ::RECT* p_pDestRect, const CSurface* p_pSrcSurface, const ::RECT* p_pSrcRect=NULL, DWORD p_dwFilter=D3DX_DEFAULT, D3DCOLOR p_colorKey=0) const;

	// 4) Apply
			BOOL				ApplyToRenderTarget(int p_Layer) const;
			BOOL				SetFromRenderTarget(int p_Layer);
			BOOL				ApplyToDepthStencil() const;
			BOOL				SetFromDepthStencilSurface();

	// 5) �Ӽ� �� ����
			bool				IsCreated() const						{	return m_pD3DSurface!=nullptr;}
			bool				IsEmpty() const							{	return m_pD3DSurface==nullptr;}

			LPDIRECT3DSURFACE9	GetD3DSurface()	const					{	return m_pD3DSurface;}
			void				GetSurfaceDesc(D3DSURFACE_DESC* p_pDesc) const;

	// 6) Operator
 			CSurface&			operator=(const CSurface& p_rhs)		{	Duplicate(p_rhs); return *this;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
private:
	// 1) Restorable
	virtual BOOL				Restore();

	// 2) Process Render
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override	{	return 0;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
			LPDIRECT3DSURFACE9	m_pD3DSurface;
};


}
