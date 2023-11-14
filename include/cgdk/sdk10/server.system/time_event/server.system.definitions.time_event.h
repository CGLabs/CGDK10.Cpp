//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Event Classes                            *
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
//----------------------------------------------------------------------------
//
//
//  Definitions for Event Classes
//
//
//----------------------------------------------------------------------------
namespace time_event
{
	const int infinite = -1;

	enum class eSETTER : uint32_t
	{
		NONE		 = 0,

		SYSTEM		 = 1,
		LOCAL		 = 2,	
		ADMIN		 = 3,

		MAX
	};

	enum class eSTATE : uint32_t
	{
		NONE		 = 0,

		WAIT		 = 1,
		RUN			 = 2,
		DONE		 = 3,

		MAX
	};

	enum class eTYPE : uint32_t
	{
		NONE		 = 0,

		ONCE		 = 1,		// 1
		ITERATION,				// 2
		START_END,				// 3
		START_ITERATION_END,	// 4
		ENTITY,					// 5
		CUSTOM,					// 6

		MAX
	};
		
	struct sEVENT_SETTING
	{
	public:
		static_string<MAX_NAME_LENGTH> name;
		eTYPE						type = eTYPE::NONE;
		uint64_t					option = 0;

		chrono::time::utc::time_point time_execute;
		chrono::time::duration		time_interval = chrono::time::duration::zero();
		int							count_times = 0;

	public:
		sEVENT_SETTING() noexcept {}
		sEVENT_SETTING(const std::string_view _name, eTYPE _type, uint64_t _option, chrono::time::utc::time_point _time_execute, chrono::time::duration _time_interval = chrono::time::duration::zero(), int _count_times = 0) noexcept :
			name{ _name },
			type{ _type },
			option{ _option },
			time_execute{ _time_execute },
			time_interval{ _time_interval },
			count_times{ _count_times }
		{
		}
		sEVENT_SETTING(const sEVENT_SETTING& _copy) noexcept;
		sEVENT_SETTING& operator = (const sEVENT_SETTING& _rhs) noexcept;
	};

	struct sEVENT_STATUS
	{
	public:
		uint64_t					id = 0;
		std::atomic<eSTATE>			state = eSTATE::DONE;

		chrono::time::utc::time_point time_last_executed;
		chrono::time::utc::time_point time_next;

		std::atomic<int64_t>		count_remained;

	public:
		sEVENT_STATUS() noexcept {}
		sEVENT_STATUS(const sEVENT_STATUS& _copy) noexcept;
		sEVENT_STATUS& operator = (const sEVENT_STATUS& _rhs) noexcept;
		void reset() noexcept;
	};

	struct sENTITY_SETTING
	{
	public:
		static_string<MAX_NAME_LENGTH> name;
		uint64_t					type = 0;

		eSETTER						setter = eSETTER::NONE;
		int							level = 0;

	public:
		sENTITY_SETTING() noexcept {}
		sENTITY_SETTING(uint64_t _type) noexcept : type (_type) {}
		sENTITY_SETTING(const sENTITY_SETTING& _copy) noexcept;
		sENTITY_SETTING& operator = (const sENTITY_SETTING& _rhs) noexcept;
	};

	struct sENTITY_STATUS
	{
	public:
		uint64_t					id = 0;
		std::atomic<eSTATE>			state = eSTATE::NONE;

		chrono::time::utc::time_point time_setup;
		chrono::time::utc::time_point time_last_try;
		chrono::time::utc::time_point time_last_succeeded;
		chrono::time::utc::time_point time_last_failed;
		chrono::time::utc::time_point time_next;

		std::atomic<int64_t>		count_try = 0;
		std::atomic<int64_t>		count_succeeded = 0;
		std::atomic<int64_t>		count_failed = 0;

	public:
		sENTITY_STATUS() noexcept {}
		sENTITY_STATUS(const sENTITY_STATUS& _copy) noexcept;
		sENTITY_STATUS& operator = (const sENTITY_STATUS& _rhs) noexcept;

		void						reset() noexcept;
		void						reset_next_time() noexcept		{ time_last_failed = chrono::time::utc::time_point(chrono::time::duration::zero()); }

		void						statistics_try() noexcept		{ ++count_try; time_last_try = chrono::time::utc::now();}
		void						statistics_succeeded() noexcept	{ ++count_succeeded; time_last_succeeded = chrono::time::utc::now();}
		void						statistics_failed() noexcept	{ ++count_failed; time_last_failed = chrono::time::utc::now();}
	};
}

template<class TTYPE = char> std::basic_string_view<TTYPE>	to_string(time_event::eSETTER _setter, bool _upper_case = true) noexcept;
template<class TTYPE = char> std::basic_string_view<TTYPE>	to_string(time_event::eSTATE _state, bool _upper_case = true) noexcept;
template<class TTYPE = char> std::basic_string_view<TTYPE>	to_string(time_event::eTYPE _type, bool _upper_case = true) noexcept;
using EVENT_FUNCTION = std::function<result_code(chrono::time::utc::time_point)>;


}
