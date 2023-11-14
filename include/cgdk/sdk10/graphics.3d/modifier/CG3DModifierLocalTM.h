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
// 1. CG3DRendererMesh는...
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
namespace CG3DModifier
{

class CLocalTM : 
// ****************************************************************************
// 1. 상속한 Super Class들
// ----------------------------------------------------------------------------
	virtual public				ICG3DModifier							// (I) Modifier
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CLocalTM();
			CLocalTM(const MATRIX& p_ptmLocal);
	virtual ~CLocalTM();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Clear
			void				ClearModifierLocalTM();

	// 2) Target Transform matrix
			void				SetTargetTransformMatrix(CMatrix* p_pTransformMatrix)		{	m_ptmTarget=p_pTransformMatrix;}
			void				ResetTargetTransformMatrix()								{	m_ptmTarget.reset();}
			CGPTR<CMatrix>		GetTargetTransformMatrix() const							{	return m_ptmTarget;}

	// 3) Parent Transform matrix
			void				SetParentTransformMatrix(CMatrix* p_pTransformMatrix)		{	m_ptmParent=p_pTransformMatrix;}
			void				ResetParentTransformMatrix()								{	m_ptmParent.reset();}
			CGPTR<CMatrix>		GetParentTransformMatrix() const							{	return m_ptmParent;}

	// 4) Local Transform matrix
			void				SetLocalTransformMatrix(const MATRIX& p_rTransformMatrix)	{	RETURN_IF(m_ptmLocal.empty(), ); *m_ptmLocal=p_rTransformMatrix;}
			void				SetLocalTransformMatrix(CMatrix* p_pTransformMatrix)		{	m_ptmLocal=p_pTransformMatrix;}
			CGPTR<CMatrix>		GetLocalTransformMatrix() const								{	return m_ptmLocal;}


// ****************************************************************************
// Message)
// ----------------------------------------------------------------------------
public:
	// Declare) 
	DECLARE_CGMESSAGE_MAP

	// 1) Functions
	virtual	uint32_t			OnFunction_SetTargetTransformMatrix		(CGMSG_SET<CMatrix>& _Msg);
	virtual	uint32_t			OnFunction_GetTargetTransformMatrix		(CGMSG_GET<CMatrix>& _Msg);

	virtual	uint32_t			OnFunction_SetParentTransformMatrix		(CGMSG_SET<CMatrix>& _Msg);
	virtual	uint32_t			OnFunction_GetParentTransformMatrix		(CGMSG_GET<CMatrix>& _Msg);

	virtual	uint32_t			OnFunction_SetLocalTransformMatrix		(CGMSG_SET<CMatrix>& _Msg);
	virtual	uint32_t			OnFunction_GetLocalTransformMatrix		(CGMSG_GET<CMatrix>& _Msg);


	// 2) Notifications for Automation
	virtual	uint32_t			OnNotify_OnWorldTransformMatrixChange	(CGMSG_COMMAND_PARAM_PTR<CMatrix>& _Msg);
	virtual	uint32_t			OnNotify_OnAttach						(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	uint32_t			OnNotify_OnDetach						(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	uint32_t			OnNotify_OnParentChange					(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
	// 1) Process Message
	virtual	int					ProcessMessage(CGMSG& _Msg) override;
private:
	// 2) Process Render
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& _MSGRender) override;


protected:
	// 1) Target Transform matrix
			CGPTR<CMatrix>		m_ptmTarget;

	// 2) Parent Transform matrix & Local Transform matrix
			CGPTR<CMatrix>		m_ptmParent;
			CGPTR<CMatrix>		m_ptmLocal;
};


}
