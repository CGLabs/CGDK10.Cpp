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
// CGDK::server::web::entity::text
//
//
// ----------------------------------------------------------------------------
class server::web::entity::text :
// inherited classes) 
	virtual public				server::web::entity::Itext,
	public						object::Ninitializable_startable,
	public						object::Nnameable
{
// constructor/destructor)
public:
			text() noexcept;
			text(const std::string_view _source, server::web::eENTITY_TYPE _entity_type);
	virtual ~text() noexcept;
	
// public)
public:
	// 1) initialize
	virtual	result_code			initialize(const std::string_view _source, server::web::eENTITY_TYPE _entity_type);
			result_code			initialize() { context _context; return initialize(_context); }
	virtual	result_code			initialize(context& _context) override { return object::Ninitializable::initialize(_context);}

	// 2) ...
	virtual	int					get_encode_type() const noexcept;
	virtual	void				set_encode_type(int _entity_type);

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

	// 4) ...
	virtual	shared_buffer		process_encode(shared_buffer& _buffer);
	virtual	std::size_t			process_build_body(sMESSAGE_HTTP_REQUEST& _msg, std::vector<shared_buffer>& _vector_buffer);

// implementation)
protected:
	// Defintion) 
			struct PARTIAL
			{
			public:
				shared_buffer	buffer_text;
				//object_ptr<ISource>	pParser;
			};

	// 1) Data
			std::vector<PARTIAL> m_vector_data;

	// 2) 
			int					m_encode_type;
};


}