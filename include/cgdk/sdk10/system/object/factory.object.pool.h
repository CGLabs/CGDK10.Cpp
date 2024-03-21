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
 @brief		��ü�� �Ҵ�� ������ ȿ���� ����Ű�� ���� ��ü Ǯ
 @todo		
 @ref		Ipoolable, Npoolable
 @details	\n
 ��ü�� ���� �Ҵ�� ������ ȿ������ ���̱� ���� Ǯ ��ü�̴�.
 ���������� �������� �����ϱ� ������ �ſ� ������ �����Ѵ�.

 Ǯ�� ��� ��ü�� �Ƿ��� �ݵ�� Ipoolable<TOBJECT>�� ��ӹ��� Ŭ��������Ѵ�.

 Ǯ�� �Ҵ��� �䱸�ϸ� ���� ������ ���ø� ���� �˻��Ѵ�. ���� ���ÿ� ��ü�� ���� ��� �װ��� �Ҵ����ش�.
 ���� ���ÿ� ��ü�� �ϳ��� ���ٸ� ���� �����ؼ� �Ҵ����ش�.
 �Ҵ����� ��ü�� �ٽ� ���ƿ��� �Ǹ� ������ ���ÿ� ������ ���Ҵٰ� ���� �Ҵ� �䱸�� �Ҵ����ش�.
 �ٸ� �ʹ� ���� ��ü�� ������ ���ÿ� ������ ��� �������� ������ ������ ������ �����Ѵ�.

 Ǯ���� ��ü�� �Ҵ��ϱ� ���ؼ��� alloc()�Լ��� ȣ���ϸ� �Ҵ� �ߴ� ��ü�� �����ϱ� ���ؼ��� free()�Լ��� ����Ѵ�.
 prepare()�Լ��� ����ϸ� �̸� ��ü�� �����س��� ���� �ִ�.
 shrink()�Լ��� ����ϸ� �׿��ִ� ���������� �Ҵ� ������ ���� �ִ�.

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
		// 1) �ϴ� ���� �����ȴ�.
		auto pobject = this->create_object(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);

		// 2) pool�� setting�Ѵ�. (ó���������� pool�� reference Counting�� 1������Ű�� �ȴ�.)
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

		// 2) increase reference count (m_ppool�� setting���� ������ ��ü������ ������Ų��.)
		this->add_ref();

		// return) ����!!
		return pobject;
	}

// framework) 
private:
	// 3) ��� ��ü Stack
			LOCKFREE_SELF_STACK<TOBJECT*> m_stack_object;

	// 4) Pool Sustainment�� ���� ������
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
	// 1) �ִ� ���� ������ -1�� �Ѵ�.
	this->m_statistics.now.existing_limits = -1;

	// 2) free stacked object
	TOBJECT* pobject;
	while ((pobject = this->m_stack_object.pop()) != nullptr)
	{
		// - ��ü�� �ı��Ѵ�.
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
	// check) prepare�� ���� 0���ٴ� Ŀ���Ѵ�.
	CGASSERT(_amount > 0, 0);

	// check) 0���� �۰ų� ������ prepare�Ҳ� ������ �׳� ������.
	RETURN_IF(_amount <= 0, 0);

	// 1) �ӽ÷� ����� List�� �Ҵ�޴´�.
	std::vector<TOBJECT*> vector_created;

	// 2) Reserve�Ѵ�.
	vector_created.reserve(_amount);

	try
	{
		// 3) prepare ����ŭ Loop�� ���鼭 �����Ѵ�.
		for(; _amount>0; --_amount)
		{
			// declare) ���� �����Ѵ�.
			auto pcreate = this->template process_create_object<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_INITIAL);

			// - ������ ��ü�� �ӽ� ���ۿ� ¤�� �ִ´�.
			vector_created.emplace_back(pcreate);
		}
	}
	// exception) 
	catch(...)
	{
		// - �̹� ������ �͵鸸 prepare�ϵ��� �Ѵ�.
	}

	// declare)
	auto size_created = static_cast<int64_t>(vector_created.size());

	// 4) ��հ��� �����Ѵ�.
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

	// 1) stack�Ǿ� �ִ� object�� tempShrink��ŭ �����.
	for(; count_shrink < _amount; ++count_shrink)
	{
		// - Pop�� �����Ѵ�.
		auto pobject = this->m_stack_object.pop();

		// check) pobject�� nullptr�̸� �ȵȴ�.
		BREAK_IF(pobject == nullptr);

		// - Object�� destroy�Ѵ�.
		this->template process_destroy_object<TOBJECT>(pobject);
	}

	// statistics)
	this->statistics_on_shrink(count_shrink);

	// 4) ��հ��� ����.
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

		// - ������� ������ �ִ��Ҵ�ġ�� �Ѿ ��� �����Ѵ�.
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

	// 2) �ִ� �Ѱ� stack������ stack�� memory Block������ ������ �Ҵ������Ѵ�.
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