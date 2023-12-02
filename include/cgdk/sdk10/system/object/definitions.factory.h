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
//
// definitions
//
//-----------------------------------------------------------------------------
#define _USE_TLS_FACTORY_STATISTICS

//template<class T> using default_factory_pool_t = class factory::object_pool<T>;
template<class T> using default_factory_pool_t = class factory::object_pool_tls<T>;


//-----------------------------------------------------------------------------
//
// factory 
//
//-----------------------------------------------------------------------------
enum class eFACTORY_TYPE : int32_t
{
	DEFAULT				 = 0,	// default
	POOL_MEMORYBLOCK	 = 1,	// memory block pool
	POOL_SYSTEM			 = 2,	// pool allocator created by system
	POOL_USER			 = 3,	// pool allocator created by user
	ALLOCATOR_SYSTEM	 = 4,	// allocator created by system
	ALLOCATOR_USER		 = 5,	// allocator created by user
	MAX
};
template<class TCHAR_T> std::basic_string_view<TCHAR_T> to_string(eFACTORY_TYPE _type);

enum class eFACTORY_GC_LEVEL : int32_t
{
	NORMAL		 = 0,
	HEAVY		 = 1,
	EXCESS_ALL	 = 2,
	STACKED_ALL	 = 3
};

enum class eFACTORY_GC_TYPE : int32_t
{
	NO_POOLING = 0,
	POOLING = 1,
	POOLING_NO_GC = 3,
	TLS_POOLING = 5,
	TLS_POOLING_NO_GC = 7,

	DEFAULT = TLS_POOLING
};
template<class TCHAR_T> std::basic_string_view<TCHAR_T> to_string(eFACTORY_GC_TYPE _type);

enum eFACTORY_SHRINK : size_t
{
	EXCEED	 = SIZE_MAX -1,
	ALL		 = SIZE_MAX -2,
};

namespace statistics
{
	struct unit_factory
	{
		chrono::tick::time_point tick_snap = chrono::tick::time_point::max();// 저장된 시간(tick으로..)
		int64_t					existing_limits = INT64_MAX;	// 할당되는 최대 객체의 제한 ( 이제 한 값 이상의 객체가 생산되어 있을 경우 ::free시 바로 delete를 하게 된다.)
		int64_t					tls_stack_depth_threshold = 0;//
	#if defined(_USE_TLS_FACTORY_STATISTICS)
		uint64_t				alloc_stack = 0;				// 할당시 Stack에 저장된 객체를 재활용해서 할당해 준 횟수 (비율이 높을 수록 좋다.)
		uint64_t				alloc_stack_tls = 0;			// 할당시 tls stack에 저장된 객체를 재활용해서 할당해 준 횟수 (비율이 높을 수록 좋다.)
		uint64_t				alloc_create = 0;				// 할당시 새로 생성해 할당해 준 횟수(적을 수록 좋다.)
		uint64_t				free_stack = 0;					// 할당해제 시 Stack에 저장된 횟수. (비율이 높을 수록 좋다.)
		uint64_t				free_stack_tls = 0;				// 할당시 tls stack에 저장된 객체를 재활용해서 할당해 준 횟수 (비율이 높을 수록 좋다.)
		uint64_t				free_delete = 0;				// 할당해제 시 즉시 지워진 횟수.(적을 수록 좋다.)
		int64_t					existing = 0;					// 현재 생성되어 있는 총 갯수 (할당된 갯수 + 스택된 갯수)
		int64_t					tls_stack_depth = 0;
		int64_t					in_using = 0;					// 현재 할당 된 총 객체의 갯수
		uint64_t				extra = 0;						// extra
	#else
		std::atomic<uint64_t>	alloc_stack = 0;				// 할당시 Stack에 저장된 객체를 재활용해서 할당해 준 횟수 (비율이 높을 수록 좋다.)
		std::atomic<uint64_t>	alloc_stack_tls = 0;			// 할당시 tls stack에 저장된 객체를 재활용해서 할당해 준 횟수 (비율이 높을 수록 좋다.)
		std::atomic<uint64_t>	alloc_create = 0;				// 할당시 새로 생성해 할당해 준 횟수(적을 수록 좋다.)
		std::atomic<uint64_t>	free_stack = 0;					// 할당해제 시 Stack에 저장된 횟수. (비율이 높을 수록 좋다.)
		std::atomic<uint64_t>	free_delete = 0;				// 할당해제 시 즉시 지워진 횟수.(적을 수록 좋다.)
		std::atomic<uint64_t>	free_stack_tls = 0;				// 할당시 tls stack에 저장된 객체를 재활용해서 할당해 준 횟수 (비율이 높을 수록 좋다.)
		std::atomic<int64_t>	existing = 0;					// 현재 생성되어 있는 총 갯수 (할당된 갯수 + 스택된 갯수)
		std::atomic<int64_t>	tls_stack_depth = 0;
		std::atomic<int64_t>	in_using = 0;					// 현재 할당 된 총 객체의 갯수
		std::atomic<uint64_t>	extra = 0;						// extra
	#endif
		unit_factory() noexcept;
		unit_factory(const unit_factory& rhs) noexcept;
		unit_factory& operator = (const unit_factory& rhs) noexcept;
		void reset() noexcept;
	};

