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
	//// 1) p_p3DView�� NULL�̾�� �ȵȴ�.
	//CGASSERT(p_pView3D!=NULL,);


	//// -----------------------------------------------------------------
	//// 1. Terrain Node�� Rendering�Ѵ�.
	//// -----------------------------------------------------------------
	//// - ���� Inside�� �������� ��� Terrain�� �׸��� �ʴ´�.
	////   �ֳ��ϸ� ���� Level���� �׷��� ���̱� �����̴�.
	//// - Intersection���� �ǰ��� ���� ��쿡�� Renderer�� Attach�Ѵ�.
	//if(p_pBoundingPlane!=NULL && p_pBoundingPlane->size())
	//{
	//	QueueTerrainRendererTo(p_pQueueRenderer);
	//}

	////----------------------------------------------------------------
	//// 2. ���� class�� ProcessRender()�� ȣ���Ѵ�.
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