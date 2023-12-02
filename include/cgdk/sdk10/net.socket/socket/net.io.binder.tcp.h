//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// net::io::binder::Ntcp
// 
// 1. binder��~
//    1) TCP�� ���� bind() ����� �ִ� �Լ��� TCP�� ���� ���۵� Ŭ�����̴�.
//    2) TCP�� ��� Accept�� ���� bind�� �����ϴµ� �̸� ���� Ŭ�����̴�.
//    3) Accept�� ���� �ʴ��� Ŭ���̾�Ʈ TCP ������ ��� BInd�� �ϰ��� �� ����
//       �ִ� �̶� ����� �� �ִ�.
//    4) TCP�� connector ��ü�� �⺻������ BInder�� ��ӹ޾� ���۵ȴ�.
//    5) bind�� �ּҿ� 0����  �����ϸ� �ϵ������ ��� �ּҿ� bind�Ǹ� ��Ʈ�� 0����
//       �ϸ� ������ �� ��Ʈ�� �ڵ������� �����Ͽ� bind�ȴ�.
//    6) Ư���� �ּҿ� ��Ʈ�� ���ε带 �� ���� �ǵ��� 1000�̻��� ��Ʈ�� ����ϴ�
//       ���� ����. �ֳ��ϸ� �� ������ ��Ʈ�� ����� ��Ʈ�� ���� �����̴�.
//
//-----------------------------------------------------------------------------
class net::io::binder::Ntcp :
// inherited classes)
	virtual public				net::io::Isocket,
	virtual public				net::io::Ibinder,
	virtual public				net::io::statistics::Nsocket
{
// publics)
public:
	virtual	bool				process_request_bind(const net::sockaddr& _address) override;
	virtual	void				process_reset_binder() override {}
};


}