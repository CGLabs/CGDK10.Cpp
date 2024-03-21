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
// 1. logger_hub_archive��~
//    ������ Log�� ����� �������� �ʰ� ������ ���� LogHub ��ü��.
//    ����� Log ��ü�� 'get_stored_log()'�Լ��� ����� ��� �� �� �ִ�.
//
//    ������ log�� �Ϸù�ȣ�� �ο��Ǹ� �Ϸù�ȣ�� �������̴�.
//    �ִ� ���� log�� �Ѿ ��� ���� ó�� log�� ����� �ȴ�.
//    'get_stored_log()'�Լ��� log ��ü�� ���� ��� _position�Ķ���Ϳ� �Ϸù�ȣ��
//    �־�� �Ѵ�.
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