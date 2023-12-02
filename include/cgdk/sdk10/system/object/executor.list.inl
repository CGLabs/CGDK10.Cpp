////*****************************************************************************
////*                                                                           *
////*                      Cho sanghyun's Game Classes II                       *
////*                       Ver 10.0 / Release 2019.12.11                       *
////*                                                                           *
////*                              object classes                               *
////*                                                                           *
////*                                                                           *
////*                                                                           *
////*                                                                           *
////*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
////*  Best for Game Developement and Optimized for Game Developement.          *
////*                                                                           *
////*                (c) 2003. Cho Sanghyun. All right reserved.                *
////*                          http://www.CGCII.co.kr                           *
////*                                                                           *
////*****************************************************************************
//#pragma once
////-----------------------------------------------------------------------------
////
//// executor::list
////
//// 1. executor::list��~
////    1) ���� ���� executor�� �����ð����� ��������ִ� executor�� executor�̴�.
////    
//// 2. �ֿ��Լ�.
////    1) bool register_executor(TEXECUTOR* _pexecutor);
////       - ������ TEXECUTOR�� ���̴� �Լ��̴�.
////
////    2) bool unregister_executor(TEXECUTOR* _pexecutor);
////       - ������ TEXECUTOR�� �����.
////
////-----------------------------------------------------------------------------
//namespace CGDK
//{
//
//template <class TEXECUTOR>
//class executor::list<TEXECUTOR>::ITERATOR
//{
//public:
//	ITERATOR(const lockable<CONTAINER>& pcontainer) noexcept : m_lockable_lock(pcontainer), m_iter(pcontainer.begin()), m_iter_end(pcontainer.end())	{}
//
//public:
//	bool			is_continue() const noexcept{ return this->m_iter!=this->m_iter_end;}
//	bool			is_ended() const noexcept	{ return this->m_iter==this->m_iter_end;}
//	bool			move_next() noexcept		{ if(this->m_iter==this->m_iter_end) return false; ++m_iter; return true;}
//												  
//	void			operator++() noexcept		{ ++this->m_iter;}
//	TEXECUTOR*		operator->() const noexcept	{ return *this->m_iter;}
//	TEXECUTOR*		operator*() const noexcept	{ return *this->m_iter;}
//
//public:
//			std::unique_lock<lock_object> m_lockable_lock;
//	typename CONTAINER::iterator	m_iter;
//	typename CONTAINER::iterator	m_iter_end;
//};
//
//template <class TEXECUTOR>
//executor::list<TEXECUTOR>::list()
//{
//	// 1) set object type
//	this->set_object_type(eOBJECT_TYPE::EXECUTOR_LIST);
//
//	// 2) register to factory manager
//	this->process_register_executor();
//}
//
//template <class TEXECUTOR>
//executor::list<TEXECUTOR>::list(std::string_view _name) :
//	Nexecutor(_name)
//{
//	// 1) set object type
//	this->set_object_type(eOBJECT_TYPE::EXECUTOR_LIST);
//
//	// 2) register to factory manager
//	this->process_register_executor();
//}
//
//template <class TEXECUTOR>
//executor::list<TEXECUTOR>::~list() noexcept
//{
//	// 1) clear executors
//	scoped_lock(this->m_list_executor)
//	{
//		this->m_list_executor.clear();
//	}
//
//	// 2) unregister to factory manager
//	this->process_unregister_executor();
//}
//
//template <class TEXECUTOR>
//result_code executor::list<TEXECUTOR>::_process_initializing(context& _context)
//{
//	// 1) call 'on_initializing'
//	this->on_initializing(_context);
//
//	// return)
//	return result_code(eRESULT::SUCCESS);
//}
//template <class TEXECUTOR>
//result_code executor::list<TEXECUTOR>::_process_initialize(context& _context)
//{
//	// 1) call 'on_initialize'
//	this->on_initialize(_context);
//
//	// return)
//	return result_code(eRESULT::SUCCESS);
//}
//
//template <class TEXECUTOR>
//result_code executor::list<TEXECUTOR>::_process_destroying() noexcept
//{
//	// 1) call 'on_destroying'
//	this->on_destroying();
//
//	// return)
//	return result_code(eRESULT::SUCCESS);
//}
//template <class TEXECUTOR>
//result_code executor::list<TEXECUTOR>::_process_destroy() noexcept
//{
//	// 1) call 'on_destroy'
//	this->on_destroy();
//
//	// return)
//	return result_code(eRESULT::SUCCESS);
//}
//
//template <class TEXECUTOR>
//result_code executor::list<TEXECUTOR>::_process_starting(context& _context)
//{
//	// 1) call 'on_starting'
//	this->on_starting(_context);
//
//	// return)
//	return result_code(eRESULT::SUCCESS);
//}
//
//template <class TEXECUTOR>
//result_code executor::list<TEXECUTOR>::_process_start(context& _context)
//{
//	// 1) call 'on_start'
//	this->on_start(_context);
//
//	// return)
//	return result_code(eRESULT::SUCCESS);
//}
//
//template <class TEXECUTOR>
//result_code executor::list<TEXECUTOR>::_process_stopping() noexcept
//{
//	// 1) call 'on_stopping'
//	this->on_stopping();
//
//	// 2) ��� �Ҵ��������ش�.(�̰� �Ҹ��ڿ��� �ݵ�� ����� �Ѵ�. �ƴϸ� �Ҹ��� ���� ������ ���� �� �ִ�.)
//	scoped_lock(this->m_list_executor)
//	{
//		this->m_list_executor.clear();
//	}
//
//	// return)
//	return result_code(eRESULT::SUCCESS);
//}
//
//template <class TEXECUTOR>
//result_code executor::list<TEXECUTOR>::_process_stop() noexcept
//{
//	// 1) call 'on_stop'
//	this->on_stop();
//
//	// return)
//	return result_code(eRESULT::SUCCESS);
//}
//
//template <class TEXECUTOR>
//bool executor::list<TEXECUTOR>::process_attach(TEXECUTOR* _pexecutor)
//{
//	// check)
//	CGASSERT_ERROR(_pexecutor!=nullptr);
//
//	// check) _pexecutor�� nullptr�̸� �ȉ´�!
//	RETURN_IF(_pexecutor == nullptr, false);
//
//	scoped_lock(m_list_executor)
//	{
//		// 1) �ش� ��ü�� ã�´�.
//		auto iter_end = this->m_list_executor.end();
//		auto iter = std::find(this->m_list_executor.begin(), iter_end, _pexecutor);
//
//		// check) �̹� �߰��Ǿ� ������ ������.
//		RETURN_IF(iter != iter_end, false);
//
//		// 2) �߰��Ѵ�.
//		this->m_list_executor.emplace_back(_pexecutor);
//	}
//
//	// return) ����~
//	return true;
//}
//
//template <class TEXECUTOR>
//bool executor::list<TEXECUTOR>::process_detach(TEXECUTOR* _pexecutor) noexcept
//{
//	scoped_lock(this->m_list_executor)
//	{
//		// check) nullptr�̸� ��� ��ü�� ������.
//		if(_pexecutor == nullptr)
//		{
//			return this->unregister_executor_all();
//		}
//
//		// 1) �ش� ��ü�� ã�´�.
//		auto iter_end = this->m_list_executor.end();
//		auto iter = std::find(this->m_list_executor.begin(), iter_end, _pexecutor);
//
//		// check) ��ã������ ������.
//		RETURN_IF(iter == iter_end, false);
//
//		// 2) �����.
//		this->m_list_executor.erase(iter);
//	}
//
//	// return) ����!!!
//	return true;
//}
//
//template <class TEXECUTOR>
//int executor::list<TEXECUTOR>::unregister_executor_all() noexcept
//{
//	int	count;
//
//	scoped_lock(this->m_list_executor)
//	{
//		// 1) Excutor�� ������ ������ ���´�.
//		count = static_cast<int>(this->m_list_executor.size());
//
//		// 2) ��� ����
//		this->m_list_executor.clear();
//	}
//
//	// return)
//	return count;
//}
//
//template <class TEXECUTOR>
//typename executor::list<TEXECUTOR>::ITERATOR executor::list<TEXECUTOR>::get_iterator() noexcept
//{
//	scoped_lock(m_list_executor)
//	{
//		return ITERATOR(this->m_list_executor);
//	}
//}
//
//// definitions) 
//template <class TREF>
//class CGATOMIC_REF
//{
//public:
//	CGATOMIC_REF(std::atomic<TREF>& _ref) noexcept : m_ref(_ref) { value=_ref.fetch_add(1)+1; }
//	~CGATOMIC_REF() noexcept { this->m_ref.fetch_sub(1); }
//
//private:
//	std::atomic<TREF>& m_ref;
//public:
//	TREF value;
//};
//
//template <class TEXECUTOR>
//bool executor::list<TEXECUTOR>::process_post(object_ptr<Iexecutable>&& _pxecutable)
//{
//	// check) _pexecutable�� nullptr�̸� �׳� ������.
//	RETURN_IF(_pxecutable == nullptr, false);
//
//	// �ӽ÷�...
//	CGASSERT_ERROR(false);
//
//	// declare) 
//	CGATOMIC_REF<size_t> rExecutable(_pxecutable->m_count_concurrent_executing);
//
//	// check) ���� ������� MAXġ���� ũ�� 1�� ���̰� ������.
//	RETURN_IF(rExecutable.value> _pxecutable->maximum_concurrent_executing_count(), false);
//
//	// 1) �ٷ� �����Ѵ�.
//	_pxecutable->process_execute(0, 0);
//
//	// return)
//	return true;
//}
//
//
//template <class TEXECUTOR>
//bool executor::list<TEXECUTOR>::execute(chrono::tick::duration _tick_diff, intptr_t _option)
//{
//	// declare) 
//	fast_vector<object_ptr<TEXECUTOR>, 64> vector_executor;
//
//	scoped_lock(this->m_list_executor)
//	{
//		// 1) Resserve
//		for(const auto& iter:m_list_executor)
//		{
//			vector_executor.emplace_back(iter);
//		}
//	}
//
//	// 4) ���鼭 execute�Ѵ�.
//	for(auto& iter:vector_executor)
//	{
//		iter->execute(_tick_diff, _option);
//	}
//
//	// return)
//	return true;
//}
//
//template <class TEXECUTOR>
//size_t executor::list<TEXECUTOR>::count() const noexcept
//{
//	scoped_lock(this->m_list_executor)
//	{
//		return this->m_list_executor.size();
//	}
//}
//
//template <class TEXECUTOR>
//bool executor::list<TEXECUTOR>::empty() const noexcept
//{
//	return this->count() == 0;
//}
//
//template <class TEXECUTOR>
//bool executor::list<TEXECUTOR>::exist() const noexcept
//{
//	return this->count() != 0;
//}
//
//
//}