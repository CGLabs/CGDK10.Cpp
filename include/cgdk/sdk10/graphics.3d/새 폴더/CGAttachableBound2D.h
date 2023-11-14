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
// CGAttachable::Bound::C2D
//
// 1. CGAttachable::Bound::C2D는...
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
// 2. CGAttachable::Bound::C2D의 핵심! Function의 기능 설명
//    1) Render      Render를 시행하는 핵심 구조이다.  
//    2) 음...
//
// 3. 주의 사항
//    음... -_-;;
//
//-----------------------------------------------------------------------------
namespace CGAttachable
{
namespace Bound
{

class C2D :
// ****************************************************************************
// 1. 상속한 Super Class들
// ----------------------------------------------------------------------------
	public						CGAttachable::Bound::CBase
{
// ****************************************************************************
// 2. Bounding Infos
// ----------------------------------------------------------------------------
// 1) Bounding Object (충돌처리용)
//    - Bounding Object는 순수하게 충돌영역을 표시하는 것으로만 사용됩니다.
//    - 그리는 영역이라든지 그런 것에는 사용을 지양합니다. 만약 충돌을 할 필요가 없는 객체라면
//      이 객체를 생성할 필요가 없을 것입니다.
protected:
			CGBound::IBase2D*	m_pBoundingObject;			// 충돌처리를 위한 Object임.

public:
			CGBound::IBase2D* GetBoundingObject()						{	return m_pBoundingObject;}
			void				SetBoundingObject(CGBound::IBase2D* const p_pBoundingObject)		{	m_pBoundingObject=p_pBoundingObject;}

			BOOL const			HaveBoundingObject()					{	return (m_pBoundingObject != NULL);}

public:
			BOOL				CreateAs2DRect(float p_fX, float p_fY, float p_iWidth, float p_iHeight);
			BOOL				CreateAs2DCircle(float p_fRadius, float p_fCenterX=0.0f, float p_fCenterY=0.0f);
			BOOL				Destroy();



// ****************************************************************************
// 3. 생성자/박살자
// ----------------------------------------------------------------------------
public:
			C2D(BOOL p_flgDrawBoundingObject=DEFAULT_DRAW_BOUNDINGOBJECT) : CGAttachable::Bound::CBase(p_flgDrawBoundingObject)		{	SetBoundingObject(NULL);}
			C2D(CGBound::IBase2D* p_pBoundingObject, BOOL p_flgDrawBoundingObject=DEFAULT_DRAW_BOUNDINGOBJECT) : CGAttachable::Bound::CBase(p_flgDrawBoundingObject)	{	SetBoundingObject(p_pBoundingObject);}
	virtual ~C2D();
};


}
}