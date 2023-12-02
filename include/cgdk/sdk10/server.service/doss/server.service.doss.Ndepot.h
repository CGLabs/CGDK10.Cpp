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
//
// doss::Ndepot<TENTITY>
//
//
//-----------------------------------------------------------------------------
namespace CGDK
{

class doss::Ndepot :
// inherited classes)
	public						doss::Idepot,
	public						group::list_sender<doss::Idepot::socket>
{
// constructor/destructor) 
public:
			Ndepot();
			Ndepot(const std::string_view _name);
	virtual	~Ndepot() noexcept;

public:
	[[nodiscard]] virtual object_ptr<Irepository> get_repository(const shared_buffer& _buffer) const noexcept PURE;
	[[nodiscard]] auto			get_source_id() const { return m_id_repository.object_id();}
			void				checkout_all() noexcept;

// frameworks) 
protected:
	// 1) Initialize/Destry
	virtual	void				on_initializing (context& _msg) override;
	virtual	void				on_initialize (context& _msg) override;
	virtual	void				on_destroying () override;
	virtual	void				on_destroy () override;

	// 2) Start/Stop
	virtual	void				on_starting (context& _msg) override;
	virtual	void				on_start (context& _msg) override;
	virtual	void				on_stopping () override;
	virtual	void				on_stop () override;

	// 3) Member Enter/Leave
	virtual	result_code			on_member_entering (socket* _pmember, sMESSAGE& _msg);
	virtual	void				on_member_entered (socket* _pmember, sMESSAGE& _msg);
	virtual	uintptr_t			on_member_leaving (socket* _pmember);
	virtual	void				on_member_leaved (socket* _pmember, uintptr_t _result);

// implementation) 
protected:
	virtual	void				process_entity_transaction_request (Itransactable* _ptransactable) noexcept override;
	virtual	void				process_entity_transaction_complete (Itransactable* _ptransactable) noexcept override;
	virtual	void				process_entity_set (Itransactable* _ptransactable) override;
	virtual	bool				process_entity_reset (Ientity* _pentity, const sCHECKIN_ID& _cid, bool _is_force) noexcept override;
	[[nodiscard]] object_ptr<socket> process_find_member (const sSESSION_ID& _session_id) const noexcept;
	[[nodiscard]] object_ptr<socket> process_find_member (const sREPOSITORY_ID& _repository_id, member_t* _pmember_self) const noexcept;

// message)  
protected:
	DECLARE_CGMESSAGE_MAP

	// 1) Message
	virtual result_code			on_message (sMESSAGE_NETWORK& _msg) override;
			result_code			on_message_SERVER_DOSS_COMMAND_REQUEST (sMESSAGE_NETWORK& _msg);
			result_code			on_message_SERVER_DOSS_COMMAND_CANCEL (sMESSAGE_NETWORK& _msg);
			result_code			on_message_SERVER_DOSS_COMMAND_FAIL (sMESSAGE_NETWORK& _msg);
			result_code			on_message_SERVER_DOSS_SEND_ACK (sMESSAGE_NETWORK& _msg);

protected:
	// 1) acceptor/socket
			own_ptr<net::acceptor<socket>>	m_pacceptor_remository;
			own_ptr<group_immigration>		m_pgroup_socket_immigration;
			std::vector<object_ptr<restore>> m_vector_restore;

	// 2) checkins
			lockable<>			m_lockable_map_cid;
			std::map<sCHECKIN_ID, sSESSION_ID> m_map_cid;

	// 3) Repository ID
			sREPOSITORY_ID		m_id_repository;

	// 4) statistics
			statistics::entity	m_statistics;
};


}
