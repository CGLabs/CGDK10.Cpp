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
// CG3D::IScenenode
//
// 1. IScenenode는...
//    1) Renderable::View::C3D에 Scene Graph가 되는 class들이다.
//    2) Scene Graph에 붙을 수 있는 class가 되려면 이 Class를 상속받아야 한다.
//    3) 단순히 ProcessRender()함수를 interface로 가진 함수라고 보면 된다.
//
// 2. IScenenode의 Function
//    1) ProcessRender()
//       - 핵심 Interface로 Render의 과정이 정의되는 함수이다.
//       - View에서 이 함수를 호출함으로써 Render가 수행된다.
//
//    2) Scenenode의 flag
//       - Scene Node를 수행할지 말지에 대한 결정을 수행하는 함수이다.
//       - Disable이 되면 진행이 되지 않으며 Enable이 되면 진행한다.
//
//
//-----------------------------------------------------------------------------
template<class TSCENECOMPONENT=ICG3DSceneComponent>
class ICG3DSceneNode : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICG3DSceneComponent,
	public						NCGAttachable<TSCENECOMPONENT>
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICG3DSceneNode()											{}
	virtual	~ICG3DSceneNode()											{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Detach All
			void				DetachAllSceneComponent();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Process Render
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER&  _MSGRender) override;

	// 3) Attach/Detach
	virtual	bool				ProcessAttach(TSCENECOMPONENT* _pScenenode) override;
	virtual	bool				ProcessDetach(TSCENECOMPONENT* _pScenenode) override;


// ****************************************************************************
// Message)
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

