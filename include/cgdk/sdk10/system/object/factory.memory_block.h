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

 @class		memory_block
 @brief		임의 크기의 메모리 객체를  할당해주는 풀이다.
 @todo		
 @ref		CGDK.factory::CPoolObject<TOBJECT>, CGDK.factory::CPoolMemory
 @details	\n
 임의 크기의 메모리 객체를 할당해 주는 풀이다.
 
 임의의 크기를 할당 요구하게 되면 최소한 요구한 크기보다 크거나 최소한 같은 메모리 객체를 할당해준다.
 메모리 블록 풀은 다양한 크기 객체풀(CGDK.factory::CPoolObject<T>)를 묶은 풀로 구성되어 있다.
 1K, 2K, 3K, 4K, ..., 64K  등 여러 크기의 메모리 객체를 할당해주는 풀을 묶어 임의의 크기의 메모리 객체를 할당 요구할 경우
 요구한 크기를 만족하는 풀에서 메모리 객체를 할당해서 돌려준다.
 즉 3.5k의 메모리를 요구할 경우 4k 메모리풀에서 할당해 준다는 것이다.
 따라서 필요 이상의 메모리가 할당될 수 있다.(4~7% 정도)

 메모리 블록 크기와 설정
 메모리블록풀은 할당하는 메모리의 한계가 있다. 메모리를 어떤 단위로 몇개의 풀로 구성하는 가에 따라 할당할 수 있는 최대 메모리 크기가 결정된다.
 따라서 상황에 따라 메모리 블록의 크기나 갯수 분포 등을 다르게 아래와 같이 설정할 수 있다.
 (자세한 것은 'CGDefinitionsPoolMemoryBlock.h'파일을 참조바람.)

 // - 단일한 간격의 메모리 풀
 * MEMORYPOOLTYPE_UNIFORM_TINY		- 256Byte x64, Max 16KByte
 * MEMORYPOOLTYPE_UNIFORM_NORMAL	- 1KByte x64, Max 64KByte
 * MEMORYPOOLTYPE_UNIFORM_LARGE		- 4KByte x64, Max 256KByte
 * MEMORYPOOLTYPE_UNIFORM_HUGE		- 16KByte x64, Max 1MByte
 
 // - 가변 크기 메모리 풀
 * MEMORYPOOLTYPE_SCALED_TINY		- 128Bytex8, 1KByte x7, Max 8KByte
 * MEMORYPOOLTYPE_SCALED_NORMAL		- TINY   +  4KByte x14, Max 64KByte
 * MEMORYPOOLTYPE_SCALED_LARGE		- NORMAL + 16KByte x12, Max 256KByte
 * MEMORYPOOLTYPE_SCALED_HUGE		- LARGE  + 16KByte x12, Max 1MByte
 
 만약 할당할 수 있는 최대 크기보다 더 큰 메모리를 요구한다면 풀을 사용하지 않고 그냥 바로 동적할당해서 준다.

 풀에서 메모리를 할당하기 위해서는 _alloc_object('할당요청 크기')를 호출하면 되고 할당해제하려면 ::free('메모리 객체 포인터')를 호출해 주면 된다.

 1. memory_block Block Pool은 atomic을 이용한 Lock-free로 동작함.
     memory_block factory은 Lock free로 구현하기 위해 lockfreePush/Pop을 이용 
    하여 구현하였다.
     따라서 새로운 memory_block을 할당하고 해지하더라도 CriticalSection과
    같은 Lock은 수행되지 않아 잦은 Allock와 free를 수행해도 뛰어난 속도를
    보장한다.

 2. 매우 작은 부하의 alloc()와 free()함수
    - alloc()와 ::free()함수는 매우 적은 부하의 코드로 작성이 되어 있다.
    - alloc()와 ::free()가 new나 delete에 소모되는 비용을 최소화 하게 하기 위한
      것인 만큼 수행상에 최소한의 code만이 수행되는 것을 염두해서 제작되었다.
    - alloc와 free모두 Loop문은 존재하지 않으며 alloc_object는 단지 3~4번의 if문과
      몇 라인의 실행만으로 수행되며 free함수는 단지 몇개의 라인만으로
      수행된다. 
 
 3. 다양한 형태의 memory_block 크기
 
 4. memory_block factory의 동작설명!!
     memory_block Pool에 alloc()함수를 사용하여 필요한 크기를 설정하면 해당
    크기보다 큰 memory_block을 할당해준다. 예를 들어 1024Byte단위로 Block이
    설정되어 있다면 1500Byte를 할당요구할 경우 2048Byte짜리 memory_block을
    할당해 준다는 것이다.

 5. memory_block Pool의 동작설명!!
    1) alloc() - memory_block을 할당해주는 함수이다.
       - 요구하는 크기보다 약간 큰 Block Size를 계산을 한다!
       - 해당하는 크기의 memory_block이 저장되어 있는지 확인한다.
          Case A) 그 계산한 Size의 Block가 Stack에 존재할 때!
                  -> 그걸 그냥 할당해 준다.
          Case B) 존재하지 않을 경우!
                  -> 즉시, 새로 만들어서 할당해 준다.
          * TLS cache를 사용할 경우 TLS cache를 먼저 사용한다.

    2) dealloc() - memory_block을 반환하는 함수이다.
       - 돌려진 memory_block의 Size에 맞는 저장소를 확인한다.
          Case A) 최대 허용치인 m_nExistingLimits보다 생성된 memory_block이 많다면
                  -> 그냥 dealloc()한다.
          Case B) 그렇지 않다면 
                  -> 저장소에 쌓는다.
 
    3) prepare() - 미리 memory_block을 할당해 놓는다.
       - 미리 해당 Block을 할당서 Pool에 집어 넣어 놓는 함수이다.
       - 일반적으로 Pool이 처음 실행될 때 Pool에는 저장된 memory_block이
         존재하지 않는다. 만약 미리 사용될 memory_block의 갯수가 대략 몇개
         정도인지에 대한 정보가 존재한다면 Server의 수행전에 미리 할당해
         놓은 다음 Server를 수행하도록 하기위해 사용된다.
    
    4) shrink() - 저장된 memory_block을 할당해제함.
       - 너무 많은 Block이 저장되어 있는 경우 많은 메모리 낭비를 불러옴으로
         Stack된 Block을 지워버릴 때 사용된다.
       - 일반적으로 접속초기라든지 순간적으로 접속이 폭주할 경우 Block의
         수요가 급증했다가 다시 할당해제될 경우 너무 많은 Block이 쌓여있을
         수가 있다. 이럴 때 쌓여있는 Block을 제거해 주는데 사용된다.
         일반적으로 이런 것은 통계치에 의해서 사용하게 된다.
       - 자동적인 계산에 의해 최적의 저장량만을생성하여 관리하므로 특별히 
         호출해 주지 않아도 된다.


