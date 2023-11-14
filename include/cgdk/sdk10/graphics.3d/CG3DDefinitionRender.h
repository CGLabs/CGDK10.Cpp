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
// CGMSG_RENDER
//
// 1. CGMSG_RENDER는...
//    1) 렌더링을 위한 상황정보를 담고 있는 Class
//
//
//-----------------------------------------------------------------------------
#define	CGMESSAGE_PROCESS_RENDER					(CGMESSAGE_GRAPHICS+1)
#define	CGMESSAGE_RENDER_FORE						(CGMESSAGE_GRAPHICS+2)
#define	CGMESSAGE_RENDER_SHADOWMAP					(CGMESSAGE_GRAPHICS+3)
#define	CGMESSAGE_RENDER_PRELIGHTING				(CGMESSAGE_GRAPHICS+4)
#define	CGMESSAGE_RENDER_DEPTHNORMAL				(CGMESSAGE_GRAPHICS+5)

#define	RENDER_BATCH_TYPE_PRIMITIVE				0
#define	RENDER_BATCH_TYPE_INDEXED_PRIMITIVE		1
#define	RENDER_BATCH_TYPE_PRIMITIVE_UP			2
#define	RENDER_BATCH_TYPE_ETC					3

//-----------------------------------------------------------------------------
// Rendering RENDER
//-----------------------------------------------------------------------------
struct CGMSG_RENDER : public CGMSG
{
public:
	CGPTR<CG3D::CViewport>		pViewport;
	CGPTR<CG3DApplier::CCamera>	pCamera;
	CGPTR<CG3DBounding::CPlanes> pboundView;
	CGPTR<ICG3DSceneComponent>	pScene;
	RENDER_TYPE					dwRenderType;
	int							iRenderPass;

	int							countProcessRender;
	int							countProcessModify;
	int							countRender[RENDER_PASS_MAX];

public:
	void						ResetStatistics()	{	countProcessRender=0; countProcessModify=0; countRender[0]=countRender[1]=countRender[2]=countRender[3]=0;}
	void						Statistics_OnProcessRenser()	{	++countProcessRender;}
	void						Statistics_OnProcessModify()	{	++countProcessModify;}
	void						Statistics_OnRender(int p_iType){	++countRender[p_iType];}

public:
	CGMSG_RENDER() : CGMSG(CGMESSAGE_RENDER_FORE), dwRenderType(RENDER_TYPE_DEFAULT_ALL), iRenderPass(0)	{	ResetStatistics();}
	CGMSG_RENDER(DWORD p_dwType) : CGMSG(p_dwType), dwRenderType(RENDER_TYPE_DEFAULT_ALL), iRenderPass(0)	{	ResetStatistics();}
};


//-----------------------------------------------------------------------------
// Culling Only
//-----------------------------------------------------------------------------
struct CGMSG_PROCESS_RENDER : public CGMSG_RENDER
{
public:
	CGPTR<ICG3DRenderQueue>	pqueueRenderer;

public:
	CGMSG_PROCESS_RENDER() : CGMSG_RENDER(CGMESSAGE_PROCESS_RENDER)	{}
	CGMSG_PROCESS_RENDER(ICG3DRenderQueue* p_iRenderQueue) : CGMSG_RENDER(CGMESSAGE_PROCESS_RENDER), pqueueRenderer(p_iRenderQueue)	{}
};

	//bool	operator=(const CGMSG_PROCESS_RENDER& rhs)	{	pViewport=rhs.pViewport; pCamera=rhs.pCamera; pboundView=rhs.pboundView;}


namespace CG3D
{
	VECTOR4 GetTransformedPosition(const CG3D::VECTOR4& p_rv3Position3D, const CGMSG& p_rcontextRendering);
	VECTOR4 GetTransformedPosition(const CG3D::VECTOR4& p_rv3Position3D, const CG3DApplier::CCamera& p_rCamera, const CG3D::CViewport& p_rViewport);
}
