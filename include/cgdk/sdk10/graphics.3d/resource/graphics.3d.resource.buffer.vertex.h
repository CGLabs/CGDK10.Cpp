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
// CGResource::Buffer::CVretex
//
// 1. CGResource::Buffer::CVretex��...
//    1) Vertex Buffer�� Delcation�� Class�̴�.
//    2) �� Class�� �Ϲ������� new�� �ؼ� ���������� �ʴ´�.
//	  3) ������ Create()�Լ��� ���� LPD3DTEXTURE�� ���������ν� ó���� �Ǹ�
//    4) ���������� shared����� �����Ƿ� �ַ� �̸� ���� ����Ѵ�.
//
// 2. CGResource::Buffer::CVretex�� ��� ����
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
namespace Buffer
{

class CVertex :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGResource::IBuffer,					// (I) Buffer Base 
	public						ICGDeviceGraphic						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CVertex();
			CVertex(const CVertex& p_rCopy);
			CVertex(DWORD p_dwSize, DWORD p_dwStride, DWORD p_dwUsage=D3DUSAGE_WRITEONLY, D3DPOOL p_Pool=D3DPOOL_MANAGED, DWORD p_FVF=0);
	virtual	~CVertex();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Create & Destroy
			void				Create(DWORD p_dwSize, DWORD p_dwStride=0, DWORD p_dwUsage=D3DUSAGE_WRITEONLY, D3DPOOL p_Pool=D3DPOOL_MANAGED, DWORD p_FVF=0);
			void				Create(const CVertex& p_pSourceVertexBuffer, DWORD p_dwUsage=D3DUSAGE_WRITEONLY, D3DPOOL p_Pool=D3DPOOL_MANAGED, DWORD p_FVF=0);
			void				Duplicate(const CVertex& p_rCopy);
	virtual	void				Destroy();

	// 2) push_back
			void				AppendVertexbuffer(const CVertex& p_rbufferAppend);
			void				WriteBuffer(const void* _pBuffer, DWORD p_dwSize, DWORD p_dwPosition=0);

	// 3) Lock & UnLock
			void*				Lock(DWORD p_dwFlags=0, DWORD p_dwOffsetToLock=0, DWORD p_dwSizeToLock=0) const;
			void				Unlock() const;

	// 4) Apply
			void				ApplyStream(int p_iStream, DWORD p_dwVertexStride, DWORD p_dwOffset=0) const;
			void				ApplyStream(int p_iStream=0) const		{	ApplyStream(p_iStream, m_dwVertexStride, 0);}

	// 5) Buffer Attribute
			bool				IsCreated() const						{	return m_pD3DVertexBuffer.exist();}
			bool				IsDestroyed() const						{	return !IsCreated();}

			void				SetVertexStride(DWORD p_dwStride)		{	m_dwVertexStride=p_dwStride;}
			DWORD				GetVertexStride() const					{	return m_dwVertexStride;}

			void				GetDesc(D3DVERTEXBUFFER_DESC* p_pDesc) const;
			CGPTR<D3DVERTEXBUFFER> GetD3DVertexbuffer() const			{	return m_pD3DVertexBuffer;}

	// 6) operation
			CVertex&			operator=(const CVertex& p_rhs)			{	Duplicate(p_rhs); m_dwVertexStride=p_rhs.m_dwVertexStride; return *this;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
protected:
	// 1) Resotorable
	virtual BOOL				Restore();

	// 2) Process Message
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override	{	return 0;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			// 1) VertexBuffer Info
			CGPTR<D3DVERTEXBUFFER> m_pD3DVertexBuffer;

			// 2) Stride Info
			DWORD				m_dwVertexStride;
};


}
}
