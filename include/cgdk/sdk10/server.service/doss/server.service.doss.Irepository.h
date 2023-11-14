//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                              Account Classes                              *
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
//-----------------------------------------------------------------------------
namespace CGDK
{

class doss::Irepository :
// inherited classes)
	virtual public				object::Inameable,
	virtual public				object::Iidentifiable,
	virtual public				object::Istate,
	virtual public				object::Istartable,
	virtual public				object::Iinitializable,
	public						statistics::Nrepository
{
// public)
public:
	[[nodiscard]] auto			get_entity(sENTITY_ID _entity_id) { return process_entity_get(_entity_id); }
	[[nodiscard]] auto			find_entity(sENTITY_ID _entity_id) const noexcept { return process_entity_find(_entity_id); }
	[[nodiscard]] auto			get_repository_id() const noexcept { return m_id_repository; }

	virtual	bool				wait();

// framework)
protected:
	virtual	result_code			on_request_checkin (Itransactable* _ptransactable) { _ptransactable->set_result(eRESULT::SUCCESS); return eRESULT::SUCCESS; }
	virtual	result_code			on_request_checkout (Itransactable* _ptransactable) { _ptransactable->set_result(eRESULT::SUCCESS); return eRESULT::SUCCESS; }
	virtual	result_code			on_request_command (Itransactable* _ptransactable) { _ptransactable->set_result(eRESULT::SUCCESS); return eRESULT::SUCCESS; }
	virtual	result_code			on_request_update (Itransactable* _ptransactable) { _ptransactable->set_result(eRESULT::SUCCESS); return eRESULT::SUCCESS; }
	                          
// framework)
public:
	virtual object_ptr<Ientity> process_entity_get (sENTITY_ID _entity_id) PURE;
	virtual object_ptr<Ientity> process_entity_find (sENTITY_ID _entity_id) const noexcept PURE;

	virtual	result_code			process_request_transaction (Itransactable* _ptransactable);
			result_code			process_transaction (Itransactable* _ptransactable);
	virtual bool				process_complete_transaction (Itransactable* _ptransactable) noexcept;
	virtual void				process_fail_transaction (Itransactable* _ptransactable) noexcept;
	virtual void				process_cancel_checkin (Ientity* _pentity, sCHECKIN_ID _cid) noexcept;

			result_code			process_request_transaction_checkin	(Itransactable* _ptransactable);
			bool				process_complete_transaction_checkin (Itransactable* _ptransactable) noexcept;

			result_code			process_request_transaction_command	(Itransactable* _ptransactable);
			bool				process_complete_transaction_command (Itransactable* _ptransactable) noexcept;

			result_code			process_request_transaction_update (Itransactable* _ptransactable);
			bool				process_complete_transaction_update	(Itransactable* _ptransactable) noexcept;

			result_code			process_request_transaction_checkout (Itransactable* _ptransactable);
			bool				process_complete_transaction_checkout (Itransactable* _ptransactable) noexcept;

			result_code			process_request_transaction_create (Itransactable* _ptransactable);
			bool				process_complete_transaction_create	(Itransactable* _ptransactable) noexcept;

			result_code			process_request_transaction_remove (Itransactable* _ptransactable);
			bool				process_complete_transaction_remove	(Itransactable* _ptransactable) noexcept;

			sCHECKIN_ID			process_generate_new_cid (sCHECKIN_ID& _cid_request) noexcept;

public:
			sREPOSITORY_ID		m_id_repository;
			lockable<>			m_lockable_wait;
			lockable<>			m_lockable_map_entity;
			std::condition_variable_any m_cv_complete;

protected:
			friend class doss::manager_repository;
			friend class doss::Ientity;
			friend class doss::Itransactable;
};


}
