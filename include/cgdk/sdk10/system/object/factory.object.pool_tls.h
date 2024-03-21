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

 @class		object_pool_tls
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
class factory::object_pool_tls : 
// inherited classes)
	public						factory::Iobject<TOBJECT>
{
// constructor/destructor) 
public:
			object_pool_tls() : object_pool_tls(std::string_view(), eFACTORY_TYPE::POOL_USER) { this->set_gc_type(eFACTORY_GC_TYPE::DEFAULT); }
			object_pool_tls(const std::string_view _name, eFACTORY_TYPE _factory_type = eFACTORY_TYPE::DEFAULT) : factory::Iobject<TOBJECT> (_name, _factory_type) { this->set_gc_type(eFACTORY_GC_TYPE::DEFAULT); }
	virtual	~object_pool_tls() noexcept;

// public) 
public:
	virtual	size_t				prepare(size_t _amount) override;
	virtual	size_t				shrink(size_t _amount) noexcept override;
	virtual	void				sustain(eFACTORY_GC_LEVEL _level= eFACTORY_GC_LEVEL::NORMAL) noexcept override;

	[[nodiscard]] virtual size_t object_size() const noexcept override { return sizeof(TOBJECT);}
	[[nodiscard]] virtual size_t stacked_count() const noexcept override { return this->m_stack_object.size();}
	[[nodiscard]] virtual int64_t existing_limits() const noexcept override { return this->m_statistics.now.existing_limits;}
	virtual	void				set_gc_type(eFACTORY_GC_TYPE _gc_type) noexcept override;

	[[nodiscard]] TOBJECT*		alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
			void				dealloc(TOBJECT* _pobject) noexcept;

			struct sTLS_DATA
			{
				TOBJECT*		tls_stack = nullptr;
				sSTATISTICS_TLS statistics;
			};
			std::mutex			m_cs_vector_tls_data;
			std::vector<sTLS_DATA*> m_vector_tls_data;
	thread_local static sTLS_DATA* m_tls_data[54];
			int					m_local_data_index = 0;

	[[nodiscard]] sTLS_DATA*	_get_tls_data() noexcept { auto p = *(m_tls_data + this->m_local_data_index); if ( p == nullptr) { p = this->_alloc_tls_data();} return p; }
	[[nodiscard]] sTLS_DATA*	_alloc_tls_data();
			bool				_process_gathering_tls_statistics() noexcept;
			void				_free_all_tls_data() noexcept;
			TOBJECT*			_process_pop_from_centeral_stack_or_create(sTLS_DATA* _ptls_data CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS);
			void 				_process_push_to_centeral_stack_or_delete(sTLS_DATA* _ptls_data, TOBJECT* _pobject);
			void				_process_tls_redundancy(sTLS_DATA* _ptls_data, int32_t _count);

private:
			object_pool_tls(const object_pool_tls<TOBJECT>&) = delete;
			void				operator = (const object_pool_tls<TOBJECT>&) = delete;

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

	virtual	void				process_tls_garbage_collection() override
	{
		// 1) get tls data
		auto ptls_data = this->_get_tls_data();

		// 2) get count of redundancy
		auto count_redundancy = ptls_data->statistics.now.tls_stack_depth - static_cast<int32_t>(this->m_statistics.now.tls_stack_depth_threshold);

		// check)
		RETURN_IF(count_redundancy <= 0, );

		// 3) process garbage collection 
		this->_process_tls_redundancy(ptls_data, count_redundancy);
	}


private:
	// 3) 재고 객체 stack
			LOCKFREE_SELF_STACK<TOBJECT*> m_stack_object;

	// 4) Pool Sustainment를 위한 변수들
			std::atomic<int64_t> m_existing = 0;
			int64_t				m_existing_term_peak = 0;
			int64_t				m_existing_smoothed_average = 0;
			int64_t				m_existing_variation = 0;
private:
	[[nodiscard]] virtual TOBJECT* create_object(CGNEW_DEBUG_INFO_PARAMETERS) override;
	virtual	void				close() noexcept override;
};

template <class TOBJECT>
thread_local typename factory::object_pool_tls<TOBJECT>::sTLS_DATA* factory::object_pool_tls<TOBJECT>::m_tls_data[54];

