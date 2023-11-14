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
// 1. ICGResource��!
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

class CBoneInfo : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DApplier,							// (I) Applier
	public						ICGDeviceGraphic						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CBoneInfo();
	virtual	~CBoneInfo();

public:
			CBoneInfo(CGResource::CBoneInfo* p_pBoneInfo, const MATRIX** p_ppBone=NULL);
			CBoneInfo(CGResource::CBoneInfo* p_pBoneInfo, const vector<int>& p_rvectorBoneIndex, const vector<CGPTR<ICGObject>>& p_vectorScenenode);


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
			void				Create(CGResource::CBoneInfo* p_pBoneInfo, const MATRIX** p_ppBone=nullptr);
			void				Create(CGResource::CBoneInfo* p_pBoneInfo, const vector<int>& p_rvectorBoneIndex, const vector<CGPTR<ICGObject>>& p_vectorScenenode);
			void				Destroy();

			void				SetResourceBoneInfo(CGResource::CBoneInfo* p_presourceBoneinfo)	{	m_presourceBoneinfo=p_presourceBoneinfo;}
			CGPTR<CGResource::CBoneInfo>	GetResourceBoneInfo() const					{	return m_presourceBoneinfo;}

			void				SetBone(int p_BoneNumber, const MATRIX* p_pBone)		{	m_vectorBone[p_BoneNumber] = p_pBone;}
			const MATRIX*		GetBone(int p_BoneNumber) const			{	return m_vectorBone[p_BoneNumber];}

			void				ApplyBoneInfo() const;
	virtual	void				Apply();


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
			CGPTR<CGResource::CBoneInfo>	m_presourceBoneinfo;
			vector<const MATRIX*>	m_vectorBone;
};


}