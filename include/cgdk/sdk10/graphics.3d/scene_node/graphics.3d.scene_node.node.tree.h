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
// CG3DScenenode::Node::CTree
//
// 1. CG3DScenenode::Node::CTree��...
//    1) ������ QuadȤ�� Oct Tree�� ���� ���̴�.
//    2) Scenenode�� �߰��ϰԵǸ� Threshold������ Inside�� ��� �ش� Node��
//       �߰��Ѵ�. �׸��� Bounding�� ���� ����Ѵ�.
//    3) AttachScenenode()�� ���
//       - �ڵ������� �ڽ��� �Ϻ�Node���� �߰� �˻縦 ���� ������ �� �Ϻ� Node�� 
//         ���� ���� ��� �ڽ��� Node�� �߰��� �Ѵ�.
//    4) DetachScenenode()�� ��� 
//       - Detach�� �ڽŻӸ� �ƴ϶� �ڽ� Tree���� Node���� �˻� �� �����Ѵ�.
//
// 2. CG3DScenenode::Node::CTree Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ������ n-ary Tree
//    - m_aabbMax�� ������ �ִ�ġ�� Bounding ������ Max�� �Ѿ�� �ȵȴ�.
//    - ���� �� ������ ���ǿ� ��� �������� �� �߰��Ǹ� ���� Region�� ���� �߰���
//      Bounding�� ���� Bounding�� ������(Union)���� �缳���ȴ�.
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
	// 1) Scene Node�� Attach�� Detach
	virtual	bool				AttachScenenode(ICG3DSceneNode* p_pScenenode);
	virtual	bool				DetachScenenode(ICG3DSceneNode* p_pScenenode);

	// 2) Bounding Area�� ����
			const AABB&	GetRegion() const						{	return m_aabbRegion;}
			const AABB&	GetRegionMax() const					{	return m_aabbMax;}
			void				SetRegionMax(const AABB& p_rB)	{	m_aabbMax=p_rB;}

	// 3) Tree Node�� ��� �����ϱ�.
			TNODE*				GetTreeNode(int p_indexNode) const;
			void				SetTreeNode(int p_indexNode, TNODE* p_pNode);

	// 4) �����ϱ�/�ı��ϱ�
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
	// 1) Bounding Min/Max�� �����Ѵ�.
	VECTOR3	v3Min(FLT_MAX, FLT_MAX, FLT_MAX);
	VECTOR3	v3Max(FLT_MIN, FLT_MIN, FLT_MIN);

	// 2) RegionBox�� Reset�Ѵ�.
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
		//  1. Node�� �����Ѵ�.
		// --------------------------------------------------------------------------------
		// 1) �����Ѵ�.
		m_vectorTreeNode.resize(p_nTree);

		// 2) Reset�Ѵ�.
		for(auto& iter:m_vectorTreeNode)
		{
			iter	 = NULL;
		}

		// Return) ����!
		return	TRUE;
	}

	catch(...)
	{
		// Trace) 
		CGLOG_ERROR("Exception(CG3D) : Create Tree Node!! (" _CGTEXT(__FUNCTION__) ")\n");
	}

	// Return) ����!
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
	// 1) Node���� �ǵ�����.
	return m_vectorTreeNode[p_indexNode];
}

template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
void CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::SetTreeNode(int p_indexNode, TNODE* p_pNode)
{
	// Check) 

	// 1) Node�� �����Ѵ�.
	m_vectorTreeNode[p_indexNode]=p_pNode;
}


