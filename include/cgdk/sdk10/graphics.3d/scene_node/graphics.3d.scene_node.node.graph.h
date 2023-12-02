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
// CG3DScenenode::Node::CGraph
//
// 1. CG3DScenenode::Node::CGraph는...
//    1) Graph로 연결된 Node들이다.
//    2) Graph는 n개의 Edge를 가질수 있다.
//       추가한다. 그리고 Bounding을 새로 계산한다.
//    3) AttachScenenode()의 경우
//       - 자동적으로 자신의 하부Node에서 추가 검사를 먼저 수행한 후 하부 Node에 
//         붙지 않을 경우 자신의 Node에 추가를 한다.
//    4) DetachScenenode()의 경우 
//       - Detach시 자신뿐만 아니라 자신 Tree상의 Node까지 검사 후 제거한다.
//
// 2. CG3DScenenode::Node::CGraph Function의 기능 설명
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
	// 1) Bounding Area의 설정
			AABB				GetRegion() const						{	return m_aabbRegion;}
			AABB				GetRegionMax() const					{	return m_aabbMax;}
			void				SetRegionMax(const AABB& p_rAABB)	{	m_aabbMax=p_rAABB;}

	// 2) Edge를 얻고 설정하기.
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
	// 1) Bounding Min/Max를 설정한다.
	VECTOR3	v3Min(FLT_MAX, FLT_MAX, FLT_MAX);
	VECTOR3	v3Max(FLT_MIN, FLT_MIN, FLT_MIN);

	// 2) RegionBox를 Reset한다.
	m_aabbRegion	 = AABB(v3Min, v3Max);
}

template <typename TEDGE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
void CGraph<TEDGE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::SetEdge(int p_indexNode, TEDGE* p_pEdge)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_p3DView가 NULL이어서는 안된다.
	CGASSERT(p_pEdge!=NULL,);


	//----------------------------------------------------------------
	// 1. 붙힌다.
	//----------------------------------------------------------------
	// 1) 크기조정.
	if(m_vectorEdge.size() <=p_indexNode)
	{
		m_vectorEdge.resize(p_indexNode+1);
	}

	// 2) 설정하기
	m_vectorEdge[p_indexNode]=p_pEdge;
}

template <typename TEDGE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
void CGraph<TEDGE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::AddEdge(TEDGE* p_pEdge)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_p3DView가 NULL이어서는 안된다.
	CGASSERT(p_pEdge!=NULL,);


	//----------------------------------------------------------------
	// 1. 붙힌다.
	//----------------------------------------------------------------
	m_vectorEdge.push_back(p_pEdge);
}

template <typename TEDGE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
void CGraph<TEDGE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::RemoveEdge(TEDGE* p_pEdge)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_p3DView가 NULL이어서는 안된다.
	CGASSERT(p_pEdge!=NULL,);


	//----------------------------------------------------------------
	// 1. 먼저 찾는다.
	//----------------------------------------------------------------
	vector<TEDGE*>::iterator	iter;

	// 1) 찾는다.
	iter	 = m_vectorEdge.find(p_pEdge);

	// Check) 못찾았으면 그냥 끝낸다.
	RETURN_IF(iter==m_vectorEdge.end(),);

	// 2) 찾았으면 지운다.
	m_vectorEdge.erase(iter);
}

template <typename TEDGE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
void CGraph<TEDGE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::RemoveEdge(int p_iEdge)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_p3DView가 NULL이어서는 안된다.
	CGASSERT(p_iEdge>=0,);

	// 2) Index가 size보다 크거나 같으면 그냥 되돌린다.(값의 범위를 넘어섰다.)
	RETURN_IF(m_vectorEdge.size() <=p_iEdge,);


	//----------------------------------------------------------------
	// 1. 지운다.
	//----------------------------------------------------------------
	m_vectorEdge.erase(m_vectorEdge.begin()+p_iEdge);
}


template <typename TEDGE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
int CGraph<TEDGE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::ProcessRender(CGMSG& _Msg)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	//// 1) p_p3DView가 NULL이어서는 안된다.
	//CGASSERT(p_pView3D!=NULL,);


	//----------------------------------------------------------------
	// 2. 상위 class의 ProcessRender()를 호출한다.
	//----------------------------------------------------------------
	__super::ProcessRender(_Msg);


	// -----------------------------------------------------------------
	// 3. Node들을 ProcessRender한다.
	// -----------------------------------------------------------------
	for(auto& iter:m_vectorEdge)
	{
		// Check) 만약 m_pNode[i]가 NULL이면 다음...
		CONTINUE_IF(iter==nullptr);

		// 1) 자식 Node를 ProcessRender한다.
		iter->RequestRender(_Msg);
	}

	// Return) 
	return	0;
}


}
}