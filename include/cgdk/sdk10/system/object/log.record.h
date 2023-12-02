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

//-----------------------------------------------------------------------------
/**
@class		LOG_RECORD
*/
//-----------------------------------------------------------------------------
class CGDK::LOG_RECORD : virtual public Ireferenceable, public Ibuffer_serializable, public factory::_traits_system
{
public:
	virtual ~LOG_RECORD() noexcept {}

public:
	void						clear() noexcept { buf_message.clear(); sub_plog.clear();}
	object_ptr<LOG_RECORD>		clone(eCHARACTER_SET _character_set = eCHARACTER_SET::NONE) const;

	void						set_message(const std::string_view _message, eCHARACTER_SET _character_set = _DEFAULT_CHAR_CHARACTER_SET);
	void						set_message(const std::wstring_view _message, eCHARACTER_SET _character_set = _DEFAULT_WCHAR_CHARACTER_SET);
	void						set_message(const std::u16string_view _message, eCHARACTER_SET _character_set = _DEFAULT_CHAR16_CHARACTER_SET);

	void						add_message(const std::string_view _message, eCHARACTER_SET _character_set = _DEFAULT_CHAR_CHARACTER_SET);
	void						add_message(const std::wstring_view _message, eCHARACTER_SET _character_set = _DEFAULT_WCHAR_CHARACTER_SET);
	void						add_message(const std::u16string_view _message, eCHARACTER_SET _character_set = _DEFAULT_CHAR16_CHARACTER_SET);

	[[nodiscard]] size_t		get_line_count() const noexcept;
	[[nodiscard]] bool			is_empty() const noexcept { return buf_message.empty(); }

	auto&						operator >> (std::ostream& _stream_out) { stream_out(_stream_out); return *this; }
	auto&						operator >> (std::ostream& _stream_out) const { stream_out(_stream_out); return *this; }
	void						stream_out(std::ostream& _stream_out, eCHARACTER_SET _character_set = _DEFAULT_CHAR_CHARACTER_SET) const;

	DEFINE_BUFFER_SERIALIZE(type, level, result, char_encoding, buf_message, origin, attribute, source, destination, time_occure)

public:
	size_t						process_buffer_size(eCHARACTER_SET _character_set) const noexcept;
	void						process_append_text_date(shared_buffer& _dst, eCHARACTER_SET _character_set) const;

	void						process_append_to_buffer(shared_buffer& _dst, eCHARACTER_SET _character_set) const;
	void						process_append_to_buffer_mbcs(shared_buffer& _dst) const;
	void						process_append_to_buffer_windows_unicode(shared_buffer& _dst) const;
	void						process_append_to_buffer_utf8(shared_buffer& _dst) const;

	size_t						process_get_message(shared_buffer& _dst, size_t _pos, eCHARACTER_SET _character_set) const;
	size_t						process_get_message_from_mbcs(shared_buffer& _dst, size_t _pos, eCHARACTER_SET _character_set) const;
	size_t						process_get_message_from_windows_unicode(shared_buffer& _dst, size_t _pos, eCHARACTER_SET _character_set) const;
	size_t						process_get_message_from_utf8(shared_buffer& _dst, size_t _pos, eCHARACTER_SET _character_set) const;
	size_t						process_get_message_from_ucs16(shared_buffer& _dst, size_t _pos, eCHARACTER_SET _character_set) const;

public:
	log_type_t					type{ log_type_t::undefined };
	log_level_t					level{ log_level_t::normal() };
	result_code					result{ eRESULT::NOT_DEFINED };

	eCHARACTER_SET				char_encoding{ _DEFAULT_CHAR_CHARACTER_SET };
	shared_buffer				buf_message;

	log_origin_t				origin{ 0 };
	log_attribute_t				attribute{ 0 };
	log_source_t				source{ 0 };
	log_destination_t			destination{ 0 };
	chrono::time::utc::time_point time_occure;

	circular_list<object_ptr<LOG_RECORD>> sub_plog;

	static	object_ptr< LOG_RECORD> _alloc();
};

namespace CGDK
{
	//-----------------------------------------------------------------------------
	/**
	@class		sMESSAGE_LOG
	*/
	//-----------------------------------------------------------------------------
	struct sMESSAGE_LOG : public sMESSAGE
	{
	public:
		sMESSAGE_LOG() noexcept : sMESSAGE(eMESSAGE::SYSTEM::LOG_) {}
		sMESSAGE_LOG(LOG_RECORD* _plog_record) noexcept : sMESSAGE(eMESSAGE::SYSTEM::LOG_), plog_record(_plog_record) {}
		sMESSAGE_LOG(log_type_t _type, log_level_t _level, eCHARACTER_SET _character_set, const std::string_view _message);
		sMESSAGE_LOG(log_type_t _type, log_level_t _level, eCHARACTER_SET _character_set, const std::string_view _message, const chrono::time::utc::time_point& _time_occure);

	public:
		object_ptr<LOG_RECORD>	plog_record;
	};

}