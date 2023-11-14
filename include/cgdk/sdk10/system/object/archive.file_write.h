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
// file_log
//
//-----------------------------------------------------------------------------
class archive::file_record : 
	public						object::Ninitializable_startable,
	public						object::Nnameable,
	virtual public				Iarchive,
	virtual public				Iexecutable
{
public:
			file_record();
	virtual ~file_record() noexcept;

public:
			result_code			start() { context _context; return start(_context);}
			result_code			start(const context& _context) { context context_copy(_context); return start(context_copy);}
	virtual	result_code			start(context& _context) override { return object::Nstartable::start(_context);}
			result_code			start(const std::string_view _filename, bool _is_create_new = false);

	[[nodiscard]] virtual uint32_t get_status() const override { return CGARCHIVE_STATUS_LOADING; }
	virtual	uint32_t			set_status(uint32_t _status) override { if(_status != CGARCHIVE_STATUS_LOADING) { CGASSERT_ERROR(false); throw throwable::failure(eRESULT::INVALID_ARGUMENT); } return CGARCHIVE_STATUS_LOADING; }

			bool 				set_filename(const std::string_view _name);

private:
	virtual	void				on_initializing	(context& /*_context*/) override {}
	virtual	void				on_initialize (context& /*_context*/) override {}
	virtual	void				on_destroying () override {}
	virtual	void				on_destroy () override {}
	virtual	void				on_starting (context& /*_context*/) override {}
	virtual	void				on_start (context& /*_context*/) override {}
	virtual	void				on_stopping () override {}
	virtual	void				on_stop () override {}

	virtual void				on_read_complete(const shared_buffer& /*_buffer*/) {}
	virtual void				on_write_complete(const shared_buffer& /*_buffer*/) {}

protected:
	virtual result_code			_process_initializing(context& _context) override;
	virtual result_code			_process_initialize(context& _context) override;
	virtual result_code			_process_destroying() noexcept override;
	virtual result_code			_process_destroy() noexcept override;

	virtual result_code			_process_starting(context& _context) override;
	virtual result_code			_process_start(context& _context) override;
	virtual result_code			_process_stopping() noexcept override;
	virtual result_code			_process_stop() noexcept override;

	virtual bool				process_read(shared_buffer& /*_buffer*/) override { CGASSERT_ERROR(false); return false;}
	virtual bool				process_write(shared_buffer& _buffer) override;

protected:
			lockable<>			m_lockable_buffer;
			shared_buffer		m_buffer_writing;
			int					m_writing_count;
			circular_list<shared_buffer> m_queue_buffer;

			static_string<512>	m_file_name;
	#if defined (_WIN32)
			FILE_HANDLE			m_handle_file;
	#elif defined(__linux__)
			int					m_handle_file;
			aiocb				m_aio_control_block;
	#else
			#error "[CGDK10] Not supported UWP platform"
	#endif

protected:
	virtual	intptr_t			process_execute(intptr_t _result, size_t _param) override;

#if defined(_WIN32)
	static	void				_close_file(FILE_HANDLE& _file_handle) noexcept;
#elif defined(__linux__)
	static	void				_close_file(int& _file_handle) noexcept;
	static	void				_process_signal_handler(int _signal, siginfo_t *_signal_info, void *_context);
#else
	#error "[CGDK10] Not supported UWP platform"
#endif
};


}