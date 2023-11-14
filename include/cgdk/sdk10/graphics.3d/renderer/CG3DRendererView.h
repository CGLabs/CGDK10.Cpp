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
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CG3DScenenode::CView
//
// 1. CG3DScenenode::CView¶õ!
//    1) 
//    2) 
//    3) 
//    4) 
//
//-----------------------------------------------------------------------------
namespace CG3DRenderer
{
	
class NView :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DRenderer							// (I) Scenenode
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			NView();
	virtual ~NView();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) Init/Destroy
	virtual	void				Destroy();

	// 2) Camera
			void				SetCamera(CG3DApplier::CCamera* p_pCamera);
			CGPTR<CG3DApplier::CCamera> GetCamera() const;

	// 3) Viewport
			void				SetViewport(CG3D::CViewport* p_pViewport);
			CGPTR<CG3D::CViewport> GetViewport() const;

	// 4) Render Queue
	virtual	CGPTR<ICG3DRenderQueue>	GetRenderQueue() const PURE;

	// 5) Scene
			void				SetScene(ICG3DSceneComponent* _pScene)	{	m_pScene=_pScene;}
	CGPTR<ICG3DSceneComponent>	GetScene() const						{	return m_pScene;}
	

// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Render Context
			CGPTR<CG3DApplier::CCamera>		m_papplierCamera;
			CGPTR<CG3D::CViewport>			m_pViewport;
			CGPTR<CG3DBounding::CPlanes>	m_pboundView;

	// 2) Scene Top
			CGPTR<ICG3DSceneComponent>		m_pScene;

};


}
