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
namespace CGDK
{

// defintion) memory_block Object for memory_block factory
class factory::memory_block::memory : 
	public Imemory,
	public Ipoolable<memory_block::memory>,
	public factory::_traits_has_pool
{
public:
			memory(size_t _size);
			memory() noexcept : Imemory(nullptr, 0) {}
	virtual	~memory() noexcept;
private:
	virtual	void	process_dispose() noexcept override	{ this->m_ppool->dealloc(this);}

public:
			object_ptr<pool_t>	m_ppool;
};

inline factory::memory_block::memoryblock_t* factory::memory_block::alloc(int _index CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS)
{
	// check)
	THROW_IF(_index < 0 || _index >= static_cast<int>(this->m_vector_memory_block_pool.size()), throwable::failure(eRESULT::RANGE_ERROR, 0, "out of memory_block factory's block index range"sv));

	// check)
	THROW_IF(this->m_vector_memory_block_pool.at(_index).empty(), throwable::failure(eRESULT::NOT_READY, 0, "memory_block factory is not ready"sv));

	// return)
	return this->m_vector_memory_block_pool.at(_index)->alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
}

class factory::memory_block::memory_general : 
	public Imemory,
	public Ipoolable<memory_general>,
	public factory::_traits_has_pool,
	public factory::_traits_memory
{
public:
			memory_general() noexcept {}
	virtual	~memory_general() noexcept {}
	void prepare(size_t _size)
	{
		// check)
		CGASSERT_ERROR(data_ == nullptr);

		// 1) alloc buffer
		auto pmemory = ::malloc(_size);

		// check)
		THROW_IF(pmemory == nullptr, throwable::failure(eRESULT::BAD_ALLOC));

		set_data(reinterpret_cast<char*>(pmemory));
		set_size(_size);
	}

private:
	virtual	void	process_dispose() noexcept override { SAFE_FREE(data_); this->m_ppool->dealloc(this); }

public:
			object_ptr<pool_extra_t>	m_ppool;
};

inline factory::memory_block::memory_general_t* factory::memory_block::alloc_general(size_t _size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS)
{
	// 1) alloc memory object
	auto pmemory = m_memory_block_extra_pool->alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);

	// 2) create memory
	pmemory->prepare(_size);

	// return)
	return pmemory;
}

inline void factory::memory_block::dealloc(int _index, memoryblock_t* _pblock) noexcept
{
	// check)
	CGASSERT_ERROR(_index >= 0 && _index<static_cast<int>(m_vector_memory_block_pool.size()));

	// check)
	RETURN_IF(_index < 0 || _index>=static_cast<int>(m_vector_memory_block_pool.size()));

	// - get factory
	own_ptr<pool_t>& pfactory = m_vector_memory_block_pool.at(_index);

	// check)
	CGASSERT_ERROR(pfactory.exist());

	// check)
	RETURN_IF(pfactory.empty());

	// return)
	return pfactory->dealloc(_pblock);
}

inline factory::memory_block::memory* _mem_pool_alloc(size_t _size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS)
{
	return factory::memory_block::instance().alloc(SELECT_BLOCK(_size) CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
}

inline void _mem_pool_free(factory::memory_block::memory* _pmemeory) noexcept
{
	_pmemeory->m_ppool->dealloc(_pmemeory);
}

inline object_ptr<Imemory> _mem_alloc(size_t _size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS)
{
	if (_size <= MEMORYPOOL_MAX_SIZE_OF_MEMORY_BLOCK)
		return factory::memory_block::instance().alloc(SELECT_BLOCK(_size) CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
	else
		return factory::memory_block::instance().alloc_general(_size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
}


}