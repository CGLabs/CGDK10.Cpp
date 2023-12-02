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
* @brief ������ ����Ǿ��� �� ���۳����� �����ϰ� �ִٰ� �������� ���ִ� ���
*
*/
//-----------------------------------------------------------------------------
class net::io::Nretransferable :
	virtual	public				net::io::Isender,
	virtual public				net::io::messageable::Nbase
{
public:
	//! @brief �������� �����ϴ� �޽����� �����Ѵ�.
			bool				send_reliable(const shared_buffer& _buffer);
	//! @brief �������� �����Ѵ�.
			void				reset_retransfer();
	//! @brief �������� ��û�Ѵ�.(�Ϲ������� ó�� �����Ҷ� ȣ���Ѵ�.)
			bool				request_restore();

protected:
	//! @brief �޽��� ó���� �����Ѵ�. @param _msg ó�� ��û�ϴ� �޽��� @return true !0 ó���� @return 0 ó������ ����
	virtual	result_code			process_message(sMESSAGE& _msg) override;
	//! @brief �������� ��û�޾��� �� ó���� �����Ѵ�.
			void				process_request_retransfer();
	//! @brief ������ ó���� ������ ��û�޾��� ���� ó���� �����Ѵ�.
			void				process_request_reset_retransfer();

	//! @brief �������� ��û�� �� �����ϴ� �޽�����.
	[[nodiscard]] static shared_buffer message_REQUEST_RESTORE(uint64_t _serial_last_received);
	//! @brief �������� ��û�� �� �����ϴ� �޽�����.
	[[nodiscard]] static shared_buffer message_REQUEST_RESET(uint64_t _serial_last_received);
	//! @brief �������� �Ϸ� ���� �۽ŵǴ� �޽�����.
	[[nodiscard]] static shared_buffer message_RETRNAMISSION_COMPLETE();
	//! @brief ACK �޽����� �����Ѵ�.
	[[nodiscard]] static shared_buffer message_SEND_ACK(uint64_t _serial_received);

private:
			lockable<circular_list<shared_buffer>> m_list_retransfer;
			uint64_t			m_ack_sended = 0;
			uint64_t			m_ack_received = 0;
};


}