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
// 1. CG3D::MATRIX_DECOMP는...
//    1) 독립적인 Render와 Loop상의 Render를 동시에 지원하는 방법을 택했다.
//    2) Render에 필요한 각종 정보를 독립적으로 모두 가지고 있게 한다. Render시
//       그 값들을 설정해서 사용하지만 중복 설정 시 다시 설정하지 않아도 되게
//       설정을 한다.
//    3) Linked List라든지 혹은 Array의 구조는 체택하지 않는다! 이유는 Modify와
//       틀리게 Arrange등이 필요하며 찍히는 순서는 오히려 별 의미가 없기 때문이
//       다. 2D의 경우나 혹은 Sprite같은 경우는 순서가 필요하나 이런 경우는 다
//       른 방법으로 구현을 하며 Default로 지원하는 구조는 넣지 않는다.
//       이유는 다양한 방법의 구조가 존재할 수 있기 때문이다. 예를 들면 Arrange
//       도 Z Ordering을 해야하는 경우 Y Ordering을 해야하는 경우나 필요 없는
//       경우 등 각기 틀린 필요에 따라 다른 구조를 체택해야 하기 때문이다.
//
//
// 2. CGNetRoot의 핵심! Function의 기능 설명
//    1) Render      Render를 시행하는 핵심 구조이다.  
//    2) 음...
//
// 3. 주의 사항
//    음... -_-;;
//
//-----------------------------------------------------------------------------
#define	MATRIX_COMP_TRANSLATION	0x01
#define	MATRIX_COMP_ROTATION	0x02
#define	MATRIX_COMP_SCALE		0x04
#define	MATRIX_COMP_ALL			0xffffffff


namespace CG3D
{

class MATRIX_DECOMP
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			MATRIX_DECOMP() : m_dwModify(0)										{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 4) Decomped Compose
			void				SetComposeModify(DWORD p_dwMask)				{	m_dwModify=p_dwMask;}
			void				ResetComposeModify()							{	m_dwModify=0;}
			DWORD				GetComposeModify() const						{	return m_dwModify;}

			void				SetTranslation(const VECTOR3& p_rTranslation)	{	m_v3Translation=p_rTranslation;}
			void				SetRotation(const QUATERNION& p_rRotation)		{	m_qtRotation=p_rRotation;}
			void				SetScale(const VECTOR3& p_rScale) 				{	m_v3Scale=p_rScale;}
			void				SetScaleAxis(const QUATERNION& p_rScaleAxis)	{	m_qtScaleAxis=p_rScaleAxis;}

			void				BlendTranslation(const VECTOR3& p_rTranslation, float p_fWeight)	{	if(p_fWeight!=0.0f) {CG3DVec3Lerp(m_v3Translation, p_rTranslation, m_v3Translation, p_fWeight); return;} m_v3Translation=p_rTranslation;}
			void				BlendRotation(const QUATERNION& p_rRotation, float p_fWeight)		{	if(p_fWeight!=0.0f) {CG3DQuaternionSlerp(m_qtRotation, p_rRotation, m_qtRotation, p_fWeight); return;} m_qtRotation=p_rRotation;}
			void				BlendScale(const VECTOR3& p_rScale, float p_fWeight) 				{	if(p_fWeight!=0.0f) {CG3DVec3Lerp(m_v3Scale, p_rScale, m_v3Scale, p_fWeight); return;} m_v3Scale=p_rScale;}
			void				BlendScaleAxis(const QUATERNION& p_rScaleAxis, float p_fWeight)		{	if(p_fWeight!=0.0f) {CG3DQuaternionSlerp(m_qtScaleAxis, p_rScaleAxis, m_qtScaleAxis, p_fWeight); return;} m_qtScaleAxis=p_rScaleAxis;}

			const VECTOR3&		GetTranslation() const							{	return m_v3Translation;}
			const QUATERNION&	GetRotation() const								{	return m_qtRotation;}
			const VECTOR3&		GetScale() const								{	return m_v3Translation;}
			const QUATERNION&	GetScaleAxis() const							{	return m_qtScaleAxis;}

			void				Decompose(const MATRIX& _tm);

			bool				IsModified() const								{	return m_dwModify!=0;}
			bool				IsNoModified() const							{	return m_dwModify==0;}

			void				DoCompose(MATRIX& p_pTM)
								{
									// Check) 
									RETURN_IF(IsNoModified(),)

									// 1) Local Matrix를 Compose한다.
									Compose(p_pTM);

									// 2) Modified를 FALSE로 설정한다.
									ResetComposeModify();
								}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Decomposed Transform Matrix
			DWORD				m_dwModify;

	// 2) Decompos Affained Values
			VECTOR3				m_v3Translation;
			QUATERNION			m_qtRotation;
			VECTOR3				m_v3Scale;
			QUATERNION			m_qtScaleAxis;

	// 3) Functions
			void				Compose(MATRIX& p_pTransformMatrix);
};


}