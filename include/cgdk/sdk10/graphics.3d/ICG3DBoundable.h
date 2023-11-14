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
// ICG3DBoundCullable
//
// 1. ICG3DBoundCullable��...
//    1) Renderable::View::C3D�� Scene Graph�� �Ǵ� class���̴�.
//    2) Scene Graph�� ���� �� �ִ� class�� �Ƿ��� �� Class�� ��ӹ޾ƾ� �Ѵ�.
//    3) �ܼ��� ProcessRender()�Լ��� interface�� ���� �Լ���� ���� �ȴ�.
//
// 2. ICG3DBoundCullable�� Function
//    1) ProcessRender()
//       - �ٽ� Interface�� Render�� ������ ���ǵǴ� �Լ��̴�.
//       - View���� �� �Լ��� ȣ�������ν� Render�� ����ȴ�.
//
//    2) Boundable�� flag
//       - Scene Node�� �������� ������ ���� ������ �����ϴ� �Լ��̴�.
//       - Disable�� �Ǹ� ������ ���� ������ Enable�� �Ǹ� �����Ѵ�.
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
