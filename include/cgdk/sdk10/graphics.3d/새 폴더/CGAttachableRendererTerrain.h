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
// CGAttachable::CRendererTerrain
//
// 1. CGAttachable::CRendererTerrain��...
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
// 2. CGAttachable::CRendererTerrain�� �ٽ�! Function�� ��� ����
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
class CRendererTerrain
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CRendererTerrain()	{}
	virtual	~CRendererTerrain()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Renderable Attach/Detach
	virtual	bool				AttachTerrainRenderer(ICGRenderer* p_pRenderer);
	virtual	bool				DetachTerrainRenderer(ICGRenderer* p_pRenderer);

	// 2) Attached�� ��� Renderer�� Render() �Լ� ȣ���ϱ�
			void				RenderTerrain(CONTEXT_RENDERING& p_rRC);
			void				QueueTerrainRendererTo(ICGRenderQueue* p_pView);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			TCONTAINER_RENDERER	m_containerTerrain;
};



template <typename TRENDERER, typename TCONTAINER_RENDERER>
bool CRendererTerrain<TRENDERER, TCONTAINER_RENDERER>::AttachTerrainRenderer(ICGRenderer* p_pRenderer)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pRenderer!=nullptr);


	//----------------------------------------------------------------
	// 1. ������.
	//----------------------------------------------------------------
	// 1) Casting�Ѵ�.
	auto*	tempRenderer	 = dynamic_cast<TRENDERER*>(p_pRenderer);

	// Check) 
	RETURN_IF(tempRenderer==nullptr, false);


	//----------------------------------------------------------------
	// 1. List�� ������.
	//----------------------------------------------------------------
	// 1) ������...
	m_containerTerrain.push_back(tempRenderer);


	// Return) ����!!
	return	true;
}

template <typename TRENDERER, typename TCONTAINER_RENDERER>
bool CRendererTerrain<TRENDERER, TCONTAINER_RENDERER>::DetachTerrainRenderer(ICGRenderer* p_pRenderer)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pRenderer!=nullptr);


	//----------------------------------------------------------------
	// 1. ������.
	//----------------------------------------------------------------
	// 1) Casting�Ѵ�.
	auto*	tempRenderer	 = dynamic_cast<TRENDERER*>(p_pRenderer);

	// Check) Renderer�� NULL�ΰ�?
	RETURN_IF(tempRenderer==nullptr, false);


	//----------------------------------------------------------------
	// 1. List�� ���� ������.
	//----------------------------------------------------------------
	// 1) ã�Ƽ� �����.
	for(auto& iter:m_containerTerrain)
	{
		if(iter == tempRenderer)
		{
			// - �����..
			m_containerTerrain.erase(iter);

			// Return) ����!!
			return	true;
		}
	}

	// Return) ����!!
	return	false;
}



template <typename TRENDERER, typename TCONTAINER_RENDERER>
void CRendererTerrain<TRENDERER, TCONTAINER_RENDERER>::RenderTerrain(CONTEXT_RENDERING& p_rRC)
{
	for(auto& iter:m_containerTerrain)
	{
		iter->Render(p_pView3D, p_RenderType);
	}
}

template <typename TRENDERER, typename TCONTAINER_RENDERER>
void CRendererTerrain<TRENDERER, TCONTAINER_RENDERER>::QueueTerrainRendererTo(ICGRenderQueue* p_pRenderQueue)
{
	for(auto& iter:m_containerTerrain)
	{
		// - Renderer�� �߰��Ѵ�.
		p_pRenderQueue->AddRenderer(iter);
	}
}


}