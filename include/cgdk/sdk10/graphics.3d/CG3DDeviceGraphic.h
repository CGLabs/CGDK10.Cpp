//*****************************************************************************
//*                                                                           *
//*                      Cho SangHyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                             CG Object Classes                             *
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
// ----------------------------------------------------------------------------
//
// ICGDeviceGraphic
//
// 1. ICGDeviceGraphic는...
//    1) Framework의 Interface class임.
//    2) Framework는 Renderable, Progressable, Controllable등의 Top을 가지고 있음.
//    3) 각 Top을 설정가능함.
//
// 2. ICGDeviceGraphic의 핵심! Function의 기능 설명
//    1) Close()...	닫는 함수. Open()은 virtual로 정의하지 않는다.
//	  2) SetStatus()/GetStatus()
//		 장면의 Status를 설정하고 얻는 함수.
//
//
// ----------------------------------------------------------------------------
#define	USE_IIDDIRECT3D			IID_IDirect3D9
typedef	LPDIRECT3D9				LPDIRECT3D;
typedef	LPDIRECT3DDEVICE9		LPDIRECT3DDEVICE;
typedef	IDirect3DBaseTexture9	D3DBASETEXTURE, *LPD3DBASETEXTURE;

namespace CG3D
{
//
//class CDeviceSetting
//{
//public:
//	HWND					PresentTarget;			// Present할 Target HWND (Clipping 정보에 영향을 줌)
//
//	CG3DApplier::CCamera*		AppliedCamera;
//	CViewport*				AppliedViewport;
//	const MATRIX*			AppliedTransformer;
//
//	CGPTR<VERTEXBUFFER>		AppliedVertexBuffer[8];
//	CGPTR<INDEXBUFFER>		AppliedIndexBuffer;
//
//public:
//	~C3DDeviceSetting()		{}
//
//};

	//static	D3DFORMAT			GetSurfaceFormat()																{	return m_DisplayModeInfo.Format;}


class ICGDeviceGraphic 
{
// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// ----------------------------------------------------------------------------
	// 1. D3D Interface & Device
	// ----------------------------------------------------------------------------
	// 1) D3D Interface
	static	void				InitD3D();
	static	void				ReleaseD3D();

	// 2) Device Creat/Destroy
	static	void				CreateDevice(HWND p_hFocusWnd, D3DPRESENT_PARAMETERS& p_rD3DPresentParameters, UINT p_iAdapter=D3DADAPTER_DEFAULT, D3DDEVTYPE p_eDeviceType=D3DDEVTYPE_HAL, DWORD p_flgBehaviorType=D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED);
	static	void				CreateDevice_PerfHud(HWND p_hFocusWnd, D3DPRESENT_PARAMETERS& p_rD3DPresentParameters);
	static	void				InitDevice(LPDIRECT3DDEVICE p_pD3DDevice);
	static	void				DestroyDevice();
	
	// 3) Device Value
	static	LPDIRECT3DDEVICE&	Direct3DDevice()																{	return m_lpDirect3DDevice;}
	static  HWND				GethWnd()																		{	return m_D3DPresentParameters.hDeviceWindow;}

	// 4) Default Font
	static	CGPTR<CGResource::CFont> GetDefaultFont()															{	return m_pDefaultFont;}


	// ----------------------------------------------------------------------------
	// 2. Scene관련
	// ----------------------------------------------------------------------------
	// 1) Begin/End Scene
	static	HRESULT				BeginScene()																	{	return m_lpDirect3DDevice->BeginScene();}
	static	HRESULT				EndScene()																		{	return m_lpDirect3DDevice->EndScene();}

	// 2) Render & Preset
	static	void				Present(HWND p_hPresentTarget);


