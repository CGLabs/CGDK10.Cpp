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

 �������� thread pool�� ����ϸ� iocp�� ���� i/o�� completion������ ���
 �뵵�θ� ���δ�.
 �������� thread���� �ֱ������� iocp�� ���� i/o completion ������ �̾Ƴ� 
 ���� thread pool�� ���� �ָ� ���� thread���� �ش� i/oó���� �ϴ� �����̴�.
 ��ü���� thread pool�� ��������ν� ������� ���ɻ��� ������ ������
 iocp�� ���� ó���Ǵ� i/o completion ������ �ణ�� �����ð��� �� �߰��ɼ� �ִ�.
 
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
