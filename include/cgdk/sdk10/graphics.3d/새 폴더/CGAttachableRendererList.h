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
// CGAttachable::CRendererList
//
// 1. CGAttachable::CRendererList��...
//    1) �������� Render�� Loop���� Render�� ���ÿ� �����ϴ� ����� ���ߴ�.
//    2) Render�� �ʿ��� ���� ������ ���������� ��� ������ �ְ� �Ѵ�. Render��
//       �� ������ �����ؼ� ��������� �ߺ� ���� �� �ٽ� �������� �ʾƵ� �ǰ�
//       ������ �Ѵ�.
//    3) Linked List����� Ȥ�� Array�� ������ ü������ �ʴ´�! ������ Modify��
//       Ʋ���� Arrange���� �ʿ��ϸ� ������ ������ ������ �� �ǹ̰� ���� ������
//       ��. 2D�� ��쳪 Ȥ�� Sprite���� ���� ������ �ʿ��ϳ� �̷� ���� ��
//       �� ������� ������ �ϸ� Default�� �����ϴ� ������ ���� �ʴ´�.
//       ������ �پ��� ����� ������ ������ �� �ֱ� �����̴�. ���� ��� Arrange
//       �� Z Ordering�� �ؾ��ϴ� ��� Y Ordering�� �ؾ��ϴ� ��쳪 �ʿ� ����
//       ��� �� ���� Ʋ�� �ʿ信 ���� �ٸ� ������ ü���ؾ� �ϱ� �����̴�.
//
//
// 2. CGAttachable::CRendererList�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
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

	// 2) Attached�� ��� Renderer�� Render() �Լ� ȣ���ϱ�
			void				RenderAttached(CONTEXT_RENDERING& p_rRC);
			void				AddRendererAttached(ICGRenderQueue* p_pView);

	// 3) Queue Bound�Լ�.
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
	// Check) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pRenderer!=NULL);

	// 1) Casting�Ѵ�.
	auto*	tempRenderer	 = dynamic_cast<TRENDERER*>(p_pRenderer);

	// Check)
	RETURN_IF(tempRenderer==nullptr, false);

	// 2) ������...
	m_containerRenderer.push_back(tempRenderer);

	// Return) ����!!
	return	true;
}

template <typename TRENDERER, typename TCONTAINER_RENDERER>
bool CRendererList<TRENDERER, TCONTAINER_RENDERER>::DetachRenderer(ICGRenderer* p_pRenderer)
{
	// Check) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pRenderer!=NULL);

	// 1) Casting�Ѵ�.
	auto*	tempRenderer	 = dynamic_cast<TRENDERER*>(p_pRenderer);

	// Check)
	RETURN_IF(tempRenderer==nullptr, false);

	// 2) ã�Ƽ� �����.
	for(auto& iter:m_containerRenderer)
	{
		if(iter == tempRenderer)
		{
			// - �����..
			m_containerRenderer.erase(iter);

			// Return) ����!!
			return	true;
		}
	}

	// Return) ����!!
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
		// - Renderer�� �߰��Ѵ�.
		p_pRenderQueue->AddRenderer(iter);
	}
}

template <typename TRENDERER, typename TCONTAINER_RENDERER>
void CRendererList<TRENDERER, TCONTAINER_RENDERER>::QueueBoundAttached(ICGRenderQueue* /*p_pQueueRenderer*/, const PLANE_ARRAY* /*p_pBoundingPlane*/)
{
	//----------------------------------------------------------------
	// 1. Child Renderer�� QueueBound()�Լ��� ȣ���Ѵ�.
	//----------------------------------------------------------------
	for(auto& iter:m_containerRenderer)
	{
		// 1) Renderer�� �߰��Ѵ�.(���������� Bounding Check�� ������ ���̴�.)
		//iter->QueueBound(p_pQueueRenderer, p_pBoundingPlane);
	}
}

template <typename TRENDERER, typename TCONTAINER_RENDERER>
void CRendererList<TRENDERER, TCONTAINER_RENDERER>::QueueBoundAttached(ICGRenderQueue* /*p_pQueueRenderer*/, const SPHERE* /*p_pBoundingSphere*/)
{
	//----------------------------------------------------------------
	// 1. Child Renderer�� QueueBound()�Լ��� ȣ���Ѵ�.
	//----------------------------------------------------------------
	for(auto& iter:m_containerRenderer)
	{
		// 1) Renderer�� �߰��Ѵ�.(���������� Bounding Check�� ������ ���̴�.)
		//iter->QueueBound(p_pQueueRenderer, p_pBoundingSphere);
	}
}


}