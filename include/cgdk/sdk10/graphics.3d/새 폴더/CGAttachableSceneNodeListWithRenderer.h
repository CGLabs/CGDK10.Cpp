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
// CGAttachable::CScenenodeList
//
// 1. CGAttachable::CScenenodeList는...
//    1) Scenenode가 Renderer를 가졌을 경우 그것을 Rendering하기 위한 것이다.
//    2) IScenenode로 Attach가 될 경우 그것이 Dynamic cast를 이용하여 
//       IRenderer Interface를 가졌는지 검사하여 만약 가졌다면 그 Pointer를
//       따로 vector에 저장해 놓는다.
//    3) Render를 수행할 때 이 따로 모아 놓은 IRenderer를 돌리며 Render를 호출
//       한다.
//    4) 이렇게 따로 IRender의 포인터를 모아 놓는 이유는 Render시 실시간으로 
//       Dynamic_cast를 이용하여 IRenderer Interface를 얻어 Render할 경우 
//       Dynamic_cast의 부하가 걸릴 것이기 때문에 그 부하를 줄이기 위해서이다.
//
//
// 2. CGAttachable::CScenenodeList의 핵심! Function의 기능 설명
//    1) AttachScenenode
//       - IScenenode를 붙이는 함수로 내부적으로 IRenderer Interface를 얻어
//		   그것을 따로 vector에 저장한다.
//
//    2) DetachRenderNOde
//       - AttachScenenode와 반대 역할을 수행한다.
//
//    3) RenderAttachedScenenode
//		 - 모아 놓은 IRenderer의 Render()함수를 호출해준다.
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

	// 2) Scenenode의 Renderer의 Render를 수행하는 함수.
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
	// 1) p_pScenenode가 NULL이어서는 안된다.
	CGASSERT_ERROR(p_pScenenode!=NULL);


	// -----------------------------------------------------------------
	// 1. Scene Node를 List에 추가한다.
	// -----------------------------------------------------------------
	bool	bResult;

	// 1) 일단 먼저 추가한다.
	bResult	 = __super::AttachScenenode(p_pScenenode);

	// Check) 추가하지 모했으면 여기서 끝낸다.
	RETURN_IF(bResult==false, false);


	// -----------------------------------------------------------------
	// 2. Renderer를 추가한다.
	// -----------------------------------------------------------------
	// 1) Sub Renderer의 속성이 있는지 확인한다.
	//    - Sub Renderer의 속성이 있어야지만 Renderer를 추가한다.
	//if(HAS_ATTRIBUTE(CGRenderer::Attribute::ISub, p_pScenenode))
	//{
	//	// 1) Renderer Interface가 있는지 확인한다.
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
	// 1) p_pScenenode가 NULL이어서는 안된다.
	CGASSERT_ERROR(p_pScenenode!=NULL);


	// -----------------------------------------------------------------
	// 1. Renderer가 있으면 떼낸다.
	// -----------------------------------------------------------------
	// 1) Renderer Interface가 있는지 확인한다.
	//if(HAS_ATTRIBUTE(CGRenderer::Attribute::ISub, p_pScenenode))
	//{
	//	// - Renderer Interface를 얻는다.
	//	auto*	pRenderer	 = dynamic_cast<ICGRenderer*>(p_pScenenode);

	//	if(pRenderer!=NULL)
	//	{
	//		// Declare) 
	//		vector<ICGRenderer*>::iterator	iter;

	//		// - 해당 Renderer가 있는지 확인한다.
	//		iter	 = m_vectorRenderSub.find(pRenderer);

	//		// - 있으면 Queue에서 제거한다.
	//		if(iter!=m_vectorRenderSub.end())
	//		{
	//			m_vectorRenderSub.erase(iter);
	//		}
	//	}
	//}

	// -----------------------------------------------------------------
	// 2. Scene Node를 List에 추가한다.
	// -----------------------------------------------------------------
	// 1) 일단 먼저 추가한다.
	return	__super::DetachScenenode(p_pScenenode);
}


template <typename TSCENENODE, typename TCONTAINER_SCENENODE>
void CScenenodeListSub<TSCENENODE, TCONTAINER_SCENENODE>::RenderAttachedSub(CONTEXT_RENDERING& /*p_rRC*/)
{
	////----------------------------------------------------------------
	//// Check) 
	////----------------------------------------------------------------
	//// 1) p_p3DView가 NULL이어서는 안된다.
	//CGASSERT(p_pView3D!=NULL,);


	//// -----------------------------------------------------------------
	//// 1. Attached Scenenode를 Rneder한다.
	//// -----------------------------------------------------------------
	//// 1) Attached Node를 모조리 Rendering한다.
	//for(auto& iter:m_vectorRenderSub)
	//{
	//	iter->Render(p_rRC);
	//}
}


}
