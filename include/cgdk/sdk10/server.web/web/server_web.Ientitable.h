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
// CGDK::server::web::Ientity
// 
//
// ----------------------------------------------------------------------------
class server::web::Ientitable :
// inherited classes) 
	virtual public				Ireferenceable
{
public:
			auto				get_web_entity() const noexcept { return m_web_entity; }
			void				set_web_entity(server::web::Ientity* _pweb_entity) noexcept { m_web_entity = _pweb_entity; }
			void				reset_web_entity() noexcept { m_web_entity.reset(); }
			const auto&			get_webserver_context() const noexcept { return m_webserver_context; }
			void				set_webserver_name(std::string_view _server_name) noexcept { m_webserver_context.server_name = _server_name; }
			auto				get_webserver_name() const noexcept { return m_webserver_context.server_name; }
			void				set_webserver_version(uint32_t _version_high, uint32_t _version_low) noexcept { m_webserver_context.server_version_high = _version_high; m_webserver_context.server_version_low = _version_low; }
			auto				get_webserver_high() noexcept { return m_webserver_context.server_version_high; }
			auto				get_webserver_low() noexcept { return m_webserver_context.server_version_low; }

protected:
			object_ptr<server::web::Ientity> m_web_entity;
			server::web::sWEB_SERVER_CONTEXT m_webserver_context;
};


}