template <class TOBJECT>
factory::object_pool_tls<TOBJECT>::~object_pool_tls() noexcept
{
	CGASSERT_ERROR(this->m_existing == 0);

	// 1) delete vector_tls_data
	scoped_lock(this->m_cs_vector_tls_data)
	{
		for (auto iter : this->m_vector_tls_data)
		{
			delete iter;
		}
	}
}

template <class TOBJECT>
void factory::object_pool_tls<TOBJECT>::close() noexcept
{
	// 1) 최대 유지 갯수를 -1로 한다.
	this->m_statistics.now.existing_limits = -1;

	// 2) get tls
	auto ptls_data = *(this->m_tls_data + this->m_local_data_index);

	// 3) free stacked object
	TOBJECT* pobject;
	while ((pobject = this->m_stack_object.pop()) != nullptr)
	{
		// - 객체를 파괴한다.
		this->template process_destroy_object<TOBJECT>(pobject);

		// statistics) 
		if (ptls_data != nullptr)
		{
			--ptls_data->statistics.now.free_stack;
			++ptls_data->statistics.now.free_delete;
		}
		else
		{
			--this->m_statistics.now.existing;
			--this->m_statistics.now.free_stack;
			++this->m_statistics.now.free_delete;
		}
	}

	// 4) free all local data
	this->_free_all_tls_data();
}

template <class TOBJECT>
typename factory::object_pool_tls<TOBJECT>::sTLS_DATA* factory::object_pool_tls<TOBJECT>::_alloc_tls_data()
{
	// 1) create new sTLS_DATA
	auto p = new sTLS_DATA;
	
	// 2) set default value;
	if (this->gc_type() == eFACTORY_GC_TYPE::TLS_POOLING_NO_GC)
	{
		p->statistics.now.tls_stack_depth_threshold = INT32_MAX;
	}

	// 3) set...
	*(this->m_tls_data + this->m_local_data_index) = p;
	scoped_lock(this->m_cs_vector_tls_data)
	{
		this->m_vector_tls_data.push_back(p);
	}
	
	return p;
}

template <class TOBJECT>
bool factory::object_pool_tls<TOBJECT>::_process_gathering_tls_statistics() noexcept
{
	// declare)
	bool result = false;

	// 1) gathering tls data 
	scoped_lock(this->m_cs_vector_tls_data)
	{
		// - prepare
		this->m_statistics.now.tls_stack_depth = 0;
		this->m_statistics.now.tls_stack_depth_threshold = 0;

		// - update
		for (auto iter : this->m_vector_tls_data)
		{
			result |= iter->statistics.update_statistics(this->m_statistics.now, this->gc_type());
		}
	}

	// return)
	return result;
}

template <class TOBJECT>
void factory::object_pool_tls<TOBJECT>::_free_all_tls_data() noexcept
{
	// 1) delete all tls stacked object and get all tls data
	scoped_lock(this->m_cs_vector_tls_data)
	{
		// declare) 
		int64_t count_delete = 0;

		// - prepare
		this->m_statistics.now.tls_stack_depth = 0;

		// - apply all to m_statistics
		for (auto iter : this->m_vector_tls_data)
		{
			// - set existing tls
			iter->statistics.now.tls_stack_depth_threshold = -1;

			// declare) 
			int32_t count = 0;

			TOBJECT* iter_end = nullptr;

			do
			{
				// - destroy tls objects
				auto pobject_first = iter->tls_stack;

				// -  destroy object
				auto piter = pobject_first;
				while (piter != nullptr && piter != iter_end)
				{
					auto pobject_now = piter;
					piter = piter->Next;

					++count;

					// - destory
					this->template process_destroy_object<TOBJECT>(pobject_now);
				}

				// check)
				if (pobject_first != iter->tls_stack)
				{
					CGASSERT_ERROR(false);

					iter_end = pobject_first;

					std::this_thread::sleep_for(1ms);
				}
				else
				{
					iter->tls_stack = nullptr;
				}

			} while (iter->tls_stack != nullptr);

			// statistics)
			iter->statistics.now.free_delete += count;
			iter->statistics.now.tls_stack_depth -= count;

			// check)
			CGASSERT_ERROR(iter->statistics.now.tls_stack_depth == 0);

			// - process statistics
			iter->statistics.update_statistics(this->m_statistics.now, this->gc_type());

			// -...
			count_delete += count;
		}

		// check)
		CGASSERT_ERROR(this->m_statistics.now.tls_stack_depth == 0);

		// statistics) 
		this->m_existing -= count_delete;
	}
}

