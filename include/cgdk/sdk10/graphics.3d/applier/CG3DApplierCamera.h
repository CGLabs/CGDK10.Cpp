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
// CG3DApplier::CCamera
//
// 1. CG3DApplier::CCamera란!
//    1) Client에 사용되게 하기 위해 Performance보다는 Client와의 동기를 중요 
//       점을 두어 다른 Program이 동작하는 중간에 Run을 실행함으로써 각종 처리
//       를 할 수 있도록 한 것이다.
//    2) 기본적으로 이것은 Connect만 지원할 뿐 Listen은 지원하지 않는다.
//    3) 소량의 연결처리르 전제로 하였으므로 Socket Manager와 Socket Pool 등은
//       지원하지 않는다.
//    4) 그래도 과거에 비해 반응속도가 크게 증가하였고 각종 Pending현상으로 인한
//       Failure를 거의 없앴다.
//
//
// 2. CG3DApplier::CCamera의 핵심! Function의 기능 설명
//    1) Run   접속을 시대해온 Socket을 처리하고 I/O를 처리하는 것이다.
//             이것을 Loop에 넣어서 일정 시간간격으로 처리를 해 주어야 한다.
//             자주 불러주면 그만큼 반응속도가 빨라진다.
//
// 3. 주의 사항
//  Run을 항상 일정 시간마다 실행을 시켜 I/O에 대한 처리를 반듯이 해주어야 한다.
//
//
//-----------------------------------------------------------------------------
namespace CG3DApplier
{

class CCamera :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DApplier,								// (I) Applier
	public						CG3D::CCamera,							// (@) Camera Info
	public						ICGDeviceGraphic						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCamera();
			CCamera(const CG3DApplier::CCamera& p_rCamera);
	virtual ~CCamera();

public:
			CCamera(const CG3D::CCamera& p_rCamera);
			CCamera(const VECTOR3& p_rv3Location, const VECTOR3& p_rv3LookAt, const VECTOR3& p_rv3Up);
			CCamera(const MATRIX& p_rtmWorld);


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Clear
			void				ClearApplierCamera();
	
	// 2) Source Trasform Matrix
			CGPTR<CMatrix>		GetSourceTransformMatrix() const;
			void				SetSourceTransformMatrix(CMatrix* p_pSource);
			void				ResetSourceTransformMatrix();

	// 3) Attributes
			void				SetCameraInfo(const CG3D::CCamera& p_rCamera) {	*(CG3D::CCamera*)this=p_rCamera;}
			void				SetCameraInfo(const CG3DApplier::CCamera& p_rCamera)	{	*this=p_rCamera;}

			const CG3D::MATRIX&	GetViewProjectionTransformMatrix() const{	return m_tmViewProjection;}
			const PLANE_ARRAY&	GetViewfrustum() const					{	return m_planesViewfrustum;}

	// 4) Apply
	virtual void				Apply();

	// 5) Build
			void				BuildViewTransformMatrix();
			void				BuildProjectionTransformMatrix();
			void				BuildCameraInfo();

	// 6) Modifier
			bool				AttachModifier(ICG3DModifier* p_pModifier);
			bool				DetachModifier(ICG3DModifier* p_pModifier);
			CGPTR<ICG3DModifier> FindModifierByName(_In_z_ const _CHAR* p_strName);
			CGPTR<ICG3DModifier> FindModifierByType(DWORD p_dwIndex);
			CGPTR<ICG3DModifier> FindModifierByIndex(int p_iIndex);


// ****************************************************************************
// Message)
// ----------------------------------------------------------------------------
public:
	// Declare) 
	DECLARE_CGMESSAGE_MAP

	// 1) Functions
	virtual	int					OnFunction_SetWorldTransformMatrix	(CGMSG_SET<CMatrix>& _Msg);
	virtual	int					OnFunction_GetWorldTransformMatrix	(CGMSG_GET<CMatrix>& _Msg);

	virtual	int					OnFunction_AttachModifier			(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	int					OnFunction_DetachModifier			(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	int					OnFunction_FindModifierByName		(CGMSG_FIND_BY_NAME<ICGObject>& _Msg);
	virtual	int					OnFunction_FindModifierByType		(CGMSG_FIND_BY_TYPE<ICGObject>& _Msg);
	virtual	int					OnFunction_FindModifierByIndex		(CGMSG_FIND_BY_INDEX<ICGObject>& _Msg);
	virtual	int					OnFunction_SearchModifierByType		(CGMSG_SEARCH_BY_TYPE<ICGObject>& _Msg);

	// 2) Notifications for Automation
	virtual	int					OnNotify_OnAttach					(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	int					OnNotify_OnDetach					(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	// 1) Process Message
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

	// 2) Process Render
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& _MSGRender) override;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
	// 1) Source Transform Matrix
			CGPTR<CMatrix>		m_ptmSource;

	// 2) ViewProjection Matrix
			MATRIX				m_tmViewProjection;

	// 3) View Frustums
			PLANE_ARRAY			m_planesViewfrustum;

	// 4) Containers
			vector<CGPTR<ICG3DModifier>>	m_containerModifier;

};


}