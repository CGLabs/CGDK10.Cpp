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
// 1. CGResource::CPlanelist란!
//    1) Terrain용 Bounding Object임.
//    2) 기본적으로 이것은 Connect만 지원할 뿐 Listen은 지원하지 않는다.
//    3) 소량의 연결처리르 전제로 하였으므로 Socket Manager와 Socket Pool 등은
//       지원하지 않는다.
//    4) 그래도 과거에 비해 반응속도가 크게 증가하였고 각종 Pending현상으로 인한
//       Failure를 거의 없앴다.
//
//-----------------------------------------------------------------------------
namespace CGResource
{

class CPlanelist : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGResource,							// (I) Texture Base
	public						CGNameable::NString						// (@) Nameable	
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CPlanelist();
			CPlanelist(const CPlanelist& p_rCopy);
	virtual ~CPlanelist();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Create/Duplicate/Release
			void				Create(int p_nPlane, int p_iPitch=0);
			void				Duplicate(const CPlanelist& p_rCopy);
	virtual	void				Destroy();

	// 2) Attributes
			void				Write(const PLANE* p_pPlaneData, DWORD p_dwSize, DWORD p_dwOffset=0);

	// 3) operation
			CPlanelist&			operator=(const CPlanelist& p_rhs)		{	Duplicate(p_rhs); return *this;}

	// 4) 
			PLANE&				GetPlane(int p_iIndex)					{	return m_vectorPlane[p_iIndex];}
			int					GetPlaneCount() const					{	return (int)m_vectorPlane.size();}


// ****************************************************************************
// Protected) 
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override	{	return 0;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) Plane list Info
			vector<PLANE>		m_vectorPlane;
			int					m_iPitch;		// Width(X의 길이)
};


}