//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / Release 2017.01.03                        *
//*                                                                           *
//*                             Web Server Classes                            *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 (c) 2016 Cho Sanghyun All right reserved.                 *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// CGDK::net::socket::web_server
//
//
// ----------------------------------------------------------------------------
class net::socket::web_server :
// inherited classes) 
	public						net::socket::http_server,
	public						Nmessage_transmitter
{
// public) 
public:
			auto				get_web_entity() const noexcept { return m_pweb_entity; }
			void				set_web_entity(server::web::Ientity* _pweb_entity) noexcept { m_pweb_entity = _pweb_entity; }
			void				reset_web_entity() noexcept { m_pweb_entity.reset(); }
			const auto&			get_webserver_context() const noexcept { return m_webserver_context; }
			void				set_webserver_name(std::string_view _server_name) noexcept { m_webserver_context.server_name = _server_name; }
			auto				get_webserver_name() const noexcept { return m_webserver_context.server_name; }
			void				set_webserver_version(uint32_t _version_high, uint32_t _version_low) noexcept { m_webserver_context.server_version_high = _version_high; m_webserver_context.server_version_low = _version_low; }
			auto				get_webserver_high() noexcept { return m_webserver_context.server_version_high; }
			auto				get_webserver_low() noexcept { return m_webserver_context.server_version_low; }

// framework) 
protected:
	// 1) 접속이 되었을 때 불려지는 함수.
	virtual void				on_connect(net::io::Iconnective* _pconnective);

	// 2) 접속이 종료되었을 때 호출되는 함수.
	virtual void				on_disconnect(uint64_t _disconnect_reason);

	// 3) Message Packet을 받았을 때 불려지는 함수.
	virtual result_code			on_message(sMESSAGE_HTTP_REQUEST& _msg) override;
	virtual result_code			on_message(sMESSAGE_HTTP_WEBSOCKET& _msg) override;

protected:
			object_ptr<server::web::Ientity> m_pweb_entity;
			server::web::sWEB_SERVER_CONTEXT m_webserver_context;

};


}
