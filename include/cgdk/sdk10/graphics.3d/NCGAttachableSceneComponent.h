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
// CGAttachable::NSceneComponent
//
// 1. ICGScene는...
//    1) Scene은 장면을 관리하는 기본적인 구조를 제공해 주는 Interface Class이다.
//    2) Scene은 기본적으로 Message Trigging과 Scene의 Chained working을 기본으로
//       설정되게 되어 있다.
//
// 2. ICGScene의 핵심! Function의 기능 설명
//    1) CloseScene()	닫는 함수. Open()은 다양할수 있기 때문에 virtual로 정의하지 않는다.
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