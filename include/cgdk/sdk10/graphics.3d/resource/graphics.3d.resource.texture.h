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
// CGResource::ITexture
//
// 1. CGResource::ITexture��...
//    1) LPD3DBASETEXTURE�� Wrapping�� Deligation class�̴�.
//    2) �������� ������ ��� Deligation���� �����ϸ� �� class�� ����/����/�ı���
//	     ����ϰ� �ȴ�.
//    3) new�� ���� �������ٴ� ���������� ���� ������ Duplicate�� ���� ��������
//       �ǵ��� �Ѵ�.
//    4) ������ ��ġ shared_ptró�� �����Ѵ�.
//
// 2. CGResource::ITexture�� ��� ����
//    1) Create()		�� �״�� Texture�� �����ϴ� ���̴�.
//	  2) Duplicate()	Swallow Copy�� �����ϸ� Reference count�� ������Ų��.
//    3) Destroy()		������ ��� ��ü�� Release�� ����Ѵ�. Reference Count��
//						0�� �Ǳ��������� ���� �ı��� ���� �ʴ´�.
//	  4) D3D Functions
//       - LPD3DBASETEXTURE�� ������ �ִ� Interface��  Wrapping�� �Լ����̴�.
//		 - GetLOD()/SetLOD() ����.. �� �ִ�.
//
//	  5) D3DX Functions
//	     - D3DX���� �������ִ� �߰����� �Լ��̴�. �ַ� Load/Save�� ���õ� ���̴�.
//       - SaveToFile(), SaveFileInMemory() ���...
//
//-----------------------------------------------------------------------------
namespace CGResource
{

class ITexture :
// ****************************************************************************
// 1. ����� Super Class��
// ----------------------------------------------------------------------------
	virtual public				CGResource::IBuffer,					// (I) Buffer Base 
	public						ICGDeviceGraphic						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
// - ���������� ������ �Ұ����ϰ� �ϱ� ���� Constructor�� protected�� �Ѵ�.
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
