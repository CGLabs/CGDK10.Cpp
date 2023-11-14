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
// ICG3DRenderQueue
//
// 1. ICG3DRenderQueue��...
//    1) Render Queue�� Interface class�̴�.
//
// 2. ICG3DRenderQueue�� �ٽ�! Function�� ��� ����
//    1) AddRenderer		Queue�� Renderer�� �ִ� �Լ�.
//    2) AddApplier			Queue�� Applicer�� �ִ� �Լ�.
//	  3) ClearQueue			Queue�� ������ ��� ���� �Լ�.
//
// 3. ���� ����
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
