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
// CGResource::Mesh::CPrimitive
//
// 1. CGResource::Texture::CCube��...
//    1) ����...
//    2) Linked List����� Ȥ�� Array�� ������ ü������ �ʴ´�! ������ Modify��
//
//
// 2. CGResource::Texture::CCube�� ��� ����
//    1) ()	�ܺο��� Render�� �䱸�� �� ȣ���ϴ� �Լ��̴�.
//								���������� ()�Լ��� ȣ���ϵ��� �Ǿ� �ִ�.
//    2) ()	Rendering�� ������ �����ϴ� �Լ��̴�.
//								�� class�� ��ӹ޾� �� �Լ��� �������ϴ� ���� �ٽ��̴�.
//	  3) Renderable Status �Լ���
//		 - Renderable�� Enable/Disble�ϴ� �Լ��̴�. �� �� ���¸� ���� �� �ִ�
//         �Լ����̴�.
//
//
//-----------------------------------------------------------------------------
namespace CGResource
{
namespace Mesh
{

class CPrimitive : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGResource::IMesh,						// (I) Mesh Base
	public						ICGDeviceGraphic						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CPrimitive();
			CPrimitive(const CPrimitive& p_rMesh);
	virtual	~CPrimitive();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Create & Init
			void				CreateTriangle(float p_fSize=1.0f);
			void				CreateRect(float p_fSize=1.0f);
			void				CreateRect(float p_fLeft, float p_fTop, float p_fRight, float p_fBottom);
			void				Duplicate(const CPrimitive& p_rMesh);
	virtual	void				Destroy();

	// 2) Draw Function
	virtual	BOOL				Draw(CGMSG& _Msg);

	// 3) Operation
	virtual	BOOL				Transform(const MATRIX& _tm);
	virtual	BOOL				CalculateBoundingSphere(SPHERE& p_rBoundingSphere);
	virtual	BOOL				CalculateBoundingBox(AABB& p_rAABB);
	virtual	BOOL				CalculateBoundingBox(OBB& p_rOBB);
	virtual void				ReadyForShadowVolume();

	// 4) Vertex Declaration
			void				SetVertexDeclaration(VERTEXDECL* p_pVertexdeclaration)	{	m_VertexDeclaration=p_pVertexdeclaration;}
			CGPTR<VERTEXDECL>	GetVertexDeclaration() const			{	return m_VertexDeclaration;}

	// 5) Vertex Buffer
			void				SetVertexbuffer(VERTEXBUFFER* p_rVertexbuffer)	{	m_Vertexbuffer=p_rVertexbuffer;}
			CGPTR<VERTEXBUFFER>	GetVertexbuffer() const					{	return m_Vertexbuffer;}

	// 6) Cull Mode����
			CULL				GetCullMode() const						{	return m_PrimitiveInfo.eCullMode;}
			void				SetCullMode(CULL p_eCullMode)			{	m_PrimitiveInfo.eCullMode=p_eCullMode;}

	// 7) Primitive Info
			DWORD				GetStartIndex() const					{	return m_PrimitiveInfo.dwStartIndex;}
			DWORD				GetPrimitiveCount() const				{	return m_PrimitiveInfo.dwPrimitiveCount;}

	// 8) Operator 
			CPrimitive&			operator=(const CPrimitive& p_rMesh)	{	Duplicate(p_rMesh); return *this;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override	{	return 0;}

public:
	// 1) Vertex Declaration
			CGPTR<VERTEXDECL>	m_VertexDeclaration;

	// 2) Vertex Buffer & Basic Primitive Data
			CGPTR<VERTEXBUFFER>	m_Vertexbuffer;

	// 3) Primitive Info
			struct FILE
			{
				// - Resource Info.
				int					idxVertexDecl;
				int					idxVertexbuffer;

				// - Primitive Info.
				D3DPRIMITIVETYPE	ePrimitiveType;
				DWORD				dwStartIndex;
				DWORD				dwPrimitiveCount;

				// - Cull Mode
				CULL				eCullMode;
			} m_PrimitiveInfo;
};


}
}