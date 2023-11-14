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
// CGResource::Buffer::CIndex
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
namespace Buffer
{

class CIndex : 
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
			CIndex();
			CIndex(const CIndex& p_rCopy);
			CIndex(DWORD p_dwSize, DWORD p_dwUsage=D3DUSAGE_WRITEONLY, D3DFORMAT p_Format=D3DFMT_INDEX16, D3DPOOL p_Pool=D3DPOOL_MANAGED);
	virtual	~CIndex();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Create & Destroy
			void				Create(DWORD p_dwSize, DWORD p_dwUsage=D3DUSAGE_WRITEONLY, D3DFORMAT p_Format=D3DFMT_INDEX16, D3DPOOL p_Pool=D3DPOOL_MANAGED);
			void				Create(const CIndex& p_rIndexBuffer, DWORD p_dwUsage=D3DUSAGE_WRITEONLY, D3DPOOL p_Pool=D3DPOOL_MANAGED);
			void				Duplicate(const CIndex& p_rCopy);
	virtual	void				Destroy();

	// 2) push_back
			void				AppendIndexbuffer(const CIndex& p_prIndexbuffer);
			void				WriteBuffer(void* _pBuffer, DWORD p_dwSize, DWORD p_dwPosition=0);

	// 3) Lock & UnLock
			LPINDEX_SIZE		Lock(DWORD p_dwFlags=0, DWORD p_dwOffsetToLock=0, DWORD p_dwSizeToLock=0) const;
			void				Unlock() const;

	// 4) Apply
			void				ApplyIndices();

	// 5) Buffer Attribute
			bool				IsCreated() const						{	return m_pD3DIndexBuffer.exist();}
			bool				IsDestroyed() const						{	return !IsCreated();}

			void				GetDesc(D3DINDEXBUFFER_DESC* p_pDesc) const;
			CGPTR<D3DINDEXBUFFER> GetD3DIndexbuffer() const				{	return m_pD3DIndexBuffer;}

	// 6) operation
			CIndex&				operator=(const CIndex& p_rhs)			{	Duplicate(p_rhs); return *this;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
private:
	// 1) Restorable
	virtual	BOOL				Restore();

	// 2) Process Render
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override		{	return 0;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			CGPTR<D3DINDEXBUFFER>	m_pD3DIndexBuffer;
};


}
}
