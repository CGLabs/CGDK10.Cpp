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
// CG3DRenderer::CWire
//
// 1. CG3DRenderer::CWire는...
//    1) 독립적인 Render와 Loop상의 Render를 동시에 지원하는 방법을 택했다.
//    2) Render에 필요한 각종 정보를 독립적으로 모두 가지고 있게 한다. Render시
//       그 값들을 설정해서 사용하지만 중복 설정 시 다시 설정하지 않아도 되게
//       설정을 한다.
//    3) Linked List라든지 혹은 Array의 구조는 체택하지 않는다! 이유는 Modify와
//       틀리게 Arrange등이 필요하며 찍히는 순서는 오히려 별 의미가 없기 때문이
//       다. 2D의 경우나 혹은 Sprite같은 경우는 순서가 필요하나 이런 경우는 다
//       른 방법으로 구현을 하며 Default로 지원하는 구조는 넣지 않는다.
//       이유는 다양한 방법의 구조가 존재할 수 있기 때문이다. 예를 들면 Arrange
//       도 Z Ordering을 해야하는 경우 Y Ordering을 해야하는 경우나 필요 없는
//       경우 등 각기 틀린 필요에 따라 다른 구조를 체택해야 하기 때문이다.
//
//
// 2. CGNetRoot의 핵심! Function의 기능 설명
//    1) Render      Render를 시행하는 핵심 구조이다.  
//    2) 음...
//
// 3. 주의 사항
//    음... -_-;;
//
//-----------------------------------------------------------------------------
namespace CG3DRenderer
{

class CWire :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DRenderer,
	virtual public				ICG3DWorldTransform, 
	public						ICGDeviceGraphic				// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CWire();
			CWire(CMatrix* p_pTransformMatrix);
			CWire(const AABB& p_pAABB);
			CWire(const OBB& p_pOBB);
			CWire(const VECTOR3& p_v3Min, const VECTOR3& p_v3Max);
			CWire(const VECTOR3* p_pv3Vertex);
			CWire(const VECTOR4* p_pv4Vertex);
	virtual	~CWire();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Virtual함수.
	virtual void				ClearRendererWire();

	// 2) Virtual함수.
	virtual uint32_t			Render(CGMSG_RENDER& _Msg);

	// 3) Transform Matrix
			void				SetWorldTransformMatrix(CMatrix* p_ptm)	{	m_ptmWorld=p_ptm;}
			CGPTR<CMatrix>		GetWorldTransformMatrix()				{	return m_ptmWorld;}

	// 4) Mesh 생성 함수.
			// - Point List로.
			void				CreatePoint(int p_iNumberOfPoints);
			void				CreatePointSkinned(int p_iNumberOfPoints);
			void				CreatePointColor(int p_iNumberOfPoints);
			void				CreatePointSkinnedColor(int p_iNumberOfPoints);

			// - Line List로.
			void				CreateWire(int p_iNumberOfLine);
			void				CreateWireSkinned(int p_iNumberOfLine);
			void				CreateWireColor(int p_iNumberOfLine);
			void				CreateWireSkinnedColor(int p_iNumberOfLine);

			// - Sphere로 만들기.
			void				CreateWireAsXYCircle(const SPHERE& p_rSphere);
			void				CreateWireAsXYCircle(float p_fRadius);
			void				CreateWireAsTriCircle(const SPHERE& p_rSphere);

			// - Box로 만들기.
			void				CreateWireAsBox(const AABB& p_pboxVertex);
			void				CreateWireAsBox(const OBB& p_pBox);
			void				CreateWireAsBox(const VECTOR3& p_v3Min, const VECTOR3& p_v3Max);
			void				CreateWireAsBox(const VECTOR3* p_pv3Vertex=nullptr);
			void				CreateWireAsBox(const VECTOR4* p_pv4Vertex);
			void				CreateWireAsViewFrustum(const MATRIX* p_ptmViewProjection);
			void				CreateWireAsViewUnitCube();

			// - Rect로 만들기.
			void				CreateWireAsRect(float p_fWidth, float p_fHeight);

			// - 기타 만들기.
			void				CreateWireAsGrid(float p_CellWidth, float p_CellHeight, int p_Width, int p_Height, COLOR p_colorGrid, COLOR p_colorAxis);
			void				CreateWireAsTriAxis(float p_fSize=1.0f, COLOR p_colorAxisX=CG3D_RGBA(255,0,0,255), COLOR p_colorAxisY=CG3D_RGBA(0,255,0,255), COLOR p_colorAxisZ=CG3D_RGBA(0,0,255,255));
			void				CreateWireAsTriAxis(const CG3D::MATRIX& p_rtmTransform, float p_fSize=1.0f, COLOR p_colorAxisX=CG3D_RGBA(255,0,0,255), COLOR p_colorAxisY=CG3D_RGBA(0,255,0,255), COLOR p_colorAxisZ=CG3D_RGBA(0,0,255,255));

			void				Destroy() throw();


	// 6) Mesh 정보 설정하기.
			BOOL				SetWireAsXYCircle(const SPHERE& p_rSphere);
			BOOL				SetWireAsTriCircle(const SPHERE& p_rSphere);

			BOOL				SetWireAsBox(const AABB& p_rboxVertex);
			BOOL				SetWireAsBox(const OBB& p_rboxVertex);
			BOOL				SetWireAsBox(const VECTOR3& p_v3Min, const VECTOR3& p_v3Max);
			BOOL				SetWireAsBox(const VECTOR3* p_pv3Vertex=nullptr);
			BOOL				SetWireAsBox(const VECTOR4* p_pv4Vertex);
			void				SetWireAsViewFrustum(const MATRIX& p_rtmViewProjection);
			void				SetWireAsViewUnitCube();

