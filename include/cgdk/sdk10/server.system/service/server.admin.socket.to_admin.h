//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Admin Classes                            *
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
// ----------------------------------------------------------------------------
//
// server_admin::socket_to_admin (server -> admin)
//
// 
// ----------------------------------------------------------------------------
class server_admin::socket_to_admin : 
	public						net::io::connect_requestable::Ntcp_reconnect,
	public						net::socket::tcp<>,
	public						Nmessage_transmitter,
	public						schedulable::Iexecutable,
	virtual public				Ilogger
{
public:
			socket_to_admin();
	virtual ~socket_to_admin();

			void				set_service(server_system::service* _pservice) noexcept;
			void				reset_service() noexcept;
			lockable<>			m_lockable_notify;
private:
	virtual void				on_connect() override;
	virtual void				on_disconnect(uint64_t _disconnect_reason) override;

	virtual result_code			on_message (sMESSAGE_NETWORK& _msg) override;
			result_code			on_message_SERVER_ADMIN_EXCEPTION_DUMP (sMESSAGE_DUMP& _msg); // eMESSAGE::DUMP
			result_code			on_message_FACTORY_REGISTER (sMESSAGE& _msg); // eMESSAGE::FACTORY::FACTORY_REGISTER
			result_code			on_message_FACTORY_UNREGISTER (sMESSAGE& _msg); // eMESSAGE::FACTORY::FACTORY_UNREGISTER
			result_code			on_message_FACTORY_UPDATE (sMESSAGE& _msg); // eMESSAGE::FACTORY::FACTORY_UPDATE
			result_code			on_message_THREAD_REGISTER (sMESSAGE& _msg); // eMESSAGE::THREAD_REGISTER
			result_code			on_message_THREAD_UNREGISTER (sMESSAGE& _msg); // eMESSAGE::THREAD_UNREGISTER
			result_code			on_message_EXECUTOR_REGISTER (sMESSAGE& _msg); // eMESSAGE::EXECUTOR_REGISTER
			result_code			on_message_EXECUTOR_UNREGISTER (sMESSAGE& _msg); // eMESSAGE::EXECUTOR_UNREGISTER
			result_code			on_message_EXECUTOR_UPDATE (sMESSAGE& _msg); // eMESSAGE::EXECUTOR_UNREGISTER
			result_code			on_message_NETWORK_SOCKET_CONNECTIVE_REGISTER (sMESSAGE& _msg); // eMESSAGE::NETWORK::SOCKET::CONNECTIVE_REGISTER
			result_code			on_message_NETWORK_SOCKET_CONNECTIVE_UNREGISTER (sMESSAGE& _msg); // eMESSAGE::NETWORK::SOCKET::CONNECTIVE_UNREGISTER
			result_code			on_message_NETWORK_SOCKET_CONNECTIVE_UPDATE (sMESSAGE& _msg); // eMESSAGE::NETWORK::SOCKET::CONNECTIVE_UPDATE
			result_code			on_message_NETWORK_SOCKET_BINDER_REGISTER (sMESSAGE& _msg); // eMESSAGE::NETWORK::SOCKET::BINDER_REGISTER
			result_code			on_message_NETWORK_SOCKET_BINDER_UNREGISTER (sMESSAGE& _msg); // eMESSAGE::NETWORK::SOCKET::BINDER_UNREGISTER
			result_code			on_message_NETWORK_SOCKET_BINDER_UPDATE (sMESSAGE& _msg); // eMESSAGE::NETWORK::SOCKET::BINDER_UPDATE
			result_code			on_message_SERVER_TIME_EVENT_EVENT_REGISTER (sMESSAGE& _msg); // eMESSAGE::SERVER::EVENT::ADD_EVENT
			result_code			on_message_SERVER_TIME_EVENT_EVENT_UNREGISTER (sMESSAGE& _msg); // eMESSAGE::SERVER::EVENT::REMOVE_EVENT
			result_code			on_message_SERVER_TIME_EVENT_EVENT_UPDATE (sMESSAGE& _msg); // eMESSAGE::SERVER::EVENT::REMOVE_EVENT
			result_code			on_message_SERVER_TIME_EVENT_EVENT_EXECUTE (sMESSAGE& _msg); // eMESSAGE::SERVER::EVENT::REMOVE_EVENT

	virtual result_code			process_message(sMESSAGE& _msg) override;
	virtual	intptr_t			process_execute(intptr_t _return, size_t _param) override;
	virtual	void				process_log(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) override;

			object_ptr<server_system::service> m_pservice;
};


}