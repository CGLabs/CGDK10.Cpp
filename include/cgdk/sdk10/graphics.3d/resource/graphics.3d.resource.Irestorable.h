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
// CGResource::IRestorable
//
// 1. CGResource::IRestorable��...
//    1) Vertex Buffer�� Delcation�� Class�̴�.
//    2) �� Class�� �Ϲ������� new�� �ؼ� ���������� �ʴ´�.
//	  3) ������ Create()�Լ��� ���� LPD3DTEXTURE�� ���������ν� ó���� �Ǹ�
//    4) ���������� shared����� �����Ƿ� �ַ� �̸� ���� ����Ѵ�.
//
// 2. CGResource::Buffer::CVretex�� ��� ����
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

class IRestorable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			IRestorable();
	virtual ~IRestorable();


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	virtual BOOL				Restore() PURE;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// Class) Restore Manager
	class CManagerRestorable;

	// Static) Restorable Manager
	static	CManagerRestorable	m_ManagerRestorable;
};


}