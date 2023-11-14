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
// CGResource::IRestorable
//
// 1. CGResource::IRestorable는...
//    1) Vertex Buffer를 Delcation한 Class이다.
//    2) 이 Class는 일반적으로 new를 해서 생성하지는 않는다.
//	  3) 생성은 Create()함수를 통해 LPD3DTEXTURE가 생성됨으로써 처리가 되며
//    4) 내부적으로 shared기능이 있으므로 주로 이를 통해 사용한다.
//
// 2. CGResource::Buffer::CVretex의 기능 설명
//    1) ()	외부에서 Render를 요구할 때 호출하는 함수이다.
//								내주적으로 ()함수를 호출하도록 되어 있다.
//    2) ()	Rendering의 절차를 정의하는 함수이다.
//								이 class를 상속받아 이 함수를 재정의하는 것이 핵심이다.
//	  3) Renderable Status 함수들
//		 - Renderable을 Enable/Disble하는 함수이다. 또 그 상태를 얻을 수 있는
//         함수들이다.
//
//
//-----------------------------------------------------------------------------
namespace CGResource
{

class IRestorable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			IRestorable();
	virtual ~IRestorable();


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	virtual BOOL				Restore() PURE;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// Class) Restore Manager
	class CManagerRestorable;

	// Static) Restorable Manager
	static	CManagerRestorable	m_ManagerRestorable;
};


}