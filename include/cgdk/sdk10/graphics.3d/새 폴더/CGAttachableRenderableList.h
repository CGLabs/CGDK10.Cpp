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
// CGAttachable::CRenderableList
//
// 1. CGAttachable::CRenderableList��...
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
// 2. CGAttachable::CRenderableList�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
//
//-----------------------------------------------------------------------------
namespace CGAttachable
{

template <typename TRENDERABLE=CGProperty::IRenderable, typename TCONTAINER_RENDERABLE=list<CGPTR<TRENDERABLE> > >
class CRenderableList :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGAttachable::IRenderable			// 1) Attachable Base
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CRenderableList()	{}
	virtual	~CRenderableList()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Renderable Attach/Detach
	virtual	bool				AttachRenderable(CGProperty::IRenderable* p_pRenderable);
	virtual	bool				DetachRenderable(CGProperty::IRenderable* p_pRenderable);

	// 2) ���Ǽ��� ���� �Լ�.
			void				RequestRenderableAttached(CONTEXT_RENDERING& p_rRC);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			TCONTAINER_RENDERABLE	m_containerRenderable;
};


template <typename TRENDERABLE, typename TCONTAINER_RENDERABLE>
bool CRenderableList<TRENDERABLE, TCONTAINER_RENDERABLE>::AttachRenderable(CGProperty::IRenderable* p_pRenderable)
{
	// Check) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pRenderable!=NULL);

	// 1) Casting�Ѵ�.
	auto*	pRenderable	 = dynamic_cast<TRENDERABLE*>(p_pRenderable);

	// Check)
	RETURN_IF(pRenderable==nullptr, false);

	// 2) ������...
	m_containerRenderable.push_back(p_pRenderable);

	// Return) ����!!
	return	true;
}

template <typename TRENDERABLE, typename TCONTAINER_RENDERABLE>
bool CRenderableList<TRENDERABLE, TCONTAINER_RENDERABLE>::DetachRenderable(CGProperty::IRenderable* p_pRenderable)
{
	// Check) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pRenderable!=NULL);

	// 1) Casting�Ѵ�.
	auto*	pRenderable	 = dynamic_cast<TRENDERABLE*>(p_pRenderable);

	// Check) 
	RETURN_IF(pRenderable==nullptr, false);

	// 2) ã�Ƽ� �����.
	for(auto& iter:m_containerRenderable)
	{
		CGPTR<CGProperty::IRenderable> pRenderableNow	 = iter;

		if(pRenderableNow == pRenderable)
		{
			// - �����..
			m_containerRenderable.erase(iter);

			// Return) ����!!
			return	true;
		}
	}

	// Return) ����!!
	return	false;
}


template <typename TRENDERABLE, typename TCONTAINER_RENDERABLE>
void CRenderableList<TRENDERABLE, TCONTAINER_RENDERABLE>::RequestRenderableAttached(CONTEXT_RENDERING& p_rRC)
{
	// 1) RequestRender�� �����Ѵ�.
	for(auto& iter:m_containerRenderable)
	{
		iter->RequestRenderable(p_rRC);
	}
}


}