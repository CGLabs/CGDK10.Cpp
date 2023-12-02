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
// net::io::socket::Nbase
//
//  socket을 위한 기본 통계정보 클래스와 초기화에 관련된 함수들을 가지고 있다.
//
//-----------------------------------------------------------------------------
class net::io::socket::Nbase :
	virtual public				Isocket,
	virtual public				net::io::statistics::Nsocket
{
public:
	virtual ~Nbase() noexcept {}

protected:
	virtual	void				on_preparing_socket() {}
	virtual	void				on_prepare_socket() {}
	virtual	void				on_closesocket(uint64_t /*_disconnect_reason*/) {}

	virtual	void				process_prepare_socket(ADDRESS_FAMILY _address_family) override;

public:
			Ibinder*			m_pbinder = nullptr;
			Iconnect_requestable* m_pconnect_requestable = nullptr;
			Iconnectable*		m_pconnectable = nullptr;
			Isendable*			m_psendable = nullptr;
			Isend_request*		m_psend_request = nullptr;
			Ireceivable_stream*	m_preceivable_stream = nullptr;
			Ireceivable_datagram* m_preceivable_datagram = nullptr;
			Ipacketable*		m_ppacketable = nullptr;
};


}