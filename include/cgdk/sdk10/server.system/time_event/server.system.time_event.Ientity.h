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
// ----------------------------------------------------------------------------
//
// time_event::Ientity
//
//
//
// ----------------------------------------------------------------------------
class time_event::Ientity :
	virtual public				CGDK::object::Inameable,
	public						CGDK::object::Ninitializable_startable,
	public						CGDK::object::Npausable,
	virtual public				Iexecutable
{
public:
	virtual ~Ientity() noexcept {}

	[[nodiscard]] auto&			entity_setting() noexcept { return this->m_entity_setting;}
	[[nodiscard]] const auto&	entity_setting() const noexcept { return this->m_entity_setting;}
	[[nodiscard]] auto&			entity_status() noexcept { return this->m_entity_status;}
	[[nodiscard]] const auto&	entity_status() const noexcept { return this->m_entity_status;}
	[[nodiscard]] auto&			entity_result_log() noexcept { return this->m_plog_result;}
	[[nodiscard]] const auto&	entity_result_log() const noexcept { return this->m_plog_result;}
			void				set_next_time(chrono::time::utc::time_point _time_next) noexcept;

	[[nodiscard]] auto			executor() const noexcept { scoped_lock(this->m_cs_pexecutor) { return this->m_pexecutor; } }
			void				executor(const object_ptr<Iexecutor>& _pexecutor) noexcept { this->executor(object_ptr<Iexecutor>(_pexecutor)); }
			void				executor(object_ptr<Iexecutor>&& _pexecutor) noexcept { scoped_lock(this->m_cs_pexecutor) { this->m_pexecutor = std::move(_pexecutor); } }
	[[nodiscard]] bool			has_executor() const noexcept { scoped_lock(this->m_cs_pexecutor) { return this->m_pexecutor.exist(); } }

			void				LOG_EVENT(Ilogger* _plog_target, log_type_t _type, log_level_t _level, eCHARACTER_SET _char_code, std::string_view _message) noexcept;
			void				LOG_EVENT(Ilogger* _plog_target, log_type_t _type, log_level_t _level, std::string_view _message) noexcept { LOG_EVENT(_plog_target, _type, _level, _DEFAULT_CHAR_CHARACTER_SET, _message); }
			template <class... TARGS>
			void				LOG_EVENT(Ilogger* _plog_target, log_type_t _type, log_level_t _level, eCHARACTER_SET _char_code, std::string_view _format, TARGS... _args) noexcept;
			template <class... TARGS>
			void				LOG_EVENT(Ilogger* _plog_target, log_type_t _type, log_level_t _level, std::string_view _format, TARGS... _args) noexcept { LOG_EVENT(_plog_target, _type, _level, _DEFAULT_CHAR_CHARACTER_SET, _format, std::forward<TARGS...>(_args...)); }

protected:
	[[nodiscard]] virtual bool	process_is_this(std::string_view _name) const noexcept { return this->m_entity_setting.name == _name;}
	[[nodiscard]] virtual std::string_view process_get_name() const noexcept { return this->m_entity_setting.name; }
	virtual	void				process_set_name(std::string_view _name) { this->m_entity_setting.name = _name;}
			void				process_notify_update_next_time();

			object_ptr<LOG_RECORD> _append_result_log(std::string_view _state) noexcept;
			void				_append_result_log_post(LOG_RECORD* _plog_result);

			lockable<>			m_cs_pexecutor;
			object_ptr<Iexecutor> m_pexecutor;

			sENTITY_SETTING		m_entity_setting;
			sENTITY_STATUS		m_entity_status;
			lockable<object_ptr<LOG_RECORD>> m_plog_result;

			friend	class time_event::entity_manager;
};																				  

template <class... TARGS>
void time_event::Ientity::LOG_EVENT(Ilogger* _plog_target, log_type_t _type, log_level_t _level, eCHARACTER_SET _char_code, std::string_view _format, TARGS... _args) noexcept
{
	// check) _format shouldn't be nullptr
	CGASSERT_ERROR(_format.empty() == false);

	// check) _format shouldn't be nullptr
	RETURN_IF(_format.empty());

	try
	{
		// declare) 
		object_ptr<LOG_RECORD> plog_sub;

		scoped_lock(this->m_plog_result)
		{
			// check) 
			RETURN_IF(this->m_plog_result.empty());

			// check) 
			RETURN_IF(this->m_plog_result->sub_plog.empty());

			// 1) 제일 마지막의 SubEvent객체를 얻어 온다.
			auto presult_event = this->m_plog_result->sub_plog.back();

			// declare) 
			shared_buffer temp_buf_message = alloc_shared_buffer(MAX_TRACE_STRING_LENGTH);

			// 2) Add size of message 
			temp_buf_message.append<COUNT_T>();

			// 3) Add messsge
			auto temp_result = __sprintf(temp_buf_message.data() + sizeof(COUNT_T), MAX_TRACE_STRING_LENGTH - sizeof(COUNT_T) - 1, _format.data(), _args...);

			// 4) Set
			temp_buf_message.front<COUNT_T>() = static_cast<COUNT_T>(temp_result);

			// 3) allocate new LOG_RECORD object
			plog_sub = make_object<LOG_RECORD>();

			// 4) set log info
			plog_sub->type = _type;
			plog_sub->level = _level;
			plog_sub->char_encoding = _char_code;
			plog_sub->buf_message = temp_buf_message;
			plog_sub->time_occure = presult_event->time_occure;

			// 5) add LOG_RECORD object
			presult_event->sub_plog.push_back(plog_sub);
		}

		// log) 
		_log(_plog_target, plog_sub);
	}
	catch (...)
	{
	}
}


}
