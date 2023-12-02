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
struct sMESSAGE_HTTP_WEBSOCKET : public sMESSAGE_HTTP
{
public:
			sMESSAGE_HTTP_WEBSOCKET() : sMESSAGE_HTTP(eMESSAGE::SYSTEM::WEBSOCKET) {}
			sMESSAGE_HTTP_WEBSOCKET(const shared_buffer& _buffer) : sMESSAGE_HTTP(eMESSAGE::SYSTEM::WEBSOCKET, _buffer) {}
};


}