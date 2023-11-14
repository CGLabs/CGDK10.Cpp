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
// ICG3DBoundCullable
//
// 1. ICG3DBoundCullable는...
//    1) Renderable::View::C3D에 Scene Graph가 되는 class들이다.
//    2) Scene Graph에 붙을 수 있는 class가 되려면 이 Class를 상속받아야 한다.
//    3) 단순히 ProcessRender()함수를 interface로 가진 함수라고 보면 된다.
//
// 2. ICG3DBoundCullable의 Function
//    1) ProcessRender()
//       - 핵심 Interface로 Render의 과정이 정의되는 함수이다.
//       - View에서 이 함수를 호출함으로써 Render가 수행된다.
//
//    2) Boundable의 flag
//       - Scene Node를 수행할지 말지에 대한 결정을 수행하는 함수이다.
//       - Disable이 되면 진행이 되지 않으며 Enable이 되면 진행한다.
//
//
//-----------------------------------------------------------------------------
class ICG3DBoundable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICG3DBoundable() : m_bEnableCulling(true)				{}
	virtual	~ICG3DBoundable()										{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) QUeryBounding
			BOUNDINGSTATUS		QueryPicking(CGMSG_BOUNDING_SEGMENT& _Msg){	RETURN_IF(m_bEnableCulling==false, BOUNDINGSTATUS_OUTSIDE); return ProcessQueryPicking(_Msg);}
			BOUNDINGSTATUS		QueryCollision(CGMSG_IBOUNDING& _Msg)		{	RETURN_IF(m_bEnableCulling==false, BOUNDINGSTATUS_OUTSIDE); return ProcessQueryCollision(_Msg);}
			BOUNDINGSTATUS		QueryCulling(const CG3D::PLANE_ARRAY& p_rBoundingView)	{	RETURN_IF(m_bEnableCulling==false, BOUNDINGSTATUS_INTERSECT); return ProcessQueryCulling(p_rBoundingView);}

	// 2) Node Enable/Disable Flags
			void				SetPickingStatus(bool p_bStatus)		{	m_bEnableCulling=p_bStatus;}
			void				EnableCulling()							{	m_bEnableCulling=true;}
			void				DisableCulling()						{	m_bEnableCulling=false;}
			void				ToggleCulling()							{	m_bEnableCulling=!m_bEnableCulling;}

			bool				IsCullingEnable() const					{	return	m_bEnableCulling;}
			bool				IsCullingDisable() const				{	return	!IsCullingEnable();}

	// 3) Attach/Detach
	virtual	bool				AttachBounding(ICG3DBounding* p_pBounding) PURE;
	virtual	bool				DetachBounding(ICG3DBounding* p_pBounding) PURE;
	

// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) QueryBounding
	virtual	BOUNDINGSTATUS		ProcessQueryPicking(CGMSG_BOUNDING_SEGMENT& _Msg) PURE;
	virtual	BOUNDINGSTATUS		ProcessQueryCollision(CGMSG_IBOUNDING& _Msg) PURE;
	virtual	BOUNDINGSTATUS		ProcessQueryCulling(const CG3D::PLANE_ARRAY& p_rBoundingView) PURE;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Enable Scene node
			bool				m_bEnableCulling;
};
