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
// CG3DRenderer::Mesh::CObject
//
// 1. CG3DRenderer::Mesh::CObject는...
//    1) 독립적인 Render와 Loop상의 Render를 동시에 지원하는 방법을 택했다.
//    2) Render에 필요한 각종 정보를 독립적으로 모두 가지고 있게 한다. Render시
//       그 값들을 설정해서 사용하지만 중복 설정 시 다시 설정하지 않아도 되게
//       설정을 한다.
//    3) Linked List라든지 혹은 Array의 구조는 체택하지 않는다! 이유는 Modify와
//       틀리게 Arrange등이 필요하며 찍히는 순서는 오히려 별 의미가 없기 때문이
//       다. 2D의 경우나 혹은 Sprite같은 경우는 순서가 필요하나 이런 경우는 다
//       른 방법으로 구현을 하며 Default로 지원하는 구조는 넣지 않는다.
//       이유는 다양한 방법의 구조가 존재할 수 있기 때문이다. 예를 들면 Arrange
//       도 Z Ordering을 해야하는 경우 Y Ordering을 해야하는 경우나 필요 없는
//       경우 등 각기 틀린 필요에 따라 다른 구조를 체택해야 하기 때문이다.
//
//
// 2. CGNetRoot의 핵심! Function의 기능 설명
//    1) Render      Render를 시행하는 핵심 구조이다.  
//    2) 음...
//
// 3. 주의 사항
//    음... -_-;;
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

	// 2) Render함수.
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
			CGPTR<CG3DApplier::CEffect>		m_papplierEffect;		// Applier Effect임.

	// 2) Texture
			CGPTR<CG3DApplier::CTexture>	m_papplierTexture;		// Applier Texture

	// 3) Material
			CGPTR<CG3DApplier::CMaterial>	m_papplierMaterial;		// Applier Material

	// 4) Additional Applier (Generally Skinning Info)
			CGPTR<ICG3DApplier>				m_papplier;				// (보통 SkinningInfo등)

public:
	// 1) 
			DWORD				QueryCulling();
			DWORD				RenderMesh(CGMSG& _Msg);
			DWORD				RenderAll(CGMSG& _Msg);
};
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

}
}