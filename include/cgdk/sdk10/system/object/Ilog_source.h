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
//
// Ilog_source
//
//-----------------------------------------------------------------------------
class CGDK::Ilog_source : virtual public Ireferenceable
{
public:
	virtual ~Ilog_source() noexcept {}
	virtual object_ptr<LOG_RECORD>	process_store_log(log_type_t _log_type, log_level_t _log_level, eCHARACTER_SET _char_code, std::string_view _log_message) noexcept PURE;

};
