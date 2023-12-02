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

class CCapsule : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DBounding
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCapsule();
			CCapsule(const CAPSULE& p_rSphere);
	virtual	~CCapsule();


// ****************************************************************************
// 2. 핵심 virtual 함수
// ----------------------------------------------------------------------------
public:
	// 1) Updatable
	virtual	int					ProcessUpdate(CGMSG& _Msg) override;

	// 2) 범용적인 Bounding Object처리를 위한 함수.
	virtual	BOUNDINGSTATUS		CheckCollision(CG3D::CONTACT& p_rResult, const ICG3DBounding& p_rActor) const;
			BOUNDINGSTATUS		CheckCollision(CG3D::CONTACT& p_rResult, const CG3D::SEGMENT& p_rActor) const;
			BOUNDINGSTATUS		CheckCollision(CG3D::CONTACT& p_rResult, const CG3D::SPHERE& p_rActor) const;
			BOUNDINGSTATUS		CheckCollision(CG3D::CONTACT& p_rResult, const CG3D::AABB& p_rActor) const;
			BOUNDINGSTATUS		CheckCollision(CG3D::CONTACT& p_rResult, const CG3D::OBB& p_rActor) const;
			BOUNDINGSTATUS		CheckCollision(CG3D::CONTACT& p_rResult, const CG3D::PLANE& p_rActor) const;

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

	// 3) Bounding info
			void				CG3DBoundInfo();
			void				SetBoundingInfo(const CAPSULE& p_rSphere);
			const CAPSULE&		GetBounding() const							{	return m_Bounding;}
			const CAPSULE&		GetOriginalBounding() const					{	return m_Bounding_Original;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Original Bounding Info
			CG3D::CAPSULE		m_Bounding_Original;

	// 2) Transformed Bounding Info
			CG3D::CAPSULE		m_Bounding;
};


}



	//// 5) Transformed
	//		const VECTOR3&		Center() const							{	return m_Sphere_Original.v3Center;}
	//		const VECTOR3*		GetCenter() const						{	return &m_Sphere_Original.v3Center;}
	//		void				SetCenter(const VECTOR3& p_v3Center)	{	m_Sphere_Original.v3Center=p_v3Center; m_Sphere=m_Sphere_Original;}

	//		float				GetRadiusSqure() const 					{	return m_Sphere_Original.fRadiusSqure;}
	//		float				GetRadius() const						{	return m_Sphere_Original.fRadius;}
	//		void				SetRadius(float p_fRadius)				{	m_Sphere_Original.fRadius=p_fRadius; m_Sphere_Original.fRadiusSqure=p_fRadius*p_fRadius; m_Sphere=m_Sphere_Original;}

	//		const VECTOR3&		TransformedCenter() const				{	return m_Sphere.v3Center;}
	//		const VECTOR3*		GetTransformedCenter() const 			{	return (VECTOR3*)&m_Sphere.v3Center;}
	//		const SPHERE&		TransformedSphere() const				{	return m_Sphere;}
	//		const SPHERE*		GetTransformedSphere() const			{	return &m_Sphere;}
