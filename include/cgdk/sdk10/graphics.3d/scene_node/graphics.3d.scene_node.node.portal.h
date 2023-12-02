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
// CG3DScenenode::Node::CPortal
//
// 1. CG3DScenenode::Node::CPortal��...
//    1) CG3DScenenode::CListLocal���ٰ� Scenenode�� ���� �� �ֵ��� �� ���̴�.
//    2) CG3DScenenode::Node::CList�� ������ ���������� �ڽ��� Transform Matrix��
//       ������ �ִٴ� �͸� ���̰� �ִ�.
//
// 2. CG3DScenenode::Node::CListLocal Function�� ��� ����
//    - Ư���� ����...
//
//-----------------------------------------------------------------------------
namespace CG3DScenenode
{
namespace Node
{

template <typename TNODE=ICG3DSceneNode
		, typename TRENDERER=CG3DRenderer
		, typename TMODIFIER=ICG3DModifier
		, typename TCONTAINER_SCENENODE=vector<CGPTR<TNODE>> 
		, typename TCONTAINER_RENDERER=vector<CGPTR<TRENDERER>> 
		, typename TCONTAINER_MODIFIER=vector<CGPTR<TMODIFIER>> 
		>
class CPortal : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CG3DScenenode::Node::CList<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CPortal()													{}
	virtual ~CPortal()													{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
	// 1) List
public:
			void				AttachPortal(ICG3DSceneNode* p_pScenenode, AABB* p_pBoundPortal);
			void				DetachPortal(ICG3DSceneNode* p_pScenenode);
	

// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	int					ProcessRender(CGMSG& _Msg);


// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
protected:
			typedef struct PORTAL
			{
				ICG3DSceneNode*	pScenenode;
				AABB*		pboundPortal;	// Portal�� 
			} *LPPORTAL, &RPPORTALL;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			list<PORTAL>		m_listPortal;
};



template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER>
void CPortal<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::AttachPortal(ICG3DSceneNode* p_pScenenode, AABB* p_pBoundPortal)
{

	// -----------------------------------------------------------------
	// 1. �̹� �����ϰ� �ִ� �������� ���ؼ� �˻��Ѵ�.
	// -----------------------------------------------------------------
	// Declare)
	list<PORTAL>::iterator	iter;

	// 1) ã�´�.
	iter	 = m_listPortal.find(p_pScenenode);

	// Check) �̹� �����ϴ� ������ �˻��Ѵ�.
	if(iter!=m_listPortal.end() && iter->p_pBoundPortal==p_pBoundPortal)
	{
		return;
	}	


	// -----------------------------------------------------------------
	// 2. Portal������ Push�Ѵ�.
	// -----------------------------------------------------------------
	// 1) Structure �����
	PORTAL	tempPortal;
	tempPorgal.pScenenode	 = p_pScenenode;
	tempPorgal.pboundPortal	 = p_pBoundPortal;

	// 2) ����ֱ�.
	m_listPortal.push_back(tempPortal);
}

template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER>
void CPortal<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::DetachPortal(ICG3DSceneNode* p_pScenenode)
{
	// 1) �ش� Node�� ���õ� Portal�� ��� �����Ѵ�.
	m_listPortal.erase(p_pScenenode);
}

template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER>
int CPortal<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::ProcessRender(CGMSG& _Msg)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_pQueueRenderer�� NULL�̾�� �ȵȴ�.
	//CGASSERT_ERROR(p_pView3D!=NULL);


	//----------------------------------------------------------------
	// 1. ���� class�� ProcessRender�� ���� ó���Ѵ�.
	//----------------------------------------------------------------
	__super::ProcessRender(_Msg);


	// -----------------------------------------------------------------
	// 3. Portal�� ó���Ѵ�.
	// -----------------------------------------------------------------
	for(auto& iter:m_listPortal)
	{
		// Declare)
		BOUNDINGSTATUS	tempBoundingStatus;

		// - Bounding Check�� �Ѵ�.
		tempBoundingStatus	 = iter->pboundPortal->CheckBoundingStatus(p_pBoundingPlane);

		// Check) Outside�� ���͵� ���� ���ٷ� �ǵ�����.
		CONTINUE_IF(tempBoundingStatus == BOUNDINGSTATUS_OUTSIDE);

		// - RequestRender�� �����Ѵ�.
		iter->pScenenode->RequestRender(_Msg);
	}

	// Return) 
	return	FALSE;
}


}
}