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
 @brief		���� ũ���� �޸� ��ü��  �Ҵ����ִ� Ǯ�̴�.
 @todo		
 @ref		CGDK.factory::CPoolObject<TOBJECT>, CGDK.factory::CPoolMemory
 @details	\n
 ���� ũ���� �޸� ��ü�� �Ҵ��� �ִ� Ǯ�̴�.
 
 ������ ũ�⸦ �Ҵ� �䱸�ϰ� �Ǹ� �ּ��� �䱸�� ũ�⺸�� ũ�ų� �ּ��� ���� �޸� ��ü�� �Ҵ����ش�.
 �޸� ��� Ǯ�� �پ��� ũ�� ��üǮ(CGDK.factory::CPoolObject<T>)�� ���� Ǯ�� �����Ǿ� �ִ�.
 1K, 2K, 3K, 4K, ..., 64K  �� ���� ũ���� �޸� ��ü�� �Ҵ����ִ� Ǯ�� ���� ������ ũ���� �޸� ��ü�� �Ҵ� �䱸�� ���
 �䱸�� ũ�⸦ �����ϴ� Ǯ���� �޸� ��ü�� �Ҵ��ؼ� �����ش�.
 �� 3.5k�� �޸𸮸� �䱸�� ��� 4k �޸�Ǯ���� �Ҵ��� �شٴ� ���̴�.
 ���� �ʿ� �̻��� �޸𸮰� �Ҵ�� �� �ִ�.(4~7% ����)

 �޸� ��� ũ��� ����
 �޸𸮺��Ǯ�� �Ҵ��ϴ� �޸��� �Ѱ谡 �ִ�. �޸𸮸� � ������ ��� Ǯ�� �����ϴ� ���� ���� �Ҵ��� �� �ִ� �ִ� �޸� ũ�Ⱑ �����ȴ�.
 ���� ��Ȳ�� ���� �޸� ����� ũ�⳪ ���� ���� ���� �ٸ��� �Ʒ��� ���� ������ �� �ִ�.
 (�ڼ��� ���� 'CGDefinitionsPoolMemoryBlock.h'������ �����ٶ�.)

 // - ������ ������ �޸� Ǯ
 * MEMORYPOOLTYPE_UNIFORM_TINY		- 256Byte x64, Max 16KByte
 * MEMORYPOOLTYPE_UNIFORM_NORMAL	- 1KByte x64, Max 64KByte
 * MEMORYPOOLTYPE_UNIFORM_LARGE		- 4KByte x64, Max 256KByte
 * MEMORYPOOLTYPE_UNIFORM_HUGE		- 16KByte x64, Max 1MByte
 
 // - ���� ũ�� �޸� Ǯ
 * MEMORYPOOLTYPE_SCALED_TINY		- 128Bytex8, 1KByte x7, Max 8KByte
 * MEMORYPOOLTYPE_SCALED_NORMAL		- TINY   +  4KByte x14, Max 64KByte
 * MEMORYPOOLTYPE_SCALED_LARGE		- NORMAL + 16KByte x12, Max 256KByte
 * MEMORYPOOLTYPE_SCALED_HUGE		- LARGE  + 16KByte x12, Max 1MByte
 
 ���� �Ҵ��� �� �ִ� �ִ� ũ�⺸�� �� ū �޸𸮸� �䱸�Ѵٸ� Ǯ�� ������� �ʰ� �׳� �ٷ� �����Ҵ��ؼ� �ش�.

 Ǯ���� �޸𸮸� �Ҵ��ϱ� ���ؼ��� _alloc_object('�Ҵ��û ũ��')�� ȣ���ϸ� �ǰ� �Ҵ������Ϸ��� ::free('�޸� ��ü ������')�� ȣ���� �ָ� �ȴ�.

 1. memory_block Block Pool�� atomic�� �̿��� Lock-free�� ������.
     memory_block factory�� Lock free�� �����ϱ� ���� lockfreePush/Pop�� �̿� 
    �Ͽ� �����Ͽ���.
     ���� ���ο� memory_block�� �Ҵ��ϰ� �����ϴ��� CriticalSection��
    ���� Lock�� ������� �ʾ� ���� Allock�� free�� �����ص� �پ �ӵ���
    �����Ѵ�.

 2. �ſ� ���� ������ alloc()�� free()�Լ�
    - alloc()�� ::free()�Լ��� �ſ� ���� ������ �ڵ�� �ۼ��� �Ǿ� �ִ�.
    - alloc()�� ::free()�� new�� delete�� �Ҹ�Ǵ� ����� �ּ�ȭ �ϰ� �ϱ� ����
      ���� ��ŭ ����� �ּ����� code���� ����Ǵ� ���� �����ؼ� ���۵Ǿ���.
    - alloc�� free��� Loop���� �������� ������ alloc_object�� ���� 3~4���� if����
      �� ������ ���ุ���� ����Ǹ� free�Լ��� ���� ��� ���θ�����
      ����ȴ�. 
 
 3. �پ��� ������ memory_block ũ��
 
 4. memory_block factory�� ���ۼ���!!
     memory_block Pool�� alloc()�Լ��� ����Ͽ� �ʿ��� ũ�⸦ �����ϸ� �ش�
    ũ�⺸�� ū memory_block�� �Ҵ����ش�. ���� ��� 1024Byte������ Block��
    �����Ǿ� �ִٸ� 1500Byte�� �Ҵ�䱸�� ��� 2048Byte¥�� memory_block��
    �Ҵ��� �شٴ� ���̴�.

 5. memory_block Pool�� ���ۼ���!!
    1) alloc() - memory_block�� �Ҵ����ִ� �Լ��̴�.
       - �䱸�ϴ� ũ�⺸�� �ణ ū Block Size�� ����� �Ѵ�!
       - �ش��ϴ� ũ���� memory_block�� ����Ǿ� �ִ��� Ȯ���Ѵ�.
          Case A) �� ����� Size�� Block�� Stack�� ������ ��!
                  -> �װ� �׳� �Ҵ��� �ش�.
          Case B) �������� ���� ���!
                  -> ���, ���� ���� �Ҵ��� �ش�.
          * TLS cache�� ����� ��� TLS cache�� ���� ����Ѵ�.

    2) dealloc() - memory_block�� ��ȯ�ϴ� �Լ��̴�.
       - ������ memory_block�� Size�� �´� ����Ҹ� Ȯ���Ѵ�.
          Case A) �ִ� ���ġ�� m_nExistingLimits���� ������ memory_block�� ���ٸ�
                  -> �׳� dealloc()�Ѵ�.
          Case B) �׷��� �ʴٸ� 
                  -> ����ҿ� �״´�.
 
    3) prepare() - �̸� memory_block�� �Ҵ��� ���´�.
       - �̸� �ش� Block�� �Ҵ缭 Pool�� ���� �־� ���� �Լ��̴�.
       - �Ϲ������� Pool�� ó�� ����� �� Pool���� ����� memory_block��
         �������� �ʴ´�. ���� �̸� ���� memory_block�� ������ �뷫 �
         ���������� ���� ������ �����Ѵٸ� Server�� �������� �̸� �Ҵ���
         ���� ���� Server�� �����ϵ��� �ϱ����� ���ȴ�.
    
    4) shrink() - ����� memory_block�� �Ҵ�������.
       - �ʹ� ���� Block�� ����Ǿ� �ִ� ��� ���� �޸� ���� �ҷ�������
         Stack�� Block�� �������� �� ���ȴ�.
       - �Ϲ������� �����ʱ����� ���������� ������ ������ ��� Block��
         ���䰡 �����ߴٰ� �ٽ� �Ҵ������� ��� �ʹ� ���� Block�� �׿�����
         ���� �ִ�. �̷� �� �׿��ִ� Block�� ������ �ִµ� ���ȴ�.
         �Ϲ������� �̷� ���� ���ġ�� ���ؼ� ����ϰ� �ȴ�.
       - �ڵ����� ��꿡 ���� ������ ���差���������Ͽ� �����ϹǷ� Ư���� 
         ȣ���� ���� �ʾƵ� �ȴ�.


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