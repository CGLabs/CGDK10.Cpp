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
// CG3DRenderer::CQueue
//
// 1. CG3DRenderer::Queue::CList��...
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
// 2. CGNetRoot�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
//
//-----------------------------------------------------------------------------
namespace CG3DRenderer
{

template <typename TNODE=ICG3DRenderer, typename TCONTAINER=vector<CGPTR<TNODE>> >
class CQueue : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DRenderer,						// (I) Renderer
	virtual public				ICG3DRenderQueue					// (I) RenderQueue
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CQueue()			{ m_containerQueue.reserve(4096);}
	virtual	~CQueue()			{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Render �Լ�
	virtual	uint32_t			Render(CGMSG_RENDER& _Msg) override;

	// 2) Object ���� �Լ�.
	virtual	bool				ProcessAttach(ICG3DRenderer* p_pRenderer) override;
	virtual	bool				ProcessDetach(ICG3DRenderer* p_pRenderer) override;

	virtual	bool				ProcessAttach(ICG3DApplier* p_pAppier) override;
	virtual	bool				ProcessDetach(ICG3DApplier* p_pAppier) override;
	virtual	bool				ClearQueue() override;

	// 3) Attribute
			int					GetRendererCount()						{ return m_containerQueue.size();}

	// 3) Attributes
			CGPTR<CG3DApplier::CLight>	GetGlobalLight() const			{ return m_papplierLightGlobal; }
			bool				SetGlobalLight(CG3DApplier::CLight* _pLight) { m_papplierLightGlobal=_pLight;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& /*_MSGRender*/);

protected:
			LOCKABLE<TCONTAINER>	m_containerQueue;

			//CGPTR<CG3DApplier::CLight>	m_papplierLightGlobal;
};


template <typename TNODE, typename TCONTAINER>
uint32_t CQueue<TNODE, TCONTAINER>::Render(CGMSG_RENDER& _Msg)
{
	// Check) ResourceMesh�� ������ �׳� ����������.
	RETURN_IF(IsRenderType(_Msg.dwRenderType)==false, FALSE);

	// 1) Normal Rendering Queueó��
	LOCK(m_containerQueue)
	{
		for(auto& iter:m_containerQueue)
		{
			iter->Render(_Msg);
		}
	}

	// Return) 
	return	1;
}

template <typename TNODE, typename TCONTAINER>
bool CQueue<TNODE, TCONTAINER>::ProcessAttach(ICG3DRenderer* p_pRenderer)
{
	// 1) p_Renderer�� NULL�̸� �߰� ��ü�� �ǹ̰� ����.
	ASSERT(p_pRenderer != nullptr);

	// 2) Attach�Ѵ�.
	LOCK(m_containerQueue)
	{
		m_containerQueue.push_back(p_pRenderer);
	}

	// Return) ����!!!
	return	true;
}

template <typename TNODE, typename TCONTAINER>
bool CQueue<TNODE, TCONTAINER>::ProcessDetach(ICG3DRenderer* /*p_pRenderer*/)
{
	// Return) ����!!!
	return	true;
}

template <typename TNODE, typename TCONTAINER>
bool CQueue<TNODE, TCONTAINER>::ProcessAttach(ICG3DApplier* _pAppier)
{
	// 1) p_Renderer�� NULL�̸� �߰� ��ü�� �ǹ̰� ����.
	CGASSERT(_pAppier!=nullptr, false);

	// 2) Attach�Ѵ�.
	if(_pAppier->GetObjectType()==CGOBJECTTYPE_APPLIER_LIGHT)
	{
		// - Light ��ü�� Casting
		CG3DApplier::CLight*	pApplierLight	 = dynamic_cast<CG3DApplier::CLight*>(_pAppier);

		// Check) 
		RETURN_IF(pApplierLight->bEnabled == 0, FALSE);

		// - Directional�� ���...
		switch(_pAppier->GetApplierType())
		{
		case	APPLIER_TYPE_GLOBAL:
				{
					m_papplierLightGlobal	 = pApplierLight;
				}
				break;

		default:
				break;
		}
	}

	// Return)
	return	true;
}

template <typename TNODE, typename TCONTAINER>
bool CQueue<TNODE, TCONTAINER>::ProcessDetach(ICG3DApplier* /*p_pAppier*/)
{
	// Return) ����!!!
	return	TRUE;
}

template <typename TNODE, typename TCONTAINER>
bool CQueue<TNODE, TCONTAINER>::ClearQueue()
{
	// 1) Clear
	LOCK(m_containerQueue)
	{
		m_containerQueue.clear();
	}

	// Return) ����!!!
	return	true;
}

template <typename TNODE, typename TCONTAINER>
int CQueue<TNODE, TCONTAINER>::ProcessRender(CGMSG_PROCESS_RENDER& /*_Msg*/)
{
	// Return) ����!!!
	return	0;
}


}
