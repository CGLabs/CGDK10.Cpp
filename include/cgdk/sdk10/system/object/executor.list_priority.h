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

 @class		list_priority
 @brief		ť�׵� Executable���� �켱����ť �˰����� ����� ���ʷ� �����Ѵ�.
 @todo		
 @ref		
 @details	\n
ť�׵� Iexecutable ��ü �� ���ǵ� ����ð��� ���� �͵鸸 �������ش�.
 �켱���� ť(Priority queue)�� ����� �Ź� ��� ��ϵ� ��ü�� ��ȸ���� �ʰ� ���� ����Ǿ�� �ϴ� ��ü�� ������ �ش�.

*///-----------------------------------------------------------------------------
//class executor::list_priority :
//	virtual public				Iexecutor
//{
//public:
//			list_priority(Iexecutor* _pexecutor = nullptr) noexcept;
//			list_priority(object_ptr<Iexecutor>&& _executor) noexcept;
//	virtual ~list_priority() noexcept;
//
//public:
//	virtual	result_code			start(context& _context) override;
//	virtual	result_code			stop() noexcept override;
//
//			bool				register_executable(Iexecutable* _pexecutable);
//			bool				register_executable(object_ptr<Iexecutable>&& _pexecutable);
//			bool				unregister_executable(Iexecutable* _pexecutable) noexcept;
//			void				unregister_executor_all() noexcept;
//
//	[[nodiscard]] size_t		count() const noexcept;
//	[[nodiscard]] bool			empty() const noexcept { return this->count() == 0;}
//	[[nodiscard]] bool			exist() const noexcept { return this->count() != 0;}
//			
//	[[nodiscard]] object_ptr<Iexecutor> executor() const noexcept { return this->m_psystem_executor;}
//			void				executor(Iexecutor* _pexecutor) noexcept { this->m_psystem_executor=_pexecutor;}
//			template<class TEXECUTOR>
//			void				executor(object_ptr<TEXECUTOR>&& _pexecutor) noexcept { this->m_psystem_executor = std::move(_pexecutor);}
//			void				reset_executor() noexcept { this->m_psystem_executor.reset();}
//
//private:
//			lockable<std::vector<object_ptr<Iexecutable>>> m_priorityqueue_executable;
//			object_ptr<Iexecutor> m_psystem_executor;
//
//	virtual	bool				process_post(object_ptr<Iexecutable>&& _pexecutable) override;
//	virtual	bool				process_execute(chrono::tick::duration _ticks_wait, intptr_t _option) override;
//
//			void				heap_down_executable() noexcept;
//
//};


}