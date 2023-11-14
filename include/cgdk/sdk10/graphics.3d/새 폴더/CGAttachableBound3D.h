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
// CGAttachable::Bound::C3D
//
// 1. CGAttachable::Bound::C3D��...
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
// 2. CGAttachable::Bound::C3D�� �ٽ�! Function�� ��� ����
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

class C3D : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CGAttachable::Bound::CBase
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			C3D(BOOL p_flgDrawBoundingObject=DEFAULT_DRAW_BOUNDINGOBJECT) : CGAttachable::Bound::CBase(p_flgDrawBoundingObject)		{	SetBoundingObject(NULL);}
			C3D(CGBound::IBase3D* p_pBoundingObject, BOOL p_flgDrawBoundingObject=DEFAULT_DRAW_BOUNDINGOBJECT) : CGAttachable::Bound::CBase(p_flgDrawBoundingObject)	{	SetBoundingObject(p_pBoundingObject);}
	virtual ~C3D();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
			CGBound::IBase3D*	GetBoundingObject() const					{	return m_pBoundingObject;}
			void				SetBoundingObject(CGBound::IBase3D* const p_pBoundingObject)	{	m_pBoundingObject=p_pBoundingObject;}

			bool				HaveBoundingObject()					{	return (m_pBoundingObject != NULL);}

			BOUNDINGSTATUS	CheckVisiableStatus(CView3D* p_p3DView, const PLANE_ARRAY* p_pBoundingPlane);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			CGBound::IBase3D*	m_pBoundingObject;
};


}
}