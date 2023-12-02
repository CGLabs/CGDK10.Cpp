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
//----------------------------------------------------------------------------
//
// message type
//
//----------------------------------------------------------------------------
namespace CGDK
{
	namespace eMESSAGE
	{
		namespace UPDATE
		{
			const message_t	BEGIN						 = BASE +   1;
			const message_t	END							 = BASE +   2;
			const message_t	BEGIN_REQUEST				 = BASE +   3;
			const message_t	BEGIN_RESPONSE				 = BASE +   4;
			const message_t	UPDATABLE_REQUEST			 = BASE +   5;
			const message_t	UPDATABLE_RESPONSE			 = BASE +   6;
			const message_t	UPDATABLE_BEGIN				 = BASE +   7;
			const message_t	UPDATABLE_BLOCK				 = BASE +   8;
			const message_t	UPDATABLE_END				 = BASE +   9;

			const message_t	REQUEST						 = BASE +  11;
			const message_t	RESPONSE					 = BASE +  12;
			const message_t	COMPLETE					 = BASE +  13;
		}
	}
}


//----------------------------------------------------------------------------
//
// message 
//
//----------------------------------------------------------------------------
// 1) for updater
CGDK::shared_buffer _message_UPDATE_BEGIN_REQUEST (CGDK::update::RECEIVER_ID _receiver_id, CGDK::update::SENDER_ID _sender_id, const CGDK::update::sUPDATE_REQUEST_INFO& _update_request_info);
CGDK::shared_buffer _message_UPDATE_BEGIN_RESPONSE (CGDK::update::SENDER_ID _sender_id, CGDK::update::RECEIVER_ID _receiver_id, eRESULT _result);
CGDK::shared_buffer _message_UPDATE_END (CGDK::update::RECEIVER_ID _receiver_id, CGDK::update::SENDER_ID _sender_id, eRESULT _result);

// 2) for updtable
CGDK::shared_buffer _message_UPDATE_UPDATABLE_REQUEST (CGDK::update::RECEIVER_ID _receiver_id, CGDK::update::SENDER_ID _sender_id, const CGDK::resource::sUPDATABLE_FILE_META_INFO& _file_meta_info); // server -> client
CGDK::shared_buffer _message_UPDATE_UPDATABLE_RESPONSE (CGDK::update::SENDER_ID _sender_id, CGDK::update::RECEIVER_ID _receiver_id, CGDK::update::UPDATABLE_ID _updatable_id, const CGDK::sUPDATABLE_PREPARE_INFO& _updatable_prepare_info); // client -> server
CGDK::shared_buffer _message_UPDATE_UPDATABLE_BEGIN (CGDK::update::RECEIVER_ID _receiver_id, CGDK::update::SENDER_ID _sender_id, CGDK::update::UPDATABLE_ID _updatable_id, uint64_t _pos_begin); // server -> client
CGDK::shared_buffer _message_UPDATE_UPDATABLE_BEGIN(CGDK::update::SENDER_ID _sender_id, CGDK::update::RECEIVER_ID _receiver_id, CGDK::update::UPDATABLE_ID _updatable_id, eRESULT _result, uint64_t _pos_begin); // client -> server
CGDK::shared_buffer _message_UPDATE_UPDATABLE_BLOCK (CGDK::update::RECEIVER_ID _receiver_id, CGDK::update::SENDER_ID _sender_id, uint32_t _size_block); //
CGDK::shared_buffer _message_UPDATE_UPDATABLE_END (CGDK::update::RECEIVER_ID _receiver_id, CGDK::update::SENDER_ID _sender_id, CGDK::update::UPDATABLE_ID _updatable_id, eRESULT _result); // server -> clieSnt
CGDK::shared_buffer _message_UPDATE_UPDATABLE_END(CGDK::update::SENDER_ID _sender_id, CGDK::update::RECEIVER_ID _receiver_id, CGDK::update::UPDATABLE_ID _updatable_id, eRESULT _result, CGDK::MD5 _md5); // client -> server
