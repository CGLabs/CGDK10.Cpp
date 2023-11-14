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
// CG3DRenderer::CQueue
//
// 1. CG3DRenderer::Queue::CList는...
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
// 2. CGNetRoot의 핵심! Function의 기능 설명
//    1) Render      Render를 시행하는 핵심 구조이다.  
//    2) 음...
//
// 3. 주의 사항
//    음... -_-;;
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
	// 1) Render 함수
	virtual	uint32_t			Render(CGMSG_RENDER& _Msg) override;

	// 2) Object 관리 함수.
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
	// Check) ResourceMesh가 없으면 그냥 돌려보낸다.
	RETURN_IF(IsRenderType(_Msg.dwRenderType)==false, FALSE);

	// 1) Normal Rendering Queue처리
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
	// 1) p_Renderer가 NULL이면 추가 자체가 의미가 없다.
	ASSERT(p_pRenderer != nullptr);

	// 2) Attach한다.
	LOCK(m_containerQueue)
	{
		m_containerQueue.push_back(p_pRenderer);
	}

	// Return) 성공!!!
	return	true;
}

template <typename TNODE, typename TCONTAINER>
bool CQueue<TNODE, TCONTAINER>::ProcessDetach(ICG3DRenderer* /*p_pRenderer*/)
{
	// Return) 성공!!!
	return	true;
}

template <typename TNODE, typename TCONTAINER>
bool CQueue<TNODE, TCONTAINER>::ProcessAttach(ICG3DApplier* _pAppier)
{
	// 1) p_Renderer가 NULL이면 추가 자체가 의미가 없다.
	CGASSERT(_pAppier!=nullptr, false);

	// 2) Attach한다.
	if(_pAppier->GetObjectType()==CGOBJECTTYPE_APPLIER_LIGHT)
	{
		// - Light 객체로 Casting
		CG3DApplier::CLight*	pApplierLight	 = dynamic_cast<CG3DApplier::CLight*>(_pAppier);

		// Check) 
		RETURN_IF(pApplierLight->bEnabled == 0, FALSE);

		// - Directional일 경우...
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
	// Return) 성공!!!
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

	// Return) 성공!!!
	return	true;
}

template <typename TNODE, typename TCONTAINER>
int CQueue<TNODE, TCONTAINER>::ProcessRender(CGMSG_PROCESS_RENDER& /*_Msg*/)
{
	// Return) 성공!!!
	return	0;
}


}
