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

api::io_context_iocp_queued

 독립적인 thread pool을 사용하며 iocp는 단지 i/o의 completion정보를 얻는
 용도로만 쓰인다.
 독자적인 thread에서 주기적으로 iocp로 부터 i/o completion 정보를 뽑아내 
 메인 thread pool에 던저 주면 메인 thread에서 해당 i/o처리를 하는 구조이다.
 자체적인 thread pool을 사용함으로써 얻어지는 성능상의 이점은 있지만
 iocp로 부터 처리되는 i/o completion 정보는 약간의 지연시간이 더 추가될수 있다.
 
*///-----------------------------------------------------------------------------
class api::io_context_iocp_queued : public io_context_Niocp
{
// constructor/destructor)
public:
			io_context_iocp_queued() noexcept;
	virtual	~io_context_iocp_queued() noexcept;

public:
			bool				create() noexcept;
	virtual	CGHANDLE			dispose() noexcept override;
	virtual	result_code			destroy() noexcept override;
			bool				post_executable(uint32_t _bytes_transferred, uintptr_t _completion_key, object_ptr<Iexecutable>&& _pexecutable) noexcept;
			bool				post_executable(uint32_t _bytes_transferred, uintptr_t _completion_key, Iexecutable* _pexecutable) noexcept;
			void				pop_executable(RESULT& _result, chrono::tick::duration _ticks_wait) noexcept;
			[[nodiscard]] size_t queued_count() const noexcept { scoped_lock(m_lock_complete) { return m_queue_executable.size(); } }

// implementation)
private:
			void				_process_popup_iocp_event();
	static	void				_fn_process_popup_iocp_event(api::io_context_iocp_queued* _pobject);

			using CONTAINER_EXECUTABLE_QUEUE = CGDK::circular_list<RESULT>;
			CONTAINER_EXECUTABLE_QUEUE	m_queue_executable;
			int						m_count_wait;
			std::mutex				m_lock_complete;
			std::condition_variable	m_cv_complete;
			std::vector<object_ptr<api::threads>> m_vector_thread;
};


}
#endif
