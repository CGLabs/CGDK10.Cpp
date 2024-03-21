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
// 1. C_logEvent��~
//     Logó���� ���� ���̴�.
//
// 2. Log�� ����
//	  0) Date/Time		Log�� ���� �ð��̴�.(�ڵ����)
//	  1) Logger			Log�� ����� ���� �̸��̴�.(�ڵ� ���)
//	  2) type			Log�� �����̴�. Errror, Progress, Warning, Info, ...
//	  3) Level			Log�� �߿䵵�̴�.
//	  4) Source			Log�� ����� Event�� ��ü�� �Ǵ� ���� �ǹ��Ѵ�.
//	  5) Dest			Log�� ����� Event�� ����� �Ǵ� ���� �ǹ��Ѵ�.
//	  6) Where			Log�� ����� Event�� �߻��ϴ� ��ü�� �ǹ��Ѵ�.
//	  7) Function		Log�� ���� Event�� ȣ���� �Լ��� �ǹ��Ѵ�.
//	  8) Message		���� Log Message�� �ǹ��Ѵ�.
//
// 3. Initializing Parameters
//    1) ���� �̸�		'filename'			���ϸ�  ex) "log_file ({}{}[}-{}{}{}.log"
//    2) ���� �ð�		'recreation'		����� ���� (true, false)
//    3) ����� ����	'interval'			1�д����� ����� �ð� 
//    4) ���� �ð�		'origin_time_type'	������� ���� �ð� ���� ("now", "minute_begin", "hour_begin", "day_begin", "week_begin", "month_begin", "year_begin", "specified", "default")
//    5) ���� �ð�		'origin_time'		���� �ð� (origin_time_type�� "specified"�� ��� ���� �ð�
//    6) ���� �ð�		'create_new'		���� ���� ���� (true, false)
//    7) ���� �ð�		'char_encoding'			���� ���ڵ� ("multiibyte", "utf8", "utf16", "utf32", "ucs16", "ucs32", "default")
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