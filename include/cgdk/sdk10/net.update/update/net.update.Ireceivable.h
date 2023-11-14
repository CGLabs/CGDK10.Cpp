//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network update classes                           *
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
//
// CGDK::update::Ireceivable
//
//
//-----------------------------------------------------------------------------
namespace CGDK
{
namespace update
{

class Ireceivable :	virtual public Ireferenceable
{
public:
			std::string_view	get_full_file_path() const noexcept { return m_full_file_path; }
			void				set_full_file_path(const std::string& _full_file_path) { m_full_file_path = _full_file_path; }
			void				set_full_file_path(std::string&& _full_file_path) { m_full_file_path = std::move(_full_file_path); }

	virtual sUPDATABLE_PREPARE_INFO process_prepare(std::string_view _full_file_path) PURE;
	virtual void				process_begin (uint64_t _pos_begin) PURE;
	virtual result_code			process_process (const CGDK::resource::sMETA_FILE_BLOCK& _meta_file_block, buffer_view _buf_data) PURE;
	virtual result_code			process_end () PURE;

public:
			lockable<>			m_cs_info;
			SENDER_ID			m_sender_id;

			resource::sUPDATABLE_FILE_META_INFO m_meta_info;
			std::string			m_full_file_path;

			edc::md5			m_md5_check;
};

}
}