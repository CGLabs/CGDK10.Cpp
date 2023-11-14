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
// 1. Renderer Manager
//
//    - Scene Manager는 Scene Graph을 가지고 있는 것이다.
//    - Scene Manager의 주요 구성 요소
//      주요 구성요소는 장면을 구성하는 Renderer들의 SceneGraph를 구성하는
//      역할을 한다.
//      Global Ambient등과 같은 Global Info가 들어간다.
//      또, 상황에 따라서 Clear기능이 들어갈 수도 있으며 각종 Light관련된
//      정보를 가지고 있을 수도 있다.
//
//
//-----------------------------------------------------------------------------
namespace CG3DApplier
{
namespace RenderTarget
{

class CTexture :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CG3DApplier::RenderTarget::CBase				// (@) RenderTarget
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTexture();
			~CTexture();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) 생성관련.
			BOOL				CreateRenderTargetTexture(int p_iPage, D3DFORMAT p_fRenderTarget=D3DFMT_X8R8G8B8);
			void				ClearRenderTargetTexture();
			void				RestoreRenderTargetAndBlt();


	// 2) Attributes
			CGPTR<TEXTURE>		GetRenderTargetTexture(int p_iLayer)	{	return m_ptextureRenderTarget[p_iLayer];}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) RenderTarget Info(여기서는 Texture로 사용해야 하므로...)
			CGPTR<TEXTURE>		m_ptextureRenderTarget[MAX_NUMBEROF_RENDERTARGET];
};


}
}