template <class TOBJECT>
size_t factory::object_pool_tls<TOBJECT>::prepare(size_t _amount)
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
	}

	// declare)
	auto size_created = static_cast<int32_t>(vector_created.size());

	// 4) 평균값을 수정한다.
	this->m_existing_smoothed_average += size_created;

	// statistics) 
	this->_get_tls_data()->statistics.now.statistics_on_prepare(size_created);

	// 6) store to stack
	for(auto& iter:vector_created)
	{
		this->m_stack_object.push(iter);
	}

	// return) 성공!!
	return vector_created.size();
}

template <class TOBJECT>
size_t factory::object_pool_tls<TOBJECT>::shrink(size_t _amount) noexcept
{
	// case) shrink exceed
	if(_amount == eFACTORY_SHRINK::EXCEED)
	{
		_amount = static_cast<size_t>(this->m_statistics.now.existing - this->m_statistics.now.existing_limits);
	}
	// case) shrink all
	else if(_amount == eFACTORY_SHRINK::ALL)
	{
		_amount = static_cast<int>(m_stack_object.size());
	}

	// check) return if _amount is 0
	RETURN_IF(_amount < 1, 0);

	// declare)
	uint32_t count_shrink = 0;

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
	this->_get_tls_data()->statistics.now.statistics_on_shrink(count_shrink);

	// 4) 평균값을 수정.
	this->m_existing_smoothed_average -= count_shrink;
	
	// return)
	return count_shrink;
}

template <class TOBJECT>
void factory::object_pool_tls<TOBJECT>::sustain(eFACTORY_GC_LEVEL _level) noexcept
{
	// 1) gathering tls statistics
	auto is_active = this->_process_gathering_tls_statistics();

	// check) is closed?
	RETURN_IF(this->m_statistics.now.existing_limits < 0);

	// 2) garbage collection
	auto ptls_data = this->_get_tls_data();

	// 3) get garbage count
	auto count_garbage = ptls_data->statistics.now.tls_stack_depth - static_cast<int32_t>(this->m_statistics.now.tls_stack_depth_threshold);

	// 4) garbage collection
	if (count_garbage > 0)
	{
		this->_process_tls_redundancy(ptls_data, count_garbage);
	}

	// declare)
	auto temp_gc_type = this->gc_type();

	// 5) calculate m_statistics.now.existing_limits
	if (temp_gc_type == eFACTORY_GC_TYPE::POOLING
	 || temp_gc_type == eFACTORY_GC_TYPE::TLS_POOLING)
	{
		int64_t in_using_max;

		// - calculate using_max
		if (is_active == true)
			in_using_max = ((this->m_existing_term_peak * 9) >> 3) + 8;
		else
			in_using_max = this->m_existing_term_peak;

		// - get average of stacked
		auto in_using_smoothed_average = ((this->m_existing_smoothed_average * 896 + in_using_max * 128) >> 10);

		// - get distributions of stacked
		auto in_using_variation = ((this->m_existing_variation * 896 + 128 * ((in_using_smoothed_average > in_using_max) ? (in_using_smoothed_average - in_using_max) : (in_using_max - in_using_smoothed_average)) + 1) >> 10);

		// - get max existing stack
		if (this->m_statistics.now.existing_limits >= 0)
		{
			auto existing_limits = in_using_smoothed_average + (in_using_variation << 2);
			this->m_statistics.now.existing_limits = (existing_limits >= 0) ? existing_limits : 0;
		}

		// - update and reset values
		this->m_existing_smoothed_average = in_using_smoothed_average;
		this->m_existing_variation = in_using_variation;
		this->m_existing_term_peak = this->m_statistics.now.in_using;
	}

	// 6) get shrink count
	auto count_shrink = this->_get_shrink_count(_level);

	// 7) shrink 
	this->shrink(count_shrink);
}

