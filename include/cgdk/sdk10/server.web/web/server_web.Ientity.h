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
class server::web::Ientity :
// inherited classes) 
	virtual public				object::Istate,
	virtual public				object::Iinitializable,
	virtual public				object::Istartable,
	virtual public				object::Iupdatable,
	virtual public				object::Inameable
{
// public)
public:
	// 1) request
			int					request(sMESSAGE_HTTP_REQUEST& _msg, const sWEB_SERVER_CONTEXT& _webserver_context) { std::vector<std::string> path_now; return process_request(_msg, path_now, _webserver_context); }
			auto				get_path() const noexcept { return m_path_source.string(); }
			auto				get_parent_entity() const noexcept { return m_pentity_parent;}
			auto				get_entity_type() const noexcept { return m_entity_type; }

			const auto&			get_entity_name() const noexcept { return m_entity_name; }
			void				set_entity_name(std::string_view _entity_name) { m_entity_name = _entity_name; }
			void				set_entity_name(std::string&& _entity_name) noexcept { m_entity_name = std::move(_entity_name); }

// framework)
public:
	virtual	int					process_request(sMESSAGE_HTTP_REQUEST& _msg, std::vector<std::string>& _path, const sWEB_SERVER_CONTEXT& _webserver_parameters) PURE;

public:
	// 3) path
			eENTITY_TYPE		m_entity_type = eENTITY_TYPE::NONE;
			std::string			m_entity_name;
			std::filesystem::path m_path_source;

	// 4) parent entity
			object_ptr<Ientity>	m_pentity_parent;
			std::map<std::string, object_ptr<Ientity>>::iterator m_iter_parent;
	static	shared_buffer		m_buffer_context_tail;
	static	void				init_context();
};


}