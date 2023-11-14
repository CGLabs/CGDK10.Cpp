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

 @class		Ntcp_async
 @brief		
 @todo		
 @ref		
 @details	\n

 가장 기본적인 형태인 블록킹 전송을 수행한다.
 Overlapped를 사용한 비동기 송수신의 경우 적은 데이터를 빈번하지 않게 전송할 경우 오히려 오버헤드가 더 클수 있다.
 이 sendable 클래스는 전송 과정에서 복잡한 처리 과정이 일절 없기 때문에 전송 트래픽이 높지 않다면 오히려 더 좋은 효율을 낼수 있다.
 전송 상태에 대한 아무런 동작도 처리하지 않기 때문에 대용량의 전송에는 비효율적일 수 있으며 전송량이 많으면 접속이 끊어질 수도 있다.
 
*/
//-----------------------------------------------------------------------------
class net::io::sendable::Ntcp_async :
	public						net::io::sendable::Itcp_gather,
	virtual public				net::io::Isender_closser
{
public:
		#if defined(_SYS_EPOLL_H)
			template <class T> using container_t = std::list<T>;
			struct QUEUE_SEND
			{
				struct NODE
				{
					buffer_view		buf_send;
					object_ptr<Ireferenceable> powner;
					std::size_t		bytes_data = 0;
					std::size_t		count_message = 0;
				};

				container_t<NODE> array_node;
				std::size_t		bytes_data = 0;

				void clear() noexcept;
			};
		#endif

			Ntcp_async();
	virtual ~Ntcp_async() noexcept;

// publics)
protected:
	virtual	bool				process_sendable(const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _paddress) override;
	virtual	void				process_complete_sendable(uintptr_t _result, std::size_t _transferred_bytes, std::size_t _transferred_message) override;
	virtual	void				process_close_sender() override;
	virtual	void				process_reset_sendable() noexcept override;
	virtual	std::size_t			process_get_sending_queued_bytes() const noexcept override;

#if defined(_WINSOCK2API_)
			int					m_count_pended = 0;
			size_t				m_bytes_pended = 0;
#elif defined(_SYS_EPOLL_H)
	virtual	uint32_t			process_recover_sendable(intptr_t _event, std::size_t _param);
			void				_process_clear_send_buffers();

protected:
			QUEUE_SEND			m_queue_pending;
			QUEUE_SEND			m_queue_sending;
			bool				m_flag_sending = false;
#endif
			lockable<>			m_lockable_sending;
};


}