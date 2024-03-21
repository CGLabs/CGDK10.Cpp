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
* @class Nstream_queue
*
* @ingroup net::io::receivable
*
* @brief 대규모 스트림(TCP) 데이터 수신을 위해 최적화된 저수준 I/O IReceivable 클래스
*
*  TCP와 같이 Stream으로 전달되어 오는 데이터의 receive를 처리하는 class이다.
*  Nstream과 구현은 유사하지나 차이점은 데이터를 받은 후 최대한 빨리 다시 receive를 
*  수행한다는 것이다. 그리고 데이터의 처리는 다른 쓰레드에서 처리하도록 되어 있다.
*  이때 데이터의 처리는 순서가 보장된다.
*  파일 수신 서버와 같이 대규모 데이터를 수신할 경우 최적의 성능을 낼수 있다.
*  하지만 데이터의 처리가 적을 경우 오히려 복잡한 동작으로 추가적인 부하만 만들 수 있다.
*
* @see net::io::Receiveable::Nstream
* @see net::io::Receiveable::Nstream_rio
*
*/
//-----------------------------------------------------------------------------
class net::io::receivable::Nstream_queue :
// inherited classes)
	virtual public				net::io::Isocket,
	virtual public				net::io::Ireceivable_stream,
	virtual public				net::io::Iconnectable,
	virtual public				net::io::Ipacketable
{
// constructor/destructor)
protected:
			Nstream_queue();
	virtual	~Nstream_queue() noexcept;

// public)
public:
	// 1) sustain Torrence 관련 함수.
	[[nodiscard]] std::size_t	max_received_bytes_queued() const { return m_max_received_bytes_queued;}
			void				max_received_bytes_queued(std::size_t _max)	{ m_max_received_bytes_queued= _max;}

	//! @brief '소켓별 최소 메시지 버퍼'를 설정한다.
				  std::size_t	minimum_message_buffer_size(std::size_t _size) noexcept;
	[[nodiscard]] std::size_t	minimum_message_buffer_size() noexcept;

				  std::size_t	maximum_message_buffer_size(std::size_t _size) noexcept;
	[[nodiscard]] std::size_t	maximum_message_buffer_size() noexcept;

	// 2) Received Data
	[[nodiscard]] std::size_t	queued_receive_bytes() const { return m_byte_queued_receive;}
	[[nodiscard]] std::size_t	queued_receive_io() const { return m_queue_received.size();}

// frameworks)
protected:
	// 3) 일반적인 On함수.
	virtual	void				on_receive( const buffer_view& /*_buffer*/, const net::sockaddr& /*_address*/)	{}

// implementation)
protected:
	// 1) Buffers
			shared_buffer		m_buffer_receiving;

	// 2) send Queue
			lockable<>			m_lockable_queue_received;
			std::list<shared_buffer> m_queue_received;
			std::size_t			m_byte_queued_receive;

	// 3) Packet Processing관련
			shared_buffer		m_buf_processing;
			std::size_t			m_bytes_required;

	// 4) buffer size
			std::size_t			m_max_received_bytes_queued;

protected:
	// 6) receive함수.
			bool				receive();

	// 7) reset할 때 호출하는 함수.
	virtual	void				process_reset_receivable() override;

	// 8) prepare receive
	virtual	bool				prepare_receive() override;

	//! @brief receive를 받았을 때 호출된다. @return 0 성공 @return !0 실패
	virtual void				process_on_receive (const buffer_view& _buffer, const net::sockaddr& _address) { on_receive(_buffer, _address); }
	virtual	intptr_t			process_complete_receivable (intptr_t _result, std::size_t _transferred) override;

private:
			std::size_t			m_minimum_mesage_buffer_size;
			std::size_t			m_maximum_message_buffer_size;

	// 10) process message
			void				queue_received_message( const shared_buffer& _buffer);
			void				queue_close_message();
			bool				post_received_buffer();
			void				process_received_buffer();

	// 11) executable for Process receive
		#if defined(_WINSOCK2API_)
			class executable_receiving : virtual public Iexecutable, public Npoolable<executable_receiving>, public factory::_traits_system
			{
			public:
				Nstream_queue*	m_preceivable_stream = nullptr;
				virtual	intptr_t process_execute( intptr_t _result, std::size_t _param) override;
				virtual void	on_final_release() noexcept override;
			};

			class executable_received : virtual public Iexecutable, public Npoolable<executable_received>, public factory::_traits_system
			{
			public:
				Nstream_queue*	m_preceivable_stream = nullptr;
				virtual	intptr_t process_execute( intptr_t _result, std::size_t _param) override;
			};

			object_ptr<executable_receiving> m_pexecutable_receiving;
			object_ptr<executable_received>	m_pexecutable_received;

			WSABUF				m_wsabuf_receiving{ 0,0 };	// receive를 걸어 놓은 buffer...
			DWORD				m_wsa_bytes_received{ 0 };
			DWORD				m_wsa_flag{ 0 };
		#elif defined(_SYS_EPOLL_H)
		#endif
};


}