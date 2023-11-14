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

 @class		queue_executable
 @brief		queue of executable 
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
class api::queue_executable :
	virtual public				Ireferenceable
{
// constructor/destructor)
public:
			queue_executable();
	virtual	~queue_executable() noexcept;

// public)
public:
	class RESULT
	{
	public:
		uintptr_t				completion_key {};
		Iexecutable*			pexecutable = nullptr;
		intptr_t				result_{};
		uint32_t				bytes_transfered{};
	public:
		[[nodiscard]] bool			is_valid() const noexcept { return pexecutable != nullptr;}
		[[nodiscard]] intptr_t		result() const noexcept { return result_; }
		[[nodiscard]] Iexecutable*	executable() const noexcept { return static_cast<Iexecutable*>(pexecutable);}
		[[nodiscard]] size_t		param() const noexcept { return static_cast<size_t>(bytes_transfered); }
	};

public:
			bool				post_executable(uint32_t _bytes_transferred, uintptr_t _completion_key, Iexecutable* _pexecutable) noexcept;
			bool				post_executable(uint32_t _bytes_transferred, uintptr_t _completion_key, object_ptr<Iexecutable>&& _executable) noexcept;

			uint32_t			pop_queued_executable(RESULT& _result, chrono::tick::duration _ticks_wait) noexcept;
			int					pop_queued_executable(RESULT* _presult_event, int _max_event, chrono::tick::duration _ticks_wait) noexcept;

// implementation)
private:
			CGDK::circular_list<RESULT>	m_queue_executable;
			std::mutex				m_lock_complete;
			std::condition_variable	m_cv_complete;
};

}
