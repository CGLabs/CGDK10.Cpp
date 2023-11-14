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

#if defined(__ANDROID__) || defined(__linux__)

namespace CGDK
{
//-----------------------------------------------------------------------------
/**

 @class		io_context_epoll
 

*///-----------------------------------------------------------------------------
class api::io_context_epoll :
	virtual public				object::Idestroyable
{
// constructor/destructor)
public:
			io_context_epoll();
	virtual	~io_context_epoll() noexcept;

// public)
public:
	class RESULT : public epoll_event
	{
	public:
		RESULT() noexcept { data.ptr = nullptr; }

	public:
		[[nodiscard]] bool		is_valid() const noexcept { return data.ptr != nullptr;}
		[[nodiscard]] intptr_t	result() const noexcept { return events;}
		Iexecutable*			executable() const noexcept { return reinterpret_cast<Iexecutable*>(data.ptr); }
		[[nodiscard]] size_t	param() const noexcept { return 0; }
	};

public:
			size_t				attached_count() const noexcept { return m_count_attached;}
			[[nodiscard]] CGHANDLE handle() const noexcept { return m_handle_epoll;}
			
			bool				create(int _hint_size = 4096) noexcept;
			CGHANDLE			dispose() noexcept;
	virtual	result_code			destroy() noexcept override;

			bool				attach(CGHANDLE _handle, Iexecutable* _pexecutable, uint32_t _event) noexcept;
			bool				detach(CGHANDLE _handle) noexcept;
			bool				modify(CGHANDLE _handle, uint32_t _event, Iexecutable* _pexecutable)  noexcept;

			bool				post_executable(uint32_t _bytes_transferred, uintptr_t _completion_key, Iexecutable* _pexecutable) noexcept;
			bool				post_executable(uint32_t _bytes_transferred, uintptr_t _completion_key, object_ptr<Iexecutable>&& _executable) noexcept;

			void				pop_executable(RESULT& _result_event, chrono::tick::duration _ticks_wait) noexcept;
			[[nodiscard]] size_t queued_count() const noexcept { std::lock_guard<std::mutex> cs(const_cast<std::mutex&>(this->m_lock_complete)); return this->m_queue_executable.size(); }

// implementation)
private:
			std::atomic<CGHANDLE>	m_handle_epoll;
			std::atomic<size_t>		m_count_attached;

	static	const size_t			BUCKET_COUNT = 4096;
	static	const CGHANDLE			BUCKET_MASK = 0x00000fff;

			struct NODE
			{
				CGHANDLE			handle;
				Iexecutable*		pexecutable;
			};

			struct BUCKET_REGISTER
			{
				std::shared_mutex	cs_register;
				std::vector<NODE>	vector_register;
			};

			BUCKET_REGISTER		m_manager_attached[BUCKET_COUNT];
			void				_process_register_handle(CGHANDLE _handle, Iexecutable* _pexecutable);
			void				_process_unregister_handle(CGHANDLE _handle) noexcept;
			void*				_process_get_executable(CGHANDLE _handle) const noexcept;
			bool				_process_update_handle(CGHANDLE _handle, Iexecutable* _pexecutable);
			void				_process_popup_epoll_event();
	static	void				_fn_process_popup_epoll_event(api::io_context_epoll* _pobject);

			using CONTAINER_EXECUTABLE_QUEUE = CGDK::circular_list<RESULT>;

			CONTAINER_EXECUTABLE_QUEUE	m_queue_executable;
			int						m_count_wait;
			std::mutex				m_lock_complete;
			std::condition_variable	m_cv_complete;
			object_ptr<api::threads> m_pthread;
};

}

#endif