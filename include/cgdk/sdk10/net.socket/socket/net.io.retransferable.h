//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
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
/*!
* @class NRetransferable
*
* @ingroup net::io::NRetransferable
*
* @brief 접속이 종료되었을 때 전송내용을 보존하고 있다가 재전송을 해주는 모듈
*
*/
//-----------------------------------------------------------------------------
class net::io::Nretransferable :
	virtual	public				net::io::Isender,
	virtual public				net::io::messageable::Nbase
{
public:
	//! @brief 재전송을 보장하는 메시지를 전송한다.
			bool				send_reliable(const shared_buffer& _buffer);
	//! @brief 재전송을 리셋한다.
			void				reset_retransfer();
	//! @brief 재전송을 요청한다.(일반적으로 처음 접속할때 호출한다.)
			bool				request_restore();

protected:
	//! @brief 메시지 처리를 정의한다. @param _msg 처리 요청하는 메시지 @return true !0 처리됨 @return 0 처리되지 않음
	virtual	result_code			process_message(sMESSAGE& _msg) override;
	//! @brief 재전송을 요청받았을 때 처리를 정의한다.
			void				process_request_retransfer();
	//! @brief 재전송 처리의 리셋을 요청받았을 때의 처리를 정의한다.
			void				process_request_reset_retransfer();

	//! @brief 재전송을 요청할 때 전송하는 메시지다.
	[[nodiscard]] static shared_buffer message_REQUEST_RESTORE(uint64_t _serial_last_received);
	//! @brief 재전송을 요청할 때 전송하는 메시지다.
	[[nodiscard]] static shared_buffer message_REQUEST_RESET(uint64_t _serial_last_received);
	//! @brief 재전송을 완료 직후 송신되는 메시지다.
	[[nodiscard]] static shared_buffer message_RETRNAMISSION_COMPLETE();
	//! @brief ACK 메시지를 전송한다.
	[[nodiscard]] static shared_buffer message_SEND_ACK(uint64_t _serial_received);

private:
			lockable<circular_list<shared_buffer>> m_list_retransfer;
			uint64_t			m_ack_sended = 0;
			uint64_t			m_ack_received = 0;
};


}