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
// CG3DApplier::CVertexStream
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
namespace CG3DApplier
{

class CVertexStream :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DApplier,							// (I) Applier
	public						CGResource::Buffer::CVertex
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CVertexStream();
			CVertexStream(VERTEXBUFFER* p_pVertexbuffer, UINT p_StreamNumber);
			CVertexStream(DWORD p_dwSizeOfVertexBuffer, UINT p_dwVertexStride=0, DWORD p_dwUsage=D3DUSAGE_WRITEONLY, D3DPOOL p_Pool=D3DPOOL_MANAGED, UINT p_StreamNumber=0);
	virtual ~CVertexStream();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	virtual void				Apply();

			void				ClearApplierVertexStream();

			void				SetVertexDeclaration(DWORD p_dwFVF);
			void				SetVertexDeclaration(VERTEXDECL* p_pVertexDeclaration)	{	m_pVertexdeclaration=p_pVertexDeclaration;}
			CGPTR<VERTEXDECL>	GetVertexDeclaration() const			{	return m_pVertexdeclaration;}

			void				SetVertexbuffer(VERTEXBUFFER* p_pVertexbuffer)	{	*(VERTEXBUFFER*)this=*p_pVertexbuffer;}
			void				SetVertexbuffer(VERTEXBUFFER* p_pVertexbuffer, UINT p_StreamNumber)	{	SetVertexbuffer(p_pVertexbuffer); SetVertexStreamNumber(p_StreamNumber);}

			void				SetVertexStreamNumber(UINT p_StreamNumber)	{	m_iStream=p_StreamNumber;}
			int					GetVertexStreamNumber() const			{	return m_iStream;}

			void				SetVertexStride(UINT p_dwVertexStride)	{	m_dwVertexStride=p_dwVertexStride;}
			DWORD				GetVertexStride() const					{	return m_dwVertexStride;}
			DWORD				GetOffset() const						{	return m_dwOffset;}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) Process Message
	virtual	int					ProcessMessage(CGMSG& _Msg) override	{	return CGResource::Buffer::CVertex::ProcessMessage(_Msg);}

	// 2) Process Render
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& /*_MSGRender*/) override	{ return 0; }


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Vertex Declation
			CGPTR<VERTEXDECL>	m_pVertexdeclaration;	// Vertex Declaration
			UINT				m_iStream;

	// 2) Vertexbuffer Info
			UINT				m_dwVertexStride;
			UINT				m_dwOffset;
};


}