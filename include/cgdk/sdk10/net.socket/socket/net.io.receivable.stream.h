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
/**

@class		Nstream
@brief 스트림(TCP)용 저수준 I/O receive 처리 클래스

TCP와 같이 Stream으로 전달되어 오는 데이터의 receive를 처리하는 class이다.
구현은 Pro-Actor패턴인 IOCP로 구현되어 있기 때문에 접속과 동시에 prepare_receive()함수를 호출하여
receive을 걸어놓는다.
Stream처리이기 때문에 동시에 한번의 receive I/O만 걸어놓는다.
receive 완료된 후 받은 message를 완전히 다 처리한 후 다시 receive를 걸도록 설계되었다.
이로 인해 대량의 데이터를 receive할 경우 처리가 지연될 수 있다.
receive의 완료가 0Byte 혹은 Error로 되면 접속 종료처리를 한다.

@todo
@ref		net::io::Receiveable::Nstream_queue, net::io::Receiveable::Nstream_rio 
@details	\n

*/
//-----------------------------------------------------------------------------
class net::io::receivable::Nstream :
// inherited classes)
	virtual public				net::io::Isocket,
	virtual public				net::io::Ireceivable_stream,
	virtual public				net::io::Iconnectable,
	virtual public				net::io::Ipacketable
{
// constructor/destructor)
protected:
			Nstream();
	virtual	~Nstream() noexcept;

// public)
public:
	//! @brief '소켓별 최소 메시지 버퍼'를 설정한다.
			std::size_t			minimum_message_buffer_size(std::size_t _size) noexcept;
	[[nodiscard]] std::size_t	minimum_message_buffer_size() noexcept;

			std::size_t			maximum_message_buffer_size(std::size_t _size) noexcept;
	[[nodiscard]] std::size_t	maximum_message_buffer_size() noexcept;

	//! @brief 받아 놓은 데이터 중 처리되지 않은 데이트 Byte수.
	[[nodiscard]] std::size_t	queued_receive_bytes() const noexcept { return m_buffer_received.size(); }

// frameworks)
protected:
	//! @brief 데이터를 수신 했을 때 호출되는 함수.
	virtual	void				on_receive( const buffer_view& /*_buffer*/, const net::sockaddr& /*_address*/)	{}

// implementation)
protected:
	//! @brief receive를 거는 함수. @return true true 성공 @return true false 실패
	#if defined(_WINSOCK2API_)
			bool				receive();
	#elif defined(_SYS_EPOLL_H)
	#endif

	//! @brief receivable을 초기화한다.
	virtual	void				process_reset_receivable() override;

	//! @brief 최초 접속 시 receive를 준비한다.
	virtual	bool				prepare_receive() override;

	//! @brief receive를 받았을 때 호출된다. @return 0 성공 @return !0 실패
	virtual void				process_on_receive( const buffer_view& _buffer, const net::sockaddr& _address) { on_receive (_buffer, _address);}
	virtual	intptr_t			process_complete_receivable( intptr_t _result, std::size_t _transferred) override;
			void				process_clear_buffer() noexcept;

protected:
			std::size_t			m_minimum_mesage_buffer_size;
			std::size_t			m_maximum_message_buffer_size;

		#if defined(_WINSOCK2API_)
			class executable_receiving : virtual public Iexecutable, public Npoolable<executable_receiving>, public factory::_traits_system
			{
			public:
				Nstream*		m_preceivable_stream = nullptr;
				virtual	intptr_t process_execute( intptr_t _result, std::size_t _param);
			};

			class executable_receiving_dispatch : public executable_receiving
			{
			public:
				virtual	intptr_t process_execute(intptr_t _result, std::size_t _param);
			};

			shared_buffer		m_buffer_received; // 현재 메시지 처리하기 위해 남은 잔량 buffer...
			WSABUF				m_wsabuf_receiving; // receive를 걸어 놓은 shared_buffer...
			DWORD				m_wsa_bytes_received{ 0 };
			DWORD				m_wsa_flag{ 0 };

			object_ptr<executable_receiving> m_pexecutable_receiving; //! @brief receive를 처리할 Iexecutable 객체
		#elif defined(_SYS_EPOLL_H)
			shared_buffer		m_buffer_received; // 수신 후 처리되지 않은 남은 데이터
			int					m_bytes_buffer_receive; // 현재 수신 버퍼의 크기
		#endif
};

namespace net::io::receivable
{
	//! @brief '기본 최소 메시지 버퍼 크기'를 설정한다. @param _bytes_size 설정할 '기본 최소 메시지 버퍼 크기'
	void	default_message_buffer_min_size(std::size_t _bytes_size);
	//! @brief '기본 최대 메시지 버퍼 크기'를 설정한다. @param _bytes_size 설정할 '기본 최대 메시지 버퍼 크기'
	void	default_message_buffer_max_size(std::size_t _bytes_size);
	//! @brief '기본 메시지 버퍼 크기'를 설정한다. @param _bytes_size_min 설정할 '기본 최소 메시지 버퍼 크기' @param _bytes_size_max 설정할 '기본 최대 메시지 버퍼 크기'
	void	set_default_packet_buffer_size(std::size_t _bytes_size_min, std::size_t _bytes_size_max);
	//! @brief '기본 최소 메시지 버퍼 크기'를 얻는다. @return 설정된 '기본 최소 메시지 버퍼 크기'
	std::size_t	default_message_buffer_min_size();
	//! @brief '기본 최대 메시지 버퍼 크기'를 얻는다. @return 설정된 '기본 최대 메시지 버퍼 크기'
	std::size_t	default_message_buffer_max_size();
}


}