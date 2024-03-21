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
// _log_stream
//
// << 연산자를 사용해 로그를 C++ iostream과 같이 남길 수 있도록 지원해주는 클래스이다.
//
//   _log_stream		Stream 객체로 c++ iostream의 std::cout 등에 해당하는 객체이다.
//	 _log_end		Stream의 끝을 나타의미하는 객체로 std::endl 과 같은 객체다.
//
//  example)
//       -> 기존 _log함수 사용 예 
//			LOG(plogger, log_type_t::INFO) << "Test Log {} {}", x, t.c_str());
//
//       -> 기본 log_target을 사용시 log_target을 생략
//			LOG(log_type_t::info) << "Test Log";
//
//       -> fmt::format 사용예
//			LOG(log_type_t::info) << fmt::format("Test Log {} {}", x, t.c_str());
//
//       -> defiontion을 사용
//			LOG_INFO << "Test Log"sv;
//          (LOG(log_type_t::info) << "Test Log"와 동일한다.
//
//-----------------------------------------------------------------------------
struct log_continue_t
{
};

class _log_stream
{
public:
	_log_stream();
	_log_stream(Ilogger* _plogger, log_type_t _type);
	_log_stream(log_type_t _type);
	~_log_stream() noexcept		{ CGASSERT_ERROR(plog_record.empty()); }

public:
	_log_stream&				operator << (char _rhs) { process_stream_in<char>(_rhs); return *this; }
	_log_stream&				operator << (int8_t _rhs) { process_stream_in<int8_t>(_rhs); return *this; }
	_log_stream&				operator << (uint8_t _rhs) { process_stream_in<uint8_t>(_rhs); return *this; }
	_log_stream&				operator << (int16_t _rhs) { process_stream_in<int16_t>(_rhs); return *this; }
	_log_stream&				operator << (uint16_t _rhs) { process_stream_in<uint16_t>(_rhs); return *this; }
	_log_stream&				operator << (int32_t _rhs) { process_stream_in<int32_t>(_rhs); return *this; }
	_log_stream&				operator << (uint32_t _rhs) { process_stream_in<uint32_t>(_rhs); return *this; }
	_log_stream&				operator << (int64_t _rhs) { process_stream_in<int64_t>(_rhs); return *this; }
	_log_stream&				operator << (uint64_t _rhs) { process_stream_in<uint64_t>(_rhs); return *this; }
#if defined(_MSC_VER)
	_log_stream&				operator << (long _rhs) { process_stream_in<long>(_rhs); return *this; }
	_log_stream&				operator << (unsigned long _rhs) { process_stream_in<unsigned long>(_rhs); return *this; }
#else
	_log_stream&				operator << (long long _rhs) { process_stream_in<long long>(_rhs); return *this; }
	_log_stream&				operator << (unsigned long long _rhs) { process_stream_in<unsigned long long>(_rhs); return *this; }
#endif
	_log_stream&				operator << (log_continue_t /*_rhs*/) { CGASSERT_ERROR(plog_record != nullptr); if(plog_record == nullptr) return *this; plog_record->type = (plog_record->type | log_type_t::continue_); return *this; }
	_log_stream&				operator << (log_level_t _rhs) { CGASSERT_ERROR(plog_record != nullptr); if(plog_record == nullptr) return *this; plog_record->level = _rhs; return *this; }
	_log_stream&				operator << (log_attribute_t _rhs) { CGASSERT_ERROR(plog_record != nullptr); if(plog_record == nullptr) return *this; plog_record->attribute = _rhs; return *this; }
	_log_stream&				operator << (log_origin_t _rhs) { CGASSERT_ERROR(plog_record != nullptr); if(plog_record == nullptr) return *this; plog_record->origin = _rhs; return *this; }
	_log_stream&				operator << (log_source_t _rhs) { CGASSERT_ERROR(plog_record != nullptr); if(plog_record == nullptr) return *this; plog_record->source = _rhs; return *this; }
	_log_stream&				operator << (log_destination_t _rhs) { CGASSERT_ERROR(plog_record != nullptr); if(plog_record == nullptr) return *this; plog_record->destination = _rhs; return *this; }

	_log_stream&				operator << (float _rhs) { process_stream_in<float>(_rhs); return *this; }
	_log_stream&				operator << (double _rhs) { process_stream_in<double>(_rhs); return *this; }
	_log_stream&				operator << (const std::string_view _rhs);
	_log_stream&				operator << (const std::wstring_view _rhs);
	_log_stream&				operator << (void(*_pfunction)(_log_stream&)) { _pfunction(*this); return *this; }

public:
			object_ptr<LOG_RECORD> plog_record;
			object_ptr<Ilogger>	plogger;
			Ilogger*			plogger_source {nullptr};
			int64_t				pos{ 0 };
protected:
			template <class T>
			void				process_stream_in(T _rhs);
};

template <class T>
void _log_stream::process_stream_in(T _rhs)
{
	// check) 
	RETURN_IF(plogger.empty());

	// check) 
	RETURN_IF(plog_record.empty());

	// 1) set 
	auto dest_strlen	 = plog_record->buf_message.front<COUNT_T>(pos);
	auto dest_remained	 = plog_record->buf_message.get_remained_size();
	auto dest_ptr		 = plog_record->buf_message.data<char>() + pos + dest_strlen - sizeof(char) + sizeof(COUNT_T);

	// 2) write to string
	auto temp_result = __to_string(dest_ptr, dest_remained, _rhs);

	// 3) 크기 써넣기
	plog_record->buf_message.front<COUNT_T&>(pos) = static_cast<COUNT_T>(dest_strlen + temp_result.size());
	plog_record->buf_message.add_size(temp_result.size());
}


//-----------------------------------------------------------------------------
// _log_endl
//-----------------------------------------------------------------------------
void log_endl(_log_stream& _log_stream);

struct _log_end
{
public:
	void operator = (_log_stream&& _log) { _log_end::operator = (_log); }
	void operator = (_log_stream& _log);
};


//-----------------------------------------------------------------------------
// LOG_MESSAGE_EMPTY
//-----------------------------------------------------------------------------
class LOG_MESSAGE_EMPTY
{
public:
			LOG_MESSAGE_EMPTY&	operator << (char ) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (int8_t ) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (uint8_t ) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (int16_t ) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (uint16_t ) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (int32_t ) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (uint32_t ) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (int64_t ) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (uint64_t ) noexcept { return *this; }
		#if defined(_MSC_VER)
			LOG_MESSAGE_EMPTY&	operator << (long) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (unsigned long) noexcept { return *this; }
		#else 
			LOG_MESSAGE_EMPTY&	operator << (long long) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (unsigned long long) noexcept { return *this; }
		#endif
			LOG_MESSAGE_EMPTY&	operator << (float ) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (double ) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (const std::string_view ) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (const std::wstring_view ) noexcept { return *this; }
			LOG_MESSAGE_EMPTY&	operator << (_log_stream&(*)(_log_stream&)) { return *this; }
};


}