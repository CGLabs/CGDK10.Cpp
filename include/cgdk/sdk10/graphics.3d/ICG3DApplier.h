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
//*****************************************************************************
// Chosanghyun's 3DGame Network Root! = CGNetRootClinet!!!  ( ` ~`)b
//*****************************************************************************
// 1. CGNetRootClient란!
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
//
//
class ICG3DApplier : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICG3DSceneComponent,				// (I) 3D Object
	public						CGNameable::NString					// (@) Nameable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICG3DApplier() : m_eApplierType(APPLIER_TYPE_NONE)			{}
			ICG3DApplier(APPLIER_TYPE p_eType) : m_eApplierType(p_eType)	{}
	virtual	~ICG3DApplier()												{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
			APPLIER_TYPE		GetApplierType() const					{	return m_eApplierType;}
			void				SetApplierType(APPLIER_TYPE p_eType)	{	m_eApplierType=p_eType;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	virtual void				Apply() PURE;

protected:
			APPLIER_TYPE		m_eApplierType;

};
