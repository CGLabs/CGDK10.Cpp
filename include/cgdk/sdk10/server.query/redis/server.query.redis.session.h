//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                Redis Classes                              *
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
// query::redis::session
//
//
// ----------------------------------------------------------------------------
class query::redis::session :
// inherited classes) 
	public						net::io::connect_requestable::Ntcp_reconnect,
	public						net::io::socket::tcp::Ndefault,
	public						net::io::connectable::tcp::Ndefault,
	public						net::io::sendable::tcp::Ndefault,
	public						net::io::sender::Nresp,
	public						net::io::receivable::tcp::Ndefault,
	public						net::io::packetable::Nresp,
	virtual public				Imessageable
{
// constructor/destructor)
public:
			session();
	virtual	~session();

// defintions) 
public:
			struct REQUEST_QUERY
			{
				object_ptr<Iquery>		pquery;
				shared_buffer			buf_request;
				std::function<void()>	response;
			};

// public)
public:
			bool				execute_query(REQUEST_QUERY&& _query);
			void				cancel_query_all() noexcept;

			void				add_query_reference();
			void				release_query_reference();

// framework)
protected:
	virtual void				on_request_connect(const net::sockaddr& _paddress_peer) override;

	virtual void				on_connect() override;
	virtual void				on_fail_connect(uint64_t _disconnect_reason) override;
	virtual	void				on_disconnect(uint64_t _disconnect_reason) override;

	virtual	result_code			process_message(sMESSAGE& _msg) override;

// implementation)
public:
			std::recursive_mutex m_cs_list_query;
			circular_list<REQUEST_QUERY> m_list_query;
			object_ptr<querier>	m_pquerier;

			REQUEST_QUERY		pop_query() noexcept;
			void				push_query(REQUEST_QUERY _request_info);
public:

			std::atomic<int>	m_query_reference;
			
};


}