//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              CG3D D3D Classes                             *
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

#ifdef _WIN32

namespace CGDK
{
//-----------------------------------------------------------------------------
/**

 @class		executable_batch
 @brief		비동기적 Update를 처리하기 위한 클래스이다.
 @todo		
 @ref		
 @details	\n
 Update처리를 executor에 전달해 실행하기 위한 클래스이다.
 일반적으로 Update처리를 비동기 처리해야할 때 사용된다.

*///-----------------------------------------------------------------------------
class updatable::executable_batch :
// Inherited Classes) 
	virtual public				object::Iupdatable,
	virtual public				Iexecutable
{
// constructor/destructor)
public:
			executable_batch(size_t _count_thread = CGEXECUTOR_AUTO) noexcept;
	virtual	~executable_batch() noexcept;

// public) 
public:
	// 2) Queue
	//! @brief '업데이트블 객체'를 큐잉한다. @param _pupdatable 업데이트할 '업데이트 객체'
			void				queue_updatable(object::Iupdatable* _pupdatable);

// implementation) 
public:
	virtual	result_code			process_update(context& _context) override;

protected:
	// 1) 생성/파괴
			bool				process_initialize(size_t _count_thread);
	virtual	bool				process_destroy() noexcept;

	// 2) Rendering Context
			context				m_context;

	// 3) Executable List
			lockable<circular_list<object_ptr<object::Iupdatable>>> m_list_updatable;
			
	// 4) Thread...
			size_t				m_max_thread_count;
			std::atomic<size_t>	m_count;

	// 5) Conditional_variable
			std::unique_lock<std::mutex>	m_lock;
			std::condition_variable			m_cv_complete;

	// 6) 실행을 처리한다.
	virtual intptr_t			process_execute(intptr_t _return, std::size_t _param) override;
};


}

#endif