			BOOL				SetWireAsRect(const VECTOR3* p_pv3Vertex=nullptr);
			BOOL				SetWireAsRect(const VECTOR4* p_pv4Vertex);

			void				SetWireAsTriAxis(float p_fSize=1.0f, COLOR p_colorAxisX=CG3D_RGBA(255,0,0,255), COLOR p_colorAxisY=CG3D_RGBA(0,255,0,255), COLOR p_colorAxisZ=CG3D_RGBA(0,0,255,255));
			void				SetWireAsTriAxis(const CG3D::MATRIX& p_rtmTransform, float p_fSize=1.0f, COLOR p_colorAxisX=CG3D_RGBA(255,0,0,255), COLOR p_colorAxisY=CG3D_RGBA(0,255,0,255), COLOR p_colorAxisZ=CG3D_RGBA(0,0,255,255));

	// 7) Vertex Shader
			void				SetVertexshader(VERTEXSHADER* p_pVertexshader)		{	m_pVertexshader=p_pVertexshader;}
			CGPTR<VERTEXSHADER>	GetVertexshader() const								{	return m_pVertexshader;}

	// 8) Pixel Shader
			void				SetPixelshader(PIXELSHADER* p_pPixelshader)			{	m_pPixelshader=p_pPixelshader;}
			CGPTR<PIXELSHADER>	GetPixelshader() const								{	return m_pPixelshader;}

	// 9) Vertex Buffer
			void				SetVertexbuffer(VERTEXBUFFER* p_pVertexbuffer)		{	m_pVertexbuffer=p_pVertexbuffer;}
			CGPTR<VERTEXBUFFER>	GetVertexbuffer() const								{	return m_pVertexbuffer;}

	// 10) Vertex Declaration
			void				SetVertexDeclaration(VERTEXDECL* p_pVertexdeclaration)	{	m_pVertexDeclaration=p_pVertexdeclaration;}
			CGPTR<VERTEXDECL>	GetVertexDeclaration() const						{	return m_pVertexDeclaration;}

	// 11) Line Color
			void				SetWireColor(const COLOR4 p_colorLine)				{	m_colorWire=p_colorLine;}
			void				SetWireColor(float p_fRed, float p_fGreen, float p_fBlue, float p_fAlpha=1.0f)	{	m_colorWire.r=p_fRed;m_colorWire.g=p_fGreen;m_colorWire.b=p_fBlue;m_colorWire.a=p_fAlpha;}
			COLOR4				GetWireColor()										{	return m_colorWire;}

	// 12) Primitive Info
			void				SetPrimitiveInfo(D3DPRIMITIVETYPE p_ePrimitiveType, DWORD p_dwStartIndex, DWORD p_dwPrimitiveCount);

			void				SetPrimitiveCount(DWORD p_dwPrimitiveCount)			{	m_dwPrimitiveCount=p_dwPrimitiveCount;}
			DWORD				GetPrimitiveCount() const							{	return m_dwPrimitiveCount;}
			void				AddPrimitiveCount(int p_iDiffer)					{	m_dwPrimitiveCount+=p_iDiffer;}

			void				SetStartIndex(DWORD p_dwStartIndex)					{	m_dwStartIndex=p_dwStartIndex;}
			DWORD				GetStartIndex() const								{	return m_dwStartIndex;}
			void				AddStartIndex(int p_iDiffer)						{	m_dwStartIndex+=p_iDiffer;}

			void				SetPrimitiveType(D3DPRIMITIVETYPE p_ePrimitiveType)	{	m_ePrimitiveType=p_ePrimitiveType;}
			D3DPRIMITIVETYPE	GetPrimitiveType() const							{	return m_ePrimitiveType;}


// ****************************************************************************
// Message)
// ----------------------------------------------------------------------------
public:
	// Declare) 
	DECLARE_CGMESSAGE_MAP

	// 1) Functions
	virtual	int					OnFunction_SetWorldTransformMatrix	(CGMSG_SET<CMatrix>& _Msg);
	virtual	int					OnFunction_GetWorldTransformMatrix	(CGMSG_GET<CMatrix>& _Msg);

	// 2) Notifications for Automation
	virtual	int					OnNotify_OnAttach					(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	int					OnNotify_OnDetach					(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& _Msg) override;
	
	// 2) ProcessRender
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& _MSGRender) override;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Transform Matrix
			CGPTR<CMatrix>		m_ptmWorld;

	// 2) Vertex & Pixel Shader
			CGPTR<VERTEXSHADER>	m_pVertexshader;
			CGPTR<PIXELSHADER>	m_pPixelshader;

	// 3) Vertex Declaration
			CGPTR<VERTEXDECL>	m_pVertexDeclaration;

	// 4) Vertex Buffer
			CGPTR<VERTEXBUFFER>	m_pVertexbuffer;

	// 5) Line color
			COLOR4				m_colorWire;

public:
	// 6) Primitive Info
			D3DPRIMITIVETYPE	m_ePrimitiveType;
			DWORD				m_dwStartIndex;
			DWORD				m_dwPrimitiveCount;
};

}

void SetVertexAsWireXYCircle(LPVOID _pBuffer, int p_iStride, const SPHERE& p_pSphere);
void SetVertexAsWireBox(LPVOID _pBuffer, int p_iStride, const OBB& p_boxOBB);
void SetVertexAsWireBox(LPVOID _pBuffer, int p_iStride, const AABB& p_boxOBB);
void SetVertexAsWireBox(LPVOID _pBuffer, int p_iStride, const VECTOR3& p_v3Min, const VECTOR3& p_v3Max);
