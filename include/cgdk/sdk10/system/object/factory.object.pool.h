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

 @class		object_pool
 @brief		객체의 할당과 해제의 효율을 향상시키기 위한 객체 풀
 @todo		
 @ref		Ipoolable, Npoolable
 @details	\n
 객체의 동적 할당과 해제의 효율성을 높이기 위한 풀 객체이다.
 내부적으로 락프리로 동작하기 때문에 매우 고성능을 제공한다.

 풀의 대상 객체가 되려면 반드시 Ipoolable<TOBJECT>를 상속받은 클래스어야한다.

 풀에 할당을 요구하면 먼저 가비지 스택를 먼저 검사한다. 만약 스택에 객체가 있을 경우 그것을 할당해준다.
 만약 스택에 객체가 하나도 없다면 새로 생성해서 할당해준다.
 할당해준 객체가 다시 돌아오게 되면 가비지 스택에 저장해 놓았다가 다음 할당 요구때 할당해준다.
 다만 너무 많은 객체가 가비지 스택에 존재할 경우 일정량을 해제해 적절한 수량을 유지한다.

 풀에서 객체를 할당하기 위해서는 alloc()함수를 호출하며 할당 했던 객체를 해제하기 위해서는 free()함수를 사용한다.
 prepare()함수를 사용하면 미리 객체를 생성해놓을 수도 있다.
 shrink()함수를 사용하면 쌓여있는 가비지들을 할당 해제할 수도 있다.

