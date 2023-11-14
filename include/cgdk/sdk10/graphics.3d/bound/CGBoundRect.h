//*****************************************************************************
//*                                                                           *
//*                      Cho SangHyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           CG 3D Object Classes                            *
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
// 1. CG3DBounding::CAABB
//
//-----------------------------------------------------------------------------
namespace CG3DBounding
{

class CRect : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DBounding
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CRect();
	virtual ~CRect();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Updatable
	virtual	int					ProcessUpdate(CGMSG& _Msg) override;

	// 2) 범용적인 Bounding Object처리를 위한 함수.
	virtual	BOUNDINGSTATUS		CheckCollision(CG3D::CONTACT& p_rResult, const ICG3DBounding& p_rBounding) const;

	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::VECTOR3& p_rv3Point) const;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::PLANE& p_rPlane) const;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::PLANE_ARRAY& p_rPlanes) const;
	virtual	BOUNDINGSTATUS		CheckBounding(CG3D::PLANE_ARRAY& p_rResult, const CG3D::PLANE_ARRAY& p_rPlanes) const;
	virtual	BOUNDINGSTATUS		CheckBounding(INTERSECT_INFO* p_pfResultT, const CG3D::LINE& p_rLine) const;
	virtual	BOUNDINGSTATUS		CheckBounding(INTERSECT_INFO* p_pfResultT, const CG3D::SEGMENT& p_rSegment) const;

	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::SPHERE& p_rSphere) const;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::AABB& p_rAABB) const;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::OBB& p_rOBB) const;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::CYLINDER& p_rCylinder) const;

	virtual	BOUNDINGSTATUS		CheckViewCulling(CG3DApplier::CCamera* p_pCamera) const;

	virtual	VECTOR3				GetSupportPoint(const VECTOR3& p_rDirection) const;
	virtual	VECTOR3				GetSupportOriginPoint() const;

	// 3) 설정함수들...
			void				CG3DBoundInfo();
			void				SetBoundingInfo(const CONVAX& p_rBounding);
			const CONVAX&		GetBounding() const							{	return m_Bounding;}
			const CONVAX&		GetOriginalBounding() const					{	return m_Bounding_Original;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Original Bounding Info
			CG3D::CONVAX		m_Bounding_Original;

	// 2) Transformed Bounding Info
			CG3D::CONVAX		m_Bounding;
};


}


	//// 3) Make Bounding Point
	//		void				MakeBoundingPoint();


			//VECTOR4*			GetVertex(int const p_iVertex) 			{	return m_v4Bounding+p_iVertex;}
			//VECTOR4*			GetVertexLeftTop() 						{	return m_v4Bounding+0;}
			//VECTOR4*			GetVertexRightTop()						{	return m_v4Bounding+1;}
			//VECTOR4*			GetVertexLeftBottom() 					{	return m_v4Bounding+2;}
			//VECTOR4*			GetVertexRightBottom()					{	return m_v4Bounding+3;}

			//void				SetVertex(int p_iVertex, const VECTOR4& p_pVertex)	{	m_v4Bounding[p_iVertex] = p_pVertex;;}
			//void				SetVertexLeftTop(const VECTOR4& p_pVertex) 	{	m_v4Bounding[0] = p_pVertex;}
			//void				SetVertexRightTop(const VECTOR4& p_pVertex)	{	m_v4Bounding[1] = p_pVertex;}
			//void				SetVertexLeftBottom(const VECTOR4& p_pVertex) {	m_v4Bounding[2] = p_pVertex;}
			//void				SetVertexRightBottom(const VECTOR4& p_pVertex){	m_v4Bounding[3] = p_pVertex;}