protected:
	// Declare) 
	DECLARE_CGMESSAGE_MAP

	// 2) Functions
	virtual	int					OnFunction_Attach		(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	int					OnFunction_Detach		(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	int					OnFunction_Find			(CGMSG_FIND_BY_NAME<ICGObject>& _Msg);
	virtual	int					OnFunction_Find			(CGMSG_FIND_BY_TYPE<ICGObject>& _Msg);
	virtual	int					OnFunction_Search		(CGMSG_SEARCH_BY_TYPE<ICGObject>& _Msg);
	
	virtual	int					OnFunction_AttachBound	(CGMSG_COMMAND_PARAM_PTR<ICG3DBounding>& _Msg);
	virtual	int					OnFunction_DetachBound	(CGMSG_COMMAND_PARAM_PTR<ICG3DBounding>& _Msg);

	// 4) Notify
	virtual	int					ProcessMessage_ToAttached(CGMSG& _Msg);
};

template <class TSCENECOMPONENT>
void ICG3DSceneNode<TSCENECOMPONENT>::DetachAllSceneComponent()
{
	TCONTAINER	vectorTemp = m_container;

	for (auto& iter : vectorTemp)
	{
		ProcessDetach(iter);
	}
}

template <class TSCENECOMPONENT>
int ICG3DSceneNode<TSCENECOMPONENT>::ProcessRender(CGMSG_PROCESS_RENDER&  _MSGRender)
{
	for (auto& iter : m_container)
	{
		// - RequestRender를 한다.
		auto	iReturn	 = (*iter).RequestRender(_MSGRender);

		// Check) iReturn이 0이 아니면 여기서 끝낸다.
		RETURN_IF(iReturn!=0, iReturn);
	}

	// 2) Count...
	_MSGRender.Statistics_OnProcessRenser();

	// Return) 
	return	0;
}

template <class TSCENECOMPONENT>
bool ICG3DSceneNode<TSCENECOMPONENT>::ProcessAttach(TSCENECOMPONENT* _pScenenode)
{
	// Check) _pScenenode가 nullptr이면 안됀다.
	CGASSERT_ERROR(_pScenenode!=nullptr);

	// Check) _pScenenode가 nullptr면 그냥 리턴한다.
	RETURN_IF(_pScenenode==nullptr, false);

	// Check) _pScenenode가 Parent Node와 같으면 안됀다.
	CGASSERT_ERROR(_pScenenode!=m_pParent);

	// Check) 자기 자신이면 안됀다!
	CGASSERT_ERROR(_pScenenode!=this);

	// Check) _pScenenode의 Parent node가 nullptr이어야만 한다.
	CGASSERT_ERROR(_pScenenode->GetParent() == nullptr);

#ifdef _DEBUG
	// 1) 이미 존재하는지 찾는다.
	auto iterFind	 = std::find(m_container.begin(), m_container.end(), _pScenenode);

	// Check) 이미 존재하면 그냥 ASSERT 발생!
	CGASSERT_ERROR(iterFind==m_container.end());

	// Check) 이미 존재하면 그냥 false를 리턴한다.
	RETURN_IF(iterFind!=m_container.end(), false);
#endif

	// 2) 추가를 Notify한다.
	_pScenenode->RequestProcessMessage(CGMSG_AUTOMATION_PTR<ICGObject>(CG3DNOTIFY_ON_ATTACH, (ICGObject*)this));
	ProcessMessage_ToAttached(CGMSG_AUTOMATION_PTR<ICGObject>(CG3DNOTIFY_ON_SIBLING_ATTACH, (ICGObject*)_pScenenode));

	// 3) 추가한다.
	m_container.push_back(_pScenenode);

	// Return) 
	return	true;
}

template <class TSCENECOMPONENT>
bool ICG3DSceneNode<TSCENECOMPONENT>::ProcessDetach(TSCENECOMPONENT* _pScenenode)
{
	// Check) _pScenenode이 nullptr이면 안됀다.
	CGASSERT_ERROR(_pScenenode!=nullptr);

	// Check) _pScenenode이 nullptr이면 안됀다.
	RETURN_IF(_pScenenode==nullptr, false);

	// Check) _pScenenode가 Parent Node와 같으면 안됀다.
	CGASSERT_ERROR(_pScenenode!=m_pParent);

	// Check) 자기 자신이면 안됀다!
	CGASSERT_ERROR(_pScenenode!=this);

	// 1) 존재 하는 Node인지 찾는다.
	auto iterFind	 = std::find(m_container.begin(), m_container.end(), _pScenenode);

	// Check) 이미 존재하면 그냥 false를 리턴한다.
	RETURN_IF(iterFind==m_container.end(), false);

	// 2) 삭제를 Notify한다.
	_pScenenode->RequestProcessMessage(CGMSG_AUTOMATION_PTR<ICGObject>(CG3DNOTIFY_ON_DETACH, (ICGObject*)this));
	ProcessMessage_ToAttached(CGMSG_AUTOMATION_PTR<ICGObject>(CG3DNOTIFY_ON_SIBLING_DETACH, (ICGObject*)_pScenenode));

	// 3) 삭제한다.
	m_container.erase(iterFind);

	// Return) 
	return	true;
}


template <class TSCENECOMPONENT>
BEGIN_CGMESSAGE_MAP(ICG3DSceneNode<TSCENECOMPONENT>)
	// 1) Functions
	CGMESSAGE_TYPE_SUB(CGMESSAGE_MEMBER_FUNCTION, ((CGMSG_COMMAND&)_Msg).dwCommand)
		ON_CGMESSAGE(CGFUNCTION_ATTACH,				OnFunction_Attach,		CGMSG_COMMAND_PARAM_PTR<ICGObject>)
		ON_CGMESSAGE(CGFUNCTION_DETACH,				OnFunction_Detach,		CGMSG_COMMAND_PARAM_PTR<ICGObject>)
		ON_CGMESSAGE(CGFUNCTION_FIND_BY_NAME,		OnFunction_Find,		CGMSG_FIND_BY_NAME<ICGObject>)
		ON_CGMESSAGE(CGFUNCTION_SEARCH_BY_TYPE,		OnFunction_Search,		CGMSG_SEARCH_BY_TYPE<ICGObject>)

		ON_CGMESSAGE(CGFUNCTION_ATTACH_BOUND,		OnFunction_AttachBound,	CGMSG_COMMAND_PARAM_PTR<ICG3DBounding>)
		ON_CGMESSAGE(CGFUNCTION_DETACH_BOUND,		OnFunction_DetachBound,	CGMSG_COMMAND_PARAM_PTR<ICG3DBounding>)
	END_SUB_CGMESSAGE_MAP
END_CGMESSAGE_MAP

template <class TSCENECOMPONENT>
int ICG3DSceneNode<TSCENECOMPONENT>::ProcessMessage(CGMSG& _Msg)
{
	// 1) Message Map을 실행한다.
	EXECUTE_CGMESSAGE_MAP(_Msg);

	// Return)
	return	__super::ProcessMessage(_Msg);
}

template <class TSCENECOMPONENT>
int ICG3DSceneNode<TSCENECOMPONENT>::ProcessMessage_ToAttached(CGMSG& _Msg)
{
	for(auto& iter:m_container)
	{
		// - Dispatch한다.
		auto	result	 = iter->RequestProcessMessage(_Msg);

		// Check) 
		RETURN_IF(result>0, dwResult);
	}

	// Return) 
	return	FALSE;
}

template <class TSCENECOMPONENT>
int ICG3DSceneNode<TSCENECOMPONENT>::OnFunction_Attach(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg)
{
	// 1) Casting 한다.
	CGPTR<ICG3DSceneComponent>	pScenenode	 = dynamic_pointer_cast<ICG3DSceneComponent>(_Msg.pParam);

	// Check) pScenenode는 nullptr이면 끝낸다.
	RETURN_IF(pScenenode.empty(), 0);

	// 2) 추가 한다.
	return	ProcessAttach(pScenenode);
}

template <class TSCENECOMPONENT>
int ICG3DSceneNode<TSCENECOMPONENT>::OnFunction_Detach(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg)
{
	// 1) Casting 한다.
	CGPTR<ICG3DSceneComponent>	pScenenode	 = dynamic_pointer_cast<ICG3DSceneComponent>(_Msg.pParam);

	// Check) pScenenode는 nullptr이면 끝낸다.
	RETURN_IF(pScenenode.empty(), 0);

	// 2) 제거 한다.
	return	ProcessDetach(pScenenode);
}

template <class TSCENECOMPONENT>
int ICG3DSceneNode<TSCENECOMPONENT>::OnFunction_Find(CGMSG_FIND_BY_NAME<ICGObject>& _Msg)
{
	for(auto& iter:m_container)
	{
		if(CGSTRCMP(iter->GetName(), _Msg.strName)==0)
		{
			_Msg.pParam	 = iter;
			return	1;
		}
	}

	if(_Msg.bRecursive)
	{
		for(auto& iter:m_container)
		{
			iter->RequestProcessMessage(_Msg);

			// Check) 
			RETURN_IF(_Msg.pParam.exist(), 1);
		}
	}

	// Return) 
	return	0;
}

template <class TSCENECOMPONENT>
int ICG3DSceneNode<TSCENECOMPONENT>::OnFunction_Find(CGMSG_FIND_BY_TYPE<ICGObject>& _Msg)
{
	for(auto& iter:m_container)
	{
		if((iter->GetObjectType() & _Msg.dwMask)==_Msg.dwType)
		{
			_Msg.pParam	 = iter;
			return	1;
		}
	}

	if(_Msg.bRecursive)
	{
		for(auto& iter:m_container)
		{
			iter->RequestProcessMessage(_Msg);

			// Check) 
			RETURN_IF(_Msg.pParam.exist(), 1);
		}
	}

	// Return) 
	return	0;
}

template <class TSCENECOMPONENT>
int ICG3DSceneNode<TSCENECOMPONENT>::OnFunction_Search(CGMSG_SEARCH_BY_TYPE<ICGObject>& _Msg)
{
	for(auto& iter:m_container)
	{
		if((iter->GetObjectType() & _Msg.dwMask)==_Msg.dwType)
		{
			_Msg.vectorSource.push_back(iter);
		}
	}

	if(_Msg.bRecursive)
	{
		for(auto& iter:m_container)
		{
			iter->RequestProcessMessage(_Msg);
		}
	}

	// Return) 
	return	FALSE;
}

template <class TSCENECOMPONENT>
int ICG3DSceneNode<TSCENECOMPONENT>::OnFunction_AttachBound(CGMSG_COMMAND_PARAM_PTR<ICG3DBounding>& _Msg)
{
	// 1) Boundable Interface가 있는지 확인해 본다.
	ICG3DBoundable*	pBoundable	 = dynamic_cast<ICG3DBoundable*>(this);

	// 2) Boundable Interface가 존재하면 붙인다.
	if(pBoundable!=nullptr)
	{
		pBoundable->AttachBounding(_Msg.pParam);
	}

	// Return) 
	return	TRUE;
}

template <class TSCENECOMPONENT>
int ICG3DSceneNode<TSCENECOMPONENT>::OnFunction_DetachBound(CGMSG_COMMAND_PARAM_PTR<ICG3DBounding>& _Msg)
{
	// 1) Boundable Interface가 있는지 확인해 본다.
	ICG3DBoundable*	pBoundable	 = dynamic_cast<ICG3DBoundable*>(this);

	// 2) Boundable Interface가 존재하면 제거한다.
	if(pBoundable!=nullptr)
	{
		pBoundable->DetachBounding(_Msg.pParam);
	}

	// Return) 
	return	TRUE;
}


































//template <typename TSCENENODE=CG3DScenenode<TSCENENODE, TSCENECOMPONENT>
//		, typename TSCENECOMPONENT=ICG3DSceneComponent>
//class CBase :
//// ****************************************************************************
//// Inherited Classes)
//// ----------------------------------------------------------------------------
//	virtual public				ICG3DSceneNode<>,							// (I) Scenenode
//	public						CGAttachable::NSceneNode<TSCENENODE>,	// (*) Attachable
//	public						CGAttachable::NSceneComponent<TSCENECOMPONENT>,// (*) Attachable
//	public						CGNameable::NString						// (*) Nameable
//{
//// ****************************************************************************
//// Definitions) 
//// ----------------------------------------------------------------------------
//public:
//			typedef	TSCENENODE		TSCENENODE;
//			typedef	TSCENECOMPONENT	TSCENECOMPONENT;
//
//
//// ****************************************************************************
//// Constructor/Destructor) 
//// ----------------------------------------------------------------------------
//public:
//			CBase()				{	SetObjectType(CGOBJECTTYPE_SCENENODE);}
//	virtual ~CBase()			{}
//
//
//// ****************************************************************************
//// Public) 
//// ----------------------------------------------------------------------------
//public:
//	// 1) Clear
//			void				ClearScenenode();
//
//	// 2) Parent Scenenode
//			void				SetParentScenenode(TSCENENODE* p_pNode);
//			void				ResetParentScenenode();
//			CGPTR<TSCENENODE>	GetParentScenenode() const;
//
//	// 3) Child Scenenode
//			CGPTR<TSCENENODE>	FindScenenode(_In_z_ const _CHAR* p_strName);
//
//			
//// ****************************************************************************
//// Message)
//// ----------------------------------------------------------------------------
//public:
//	// Declare) 
//	DECLARE_CGMESSAGE_MAP
//
//	// 1) Functions
//			DWORD				OnFunction_SetParentScenenode		(CGMSG_COMMAND_PARAM_PTR<TSCENENODE>& _Msg);
//			DWORD				OnFunction_GetParentScenenode		(CGMSG_COMMAND_PARAM_PTR<TSCENENODE>& _Msg);
//
//			DWORD				OnFunction_AttachSceneComponent		(CGMSG_COMMAND_PARAM_PTR<TSCENECOMPONENT>& _Msg);
//			DWORD				OnFunction_DetachSceneComponent		(CGMSG_COMMAND_PARAM_PTR<TSCENECOMPONENT>& _Msg);
//			DWORD				OnFunction_FindSceneComponent		(CGMSG_FIND_BY_NAME<TSCENECOMPONENT>& _Msg);
//			DWORD				OnFunction_SearchSceneComponent		(CGMSG_SEARCH_BY_TYPE<TSCENECOMPONENT>& _Msg);
//
//			//DWORD				OnFunction_FindModifierByName		(CGMSG_FIND_BY_NAME<ICG3DModifier>& _Msg);
//			//DWORD				OnFunction_FindModifierByType		(CGMSG_FIND_BY_TYPE<ICG3DModifier>& _Msg);
//			//DWORD				OnFunction_FindModifierByIndex		(CGMSG_FIND_BY_INDEX<ICG3DModifier>& _Msg);
//			//DWORD				OnFunction_SearchModifierByType		(CGMSG_SEARCH_BY_TYPE<ICG3DModifier>& _Msg);


//// ****************************************************************************
//// Framework)
//// ----------------------------------------------------------------------------
//protected:
//	// 1) Process Render
//	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& _MSGRender);
//
//	// 2) Process Render
//	virtual	int					ProcessMessage(CGMSG& _Msg) override;
//
//	// 3) [SceneNode] Attach/Detach
//	virtual	bool				ProcessAttachSceneNode(TSCENENODE* p_pScenenode);
//	virtual	bool				ProcessDetachSceneNode(TSCENENODE* p_pScenenode);
//
//	// 4) [SceneCompoent] Attach/Detach
//	virtual	bool				ProcessAttachSceneComponent(TSCENECOMPONENT* p_pScenenode);
//	virtual	bool				ProcessDetachSceneComponent(TSCENECOMPONENT* p_pScenenode);
//
//
//// ****************************************************************************
//// Implementation)
//// ----------------------------------------------------------------------------
//public:
//	// 1) Parent Scene node
//			CGPTR<TSCENENODE>	m_pnodeParent;
//
//};
//
//

//template <typename TSCENENODE, typename TSCENECOMPONENT>
//void CBase<TSCENENODE, TSCENECOMPONENT>::ClearScenenode()
//{
//	//m_ptmWorld.reset();
//	m_pnodeParent.reset();
//
//	//CGAttachable::NSceneNode<TSCENENODE>::m_container.clear();
//	//CGAttachable::NModifier<TSCENECOMPONENT>::m_container.clear();
//}
//
//template <typename TSCENENODE, typename TSCENECOMPONENT>
//int CBase<TSCENENODE, TSCENECOMPONENT>::ProcessMessage(CGMSG& _Msg)
//{
//	// 1) Automation에 넘긴다.
//	EXECUTE_CGMESSAGE_MAP(_Msg);
//
//	// Return) 
//	return	FALSE;
//}
//
//template <typename TSCENENODE, typename TSCENECOMPONENT>
//void CBase<TSCENENODE, TSCENECOMPONENT>::SetParentScenenode(TSCENENODE* p_pScenenode)
//{
//	// Check) 
//	RETURN_IF(m_pnodeParent==p_pScenenode, );
//
//	// Check) 만에 하나 Child Node 중에 속해 있는지 확인한다.
//	#ifdef _DEBUG
//	CGASSERT_ERROR(std::find(CGAttachable::NSceneNode<TSCENENODE>::m_container.begin(), CGAttachable::NSceneNode<TSCENENODE>::m_container.end(), p_pScenenode)==CGAttachable::NSceneNode<TSCENENODE>::m_container.end());
//	#endif
//
//	// 1) Parent Scenenode를 설정한다.
//	m_pnodeParent	 = p_pScenenode;
//
//	// 2) Notify한다.
//	DispatchMessageToAttached(CGMSG_AUTOMATION_PTR<ICG3DSceneNode>(CG3DNOTIFY_ON_SCENENODE_PARENT_CHANGE, p_pScenenode));
//}
//
//template <typename TSCENENODE, typename TSCENECOMPONENT>
//void CBase<TSCENENODE, TSCENECOMPONENT>::ResetParentScenenode()
//{
//	// Check) 
//	RETURN_IF(m_pnodeParent.empty(), );
//
//	// 1) Parent scenenode를 Reset한다.
//	m_pnodeParent.reset();
//
//	// 2) Notify한다.
//	DispatchMessageToAttached(CGMSG_AUTOMATION_PTR<ICG3DSceneNode>(CG3DNOTIFY_ON_SCENENODE_PARENT_CHANGE, nullptr));
//}
//
//template <typename TSCENENODE, typename TSCENECOMPONENT>
//CGPTR<TSCENENODE> CBase<TSCENENODE, TSCENECOMPONENT>::GetParentScenenode() const
//{
//	return m_pnodeParent;
//}
//
//template <typename TSCENENODE, typename TSCENECOMPONENT>
//CGPTR<TSCENENODE> CBase<TSCENENODE, TSCENECOMPONENT>::FindScenenode(_In_z_ const _CHAR* p_strName)
//{
//	// Check) 
//	RETURN_IF(p_strName==nullptr, CGPTR<TSCENENODE>());
//
//	// Declare) 
//	CGMSG_FIND_BY_NAME<ICG3DSceneNode>	msgQuery(CGFUNCTION_FIND_SCENENODE, p_strName);
//
//	// 1) Query한다.
//	OnFunction_FindChildScenenode(msgQuery);
//
//	// Return) 
//	return	msgQuery.pSource;
//}
//
//template <typename TSCENENODE, typename TSCENECOMPONENT>
//bool CBase<TSCENENODE, TSCENECOMPONENT>::ProcessAttachSceneComponent(TSCENECOMPONENT* p_pModifier)
//{
//	//// Check)
//	//RETURN_IF(p_pModifier==nullptr, false);
//
//	//// 1) 이미 존재하는지 찾는다.
//	//auto iterFind	 = std::find(CGAttachable::NModifier<TSCENECOMPONENT>::m_container.begin(), CGAttachable::NModifier<TSCENECOMPONENT>::m_container.end(), p_pModifier);
//
//	//// Check) 이미 존재하면 그냥 false를 리턴한다.
//	//CGASSERT_ERROR(iterFind==CGAttachable::NModifier<TSCENECOMPONENT>::m_container.end());
//
//	//// Check) 이미 존재하면 그냥 false를 리턴한다.
//	//RETURN_IF(iterFind!=CGAttachable::NModifier<TSCENECOMPONENT>::m_container.end(), false);
//
//	//// 2) 추가를 Notify한다.
//	//p_pModifier->RequestProcessMessage(CGMSG_AUTOMATION_PTR<ICGObject>(CG3DNOTIFY_ON_ATTACH, (ICGObject*)this));
//	//DispatchMessageTo(CGMSG_AUTOMATION_PTR<ICGObject>(CG3DNOTIFY_ON_MODIFIER_SIBLING_ATTACH, (ICGObject*)p_pModifier));
//
//	//// 3) 추가한다.
//	//CGAttachable::NModifier<TSCENECOMPONENT>::m_container.push_back(p_pModifier);
//
//	// Return) 
//	return	true;
//}
//
//template <typename TSCENENODE, typename TSCENECOMPONENT>
//bool CBase<TSCENENODE, TSCENECOMPONENT>::ProcessDetachSceneComponent(TSCENECOMPONENT* p_pModifier)
//{
//	//// Check)
//	//RETURN_IF(p_pModifier==nullptr, false);
//
//	//// 1) 이미 존재하는지 찾는다.
//	//auto iterFind	 = std::find(CGAttachable::NModifier<TSCENECOMPONENT>::m_container.begin(), CGAttachable::NModifier<TSCENECOMPONENT>::m_container.end(), p_pModifier);
//
//	//// Check) 이미 존재하면 그냥 false를 리턴한다.
//	//RETURN_IF(iterFind==CGAttachable::NModifier<TSCENECOMPONENT>::m_container.end(), false);
//
//	//// 2) 삭제를 Notify한다.
//	//p_pModifier->RequestProcessMessage(CGMSG_AUTOMATION_PTR<ICGObject>(CG3DNOTIFY_ON_DETACH, (ICGObject*)this));
//	//DispatchMessageTo(CGMSG_AUTOMATION_PTR<ICGObject>(CG3DNOTIFY_ON_MODIFIER_SIBLING_DETACH, (ICGObject*)p_pModifier));
//
//	//// 3) 삭제한다.
//	//CGAttachable::NModifier<TSCENECOMPONENT>::m_container.erase(iterFind);
//
//	// Return) 
//	return	true;
//}
//
//
//template <typename TSCENENODE, typename TSCENECOMPONENT>
//DWORD CBase<TSCENENODE, TSCENECOMPONENT>::DispatchMessageToAttached(CGMSG& _Msg)
//{
//	for(auto& iter:CGAttachable::NModifier<TSCENECOMPONENT>::m_container)
//	{
//		// - Dispatch한다.
//		auto	iResult	 = iter->RequestProcessMessage(_Msg);
//
//		// Check) 
//		RETURN_IF(iResult!=0, dwResult);
//	}
//
//	// Return) 
//	return	FALSE;
//}
//
//

////// Modifier
////template <typename TSCENENODE, typename TSCENECOMPONENT>
////int CBase<TSCENENODE, TSCENECOMPONENT>::OnFunction_AttachModifier(CGMSG_COMMAND_PARAM_PTR<ICG3DModifier>& _Msg)
////{
////	// 1) Casting한다.
////	CGPTR<TSCENECOMPONENT>	pModifier	 = dynamic_pointer_cast<TSCENECOMPONENT>(_Msg.pSource);
////
////	// 2) 추가한다.
////	ATTACH<ICGObject>(this, pModifier);
////
////	// Return) 
////	return	TRUE;
////}
////
////template <typename TSCENENODE, typename TSCENECOMPONENT>
////int CBase<TSCENENODE, TSCENECOMPONENT>::OnFunction_DetachModifier(CGMSG_COMMAND_PARAM_PTR<ICG3DModifier>& _Msg)
////{
////	// 1) Casting한다.
////	CGPTR<TSCENECOMPONENT>	pModifier	 = dynamic_pointer_cast<TSCENECOMPONENT>(_Msg.pSource);
////
////	// 2) 추가한다.
////	DETACH<ICGObject>(this, pModifier);
////
////	// Return) 
////	return	TRUE;
////}
////
////template <typename TSCENENODE, typename TSCENECOMPONENT>
////int CBase<TSCENENODE, TSCENECOMPONENT>::OnFunction_FindModifierByName(CGMSG_FIND_BY_NAME<ICG3DModifier>& _Msg)
////{
////	_Msg.pSource	 = FindModifierByName(_Msg.strName);
////
////	return	_Msg.pSource.exist();
////}
////
////template <typename TSCENENODE, typename TSCENECOMPONENT>
////int CBase<TSCENENODE, TSCENECOMPONENT>::OnFunction_SearchModifierByType(CGMSG_SEARCH_BY_TYPE<ICG3DModifier>& _Msg)
////{
////	// 1) Child에서 찾는다.
////	for(auto& iter:CGAttachable::NModifier<TSCENECOMPONENT>::m_container)
////	{
////		if((iter->GetObjectType() & _Msg.dwMask)==_Msg.dwType)
////		{
////			_Msg.Add(iter);
////		}
////	}
////
////	// 2) Child의 Child에서 찾는다.
////	for(auto& iter:CGAttachable::NSceneNode<TSCENENODE>::m_container)
////	{
////		iter->RequestProcessMessage(_Msg);
////	}
////
////	return	FALSE;
////}
////
