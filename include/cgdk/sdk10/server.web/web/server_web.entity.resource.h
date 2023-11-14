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
// CGDK::server::web::entity::resource_file
//
//
// ----------------------------------------------------------------------------
class server::web::entity::resource :
// inherited classes) 
	virtual public				server::web::entity::Iresource,
	public						object::Ninitializable_startable,
	public						object::Nnameable
{
// constructor/destructor)
public:
			resource() noexcept;
			resource(const std::string_view _source, server::web::eENTITY_TYPE _entity_type, chrono::time::utc::time_point _time_last_modified, chrono::time::duration _duration_expires);
	virtual ~resource() noexcept;
	
// public)
public:
			result_code			initialize(const std::string_view _source, server::web::eENTITY_TYPE _entity_type, chrono::time::utc::time_point _time_last_modified, chrono::time::duration _duration_expires);
			result_code			initialize() { context _context; return initialize(_context); }
	virtual	result_code			initialize(context& _context) override { return object::Ninitializable::initialize(_context);}

// frameworks)
protected:
	// 1) initialize/destry/start/stop
	virtual	void				on_initializing(context& _context) override;
	virtual	void				on_initialize(context& _context) override;
	virtual	void				on_destroying() override;
	virtual	void				on_destroy() override;
	virtual	void				on_starting(context& _context) override;
	virtual	void				on_start(context& _context) override;
	virtual	void				on_stopping() override;
	virtual	void				on_stop() override;

	// 2) updateable
	virtual	result_code			process_update(context& _context) override;

	// 3) request
	virtual	int					process_request(sMESSAGE_HTTP_REQUEST& _msg, std::vector<std::string>& _path, const sWEB_SERVER_CONTEXT& _webserver_parameters);
	virtual	int					process_request_file(sMESSAGE_HTTP_REQUEST& _msg, std::vector<std::string>& _path, const sWEB_SERVER_CONTEXT& _webserver_parameters);
	virtual	int					process_request_image(sMESSAGE_HTTP_REQUEST& _msg, std::vector<std::string>& _path, const sWEB_SERVER_CONTEXT& _webserver_parameters);
	virtual	int					process_request_audio(sMESSAGE_HTTP_REQUEST& _msg, std::vector<std::string>& _path, const sWEB_SERVER_CONTEXT& _webserver_parameters);
	virtual	int					process_request_viedo(sMESSAGE_HTTP_REQUEST& _msg, std::vector<std::string>& _path, const sWEB_SERVER_CONTEXT& _webserver_parameters);

	// 4) ...
			void				initialize_file(context& _context);
			void				initialize_image(context& _context);
			void				initialize_audio(context& _context);
			void				initialize_video(context& _context);

// implementation)
protected:
			shared_buffer		m_buffer_data;
			chrono::time::duration		m_duration_expires;
			chrono::time::utc::time_point m_time_last_modified;
};


}