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
// service_ex
//
// 
// ----------------------------------------------------------------------------
class server_system::service_ex :
	public						service
{
public:
			service_ex(const std::string_view _name, const std::string_view _filename_log, const std::string_view _filename_configure);
	virtual ~service_ex();

protected:
	virtual	void				on_server_certified(const shared_buffer& _buffer) override;

	virtual	void				_process_initializing_pre(context& _context);
	virtual	void				_process_destroy_post() noexcept;

			own_ptr<logger_file> m_plogger_file;
};


}