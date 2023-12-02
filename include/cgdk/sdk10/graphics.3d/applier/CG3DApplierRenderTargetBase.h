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
// 1. ICGResource란!
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
//-----------------------------------------------------------------------------
#define	DEFAULT_BACKCOLOR						0xff000000
#define	MAX_NUMBEROF_RENDERTARGET				4

namespace CG3DApplier
{
namespace RenderTarget
{

class CBase : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DApplier, 
	public						CClearOption
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CBase();
			~CBase();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Apply & Resource
	virtual void				Apply();
			BOOL				RestoreRenderTarget();

	// 2) Create
			void				CreateRenderTargetSurface(int p_iPage, D3DFORMAT p_eRenderTarget=D3DFMT_X8R8G8B8, D3DMULTISAMPLE_TYPE eMultiSample=D3DMULTISAMPLE_NONE, DWORD dwMultisampleQuality=0, BOOL bLockable=FALSE);
			void				CreateDepthStencilSurface(D3DFORMAT p_eDepthStencil=D3DFMT_D24S8, D3DMULTISAMPLE_TYPE eMultiSample=D3DMULTISAMPLE_NONE, DWORD dwMultisampleQuality=0, BOOL bDiscard=FALSE);

	// 3) Attributes
			CGPTR<SURFACE>		GetRenderTargetSurface(int p_iLayer)		{	return m_vectorSurfaceRenderTarget[p_iLayer];}
			void				SetRenderTargetSurface(int p_iLayer, SURFACE* p_psurface)	{	m_vectorSurfaceRenderTarget[p_iLayer]=p_psurface;}

			CGPTR<SURFACE>		GetDepthStencilSurface()					{	return m_psurfaceDepthStencilBuffer;}
			void				SetDepthStencilSurface(SURFACE* p_surface)	{	m_psurfaceDepthStencilBuffer=p_surface;}

			int					GetWidth() const							{	return m_sizeRenderTarget.cx;}
			int					GetHeight() const							{	return m_sizeRenderTarget.cy;}

			void				SetRenderTargetAttribute(int p_iWidth, int p_iHeight)	{	m_sizeRenderTarget.cx=p_iWidth;	m_sizeRenderTarget.cy=p_iHeight;}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) Process Render
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& /*_MSGRender*/) override	{ return 0; }


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) RenderTarget Info
			vector<CGPTR<SURFACE>>	m_vectorSurfaceRenderTarget;
			vector<CGPTR<SURFACE>>	m_vectorSurfaceRenderTargetPre;

	// 2) Depth/Stencil Buffer
			CGPTR<SURFACE>		m_psurfaceDepthStencilBuffer;
			CGPTR<SURFACE>		m_psurfaceDepthStencilBufferPre;

	// 3) Rect
			SIZE				m_sizeRenderTarget;
};


}
}