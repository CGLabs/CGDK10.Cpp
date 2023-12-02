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
// CGAttachable::CRendererList
//
// 1. CGAttachable::CRendererList는...
//    1) 독립적인 Render와 Loop상의 Render를 동시에 지원하는 방법을 택했다.
//    2) Render에 필요한 각종 정보를 독립적으로 모두 가지고 있게 한다. Render시
//       그 값들을 설정해서 사용하지만 중복 설정 시 다시 설정하지 않아도 되게
//       설정을 한다.
//    3) Linked List라든지 혹은 Array의 구조는 체택하지 않는다! 이유는 Modify와
//       틀리게 Arrange등이 필요하며 찍히는 순서는 오히려 별 의미가 없기 때문이
//       다. 2D의 경우나 혹은 Sprite같은 경우는 순서가 필요하나 이런 경우는 다
//       른 방법으로 구현을 하며 Default로 지원하는 구조는 넣지 않는다.
//       이유는 다양한 방법의 구조가 존재할 수 있기 때문이다. 예를 들면 Arrange
//       도 Z Ordering을 해야하는 경우 Y Ordering을 해야하는 경우나 필요 없는
//       경우 등 각기 틀린 필요에 따라 다른 구조를 체택해야 하기 때문이다.
//
//
// 2. CGAttachable::CRendererList의 핵심! Function의 기능 설명
//    1) Render      Render를 시행하는 핵심 구조이다.  
//    2) 음...
//
// 3. 주의 사항
//    음... -_-;;
//
//-----------------------------------------------------------------------------
namespace CGAttachable
{

template <typename TRENDERER=ICGRenderer, typename TCONTAINER_RENDERER=vector<CGPTR<TRENDERER>> >
class CRendererList : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGAttachable::IRenderer
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CRendererList()		{}
	virtual	~CRendererList()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Renderable Attach/Detach
	virtual	bool				AttachRenderer(ICGRenderer* p_pRenderer);
	virtual	bool				DetachRenderer(ICGRenderer* p_pRenderer);

	// 2) Attached된 모든 Renderer의 Render() 함수 호출하기
			void				RenderAttached(CONTEXT_RENDERING& p_rRC);
			void				AddRendererAttached(ICGRenderQueue* p_pView);

	// 3) Queue Bound함수.
			void				QueueBoundAttached(ICGRenderQueue* p_pQueueRenderer, const PLANE_ARRAY* p_pBoundingPlane);
			void				QueueBoundAttached(ICGRenderQueue* p_pQueueRenderer, const SPHERE* p_pBoundingSphere);

	// 4) 
			bool				IsNodeEmpty() const						{	return m_containerRenderer.empty();}
			bool				IsNodeExist() const						{	return !m_containerRenderer.empty();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			TCONTAINER_RENDERER	m_containerRenderer;
};



template <typename TRENDERER, typename TCONTAINER_RENDERER>
bool CRendererList<TRENDERER, TCONTAINER_RENDERER>::AttachRenderer(ICGRenderer* p_pRenderer)
{
	// Check) p_p3DRenderer가 NULL이어서는 안된다.
	CGASSERT_ERROR(p_pRenderer!=NULL);

	// 1) Casting한다.
	auto*	tempRenderer	 = dynamic_cast<TRENDERER*>(p_pRenderer);

	// Check)
	RETURN_IF(tempRenderer==nullptr, false);

	// 2) 붙히기...
	m_containerRenderer.push_back(tempRenderer);

	// Return) 성공!!
	return	true;
}

template <typename TRENDERER, typename TCONTAINER_RENDERER>
bool CRendererList<TRENDERER, TCONTAINER_RENDERER>::DetachRenderer(ICGRenderer* p_pRenderer)
{
	// Check) p_p3DRenderer가 NULL이어서는 안된다.
	CGASSERT_ERROR(p_pRenderer!=NULL);

	// 1) Casting한다.
	auto*	tempRenderer	 = dynamic_cast<TRENDERER*>(p_pRenderer);

	// Check)
	RETURN_IF(tempRenderer==nullptr, false);

	// 2) 찾아서 지운다.
	for(auto& iter:m_containerRenderer)
	{
		if(iter == tempRenderer)
		{
			// - 지우기..
			m_containerRenderer.erase(iter);

			// Return) 성공!!
			return	true;
		}
	}

	// Return) 실패!!
	return	false;
}



template <typename TRENDERER, typename TCONTAINER_RENDERER>
void CRendererList<TRENDERER, TCONTAINER_RENDERER>::RenderAttached(CONTEXT_RENDERING& p_rRC)
{
	for(auto& iter:m_containerRenderer)
	{
		iter->Render(p_rRC);
	}
}

template <typename TRENDERER, typename TCONTAINER_RENDERER>
void CRendererList<TRENDERER, TCONTAINER_RENDERER>::AddRendererAttached(ICGRenderQueue* p_pRenderQueue)
{
	for(auto& iter:m_containerRenderer)
	{
		// - Renderer를 추가한다.
		p_pRenderQueue->AddRenderer(iter);
	}
}

template <typename TRENDERER, typename TCONTAINER_RENDERER>
void CRendererList<TRENDERER, TCONTAINER_RENDERER>::QueueBoundAttached(ICGRenderQueue* /*p_pQueueRenderer*/, const PLANE_ARRAY* /*p_pBoundingPlane*/)
{
	//----------------------------------------------------------------
	// 1. Child Renderer의 QueueBound()함수를 호출한다.
	//----------------------------------------------------------------
	for(auto& iter:m_containerRenderer)
	{
		// 1) Renderer를 추가한다.(내부적으로 Bounding Check를 수행할 것이다.)
		//iter->QueueBound(p_pQueueRenderer, p_pBoundingPlane);
	}
}

template <typename TRENDERER, typename TCONTAINER_RENDERER>
void CRendererList<TRENDERER, TCONTAINER_RENDERER>::QueueBoundAttached(ICGRenderQueue* /*p_pQueueRenderer*/, const SPHERE* /*p_pBoundingSphere*/)
{
	//----------------------------------------------------------------
	// 1. Child Renderer의 QueueBound()함수를 호출한다.
	//----------------------------------------------------------------
	for(auto& iter:m_containerRenderer)
	{
		// 1) Renderer를 추가한다.(내부적으로 Bounding Check를 수행할 것이다.)
		//iter->QueueBound(p_pQueueRenderer, p_pBoundingSphere);
	}
}


}