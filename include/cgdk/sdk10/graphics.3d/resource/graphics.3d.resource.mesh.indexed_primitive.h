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
// CGResource::Mesh::CIndexedPrimitive
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