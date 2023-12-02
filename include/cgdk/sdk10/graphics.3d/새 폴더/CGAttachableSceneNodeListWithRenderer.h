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
// CGAttachable::CScenenodeList
//
// 1. CGAttachable::CScenenodeList��...
//    1) Scenenode�� Renderer�� ������ ��� �װ��� Rendering�ϱ� ���� ���̴�.
//    2) IScenenode�� Attach�� �� ��� �װ��� Dynamic cast�� �̿��Ͽ� 
//       IRenderer Interface�� �������� �˻��Ͽ� ���� �����ٸ� �� Pointer��
//       ���� vector�� ������ ���´�.
//    3) Render�� ������ �� �� ���� ��� ���� IRenderer�� ������ Render�� ȣ��
//       �Ѵ�.
//    4) �̷��� ���� IRender�� �����͸� ��� ���� ������ Render�� �ǽð����� 
//       Dynamic_cast�� �̿��Ͽ� IRenderer Interface�� ��� Render�� ��� 
//       Dynamic_cast�� ���ϰ� �ɸ� ���̱� ������ �� ���ϸ� ���̱� ���ؼ��̴�.
//
//
// 2. CGAttachable::CScenenodeList�� �ٽ�! Function�� ��� ����
//    1) AttachScenenode
//       - IScenenode�� ���̴� �Լ��� ���������� IRenderer Interface�� ���
//		   �װ��� ���� vector�� �����Ѵ�.
//
//    2) DetachRenderNOde
//       - AttachScenenode�� �ݴ� ������ �����Ѵ�.
//
//    3) RenderAttachedScenenode
//		 - ��� ���� IRenderer�� Render()�Լ��� ȣ�����ش�.
//
//
//-----------------------------------------------------------------------------
namespace CGAttachable
{

template <typename TSCENENODE=ICGScenenode, typename TCONTAINER_SCENENODE=vector<CGPTR<TSCENENODE>> >
class CScenenodeListSub :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGAttachable::CScenenodeList<TSCENENODE, TCONTAINER_SCENENODE>	// (@) Attachable Scenenode
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CScenenodeListSub()											{}
	virtual	~CScenenodeListSub()										{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Renderable Attach/Detach
	virtual	bool				AttachScenenode(ICGScenenode* p_pScenenode);
	virtual	bool				DetachScenenode(ICGScenenode* p_pScenenode);

	// 2) Scenenode�� Renderer�� Render�� �����ϴ� �Լ�.
			void				RenderAttachedSub(CONTEXT_RENDERING& p_rRC);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 2) RenderQueue for Render of Scenenode
			vector<CGPTR<ICGRenderer>>	m_vectorRenderSub;
};


template <typename TSCENENODE, typename TCONTAINER_SCENENODE>
bool CScenenodeListSub<TSCENENODE, TCONTAINER_SCENENODE>::AttachScenenode(ICGScenenode* p_pScenenode)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_pScenenode�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pScenenode!=NULL);


	// -----------------------------------------------------------------
	// 1. Scene Node�� List�� �߰��Ѵ�.
	// -----------------------------------------------------------------
	bool	bResult;

	// 1) �ϴ� ���� �߰��Ѵ�.
	bResult	 = __super::AttachScenenode(p_pScenenode);

	// Check) �߰����� �������� ���⼭ ������.
	RETURN_IF(bResult==false, false);


	// -----------------------------------------------------------------
	// 2. Renderer�� �߰��Ѵ�.
	// -----------------------------------------------------------------
	// 1) Sub Renderer�� �Ӽ��� �ִ��� Ȯ���Ѵ�.
	//    - Sub Renderer�� �Ӽ��� �־������ Renderer�� �߰��Ѵ�.
	//if(HAS_ATTRIBUTE(CGRenderer::Attribute::ISub, p_pScenenode))
	//{
	//	// 1) Renderer Interface�� �ִ��� Ȯ���Ѵ�.
	//	auto*	pRenderer	 = dynamic_cast<ICGRenderer*>(p_pScenenode);

	//	if(pRenderer!=NULL)
	//	{
	//		m_vectorRenderSub.push_back(pRenderer);
	//	}
	//}

	// Return)
	return	true;
}

template <typename TSCENENODE, typename TCONTAINER_SCENENODE>
bool CScenenodeListSub<TSCENENODE, TCONTAINER_SCENENODE>::DetachScenenode(ICGScenenode* p_pScenenode)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_pScenenode�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pScenenode!=NULL);


	// -----------------------------------------------------------------
	// 1. Renderer�� ������ ������.
	// -----------------------------------------------------------------
	// 1) Renderer Interface�� �ִ��� Ȯ���Ѵ�.
	//if(HAS_ATTRIBUTE(CGRenderer::Attribute::ISub, p_pScenenode))
	//{
	//	// - Renderer Interface�� ��´�.
	//	auto*	pRenderer	 = dynamic_cast<ICGRenderer*>(p_pScenenode);

	//	if(pRenderer!=NULL)
	//	{
	//		// Declare) 
	//		vector<ICGRenderer*>::iterator	iter;

	//		// - �ش� Renderer�� �ִ��� Ȯ���Ѵ�.
	//		iter	 = m_vectorRenderSub.find(pRenderer);

	//		// - ������ Queue���� �����Ѵ�.
	//		if(iter!=m_vectorRenderSub.end())
	//		{
	//			m_vectorRenderSub.erase(iter);
	//		}
	//	}
	//}

	// -----------------------------------------------------------------
	// 2. Scene Node�� List�� �߰��Ѵ�.
	// -----------------------------------------------------------------
	// 1) �ϴ� ���� �߰��Ѵ�.
	return	__super::DetachScenenode(p_pScenenode);
}


template <typename TSCENENODE, typename TCONTAINER_SCENENODE>
void CScenenodeListSub<TSCENENODE, TCONTAINER_SCENENODE>::RenderAttachedSub(CONTEXT_RENDERING& /*p_rRC*/)
{
	////----------------------------------------------------------------
	//// Check) 
	////----------------------------------------------------------------
	//// 1) p_p3DView�� NULL�̾�� �ȵȴ�.
	//CGASSERT(p_pView3D!=NULL,);


	//// -----------------------------------------------------------------
	//// 1. Attached Scenenode�� Rneder�Ѵ�.
	//// -----------------------------------------------------------------
	//// 1) Attached Node�� ������ Rendering�Ѵ�.
	//for(auto& iter:m_vectorRenderSub)
	//{
	//	iter->Render(p_rRC);
	//}
}


}
