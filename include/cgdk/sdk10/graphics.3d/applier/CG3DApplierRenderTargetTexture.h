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
// 1. Renderer Manager
//
//    - Scene Manager�� Scene Graph�� ������ �ִ� ���̴�.
//    - Scene Manager�� �ֿ� ���� ���
//      �ֿ� ������Ҵ� ����� �����ϴ� Renderer���� SceneGraph�� �����ϴ�
//      ������ �Ѵ�.
//      Global Ambient��� ���� Global Info�� ����.
//      ��, ��Ȳ�� ���� Clear����� �� ���� ������ ���� Light���õ�
//      ������ ������ ���� ���� �ִ�.
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
	// 1) ��������.
			BOOL				CreateRenderTargetTexture(int p_iPage, D3DFORMAT p_fRenderTarget=D3DFMT_X8R8G8B8);
			void				ClearRenderTargetTexture();
			void				RestoreRenderTargetAndBlt();


	// 2) Attributes
			CGPTR<TEXTURE>		GetRenderTargetTexture(int p_iLayer)	{	return m_ptextureRenderTarget[p_iLayer];}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) RenderTarget Info(���⼭�� Texture�� ����ؾ� �ϹǷ�...)
			CGPTR<TEXTURE>		m_ptextureRenderTarget[MAX_NUMBEROF_RENDERTARGET];
};


}
}