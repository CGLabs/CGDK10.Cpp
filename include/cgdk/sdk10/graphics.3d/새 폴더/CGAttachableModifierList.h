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
// CGAttachable::CModifierList
//
// 1. CGAttachable::CModifierList��...
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
//    1) CGAttachable::CModifierList      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
//
//-----------------------------------------------------------------------------
namespace CGAttachable
{

template <typename TMODIFIER=ICGModifier, typename TCONTAINER_MODIFIER=vector<CGPTR<TMODIFIER>> >
class CModifierList :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGAttachable::IModifier
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CModifierList()		{}
	virtual	~CModifierList()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Modifier Attach/Detach
	virtual	bool				AttachModifier(ICGModifier* p_pModifier);
	virtual	bool				DetachModifier(ICGModifier* p_pModifier);

	// 2) Attached�� Modifier�� Modify()�Լ� ȣ��(���Ǹ� ����)
			void				ProcessModifyAttached();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			TCONTAINER_MODIFIER	m_containerModifier;
};



template <typename TMODIFIER, typename TCONTAINER_MODIFIER>
bool CModifierList<TMODIFIER, TCONTAINER_MODIFIER>::AttachModifier(ICGModifier* p_pModifier)
{
	// Check) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pModifier!=NULL);

	// 1) Casting�Ѵ�.
	auto*	tempModifier	 = dynamic_cast<TMODIFIER*>(p_pModifier);

	// Check)
	RETURN_IF(tempModifier==nullptr, false);

	// 2) ������...
	m_containerModifier.push_back(tempModifier);

	// Return) ����!!
	return	true;
}

template <typename TMODIFIER, typename TCONTAINER_MODIFIER>
bool CModifierList<TMODIFIER, TCONTAINER_MODIFIER>::DetachModifier(ICGModifier* p_pModifier)
{
	// Check) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pModifier!=NULL);

	// 1) Casting�Ѵ�.
	auto*	tempModifier	 = dynamic_cast<TMODIFIER*>(p_pModifier);

	// Check)
	RETURN_IF(tempModifier==nullptr, false);

	// 2) 
	for(auto& iter:m_containerModifier)
	{
		if(iter == tempModifier)
		{
			// - �����..
			m_containerModifier.erase(iter);

			// Return) ����!!
			return	true;
		}
	}

	// Return) ����!!
	return	false;
}


template <typename TMODIFIER, typename TCONTAINER_MODIFIER>
void CModifierList<TMODIFIER, TCONTAINER_MODIFIER>::ProcessModifyAttached()
{
	for(auto& iter:m_containerModifier)
	{
		iter->Modify();
	}
}


}