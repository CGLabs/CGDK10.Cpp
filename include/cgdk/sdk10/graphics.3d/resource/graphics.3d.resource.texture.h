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
// CGResource::ITexture
//
// 1. CGResource::ITexture는...
//    1) LPD3DBASETEXTURE를 Wrapping한 Deligation class이다.
//    2) 내부적인 동작은 모두 Deligation으로 동작하며 이 class는 생성/복사/파괴를
//	     담당하게 된다.
//    3) new를 통한 생성보다는 지역변수에 의한 생성과 Duplicate를 통해 동적관리
//       되도록 한다.
//    4) 동작은 마치 shared_ptr처럼 동작한다.
//
// 2. CGResource::ITexture의 기능 설명
//    1) Create()		말 그대로 Texture를 생성하는 것이다.
//	  2) Duplicate()	Swallow Copy를 수행하며 Reference count를 증가시킨다.
//    3) Destroy()		생성된 대상 객체의 Release를 담당한다. Reference Count가
//						0이 되기전까지는 실제 파괴를 하지 않는다.
//	  4) D3D Functions
//       - LPD3DBASETEXTURE가 가지고 있는 Interface를  Wrapping한 함수들이다.
//		 - GetLOD()/SetLOD() 등등등.. 이 있다.
//
//	  5) D3DX Functions
//	     - D3DX에서 제공해주는 추가적인 함수이다. 주로 Load/Save에 관련된 것이다.
//       - SaveToFile(), SaveFileInMemory() 등등...
//
//-----------------------------------------------------------------------------
namespace CGResource
{

class ITexture :
// ****************************************************************************
// 1. 상속한 Super Class들
// ----------------------------------------------------------------------------
	virtual public				CGResource::IBuffer,					// (I) Buffer Base 
	public						ICGDeviceGraphic						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
// - 독자적으로 생성을 불가능하게 하기 위해 Constructor를 protected로 한다.
public:
			 ITexture();
			 ITexture(const ITexture& p_rTexture);
	virtual	~ITexture();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Destroy
			void				CreateFromFile(_In_z_ const _CHAR* p_strFileName);
			void				CreateFromFile(_In_z_ const _CHAR_SUB* p_strFileName);
			void				CreateFromFileInMemory(const void* p_pSrcData, DWORD p_dwSrcSize);
			void				Duplicate(const ITexture& p_rTexture);
	virtual	void				Destroy();

	// 2) Apply
			HRESULT				ApplyTexture(int p_iStage=0) const		{	return m_lpDirect3DDevice->SetTexture(p_iStage, m_pD3DTexture);}

	// 3) Members
			LPD3DBASETEXTURE	GetD3DTexture() const					{	return m_pD3DTexture;}

	// 4) Mip-map Attribute
			DWORD				GetLOD() const							{	return m_pD3DTexture->GetLOD();}
			DWORD				SetLOD(DWORD p_dwLODNew)				{	return m_pD3DTexture->SetLOD(p_dwLODNew);}
			DWORD				GetLevelCount() const					{	return m_pD3DTexture->GetLevelCount();}
			void				GenerateMipmapLevel() const;
			void				SetAutoGenFilterType(D3DTEXTUREFILTERTYPE p_eFilterType);
			D3DTEXTUREFILTERTYPE GetAutoGenFilterType() const			{	return m_pD3DTexture->GetAutoGenFilterType();}

	// 5) Save to File 
			void				SaveToFile(_In_z_ const _CHAR* _strDestFile, D3DXIMAGE_FILEFORMAT p_destFormat=D3DXIFF_DDS);
			void				SaveToFile(_In_z_ const _CHAR_SUB* _strDestFile, D3DXIMAGE_FILEFORMAT p_destFormat=D3DXIFF_DDS);
			void				SaveToFileInMemory(LPD3DXBUFFER* p_ppDestBuf, D3DXIMAGE_FILEFORMAT p_destFormat=D3DXIFF_DDS);

	// 6) Attributes
			bool				IsCreated() const						{	return m_pD3DTexture!=NULL;}
			bool				IsDestroyed() const						{	return m_pD3DTexture==NULL;}

	// 7) Operator overriding
			ITexture&			operator=(const ITexture& p_rhs)		{	Duplicate(p_rhs); return *this;}


// ****************************************************************************
// Protected) 
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override	{	return 0;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			LPD3DBASETEXTURE	m_pD3DTexture;
};


}
