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
// CGResource::Buffer::CVretex
//
// 1. CGResource::Buffer::CVretex는...
//    1) Vertex Buffer를 Delcation한 Class이다.
//    2) 이 Class는 일반적으로 new를 해서 생성하지는 않는다.
//	  3) 생성은 Create()함수를 통해 LPD3DTEXTURE가 생성됨으로써 처리가 되며
//    4) 내부적으로 shared기능이 있으므로 주로 이를 통해 사용한다.
//
// 2. CGResource::Buffer::CVretex의 기능 설명
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
