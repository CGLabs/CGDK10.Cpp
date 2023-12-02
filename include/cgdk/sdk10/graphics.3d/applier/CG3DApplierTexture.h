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
// CG3DApplier::CTexture
//
// 1. CG3DApplier::CTexture��...
//    1) ���� ���� Texture�� ������ �ɼǿ� ���� �����ϴ� ����� ���� Class 
//    2) ���� Stage�� Texture�� ���� �� �ִ�.
//    3) �ϳ��� Stage�� �ش� Stage�� ���� parameter�� Texture�� �ִ�.
//    4) ���������δ� ��ü �޸𸮸� �Ҵ��Ҽ� ������ Shared Memory�� �����Ѵ�.
//    5) ���� Create/Duplicate/Delete�� �����Ѵ�.
//
// 2. CG3DApplier::CTexture�� �ٽ�!
//    1) Close()...	�ݴ� �Լ�. Open()�� �پ��Ҽ� �ֱ� ������ virtual�� �������� �ʴ´�.
//	  2) SetStatus()/GetStatus()
//		 ����� Status�� �����ϰ� ��� �Լ�.
//
// 3. Use Method
//	  1) Deligation	(Optimized)
//	  2) Pointing	(Useful)
//
// 3. ���� ����
//    ��... -_-;;
//
//-----------------------------------------------------------------------------
namespace CG3DApplier
{

class CTexture : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DApplier,							// (I) Applier
	public						ICGDeviceGraphic						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTexture();
	virtual	~CTexture();

public:
			CTexture(int p_nTextureStage);


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Create/Destroy
			void				Create(int nTextureStage);
			void				Create(_In_z_ const _CHAR* p_strFileName);
			void				Create(_In_z_ const _CHAR_SUB* p_strFileName);
			void				Destroy();

	// 2) Clear
			void				ClearApplierTexture();

	// 3) Texture
			int					GetTextureCount() const					{	return (int)m_vectorTextureAttribute.size();}

			void				SetTextureStage(int p_iIndex, const TEXATTR& p_rTexAttr, TEXTUREBASE* p_rTexture)	{	SetTextureAttribute(p_iIndex, p_rTexAttr); SetTexture(p_iIndex, p_rTexture);}
			void				SetTextureAttribute(int p_iIndex, const TEXATTR& p_rTexAttr)	{	CGASSERT_ERROR(p_iIndex<(int)m_vectorTextureAttribute.size()); m_vectorTextureAttribute[p_iIndex]=p_rTexAttr;}
			const TEXATTR&		GetTextureAttribute(int p_iIndex) const	{	CGASSERT_ERROR(p_iIndex<(int)m_vectorTextureAttribute.size()); return m_vectorTextureAttribute[p_iIndex];}

			void				SetTexture(int p_iIndex, TEXTUREBASE* p_rTexture)	{	CGASSERT_ERROR(p_iIndex<(int)m_vectorTextureAttribute.size()); m_vectorTexture[p_iIndex]=p_rTexture;}
			CGPTR<TEXTUREBASE>	GetTexture(int p_iIndex) const			{	CGASSERT_ERROR(p_iIndex<(int)m_vectorTextureAttribute.size()); return m_vectorTexture[p_iIndex];}

	// 4) Attribute
			void				EnableAlpha(bool p_bUseAlpha=true)		{	m_bUseAlpha=p_bUseAlpha;}
			bool				IsEnableAlpha() const					{	return m_bUseAlpha;}

	// 5) Apply
			void				ApplyTexture();
	virtual void				Apply();


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) Process Render
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& /*_MSGRender*/) override	{ return 0; }


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
			vector<TEXATTR>		m_vectorTextureAttribute;
			vector<CGPTR<TEXTUREBASE>>	m_vectorTexture;

			bool				m_bUseAlpha;
};


}