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
//
// logger_hub
//
// 1. logger_hub은~
//    하나의 Log로 여러 곳에 Log를 남기기 위한 Log용 Hub 객체라고 할수 있다.
//    다양한 형태와 종류의 Log객체를 logger_hub 객체에 register_messageable()
//    함수로 등록해 놓으면 logger_hub 객체에 Log가 전달되었을 시 모든 등록된
//    Log 객체들에게 메시지를 전파한다.
//
// 2. Log의 내용
//		0) Date/Time	Log가 남은 시간이다.(자동기록)
//		1) type			Log의 종류이다. Errror, Progress, Warning, Info, ...
//	    2) Level		Log의 중요도이다.
//		3) Message		남길 Log Message를 의미한다.
//
//-----------------------------------------------------------------------------
class logger_hub : 
	public						Nlogger,
	public						object::Iattachable<Ilogger>
{
public:
			struct INITIALIZE_PARAMETER
			{
			};

			logger_hub() noexcept;
			logger_hub(const std::string_view _name);
	virtual ~logger_hub() noexcept;

			result_code			initialize() { return object::Ninitializable::initialize(); }
	virtual	result_code			initialize(context& _context) override	{ return object::Ninitializable::initialize(_context); }
			result_code			initialize(const INITIALIZE_PARAMETER& _parameter) { return initialize(_parameter); }

			bool				register_log_targetable(const object_ptr<Ilogger>& _plogger) { return this->register_log_targetable(object_ptr<Ilogger>(_plogger)); }
			bool				register_log_targetable(object_ptr<Ilogger>&& _plogger);
			bool				unregister_log_targetable(Ilogger* _plogger) noexcept;
			int					reset_log_taretable() noexcept;
			int					clear() noexcept;

protected:
	virtual	void				process_log(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) override;

	virtual bool				process_attach(object_ptr<Ilogger>&& _pchild) override;
	virtual bool				process_detach(Ilogger* _pchild) noexcept override;

	virtual result_code			_process_initializing(context& _context) override;
	virtual result_code			_process_destroy() noexcept override;

			bool				_process_attach(object_ptr<Ilogger>&& _pchild);
			bool				_process_detach(Ilogger* _pchild) noexcept;
			int					_process_detach_all() noexcept;

			std::mutex			m_lockable_log;
			std::vector<object_ptr<Ilogger>> m_container;
};


}