*/
//-----------------------------------------------------------------------------
template <class TOBJECT>
class factory::object_pool : 
// inherited classes)
	public						factory::Iobject<TOBJECT>
{
// constructor/destructor) 
public:
			object_pool() : object_pool(std::string_view(), eFACTORY_TYPE::POOL_USER) {}
			object_pool(const std::string_view _name, eFACTORY_TYPE _factory_type = eFACTORY_TYPE::DEFAULT) : factory::Iobject<TOBJECT>(_name, _factory_type) { this->set_gc_type(eFACTORY_GC_TYPE::POOLING); }
	virtual	~object_pool() noexcept {}

// public) 
public:
	virtual	size_t				prepare(size_t _amount) override;
	virtual	size_t				shrink(size_t _amount) noexcept override;
	virtual	void				sustain(eFACTORY_GC_LEVEL _level= eFACTORY_GC_LEVEL::NORMAL) noexcept override;

	[[nodiscard]] virtual size_t object_size() const noexcept override { return sizeof(TOBJECT);}
	[[nodiscard]] virtual size_t stacked_count() const noexcept override { return this->m_stack_object.size();}
	[[nodiscard]] virtual int64_t existing_limits() const noexcept override { return this->m_statistics.now.existing_limits;}
	virtual	void				set_gc_type(eFACTORY_GC_TYPE _gc_type) noexcept override { this->m_statistics.gc_type = _gc_type; }

	[[nodiscard]] TOBJECT*		alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
			void				dealloc(TOBJECT* _pobject) noexcept;

	#if !defined(_USE_TLS_FACTORY_STATISTICS)
			auto				statistics_on_alloc_create() noexcept				{ ++this->m_statistics.now.alloc_create; ++this->m_statistics.now.existing; return ++this->m_statistics.now.in_using; }
			void				statistics_on_alloc_create(int64_t _count) noexcept { this->m_statistics.now.alloc_create += _count; this->m_statistics.now.existing += _count; this->m_statistics.now.in_using += _count; }
			auto				statistics_on_alloc_stack() noexcept				{ ++this->m_statistics.now.alloc_stack; return ++this->m_statistics.now.in_using; }
			void				statistics_on_free_delete() noexcept				{ ++this->m_statistics.now.free_delete; --this->m_statistics.now.existing; --this->m_statistics.now.in_using; }
			void				statistics_on_free_delete(int64_t _count) noexcept	{ this->m_statistics.now.free_delete += _count; this->m_statistics.now.existing -= _count; }
			void				statistics_on_free_stack() noexcept					{ ++this->m_statistics.now.free_stack; --this->m_statistics.now.in_using; }
			void				statistics_on_existing_decrement() noexcept			{ --this->m_statistics.now.existing; }
			void				statistics_on_extra() noexcept						{ ++this->m_statistics.now.extra;}
			void				statistics_on_shrink(uint64_t _count) noexcept		{ this->m_statistics.now.free_stack -= _count; this->m_statistics.now.free_delete += _count; this->m_statistics.now.existing -= _count;}
	#else
			auto				statistics_on_alloc_create() noexcept				{ auto ptls_data = this->_get_tls_data(); ++ptls_data->statistics_now.alloc_create; ++ptls_data->statistics_now.existing; return ++ptls_data->statistics_now.in_using; }
			void				statistics_on_alloc_create(int64_t _count) noexcept { auto ptls_data = this->_get_tls_data(); ptls_data->statistics_now.alloc_create += _count; ptls_data->statistics_now.existing += _count; ptls_data->statistics_now.in_using += _count; }
			auto				statistics_on_alloc_stack() noexcept				{ auto ptls_data = this->_get_tls_data(); ++ptls_data->statistics_now.alloc_stack; return ++ptls_data->statistics_now.in_using; }
			auto				statistics_on_alloc_stack_tls() noexcept			{ auto ptls_data = this->_get_tls_data(); ++ptls_data->statistics_now.alloc_stack; ++ptls_data->statistics_now.alloc_stack_tls; return ++ptls_data->statistics_now.in_using; }
			void				statistics_on_free_delete() noexcept				{ auto ptls_data = this->_get_tls_data(); ++ptls_data->statistics_now.free_delete; --ptls_data->statistics_now.existing; --ptls_data->statistics_now.in_using; }
			void				statistics_on_free_delete(int64_t _count) noexcept	{ auto ptls_data = this->_get_tls_data(); ptls_data->statistics_now.free_delete += _count; ptls_data->statistics_now.existing -= _count; }
			void				statistics_on_free_stack() noexcept					{ auto ptls_data = this->_get_tls_data(); ++ptls_data->statistics_now.free_stack; --ptls_data->statistics_now.in_using; }
			void				statistics_on_existing_decrement() noexcept			{ auto ptls_data = this->_get_tls_data(); --ptls_data->statistics_now.existing; }
			void				statistics_on_extra() noexcept						{ auto ptls_data = this->_get_tls_data(); ++ptls_data->statistics_now.extra;}
			void				statistics_on_shrink(size_t _count) noexcept		{ auto ptls_data = this->_get_tls_data(); ptls_data->statistics_now.free_stack -= _count; ptls_data->statistics_now.free_delete += _count; }

			struct sTLS_DATA : public factory::sSTATISTICS_TLS
			{
			};
			std::mutex			m_cs_vector_tls_data;
			std::vector<sTLS_DATA*> m_vector_tls_data;
	thread_local static sTLS_DATA* m_tls_data[54];
			int					m_local_data_index = 0;

	[[nodiscard]] sTLS_DATA*	_get_tls_data() noexcept { auto p = *(m_tls_data + m_local_data_index); if ( p == nullptr) { p = this->_alloc_tls_data();} return p; }
	[[nodiscard]] auto			_alloc_tls_data() { auto p = new sTLS_DATA; *(m_tls_data + this->m_local_data_index) = p; scoped_lock(this->m_cs_vector_tls_data) { this->m_vector_tls_data.push_back(p);} return p; }
			void				_process_tls_data() noexcept;
			void				_free_all_tls_data() noexcept;
	#endif

private:
			object_pool(const object_pool<TOBJECT>&) = delete;
			void				operator = (const object_pool<TOBJECT>& /*_rhs*/) = delete;

	template <class T>
	[[nodiscard]] std::enable_if_t<std::is_base_of_v<factory::_traits_has_pool, T>, TOBJECT*>
								process_create_object(CGNEW_DEBUG_INFO_PARAMETERS)
	{
		// 1) 일단 새로 생성된다.
		auto pobject = this->create_object(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);

		// 2) pool에 setting한다. (처리과정에서 pool의 reference Counting를 1증가시키게 된다.)
		pobject->m_ppool = this;
		pobject->m_pfactory = this;

		// return)
		return pobject;
	}

	template <class T>
	[[nodiscard]] std::enable_if_t<!std::is_base_of_v<factory::_traits_has_pool, T>, TOBJECT*>
								process_create_object(CGNEW_DEBUG_INFO_PARAMETERS)
	{
		// 1) call 'create_object'
		auto pobject = this->create_object(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);

		// 2) increase reference count (m_ppool에 setting하지 않으면 자체적으로 증가시킨다.)
		this->add_ref();

		// return) 성공!!
		return pobject;
	}

// framework) 
private:
	// 3) 재고 객체 Stack
			LOCKFREE_SELF_STACK<TOBJECT*> m_stack_object;

	// 4) Pool Sustainment를 위한 변수들
			int64_t				m_existing_term_peak = 0;
			int64_t				m_existing_smoothed_average = 0;
			int64_t				m_existing_variation = 0;

private:
	[[nodiscard]] virtual TOBJECT* create_object(CGNEW_DEBUG_INFO_PARAMETERS) override;
	virtual	void				close() noexcept override;
};

