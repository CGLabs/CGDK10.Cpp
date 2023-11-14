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
// CGAttachable::Bound::C2D
//
// 1. CGAttachable::Bound::C2D��...
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
// 2. CGAttachable::Bound::C2D�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
//
//-----------------------------------------------------------------------------
namespace CGAttachable
{
namespace Bound
{

class C2D :
// ****************************************************************************
// 1. ����� Super Class��
// ----------------------------------------------------------------------------
	public						CGAttachable::Bound::CBase
{
// ****************************************************************************
// 2. Bounding Infos
// ----------------------------------------------------------------------------
// 1) Bounding Object (�浹ó����)
//    - Bounding Object�� �����ϰ� �浹������ ǥ���ϴ� �����θ� ���˴ϴ�.
//    - �׸��� �����̶���� �׷� �Ϳ��� ����� �����մϴ�. ���� �浹�� �� �ʿ䰡 ���� ��ü���
//      �� ��ü�� ������ �ʿ䰡 ���� ���Դϴ�.
protected:
			CGBound::IBase2D*	m_pBoundingObject;			// �浹ó���� ���� Object��.

public:
			CGBound::IBase2D* GetBoundingObject()						{	return m_pBoundingObject;}
			void				SetBoundingObject(CGBound::IBase2D* const p_pBoundingObject)		{	m_pBoundingObject=p_pBoundingObject;}

			BOOL const			HaveBoundingObject()					{	return (m_pBoundingObject != NULL);}

public:
			BOOL				CreateAs2DRect(float p_fX, float p_fY, float p_iWidth, float p_iHeight);
			BOOL				CreateAs2DCircle(float p_fRadius, float p_fCenterX=0.0f, float p_fCenterY=0.0f);
			BOOL				Destroy();



// ****************************************************************************
// 3. ������/�ڻ���
// ----------------------------------------------------------------------------
public:
			C2D(BOOL p_flgDrawBoundingObject=DEFAULT_DRAW_BOUNDINGOBJECT) : CGAttachable::Bound::CBase(p_flgDrawBoundingObject)		{	SetBoundingObject(NULL);}
			C2D(CGBound::IBase2D* p_pBoundingObject, BOOL p_flgDrawBoundingObject=DEFAULT_DRAW_BOUNDINGOBJECT) : CGAttachable::Bound::CBase(p_flgDrawBoundingObject)	{	SetBoundingObject(p_pBoundingObject);}
	virtual ~C2D();
};


}
}