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
// CGDK::server::web::entity::folder
//
//
// ----------------------------------------------------------------------------
class server::web::entity::folder :
	virtual public				server::web::entity::Inode,
	public						object::Ninitializable_startable,
	public						object::Nnameable
{
public:
			folder() noexcept;
			folder(const std::string_view _source, bool _flag_recursive = true);
	virtual ~folder() noexcept;

// public)
public:
			result_code			initialize(const std::string_view _source, bool _flag_recursive = true);
			result_code			initialize() { context _context; return initialize(_context); }
	virtual	result_code			initialize(context& _context) override { return object::Ninitializable::initialize(_context);}

// frameworks)
protected:
	virtual	void				on_initializing	(context& _context) override;
	virtual	void				on_initialize (context& _context) override;
	virtual	void				on_destroying () override;
	virtual	void				on_destroy () override;
	virtual	void				on_starting (context& _context) override;
	virtual	void				on_start (context& _context) override;
	virtual	void				on_stopping () override;
	virtual	void				on_stop () override;

	virtual	result_code			process_update (context& _context) override;
	virtual	int					process_request (sMESSAGE_HTTP_REQUEST& _msg, std::vector<std::string>& _path, const sWEB_SERVER_CONTEXT& _webserver_parameters);

// implementation)
protected:
			object_ptr<Ientity>	m_pentity_entry;
			std::string			m_str_entry;
			std::string			m_source;
			std::string			m_server;
};


}
