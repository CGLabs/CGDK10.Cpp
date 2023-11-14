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
// 1. CG3D::CCamera란!
//    1) Client에 사용되게 하기 위해 Performance보다는 Client와의 동기를 중요 
//       점을 두어 다른 Program이 동작하는 중간에 Run을 실행함으로써 각종 처리
//       를 할 수 있도록 한 것이다.
//    2) 기본적으로 이것은 Connect만 지원할 뿐 Listen은 지원하지 않는다.
//    3) 소량의 연결처리르 전제로 하였으므로 Socket Manager와 Socket Pool 등은
//       지원하지 않는다.
//    4) 그래도 과거에 비해 반응속도가 크게 증가하였고 각종 Pending현상으로 인한
//       Failure를 거의 없앴다.
//
//
// 2. CGNetRoot의 핵심! Function의 기능 설명
//    1) Run   접속을 시대해온 Socket을 처리하고 I/O를 처리하는 것이다.
//             이것을 Loop에 넣어서 일정 시간간격으로 처리를 해 주어야 한다.
//             자주 불러주면 그만큼 반응속도가 빨라진다.
//
// 3. 주의 사항
//  Run을 항상 일정 시간마다 실행을 시켜 I/O에 대한 처리를 반듯이 해주어야 한다.
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