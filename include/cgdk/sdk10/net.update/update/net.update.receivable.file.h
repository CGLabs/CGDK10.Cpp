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
// CGDK::update::receivable::file
//process_begin
//
//-----------------------------------------------------------------------------
namespace CGDK
{
namespace update
{
namespace receivable
{

class file : virtual public update::Ireceivable
{
public:
	virtual sUPDATABLE_PREPARE_INFO	process_prepare(std::string_view _full_file_path) override;
	virtual void					process_begin (uint64_t _pos_begin) override;
	virtual result_code				process_process (const CGDK::resource::sMETA_FILE_BLOCK& _meta_file_block, buffer_view _buf_data) override;
	virtual result_code				process_end () override;

protected:
			FILE_HANDLE				m_file_handle = INVALID_FILE_HANDLE;
};

}
}
}