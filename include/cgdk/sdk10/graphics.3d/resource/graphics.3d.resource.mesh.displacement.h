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
// CGResource::Mesh::CDisplacement
//
// 1. CGResource::Texture::CCube는...
//    1) 이음...
//    2) Linked List라든지 혹은 Array의 구조는 체택하지 않는다! 이유는 Modify와
//
//
// 2. CGResource::Texture::CCube의 기능 설명
//    1) ()	외부에서 Render를 요구할 때 호출하는 함수이다.
//								내주적으로 ()함수를 호출하도록 되어 있다.
//    2) ()	Rendering의 절차를 정의하는 함수이다.
//								이 class를 상속받아 이 함수를 재정의하는 것이 핵심이다.
//	  3) Renderable Status 함수들
//		 - Renderable을 Enable/Disble하는 함수이다. 또 그 상태를 얻을 수 있는
//         함수들이다.
//
//
//-----------------------------------------------------------------------------
namespace CGResource
{
namespace Mesh
{

class CDisplacement : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CGResource::IMesh,						// (I) Resource Base
	protected					ICGDeviceGraphic					// (@) Static Device
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CDisplacement();
	virtual ~CDisplacement();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Destroy
	virtual	void				Destroy();

	// 2) Draw Function
	virtual	BOOL				Draw(CGMSG& _Msg);

	// 3) Vertex Declaration
			void				SetVertexDeclaration(VERTEXDECL* p_pVertexdeclaration)	{	m_pVertexDeclaration=p_pVertexdeclaration;}
			CGPTR<VERTEXDECL>	GetVertexDeclaration() const			{	return m_pVertexDeclaration;}

	// 4) Vertex & Index Buffer
			void				SetVertexbuffer(int p_iIndex, VERTEXBUFFER* p_pVertexbuffer)	{	m_pVertexbuffer[p_iIndex]=p_pVertexbuffer;}
			CGPTR<VERTEXBUFFER>	GetVertexBuffer(int p_iIndex) const		{	return m_pVertexbuffer[p_iIndex];}

			void				SetIndexbuffer(INDEXBUFFER* p_Indexbuffer){	m_pIndexbuffer=p_Indexbuffer;}
			CGPTR<INDEXBUFFER>	GetIndexBuffer() const					{	return m_pIndexbuffer;}
			
	// 5) Other Parameter
			DWORD				GetBaseVertexIndex() const				{	return m_BaseVertexIndex;}
			DWORD				GetStartIndex() const					{	return m_dwStartIndex;}
			DWORD				GetPrimitiveCount() const				{	return m_dwPrimitiveCount;}

	// 6) Cull Mode관련
			void				SetCullMode(CULL p_CullMode)			{	m_CullMode=p_CullMode;}
			CULL				GetCullMode() const						{	return m_CullMode;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override	{	return 0;}

private:
			// 1) Vertex Declaration
			CGPTR<VERTEXDECL>	m_pVertexDeclaration;

			// 2) Vertex Buffer & Index Buffer
			CGPTR<VERTEXBUFFER>	m_pVertexbuffer[2];
			int					m_idxVertexbuffer[2];

			CGPTR<INDEXBUFFER>	m_pIndexbuffer;
			int					m_idxIndexbuffer;
			
			// 3) Cull Mode
			CULL				m_CullMode;

			// 4) Primitive Parameters
			D3DPRIMITIVETYPE	m_ePrimitiveType;
			DWORD				m_dwStartIndex;
			DWORD				m_dwPrimitiveCount;

			DWORD				m_BaseVertexIndex;

			DWORD				m_MinIndex;
			DWORD				m_NumVertices;
};


}
}