template <class TOBJECT>
TOBJECT* factory::object_pool_tls<TOBJECT>::create_object(CGNEW_DEBUG_INFO_PARAMETERS)
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
void factory::object_pool_tls<TOBJECT>::set_gc_type(eFACTORY_GC_TYPE _gc_type) noexcept
{
	// check)
	RETURN_IF(this->gc_type() == _gc_type);

	// 1) set gc_type
	this->m_statistics.gc_type = _gc_type;

	switch (_gc_type)
	{
	case	eFACTORY_GC_TYPE::NO_POOLING:
			this->m_statistics.now.existing_limits = 0;
			scoped_lock(this->m_cs_vector_tls_data)
			{
				for (auto iter : m_vector_tls_data)
				{
					iter->statistics.now.tls_stack_depth_threshold = 0;
				}
			}
			break;

	case	eFACTORY_GC_TYPE::POOLING:
			{
				this->m_statistics.now.existing_limits = this->m_existing;
				scoped_lock(this->m_cs_vector_tls_data)
				{
					for (auto iter : m_vector_tls_data)
					{
						iter->statistics.now.tls_stack_depth_threshold = 0;
					}
				}
			}
			break;

	case	eFACTORY_GC_TYPE::POOLING_NO_GC:
			{
				this->m_statistics.now.existing_limits = INT64_MAX;
				scoped_lock(this->m_cs_vector_tls_data)
				{
					for (auto iter : m_vector_tls_data)
					{
						iter->statistics.now.tls_stack_depth_threshold = 0;
					}
				}
			}
			break;

	case	eFACTORY_GC_TYPE::TLS_POOLING:
			{
				this->m_statistics.now.existing_limits = this->m_statistics.now.tls_stack_depth;
			}
			break;

	case	eFACTORY_GC_TYPE::TLS_POOLING_NO_GC:
			{
				this->m_statistics.now.existing_limits = INT64_MAX;
				scoped_lock(this->m_cs_vector_tls_data)
				{
					for (auto iter : m_vector_tls_data)
					{
						iter->statistics.now.tls_stack_depth_threshold = INT32_MAX;
					}
				}
			}
			break;

	default:
			break;
	}
}

template <class TOBJECT>
TOBJECT* factory::object_pool_tls<TOBJECT>::alloc(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// declare) 
	TOBJECT* pobject;

	// 1) get tls data
	auto ptls_data = this->_get_tls_data();

	// declare)
	auto& tls_stack = ptls_data->tls_stack;

	// 2.A) pop from tls_stack
	if (tls_stack != nullptr)
	{
		// statistics)
		ptls_data->statistics.now.statistics_on_alloc_stack_tls();

		// - pop tls_stacked object
		pobject = tls_stack;
		tls_stack = pobject->Next;
	}
	// 2.B) pop from tls_stack
	else
	{
		pobject = this->_process_pop_from_centeral_stack_or_create(ptls_data CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
	}

	// debug)
	CGNEW_DEBUG_INFO_SET(pobject, _filename, _line);

	// 3) set null
	pobject->Next = nullptr;

	// 4) call 'process_on_pool_alloc'
	this->template process_on_alloc<TOBJECT>(pobject);

	// return)
	return pobject;
}

template <class TOBJECT>
TOBJECT* factory::object_pool_tls<TOBJECT>::_process_pop_from_centeral_stack_or_create(sTLS_DATA* _ptls_data CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS)
{
	// 1) pop from central stack
	auto pobject = this->m_stack_object.pop();

	// 2.A) pop from centeral stack
	if (pobject != nullptr)
	{
		// statistics)
		_ptls_data->statistics.now.statistics_on_alloc_stack();
	}
	// 2.B) create new
	else
	{
		// - create new object
		pobject = this->template process_create_object<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);

		// statistics)
		_ptls_data->statistics.now.statistics_on_alloc_create();
	}

	// 3) increase existing limits
	if (this->m_statistics.gc_type >= eFACTORY_GC_TYPE::TLS_POOLING)
	{
		++_ptls_data->statistics.now.tls_stack_depth_threshold;
	}
	else
	{
	}

	// statistics) 
	auto count_centeral_using = ++this->m_existing;

	// sustain)
	if (count_centeral_using > this->m_existing_term_peak)
	{
		if (this->m_statistics.gc_type != eFACTORY_GC_TYPE::NO_POOLING)
		{
			// - update m_existing_term_peak
			this->m_existing_term_peak = count_centeral_using;

			// - 사용중인 갯수가 최대할당치를 넘어설 경우 수정한다.
			if (count_centeral_using > this->m_statistics.now.existing_limits && this->m_statistics.now.existing_limits >= 0)
			{
				this->m_statistics.now.existing_limits = static_cast<size_t>(((count_centeral_using * 9) >> 3));
			}
		}
	}

	// return)
	return pobject;
}