	// ----------------------------------------------------------------------------
	// 3. Render State 관련
	// ----------------------------------------------------------------------------
	// 1) Basic
	static	HRESULT				SetRenderState(D3DRENDERSTATETYPE State, int Value)								{	return m_lpDirect3DDevice->SetRenderState(State, Value);}
	static	HRESULT				SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)							{	return m_lpDirect3DDevice->SetRenderState(State, Value);}
	static	HRESULT				SetRenderState(D3DRENDERSTATETYPE State, float fValue)							{	return m_lpDirect3DDevice->SetRenderState(State, *(DWORD*)&fValue);}
	static	HRESULT				GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)							{	return m_lpDirect3DDevice->GetRenderState(State, pValue);}
	static	void				SetPointSpriteScale(float p_fPointA, float p_fPointB, float p_fPointC)			{	SetRenderState(D3DRS_POINTSCALE_A, *(DWORD*)&p_fPointA); SetRenderState(D3DRS_POINTSCALE_B, *(DWORD*)&p_fPointB); SetRenderState(D3DRS_POINTSCALE_C, *(DWORD*)&p_fPointC);}

	// 2) Z Buffer
	static	HRESULT				EnableZBuffer()																	{	return m_lpDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);}
	static	HRESULT				DisableZBuffer()																{	return m_lpDirect3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);}
	static	HRESULT				EnableZWrite()																	{	return m_lpDirect3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);}
	static	HRESULT				DisableZWrite()																	{	return m_lpDirect3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);}
	static	void				EnableZ()																		{	EnableZBuffer(); EnableZWrite();}
	static	void				DisableZ()																		{	DisableZBuffer(); DisableZWrite();}

	// 3) Cull Mode
	static	HRESULT				ApplyCullMode(CULL p_CullMode)													{	return SetRenderState(D3DRS_CULLMODE, p_CullMode);}
	static	HRESULT				DisableCullMode()																{	return ApplyCullMode(CULL_NONE);}
	static	HRESULT				ResetCullMode()																	{	return ApplyCullMode(CULL_CCW);}

	// 4) Alpha Blend
	static	HRESULT				EnableAlphaBlend(BOOL _bEnable=TRUE)											{	return m_lpDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, _bEnable);}
	static	HRESULT				DisableAlphaBlend()																{	return EnableAlphaBlend(FALSE);}

	// 5) Scissor Rect
	static	HRESULT				SetScissorRect(LPRECT p_pRect)													{	return m_lpDirect3DDevice->SetScissorRect(p_pRect);}
	static	HRESULT				GetScissorRect(LPRECT p_pRect)													{	return m_lpDirect3DDevice->GetScissorRect(p_pRect);}


	// ----------------------------------------------------------------------------
	// 4. Texture 관련
	// ----------------------------------------------------------------------------
	// 1) Texture Set
	//static	HRESULT				SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture)						{	return m_lpDirect3DDevice->SetTexture(Stage, pTexture);}
	static	HRESULT				GetTexture(DWORD Stage,IDirect3DBaseTexture9** ppTexture)						{	return m_lpDirect3DDevice->GetTexture(Stage, ppTexture);}
	static	HRESULT				ResetTexture(int p_Stage)														{	return m_lpDirect3DDevice->SetTexture(p_Stage, nullptr);}
	static	void				ResetTextureAll();

	// 2) Texture Stage
	static	HRESULT				SetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type, DWORD Value)	{	return m_lpDirect3DDevice->SetTextureStageState(Stage, Type, Value);}
	static	HRESULT				GetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)	{	return m_lpDirect3DDevice->GetTextureStageState(Stage, Type, pValue);}

	// 3) Sampler State
	static	HRESULT				SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type, DWORD Value)			{	return m_lpDirect3DDevice->SetSamplerState(Sampler, Type, Value);}
	static	HRESULT				GetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type, DWORD* pValue)			{	return m_lpDirect3DDevice->GetSamplerState(Sampler, Type, pValue);}


	// ----------------------------------------------------------------------------
	// 5. Shader관련
	// ----------------------------------------------------------------------------
	// 1) Vertex Shader.
	static	HRESULT				SetVertexShader(LPDIRECT3DVERTEXSHADER9 pShader=NULL)							{	return m_lpDirect3DDevice->SetVertexShader(pShader);}
	static	HRESULT				ResetVertexShader()																{	return SetVertexShader(nullptr);}
	static	HRESULT				GetVertexShader(LPDIRECT3DVERTEXSHADER9* ppShader)								{	return m_lpDirect3DDevice->GetVertexShader(ppShader);}

	// 2) Pixel Shader.
	static	HRESULT				SetPixelShader(LPDIRECT3DPIXELSHADER9 pShader=NULL)								{	return m_lpDirect3DDevice->SetPixelShader(pShader);}
	static	HRESULT				ResetPixelShader()																{	return SetPixelShader(nullptr);}
	static	HRESULT				GetPixelShader(LPDIRECT3DPIXELSHADER9* ppShader)								{	return m_lpDirect3DDevice->GetPixelShader(ppShader);}

	// 3) Vertex Shader Constant.
	static	HRESULT				SetVertexShaderConstantF(UINT p_iIndex, const FLOAT* p_pConst, UINT p_iCount)	{	return m_lpDirect3DDevice->SetVertexShaderConstantF(p_iIndex, p_pConst, p_iCount);}
	static	HRESULT				SetVertexShaderConstantI(UINT p_iIndex, const INT* p_pConst, UINT p_iCount)		{	return m_lpDirect3DDevice->SetVertexShaderConstantI(p_iIndex, p_pConst, p_iCount);}
	static	HRESULT				SetVertexShaderConstantB(UINT p_iIndex, const BOOL* p_pConst, UINT p_iCount)	{	return m_lpDirect3DDevice->SetVertexShaderConstantB(p_iIndex, p_pConst, p_iCount);}

	// 4) Pixel Shader Constant.
	static	HRESULT				SetPixelShaderConstantF(UINT p_iIndex, const FLOAT* p_pConst, UINT p_iCount)	{	return m_lpDirect3DDevice->SetPixelShaderConstantF(p_iIndex, p_pConst, p_iCount);}
	static	HRESULT				SetPixelShaderConstantI(UINT p_iIndex, const INT* p_pConst, UINT p_iCount)		{	return m_lpDirect3DDevice->SetPixelShaderConstantI(p_iIndex, p_pConst, p_iCount);}
	static	HRESULT				SetPixelShaderConstantB(UINT p_iIndex, const BOOL* p_pConst, UINT p_iCount)		{	return m_lpDirect3DDevice->SetPixelShaderConstantB(p_iIndex, p_pConst, p_iCount);}


	// ----------------------------------------------------------------------------
	// 6. VertexDeclaration
	// ----------------------------------------------------------------------------
	// 1) VFV & VE
	static	void				FVFtoVertexElements(DWORD p_dwFVF, LPD3DVERTEXELEMENT9 pElement, int* p_iNumElement=nullptr, int* p_VertexSize=nullptr);
	static	DWORD				VertexElementsToFVF(LPD3DVERTEXELEMENT9 pElement);

	// 2) FVF
	static	HRESULT				SetFVF(DWORD p_FVF)																{	return m_lpDirect3DDevice->SetFVF(p_FVF);}
			HRESULT				SetVertexDeclaration(D3DVERTEXDECL* p_pD3DVertextDecl) const					{	return m_lpDirect3DDevice->SetVertexDeclaration(p_pD3DVertextDecl);}


	// ----------------------------------------------------------------------------
	// 7. Usable
	// ----------------------------------------------------------------------------
	static	void				ApplyTexture(CG3DApplier::CTexture* p_pTexture);
	static	void				ApplyMaterial(CG3DApplier::CMaterial* p_pMaterial);

	static	HRESULT				SetTexture(int p_pStage, LPD3DBASETEXTURE p_pTexture);
	static	HRESULT				SetTexture(int p_pStage, CGResource::ITexture* p_pTexture);

	static	void				ApplyWireColor(const COLOR4& p_Color);
	static	void				ApplyWireColor(float p_Red, float p_Green, float p_Blue, float p_Alpha=1.0f);

	static	void				ApplyDefaultTexture();
	static	void				ApplyDefaultMaterial();

	static	void				DrawRect(const RECT2D& p_rRect, COLOR p_Color=0xffffffff);
	static	void				DrawRectangle(const RECT2D& p_rRect, COLOR p_Color=0xffffffff);

	static	void				_Clear(int p_iRectCount, const RECT2D* p_pRect, DWORD p_dwClearOption=D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, COLOR p_colorClear=0xff000000, float p_Z=1.0f, DWORD p_B=0L);

	static	void				ResetRenderTarget(int p_iStage);
	static	HRESULT				GetRenderTargetSurfaceDesc(D3DSURFACE_DESC& p_rDesc);


	// ---------------------------------------------
	// 8. Apply
	// ---------------------------------------------
	static	HRESULT				ApplyViewport(const CViewport& p_rViewport)										{	return m_lpDirect3DDevice->SetViewport((const USE_D3DVIEWPORT*)&p_rViewport);}

	static	void				ResetTransformMatrix();
	static	void				ApplyTransformMatrix(const MATRIX* p_tmSource);
	static	void				ApplyTransformMatrix(const MATRIX& _tm);
	static	void				ApplyTransformMatrixAsWorldView(const CG3DApplier::CCamera* p_pCamera, const MATRIX& p_tmSource);
	static	void				ApplyTransformMatrixAsBillboard(const VECTOR3& p_pv3Position, const MATRIX& p_tmView);
	static	void				ApplyTransformMatrixAsViewBillboard(const VECTOR3& p_pv3Position, const CG3DApplier::CCamera* p_pCamera);
	static	void				ApplyTransformMatrixAsViewBillboard(const VECTOR3& p_pv3Position, const VECTOR3& p_pEyePosition, const MATRIX& p_ptmView);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) D3D & D3DDevice에 대한 정보
	static	LPDIRECT3D			m_lpDirect3D;			// D3D 
	static	LPDIRECT3DDEVICE	m_lpDirect3DDevice;		// D3DDevice

	// 2) Display Mode Info & Present에 대한 정보
	static	D3DPRESENT_PARAMETERS m_D3DPresentParameters;	// Present에 대한 정보들

	// 3) Identity
	static	CG3D::MATRIX		m_tmIdentity;

	// 4) Default Font
	static	CGPTR<CGResource::CFont>	m_pDefaultFont;

};


}

	//static	D3DDISPLAYMODE		m_DisplayModeInfo;		// Displaay Mode에 관련된 정보
//class ICGDeviceObject
//{
//public:
//			CGPTR<ICGDeviceGraphic>	m_pDeviceGraphic;
//
//public:
//			CGPTR<ICGDeviceGraphic>&		GetDeviceGraphic()			{	return m_pDeviceGraphic;}
//			const CGPTR<ICGDeviceGraphic>&	GetDeviceGraphic() const	{	return m_pDeviceGraphic;}
//			bool				IsDeviceExist() const					{	return m_pDeviceGraphic.exist();}
//};


			//void				ProcessPresent(HWND p_hPresentTarget);

	//static	HANDLE				m_eventPreset;
	//static	DWORD WINAPI		fnThreadPreset(LPVOID _Param);

			//BOOL				Init(HWND p_hWnd, BOOL p_bIsWondowed, int p_Width=0, int p_Height=0, D3DFORMAT p_formatMode=D3DFMT_X8R8G8B8, ADAPTOR p_eAdaptor=ADAPTOR_MASTER);
