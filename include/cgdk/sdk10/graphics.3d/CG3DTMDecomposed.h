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
// 1. CG3D::MATRIX_DECOMP��...
//    1) �������� Render�� Loop���� Render�� ���ÿ� �����ϴ� ����� ���ߴ�.
//    2) Render�� �ʿ��� ���� ������ ���������� ��� ������ �ְ� �Ѵ�. Render��
//       �� ������ �����ؼ� ��������� �ߺ� ���� �� �ٽ� �������� �ʾƵ� �ǰ�
//       ������ �Ѵ�.
//    3) Linked List����� Ȥ�� Array�� ������ ü������ �ʴ´�! ������ Modify��
//       Ʋ���� Arrange���� �ʿ��ϸ� ������ ������ ������ �� �ǹ̰� ���� ������
//       ��. 2D�� ��쳪 Ȥ�� Sprite���� ���� ������ �ʿ��ϳ� �̷� ���� ��
//       �� ������� ������ �ϸ� Default�� �����ϴ� ������ ���� �ʴ´�.
//       ������ �پ��� ����� ������ ������ �� �ֱ� �����̴�. ���� ��� Arrange
//       �� Z Ordering�� �ؾ��ϴ� ��� Y Ordering�� �ؾ��ϴ� ��쳪 �ʿ� ����
//       ��� �� ���� Ʋ�� �ʿ信 ���� �ٸ� ������ ü���ؾ� �ϱ� �����̴�.
//
//
// 2. CGNetRoot�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
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

									// 1) Local Matrix�� Compose�Ѵ�.
									Compose(p_pTM);

									// 2) Modified�� FALSE�� �����Ѵ�.
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