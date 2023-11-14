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
// CGAttachable::CProgressableList
//
// 1. CGAttachable::CProgressableList��...
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
// 2. CGAttachable::CProgressableList�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
//
//-----------------------------------------------------------------------------
namespace CGAttachable
{

template <typename TUPDATABLE=CGProperty::IUpdatable, typename TCONTAINER_UPDATABLE=list<CGPTR<TUPDATABLE> > >
class CUpdatableList :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGAttachable::IUpdatable				// (I) Attachable Progressable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CUpdatableList()	{}
	virtual	~CUpdatableList()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Progressable Attach/Detach
	virtual	bool				AttachUpdatable(CGProperty::IUpdatable* p_pUpdatable);
	virtual	bool				DetachUpdatable(CGProperty::IUpdatable* p_pUpdatable);

	// 2) ���Ǽ��� ���� �Լ�.
			void				RequestUpdateAttached(float p_fTIme);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			TCONTAINER_UPDATABLE	m_containerUpdatable;
};


template <typename TUPDATABLE, typename TCONTAINER_UPDATABLE>
bool CUpdatableList<TUPDATABLE, TCONTAINER_UPDATABLE>::AttachUpdatable(CGProperty::IUpdatable* p_pUpdatable)
{
	// Check) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pUpdatable!=NULL);

	// 1) ������...
	m_containerUpdatable.push_back(p_pUpdatable);

	// Return) ����!!
	return	true;
}

template <typename TUPDATABLE, typename TCONTAINER_UPDATABLE>
bool CUpdatableList<TUPDATABLE, TCONTAINER_UPDATABLE>::DetachUpdatable(CGProperty::IUpdatable* p_pUpdatable)
{
	// Check) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pUpdatable!=NULL);

	for(auto& iter:m_containerUpdatable)
	{
		CGPTR<CGProperty::IUpdatable> pUpdatableNow	 = iter;

		if(pUpdatableNow == p_pUpdatable)
		{
			// - �����..
			m_containerUpdatable.erase(iter);

			// Return) ����!!
			return	true;
		}
	}

	// Return) ����!!
	return	false;
}

template <typename TUPDATABLE, typename TCONTAINER_UPDATABLE>
void CUpdatableList<TUPDATABLE, TCONTAINER_UPDATABLE>::RequestUpdateAttached(float p_fTIme)
{
	for(auto& iter:m_containerUpdatable)
	{
		iter->RequestUpdate(p_fTIme);
	}
}


}