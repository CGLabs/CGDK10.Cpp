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

namespace CGDK
{
//-----------------------------------------------------------------------------
/**

@class		logger_slack
@brief		Slack에 Log를 전달하기 위한 Log객체
@todo
@ref
@details	\n
Slack과 연결하여 Log 내용을 Slack에 남긴다.

*/
//-----------------------------------------------------------------------------
#define INFO_SIZE	4

class logger_slack : public Nlogger
{
public:
			struct INITIALIZE_PARAMETER
			{
				std::string_view token;
				std::string_view channel;
				std::string_view address;
			};

			logger_slack();
			logger_slack(const std::string_view _name);
	virtual ~logger_slack() noexcept;

			result_code			initialize(const INITIALIZE_PARAMETER& _initialize_param);
			result_code			initialize(const std::string_view _token, const std::string_view _channel, const std::string_view _address = std::string_view());

protected:
	virtual	void				process_log(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) override;

	virtual result_code			_process_initializing(context& _context) override;
	virtual result_code			_process_destroying() noexcept override;

			std::string			m_str_address;
			std::string			m_str_token;
			std::string			m_str_channel;
};


}