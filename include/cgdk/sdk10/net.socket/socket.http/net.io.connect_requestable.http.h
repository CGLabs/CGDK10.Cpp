//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        network socket http classes                        *
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
// net::io::connect_requestable::Nhttp (Web�� ������)
//
// 1. net::io::connect_requestable::Ntcp�̶�!
//    1) TCP socket�� Client ���忡�� ������...
//    2) 
//    3) �⺻������ Inameable�� ��ӹ޾� �̸��� ������ �� �ִ�.
//
// 2. �߿� �Լ�.
//    1) �Ϲ����� ����� net::io::Iconnect_requestable�� ���ǵ� �پ��� ������ connect(...)
//		 �Լ��� Ȱ���Ѵ�.
//    2) ���� connect�� ��û���� �� ó���Ǿ�� �ϴ� ���� �ִٸ� ������ �Լ���
//       �������Ͽ� ������ �� �ִ�.
//
//       virtual void on_request_connect( const net::sockaddr& _paddress_peer);
//
//    ����) Iexecutable�� ��ӹ޾� ó���ϹǷ� �� Ŭ������ ��ӹ��� Ŭ��������
//          process_execute()�� �������ϸ� ����ó���� ���� ���� �� �ִ�.
// 
//
//-----------------------------------------------------------------------------
class net::io::connect_requestable::Nhttp :
// inherited classes) 
	public						net::io::connect_requestable::Ntcp_secure
{
// publics) 
public:
	// 1) connect �Լ�
	virtual	bool				connect(Ihttp_request* _prequest);
			bool				connect(const std::string_view _url);
	
// implementation) 
protected:
			lockable<object_ptr<Ihttp_request>>	m_prequest;

protected:
			void				set_request(Ihttp_request* _prequest) noexcept;
			void				reset_request() noexcept;
			object_ptr<Ihttp_request> move_request() noexcept;

protected:
	virtual	uint16_t			process_get_default_port() noexcept override { return (m_pssl_context.empty()) ? 80 : 443; }
};


}
