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

 @class		executor::queue_list
 @brief		IOCP를 사용한 쓰레드풀을 구성한 executor이다.
 @todo		
 @ref		
 @details	\n
 @remark	\n
 IOCP에 Socket을 붙이거나 IO를 Post하는 용도로 주로 사용된다.
 이 IOCP Completion Port는 상속을 하여 Thread용으로 사용되기도 하지만 주로 .
 Client IOCP에 많이 사용된다. MainLoop와 동일한 Thread에서 사용하기 위해
 Execut()함수를 TimeOut을 0으로 절어줘서 사용한다.

*///-----------------------------------------------------------------------------
class executor::queue_list :
	virtual public				executor::Iqueue,
	public						Nexecutor
{
public:
			queue_list() noexcept;
			queue_list(std::string_view _name);
	virtual	~queue_list() noexcept;

public:
			struct START_PARAMETER
			{
			};

public:
			result_code			start() { context _context; return this->start(_context);}
			result_code			start(const START_PARAMETER& _parameter) { context temp(buffer_view((char*)&_parameter, sizeof(START_PARAMETER)));  return this->start(temp); }
	virtual result_code			start(context& _context) override;
	virtual	result_code			stop() noexcept override;
	virtual	void				execute_all() noexcept;

	[[nodiscard]] virtual size_t pended_count() const noexcept override { scoped_lock(this->m_lock_complete) { return this->m_queue_executable.size(); } }

protected:
	virtual	bool				process_post(object_ptr<Iexecutable>&& _pexecutable) override;
	virtual	bool				process_execute(chrono::tick::duration _ticks_wait, intptr_t _option) override;

protected:
		using CONTAINER_EXECUTABLE_QUEUE = circular_list<object_ptr<Iexecutable>>;

			lockable<CONTAINER_EXECUTABLE_QUEUE> m_queue_executable;

			std::mutex			m_lock_complete;
			std::condition_variable m_cv_complete;

			object_ptr<Iexecutable> pop_queued_executable() noexcept;
};


}