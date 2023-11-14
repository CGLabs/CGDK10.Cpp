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
 @brief		�񵿱��� Update�� ó���ϱ� ���� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 Updateó���� executor�� ������ �����ϱ� ���� Ŭ�����̴�.
 �Ϲ������� Updateó���� �񵿱� ó���ؾ��� �� ���ȴ�.

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
	//! @brief '������Ʈ�� ��ü'�� ť���Ѵ�. @param _pupdatable ������Ʈ�� '������Ʈ ��ü'
			void				queue_updatable(object::Iupdatable* _pupdatable);

// implementation) 
public:
	virtual	result_code			process_update(context& _context) override;

protected:
	// 1) ����/�ı�
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

	// 6) ������ ó���Ѵ�.
	virtual intptr_t			process_execute(intptr_t _return, std::size_t _param) override;
};


}

#endif