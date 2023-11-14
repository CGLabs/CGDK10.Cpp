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
// doss::CRepositoryRemote
//-----------------------------------------------------------------------------
namespace CGDK
{

template <class TENTITY = doss::Ientity, class TCREATE = TENTITY>
class doss::repository::remote :
	public						Nrepository<TENTITY>,
	public						Nmessage_transmitter,
	public						net::io::connect_requestable::Ntcp_reconnect,
	public						net::socket::tcp<>,
	public						schedulable::Nexecutable
{
public:
			remote();
			remote(const std::string_view _name);
	virtual	~remote() noexcept;

public:
	virtual	bool				wait() { return Nrepository<TENTITY>::wait(); }

protected:
	virtual	void				on_initializing (context& _msg) override;
	virtual	void				on_initialize (context& _msg) override;
	virtual	void				on_destroying () override;
	virtual	void				on_destroy () override;
	virtual	void				on_starting (context& _msg) override;
	virtual	void				on_start (context& _msg) override;
	virtual	void				on_stop_request () override;
	virtual	void				on_stopping () override;
	virtual	void				on_stop () override;
	virtual	void				on_execute () override;

	virtual void				on_connect () override;
	virtual void				on_fail_connect (uint64_t _reason) override;
	virtual void				on_disconnect (uint64_t _reason) override;
	virtual void				on_request_connect (const net::sockaddr& _address) override;

protected:
	DECLARE_CGMESSAGE_MAP

	virtual	result_code			on_message (sMESSAGE_NETWORK& _msg) override;
			result_code			on_message_SERVER_DOSS_RESPONSE_CERTIFY (sMESSAGE_NETWORK& _msg);
			result_code			on_message_SERVER_DOSS_COMMAND_RESPONSE (sMESSAGE_NETWORK& _msg);
			result_code			on_message_SERVER_DOSS_CONTROL_REQUEST (sMESSAGE_NETWORK& _msg);
			result_code			on_message_SERVER_DOSS_SEND_ACK (sMESSAGE_NETWORK& _msg);

protected:
	[[nodiscard]] virtual object_ptr<TENTITY>	process_alloc_entity(sENTITY_ID _entity_id) override;
			void				process_reset_repository(const sREPOSITORY_ID& _id_repository_remote, std::vector<sREPOSITORY_ID>&& _vec_repository);
	[[nodiscard]] virtual uint16_t process_get_default_port() noexcept override { return 31001; }
	virtual result_code			process_request_transaction(Itransactable* _ptransactable) override;
	virtual void				process_fail_transaction(Itransactable* _ptransactable) noexcept;
			bool				process_send_restoreable(Itransactable* _ptransactable);
			bool				process_send_restoreable_COMMAND_FAIL(Itransactable* _ptransactable);
			void				process_send_ack(uint64_t _send_sequence) noexcept;
			void				process_receive_ack(uint64_t _receive_sequence) noexcept;

			sREPOSITORY_ID		m_id_repository_remote_alloc;
			std::vector<sREPOSITORY_ID> m_vector_id_repository_remote;

			lockable<>			m_lockable_send_sequence;
			uint64_t			m_send_sequence = 0;
			uint64_t			m_send_sequence_ack = 0;
			circular_list<shared_buffer> m_send_sequence_buffer;
			std::atomic<uint64_t> m_receive_sequence = 0;
};


}

#include "cgdk/sdk10/server.service/doss/server.service.doss.repository.remote.inl"
