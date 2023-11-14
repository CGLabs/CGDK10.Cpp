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
// CG3DScenenode::Node::CTree
//
// 1. CG3DScenenode::Node::CTree는...
//    1) 느슨한 Quad혹은 Oct Tree를 구한 것이다.
//    2) Scenenode를 추가하게되면 Threshold내에서 Inside일 경우 해당 Node에
//       추가한다. 그리고 Bounding을 새로 계산한다.
//    3) AttachScenenode()의 경우
//       - 자동적으로 자신의 하부Node에서 추가 검사를 먼저 수행한 후 하부 Node에 
//         붙지 않을 경우 자신의 Node에 추가를 한다.
//    4) DetachScenenode()의 경우 
//       - Detach시 자신뿐만 아니라 자신 Tree상의 Node까지 검사 후 제거한다.
//
// 2. CG3DScenenode::Node::CTree Function의 기능 설명
//    1) Render      Render를 시행하는 핵심 구조이다.  
//    2) 음...
//
// 3. 느슨한 n-ary Tree
//    - m_aabbMax는 영역의 최대치로 Bounding 영역이 Max를 넘어서는 안된다.
//    - 만약 두 영역의 조건에 모두 만족했을 때 추가되며 실제 Region은 새로 추가된
//      Bounding과 기존 Bounding의 교집합(Union)으로 재설정된다.
//
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
class CTree :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CG3DScenenode::Node::CList<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTree();
	virtual ~CTree()			{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Scene Node의 Attach와 Detach
	virtual	bool				AttachScenenode(ICG3DSceneNode* p_pScenenode);
	virtual	bool				DetachScenenode(ICG3DSceneNode* p_pScenenode);

	// 2) Bounding Area의 설정
			const AABB&	GetRegion() const						{	return m_aabbRegion;}
			const AABB&	GetRegionMax() const					{	return m_aabbMax;}
			void				SetRegionMax(const AABB& p_rB)	{	m_aabbMax=p_rB;}

	// 3) Tree Node를 얻고 설정하기.
			TNODE*				GetTreeNode(int p_indexNode) const;
			void				SetTreeNode(int p_indexNode, TNODE* p_pNode);

	// 4) 생성하기/파괴하기
			BOOL				CreateTree(int p_iNode);
			void				DestroyTree();


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	int					ProcessRender(CGMSG& _Msg);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			AABB				m_aabbRegion;
			AABB				m_aabbMax;

			vector<CGPTR<TNODE>> m_vectorTreeNode;
};


template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::CTree()
{
	// 1) Bounding Min/Max를 설정한다.
	VECTOR3	v3Min(FLT_MAX, FLT_MAX, FLT_MAX);
	VECTOR3	v3Max(FLT_MIN, FLT_MIN, FLT_MIN);

	// 2) RegionBox를 Reset한다.
	m_aabbRegion	 = AABB(v3Min, v3Max);
}

template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
BOOL CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::CreateTree(int p_nTree)
{
	// --------------------------------------------------------------------------------
	//  Check) 
	// --------------------------------------------------------------------------------

	try
	{
		// --------------------------------------------------------------------------------
		//  1. Node를 생성한다.
		// --------------------------------------------------------------------------------
		// 1) 생성한다.
		m_vectorTreeNode.resize(p_nTree);

		// 2) Reset한다.
		for(auto& iter:m_vectorTreeNode)
		{
			iter	 = NULL;
		}

		// Return) 성공!
		return	TRUE;
	}

	catch(...)
	{
		// Trace) 
		CGLOG_ERROR("Exception(CG3D) : Create Tree Node!! (" _CGTEXT(__FUNCTION__) ")\n");
	}

	// Return) 실패!
	return	FALSE;
}

template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
void CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::DestroyTree()
{
	m_vectorTreeNode.clear();
}



template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
TNODE* CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::GetTreeNode(int p_indexNode) const
{
	// 1) Node값을 되돌린다.
	return m_vectorTreeNode[p_indexNode];
}

template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
void CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::SetTreeNode(int p_indexNode, TNODE* p_pNode)
{
	// Check) 

	// 1) Node를 설정한다.
	m_vectorTreeNode[p_indexNode]=p_pNode;
}


