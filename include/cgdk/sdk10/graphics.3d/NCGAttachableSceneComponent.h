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
// CGAttachable::NSceneComponent
//
// 1. ICGScene��...
//    1) Scene�� ����� �����ϴ� �⺻���� ������ ������ �ִ� Interface Class�̴�.
//    2) Scene�� �⺻������ Message Trigging�� Scene�� Chained working�� �⺻����
//       �����ǰ� �Ǿ� �ִ�.
//
// 2. ICGScene�� �ٽ�! Function�� ��� ����
//    1) CloseScene()	�ݴ� �Լ�. Open()�� �پ��Ҽ� �ֱ� ������ virtual�� �������� �ʴ´�.
//
//
//-----------------------------------------------------------------------------
namespace CGAttachable
{

template <typename TTYPE=ICG3DRenderer, typename TCONTAINER=vector<CGPTR<ICG3DRenderer>>>
class NSceneComponent : 
	virtual public NCGAttachable<TTYPE, TCONTAINER>
{
public:
			NSceneComponent()	{}	
	virtual ~NSceneComponent()	{}

public:
	// 1) Detach All
			void				DetachAllRenderer();

	// 2) Renderer
			CGPTR<TTYPE>		FindSceneCompoentByName(_In_z_ const _CHAR* p_strName);
			CGPTR<TTYPE>		FindSceneCompoentByType(DWORD p_dwType);
			CGPTR<TTYPE>		FindSceneCompoentByIndex(int p_iIndex);
};


template <typename TTYPE, typename TCONTAINER>
void NSceneComponent<TTYPE, TCONTAINER>::DetachAllRenderer()
{
	TCONTAINER	vectorTemp	 = m_container;

	for(auto& iter:vectorTemp)
	{
		ProcessDetach(iter);
	}
}


template <typename TTYPE, typename TCONTAINER>
CGPTR<TTYPE> NSceneComponent<TTYPE, TCONTAINER>::FindSceneCompoentByName(_In_z_ const _CHAR* p_strName)
{
	// Check)
	RETURN_IF(p_strName==nullptr, CGPTR<TTYPE>());

	for(auto& iter:m_container)
	{
		if(CGSTRCMP(iter->GetName(), p_strName)==0)
		{
			return	iter;
		}
	}

	// Return) 
	return	CGPTR<TTYPE>();
}

template <typename TTYPE, typename TCONTAINER>
CGPTR<TTYPE> NSceneComponent<TTYPE, TCONTAINER>::FindSceneCompoentByType(DWORD p_dwType)
{
	for(auto& iter:m_container)
	{
		if(iter->GetObjectType()==p_dwType)
		{
			return	iter;
		}
	}

	// Return) 
	return	CGPTR<TTYPE>();
}

template <typename TTYPE, typename TCONTAINER>
CGPTR<TTYPE> NSceneComponent<TTYPE, TCONTAINER>::FindSceneCompoentByIndex(int /*p_iIndex*/)
{
	//for(auto iter:m_container)
	//{
	//	if(CGSTRCMP(iter->GetName(), p_strName)==0)
	//	{
	//		return	iter;
	//	}
	//}

	// Return) 
	return	CGPTR<TTYPE>();
}


}