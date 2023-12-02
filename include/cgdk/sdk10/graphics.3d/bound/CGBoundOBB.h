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

class COBB :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DBounding
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			COBB();
			COBB(const OBB& p_rboxBox);
	virtual	~COBB();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Updatable
	virtual	int					ProcessUpdate(CGMSG& _Msg) override;

	// 2) 범용적인 Bounding Object처리를 위한 함수.
	virtual	BOUNDINGSTATUS		CheckCollision(CG3D::CONTACT& p_rResult, const ICG3DBounding& p_rActor) const;
			BOUNDINGSTATUS		CheckCollision(CG3D::CONTACT& p_rResult, const CG3D::SPHERE& p_rActor) const;
			BOUNDINGSTATUS		CheckCollision(CG3D::CONTACT& p_rResult, const CG3D::CAPSULE& p_rActor) const;
			BOUNDINGSTATUS		CheckCollision(CG3D::CONTACT& p_rResult, const CG3D::PLANE& p_rActor) const;

	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::VECTOR3& p_rv3Point) const;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::PLANE& p_rPlane) const;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::PLANE_ARRAY& p_rPlanes) const;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::SPHERE& p_rSphere) const;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::AABB& p_rAABB) const;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::OBB& p_rOBB) const;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::CYLINDER& p_rCylinder) const;

	virtual	BOUNDINGSTATUS		CheckBounding(CG3D::PLANE_ARRAY& p_rResult, const CG3D::PLANE_ARRAY& p_rPlanes) const;
	virtual	BOUNDINGSTATUS		CheckBounding(INTERSECT_INFO* p_pfResultT, const CG3D::LINE& p_rLine) const;
	virtual	BOUNDINGSTATUS		CheckBounding(INTERSECT_INFO* p_pfResultT, const CG3D::SEGMENT& p_rSegment) const;


	virtual	BOUNDINGSTATUS		CheckViewCulling(CG3DApplier::CCamera* p_pCamera) const;

	virtual	VECTOR3				GetSupportPoint(const VECTOR3& p_rDirection) const;
	virtual	VECTOR3				GetSupportOriginPoint() const;

	// 3) Bounding info
			void				CG3DBoundInfo();
			void				SetBoundingInfo(const OBB& p_rOBB);
			const OBB&			GetBounding() const						{	return m_Bounding;}
			const OBB&			GetOriginalBounding() const				{	return m_Bounding_Original;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Original Bounding Info
			OBB					m_Bounding_Original;

	// 2) Transformed Bounding Info
			OBB					m_Bounding;

	#ifdef _USE_BOUND_LINE_RENDERER
	virtual	void				CreateRenderer();
	#endif
};


}


	//// 5) 
	//		const VECTOR3&		HalfSize() const						{	return m_OBB.v3HalfSize;}
	//		const VECTOR3&		Center() const							{	return m_OBB.Center();}
	//		const CG3D::OBB&	OBB() const								{	return m_OBB;}

	//		VECTOR3				GetHalfSize() const						{	return m_OBB.v3HalfSize;}
	//		VECTOR3				GetCenter() const 						{	return m_OBB.GetCenter();}
	//		CG3D::OBB			GetOBB() const							{	return m_OBB;}

	//		void				SetHalfSize(const VECTOR3& p_rv3Half)	{	m_OBB_Original.v3HalfSize=m_OBB.v3HalfSize=p_rv3Half;}
	//		void				SetCenter(const VECTOR3& p_rCenter)		{	m_OBB_Original.SetCenter(p_rCenter); m_OBB.SetCenter(p_rCenter);}
	//		void				SetBox(const VECTOR3& p_rv3Half, const VECTOR3& p_rv3Center)	{	(VECTOR3)m_OBB_Original.v3HalfSize=p_rv3Half; (VECTOR3)m_OBB_Original.Center()=p_rv3Center; m_OBB=m_OBB_Original;}
	//		void				SetBox(const CG3D::OBB& p_rOBB)			{	m_OBB_Original = m_OBB= p_rOBB;}
	//		void				SetBox(const CG3D::AABB& p_rAABB);

