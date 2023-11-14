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
// doss::CAccount
//
//  State of Account
//
//   
//
//-----------------------------------------------------------------------------
namespace CGDK
{

class doss::Ientity :
// inherited classes)
	virtual public				Ireferenceable
{
public:
	// 1) request 
			result_code			request_transaction(Itransactable* _ptransactable) { return process_request_transaction (_ptransactable); }
	virtual	bool				complete_transaction(Itransactable* _ptransactable) noexcept;
	virtual bool				cancel_transaction(Itransactable* _ptransactable) noexcept { return process_cancel_command(_ptransactable); }
			void				checkout_all() noexcept;

	// 2) entity id & state
			const sENTITY_ID&	get_entity_id() const noexcept { return m_eid;}
			eOBJECT_STATE		get_entity_state() const noexcept { return m_state_entity;}
			std::size_t			get_queued_transaction_count() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_queue_transaction)); return this->m_queue_command.size(); }
			std::size_t			get_checkin_count() const noexcept { std::lock_guard<lockable<>> cs(const_cast<lockable<>&>(this->m_lockable_queue_transaction)); return this->m_list_cid.size(); }
			object_ptr<Isession> find_session(const sCHECKIN_ID& _cid) const noexcept;

protected:
	virtual	result_code			process_request_transaction(Itransactable* _ptransactable);
			object_ptr<Itransactable> process_complete_transaction(Itransactable* _ptransactable) noexcept;
			bool				process_cancel_command(Itransactable* _ptransactable) noexcept;

public:
			void				process_insert_cid_and_remove_existing_cid(Itransactable* _ptransactable);
			void				process_insert_cid_posterior(Itransactable* _ptransactable);
			void				process_insert_cid_duplicate(Itransactable* _ptransactable);
			void				process_transfer_cid_to_other_session(Itransactable* _ptransactable);
			bool				process_remove_cid(Isession* _psession) noexcept;
			bool				process_remove_cid(const sCHECKIN_ID& _cid);
			uint64_t			generate_request_id() noexcept;
public:
	// 1) lockable
			lockable<>			m_lockable_entity;

	// 2) entity id
			sENTITY_ID			m_eid;

	// 3) entity state and revision
			eOBJECT_STATE		m_state_entity{ eOBJECT_STATE::NONE };
			uint64_t			m_status{ 0 };
			uint64_t			m_revision{ 0 };

	// 4) repository
			object_ptr<Irepository>	m_prepository;

	// 5) queue command
			std::atomic<uint64_t> m_index_request{0};
			lockable<>			m_lockable_queue_transaction;
			circular_list<object_ptr<Itransactable>> m_queue_command;

	// 6) session
			std::vector<std::pair<sCHECKIN_ID, object_ptr<Isession>>> m_list_cid;
			int					m_idx_list = -1;
};


}