#if defined(_USE_TLS_FACTORY_STATISTICS)
template <class TOBJECT>
thread_local typename factory::object_pool<TOBJECT>::sTLS_DATA* factory::object_pool<TOBJECT>::m_tls_data[54];
#endif

template <class TOBJECT>
void factory::object_pool<TOBJECT>::close() noexcept
{
	// 1) 최대 유지 갯수를 -1로 한다.
	this->m_statistics.now.existing_limits = -1;

	// 2) free stacked object
	TOBJECT* pobject;
	while ((pobject = this->m_stack_object.pop()) != nullptr)
	{
		// - 객체를 파괴한다.
		this->template process_destroy_object<TOBJECT>(pobject);

		// statistics)
		this->statistics_on_existing_decrement();
	}

	// 3) free all local data
#if defined(_USE_TLS_FACTORY_STATISTICS)
	this->_free_all_tls_data();
#endif
}

#if defined(_USE_TLS_FACTORY_STATISTICS)
template <class TOBJECT>
void factory::object_pool<TOBJECT>::_process_tls_data() noexcept
{
	scoped_lock(this->m_cs_vector_tls_data)
	{
		// - prepare
		this->m_statistics.now.stack_tls = 0;

		// - update
		for (auto iter : m_vector_tls_data)
		{
			iter->update_statistics(this->m_statistics.now);
		}
	}
}

template <class TOBJECT>
void factory::object_pool<TOBJECT>::_free_all_tls_data() noexcept
{
	std::vector<sTLS_DATA*> vector_ptls_data;

	// 1) get all tls data
	scoped_lock(this->m_cs_vector_tls_data)
	{
		// - move all tls data
		vector_ptls_data = std::move(this->m_vector_tls_data);

		// - apply all to m_statistics
		for (auto iter : vector_ptls_data)
		{
			iter->update_statistics(this->m_statistics.now);
		}
	}

	// 2) delete tls data
	for (auto iter : vector_ptls_data)
	{
		delete iter;
	}
}

#endif

template <class TOBJECT>
size_t factory::object_pool<TOBJECT>::prepare(size_t _amount)
{
	// check) prepare할 수가 0보다는 커야한다.
	CGASSERT(_amount > 0, 0);

	// check) 0보다 작거나 같으면 prepare할꺼 같으면 그냥 끝낸다.
	RETURN_IF(_amount <= 0, 0);

	// 1) 임시로 사용할 List를 할당받는다.
	std::vector<TOBJECT*> vector_created;

	// 2) Reserve한다.
	vector_created.reserve(_amount);

	try
	{
		// 3) prepare 수만큼 Loop를 돌면서 생성한다.
		for(; _amount>0; --_amount)
		{
			// declare) 새로 생성한다.
			auto pcreate = this->template process_create_object<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_INITIAL);

			// - 생성된 객체를 임시 버퍼에 짚어 넣는다.
			vector_created.emplace_back(pcreate);
		}
	}
	// exception) 
	catch(...)
	{
		// - 이미 생성된 것들만 prepare하도록 한다.
	}

	// declare)
	auto size_created = static_cast<int64_t>(vector_created.size());

	// 4) 평균값을 수정한다.
	this->m_existing_smoothed_average += size_created;

	// statistics) 
	this->statistics_on_alloc_create(size_created);

	// 5) store to stack
	for(auto& iter:vector_created)
	{
		this->dealloc(iter);
	}
	
	// return)
	return vector_created.size();
}

template <class TOBJECT>
size_t factory::object_pool<TOBJECT>::shrink(size_t _amount) noexcept
{
	// case) shrink exceed
	if(_amount == eFACTORY_SHRINK::EXCEED)
	{
		_amount = static_cast<size_t>(this->m_statistics.now.existing - this->m_statistics.now.existing_limits);
	}
	// case) shrink all
	else if(_amount == eFACTORY_SHRINK::ALL)
	{
		_amount = static_cast<int>(this->m_stack_object.size());
	}

	// check) return if _amount is 0
	RETURN_IF(_amount < 1, 0);

	// declare)
	size_t count_shrink = 0;

	// 1) stack되어 있는 object을 tempShrink만큼 지운다.
	for(; count_shrink < _amount; ++count_shrink)
	{
		// - Pop을 먼저한다.
		auto pobject = this->m_stack_object.pop();

		// check) pobject가 nullptr이면 안된다.
		BREAK_IF(pobject == nullptr);

		// - Object를 destroy한다.
		this->template process_destroy_object<TOBJECT>(pobject);
	}

	// statistics)
	this->statistics_on_shrink(count_shrink);

	// 4) 평균값을 수정.
	this->m_existing_smoothed_average	-= count_shrink;
	
	// return)
	return count_shrink;
}

