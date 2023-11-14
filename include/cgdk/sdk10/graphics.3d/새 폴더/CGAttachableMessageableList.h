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
// CGAttachable::CControlableList
//
// 1. CGAttachable::CControlableList��...
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
// 2. CGAttachable::CControlableList�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
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

	// 2) ���Ǽ��� ���� �Լ�.
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
	// Check) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pMessageable!=NULL);

	// 1) Casting�Ѵ�.
	auto*	pMessageable	 = dynamic_cast<TMESSAGEABLE*>(p_pMessageable);

	// Check)
	RETURN_IF(pMessageable==nullptr, false);

	// 1) ������...
	m_containerMessageable.push_back(pMessageable);

	// Return) ����!!
	return	true;
}

template <typename TMESSAGEABLE, typename TMESSAGEABLE_CONTROLABLE>
bool CMessageableList<TMESSAGEABLE, TMESSAGEABLE_CONTROLABLE>::DetachMessageable(ICGMessageable* p_pMessageable)
{
	// Check) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pMessageable!=NULL);

	for(auto& iter:m_containerMessageable)
	{
		CGPTR<ICGMessageable> pMessageableNow	 = iter;

		if(pMessageableNow == p_pMessageable)
		{
			// - �����..
			m_containerMessageable.erase(iter);

			// Return) ����!!
			return	true;
		}
	}

	// Return) ����!!
	return	false;
}

template <typename TMESSAGEABLE, typename TMESSAGEABLE_CONTROLABLE>
uint32_t CMessageableList<TMESSAGEABLE, TMESSAGEABLE_CONTROLABLE>::ProcessMessageAttached(CGMSG& _Msg)
{
	for(auto& iter:m_containerMessageable)
	{
		// Declare) 
		DWORD	result	 = iter->DispatchMessage(_Msg);

		// Check) result�� 0�� �ƴ϶�� �ٷ� �����Ѵ�.
		RETURN_IF(result!=0, result);
	}

	// Return) ã�� ���ؼ� ��������.
	return	0;
}


}