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

 @class		Ntcp_async_gather_buffered
 @brief
 @todo		
 @ref		
 @details	\n

 */
//-----------------------------------------------------------------------------
class net::io::sendable::Ntcp_async_gather_buffered :
	public						net::io::sendable::Itcp_gather,
	virtual public				net::io::Isender_closser
{
public:

		#if defined(_WINSOCK2API_)
			using QUEUE_SEND = net::io::sendable::QUEUE_SEND_bufferd;
		#elif defined(_SYS_EPOLL_H)
			template <class T> using container_t = std::list<T>;
			struct QUEUE_SEND
			{
				struct NODE
				{
					buffer_view		buf_send;
					object_ptr<Ireferenceable> powner;

					std::size_t		bytes_data = 0;
					std::size_t		count_message = 0;
					std::size_t		bytes_remained = 0;
				};

				container_t<NODE> array_node;
				std::size_t		bytes_data = 0;

				void clear() noexcept;
				void push_back(const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_messages);
			};
		#endif

protected:
	virtual	bool				process_sendable( const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _paddress) override;
	virtual	void				process_complete_sendable(uintptr_t _result, std::size_t _transferred_bytes, std::size_t _transferred_message) override;
	#if defined(_SYS_EPOLL_H)
			bool				process_sendable_async(CGSOCKET _handle_socket, const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message);
	virtual	uint32_t			process_recover_sendable(intptr_t _event, std::size_t _param);
			void				_process_clear_send_buffers();
	#endif
	virtual	std::size_t			process_get_sending_queued_bytes() const noexcept override;
	virtual	void				process_close_sender() override;
	virtual	void				process_reset_sendable() noexcept override;

protected:
			lockable<>			m_lockable_sending;
			QUEUE_SEND			m_queue_pending;
			QUEUE_SEND			m_queue_sending;
			bool				m_flag_sending{ false };

		#if defined(_WINSOCK2API_)
			object_ptr<executable_send_buffer_list> m_pexecutable_send_buffer_list;
		#endif
};


}