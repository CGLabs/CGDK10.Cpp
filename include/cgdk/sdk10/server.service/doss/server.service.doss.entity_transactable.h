//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                 Distributed Object Storage System Classes                 *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
// doss::entity
//
//   
//
//-----------------------------------------------------------------------------
namespace CGDK
{

template <class TTRANACTION, class TSESSION>
class doss::entity_transactable :
	virtual public				Ireferenceable
{
public:
			typedef TTRANACTION	trasaction_t;
			typedef TSESSION	session_t;
			typedef typename TSESSION::session_id_t session_id_t;

public:
			result_code			request_transaction(object_ptr<trasaction_t>&& _ptransaction);
			void				complete_transaction() noexcept;

			void				register_client_session(object_ptr<session_t>&& _psession);
			void				unregister_client_session(session_id_t _session_id) noexcept;

			auto				size() const noexcept { scoped_lock(this->m_cs_queue_transaction) { return this->m_queue_transaction.size(); } }
			auto				client_session_now() noexcept { scoped_lock(this->m_cs_vector_client_info) { return (this->m_vector_client_session.empty() == false) ? this->m_vector_client_session.front() : object_ptr<session_t>();} }
			auto&				client_session() noexcept { return this->m_vector_client_session; }
			const auto&			statistics() const noexcept { return this->m_statistics; }

			struct sSTATISTICS
			{
				std::atomic<uint64_t> transaction_request{ 0 };
				std::atomic<uint64_t> transaction_success{ 0 };
				std::atomic<uint64_t> transaction_fail{ 0 };
			};
			int					m_idx_list = -1;

protected:
	virtual result_code			process_request_transaction(trasaction_t* _transaction);
	virtual void				process_on_session_register(session_t* /*_psession*/) {}
	virtual void				process_on_session_unresigter(session_t* /*_psession*/) noexcept {}

	virtual result_code			process_on_add_transaction(trasaction_t* /*_ptransaction*/) { return eRESULT::SUCCESS; }
	virtual void				process_on_remove_transaction(trasaction_t* /*_ptransaction*/) noexcept {}

			lockable<>			m_cs_queue_transaction;
			circular_list<object_ptr<TTRANACTION>> m_queue_transaction;
			object_ptr<TTRANACTION> m_ptransaction_now;
			size_t				m_max_transaction_queue = 8;
			bool				m_flag_transaction_prosses = false;
			sSTATISTICS			m_statistics;

			lockable<>			m_cs_vector_client_info;
			lockable<>			m_cs_client_register;
			std::vector<object_ptr<session_t>> m_vector_client_session;
};

}

#include "cgdk/sdk10/server.service/doss/server.service.doss.entity_transactable.inl"