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
// ICG3DBounding
//
// 1. ICG3DBounding는...
//    1) 렌더링을 위한 상황정보를 담고 있는 Class
//
//
//-----------------------------------------------------------------------------
enum CG3DBOUNDING_TYPE
{
	CG3DBT_GENERAL			 = 0,
	CG3DBT_SEGMENT			 = 1,
	CG3DBT_SPHERE			 = 2,
	CG3DBT_AABB				 = 3,
	CG3DBT_OBB				 = 4,
	CG3DBT_PLANE			 = 5,
	CG3DBT_TERRAIN			 = 6,
	CG3DBT_RECT				 = 7,
	CG3DBT_CIRCLE			 = 8,
	CG3DBT_TRIANGLE			 = 9,
	CG3DBT_CAPSULE			 = 10,
	CG3DBT_CYLINDER			 = 11,
	CG3DBT_CONE				 = 12,
	CG3DBT_PORTAL			 = 13,
	CG3DBT_PLANES			 = 14,
	CG3DBT_MAX
};

#define	CG3DFLAG_ALL	0xffffffff

enum CG3DBOUNDING_USAGE
{
	CG3DUT_NONE				 = 0x00,
	CG3DUT_CULLING			 = 0x01,
	CG3DUT_PICKING			 = 0x02,
	CG3DUT_COLLISION		 = 0x04,
	CG3DUT_JOINT			 = 0x08,
	CG3DUT_REFERENCE		 = 0x10,
	CG3DUT_COLLISION_NODE	 = 0x20,
	CG3DUT_BOUND_ALL		 = (CG3DUT_CULLING | CG3DUT_PICKING | CG3DUT_COLLISION)
};

enum CG3DBOUNDING_MODE
{
	CG3DBM_INCLUDE	 = 0,
	CG3DBM_EXCLUDE	 = 1
};


class ICG3DBounding : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGUpdatable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICG3DBounding() : m_dwBoundingUsage(0)		{}
			ICG3DBounding(CG3DBOUNDING_TYPE p_eType, DWORD p_dwBoundingUsage=0) : m_eBoundingType(p_eType), m_dwBoundingUsage(p_dwBoundingUsage)	{}
	virtual	~ICG3DBounding()												{}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) CheckBounding
	virtual	BOUNDINGSTATUS		CheckCollision(CG3D::CONTACT& p_rResult, const ICG3DBounding& p_rBounding) const PURE;

	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::VECTOR3& p_rv3Point) const PURE;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::PLANE& p_rPlane) const PURE;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::PLANE_ARRAY& p_rPlanes) const PURE;
	virtual	BOUNDINGSTATUS		CheckBounding(CG3D::PLANE_ARRAY& p_rResult, const CG3D::PLANE_ARRAY& p_rPlanes) const PURE;
	virtual	BOUNDINGSTATUS		CheckBounding(INTERSECT_INFO* p_pfResultT, const CG3D::LINE& p_rLine) const PURE;
	virtual	BOUNDINGSTATUS		CheckBounding(INTERSECT_INFO* p_pfResultT, const CG3D::SEGMENT& p_rSegment) const PURE;

	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::SPHERE& p_rSphere) const PURE;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::AABB& p_rAABB) const PURE;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::OBB& p_rOBB) const PURE;
	virtual	BOUNDINGSTATUS		CheckBounding(const CG3D::CYLINDER& p_rCylinder) const PURE;

	virtual	BOUNDINGSTATUS		CheckViewCulling(CG3DApplier::CCamera* p_pCamera) const PURE;

	virtual	VECTOR3				GetSupportPoint(const VECTOR3& p_rDirection) const PURE;
	virtual	VECTOR3				GetSupportOriginPoint() const PURE;
		
	// 2) Object Type
			CG3DBOUNDING_TYPE	GetBoundingType() const					{	return m_eBoundingType;}
			void				SetBoundingType(CG3DBOUNDING_TYPE p_dwType){	m_eBoundingType=p_dwType;}

			DWORD				GetBoundingUsage() const				{	return m_dwBoundingUsage;}
			void				SetBoundingUsage(DWORD p_dwUsage)		{	m_dwBoundingUsage=p_dwUsage;}

			CGPTR<CMatrix>		GetTransformMatrix()					{	return m_ptmWorld;}
			void				SetTransformMatrix(CMatrix* p_ptmWorld)	{	m_ptmWorld=p_ptmWorld; ProcessUpdate(CGMSG());}

	// 3) Owner & Parents
			CGPTR<ICGObject>	GetSourceObject() const					{	return m_pSource;}
			void				SetSourceObject(ICGObject* p_pSource)	{	m_pSource=p_pSource;}
			CGPTR<ICGObject>	GetEntityObject() const					{	return m_pEntity;}
			void				SetEntityObject(ICGObject* p_pEntity)	{	m_pEntity=p_pEntity;}

	// 4) Child Bounding
			void				AttachChildBounding(ICG3DBounding* p_pBounding);
			void				DetachChildBounding(ICG3DBounding* p_pBounding);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Bounding Type & Usage
			CG3DBOUNDING_TYPE	m_eBoundingType;
			DWORD				m_dwBoundingUsage;

	// 2) World Transform
			CGPTR<CMatrix>		m_ptmWorld;

	// 3) Parents & Owner
			CGPTR<ICGObject>	m_pSource;
			CGPTR<ICGObject>	m_pEntity;

public:
	// 4) Child Bounding
			vector<CGPTR<ICG3DBounding>>	m_vectorChildBounding;

			BOUNDINGSTATUS		ProcessChildBounding(CGMSG_IBOUNDING& _Msg);


// ----------------------------------------------------------------------------
// Debug) Debug를 위한 것임.
// ----------------------------------------------------------------------------
	// Debug용)
#ifdef	_USE_BOUND_LINE_RENDERER
public:
	virtual	CGPTR<ICG3DRenderer> GetRenderer() const					{	return m_pRendererWire;}
	virtual	void				CreateRenderer()						{}

public:
	// 1) Debug를 위한 Draw용.
	//    - 화면에 Bounding 영역을 그리는 Renderer이다.
			CGPTR<CG3DRenderer::CWire>	m_pRendererWire;

#else
	virtual	CGPTR<ICG3DRenderer> GetRenderer() const					{	return CGPTR<ICG3DRenderer>();}
#endif
};


