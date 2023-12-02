//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            Server Log Classes                             *
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
// log_filter
//
// 1. log_filter��~
//    ������ Log�� ����ϰų� �����ϱ� ���� Filtering�� �����ϴ� Class�̴�.
//    �Ϲ������� C_logFile�̳� Server MFC control�� CChild_logger_view_ex� ���ȴ�.
//
// 2. log_filter�� �ٽ� �Լ�
//		1) Filtering �Լ�
//
//         bool process_filtering(const sMESSAGE_LOG& _msg) PURE;
//
//         ���������Լ��� process_filtering�� �������Ͽ� Log�� ���� �ʿ䰡 �ִ�
//         ��Ȳ�� true�� ���ϵǾ� ������ �Լ��� ������ �ָ� �ȴ�.
//
//-----------------------------------------------------------------------------
class log_filter :
// inherited classes)
	virtual public				Ilog_filter
{
// constructor/destructor)
public:
			log_filter();
	virtual ~log_filter() noexcept;

// definitions) 
public:
	struct FILTER_INFO
	{
	public:
		bool					is_enable = false;

		bool					is_limit_level  = false;
		log_level_t				range_level_min = log_level_t::min_();
		log_level_t				range_level_max = log_level_t::max_();

		bool					is_limit_origin  = false;
		log_origin_t			range_origin_min = log_origin_t::min_();
		log_origin_t			range_origin_max = log_origin_t::max_();

		bool					is_limit_source  = false;
		log_source_t			range_source_min = log_source_t::min_();
		log_source_t			range_source_max = log_source_t::max_();

		bool					is_limit_destination  = false;
		log_destination_t		range_destination_min = log_destination_t::min_();
		log_destination_t		range_destination_max = log_destination_t::max_();
	};

// public) 
public:
			void				set_filter_info (log_type_t _log_type, const FILTER_INFO& _filter_info);
	[[nodiscard]] const FILTER_INFO& get_filter_info (log_type_t _log_type) const;

			void				enable_log (log_type_t _log_type, bool _enable = true);
			void				disable_log (log_type_t _log_type);

			void				enable_filtering_by_level_range (log_type_t _log_type, bool _enable = true);
			void				disable_filtering_by_level_range (log_type_t _log_type);
			void				set_filtering_range_by_level (log_type_t _log_type, log_level_t _min, log_level_t _max);

			void				enable_filtering_by_origin_range (log_type_t _log_type, bool _enable=true);
			void				disable_filtering_by_origin_range (log_type_t _log_type);
			void				set_filtering_range_by_origin (log_type_t _log_type, log_origin_t _min, log_origin_t _max);

			void				enable_filtering_by_source_range (log_type_t _log_type, bool _enable = true);
			void				disable_filtering_by_source_range (log_type_t _log_type);
			void				set_filtering_range_by_source (log_type_t _log_type, log_source_t _min, log_source_t _max);

			void				enable_filtering_by_destination_range (log_type_t _log_type, bool _enable = true);
			void				disable_filtering_by_destination_range (log_type_t _log_type);
			void				set_filtering_range_by_destination (log_type_t _log_type, log_destination_t _min, log_destination_t _max);

// framework) 
public:
	virtual bool				process_filtering(const LOG_RECORD* _plog_record) override;

// implementation) 
protected:
			FILTER_INFO			m_filter_info[static_cast<int>(log_type_t::max_)];
			

};


}