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
//*****************************************************************************
// Chosanghyun's 3DGame Network Root! = CGNetRootClinet!!!  ( ` ~`)b
//*****************************************************************************
// 1. CGNetRootClient��!
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
//
//
class ICG3DApplier : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICG3DSceneComponent,				// (I) 3D Object
	public						CGNameable::NString					// (@) Nameable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICG3DApplier() : m_eApplierType(APPLIER_TYPE_NONE)			{}
			ICG3DApplier(APPLIER_TYPE p_eType) : m_eApplierType(p_eType)	{}
	virtual	~ICG3DApplier()												{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
			APPLIER_TYPE		GetApplierType() const					{	return m_eApplierType;}
			void				SetApplierType(APPLIER_TYPE p_eType)	{	m_eApplierType=p_eType;}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	virtual void				Apply() PURE;

protected:
			APPLIER_TYPE		m_eApplierType;

};
