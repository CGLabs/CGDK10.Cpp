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

class CPortal :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DBounding
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CPortal();
	virtual	~CPortal();


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

	// 3) Clear
			void				CG3DBoundInfo();
			//void				SetBoundingInfo(const CONVAX& p_rBounding);
			//const CONVAX&		GetBounding() const							{	return m_Bounding;}
			//const CONVAX&		GetOriginalBounding() const					{	return m_Bounding_Original;}



// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Original
			int					m_nPortal;
			CG3D::PORTAL		m_Portal[32];
};


}