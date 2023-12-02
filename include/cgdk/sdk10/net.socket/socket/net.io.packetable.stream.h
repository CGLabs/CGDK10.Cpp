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
 * @class Nstream<TMESSAGE_HEAD>
 *
 * @ingroup net::io::packetable
 *
 * @brief Stream(TCP)�� packetable Class
 *
 *   TCP������ ���۵� ���۵� packetable�̴�.
 *   ���۹޾ƿ� �����͸� message������ �߶� Imessageable�� �Ѱ��ִ� ������ �Ѵ�.
 *   Steam���� ���������� ���޵Ǿ� ���� �������� head�� �о� ������ message
 *      ũ��� ������ Imessageable�� process_message()�Լ��� ȣ���� �������ش�.
 *
 */
 //-----------------------------------------------------------------------------
template <class TMSG_HEAD = uint32_t>
class net::io::packetable::Nstream :
// inherited classes)
	virtual public				net::io::Isocket,
	virtual public				net::io::Ipacketable,
	virtual public				Imessageable,
	virtual public				net::io::statistics::Nsocket
{
// definitions)
public:
			using TMESSAGE_HEAD = TMSG_HEAD;

// implementation)
protected:
	virtual	void				process_pre_message(sMESSAGE_NETWORK& /*_msg*/) {}
	virtual	std::size_t			process_packet(shared_buffer& _buffer, const net::sockaddr& _address_peer) override
	{
		// check) _buffer.data_�� 0�̾�� �ȵȴ�.
		THROW_IF(_buffer.data() == nullptr, throwable::failure(eRESULT::INVALID_MESSAGE_BUFFER_IS_NULL), LOG_DEBUG << "(err ) _buffer.data_ is nullptr " __CGFUNCTION__ ""sv);

		// check) _buffer->size_�� 0�̾�� �ȵȴ�.
		CGASSERT_ERROR(_buffer.size() != 0)

		// declare) 
		int count_message = 0; // ó���� ��Ŷ ���� ó���� ����...

		// declare) �ӽ� sMESSAGE_NETWORK (���޿�)
		sMESSAGE_NETWORK msg;

		// 1) shared_buffer�� Address�� length�� ��ִ´�.
		shared_buffer message = _buffer ^ sizeof(TMESSAGE_HEAD);

		// loop) remained_size�� GetSizeOfPacketHead()���� ������ ����.
		std::size_t remained_size = _buffer.size();

		try
		{
			while(remained_size >= sizeof(TMESSAGE_HEAD))
			{
				// 2) message ���̸� ���Ѵ�.
				auto message_size = definition_message_header<TMESSAGE_HEAD>::_get_message_size(message);

				// 3) set size;
				((buffer_view&)message).set_size(message_size);

				// check) ���� tempNetBuffer.size_�� TMESSAGE_HEAD���� ������ �߸��� ���̹Ƿ� Exception�� ������.
				//        (����: messageũ�Ⱑ 0Byte�� ��� Exception�� ������ ������ ���ѷ����� ���������� �ִ�.)
				THROW_IF(message_size < sizeof(TMESSAGE_HEAD), throwable::failure(eRESULT::INVALID_MESSAGE_TOO_SHORT_LENGTH), LOG_DEBUG << "(err ) message size is too short. message size: "sv << message_size << " " __CGFUNCTION__ ""sv);

				// check) MessageHeadũ�� ���� ������ ����������.
				BREAK_IF(message_size > remained_size);

				// 3) ���޿� shared_buffer�� address�� length�� ��ִ´�.
				msg.buf_message = message;
				msg.address = _address_peer;

				// debug)
			#if !defined(NDEBUG)
				if (this->is_socket_debug_logging_enabled())
					net::io::_debug_log_socket_on_message(this->native_handle(), message);
			#endif

				// 4) process message
				{
					// - ���Լ� process_pre_message()�� ȣ���Ѵ�.
					this->process_pre_message(msg);

					// - message�� Imessageable�� �����Ͽ� ó���Ѵ�.
					this->process_message(msg);

					// - History�� Queueing�Ѵ�.
					this->push_message_to_history(message);
				}

				// 7) message���� ������Ų��.
				++count_message;

				// 8) message Data�� �̵���Ų��.
				((buffer_view&)message).add_data(message_size);
				remained_size -= message_size;

				// check) ������ ����Ǿ����� �ٷ� ������.
				if (this->is_invalid_native_handle())
				{
					// - ����) remained_size�� 0���� ���ִ� ������ ReminedSize�� RequiredSize�� ���Ͽ�
					//         ó���ϴ� �κ��� �����Ƿ� ������ ���� ó���� �ߴܿ����� Remained�� 0���� ������ �־�� �Ѵ�.
					//         �� ������ ������ ������ ����Ǵ� ���̹Ƿ� ��� �����͵��� ��� ó���� ������ ������ �ʿ䰡 �ִ�!
					remained_size = 0;

					// break) 
					break;
				}
			}
		}
		catch(...)
		{
			// statistiscs) �̶����� ó���� Packet�� ���ó���� �Ѵ�.
			this->statistics_on_receive_message(count_message);

			// reraise) 
			throw;
		}

		// statistics) receive message���� ������.
		this->statistics_on_receive_message(count_message);

		// 9) ���� message�� �����Ѵ�.
		_buffer = buffer_view(message.data(), remained_size);

		// return) ���� message�� ũ�⸦ return�Ѵ�.
		return static_cast<std::size_t>(message.size());
	}
	virtual	void				process_reset_packetable() noexcept override { this->reset_message_history();}
};


}