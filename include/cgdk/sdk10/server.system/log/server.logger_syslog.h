//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            Server Log Classes                             *
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

#if defined(__linux__)

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// logger_syslog
//
//-----------------------------------------------------------------------------
class logger_syslog : 
	public						Nlogger
{
public:
			struct INITIALIZE_PARAMETER
			{
			};

public:
			logger_syslog();
			logger_syslog(const std::string_view _name);
	virtual ~logger_syslog();

public:
			result_code			initialize() { return this->object::Ninitializable::initialize(); }
			result_code			initialize(const INITIALIZE_PARAMETER&) { return this->initialize(); }
			result_code			initialize(const context& _context) { context context_copy(_context); return this->object::Ninitializable::initialize(context_copy); }
	virtual	result_code			initialize(context& _context) override { return this->object::Ninitializable::initialize(_context); }

	virtual	void				process_log(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) override;

protected:
	virtual	result_code			_process_initializing(context& _context) override;
	virtual	result_code			_process_destroying() noexcept;

protected:
			int					m_priority = 0;
};

}

#endif