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
// CGResource::Mesh::CIndexedPrimitive
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


class CIndexedPrimitive : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CGResource::Mesh::CPrimitive			// (@) Mesh Primitive 
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CIndexedPrimitive();
			CIndexedPrimitive(const CIndexedPrimitive& p_rIndexed);
	virtual	~CIndexedPrimitive();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Create/Duplicate/Destroy
			void				CreateTriangle(float p_fSize=1.0f);
			void				CreateRect(float p_fSize=1.0f);
			void				CreateShadowVolume(CIndexedPrimitive* p_pResourceMeshShadow);
			void				Duplicate(const CIndexedPrimitive& p_rData);
	virtual	void				Destroy();

	virtual	BOOL				Draw(CGMSG& _Msg);

	virtual	BOOL				Transform(const MATRIX& _tm);

	virtual	BOOL				CalculateBoundingSphere(SPHERE& p_rBoundingSphere);
	virtual	BOOL				CalculateBoundingBox(AABB& p_rBoundingAABB);
	virtual	BOOL				CalculateBoundingBox(OBB& p_rBoundingOBB);

			void				SetIndexbuffer(INDEXBUFFER* p_pIndexbuffer)	{	m_Indexbuffer=p_pIndexbuffer;}
			CGPTR<INDEXBUFFER>	GetIndexbuffer() const						{	return m_Indexbuffer;}

	// 2) Operator 
			CIndexedPrimitive&	operator=(const CIndexedPrimitive& p_rCopy)	{	Duplicate(p_rCopy); return *this;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 2) Index Buffer & Prmiitive Data for Index
			CGPTR<INDEXBUFFER>	m_Indexbuffer;

			struct FILE
			{
				int				idxIndexbuffer;
				DWORD			dwBaseVertexIndex;

				DWORD			dwMinIndex;
				DWORD			dwVerticeCount;
			} m_IndexedPrimitiveInfo;
};


}
}