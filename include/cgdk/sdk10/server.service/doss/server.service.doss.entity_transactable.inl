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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
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
inline result_code doss::entity_transactable<TTRANACTION, TSESSION>::request_transaction(object_ptr<trasaction_t>&& _ptransaction)
{
	// check)
	CGASSERT_ERROR(_ptransaction.exist());

	// statistics)
	++this->m_statistics.transaction_request;

	// 1) on add transaction
	{
		// - call 'process_on_add_transaction'
		auto result = this->process_on_add_transaction(_ptransaction.get());

		// check)
		THROW_IF(result != eRESULT::SUCCESS, throwable::failure(result));
	}

	// 2) push transaction?
	scoped_lock(this->m_cs_queue_transaction)
	{
		if (this->m_flag_transaction_prosses == true)
		{
			// - queuing
			this->m_queue_transaction.push_back(std::move(_ptransaction));

			// return)
			return eRESULT::PENDED;
		}

		// - set flag
		this->m_flag_transaction_prosses = true;
	}

	// 3) set transaction now
	this->m_ptransaction_now = std::move(_ptransaction);

	// 4) process_transactions
	auto result = this->process_request_transaction(this->m_ptransaction_now);

	if (result != eRESULT::PENDED)
	{
		// statistics) 
		if (result <= eRESULT::DONE)
			++this->m_statistics.transaction_success;
		else
			++this->m_statistics.transaction_fail;

		// - complete transaction
		this->complete_transaction();
	}

	// return)
	return result;
}

template <class TTRANACTION, class TSESSION>
inline void doss::entity_transactable<TTRANACTION, TSESSION>::complete_transaction() noexcept
{
	// 1) reset now transaction
	{
		// check)
		CGASSERT_ERROR(this->m_ptransaction_now.exist());

		// - call 'process_on_remove_transaction'
		this->process_on_remove_transaction(this->m_ptransaction_now.get());

		// - reset transaction
		this->m_ptransaction_now.reset();
	}

	for (;;)
	{
		// 3) pop front
		scoped_lock(this->m_cs_queue_transaction)
		{
			// - break if no more transaction
			if (this->m_queue_transaction.empty())
			{
				// - set flag false
				this->m_flag_transaction_prosses = false;

				// break) 
				break;
			}

			// - get next transaction
			this->m_ptransaction_now = std::move(this->m_queue_transaction.front());

			// - pop front
			this->m_queue_transaction.pop_front();
		}

		// 4) execute transaction
		auto result = this->process_request_transaction(this->m_ptransaction_now);

		// 5) break if pended
		BREAK_IF(result == eRESULT::PENDED);

		// statistics) 
		if (result <= eRESULT::DONE)
			++this->m_statistics.transaction_success;
		else
			++this->m_statistics.transaction_fail;

		// 6) on remove transaction
		{
			// - call 'process_on_remove_transaction'
			this->process_on_remove_transaction(this->m_ptransaction_now.get());

			// - reset transaction
			this->m_ptransaction_now.reset();
		}
	}
}

template <class TTRANACTION, class TSESSION>
inline void doss::entity_transactable<TTRANACTION, TSESSION>::register_client_session(object_ptr<session_t>&& _psession)
{
	//-----------------------------------------------------------------
	// 설명) reset session_info 
	// 
	//   - client의 session 정보를 setting한다.
	//   - session_t은  account_id 정보와 socket 정보 그리고 접속 ip
	//   - 초기 등록되는 session_t은 reuesting 정보는 반드시 비어
	//     있어야 한다.
	// 
	//-----------------------------------------------------------------
	// declare) 
	object_ptr<session_t> psession_old;

	// check)
	CGASSERT_ERROR(_psession.exist());
	
	// check)
	THROW_IF(_psession.empty(), throwable::failure(eRESULT::INVALID_ARGUMENT, 0, "'_client_session.psocket' is nullptr"sv));

	scoped_lock(this->m_cs_client_register)
	{
		scoped_lock(this->m_cs_vector_client_info)
		{
			// 1) 이미 존재하면 그냥 return한다.
			auto iter_aleady_exist = std::find(this->m_vector_client_session.begin(), this->m_vector_client_session.end(), _psession);

			// check)
			RETURN_IF(iter_aleady_exist != this->m_vector_client_session.end(), );

			// 2) set new clinet session and remove old client session
			if (this->m_vector_client_session.empty() == false)
			{
				psession_old = std::move(this->m_vector_client_session.front());
				this->m_vector_client_session.erase(this->m_vector_client_session.begin());
			}

			// 3) push_back
			this->m_vector_client_session.push_back(_psession);
		}

		// 4) unregister old session
		if (psession_old.exist())
		{
			this->process_on_session_unresigter(std::move(psession_old));
		}

		// 5) register new session
		this->process_on_session_register(_psession);
	}
}

template <class TTRANACTION, class TSESSION>
inline void doss::entity_transactable<TTRANACTION, TSESSION>::unregister_client_session(session_id_t _session_id) noexcept
{
	// declare) 
	object_ptr<session_t> psession;

	scoped_lock(this->m_cs_vector_client_info)
	{
		// 1) find
		auto iter_find = std::find_if(this->m_vector_client_session.begin(), m_vector_client_session.end(), [=](const auto& _iter) { return _iter->session_id == _session_id; });
		
		// check)
		RETURN_IF(iter_find == this->m_vector_client_session.end(), );

		// 2) move...
		psession = std::move(*iter_find);

		// 3) erase
		this->m_vector_client_session.erase(iter_find);
	}

	// 4) call on_session_unregister
	this->process_on_session_unresigter(psession);
}

template <class TTRANACTION, class TSESSION>
inline result_code doss::entity_transactable<TTRANACTION, TSESSION>::process_request_transaction(trasaction_t* _transaction)
{
	return _transaction->process_transaction();
}

}