template <class TOBJECT>
void factory::object_pool_tls<TOBJECT>::dealloc(TOBJECT* _pobject) noexcept
{
	// check)
	CGASSERT_ERROR(_pobject != nullptr);

	// check)
	CGASSERT_ERROR(_pobject->reference_count() == 0);

	// check)
	CGASSERT_ERROR(_pobject->Next == nullptr);

	// 1) call 'process_on_pool_dealloc'
	this->template process_on_dealloc<TOBJECT>(_pobject);

	// 2) get tls data
	auto ptls_data = this->_get_tls_data();

	// 3) get statistics.now
	auto& temp_now = ptls_data->statistics.now;

	// 4) get tls stack count 
	auto temp = temp_now.tls_stack_depth;

	// 5.A) push _object to tls stack
	if(temp < temp_now.tls_stack_depth_threshold)
	{
		// statistics)
		temp_now.tls_stack_depth = temp + 1;
		++temp_now.free;

		// - push to tls_stack
		{
			_pobject->Next = ptls_data->tls_stack;
			ptls_data->tls_stack = _pobject;
		}
	}
	// 5.B) push _object to centeral stack or delete _object
	else
	{
		this->_process_push_to_centeral_stack_or_delete(ptls_data, _pobject);
	}
}

template <class TOBJECT>
void factory::object_pool_tls<TOBJECT>::_process_push_to_centeral_stack_or_delete(sTLS_DATA* _ptls_data, TOBJECT* _pobject)
{
	// statistics)
	--this->m_existing;

	// 1) push '_pobject' to centeral stack
	if (static_cast<int64_t>(this->m_stack_object.size()) < this->m_statistics.now.existing_limits)
	{
		// statistics)
		++_ptls_data->statistics.now.free;
		++_ptls_data->statistics.now.free_stack;

		// - enqueue
		this->m_stack_object.push(_pobject);
	}
	// 2) delete '_pobject'
	else
	{
		// statistics)
		++_ptls_data->statistics.now.free;
		++_ptls_data->statistics.now.free_delete;

		// - destroy object
		this->template process_destroy_object<TOBJECT>(_pobject);
	}

	// 3) get count of redundancy
	auto count_redundancy = _ptls_data->statistics.now.tls_stack_depth - static_cast<int32_t>(this->m_statistics.now.tls_stack_depth_threshold);

	// 4) process garbage collection
	if (count_redundancy > 0)
	{
		this->_process_tls_redundancy(_ptls_data, count_redundancy);
	}
}

template <class TOBJECT>
void factory::object_pool_tls<TOBJECT>::_process_tls_redundancy(sTLS_DATA* _ptls_data, int32_t _count_garbage)
{
	// check) 
	CGASSERT_ERROR(_count_garbage > 0);

	// check) is closed?
	RETURN_IF(this->m_statistics.now.tls_stack_depth_threshold < 0);

	// 1) get first garbage object from tls_stack
	auto pobject_first = _ptls_data->tls_stack;

	// check) is tls_stack empty?
	RETURN_IF(pobject_first == nullptr)

	// 2) set last garbage object
	auto pobject_last = pobject_first;
	int32_t count = 1;

	// 3) detach from tls_stack
	while(count < _count_garbage && pobject_last->Next != nullptr)
	{
		pobject_last = pobject_last->Next;
		++count;
	}
	_ptls_data->tls_stack = pobject_last->Next;

	// 4) push garbages to centeral stack
	this->m_stack_object.push(pobject_first, pobject_last, count);

	// statistics)
	this->m_existing -= count;
	_ptls_data->statistics.now.free_stack += count;
	_ptls_data->statistics.now.tls_stack_depth -= count;
}


}