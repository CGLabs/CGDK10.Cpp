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
// ICG3DBoundPickable
//
// 1. ICG3DBoundPickable��...
//    1) Renderable::View::C3D�� Scene Graph�� �Ǵ� class���̴�.
//    2) Scene Graph�� ���� �� �ִ� class�� �Ƿ��� �� Class�� ��ӹ޾ƾ� �Ѵ�.
//    3) �ܼ��� ProcessRender()�Լ��� interface�� ���� �Լ���� ���� �ȴ�.
//
// 2. ICG3DBoundPickable�� Function
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
