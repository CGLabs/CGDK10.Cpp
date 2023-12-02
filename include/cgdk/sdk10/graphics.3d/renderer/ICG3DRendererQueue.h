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
// ICG3DRenderQueue
//
// 1. ICG3DRenderQueue는...
//    1) Render Queue의 Interface class이다.
//
// 2. ICG3DRenderQueue의 핵심! Function의 기능 설명
//    1) AddRenderer		Queue에 Renderer를 넣는 함수.
//    2) AddApplier			Queue에 Applicer를 넣는 함수.
//	  3) ClearQueue			Queue의 내용을 모두 비우는 함수.
//
// 3. 주의 사항
//    ...?
//
//-----------------------------------------------------------------------------
class ICG3DRenderQueue : 
	virtual public				ICG3DRenderer,
	virtual public				ICGAttachable<ICG3DRenderer>,
	virtual public				ICGAttachable<ICG3DApplier>
{
// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	virtual	bool				ClearQueue() PURE;


	CGPTR<CG3DApplier::CLight>		m_papplierLightGlobal;
};
