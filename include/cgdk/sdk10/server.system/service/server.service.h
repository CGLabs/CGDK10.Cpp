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
// service
//
// 
// ----------------------------------------------------------------------------
class server_system::service :
	public						Nservice
{
public:
			service();
			service(const std::string_view _name);
	virtual ~service();

public:
			void				send_to_admin_server(const shared_buffer& _buffer);

protected:
	virtual result_code			process_message(sMESSAGE& _msg) override;
	virtual	result_code			on_message_SERVER_ADMIN_CERTIFY_RESPONSE(sMESSAGE_NETWORK& _msg);
	virtual	result_code			on_message_SERVER_ADMIN_INSTANCE_CERTIFY_RESPONSE(sMESSAGE_NETWORK& _msg);
	virtual	result_code			on_message_SERVER_ADMIN_REQUEST_UPDATE_SETTING( sMESSAGE_NETWORK& _msg);
	virtual	result_code			on_message_SERVER_ADMIN_REQUEST_INIT_SERVICE( sMESSAGE_NETWORK& _msg);
	virtual	result_code			on_message_SERVER_ADMIN_REQUEST_DESTROY_SERVICE( sMESSAGE_NETWORK& _msg);
	virtual	result_code			on_message_SERVER_ADMIN_REQUEST_START_SERVICE( sMESSAGE_NETWORK& _msg);
	virtual	result_code			on_message_SERVER_ADMIN_REQUEST_STOP_SERVICE( sMESSAGE_NETWORK& _msg);
	virtual	result_code			on_message_SERVER_ADMIN_REQUEST_PAUSE_SERVICE( sMESSAGE_NETWORK& _msg);
	virtual	result_code			on_message_SERVER_ADMIN_REQUEST_CONTINUE_SERVICE( sMESSAGE_NETWORK& _msg);
	virtual	result_code			on_message_SYSTEM_LOG(sMESSAGE_NETWORK& _msg);

	virtual	void				on_server_certified(const shared_buffer& /*_buffer*/) {}

protected:
	virtual	void				process_state_changed(eOBJECT_STATE _state_new, eOBJECT_STATE _state_old) override;

	virtual	result_code			_process_initializing(context& _context) override;
	virtual	void				_process_initializing_pre(context& _context);
	virtual	void				_process_initializing_post(context& _context);

	virtual	result_code			_process_initialize(context& _context) override;
	virtual	void				_process_initialize_pre(context& _context);
	virtual	void				_process_initialize_post(context& _context);

	virtual	result_code			_process_destroying() noexcept override;
	virtual	void				_process_destroying_pre() noexcept;
	virtual	void				_process_destroying_post() noexcept;

	virtual	result_code			_process_destroy() noexcept override;
	virtual	void				_process_destroy_pre() noexcept;
	virtual	void				_process_destroy_post() noexcept;

protected:
			lockable<own_ptr<server_admin::socket_to_admin>> m_psocket_to_admin;
};


}