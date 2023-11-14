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
// 1. CGResource::CBoneInfo��!
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
namespace CGResource
{

class CBoneInfo : 
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
			CBoneInfo();
			CBoneInfo(const CBoneInfo& p_rCopy);
	virtual	~CBoneInfo();

public:
			CBoneInfo(int p_iBoneCount);


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) ������ �ı�
			void				Create(int p_iBoneCount);
			void				Duplicate(const CBoneInfo& p_rBoneInfo);
	virtual	void				Destroy();

	// 2) Bone Count
			int					GetBoneCount() const					{	return (int)m_vectorBoneInfo.size();}

	// 3) Bone Set/Get
			void				SetBoneInfo(int p_indexBone, const MATRIX& p_rBone)	{	m_vectorBoneInfo[p_indexBone]=p_rBone;}
			const MATRIX&		GetBoneInfo(int p_indexBone) const		{	return m_vectorBoneInfo[p_indexBone];}
			MATRIX&				GetBoneInfo(int p_indexBone)			{	return m_vectorBoneInfo[p_indexBone];}

	// 5) operation
			CBoneInfo&			operator=(const CBoneInfo& p_rhs)		{	Duplicate(p_rhs); return *this;}


// ****************************************************************************
// Protected) 
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override		{	return 0;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
			vector<MATRIX>		m_vectorBoneInfo;
};


} // namespace CGResource