template <class TOBJECT>
void factory::object_pool<TOBJECT>::sustain(eFACTORY_GC_LEVEL _level) noexcept
{
	// 1) apply local data
#if defined(_USE_TLS_FACTORY_STATISTICS)
	this->_process_tls_data();
#endif

	// check) 
	RETURN_IF(this->m_statistics.now.existing_limits < 0);

	// 1) calculate in_using_term_peak
	{
		// - calculate max stack
		auto in_using_max = ((this->m_existing_term_peak * 9) >> 3) + 8;

		// - get average of stacked
		auto in_using_smoothed_average = ((this->m_existing_smoothed_average * 896 + in_using_max * 128) >> 10);

		// - get distributions of stacked
		auto in_using_variation = ((this->m_existing_variation * 768 + 256 * ((in_using_smoothed_average > in_using_max) ? (in_using_smoothed_average - in_using_max) : (in_using_max - in_using_smoothed_average)) + 1) >> 10);

		// - get max existing stack
		if (this->m_statistics.now.existing_limits >= 0)
		{
			this->m_statistics.now.existing_limits = (in_using_smoothed_average + (in_using_variation << 2));
		}

		// - update values
		this->m_existing_smoothed_average = in_using_smoothed_average;
		this->m_existing_variation = in_using_variation;
		this->m_existing_term_peak = this->m_statistics.now.in_using;
	}

	// 2) get shrink count
	auto count_shrink = this->_get_shrink_count(_level);

	// 3) shrink 
	this->shrink(count_shrink);
}

template <class TOBJECT>
TOBJECT* factory::object_pool<TOBJECT>::create_object(CGNEW_DEBUG_INFO_PARAMETERS)
{
#pragma push_macro("new")
#undef new
	#ifdef _ENABLE_DEBUG_NEW
		#if defined(_WIN32)
			return new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) TOBJECT;
		#else
			return new TOBJECT;
		#endif
	#else
	return new TOBJECT;
	#endif
#pragma pop_macro("new")
}

template <class TOBJECT>
TOBJECT* factory::object_pool<TOBJECT>::alloc(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// declare)
	[[maybe_unused]] int64_t count_using;

	// 1) pop stacked 
	auto pobject = this->m_stack_object.pop();

	// 2-1) use it if exist
	if (pobject != nullptr)
	{
		// statistics)
		count_using = this->statistics_on_alloc_stack();
	}

	// 2-2) create new if empty
	else
	{
		// - create new object
		pobject = this->template process_create_object<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);

		// statistics)
		count_using = this->statistics_on_alloc_create();
	}

	// debug)
	CGNEW_DEBUG_INFO_SET(pobject, _filename, _line);

	// 3) set null
	pobject->Next = nullptr;

	// 4) process object alloc
	this->template process_on_alloc<TOBJECT>(pobject);

	// sustain)
	if(count_using > this->m_existing_term_peak)
	{
		// - update m_existing_term_peak
		this->m_existing_term_peak = count_using;

		// - 사용중인 갯수가 최대할당치를 넘어설 경우 수정한다.
		if(count_using > this->m_statistics.now.existing_limits && this->m_statistics.now.existing_limits >= 0)
		{
			this->m_statistics.now.existing_limits = static_cast<size_t>(((count_using * 9)>>3) + 8);
		}
	} 

	// return) success
	return pobject;
}

template <class TOBJECT>
void factory::object_pool<TOBJECT>::dealloc(TOBJECT* _pobject) noexcept
{
	// check)
	CGASSERT_ERROR(_pobject != nullptr);

	// check)
	CGASSERT_ERROR(_pobject->reference_count() == 0);

	// check)
	CGASSERT_ERROR(_pobject->Next == nullptr);

	// 1) on_free
	this->template process_on_dealloc<TOBJECT>(_pobject);

	// 2) 최대 한계 stack수보다 stack된 memory Block갯수가 많으면 할당해제한다.
	if(this->m_statistics.now.existing <= this->m_statistics.now.existing_limits)
	{
		// statistics)
		this->statistics_on_free_stack();

		// 3) stack object to garbage
		this->m_stack_object.push(_pobject);
	}
	else
	{
		// statistics)
		this->statistics_on_free_delete();

		// 3) destroy object
		this->template process_destroy_object<TOBJECT>(_pobject);
	}
}


}