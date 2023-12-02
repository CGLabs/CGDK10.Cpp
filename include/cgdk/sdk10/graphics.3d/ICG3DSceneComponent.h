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
class ICG3DSceneComponent : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGObject
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICG3DSceneComponent() : m_bEnableComponent(true)			{}
			ICG3DSceneComponent(uint64_t p_qwType) : ICGObject(p_qwType), m_bEnableComponent(true) {}
			ICG3DSceneComponent(const OBJECT_ID& p_id) : ICGObject(p_id), m_bEnableComponent(true) {}
	virtual	~ICG3DSceneComponent()										{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) ProcessRender 
			int					RequestRender(CGMSG_PROCESS_RENDER& _MSGRender)	{	RETURN_IF(IsSceneComponentDisable(), 0); return ProcessRender(_MSGRender);}

	// 2) Node Enable/Disable Flags
			void				SetSceneComponentStatus(bool p_bStatus)	{	m_bEnableComponent=p_bStatus;}
			void				EnableSceneComponent()					{	m_bEnableComponent=true;}
			void				DisableSceneComponent()					{	m_bEnableComponent=false;}
			void				ToggleSceneComponent()					{	m_bEnableComponent=!m_bEnableComponent;}

			bool				IsSceneComponentEnable() const			{	return	m_bEnableComponent;}
			bool				IsSceneComponentDisable() const			{	return	!IsSceneComponentEnable();}

			CGPTR<ICG3DSceneComponent>	GetParent() const;
			void				SetParent(ICG3DSceneComponent* _Parent);
			void				ResetParent();


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) ProcessRender
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& _MSGRender) PURE;


