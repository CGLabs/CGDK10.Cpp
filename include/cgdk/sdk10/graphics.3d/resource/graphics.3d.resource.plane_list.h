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
// 1. CGResource::CPlanelist��!
//    1) Terrain�� Bounding Object��.
//    2) �⺻������ �̰��� Connect�� ������ �� Listen�� �������� �ʴ´�.
//    3) �ҷ��� ����ó���� ������ �Ͽ����Ƿ� Socket Manager�� Socket Pool ����
//       �������� �ʴ´�.
//    4) �׷��� ���ſ� ���� �����ӵ��� ũ�� �����Ͽ��� ���� Pending�������� ����
//       Failure�� ���� ���ݴ�.
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
			int					m_iPitch;		// Width(X�� ����)
};


}