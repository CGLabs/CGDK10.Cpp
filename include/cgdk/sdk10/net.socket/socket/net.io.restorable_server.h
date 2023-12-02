//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
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
/*!
* @class NRetransferable
*
* @ingroup net::io::NRetransferable
*
* @brief 접속이 종료되었을 때 전송내용을 보존하고 있다가 재전송을 해주는 모듈
*
*/
//-----------------------------------------------------------------------------
class net::io::Irestorable_server :
	virtual public				Irestorable
{
public:
	virtual	bool				disconnect (uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept override;
	virtual	bool				process_send (shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option) override;
	virtual	void				process_reset_connectable () noexcept override;

public:
	virtual void				on_request_connect (const net::sockaddr& /*_address*/) {}
	virtual void				on_connect () {}
	virtual void				on_disconnect (uint64_t /*_disconnect_reason*/) {}
	virtual void				on_fail_connect (uint64_t /*_disconnect_reason*/) {}
	virtual void				on_restoring () {}
	virtual void				on_restore () {}
	virtual void				on_suspend (uint64_t /*_disconnect_reason*/) {}

public:
	virtual	void				process_create_socket(ADDRESS_FAMILY _address_family) override;
	virtual	void				process_prepare_socket (ADDRESS_FAMILY _address_family) override;
	virtual void				process_dispose_socket() noexcept override;
	virtual	void				process_request_connect ( const net::sockaddr& _address) override;
	virtual	bool				process_complete_connect (uintptr_t _result) override;
	virtual	bool				process_complete_disconnect () override;
	virtual	bool				process_close_socket (uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept override;

	virtual void				process_request_io_restore  (result_code _result, SEQUENCE_ID _ack_received) override;
	virtual void				process_response_io_restore (result_code _result, SEQUENCE_ID _ack_received) override;
	virtual void				process_complete_io_restore (result_code _result) override;

	virtual	void				process_on_connect ();
	virtual	void				process_on_disconnect (uint64_t _disconnect_reason, eSOCKET_STATE _socket_state);
	virtual	void				process_on_fail_connect (uint64_t _disconnect_reason);
			void				process_on_restoring ();
			void				process_on_restore ();
			void				process_on_suspend (uint64_t _disconnect_reason);
public:
			
			object_ptr<Irestore_server>	m_prestore_server;
};


}