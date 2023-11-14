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
// CGDK::crypt::ssl
//
//
//-----------------------------------------------------------------------------
namespace crypt
{

class ssl :
	virtual public				Icrypt,
	virtual public				object::Idestroyable
{
public:
			ssl() noexcept;
	virtual ~ssl() noexcept;

public:
	virtual	void				initialize_handshake_server(Icryptable* _pcryptable) override;
	virtual	void				initialize_handshake_client(Icryptable* _pcryptable) override;
	virtual	result_code			destroy() noexcept override;

	virtual	bool				encode(buffer_view& _dest, const const_buffer_view* _source, int _count) override;
	virtual	bool				decode(buffer_view& _dest, const_buffer_view* _source, int _count) override;

public:
			SSL*				m_pSSL;
			BIO*				m_pbio_receive;
			BIO*				m_pbio_send;

			object_ptr<crypt::ssl_context>	m_pssl_context;
};


}
}