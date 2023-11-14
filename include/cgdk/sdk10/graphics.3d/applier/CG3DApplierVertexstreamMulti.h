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
// 1. CG3DApplier::CVertexStreamMulti��!
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
namespace CG3DApplier
{

class CVertexStreamMulti :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DApplier						// (I) Applier
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CVertexStreamMulti();
	virtual ~CVertexStreamMulti();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	virtual void				Apply();

			void				ClearApplierVertexStreamMulti();


			void				AddVertexbuffer(int p_Stream, VERTEXBUFFER* p_pVertexbuffer){	m_iStream[m_nVertexbuffer]=p_Stream; m_pVertexbuffer[m_nVertexbuffer]=p_pVertexbuffer;m_nVertexbuffer++;}

			void				SetVertexStreamNumber(int p_Index, int p_StreamNumber)		{	m_iStream[p_Index]=p_StreamNumber;}
			void				SetVertexbuffer(int p_Index, VERTEXBUFFER* p_pVertexbuffer)	{	m_pVertexbuffer[p_Index]=p_pVertexbuffer;}
			void				SetVertexbuffer(int p_Index, VERTEXBUFFER* p_pVertexbuffer, int p_StreamNumber)	{	SetVertexbuffer(p_Index, p_pVertexbuffer); SetVertexStreamNumber(p_Index, p_StreamNumber);}

			int					GetVertexStreamNumber(int p_Index) const{	return m_iStream[p_Index];}
			CGPTR<VERTEXBUFFER>	GetVertexbuffer(int p_Index) const		{	return m_pVertexbuffer[p_Index];}

			int					GetVertexbufferCount() const			{	return m_nVertexbuffer;}

			void				SetVertexDeclaration(VERTEXDECL* p_pVertexDeclaration)	{	m_pVertexdeclaration=p_pVertexDeclaration;}
			CGPTR<VERTEXDECL>	GetVertexDeclaration()					{	return m_pVertexdeclaration;}

			DWORD				GetVertexStride() const					{	return m_dwVertexStride;}
			DWORD				GetOffset() const						{	return m_dwOffset;}


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
			// 1) Vertex Declation
			CGPTR<VERTEXDECL>	m_pVertexdeclaration;	// Vertex Declaration

			// 2) Number Of Vertex
			int					m_nVertexbuffer;		// Vertexbuffer�� ��
			int					m_iStream[8];			// Vertex�� Stream
			CGPTR<VERTEXBUFFER>	m_pVertexbuffer[8];		// Vertexbuffer

			DWORD				m_dwVertexStride;
			DWORD				m_dwOffset;
};


}