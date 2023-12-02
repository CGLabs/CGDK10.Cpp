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
// CGAttachable::BoundCBase
//
// 1. CGAttachable::BoundCBase��...
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
// 2. CGAttachable::BoundCBase�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
//
//-----------------------------------------------------------------------------
#define	DEFAULT_DRAW_BOUNDINGOBJECT		FALSE

namespace CGAttachable
{
namespace Bound
{

class CBase : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// 1. Bounding Flag
// ----------------------------------------------------------------------------
protected:
			DWORD			m_maskBounding;
public:
			DWORD			GetBoundingMask() const					{	return m_maskBounding;}
			void			SetBoundingMaskAll(DWORD p_dwMask)		{	m_maskBounding=p_dwMask;}

			void			SetBoundingMask(DWORD p_dwMask)			{	m_maskBounding |=p_dwMask;}
			void			ResetBoundingMask(DWORD p_dwMask)		{	m_maskBounding &=(~p_dwMask);}
			void			ToggleBoundingMask(DWORD p_dwMask)		{	m_maskBounding ^=p_dwMask;}
			DWORD			HaveBoundingMask(DWORD p_dwMask) const	{	return (m_maskBounding & p_dwMask);}


// ****************************************************************************
// Debug) Draw BoundingObject
// ----------------------------------------------------------------------------
protected:
			bool			m_bDrawBoundingObject;
public:
			void			ShowBoundingObject(bool p_bShow=true)	{	m_bDrawBoundingObject=p_bShow;}
			bool			IsDrawBoundingObject()					{	return m_bDrawBoundingObject;}


// ****************************************************************************
// 4. ������/�ڻ���
// ----------------------------------------------------------------------------
			CBase(DWORD p_dwFlag=CG3DFLAG_ALL, bool p_bDrawBoundingObject=DEFAULT_DRAW_BOUNDINGOBJECT) : m_bDrawBoundingObject(p_bDrawBoundingObject)	{	SetBoundingMaskAll(p_dwFlag);}
			~CBase()															{	;}
};

}
}