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
// CG3DRenderer::Mesh::CObject
//
// 1. CG3DRenderer::Mesh::CObject��...
//    1) �������� Render�� Loop���� Render�� ���ÿ� �����ϴ� ����� ���ߴ�.
//    2) Render�� �ʿ��� ���� ������ ���������� ��� ������ �ְ� �Ѵ�. Render��
//       �� ������ �����ؼ� ��������� �ߺ� ���� �� �ٽ� �������� �ʾƵ� �ǰ�
//       ������ �Ѵ�.
//    3) Linked List����� Ȥ�� Array�� ������ ü������ �ʴ´�! ������ Modify��
//       Ʋ���� Arrange���� �ʿ��ϸ� ������ ������ ������ �� �ǹ̰� ���� ������
//       ��. 2D�� ��쳪 Ȥ�� Sprite���� ���� ������ �ʿ��ϳ� �̷� ���� ��
//       �� ������� ������ �ϸ� Default�� �����ϴ� ������ ���� �ʴ´�.
//       ������ �پ��� ����� ������ ������ �� �ֱ� �����̴�. ���� ��� Arrange
//       �� Z Ordering�� �ؾ��ϴ� ��� Y Ordering�� �ؾ��ϴ� ��쳪 �ʿ� ����
//       ��� �� ���� Ʋ�� �ʿ信 ���� �ٸ� ������ ü���ؾ� �ϱ� �����̴�.
//
//
// 2. CGNetRoot�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
//
//-----------------------------------------------------------------------------
namespace CG3DRenderer
{
namespace Mesh
{

class CObject : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CG3DRenderer::Mesh::CBase
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CObject(CMatrix* p_pTransformMatrix=nullptr, MESH* p_ResourceMesh=nullptr);
	virtual	~CObject();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Clear
			void				ClearRendererObject();

	// 2) Render�Լ�.
	virtual uint32_t			Render(CGMSG_RENDER& _Msg);

	// 3) Vertex & Pixel Shader
			CGPTR<CG3DApplier::CEffect>	GetApplierEffect() const			{	return m_papplierEffect;}
			void				SetApplierEffect(CG3DApplier::CEffect* p_rEffect)		{	m_papplierEffect=p_rEffect;}

	// 4) Texture Applier
			CGPTR<CG3DApplier::CTexture>	GetApplierTexture() const		{	return m_papplierTexture;}
			void				SetApplierTexture(CG3DApplier::CTexture* p_rTexture)	{	m_papplierTexture = p_rTexture;}

	// 5) Material Material
			CGPTR<CG3DApplier::CMaterial>	GetApplierMaterial() const		{	return m_papplierMaterial;}
			void				SetApplierMaterial(CG3DApplier::CMaterial* p_pMaterial)	{	m_papplierMaterial = p_pMaterial;}

	// 6) General Applier
			CGPTR<ICG3DApplier>	GetApplier() const							{	return m_papplier;}
			void				SetApplier(ICG3DApplier* p_pApplier)		{	m_papplier=p_pApplier;}


// ****************************************************************************
// Message)
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

public:
	// Declare) 
	DECLARE_CGMESSAGE_MAP

	// 1) Functions
			int					OnFunction_SetApplierEffect (CGMSG_SET<ICGObject>& _Msg);
			int					OnFunction_GetApplierEffect (CGMSG_GET<ICGObject>& _Msg);

			int					OnFunction_SetApplierTexture (CGMSG_SET<ICGObject>& _Msg);
			int					OnFunction_GetApplierTexture (CGMSG_GET<ICGObject>& _Msg);

			int					OnFunction_SetApplierMaterial (CGMSG_SET<ICGObject>& _Msg);
			int					OnFunction_GetApplierMaterial (CGMSG_GET<ICGObject>& _Msg);

			int					OnFunction_SetApplier (CGMSG_SET<ICGObject>& _Msg);
			int					OnFunction_GetApplier (CGMSG_GET<ICGObject>& _Msg);


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	virtual	int					OnRendering(CGMSG_RENDER& _Msg);
	virtual	void				OnRender(CGMSG_RENDER& _Msg);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Effect
			CGPTR<CG3DApplier::CEffect>		m_papplierEffect;		// Applier Effect��.

	// 2) Texture
			CGPTR<CG3DApplier::CTexture>	m_papplierTexture;		// Applier Texture

	// 3) Material
			CGPTR<CG3DApplier::CMaterial>	m_papplierMaterial;		// Applier Material

	// 4) Additional Applier (Generally Skinning Info)
			CGPTR<ICG3DApplier>				m_papplier;				// (���� SkinningInfo��)

public:
	// 1) 
			DWORD				QueryCulling();
			DWORD				RenderMesh(CGMSG& _Msg);
			DWORD				RenderAll(CGMSG& _Msg);
};
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

}
}