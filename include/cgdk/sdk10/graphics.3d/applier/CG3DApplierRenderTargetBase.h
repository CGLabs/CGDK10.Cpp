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
// 1. ICGResource��!
//    1) Client�� ���ǰ� �ϱ� ���� Performance���ٴ� Client���� ���⸦ �߿� 
//       ���� �ξ� �ٸ� Program�� �����ϴ� �߰��� Run�� ���������ν� ���� ó��
//       �� �� �� �ֵ��� �� ���̴�.
//    2) �⺻������ �̰��� Connect�� ������ �� Listen�� �������� �ʴ´�.
//    3) �ҷ��� ����ó���� ������ �Ͽ����Ƿ� Socket Manager�� Socket Pool ����
//       �������� �ʴ´�.
//    4) �׷��� ���ſ� ���� �����ӵ��� ũ�� �����Ͽ��� ���� Pending�������� ����
//       Failure�� ���� ���ݴ�.
//
//
// 2. CGNetRoot�� �ٽ�! Function�� ��� ����
//    1) Run   ������ �ô��ؿ� Socket�� ó���ϰ� I/O�� ó���ϴ� ���̴�.
//             �̰��� Loop�� �־ ���� �ð��������� ó���� �� �־�� �Ѵ�.
//             ���� �ҷ��ָ� �׸�ŭ �����ӵ��� ��������.
//
// 3. ���� ����
//  Run�� �׻� ���� �ð����� ������ ���� I/O�� ���� ó���� �ݵ��� ���־�� �Ѵ�.
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