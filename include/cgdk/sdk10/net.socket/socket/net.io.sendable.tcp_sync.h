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
// net::io::sendable::Ntcp_sync
//
// 1. net::io::sendable::Ntcp_sync��!
//    1) TCP�� send�� �ѹ��� send�� �ѹ��� Overlapped I/O�� �ɾ �����ϴ� 
//       sendable�̴�.
//    2) �ѹ��� send�� �ѹ��� Overlapped I/O�� ���� ������ ������ �����Ͽ� send
//       �󵵰� ���� socket������ ���� ������ ����.
//    3) ������ send�� �󵵰� ���� socket������ ���� I/O�� ������ ������ ������
//       �� �����Ƿ� �󵵰� ���� send�� �����ϴ� socket������ �� sendable���
//       send Gathering�� �����ϴ� TCPGathering�� ����ϵ��� ���Ѵ�.
//    4) ��κ��� Server socket�̳� Client socket�� ��� �� ������ sendable��
//       ����ϴ�.
//
// 2. net::io::sendable::CTCP�� �ٽ�! Function�� ��� ����
//    1) process_sendable()		buffer�� �����Ѵ�.
//
//
//-----------------------------------------------------------------------------
class net::io::sendable::Ntcp_sync :
	virtual public				net::io::Isendable,
	virtual public				net::io::Iconnectable
{
protected:
	virtual	bool				process_sendable(const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _paddress) override;
	virtual	void				process_complete_sendable(uintptr_t _result, std::size_t _transferred_bytes, std::size_t _transferred_message) override;
	virtual	void				process_reset_sendable() noexcept override;

#if defined(_SYS_EPOLL_H)
	virtual	uint32_t			process_recover_sendable(intptr_t _event, std::size_t _param) override;
#endif

	#if defined(_WINSOCK2API_)
			bool				process_sendable_async(CGSOCKET _handle_socket, const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message);
	#endif
};


}