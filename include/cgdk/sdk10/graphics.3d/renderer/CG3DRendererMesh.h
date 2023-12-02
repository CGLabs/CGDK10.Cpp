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

class CBase : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DRenderer,						// 1) 
	virtual public				ICG3DWorldTransform,				// 2) World TM
	public						ICGDeviceGraphic					// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CBase();
			CBase(CMatrix* p_pTransformMatrix, MESH* p_ResourceMesh=nullptr);
	virtual	~CBase();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------*
public:
	// 1) Render�Լ�.
	virtual uint32_t			Render(CGMSG_RENDER& _Msg);

	// 2) Transform Matrix
	virtual	void				SetWorldTransformMatrix(CMatrix* p_ptm);
	virtual	CGPTR<CMatrix>		GetWorldTransformMatrix();

	// 3) Mesh ����
			CGPTR<MESH>			GetResourceMesh() const					{	return m_pResourceMesh;}
			void				SetResourceMesh(MESH* p_pResourceMesh)	{	m_pResourceMesh = p_pResourceMesh;}


// ****************************************************************************
// Message)
// ----------------------------------------------------------------------------
public:
	// Declare) 
	DECLARE_CGMESSAGE_MAP

	// 1) Functions
	virtual	uint32_t			OnFunction_SetWorldTransformMatrix	(CGMSG_SET<CMatrix>& _Msg);
	virtual	uint32_t			OnFunction_GetWorldTransformMatrix	(CGMSG_GET<CMatrix>& _Msg);

	virtual	uint32_t			OnFunction_SetResourceMesh			(CGMSG_SET<ICGObject>& _Msg);
	virtual	uint32_t			OnFunction_GetResourceMesh			(CGMSG_GET<ICGObject>& _Msg);

	// 2) Notifications for Automation
	virtual	uint32_t			OnNotify_OnAttach					(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	uint32_t			OnNotify_OnDetach					(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

	// 2) ProcessRender
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& /*_MSGRender*/) override;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Transform Matrix
			CGPTR<CMatrix>		m_ptmWorld;

	// 2) Mesh Resource
			CGPTR<MESH>			m_pResourceMesh;

	// 3) Bounding Info
			
};
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

}
}