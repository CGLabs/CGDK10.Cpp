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
// CG3DScenenode::Node::CGraph
//
// 1. CG3DScenenode::Node::CGraph��...
//    1) Graph�� ����� Node���̴�.
//    2) Graph�� n���� Edge�� ������ �ִ�.
//       �߰��Ѵ�. �׸��� Bounding�� ���� ����Ѵ�.
//    3) AttachScenenode()�� ���
//       - �ڵ������� �ڽ��� �Ϻ�Node���� �߰� �˻縦 ���� ������ �� �Ϻ� Node�� 
//         ���� ���� ��� �ڽ��� Node�� �߰��� �Ѵ�.
//    4) DetachScenenode()�� ��� 
//       - Detach�� �ڽŻӸ� �ƴ϶� �ڽ� Tree���� Node���� �˻� �� �����Ѵ�.
//
// 2. CG3DScenenode::Node::CGraph Function�� ��� ����
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

template <typename TEDGE=ICG3DSceneNode
	, typename TRENDERER=CG3DRenderer
	, typename TMODIFIER=ICG3DModifier
	, typename TCONTAINER_SCENENODE=vector<CGPTR<TEDGE>> 
	, typename TCONTAINER_RENDERER=vector<CGPTR<TRENDERER>> 
	, typename TCONTAINER_MODIFIER=vector<CGPTR<TMODIFIER>> 
>
class CGraph :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CG3DScenenode::Node::CList<TEDGE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CGraph();
	virtual ~CGraph()													{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Bounding Area�� ����
			AABB				GetRegion() const						{	return m_aabbRegion;}
			AABB				GetRegionMax() const					{	return m_aabbMax;}
			void				SetRegionMax(const AABB& p_rAABB)	{	m_aabbMax=p_rAABB;}

	// 2) Edge�� ��� �����ϱ�.
			TEDGE*				GetEdge(int p_indexNode) const			{	return m_vectorEdge[p_indexNode];}
			void				SetEdge(int p_indexNode, TEDGE* p_pNode);
			void				AddEdge(TEDGE* p_pNode);
			void				RemoveEdge(TEDGE* p_pNode);
			void				RemoveEdge(int p_iEdge);


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

			vector<TEDGE*>		m_vectorEdge;
};


template <typename TEDGE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
CGraph<TEDGE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::CGraph()
{
	// 1) Bounding Min/Max�� �����Ѵ�.
	VECTOR3	v3Min(FLT_MAX, FLT_MAX, FLT_MAX);
	VECTOR3	v3Max(FLT_MIN, FLT_MIN, FLT_MIN);

	// 2) RegionBox�� Reset�Ѵ�.
	m_aabbRegion	 = AABB(v3Min, v3Max);
}

template <typename TEDGE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
void CGraph<TEDGE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::SetEdge(int p_indexNode, TEDGE* p_pEdge)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_p3DView�� NULL�̾�� �ȵȴ�.
	CGASSERT(p_pEdge!=NULL,);


	//----------------------------------------------------------------
	// 1. ������.
	//----------------------------------------------------------------
	// 1) ũ������.
	if(m_vectorEdge.size() <=p_indexNode)
	{
		m_vectorEdge.resize(p_indexNode+1);
	}

	// 2) �����ϱ�
	m_vectorEdge[p_indexNode]=p_pEdge;
}

template <typename TEDGE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
void CGraph<TEDGE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::AddEdge(TEDGE* p_pEdge)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_p3DView�� NULL�̾�� �ȵȴ�.
	CGASSERT(p_pEdge!=NULL,);


	//----------------------------------------------------------------
	// 1. ������.
	//----------------------------------------------------------------
	m_vectorEdge.push_back(p_pEdge);
}

template <typename TEDGE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
void CGraph<TEDGE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::RemoveEdge(TEDGE* p_pEdge)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_p3DView�� NULL�̾�� �ȵȴ�.
	CGASSERT(p_pEdge!=NULL,);


	//----------------------------------------------------------------
	// 1. ���� ã�´�.
	//----------------------------------------------------------------
	vector<TEDGE*>::iterator	iter;

	// 1) ã�´�.
	iter	 = m_vectorEdge.find(p_pEdge);

	// Check) ��ã������ �׳� ������.
	RETURN_IF(iter==m_vectorEdge.end(),);

	// 2) ã������ �����.
	m_vectorEdge.erase(iter);
}

template <typename TEDGE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
void CGraph<TEDGE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::RemoveEdge(int p_iEdge)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_p3DView�� NULL�̾�� �ȵȴ�.
	CGASSERT(p_iEdge>=0,);

	// 2) Index�� size���� ũ�ų� ������ �׳� �ǵ�����.(���� ������ �Ѿ��.)
	RETURN_IF(m_vectorEdge.size() <=p_iEdge,);


	//----------------------------------------------------------------
	// 1. �����.
	//----------------------------------------------------------------
	m_vectorEdge.erase(m_vectorEdge.begin()+p_iEdge);
}


template <typename TEDGE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
int CGraph<TEDGE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::ProcessRender(CGMSG& _Msg)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	//// 1) p_p3DView�� NULL�̾�� �ȵȴ�.
	//CGASSERT(p_pView3D!=NULL,);


	//----------------------------------------------------------------
	// 2. ���� class�� ProcessRender()�� ȣ���Ѵ�.
	//----------------------------------------------------------------
	__super::ProcessRender(_Msg);


	// -----------------------------------------------------------------
	// 3. Node���� ProcessRender�Ѵ�.
	// -----------------------------------------------------------------
	for(auto& iter:m_vectorEdge)
	{
		// Check) ���� m_pNode[i]�� NULL�̸� ����...
		CONTINUE_IF(iter==nullptr);

		// 1) �ڽ� Node�� ProcessRender�Ѵ�.
		iter->RequestRender(_Msg);
	}

	// Return) 
	return	0;
}


}
}