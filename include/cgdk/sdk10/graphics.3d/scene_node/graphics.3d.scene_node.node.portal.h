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
// CG3DScenenode::Node::CPortal
//
// 1. CG3DScenenode::Node::CPortal는...
//    1) CG3DScenenode::CListLocal에다가 Scenenode를 붙일 수 있도록 한 것이다.
//    2) CG3DScenenode::Node::CList와 완전히 동일하지만 자신의 Transform Matrix를
//       가지고 있다는 것만 차이가 있다.
//
// 2. CG3DScenenode::Node::CListLocal Function의 기능 설명
//    - 특별히 없음...
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
				AABB*		pboundPortal;	// Portal용 
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
	// 1. 이미 존재하고 있는 것인지에 대해서 검사한다.
	// -----------------------------------------------------------------
	// Declare)
	list<PORTAL>::iterator	iter;

	// 1) 찾는다.
	iter	 = m_listPortal.find(p_pScenenode);

	// Check) 이미 존재하는 것인지 검사한다.
	if(iter!=m_listPortal.end() && iter->p_pBoundPortal==p_pBoundPortal)
	{
		return;
	}	


	// -----------------------------------------------------------------
	// 2. Portal정보를 Push한다.
	// -----------------------------------------------------------------
	// 1) Structure 만들기
	PORTAL	tempPortal;
	tempPorgal.pScenenode	 = p_pScenenode;
	tempPorgal.pboundPortal	 = p_pBoundPortal;

	// 2) 집어넣기.
	m_listPortal.push_back(tempPortal);
}

template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER>
void CPortal<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::DetachPortal(ICG3DSceneNode* p_pScenenode)
{
	// 1) 해당 Node에 관련된 Portal을 모두 제거한다.
	m_listPortal.erase(p_pScenenode);
}

template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER>
int CPortal<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::ProcessRender(CGMSG& _Msg)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_pQueueRenderer가 NULL이어서는 안된다.
	//CGASSERT_ERROR(p_pView3D!=NULL);


	//----------------------------------------------------------------
	// 1. 상위 class의 ProcessRender를 먼저 처리한다.
	//----------------------------------------------------------------
	__super::ProcessRender(_Msg);


	// -----------------------------------------------------------------
	// 3. Portal을 처리한다.
	// -----------------------------------------------------------------
	for(auto& iter:m_listPortal)
	{
		// Declare)
		BOUNDINGSTATUS	tempBoundingStatus;

		// - Bounding Check를 한다.
		tempBoundingStatus	 = iter->pboundPortal->CheckBoundingStatus(p_pBoundingPlane);

		// Check) Outside면 볼것도 없이 막바로 되돌린다.
		CONTINUE_IF(tempBoundingStatus == BOUNDINGSTATUS_OUTSIDE);

		// - RequestRender를 수행한다.
		iter->pScenenode->RequestRender(_Msg);
	}

	// Return) 
	return	FALSE;
}


}
}