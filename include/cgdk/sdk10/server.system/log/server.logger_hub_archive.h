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
// logger_hub_archive
//
// 1. logger_hub_archive은~
//    남겨진 Log를 사용후 제거하지 않고 저장해 놓는 LogHub 객체다.
//    저장된 Log 객체는 'get_stored_log()'함수를 사용해 얻어 올 수 있다.
//
//    남겨진 log는 일련번호가 부여되며 일련번호는 영구적이다.
//    최대 저장 log를 넘어설 경우 제일 처음 log를 덥어쓰게 된다.
//    'get_stored_log()'함수로 log 객체를 얻을 경우 _position파라메터에 일련번호를
//    넣어야 한다.
//
//-----------------------------------------------------------------------------
class logger_hub_archive : 
	public						logger_hub,
	public						log_archive,
	virtual public				Iexecutable
{
public:
			struct INITIALIZE_PARAMETER
			{
			};

public:
			logger_hub_archive();
			logger_hub_archive(const std::string_view _name);
	virtual ~logger_hub_archive() noexcept;

public:
			result_code			initialize() { return this->object::Ninitializable::initialize(); }
	virtual	result_code			initialize(context& _context) override { return this->object::Ninitializable::initialize(_context); }
			result_code			initialize(const INITIALIZE_PARAMETER& ) { return this->initialize(); }

protected:
	virtual	void				process_log(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) override;

			void				_process_wait_complete();
	virtual result_code			_process_initializing(context& _context) override;
	virtual result_code			_process_destroying() noexcept override;
	virtual result_code			_process_destroy() noexcept override;
	virtual	intptr_t			process_execute(intptr_t _return, size_t _param) override;

			std::vector<object_ptr<LOG_RECORD>> m_array_log_queue;
			std::vector<object_ptr<LOG_RECORD>> m_array_log_process;
			bool				m_is_processing;

			object_ptr<Iexecutor> m_pexecutor;
};


}