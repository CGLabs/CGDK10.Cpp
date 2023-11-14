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

   executor::io_context

*/
//-----------------------------------------------------------------------------
class executor::io_context :
	virtual public				executor::Iio_context,
	public						object::Ninitializable_startable,
	public						Nexecutor,
	public						factory::_traits_system
{
public:
			io_context() noexcept;
			io_context(std::string_view _name);
	virtual	~io_context() noexcept;

public:
#if defined(__ANDROID__) || defined(__linux__)
	virtual	bool				attach(CGHANDLE _executable_handle, Iexecutable* _pexecutable, uint32_t _option = 0) override { return this->m_io_context.attach(_executable_handle, _pexecutable, _option);}
#else
	virtual	bool				attach(CGHANDLE _executable_handle) override { return this->m_io_context.attach(_executable_handle);}
#endif
	virtual	bool				detach(CGHANDLE _executable_handle) noexcept override { return this->m_io_context.detach(_executable_handle);}
	[[nodiscard]] virtual CGHANDLE handle() const noexcept override { return this->m_io_context.handle();}
	[[nodiscard]] virtual size_t pended_count() const noexcept override { return this->m_io_context.queued_count(); }

#if defined(__ANDROID__) || defined(__linux__)
	virtual	bool				set_event(CGHANDLE _handle, uint32_t _flag_event, Iexecutable* _pexecutable = nullptr) noexcept override { return this->m_io_context.modify(_handle, _flag_event, _pexecutable); }
#endif
	virtual	void				execute_all() noexcept;

protected:
	virtual result_code			_process_initializing(context& _context) override;
	virtual result_code			_process_initialize(context& _context) override;
	virtual result_code			_process_destroying() noexcept override;
	virtual result_code			_process_destroy() noexcept override;

	virtual result_code			_process_starting(context& _context) override;
	virtual result_code			_process_start(context& _context) override;
	virtual result_code			_process_stopping() noexcept override;
	virtual result_code			_process_stop() noexcept override;

	virtual	bool				process_post(object_ptr<Iexecutable>&& _pexecutable) override;
	virtual	bool				process_execute(chrono::tick::duration _ticks_wait, intptr_t _option) override;

protected:
			OBJ<api::io_context> m_io_context;
			lockable<>			m_lock_wait;
};


}