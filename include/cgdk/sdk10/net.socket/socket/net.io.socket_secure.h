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
// 1. net::io::packetable::CStream란!
//    1) TCP으로 제작된 packetable이다.
//    2) 전송받아온 데이터를 Packet단위로 잘라서 message단위로 버퍼를 만들어
//       Imessageable에 넘겨주는 역할을 한다.
//    3) Steam으로 연속적으로 전달되어 오는 데이터의 head를 읽어 설정된 Packet크기
//       로 나누어 Imessageable의 process_message()함수를 호출해 전달해준다.
//
// 3. 주의 사항
//    1) 특별한 것은 없음.
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