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
// net::io::socket::Ndummy
//
// 1. net::io::socket::Ndummy�� Ư¡!
//    1) �ƹ��� ����� �������� ���� Dummy �����̴�.
//    2) �Ϲ������� ���������� Isocket �������̽��� ������ �ʿ��� ��� �̰���
//       ���ȴ�.
//
//
//-----------------------------------------------------------------------------
class net::io::socket::Ndummy :
// inherited classes)
	virtual public				Isocket
{
// constructor/destructor)
public:
			Ndummy();
	virtual	~Ndummy();

// public)
public:
			bool				is_free() const noexcept { return reference_count() <= 1;}

// frameworks)
protected:
	virtual	void				on_prepare_socket() {}

// implementation) 
protected:
	virtual	void				process_prepare_socket(ADDRESS_FAMILY _address_family = AF_INET) override;
	virtual	bool				process_close_socket(uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept override;

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