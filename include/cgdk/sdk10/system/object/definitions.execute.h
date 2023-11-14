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
template<class T> struct is_lambda_functor_type : std::false_type {};
template<class T> struct is_lambda_functor_type<std::function<T>> : std::true_type {};
template<class T> struct is_functor_type
{
	static const bool value = is_lambda_functor_type<std::decay_t<T>>::value || std::is_function<std::remove_pointer_t<std::decay_t<T>>>::value;
};


#define	CGEXECUTOR_AUTO		static_cast<size_t>(-1)
#define	CGEXECUTOR_NOTHREAD	0

// 1) windows system
#if defined(_WIN32)
	#define	DEFAULT_THREAD_COUNT_PER_PROCESSOR		2		// thread per processor
	#define	DEFAULT_BASE_THREAD_COUNT				2		// base thread count

// 2) android system
#elif defined(__ANDROID__)
	#define	DEFAULT_THREAD_COUNT_PER_PROCESSOR		1		// thread per processor
	#define	DEFAULT_BASE_THREAD_COUNT				2		// base thread count

// 3) linux
#elif defined(__linux__)
	#define	DEFAULT_THREAD_COUNT_PER_PROCESSOR		2		// thread per processor
	#define	DEFAULT_BASE_THREAD_COUNT				2		// base thread count

// 4) others
#else
	#define	DEFAULT_THREAD_COUNT_PER_PROCESSOR		2		// thread per processor
	#define	DEFAULT_BASE_THREAD_COUNT				2		// base thread count
#endif


//-----------------------------------------------------------------------------
//
// For exception
//
//-----------------------------------------------------------------------------
// 1) dump context
enum class eDUMP_CONTEXT
{
	MINI,
	DETAIL,
	FULL,

	DEFAULT	 = MINI
};

// 2) 
#define	DEFAULT_MAX_DUMP_LIMIT	4096

// 5) Dump Info 
struct DUMP_INFO
{
	// 1) ip
	uint64_t					id;

	// 2) 발생한 Thread
    uint32_t					thread_id;

	// 3) occure datetime 
	chrono::time::utc::time_point time_occure_first;
	chrono::time::utc::time_point time_occure_last;

	// 4) occure times
	size_t						count_times;

	// 5) 발행한 내용
#if defined(_MSC_VER)
	EXCEPTION_RECORD			sExceptionRecords;
	CONTEXT						sContextRecord;
#endif

	// 6) dump file name
	std::string					dump_filename;

public:
#if defined(_MSC_VER)
	DUMP_INFO() noexcept : id(0), thread_id(0), time_occure_first(), time_occure_last(), count_times(0), sExceptionRecords(), sContextRecord(), dump_filename() {}
#else
	DUMP_INFO() noexcept : id(0), thread_id(0), time_occure_first(), time_occure_last(), count_times(0), dump_filename() {}
#endif
};

// 6) Message for DUMP Notification
struct sMESSAGE_DUMP : public sMESSAGE
{
public:
	sMESSAGE_DUMP()  noexcept	{}
	sMESSAGE_DUMP(const DUMP_INFO& _data) noexcept : sMESSAGE(eMESSAGE::DUMP), dump_info(_data)	{}

public:
	DUMP_INFO					dump_info;
};


//-----------------------------------------------------------------------------
//
// thread
//
//-----------------------------------------------------------------------------
// 1) Thread ID
#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2012
	using THREAD_ID = std::thread::native_handle_type;
#else
	using THREAD_ID = THREAD_HANDLE;
#endif

// 1) Thread Info
namespace statistics
{

struct thread
{
	THREAD_ID			id_thread = 0;			// thread id

	uint64_t			count_executed = 0;		// executed count
	uint64_t			count_error = 0;		// error count

	chrono::tick::time_point tick_last_execute = chrono::tick::duration::zero();	// tick last executed
	bool				is_executing = false;	// is processing execution now?
};


}

//-----------------------------------------------------------------------------
//
// executor
//
//-----------------------------------------------------------------------------
enum class eEXECUTOR_TYPE : int32_t
{
	DEFAULT = 0,	// default value
	SYSTEM = 1,		// system scheduler
	USER = 2,		// user scheduler
	MAX
};

// 2) to_string functions
template <class T>	[[nodiscard]] std::basic_string_view<T>	to_string(eEXECUTOR_TYPE _character_set) noexcept;
template <>			[[nodiscard]] std::string_view			to_string<char>(eEXECUTOR_TYPE _character_set) noexcept;
template <>			[[nodiscard]] std::wstring_view			to_string<wchar_t>(eEXECUTOR_TYPE _character_set) noexcept;

namespace statistics
{
	struct unit_executor
	{
		chrono::tick::time_point tick_snap = chrono::tick::time_point::max();
		int						thread_count = 0;
		std::atomic<int64_t>	count_execute = 0;

		unit_executor() noexcept;
		unit_executor(const unit_executor& rhs) noexcept;
		unit_executor& operator = (const unit_executor& rhs) noexcept;
		void reset() noexcept;
	};

	struct unit_executor_snap
	{
		chrono::tick::time_point tick_snap = chrono::tick::time_point::max();
		int						thread_count = 0;
		int64_t					count_execute = 0;

		unit_executor_snap& operator = (const unit_executor& _copy) noexcept;
		void reset() noexcept;
	};

	struct executor
	{
	public:
		std::string				name;
		uint64_t				id = 0;
		eEXECUTOR_TYPE			type = eEXECUTOR_TYPE::USER;

		unit_executor			now;

	public:
		executor() noexcept {}
		executor(const executor& _rhs) noexcept : name(_rhs.name), id(_rhs.id), now(_rhs.now) {}
		executor& operator=(const executor& _rhs) noexcept { name = _rhs.name; id = _rhs.id; now = _rhs.now; return *this; }
	};
}


//-----------------------------------------------------------------------------
//
// executable
//
//-----------------------------------------------------------------------------
#if defined(_WIN32)
class EXECUTABLE_NODE : public OVERLAPPED
{
public:
	EXECUTABLE_NODE() noexcept : OVERLAPPED() { Internal = 0; InternalHigh = 0; Pointer=nullptr; hEvent = NULL;}
};

#else
class EXECUTABLE_NODE
{
public:
	EXECUTABLE_NODE()  noexcept {}
};
#endif


}