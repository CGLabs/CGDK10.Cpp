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
//
//namespace CGDK
//{
////-----------------------------------------------------------------------------
///**
//
//   executor::list<TEXECUTOR>
//
//
//*///-----------------------------------------------------------------------------
//template <class TEXECUTOR>
//class executor::list :
//	public						Nexecutor,
//	public						object::Nstartable,
//	virtual public				Iattachable<TEXECUTOR>
//{
//public:
//			list();
//			list(std::string_view _name);
//	virtual ~list() noexcept;
//
//public:
//			using CONTAINER = static_vector<object_ptr<TEXECUTOR>, 64>;
//			class ITERATOR;
//
//			bool				register_executor(TEXECUTOR* _pexecutor) { return this->process_attach(_pexecutor);}
//			bool				unregister_executor(TEXECUTOR* _pexecutor) noexcept	{ return this->process_detach(_pexecutor);}
//			int					unregister_executor_all() noexcept;
//	[[nodiscard]] ITERATOR		get_iterator() noexcept;
//	[[nodiscard]] size_t		count() const noexcept;
//	[[nodiscard]] bool			empty() const noexcept;
//	[[nodiscard]] bool			exist() const noexcept;
//
//	virtual	bool				execute(chrono::tick::duration _tick_diff, intptr_t _option = 0) override;
//
//private:
//			lockable<CONTAINER>	m_list_executor;
//
//	virtual result_code			_process_initializing(context& _context) override;
//	virtual result_code			_process_initialize(context& _context) override;
//	virtual result_code			_process_destroying() noexcept override;
//	virtual result_code			_process_destroy() noexcept override;
//
//	virtual result_code			_process_starting(context& _context) override;
//	virtual result_code			_process_start(context& _context) override;
//	virtual result_code			_process_stopping() noexcept override;
//	virtual result_code			_process_stop() noexcept override;
//
//	virtual	bool				process_post(object_ptr<Iexecutable>&& _pexecutable) override;
//
//	virtual	bool				process_attach(TEXECUTOR* _pschedulable) override;
//	virtual	bool				process_detach(TEXECUTOR* _pschedulable) noexcept override;
//};
//
//
//}
//
//#include "cgdk/sdk10/system/object/executor.list.inl"
