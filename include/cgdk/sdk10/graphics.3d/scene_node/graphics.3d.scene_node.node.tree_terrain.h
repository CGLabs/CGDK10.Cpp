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
		, typename TRENDERER=ICG3DRenderer
		, typename TMODIFIER=ICG3DModifier
		, typename TCONTAINER_SCENENODE=vector<CGPTR<TNODE>> 
		, typename TCONTAINER_RENDERER=vector<CGPTR<TRENDERER>> 
		, typename TCONTAINER_MODIFIER=vector<CGPTR<TMODIFIER>> 
		>
class CTreeTerrain :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CG3DScenenode::Node::CTree<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>,
	public						CGAttachable::CRendererTerrain<TRENDERER, list<TRENDERER*> >
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTreeTerrain()		{}
	virtual ~CTreeTerrain()		{}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	virtual	int						ProcessRender(CGMSG& _Msg);
};


template <typename TNODE, typename TRENDERER, typename TMODIFIER, typename TCONTAINER_SCENENODE, typename TCONTAINER_RENDERER, typename TCONTAINER_MODIFIER> 
int CTreeTerrain<TNODE, TRENDERER, TMODIFIER, TCONTAINER_SCENENODE, TCONTAINER_RENDERER, TCONTAINER_MODIFIER>::ProcessRender(CGMSG& _Msg)
{
	////----------------------------------------------------------------
	//// Check) 
	////----------------------------------------------------------------
	//// 1) p_p3DView가 NULL이어서는 안된다.
	//CGASSERT(p_pView3D!=NULL,);


	//// -----------------------------------------------------------------
	//// 1. Terrain Node를 Rendering한다.
	//// -----------------------------------------------------------------
	//// - 만약 Inside로 편정났을 경우 Terrain을 그리지 않는다.
	////   왜냐하면 윗쪽 Level에서 그렸을 것이기 때문이다.
	//// - Intersection으로 판결이 났을 경우에만 Renderer를 Attach한다.
	//if(p_pBoundingPlane!=NULL && p_pBoundingPlane->size())
	//{
	//	QueueTerrainRendererTo(p_pQueueRenderer);
	//}

	////----------------------------------------------------------------
	//// 2. 상위 class의 ProcessRender()를 호출한다.
	////----------------------------------------------------------------
	//__super::ProcessRender(p_rRC);

	// Declare) 
	CGMSG_RENDER&	rMSG	 = (CGMSG_RENDER&)_Msg;

	// 1) Count...
	rMSG.Statistics_OnProcessRender();

	// Return) 
	return	0;
}


}
}