	struct unit_factory_snap
	{
		chrono::tick::time_point tick_snap = chrono::tick::time_point::max(); // 저장된 시간(tick으로..)
		int64_t					existing_limits = INT64_MAX;	// 할당되는 최대 객체의 제한 ( 이제 한 값 이상의 객체가 생산되어 있을 경우 ::free시 바로 delete를 하게 된다.)
		int64_t					tls_stack_depth_threshold = 0;		// 
		uint64_t				alloc_stack = 0;				// 할당시 Stack에 저장된 객체를 재활용해서 할당해 준 횟수 (비율이 높을 수록 좋다.)
		uint64_t				alloc_stack_tls = 0;			// 할당시 tls stack에 저장된 객체를 재활용해서 할당해 준 횟수 (비율이 높을 수록 좋다.)
		uint64_t				alloc_create = 0;				// 할당시 새로 생성해 할당해 준 횟수(적을 수록 좋다.)
		uint64_t				free_stack = 0;					// 할당해제 시 Stack에 저장된 횟수. (비율이 높을 수록 좋다.)
		uint64_t				free_stack_tls = 0;				// 할당해제 시 Stack에 저장된 횟수. (비율이 높을 수록 좋다.)
		uint64_t				free_delete = 0;				// 할당해제 시 즉시 지워진 횟수.(적을 수록 좋다.)
		int64_t					existing = 0;					// 현재 생성되어 있는 총 갯수 (할당된 갯수 + 스택된 갯수)
		int64_t					tls_stack_depth = 0;
		int64_t					in_using = 0;					// 현재 할당 된 총 객체의 갯수
		uint64_t				extra = 0;						// extra

		unit_factory_snap& operator = (const unit_factory& rhs) noexcept;
		void reset() noexcept;
	};

	struct unit_factory_tls
	{
		int32_t					tls_stack_depth = 0;
		int32_t					alloc = 0;
		int32_t					tls_stack_depth_threshold = 0;
		int32_t					free = 0;

		int32_t					alloc_stack = 0;
		int32_t					alloc_create = 0;
		int32_t					free_stack = 0;
		int32_t					free_delete = 0;

		void					statistics_on_alloc_stack() noexcept { ++alloc; ++alloc_stack; }
		void					statistics_on_alloc_stack_tls() noexcept { ++alloc; --tls_stack_depth; }
		void					statistics_on_alloc_create() noexcept { ++alloc; ++alloc_create; }
		void					statistics_on_prepare(uint32_t _count) noexcept { alloc += _count; alloc_create += _count; free += _count; free_stack += _count; }
		void					statistics_on_shrink(uint32_t _count) noexcept { free_stack -= _count; free_delete += _count; }
	};

	struct factory
	{
		unit_factory			now;

		std::string				name;
		eFACTORY_TYPE			type = eFACTORY_TYPE::DEFAULT;
		eFACTORY_GC_TYPE		gc_type = eFACTORY_GC_TYPE{0x400000};
		eOBJECT_TYPE			object_type = eOBJECT_TYPE::NOT_DEFINED;
		int						id = 0;
	};
}

namespace factory
{
	std::string _get_name_from_rtti(std::string_view _rtti_name) noexcept;
	template<class T> class _factory_name { public: static std::string get_default_name() noexcept { return _get_name_from_rtti(std::string_view(typeid(T).name()));} };
	template<class X> class _factory_name<CGDK::POOLABLE<X>> { public: static std::string get_default_name() noexcept { return _get_name_from_rtti(std::string_view(typeid(X).name()));} };
	
	template<class T> std::enable_if_t<!std::is_base_of_v<_traits_system, T>, eFACTORY_TYPE> _get_default_factory_type() { return eFACTORY_TYPE::ALLOCATOR_USER; }
	template<class T> std::enable_if_t<std::is_base_of_v<_traits_system, T>, eFACTORY_TYPE> _get_default_factory_type() { return eFACTORY_TYPE::ALLOCATOR_SYSTEM; }

	template<class T> std::enable_if_t<!std::is_base_of_v<_traits_system, T> && !std::is_base_of_v<_traits_memory, T>, eFACTORY_TYPE> _get_default_pool_factory_type() { return eFACTORY_TYPE::POOL_USER; }
	template<class T> std::enable_if_t<std::is_base_of_v<_traits_system, T>, eFACTORY_TYPE> _get_default_pool_factory_type() { return eFACTORY_TYPE::POOL_SYSTEM; }
	template<class T> std::enable_if_t<std::is_base_of_v<_traits_memory, T>, eFACTORY_TYPE> _get_default_pool_factory_type() { return eFACTORY_TYPE::POOL_MEMORYBLOCK; }

	struct sSTATISTICS_TLS
	{
	public:
		statistics::unit_factory_tls now;
		statistics::unit_factory_tls old;
	public:
		bool update_statistics(statistics::unit_factory& _dest, eFACTORY_GC_TYPE _gc_type) noexcept;
	};
}


}