// ****************************************************************************
// Message)
// ----------------------------------------------------------------------------
protected:
	// Declare) 
	DECLARE_CGMESSAGE_MAP

	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

	// 2) Message to Attached
	virtual	int					ProcessMessage_ToAttached(CGMSG& /*_Msg*/) { return 0;}
	
	// 3) Functions
	virtual	int					OnFunction_SetParent		(CGMSG_SET<ICGObject>& _Msg);
	virtual	int					OnFunction_GetParent		(CGMSG_GET<ICGObject>& _Msg);

	// 4) Notifications for Automation
	virtual	int					OnNotify_OnAttach			(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	int					OnNotify_OnDetach			(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	int					OnNotify_OnSiblingAttach	(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	int					OnNotify_OnSiblingDetach	(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
			

// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Enable Scene node
			bool				m_bEnableComponent;

	// 2) Parent
			CGPTR<ICG3DSceneComponent>	m_pParent;
};

inline void ICG3DSceneComponent::SetParent(ICG3DSceneComponent* p_pScenenode)
{
	// Check) 같은 부모면 그냥 return한다.
	RETURN_IF(m_pParent==p_pScenenode, );

	// 1) Parent Scenenode를 설정한다.
	m_pParent	 = p_pScenenode;

	// 2) Notify한다.
	ProcessMessage_ToAttached(CGMSG_AUTOMATION_PTR<ICGObject>(CG3DNOTIFY_ON_PARENT_CHANGE, (ICGObject*)p_pScenenode));
}

inline void ICG3DSceneComponent::ResetParent()
{
	// Check) Parent가 설정되어 있지 않으면 끝낸다.
	RETURN_IF(m_pParent.empty(), );

	// 1) Parent scenenode를 Reset한다.
	m_pParent.reset();

	// 2) Notify한다.
	ProcessMessage_ToAttached(CGMSG_AUTOMATION_PTR<ICGObject>(CG3DNOTIFY_ON_PARENT_CHANGE, nullptr));
}

inline CGPTR<ICG3DSceneComponent> ICG3DSceneComponent::GetParent() const
{
	return m_pParent;
}

inline BEGIN_CGMESSAGE_MAP(ICG3DSceneComponent)
	// 1) Function
	CGMESSAGE_TYPE_SUB(CGMESSAGE_MEMBER_FUNCTION, ((CGMSG_COMMAND&)_Msg).dwCommand)
	END_SUB_CGMESSAGE_MAP

	// 2) Set
	CGMESSAGE_TYPE_SUB(CGMESSAGE_MEMBER_SET, ((CGMSG_COMMAND&)_Msg).dwCommand)
		ON_CGMESSAGE(CGCOMMAND::PARENT,				OnFunction_SetParent,		CGMSG_SET<ICGObject>)
	END_SUB_CGMESSAGE_MAP

	// 3) Get
	CGMESSAGE_TYPE_SUB(CGMESSAGE_MEMBER_GET, ((CGMSG_COMMAND&)_Msg).dwCommand)
		ON_CGMESSAGE(CGCOMMAND::PARENT,				OnFunction_GetParent,		CGMSG_GET<ICGObject>)
	END_SUB_CGMESSAGE_MAP

	// 4) Automation
	CGMESSAGE_TYPE_SUB(CGMESSAGE_AUTOMATION, ((CGMSG_COMMAND&)_Msg).dwCommand)
		ON_CGMESSAGE(CG3DNOTIFY_ON_ATTACH,			OnNotify_OnAttach,			CGMSG_COMMAND_PARAM_PTR<ICGObject>)
		ON_CGMESSAGE(CG3DNOTIFY_ON_DETACH,			OnNotify_OnDetach,			CGMSG_COMMAND_PARAM_PTR<ICGObject>)
		ON_CGMESSAGE(CG3DNOTIFY_ON_SIBLING_ATTACH,	OnNotify_OnSiblingAttach,	CGMSG_COMMAND_PARAM_PTR<ICGObject>)
		ON_CGMESSAGE(CG3DNOTIFY_ON_SIBLING_DETACH,	OnNotify_OnSiblingDetach,	CGMSG_COMMAND_PARAM_PTR<ICGObject>)
	END_SUB_CGMESSAGE_MAP
END_CGMESSAGE_MAP

inline int ICG3DSceneComponent::ProcessMessage(CGMSG& _Msg)
{
	// 1) Message Map을 실행한다.
	EXECUTE_CGMESSAGE_MAP(_Msg);

	// Return)
	return	0;
}

inline int ICG3DSceneComponent::OnFunction_SetParent(CGMSG_SET<ICGObject>& _Msg)
{
	// 1) Casting
	ICG3DSceneComponent*	pParent	 = dynamic_cast<ICG3DSceneComponent*>(_Msg.pParam.get());

	// 2) Parent Scenenode를 설정한다.
	SetParent(pParent);

	// Return) 
	return	TRUE;
}

inline int ICG3DSceneComponent::OnFunction_GetParent(CGMSG_GET<ICGObject>& _Msg)
{
	// 1) Parent Scenenode를 얻는다.
	_Msg.pParam	 = m_pParent;

	// Return) 
	return	TRUE;
}

inline int ICG3DSceneComponent::OnNotify_OnAttach(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg)
{
	// 1) Casting한다.
	ICG3DSceneComponent*	pParent = dynamic_cast<ICG3DSceneComponent*>(_Msg.pParam.get());

	// Check) Parent가 nullptr이면 그냥 끝낸다.
	RETURN_IF(pParent==nullptr, 0);

	// 2) Parent Node를 얻는다.
	SetParent(pParent);

	// Return) 
	return	CGRETURN_VALUE_CONTINUE;
}

inline int ICG3DSceneComponent::OnNotify_OnDetach(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg)
{
	// Check) 기존의 Parent와 같지 않으면 그냥 끝낸다.
	RETURN_IF(m_pParent != _Msg.pParam, 0);

	// 1) Parent Node를 Reset한다.
	ResetParent();

	// Return) 
	return	CGRETURN_VALUE_CONTINUE;
}

inline int ICG3DSceneComponent::OnNotify_OnSiblingAttach(CGMSG_COMMAND_PARAM_PTR<ICGObject>& /*_Msg*/)
{
	// Return) 
	return	CGRETURN_VALUE_CONTINUE;
}

inline int ICG3DSceneComponent::OnNotify_OnSiblingDetach(CGMSG_COMMAND_PARAM_PTR<ICGObject>& /*_Msg*/)
{
	// Return) 
	return	CGRETURN_VALUE_CONTINUE;
}
