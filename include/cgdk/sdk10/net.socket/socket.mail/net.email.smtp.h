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
//
// net::socket::smtp
//
//    1) 기본적인 tcp 소켓으로 send/receive 등을 수행할 수 있다.
//
// ----------------------------------------------------------------------------
class net::email::smtp :
	public                      object::Ninitializable_startable,
	public						object::Nnameable
{
public:
			smtp();
public:
			void				send(const sREQUEST& _email_request);
			void				send(sREQUEST&& _email_request);

			size_t				get_max_concurrent_socket() const noexcept { return m_max_concurrent_socket; }
			void				set_max_concurrent_socket(size_t _value) noexcept { m_max_concurrent_socket = _value; }

protected:
	virtual	void				on_email_sending(const sREQUEST& /*_email_send_request*/) {}
	virtual	void				on_email_sended(const sRESULT& _email_send_result)  { if (_email_send_result.request.complete) _email_send_result.request.complete(_email_send_result); }

private:
			class socket;
			friend class socket;

	virtual result_code			_process_start(context& _context) override;
	virtual result_code			_process_stopping() noexcept override;
	virtual result_code			_process_stop() noexcept override;

			void				process_complete_send(socket* _psocket);
			void				process_socket_closed(socket* _psocket);

			lockable<>			m_cs_email_request;
			std::string			m_email_server_domain;
			std::list<sREQUEST> m_list_send_email;
			size_t				m_max_concurrent_socket;

			circular_list<object_ptr<socket>> m_list_socket_queue;
			circular_list<object_ptr<socket>> m_list_socket_exist;
			sSOCKET_CONNECT_REQUEST_PARAMETER m_connect_parameter;

			shared_buffer		m_buf_EHLO;
	static	shared_buffer		m_s_buf_DATA;
	static	shared_buffer		m_s_buf_QUIT;
	static	shared_buffer		m_s_buf_email_DATA_tail;
};


}