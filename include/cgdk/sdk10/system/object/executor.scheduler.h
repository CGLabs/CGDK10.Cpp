//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
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

 @class		executor::scheduler
 @brief		������ �ð��� 1ȸ�� ����Ǵ� Executable�� ó���ϴ� executor�̴�.
 @todo		
 @ref		
 @details	\n
 ������ �ð��� 1ȸ�� ����ǰ� ����� Executable�� �����Ѵ�.
 ���������δ� �켱����ť(Priority Queue)�� ����ؼ� ��������� ������ �ſ� ���� 
 Executable�� �־ ȿ�������� ó���� �����ϴ�.
 ���� ���� ���� ������ �������� ������ �������� ��� ����� ������ ��� �õ��Ѵ�.
 ���� ������� ���� Executable�� ��� cancel_executable()�Լ��� ������ �� �ִ�.
 �⺻ �ִ� ť�� ���̴� 8192���� �����Ǿ� �ִ�. (�ʿ�� �ڵ� Ȯ��ȴ�.)

 �� ��ü������ Executable�� ���������� �ʰ� �ٸ� executor�� ������ ��û�ϱ⸸ �ϹǷ�
 �ݵ�� ���� ���� executor()�Լ��� �Ͽ��� executor�� �ݵ�� ������ �־�� �Ѵ�.
 ���� executor�� �����Ǿ� ���� ������ �ƹ��� ���۵� ���� �ʴ´�.

*///-----------------------------------------------------------------------------
class executor::scheduler :
	public						CGDK::Nexecutor,
	virtual public				executor::Iqueue,
	public						api::threads,
	public						factory::_traits_system
{
public:
			scheduler() noexcept;
			scheduler(std::string_view _name);
	virtual ~scheduler() noexcept;

			struct START_PARAMETER
			{
				object_ptr<Iexecutor> pexecutor;
			};

public:
			result_code			start() { context _context; return this->start(_context);}
			result_code			start(const START_PARAMETER& _parameter) { context temp(buffer_view((char*)&_parameter, sizeof(START_PARAMETER)));  return this->start(temp); }
			result_code			start(const context& _context) { context context_copy(_context); return this->start(context_copy);}
	virtual	result_code			start(context& _context) override;
	virtual	result_code			stop() noexcept override;

			bool				post_at(const object_ptr<Iexecutable>& _pexecutable, chrono::tick::time_point _tick_execute) { return this->process_post_at(object_ptr<Iexecutable>(_pexecutable), _tick_execute); }
			bool				post_at(object_ptr<Iexecutable>&& _pexecutable, chrono::tick::time_point _tick_execute) { return this->process_post_at(std::move(_pexecutable), _tick_execute); }

			bool				cancel(Iexecutable* _pexecutable) noexcept;
			void				cancel() noexcept;

	[[nodiscard]] virtual size_t pended_count() const noexcept override;
	[[nodiscard]] bool			empty() const noexcept { return this->pended_count() == 0;}
	[[nodiscard]] bool			exist() const noexcept { return !empty();}

	[[nodiscard]] auto			executor() const noexcept { scoped_lock(this->m_cs_pexecutor) { return this->m_pexecutor; } }
			void				executor(const object_ptr<Iexecutor>& _pexecutor) noexcept { this->executor(object_ptr<Iexecutor>(_pexecutor)); }
			void				executor(object_ptr<Iexecutor>&& _pexecutor) noexcept { scoped_lock(this->m_cs_pexecutor) { this->m_pexecutor = std::move(_pexecutor); } }
	[[nodiscard]] bool			has_executor() const noexcept { scoped_lock(this->m_cs_pexecutor) { return this->m_pexecutor.exist(); } }

			void				print_statistics() noexcept;

protected:
			struct EXECUTION_AT;

			lockable<>			m_cs_pexecutor;
			object_ptr<Iexecutor> m_pexecutor;
			std::atomic<int>	m_flag_run;

			std::vector<EXECUTION_AT> m_priorityqueue_executable;
			std::mutex			m_lockable_priorityqueue;
			std::condition_variable	m_cv_priorityqueue_exist;
			std::condition_variable	m_cv_priorityqueue_in_time;

			void				process_push_executable(EXECUTION_AT&& _pexecutable);
			void				process_pop_executable() noexcept;

	virtual	bool				process_post(object_ptr<Iexecutable>&& _pexecutable) override;
	virtual	bool				process_post_at(object_ptr<Iexecutable>&& _pexecutable, chrono::tick::time_point _tick_execute);
	virtual	bool				process_execute(chrono::tick::duration _ticks_wait, intptr_t _option) override;

protected:
	static	uint32_t			fn_thread(scheduler* _this);
};



}