template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
bool CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::AttachScenenode(ICG3DSceneNode* /*p_pScenenode*/)
{
	//// --------------------------------------------------------------------------------
	////  Check) 
	//// --------------------------------------------------------------------------------
	//// 1) p_pScenenode이 NULL이어서는 안된다.
	//RETURN_IF(p_pScenenode==NULL, FALSE);


	//// --------------------------------------------------------------------------------
	////  1. 객체가 Boundable인가를 먼저 검사한다.
	//// --------------------------------------------------------------------------------
	//// 객체가 Boundable일 경우에만 Bounding Check를 수행하고
	//// Boundable이 아닐 경우거나 Bounding Object가 설정되어져 있지 않으면 더이상 Check
	//// 할 필요 없이 막바로 Attach하고 끝내버린다.

	//// 1) Object의 Bounding Info를 얻는다.
	//CGAttachable::Bound::C3D*	tempBounding	 = dynamic_cast<CGAttachable::Bound::C3D*>(p_pScenenode);

	//// Check) tempBounding이 NULL이면 그냥 자신에게 붙이고 끝내버린다.
	//if(tempBounding == NULL || tempBounding->GetBoundingObject()==NULL)
	//{
	//	// Return) 붙이고 끝낸다.
	//	return	__super::AttachScenenode(p_pScenenode);
	//}


	//// --------------------------------------------------------------------------------
	////  1. Outside인가를 먼저 검사한다.
	//// --------------------------------------------------------------------------------
	//{
	//	// 1) Bounding Check를 한다.
	//	BOUNDINGSTATUS	result = m_aabbMax.CheckBoundingStatus(tempBounding->GetBoundingObject());

	//	// Check) 만약에 Outside일 경우 그냥 끝낸다.
	//	RETURN_IF(result != BOUNDINGSTATUS_INSIDE, FALSE);
	//}


	//// --------------------------------------------------------------------------------
	////  2. Tree Node에 대해서 Bounding을 Check한다.
	//// --------------------------------------------------------------------------------
	//// 1) 
	//for(auto& iter:m_vectorTreeNode)
	//{
	//	// Check) 해당 Node가 NULL이면 Node가 비었으므로 다음 Node...
	//	CONTINUE_IF(iter==NULL);

	//	// Declare) 
	//	BOOL	result;

	//	// - Attachable을 구한다.
	//	CGAttachable::IScenenode*	tempAttachable	 = dynamic_cast<CGAttachable::IScenenode*>(*iter);

	//	// Check) tempScenenode이 NULL이면 다음...
	//	CONTINUE_IF(tempAttachable==NULL);

	//	// - 붙힌다.
	//	result	 = tempAttachable->AttachScenenode(p_pScenenode);

	//	// Check) result가 TRUE면 붙었다는 뜻이므로 Return을 해버린다.
	//	if(result==TRUE)
	//	{
	//		// - Object의 Bounding Info를 얻는다.
	//		CGAttachable::Bound::C3D*	tempNodeBounding	 = dynamic_cast<CGAttachable::Bound::C3D*>(*iter);

	//		// Check) 붙이는데 성공했는데 Bounding정보가 없을 수는 없다.
	//		CGASSERT(tempNodeBounding==NULL, FALSE);

	//		// - Bounding을 다시 계산한다.
	//		//m_aabbRegion	+= tempNodeBounding->GetBoundingObject();

	//		// Return) 성공~
	//		return	TRUE;
	//	}
	//}


	//// --------------------------------------------------------------------------------
	////  3. Tree Node에 완전히 포함되지 않는다면 여기에 붙힌다.
	//// --------------------------------------------------------------------------------
	//{
	//	// Declare)
	//	BOOL	result;

	//	// 1) 붙힌다.
	//	result	 = __super::AttachScenenode(p_pScenenode);

	//	// Check) 자기자신한테 잘 붙혔나???
	//	ERROR_RETURN_IF(result==FALSE, FALSE, CGLOG_ERROR("CG3D Error : p_pScenenode를 추가에 실패했습니다!!(" _CGTEXT(__FUNCTION__) ")\n"));

	//	// 2) Bounding계산을 다시한다.
	//	//m_aabbRegion	+= p_pScenenode;
	//}

	// Return) 성공!!!
	return	true;
}

template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
bool CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::DetachScenenode(ICG3DSceneNode* /*p_pScenenode*/)
{
	//// --------------------------------------------------------------------------------
	////  1. 일단 자신에게서 먼저 떼내기를 시도한다.
	//// --------------------------------------------------------------------------------
	//// Declare) 
	//BOOL	result;

	//// 1) 자기자신에서 떼내기.
	//result	 = __super::DetachScenenode(p_pScenenode);

	//// Check) result가 TRUE면 끝낸다.
	//RETURN_IF(result==TRUE, TRUE);


	//// --------------------------------------------------------------------------------
	////  1. 일단 자식 Node에서 떼내기
	//// --------------------------------------------------------------------------------
	//for(auto& iter:m_vectorTreeNode)
	//{
	//	// Check) 만약 m_ppTreeNode[i]가 NULL이면 다음...
	//	CONTINUE_IF(iter==NULL);

	//	// - Attachable을 구한다.
	//	CGAttachable::IScenenode*	tempAttachable	 = dynamic_cast<CGAttachable::IScenenode*>(iter);

	//	// Check) tempScenenode이 NULL이면 다음...
	//	CONTINUE_IF(tempAttachable==NULL);

	//	// 1) 자식 Node에 붙이기를 시도한다.
	//	result	 = tempAttachable->DetachScenenode(p_pScenenode);

	//	// Check) 만약에 result가 TRUE이면 해당 Node에서 떨어진 것이므로 그냥 끝낸다.
	//	RETURN_IF(result==TRUE, TRUE);
	//}

	// Return) 떼내는데 실패했다.
	return	false;
}


template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
int CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::ProcessRender(CGMSG& _Msg)
{
	////----------------------------------------------------------------
	//// Check) 
	////----------------------------------------------------------------
	//// 1) p_p3DView가 NULL이어서는 안된다.
	//CGASSERT(p_pView3D!=NULL,);


	////----------------------------------------------------------------
	//// 2. 상위 class의 ProcessRender()를 호출한다.
	////----------------------------------------------------------------
	//__super::ProcessRender(p_pView3D, p_pQueueRenderer, p_pBoundingPlane);


	//// -----------------------------------------------------------------
	//// 3. Node들을 ProcessRender한다.
	//// -----------------------------------------------------------------
	//for(auto& iter:m_vectorTreeNode)
	//{
	//	// Check) 만약 m_pNode[i]가 NULL이면 다음...
	//	CONTINUE_IF(iter==NULL);

	//	// 1) 자식 Node를 ProcessRender한다.
	//	iter->RequestRender(p_pView3D, p_pQueueRenderer, p_pBoundingPlane);
	//}

	// Declare) 
	CGMSG_RENDER&	rMSG	 = (CGMSG_RENDER&)_Msg;

	// 1) Count...
	rMSG.Statistics_OnProcessRender();

	// Return) 
	return	0;
}


}
}