*/
//-----------------------------------------------------------------------------
class factory::memory_block
{
// constructor/destructor)
protected:
			memory_block();
	virtual ~memory_block() noexcept;

// definition)
public:
	class memory;
	class memory_general;
	using memoryblock_t = memory;
	using memory_general_t = memory_general;
	class memoryblock_pool;

	using pool_t = default_factory_pool_t<memoryblock_t>;
	using pool_extra_t = default_factory_pool_t<memory_general_t>;

	struct INITIALIZE_PARAMETER
	{
		int type = MEMORYPOOL_MEMORYPOOL_TYPE;
		size_t max = MEMORYPOOL_NUMBER_OF_BLOCK;
		size_t size = MEMORYPOOL_SIZE_OF_BLOCK;
	};

// public) 
public:
			memoryblock_t*		alloc (int _index CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
			memory_general_t*	alloc_general (size_t _size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
			void				dealloc (int _index, memoryblock_t* _pblock) noexcept;

			size_t				prepare (int _index, size_t _amount);
			size_t				shrink (int _index, size_t _amount) noexcept;

	[[nodiscard]] size_t		object_size (int _index) const noexcept;
	[[nodiscard]] size_t		stacked_count (int _index) const noexcept;
	[[nodiscard]] int64_t		existing_limits (int _index) const noexcept;

	[[nodiscard]] int64_t		statistics_allocated_stack (int _index) const noexcept;
	[[nodiscard]] int64_t		statistics_allocated_create (int _index) const noexcept;
	[[nodiscard]] int64_t		statistics_allocated (int _index) const noexcept;
	[[nodiscard]] int64_t		statistics_freed_stack (int _index) const noexcept;
	[[nodiscard]] int64_t		statistics_freed_delete (int _index) const noexcept;
	[[nodiscard]] int64_t		statistics_freed (int _index) const noexcept;
	[[nodiscard]] int64_t		statistics_existing (int _index) const noexcept;
	[[nodiscard]] int64_t		statistics_in_using (int _index) const noexcept;
	[[nodiscard]] size_t		size() const noexcept { return this->m_vector_memory_block_pool.size(); }

	static	memory_block&		instance() noexcept { return m_s_instance_pool;}
	static	void				detach() noexcept;

// implementation)
private:
	static	result_code			initialize() { INITIALIZE_PARAMETER parameter; return initialize(parameter); }
	static	result_code			initialize(const INITIALIZE_PARAMETER& _parameter);
			result_code			destroy() noexcept;

			void				process_create_as_scaled_tiny();
			void				process_create_as_scaled_normal();
			void				process_create_as_scaled_large();
			void				process_create_as_scaled_huge();
			void				process_create_general_size_pool();

private:
			static_vector<own_ptr<pool_t>,64> m_vector_memory_block_pool;
			own_ptr<pool_extra_t> m_memory_block_extra_pool;

	// static)
	static	memory_block		m_s_instance_pool;
};

}

#include "cgdk/sdk10/system/object/factory.memory_block.inl"