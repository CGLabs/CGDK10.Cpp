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

   executor::io_context_threads
 

*///-----------------------------------------------------------------------------
class executor::io_context_threads :
	public						executor::io_context,
	public						api::threads,
	virtual public				object::Inameable,
	virtual public				Iexecutor
{
public:
			struct START_PARAMETER
			{
				size_t			thread_count;
			};

public:
			io_context_threads();
			io_context_threads(std::string_view _name);
	virtual ~io_context_threads() noexcept;

public:
			result_code			start() { context _context; return start(_context); }
			result_code			start(const START_PARAMETER& _parameter) { context temp(buffer_view((char*)&_parameter, sizeof(START_PARAMETER))); return start(temp); }
			result_code			start(const context& _context) { context context_copy(_context); return start(context_copy); }
	virtual	result_code			start(context& _context) override;
	virtual	result_code			stop() noexcept override;

public:
			uint32_t			process_thread_run();
	virtual	bool				process_control(uint64_t _command, uint64_t _param) noexcept override;
			bool				process_control_block() noexcept;
			bool				process_control_unblock() noexcept;
	virtual	void				process_begin_thread_object(api::thread* _pthread) noexcept override;
	virtual	void				process_end_thread_object(api::thread* _pthread) noexcept override;

protected:
	static	uint32_t			fn_thread(io_context_threads* _this);

			bool				m_is_active {false};
			bool				m_enable_auto_exepand {false};
			std::atomic<size_t>	m_count_thread_active {0};
			size_t				m_count_thread_needed {0};
			size_t				m_count_thread_wait {0};
			size_t				m_count_thread_max {0};
			std::atomic<int>	m_thread_index{ 0 };
};


}