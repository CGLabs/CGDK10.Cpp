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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// 1. CG3D::CCamera��!
//    1) Client�� ���ǰ� �ϱ� ���� Performance���ٴ� Client���� ���⸦ �߿� 
//       ���� �ξ� �ٸ� Program�� �����ϴ� �߰��� Run�� ���������ν� ���� ó��
//       �� �� �� �ֵ��� �� ���̴�.
//    2) �⺻������ �̰��� Connect�� ������ �� Listen�� �������� �ʴ´�.
//    3) �ҷ��� ����ó���� ������ �Ͽ����Ƿ� Socket Manager�� Socket Pool ����
//       �������� �ʴ´�.
//    4) �׷��� ���ſ� ���� �����ӵ��� ũ�� �����Ͽ��� ���� Pending�������� ����
//       Failure�� ���� ���ݴ�.
//
//
// 2. CGNetRoot�� �ٽ�! Function�� ��� ����
//    1) Run   ������ �ô��ؿ� Socket�� ó���ϰ� I/O�� ó���ϴ� ���̴�.
//             �̰��� Loop�� �־ ���� �ð��������� ó���� �� �־�� �Ѵ�.
//             ���� �ҷ��ָ� �׸�ŭ �����ӵ��� ��������.
//
// 3. ���� ����
//  Run�� �׻� ���� �ð����� ������ ���� I/O�� ���� ó���� �ݵ��� ���־�� �Ѵ�.
//
//-----------------------------------------------------------------------------
namespace CG3D
{

class CCamera : 
// ****************************************************************************
// Inheritied from) 
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CCamera()													{}
			CCamera(const VECTOR3& p_rv3Position, const VECTOR3& p_rv3LookAt, const VECTOR3& p_rv3Up)	{	SetView(p_rv3Position, p_rv3LookAt, p_rv3Up); SetProjection(D3DX_PI/3.0f, 1.0f, 10.0f, 5000.0f);}
			CCamera(const MATRIX& p_rTransformMatrix)					{	SetViewAsTransformMatrix(p_rTransformMatrix);}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) View Info
			void				SetViewAsTransformMatrix(const MATRIX& p_rMatrix);
			void				SetView(const VECTOR3& p_rv3Position, const VECTOR3& p_rv3LookAt, const VECTOR3& p_rv3Up);
			const VECTOR3&		GetViewPosition() const					{	return m_tmCamera._r4v3;}
			const VECTOR3&		GetViewDirection() const				{	return m_tmCamera._r3v3;}
			const VECTOR3&		GetViewUp() const						{	return m_tmCamera._r2v3;}
			const VECTOR3&		GetViewSide() const						{	return m_tmCamera._r1v3;}

	// 2) Projection Info
			void				SetProjection(float _fFOV, float _fAspect, float _fNear, float _fFar)	{	m_fFOV=_fFOV; m_fAspect=_fAspect; m_fNear=_fNear; m_fFar=_fFar;}
			void				SetFOV(float p_fValue)					{	m_fFOV=p_fValue;}
			void				SetAspect(float p_fValue)				{	m_fAspect=p_fValue;}
			void				SetNearPlane(float p_fValue)			{	m_fNear=p_fValue;}
			void				SetFarPlane(float p_fValue)				{	m_fFar=p_fValue;}
			void				SetClippingPlane(float p_fNear, float p_fFar)	{	SetNearPlane(p_fNear); SetFarPlane(p_fFar);}
			float				GetFOV() const							{	return m_fFOV;}
			float				GetAspect() const						{	return m_fAspect;}
			float				GetNearPlane() const					{	return m_fNear;}
			float				GetFarPlane() const						{	return m_fFar;}

	// 3) Transform Matrix
			CG3D::MATRIX&		GetCameraTransformMatrix()				{	return m_tmCamera;}
			const CG3D::MATRIX&	GetCameraTransformMatrix() const		{	return m_tmCamera;}
			CG3D::MATRIX&		GetViewTransformMatrix()				{	return m_tmView;}
			const CG3D::MATRIX&	GetViewTransformMatrix() const			{	return m_tmView;}
			CG3D::MATRIX&		GetProjectionTransformMatrix()			{	return m_tmProjection;}
			const CG3D::MATRIX&	GetProjectionTransformMatrix() const	{	return m_tmProjection;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
	// 1) View Transform Matrix
			CG3D::MATRIX		m_tmCamera;
			CG3D::MATRIX		m_tmView;

	// 2) Projection Transform Matrix
			CG3D::MATRIX		m_tmProjection;

	// 3) FOV/Near/Far
			float				m_fFOV;			// Field Of View
			float				m_fAspect;
			float				m_fNear;		// Near Plane
			float				m_fFar;			// Far Plane
};


}