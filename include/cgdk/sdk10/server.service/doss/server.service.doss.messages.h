//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                 Distributed Object Storage System Classes                 *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
// doss::CAccount
//-----------------------------------------------------------------------------
shared_buffer message_SERVER_DOSS_REQUEST_CERTIFY(const sREPOSITORY_ID& _rid, const sREPOSITORY_ID& _rid_remote, uint64_t _receive_sequence_ack);
shared_buffer message_SERVER_DOSS_RESPONSE_CERTIFY(const sREPOSITORY_ID& _rid, const std::vector<sREPOSITORY_ID>& _vec_rid, uint64_t _receive_sequence_ack);
shared_buffer message_SERVER_DOSS_REQUEST_RECOVER(uint64_t _tid, const sCHECKIN_ID& _cid);

shared_buffer message_SERVER_DOSS_COMMAND_REQUEST	(uint64_t _send_sequence, doss::Itransactable* _ptransactable);
shared_buffer message_SERVER_DOSS_COMMAND_RESPONSE	(uint64_t _send_sequence, doss::Itransactable* _ptransactable);
shared_buffer message_SERVER_DOSS_COMMAND_RESPONSE	(uint64_t _send_sequence, eTRANSACTION_TYPE _command, sCHECKIN_ID _cid, sREQUEST_ID _rid, result_code _result, shared_buffer _buf_response);
shared_buffer message_SERVER_DOSS_COMMAND_FAIL		(uint64_t _send_sequence, doss::Itransactable* _ptransactable);
shared_buffer message_SERVER_DOSS_CONTROL_REQUEST	(uint64_t _send_sequence, eTRANSACTION_TYPE _command, const sCHECKIN_ID& _cid, sREQUEST_ID _rid, eRESULT _result);
shared_buffer message_SERVER_DOSS_SEND_ACK			(uint64_t _send_sequence);


enum class  eRESULT_DOSS : int
{
	SUCCESS									 = static_cast<int>(eRESULT::SUCCESS),
	ALEADY_CHECKINED						 = 0x00000200,
	PENDED									 = static_cast<int>(eRESULT::PENDED),
	SUCCESS_CREATE							 = static_cast<int>(eRESULT::SUCCESS_CREATE),
	SUCCESS_RESTORE							 = static_cast<int>(eRESULT::SUCCESS_RESTORE),
	PENDING									 = static_cast<int>(eRESULT::PENDING),

	FAIL									 = static_cast<int>(eRESULT::FAIL),	// 0x3******* Fail
	ALEADY_EXIST							 = static_cast<int>(eRESULT::ALEADY_EXIST),
	EXPIRED									 = static_cast<int>(eRESULT::EXPIRED),
	NOT_EXIST								 = static_cast<int>(eRESULT::NOT_EXIST),
	NOT_READY								 = static_cast<int>(eRESULT::NOT_READY),
	BANNED_MEMBER							 = static_cast<int>(eRESULT::BANNED_MEMBER),
	FAIL_TO_CREATE							 = static_cast<int>(eRESULT::FAIL_TO_CREATE),
	FAIL_TO_OPEN							 = static_cast<int>(eRESULT::FAIL_TO_OPEN),
	FAIL_TO_OPERATION						 = static_cast<int>(eRESULT::FAIL_TO_OPERATION),
	FAIL_NO_WEBSOCKET_KEY					 = 0x03010126,
	
	CANCEL									 = static_cast<int>(eRESULT::CANCEL),	// 0x2******* Cancel

	ERROR_									 = static_cast<int>(eRESULT::ERROR_),	// 0x3******* Error
	INVALID_STATE							 = 0x03200016,
	INVALID_HANDLE							 = 0x03200117,

	NOT_DEFINED								 = static_cast<int>(eRESULT::NOT_DEFINED)	// 0xff** Not Defined	

};


}

template <>
struct std::is_error_code_enum<CGDK::eRESULT_DOSS> : std::true_type {};
