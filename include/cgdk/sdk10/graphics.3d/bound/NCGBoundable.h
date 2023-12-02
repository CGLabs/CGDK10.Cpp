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
// ICG3DBoundPickable
//
// 1. ICG3DBoundPickable는...
//    1) Renderable::View::C3D에 Scene Graph가 되는 class들이다.
//    2) Scene Graph에 붙을 수 있는 class가 되려면 이 Class를 상속받아야 한다.
//    3) 단순히 ProcessRender()함수를 interface로 가진 함수라고 보면 된다.
//
// 2. ICG3DBoundPickable의 Function
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
class NCG3DBoundable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICG3DBoundable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NCG3DBoundable();
	virtual	~NCG3DBoundable();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	virtual	bool				AttachBounding(ICG3DBounding* p_pBounding);
	virtual	bool				DetachBounding(ICG3DBounding* p_pBounding);
	virtual	void				ResetBounding();

			CGPTR<ICG3DBounding> GetBoundingPicking() const					{	return m_pboundingPicking;}
			CGPTR<ICG3DBounding> GetBoundingCollision() const				{	return m_pboundingCollision;}
			CGPTR<ICG3DBounding> GetBoundingCulling() const					{	return m_pboundingCulling;}
	

// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) QueryBounding
	virtual	BOUNDINGSTATUS		ProcessQueryPicking(CGMSG_BOUNDING_SEGMENT& _Msg);
	virtual	BOUNDINGSTATUS		ProcessQueryCollision(CGMSG_IBOUNDING& _Msg);
	virtual	BOUNDINGSTATUS		ProcessQueryCulling(const CG3D::PLANE_ARRAY& p_rBoundingView);
			

// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Vector...
			vector<CGPTR<ICG3DBounding>>	m_vectprBounding;

	// 1) Enable Scene node
			CGPTR<ICG3DBounding>	m_pboundingPicking;
			CGPTR<ICG3DBounding>	m_pboundingCollision;
			CGPTR<ICG3DBounding>	m_pboundingCulling;
};