template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
bool CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::AttachScenenode(ICG3DSceneNode* /*p_pScenenode*/)
{
	//// --------------------------------------------------------------------------------
	////  Check) 
	//// --------------------------------------------------------------------------------
	//// 1) p_pScenenode�� NULL�̾�� �ȵȴ�.
	//RETURN_IF(p_pScenenode==NULL, FALSE);


	//// --------------------------------------------------------------------------------
	////  1. ��ü�� Boundable�ΰ��� ���� �˻��Ѵ�.
	//// --------------------------------------------------------------------------------
	//// ��ü�� Boundable�� ��쿡�� Bounding Check�� �����ϰ�
	//// Boundable�� �ƴ� ���ų� Bounding Object�� �����Ǿ��� ���� ������ ���̻� Check
	//// �� �ʿ� ���� ���ٷ� Attach�ϰ� ����������.

	//// 1) Object�� Bounding Info�� ��´�.
	//CGAttachable::Bound::C3D*	tempBounding	 = dynamic_cast<CGAttachable::Bound::C3D*>(p_pScenenode);

	//// Check) tempBounding�� NULL�̸� �׳� �ڽſ��� ���̰� ����������.
	//if(tempBounding == NULL || tempBounding->GetBoundingObject()==NULL)
	//{
	//	// Return) ���̰� ������.
	//	return	__super::AttachScenenode(p_pScenenode);
	//}


	//// --------------------------------------------------------------------------------
	////  1. Outside�ΰ��� ���� �˻��Ѵ�.
	//// --------------------------------------------------------------------------------
	//{
	//	// 1) Bounding Check�� �Ѵ�.
	//	BOUNDINGSTATUS	result = m_aabbMax.CheckBoundingStatus(tempBounding->GetBoundingObject());

	//	// Check) ���࿡ Outside�� ��� �׳� ������.
	//	RETURN_IF(result != BOUNDINGSTATUS_INSIDE, FALSE);
	//}


	//// --------------------------------------------------------------------------------
	////  2. Tree Node�� ���ؼ� Bounding�� Check�Ѵ�.
	//// --------------------------------------------------------------------------------
	//// 1) 
	//for(auto& iter:m_vectorTreeNode)
	//{
	//	// Check) �ش� Node�� NULL�̸� Node�� ������Ƿ� ���� Node...
	//	CONTINUE_IF(iter==NULL);

	//	// Declare) 
	//	BOOL	result;

	//	// - Attachable�� ���Ѵ�.
	//	CGAttachable::IScenenode*	tempAttachable	 = dynamic_cast<CGAttachable::IScenenode*>(*iter);

	//	// Check) tempScenenode�� NULL�̸� ����...
	//	CONTINUE_IF(tempAttachable==NULL);

	//	// - ������.
	//	result	 = tempAttachable->AttachScenenode(p_pScenenode);

	//	// Check) result�� TRUE�� �پ��ٴ� ���̹Ƿ� Return�� �ع�����.
	//	if(result==TRUE)
	//	{
	//		// - Object�� Bounding Info�� ��´�.
	//		CGAttachable::Bound::C3D*	tempNodeBounding	 = dynamic_cast<CGAttachable::Bound::C3D*>(*iter);

	//		// Check) ���̴µ� �����ߴµ� Bounding������ ���� ���� ����.
	//		CGASSERT(tempNodeBounding==NULL, FALSE);

	//		// - Bounding�� �ٽ� ����Ѵ�.
	//		//m_aabbRegion	+= tempNodeBounding->GetBoundingObject();

	//		// Return) ����~
	//		return	TRUE;
	//	}
	//}


	//// --------------------------------------------------------------------------------
	////  3. Tree Node�� ������ ���Ե��� �ʴ´ٸ� ���⿡ ������.
	//// --------------------------------------------------------------------------------
	//{
	//	// Declare)
	//	BOOL	result;

	//	// 1) ������.
	//	result	 = __super::AttachScenenode(p_pScenenode);

	//	// Check) �ڱ��ڽ����� �� ������???
	//	ERROR_RETURN_IF(result==FALSE, FALSE, CGLOG_ERROR("CG3D Error : p_pScenenode�� �߰��� �����߽��ϴ�!!(" _CGTEXT(__FUNCTION__) ")\n"));

	//	// 2) Bounding����� �ٽ��Ѵ�.
	//	//m_aabbRegion	+= p_pScenenode;
	//}

	// Return) ����!!!
	return	true;
}

template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
bool CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::DetachScenenode(ICG3DSceneNode* /*p_pScenenode*/)
{
	//// --------------------------------------------------------------------------------
	////  1. �ϴ� �ڽſ��Լ� ���� �����⸦ �õ��Ѵ�.
	//// --------------------------------------------------------------------------------
	//// Declare) 
	//BOOL	result;

	//// 1) �ڱ��ڽſ��� ������.
	//result	 = __super::DetachScenenode(p_pScenenode);

	//// Check) result�� TRUE�� ������.
	//RETURN_IF(result==TRUE, TRUE);


	//// --------------------------------------------------------------------------------
	////  1. �ϴ� �ڽ� Node���� ������
	//// --------------------------------------------------------------------------------
	//for(auto& iter:m_vectorTreeNode)
	//{
	//	// Check) ���� m_ppTreeNode[i]�� NULL�̸� ����...
	//	CONTINUE_IF(iter==NULL);

	//	// - Attachable�� ���Ѵ�.
	//	CGAttachable::IScenenode*	tempAttachable	 = dynamic_cast<CGAttachable::IScenenode*>(iter);

	//	// Check) tempScenenode�� NULL�̸� ����...
	//	CONTINUE_IF(tempAttachable==NULL);

	//	// 1) �ڽ� Node�� ���̱⸦ �õ��Ѵ�.
	//	result	 = tempAttachable->DetachScenenode(p_pScenenode);

	//	// Check) ���࿡ result�� TRUE�̸� �ش� Node���� ������ ���̹Ƿ� �׳� ������.
	//	RETURN_IF(result==TRUE, TRUE);
	//}

	// Return) �����µ� �����ߴ�.
	return	false;
}


template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
int CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::ProcessRender(CGMSG& _Msg)
{
	////----------------------------------------------------------------
	//// Check) 
	////----------------------------------------------------------------
	//// 1) p_p3DView�� NULL�̾�� �ȵȴ�.
	//CGASSERT(p_pView3D!=NULL,);


	////----------------------------------------------------------------
	//// 2. ���� class�� ProcessRender()�� ȣ���Ѵ�.
	////----------------------------------------------------------------
	//__super::ProcessRender(p_pView3D, p_pQueueRenderer, p_pBoundingPlane);


	//// -----------------------------------------------------------------
	//// 3. Node���� ProcessRender�Ѵ�.
	//// -----------------------------------------------------------------
	//for(auto& iter:m_vectorTreeNode)
	//{
	//	// Check) ���� m_pNode[i]�� NULL�̸� ����...
	//	CONTINUE_IF(iter==NULL);

	//	// 1) �ڽ� Node�� ProcessRender�Ѵ�.
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