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
// 1. logger_hub��~
//    �ϳ��� Log�� ���� ���� Log�� ����� ���� Log�� Hub ��ü��� �Ҽ� �ִ�.
//    �پ��� ���¿� ������ Log��ü�� logger_hub ��ü�� register_messageable()
//    �Լ��� ����� ������ logger_hub ��ü�� Log�� ���޵Ǿ��� �� ��� ��ϵ�
//    Log ��ü�鿡�� �޽����� �����Ѵ�.
//
// 2. Log�� ����
//		0) Date/Time	Log�� ���� �ð��̴�.(�ڵ����)
//		1) type			Log�� �����̴�. Errror, Progress, Warning, Info, ...
//	    2) Level		Log�� �߿䵵�̴�.
//		3) Message		���� Log Message�� �ǹ��Ѵ�.
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