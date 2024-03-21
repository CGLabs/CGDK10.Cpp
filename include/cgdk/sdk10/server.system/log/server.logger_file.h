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
// C_logEvent
//
// 1. C_logEvent은~
//     Log처리를 위한 것이다.
//
// 2. Log의 내용
//	  0) Date/Time		Log가 남은 시간이다.(자동기록)
//	  1) Logger			Log를 남기는 자의 이름이다.(자동 등록)
//	  2) type			Log의 종류이다. Errror, Progress, Warning, Info, ...
//	  3) Level			Log의 중요도이다.
//	  4) Source			Log에 남기는 Event의 주체가 되는 것을 의미한다.
//	  5) Dest			Log에 남기는 Event의 대상이 되는 것을 의미한다.
//	  6) Where			Log에 남기는 Event가 발생하는 객체를 의미한다.
//	  7) Function		Log가 남는 Event를 호출한 함수를 의미한다.
//	  8) Message		남길 Log Message를 의미한다.
//
// 3. Initializing Parameters
//    1) 파일 이름		'filename'			파일명  ex) "log_file ({}{}[}-{}{}{}.log"
//    2) 기존 시간		'recreation'		재생성 유부 (true, false)
//    3) 재생성 간격	'interval'			1분단위의 재생성 시간 
//    4) 기준 시간		'origin_time_type'	재생성시 시작 시간 유형 ("now", "minute_begin", "hour_begin", "day_begin", "week_begin", "month_begin", "year_begin", "specified", "default")
//    5) 기존 시간		'origin_time'		시작 시간 (origin_time_type이 "specified"일 경우 시작 시간
//    6) 기존 시간		'create_new'		새로 생성 여부 (true, false)
//    7) 기존 시간		'char_encoding'			문자 인코딩 ("multiibyte", "utf8", "utf16", "utf32", "ucs16", "ucs32", "default")
//
//-----------------------------------------------------------------------------
class logger_file : 
	public						Nlogger
{
public:
			struct INITIALIZE_PARAMETER
			{
				std::string_view				filename;
				chrono::time::duration			recreation_interval = chrono::time::duration::zero();
				eORIGIN_TIME_TYPE				origin_time_type = eORIGIN_TIME_TYPE::DEFAULT;
				chrono::time::utc::time_point	begin_time = (chrono::time::utc::time_point::min)();
				eCHARACTER_SET					char_code = _DEFAULT_CHAR_CHARACTER_SET;
				eEOL_TYPE						eol_type = _DEFAULT_FILE_EOL_TYPE;
			};

			logger_file();
			logger_file(const std::string_view _name);
	virtual ~logger_file() noexcept;

			result_code			initialize() { return this->object::Ninitializable::initialize(); }
			result_code			initialize(const INITIALIZE_PARAMETER& _initialize_param);
	virtual	result_code			initialize(context& _context) override	{ return this->object::Ninitializable::initialize(_context); }

	[[nodiscard]] eCHARACTER_SET character_encoding() const noexcept { return this->m_char_encoding; }
			void				character_encoding(eCHARACTER_SET _char_code) noexcept { this->m_char_encoding = _char_code; }

protected:
	virtual	result_code			_process_initializing(context& _context) override;
	virtual	result_code			_process_destroying() noexcept;

	virtual void				_process_recreate_file();
	static	void				_process_append_EOL(shared_buffer& _buf_target, eEOL_TYPE _eol_type);
	static	bool				_process_get_parameter_enabled(context& _context);
	static	std::string			_process_get_parameter_path(context& _context);
	static	std::string			_process_get_parameter_filename(context& _context);
	static	chrono::time::duration _process_get_parameter_interval(context& _context);
	static	eORIGIN_TIME_TYPE	_process_get_parameter_origin_time_type(context& _context);
	static	chrono::time::utc::time_point _process_get_parameter_origin_time(context& _context, chrono::time::utc::time_point _time_now, eORIGIN_TIME_TYPE _origin_time_type, std::string _filename);
	static	bool				_process_get_parameter_enable_recreation(context& _context);
	static	bool				_process_get_parameter_create_new(context& _context);
	static	eCHARACTER_SET		_process_get_parameter_char_encoding(context& _context);
	static	int					_process_get_parameter_filter(context& _context);
	static	bool				_process_get_parameter_is_instant_open(context& _context);

	virtual	void				process_log(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) override;

			std::shared_mutex	m_lockable_pfile;
			object_ptr<archive::file> m_pfile;
			eCHARACTER_SET		m_char_encoding{ _DEFAULT_CHAR_CHARACTER_SET };
			eEOL_TYPE			m_EOL_type{ _DEFAULT_FILE_EOL_TYPE };

			std::string			m_path;
			std::string			m_filename;

			bool				m_enable_recreation{ false };
			chrono::time::duration m_recreation_duration;
			chrono::time::utc::time_point m_recreation_next_time;
};


}