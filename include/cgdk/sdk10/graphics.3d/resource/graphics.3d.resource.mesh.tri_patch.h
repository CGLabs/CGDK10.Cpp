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
// CGResource::Mesh::CTriPatch
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

class CTriPatch : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGResource::IMesh						// (I) Mesh Base
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CTriPatch();
	virtual	~CTriPatch();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Destroy
	virtual	void				Destroy();

	// 2) Draw Function
	virtual	BOOL				Draw(CGMSG& _Msg);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override	{	return 0;}

};


}
}