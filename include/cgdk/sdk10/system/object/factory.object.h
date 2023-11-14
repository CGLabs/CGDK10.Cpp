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

  class factory::object
 
*/
//-----------------------------------------------------------------------------
template <class TOBJECT>
// inherited classes)
class factory::object : 
	virtual public				Ifactory
{
// constructor/destructor) 
public:
			object() noexcept;
	virtual	~object() noexcept;

// public) 
public:
	virtual	result_code			destroy() noexcept override;

	virtual	size_t				prepare(size_t /*_amount*/) override { return 0;}
	virtual	size_t				shrink(size_t /*_amount*/) noexcept override { return 0;}
	virtual	void				sustain(eFACTORY_GC_LEVEL _level = eFACTORY_GC_LEVEL::NORMAL) override;
	virtual	void				set_gc_type(eFACTORY_GC_TYPE _gc_type) noexcept override { this->m_statistics.gc_type = _gc_type; }

	[[nodiscard]] virtual size_t object_size() const noexcept override { return sizeof(TOBJECT);}
	[[nodiscard]] virtual size_t stacked_count() const noexcept override { return 0;}
	[[nodiscard]] virtual int64_t existing_limits() const noexcept override { return 0;}

public:
	static object_ptr<object<TOBJECT>> instance(CGNEW_DEBUG_INFO_PARAMETERS);

	#if !defined(_USE_TLS_FACTORY_STATISTICS)
			auto				statistics_on_alloc_create() noexcept { ++this->m_statistics.now.alloc_create; ++this->m_statistics.now.existing; return ++this->m_statistics.now.in_using; }
			void				statistics_on_free_delete() noexcept { ++this->m_statistics.now.free_delete; --this->m_statistics.now.existing; --this->m_statistics.now.in_using; }
	#else
			auto				statistics_on_alloc_create() noexcept { auto ptls_data = this->_get_tls_data(); ++ptls_data->statistics.now.alloc; ++ptls_data->statistics.now.alloc_create; }
			void				statistics_on_free_delete() noexcept { auto ptls_data = this->_get_tls_data(); ++ptls_data->statistics.now.free; ++ptls_data->statistics.now.free_delete; }

			struct sTLS_DATA
			{
				factory::sSTATISTICS_TLS statistics;
			};
			std::mutex			m_cs_vector_tls_data;
			std::vector<sTLS_DATA*> m_vector_tls_data;
	thread_local static sTLS_DATA* m_tls_data;

	[[nodiscard]] sTLS_DATA*	_get_tls_data() noexcept { if (this->m_tls_data == nullptr) this->_alloc_tls_data(); return this->m_tls_data; }
			void				_alloc_tls_data() { this->m_tls_data = new sTLS_DATA(); scoped_lock(this->m_cs_vector_tls_data) this->m_vector_tls_data.push_back(this->m_tls_data); }
	#endif

protected:
	// static)
	static own_ptr<object<TOBJECT>> m_s_pinstance;

private:
	virtual	void				close() noexcept override {}
};

template <class TOBJECT>
own_ptr<factory::object<TOBJECT>> __ATTRIBUTE_PRIORITY(__STATIC_PRIORITY_LEVEL1 + 10) factory::object<TOBJECT>::m_s_pinstance;

#if defined(_USE_TLS_FACTORY_STATISTICS)
template <class TOBJECT>
thread_local typename factory::object<TOBJECT>::sTLS_DATA* factory::object<TOBJECT>::m_tls_data = nullptr;
#endif

template <class TOBJECT>
factory::object<TOBJECT>::object() noexcept
{
	// 1) set default name
#ifdef __cpp_rtti
	this->set_name(_factory_name<TOBJECT>::get_default_name());
#else
	this->set_name(__FUNCTION__);
#endif
	// 2) set factory type
	this->m_statistics.type = _get_default_factory_type<TOBJECT>();
	this->m_statistics.object_type = _get_object_type<TOBJECT>();

	// 주의) 여기서 process_register_factory()를 절대 호출하지 않는다. (무한 순환 루프에 빠질 수 있기 때문에...)
	this->set_gc_type(eFACTORY_GC_TYPE::NO_POOLING);
}

template <class TOBJECT>
factory::object<TOBJECT>::~object() noexcept
{
	// 1) unregister from factory manager
	this->process_unregister_factory();
}

template <class TOBJECT>
result_code factory::object<TOBJECT>::destroy() noexcept
{
	// 2) reset factory instance
	m_s_pinstance.reset();
	
	// return) 
	return result_code(eRESULT::SUCCESS);
}

template <class TOBJECT>
void factory::object<TOBJECT>::sustain(eFACTORY_GC_LEVEL /*_level*/)
{
#if defined(_USE_TLS_FACTORY_STATISTICS)
	// 1) apply local data
	scoped_lock(m_cs_vector_tls_data)
	{
		// - prepare
		this->m_statistics.now.tls_stack_depth = 0;
		this->m_statistics.now.tls_stack_depth_threshold = 0;

		// - update
		for (auto iter : m_vector_tls_data)
		{
			iter->statistics.update_statistics(this->m_statistics.now, this->gc_type());
		}
	}
#endif
}

template <class TOBJECT>
inline object_ptr<factory::object<TOBJECT>> factory::object<TOBJECT>::instance(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// check) create instance if not created
	if (m_s_pinstance.empty())
	{
		static lockable<> cs_create;

		scoped_lock(cs_create)
		{
			// check) return if aleady created
			RETURN_IF(m_s_pinstance.exist(), m_s_pinstance);

			// 1) create instance 
			m_s_pinstance = _make_own_raw<object<TOBJECT>>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);

			// 2) register to factory manager (MUST Here!)
			m_s_pinstance->process_register_factory();
		}
	}

	// return) 
	return m_s_pinstance;
}


}