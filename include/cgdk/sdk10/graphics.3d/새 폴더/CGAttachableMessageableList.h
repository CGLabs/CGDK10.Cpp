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
// CGAttachable::CControlableList
//
// 1. CGAttachable::CControlableList는...
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
// 2. CGAttachable::CControlableList의 핵심! Function의 기능 설명
//    1) Render      Render를 시행하는 핵심 구조이다.  
//    2) 음...
//
// 3. 주의 사항
//    음... -_-;;
//
//-----------------------------------------------------------------------------
namespace CGAttachable
{

template <typename TMESSAGEABLE=ICGMessageable, typename TMESSAGEABLE_CONTROLABLE=vector<CGPTR<TMESSAGEABLE> > >
class CMessageableList :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGAttachable::IMessageable				// (I) Attachable Controlable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CMessageableList()	{}
	virtual	~CMessageableList()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Controlable Attach/Detach
	virtual	bool				AttachMessageable(ICGMessageable* p_pControlable);
	virtual	bool				DetachMessageable(ICGMessageable* p_pControlable);

	// 2) 편의성을 위한 함수.
			uint32_t			ProcessMessageAttached(CGMSG& p_Message);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			TMESSAGEABLE_CONTROLABLE	m_containerMessageable;
};


template <typename TMESSAGEABLE, typename TMESSAGEABLE_CONTROLABLE>
bool CMessageableList<TMESSAGEABLE, TMESSAGEABLE_CONTROLABLE>::AttachMessageable(ICGMessageable* p_pMessageable)
{
	// Check) p_p3DRenderer가 NULL이어서는 안된다.
	CGASSERT_ERROR(p_pMessageable!=NULL);

	// 1) Casting한다.
	auto*	pMessageable	 = dynamic_cast<TMESSAGEABLE*>(p_pMessageable);

	// Check)
	RETURN_IF(pMessageable==nullptr, false);

	// 1) 붙히기...
	m_containerMessageable.push_back(pMessageable);

	// Return) 성공!!
	return	true;
}

template <typename TMESSAGEABLE, typename TMESSAGEABLE_CONTROLABLE>
bool CMessageableList<TMESSAGEABLE, TMESSAGEABLE_CONTROLABLE>::DetachMessageable(ICGMessageable* p_pMessageable)
{
	// Check) p_p3DRenderer가 NULL이어서는 안된다.
	CGASSERT_ERROR(p_pMessageable!=NULL);

	for(auto& iter:m_containerMessageable)
	{
		CGPTR<ICGMessageable> pMessageableNow	 = iter;

		if(pMessageableNow == p_pMessageable)
		{
			// - 지우기..
			m_containerMessageable.erase(iter);

			// Return) 성공!!
			return	true;
		}
	}

	// Return) 실패!!
	return	false;
}

template <typename TMESSAGEABLE, typename TMESSAGEABLE_CONTROLABLE>
uint32_t CMessageableList<TMESSAGEABLE, TMESSAGEABLE_CONTROLABLE>::ProcessMessageAttached(CGMSG& _Msg)
{
	for(auto& iter:m_containerMessageable)
	{
		// Declare) 
		DWORD	result	 = iter->DispatchMessage(_Msg);

		// Check) result가 0이 아니라면 바로 리턴한다.
		RETURN_IF(result!=0, result);
	}

	// Return) 찾지 못해서 못지웠다.
	return	0;
}


}