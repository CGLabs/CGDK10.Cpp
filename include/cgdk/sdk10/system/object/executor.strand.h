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

 @class		executable::strand
 

*///-----------------------------------------------------------------------------
class executor::strand :
	virtual public				Iexecutor,
	virtual public				Iexecutable,
	public						object::Ninitializable_startable,
	public						object::Nnameable

{
public:
			strand() noexcept;
	virtual ~strand() noexcept;

public:
			bool				post_at(const object_ptr<Iexecutable>& _pexecutable, chrono::tick::time_point _tick_execute) { return this->process_post_at(object_ptr<Iexecutable>(_pexecutable), _tick_execute); }
			bool				post_at(object_ptr<Iexecutable>&& _pexecutable, chrono::tick::time_point _tick_execute) { return this->process_post_at(std::move(_pexecutable), _tick_execute); }

	[[nodiscard]] auto			executor() const noexcept { scoped_lock(this->m_cs_pexecutor) { return this->m_pexecutor; } }
			void				executor(const object_ptr<Iexecutor>& _pexecutor) noexcept { this->executor(object_ptr<Iexecutor>(_pexecutor)); }
			void				executor(object_ptr<Iexecutor>&& _pexecutor) noexcept { scoped_lock(this->m_cs_pexecutor) { this->m_pexecutor = std::move(_pexecutor); } }
	[[nodiscard]] bool			has_executor() const noexcept { scoped_lock(this->m_cs_pexecutor) { return this->m_pexecutor.exist(); } }

protected:
			struct EXECUTABLE
			{
				object_ptr<Iexecutable> pexecutable;
				intptr_t result = 0;
				size_t param = 0;
			};
			struct EXECUTABLE_AT
			{
				EXECUTABLE executable;
				chrono::tick::time_point tick;
			};
			class executor_post_at;

			lockable<>			m_cs_pexecutor;
			object_ptr<Iexecutor> m_pexecutor;

			lockable<>			m_cs_queue_executable;
			std::vector<EXECUTABLE> m_queue_executable;
			std::list<EXECUTABLE_AT> m_queue_executable_at;
			bool				m_is_processing = false;

	virtual result_code			_process_initialize(context& _context);
	virtual result_code			_process_destroying() noexcept;

	virtual	bool				process_post(object_ptr<Iexecutable>&& _pexecutable) override;
	virtual	bool				process_post_at(object_ptr<Iexecutable>&& _pexecutable, chrono::tick::time_point _tick_execute);
	virtual	bool				process_execute(chrono::tick::duration _ticks_wait, intptr_t _option) override;
	virtual	intptr_t			process_execute(intptr_t _result, size_t _param) override;
			void				process_execute_post_at();
			object_ptr<Iexecutor> process_get_executor();
			void				process_post_next();
};


}