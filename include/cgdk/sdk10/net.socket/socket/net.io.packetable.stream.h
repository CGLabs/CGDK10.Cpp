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
 * @brief Stream(TCP)용 packetable Class
 *
 *   TCP용으로 제작된 제작된 packetable이다.
 *   전송받아온 데이터를 message단위로 잘라서 Imessageable에 넘겨주는 역할을 한다.
 *   Steam으로 연속적으로 전달되어 오는 데이터의 head를 읽어 설정된 message
 *      크기로 나누어 Imessageable의 process_message()함수를 호출해 전달해준다.
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
		// check) _buffer.data_가 0이어서는 안된다.
		THROW_IF(_buffer.data() == nullptr, throwable::failure(eRESULT::INVALID_MESSAGE_BUFFER_IS_NULL), LOG_DEBUG << "(err ) _buffer.data_ is nullptr " __CGFUNCTION__ ""sv);

		// check) _buffer->size_가 0이어서는 안된다.
		CGASSERT_ERROR(_buffer.size() != 0)

		// declare) 
		int count_message = 0; // 처리한 패킷 수의 처리르 위해...

		// declare) 임시 sMESSAGE_NETWORK (전달용)
		sMESSAGE_NETWORK msg;

		// 1) shared_buffer의 Address와 length를 써넣는다.
		shared_buffer message = _buffer ^ sizeof(TMESSAGE_HEAD);

		// loop) remained_size가 GetSizeOfPacketHead()보다 작으면 끝냄.
		std::size_t remained_size = _buffer.size();

		try
		{
			while(remained_size >= sizeof(TMESSAGE_HEAD))
			{
				// 2) message 길이를 구한다.
				auto message_size = definition_message_header<TMESSAGE_HEAD>::_get_message_size(message);

				// 3) set size;
				((buffer_view&)message).set_size(message_size);

				// check) 만약 tempNetBuffer.size_이 TMESSAGE_HEAD보다 작으면 잘못된 것이므로 Exception을 던진다.
				//        (주의: message크기가 0Byte일 경우 Exception을 던지지 않으면 무한루프에 빠져버릴수 있다.)
				THROW_IF(message_size < sizeof(TMESSAGE_HEAD), throwable::failure(eRESULT::INVALID_MESSAGE_TOO_SHORT_LENGTH), LOG_DEBUG << "(err ) message size is too short. message size: "sv << message_size << " " __CGFUNCTION__ ""sv);

				// check) MessageHead크기 보다 작으면 빠져나간다.
				BREAK_IF(message_size > remained_size);

				// 3) 전달용 shared_buffer에 address와 length를 써넣는다.
				msg.buf_message = message;
				msg.address = _address_peer;

				// debug)
			#if !defined(NDEBUG)
				if (this->is_socket_debug_logging_enabled())
					net::io::_debug_log_socket_on_message(this->native_handle(), message);
			#endif

				// 4) process message
				{
					// - 훅함수 process_pre_message()를 호출한다.
					this->process_pre_message(msg);

					// - message를 Imessageable로 전달하여 처리한다.
					this->process_message(msg);

					// - History에 Queueing한다.
					this->push_message_to_history(message);
				}

				// 7) message수를 증가시킨다.
				++count_message;

				// 8) message Data를 이동시킨다.
				((buffer_view&)message).add_data(message_size);
				remained_size -= message_size;

				// check) 접속이 종료되었으면 바로 끝낸다.
				if (this->is_invalid_native_handle())
				{
					// - 주의) remained_size를 0으로 해주는 이유는 ReminedSize와 RequiredSize를 비교하여
					//         처리하는 부분이 있으므로 오류로 인한 처리의 중단에서는 Remained를 0으로 설정해 주어야 한다.
					//         즉 어차피 소켓이 비정상 종료되는 것이므로 모든 데이터들이 모두 처리된 것으로 설정할 필요가 있다!
					remained_size = 0;

					// break) 
					break;
				}
			}
		}
		catch(...)
		{
			// statistiscs) 이때까지 처리된 Packet의 통계처리를 한다.
			this->statistics_on_receive_message(count_message);

			// reraise) 
			throw;
		}

		// statistics) receive message수를 세린다.
		this->statistics_on_receive_message(count_message);

		// 9) 남은 message를 설정한다.
		_buffer = buffer_view(message.data(), remained_size);

		// return) 다음 message의 크기를 return한다.
		return static_cast<std::size_t>(message.size());
	}
	virtual	void				process_reset_packetable() noexcept override { this->reset_message_history();}
};


}