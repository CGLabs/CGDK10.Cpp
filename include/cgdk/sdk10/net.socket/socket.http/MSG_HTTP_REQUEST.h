//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        network socket http classes                        *
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
// sMESSAGE_HTTP_REQUEST
//
//
// ----------------------------------------------------------------------------
struct sMESSAGE_HTTP_REQUEST : public sMESSAGE_HTTP
{
public:
			sMESSAGE_HTTP_REQUEST() : sMESSAGE_HTTP(eMESSAGE::SYSTEM::HTTP_REQUEST) {}
			sMESSAGE_HTTP_REQUEST(const shared_buffer& _buffer) : sMESSAGE_HTTP(eMESSAGE::SYSTEM::HTTP_REQUEST, _buffer) {}

public:
	// 2) request line - path/parameters
			std::u8string_view path;
			std::vector<sHTTP_PATH_ITEM> parameters; // MAX:64

public:
			void				reset() noexcept { sMESSAGE_HTTP::reset(); path.remove_suffix(path.size()); parameters.clear(); }
};


}