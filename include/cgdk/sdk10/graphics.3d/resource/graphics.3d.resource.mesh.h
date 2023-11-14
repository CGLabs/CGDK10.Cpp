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
// CGResource::IMesh
//
// 1. CGResource::IMesh��...
//    1) Mesh������ Resource�� Interface class�̴�.
//    2) Draw()����� ������.
//	  3) �ڽ��� Sub Renderer�� ������.
//    4) Sub Rendrer�� Draw�ϴ� DrawSub()�Լ��� ������.
//
// 2. CGResource::IMesh�� ��� ����
//    1) ���� ����.
//
//
//-----------------------------------------------------------------------------
namespace CGResource
{

class IMesh :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGResource,							// (I) Resource
	public						CGNameable::NString						// (@) Nameable	
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~IMesh();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Draw Function
	virtual	BOOL				Draw(CGMSG& _Msg);
			BOOL				DrawSub(int p_iIndex, CGMSG& _Msg);

	// 2) Sub Mesh �����Լ���
	virtual	void				AttachSubMesh(MESH* p_pMesh);
	virtual	void				DetachSubMesh(MESH* p_pMesh);
			CGPTR<MESH>			GetSubMesh(int p_iIndex) const			{	return m_vectorSubMesh.at(p_iIndex);}

	// 3) Operation
	virtual	BOOL				Transform(const MATRIX* /*p_ptm*/)		{	return TRUE;}
	virtual	BOOL				CalculateBoundingSphere(SPHERE& /*p_rBoundingSphere*/)	{	return TRUE;}
	virtual	BOOL				CalculateBoundingBox(AABB& /*p_rAABB*/)	{	return TRUE;}
	virtual	BOOL				CalculateBoundingBox(OBB& /*p_rOBB*/)	{	return TRUE;}

	// 4) Bounding Info
			//const AABB&			GetAABB() const							{	return m_boundAABB;}
			//const OBB&			GetOBB() const							{	return m_boundOBB;}
			//const SPHERE&		GetBoundSphere() const					{	return m_boundSphere;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) Bounding Volume Info
			//CG3D::AABB			m_boundAABB;
			//CG3D::OBB			m_boundOBB;
			//CG3D::SPHERE		m_boundSphere;

	// 2) Sub Mesh
			vector<CGPTR<MESH>> m_vectorSubMesh;
};


}