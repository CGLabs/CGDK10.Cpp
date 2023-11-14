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
// CG3DRenderer::CWire
//
// 1. CG3DRenderer::CWire��...
//    1) �������� Render�� Loop���� Render�� ���ÿ� �����ϴ� ����� ���ߴ�.
//    2) Render�� �ʿ��� ���� ������ ���������� ��� ������ �ְ� �Ѵ�. Render��
//       �� ������ �����ؼ� ��������� �ߺ� ���� �� �ٽ� �������� �ʾƵ� �ǰ�
//       ������ �Ѵ�.
//    3) Linked List����� Ȥ�� Array�� ������ ü������ �ʴ´�! ������ Modify��
//       Ʋ���� Arrange���� �ʿ��ϸ� ������ ������ ������ �� �ǹ̰� ���� ������
//       ��. 2D�� ��쳪 Ȥ�� Sprite���� ���� ������ �ʿ��ϳ� �̷� ���� ��
//       �� ������� ������ �ϸ� Default�� �����ϴ� ������ ���� �ʴ´�.
//       ������ �پ��� ����� ������ ������ �� �ֱ� �����̴�. ���� ��� Arrange
//       �� Z Ordering�� �ؾ��ϴ� ��� Y Ordering�� �ؾ��ϴ� ��쳪 �ʿ� ����
//       ��� �� ���� Ʋ�� �ʿ信 ���� �ٸ� ������ ü���ؾ� �ϱ� �����̴�.
//
//
// 2. CGNetRoot�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
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
	// 1) Virtual�Լ�.
	virtual void				ClearRendererWire();

	// 2) Virtual�Լ�.
	virtual uint32_t			Render(CGMSG_RENDER& _Msg);

	// 3) Transform Matrix
			void				SetWorldTransformMatrix(CMatrix* p_ptm)	{	m_ptmWorld=p_ptm;}
			CGPTR<CMatrix>		GetWorldTransformMatrix()				{	return m_ptmWorld;}

	// 4) Mesh ���� �Լ�.
			// - Point List��.
			void				CreatePoint(int p_iNumberOfPoints);
			void				CreatePointSkinned(int p_iNumberOfPoints);
			void				CreatePointColor(int p_iNumberOfPoints);
			void				CreatePointSkinnedColor(int p_iNumberOfPoints);

			// - Line List��.
			void				CreateWire(int p_iNumberOfLine);
			void				CreateWireSkinned(int p_iNumberOfLine);
			void				CreateWireColor(int p_iNumberOfLine);
			void				CreateWireSkinnedColor(int p_iNumberOfLine);

			// - Sphere�� �����.
			void				CreateWireAsXYCircle(const SPHERE& p_rSphere);
			void				CreateWireAsXYCircle(float p_fRadius);
			void				CreateWireAsTriCircle(const SPHERE& p_rSphere);

			// - Box�� �����.
			void				CreateWireAsBox(const AABB& p_pboxVertex);
			void				CreateWireAsBox(const OBB& p_pBox);
			void				CreateWireAsBox(const VECTOR3& p_v3Min, const VECTOR3& p_v3Max);
			void				CreateWireAsBox(const VECTOR3* p_pv3Vertex=nullptr);
			void				CreateWireAsBox(const VECTOR4* p_pv4Vertex);
			void				CreateWireAsViewFrustum(const MATRIX* p_ptmViewProjection);
			void				CreateWireAsViewUnitCube();

			// - Rect�� �����.
			void				CreateWireAsRect(float p_fWidth, float p_fHeight);

			// - ��Ÿ �����.
			void				CreateWireAsGrid(float p_CellWidth, float p_CellHeight, int p_Width, int p_Height, COLOR p_colorGrid, COLOR p_colorAxis);
			void				CreateWireAsTriAxis(float p_fSize=1.0f, COLOR p_colorAxisX=CG3D_RGBA(255,0,0,255), COLOR p_colorAxisY=CG3D_RGBA(0,255,0,255), COLOR p_colorAxisZ=CG3D_RGBA(0,0,255,255));
			void				CreateWireAsTriAxis(const CG3D::MATRIX& p_rtmTransform, float p_fSize=1.0f, COLOR p_colorAxisX=CG3D_RGBA(255,0,0,255), COLOR p_colorAxisY=CG3D_RGBA(0,255,0,255), COLOR p_colorAxisZ=CG3D_RGBA(0,0,255,255));

			void				Destroy() throw();


	// 6) Mesh ���� �����ϱ�.
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
