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
//
// net::io::send_request::Nudp_resend!!!!  ( ` ~`)b
//
// 1. net::io::send_request::Nudp_resend��!
//    1) Reliable UDP send/receive�� �����ϱ� ���� ��� Class�̴�.
//    2) �� Class������ ���ۿ� ���� Reliable�� �����ϰ� �ִ�.
//    3) �� Class�� �������� Reliable�� ReliableSequenced�� �����Ѵ�.
//
// 2. Reliable�� �߰��� �Լ���...
//    1) peer key
//       - peer���� ���ۿ� �־ ���� Ȯ���� ���� key�� �ǹ��Ѵ�.
//       - �߸����޵ǰų� ���� �ٸ� ���۰��� ������ ���� peer key�� �����Ѵ�.
//       - peer key�� send�� receive key�� ������ send key�� connect�� ���
//         �� ���� ���޹޴´�.
//
//    2) Re-send Interval
//	     - �����ð� ACK�� ���ƿ��� ������ �������� �����Ѵ�.  
//         GetReSendInterval()
//         SetReSendInterval(uint32_t p_dwResendInterval)
//
//    3) ��Ÿ
//       GetSendSequence()			���� Sequence�� ���Ѵ�.
//       GetRetransmittedCount()	�������� �� Ƚ���� ���Ѵ�.
//		 GetSendQueud()				send�� ���� Queued�� Packet�� ���� ��� �Լ�.
//
// 3. ���� ����
//    1) �� Class�� �ϼ��� ���� �ƴϸ� net::io::CReliable�� CReliableSequenced
//       �� ����ϵ��� �Ѵ�.
//
//
//-----------------------------------------------------------------------------
#define		SEND_QUEUE_SIZE				1024
#define		SEND_QUEUE_INDEX_MASK		0x3ff

class net::io::send_request::Nudp_resend : 
	virtual public				net::io::Isendable,
	virtual public				net::io::Isend_request,
	virtual public				Ireferenceable
{
protected:
			Nudp_resend();
	virtual	~Nudp_resend() noexcept;

// public)
public:
	// 1) send�� �� �θ��� �Լ�.
	virtual	bool				request_send(const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _paddress) override;

// implementation)
private:
	// 1) reset�Ҷ� ȣ���ϴ� �Լ�.(�⺻�� ���...)
	virtual	void				reset_send_request() noexcept override;

	// Definition) send Queues
			struct SENDED_PACKET
			{
			public:
				int							iSendOut;
				chrono::tick::time_point	tick_last_send;
				buffer_view					buffer;
				object_ptr<Ireferenceable>	powner;
				net::sockaddr				addr_destination;
				std::size_t					count_message;
			public:
				SENDED_PACKET() noexcept :iSendOut(0), count_message(0){}
			};

	// Definition) executor Resend
			class executable_resend;

	// 2) Re-send�� Progress
			object_ptr<executable_resend>	m_pexecutable_resend;

	// 3) ProcessResend
			void				progress_resend();

	// 3) Sliding Window
			uint32_t			m_size_slinding_window;			// Sliding Window�� ũ��

	// 4) send Buffers
			uint32_t			m_serial_send;					// send Serial
			uint32_t			m_last_serial_send_acked;		// �Ϸ� ack���� ������ packet
			uint32_t			m_last_serial_sended;			// ���������� ���� Serial.

	// 5) send Queues
			int					m_nSended;
			std::vector<SENDED_PACKET> m_queue_sended;			// �̹� ���� Packet�� Array�� ������.
			circular_list<SENDED_PACKET> m_list_send_queue;		// ���� ������ ���� Packet�� ������ send Queue

	// 6) Criticalsection
			lockable<>			m_lockable_send;				// send Queue�� Critical section

	// 7) Resend Interval (������ ����� ���� �ʾ��� �� �ٽ� �������� �ϴ� ����.)
			chrono::tick::duration	 m_tick_resend_interval;
			chrono::tick::time_point m_tick_resend_next;

	// statistics) 
			int					m_retransmitted;				// �������� Ƚ��.

protected:
			bool				ack( uint32_t p_dwPacketSerial, bool p_bResult=true);

			void				create_buffers();
			void				destroy_buffers() noexcept;
			void				clear_buffers() noexcept;
};


}