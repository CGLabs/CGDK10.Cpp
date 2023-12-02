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

#if defined(_IO_APISET_H_)

namespace CGDK
{
//-----------------------------------------------------------------------------
/**

 @class		api::io_context_rio


*///-----------------------------------------------------------------------------
class api::io_context_rio :
	virtual public				object::Idestroyable
{
// constructor/destructor)
public:
			io_context_rio() noexcept;
	virtual	~io_context_rio() noexcept;

// public)
public:
	struct RESULT
	{
	public:
		uintptr_t				per_handle_key {};
		EXECUTABLE_NODE*		pexecutable {nullptr};
		intptr_t				result {};
		uint32_t				bytes_transfered {};

	public:
	[[nodiscard]]bool			is_valid() const noexcept { return pexecutable != nullptr;}
	[[nodiscard]] intptr_t		result() const noexcept { return result; }
	[[nodiscard]] Iexecutable*	executable() const noexcept { return static_cast<Iexecutable*>(pexecutable);}
	[[nodiscard]] size_t		param() const noexcept { return static_cast<size_t>(bytes_transfered); }
	};

public:
	[[nodiscard]]size_t			attached_count() const noexcept { return m_count_attached;}
	[[nodiscard]] CGHANDLE		handle() const noexcept	{ return m_handle_iocp;}

			bool				create() noexcept;
	virtual	result_code			destroy() noexcept override;

			bool				cancel_io() noexcept;
			bool				cancel_io(CGHANDLE _handle) noexcept;

			bool				attach(CGHANDLE _handle) noexcept;
			bool				detach(CGHANDLE _handle) noexcept;

			bool				post_executable(uint32_t _bytes_transferred, uintptr_t _completion_key, Iexecutable* _pexecutable) noexcept;
			bool				post_executable(uint32_t _bytes_transferred, uintptr_t _completion_key, object_ptr<Iexecutable>&& _executable) noexcept;

			void				pop_queued_executable(RESULT& _result, chrono::tick::duration _ticks_wait) noexcept;
	[[nodiscard]] size_t		queued_count() const noexcept { scoped_lock(m_lock_complete) { return m_queue_executable.size(); } }

// implementation)
private:
			std::atomic<CGHANDLE>	m_handle_iocp;
			std::atomic<size_t>		m_count_attached;

			void				_process_popup_iocp_event();
	static	void				_fn_process_popup_iocp_event(api::io_context_rio* _pobject);

			using CONTAINER_EXECUTABLE_QUEUE = CGDK::circular_list<RESULT>;

			CONTAINER_EXECUTABLE_QUEUE	m_queue_executable;
			int						m_count_wait;
			std::mutex				m_lock_complete;
			std::condition_variable	m_cv_complete;
			object_ptr<api::threads> m_pthread;
};


}
#endif
