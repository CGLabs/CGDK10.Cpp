//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                Web Classes                                *
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
// net::io::packetable::Nbase
//
// 1. net::io::packetable::CStream��!
//    1) TCP���� ���۵� packetable�̴�.
//    2) ���۹޾ƿ� �����͸� Packet������ �߶� message������ ���۸� �����
//       Imessageable�� �Ѱ��ִ� ������ �Ѵ�.
//    3) Steam���� ���������� ���޵Ǿ� ���� �������� head�� �о� ������ Packetũ��
//       �� ������ Imessageable�� process_message()�Լ��� ȣ���� �������ش�.
//
// 3. ���� ����
//    1) Ư���� ���� ����.
//
//
//-----------------------------------------------------------------------------
class net::io::Nsocket_secure :
	public						net::io::receivable::tcp::Ndefault,
	public						net::io::sendable::tcp::Ndefault,
	virtual public				net::io::Isender,
	virtual public				Icryptable
{
protected:
	virtual	void				process_reset_receivable() override;
	virtual	void				process_reset_sendable() noexcept override;

	virtual void				process_on_receive( const buffer_view& _buffer, const net::sockaddr& _address) override;
	virtual	intptr_t			process_complete_receivable( intptr_t _result, std::size_t _transferred) override;

	virtual	bool				process_sendable(const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _paddress) override;
	virtual	void				process_complete_sendable(uintptr_t _result, std::size_t _transferred_bytes, std::size_t _transferred_message) override;

public:
			buffer_view			m_buffer_decrypt_receiving;
			shared_buffer		m_buffer_decrypt_received;
};


}