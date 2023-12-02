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

 @class		Ntcp_async_gather_rio
 @brief		
 @todo		
 @ref		
 @details	\n
  
*/
//-----------------------------------------------------------------------------
class net::io::sendable::Ntcp_async_gather_rio :
	public						net::io::sendable::Itcp_gather,
	virtual public				net::io::Isender_closser
{
public:
			struct NODE
			{
				object_ptr<Ireferenceable> powner;
			};

			struct QUEUE_SEND
			{
				shared_buffer	allocated;
				LPWSABUF		array_buffer = nullptr;
				NODE*			array_node = nullptr;
				std::size_t		count_node = 0;
				std::size_t		bytes_data = 0;
				std::size_t		count_message = 0;

				void buffer_alloc(std::size_t _count);
				void buffer_free() noexcept;
				void buffer_move(QUEUE_SEND&& _move) noexcept;
				bool is_empty() const noexcept { return array_buffer == nullptr; }
			};

protected:
	virtual	bool				process_sendable( const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _paddress) override;
	virtual	void				process_complete_sendable( uintptr_t _result, std::size_t _transferred_bytes, std::size_t _transferred_message) override;
			bool				process_sendable_async(CGSOCKET _handle_socket, const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message);
	virtual	std::size_t			process_get_sending_queued_bytes() const noexcept override;
	virtual	void				process_close_sender() override;
	virtual	void				process_reset_sendable() noexcept override;

protected:
			QUEUE_SEND			m_queue_pending;
			QUEUE_SEND			m_queue_sending;
			char*				m_ptr_queued_buffer_tail = nullptr;
			NODE				m_temp_queued_send;
			bool				m_flag_sending = false;

			lockable<>			m_lockable_sending;
			void				_process_prepare_send_buffers();
};


}