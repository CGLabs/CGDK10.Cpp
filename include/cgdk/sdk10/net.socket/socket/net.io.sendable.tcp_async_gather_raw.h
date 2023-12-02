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

#if defined(_WINSOCK2API_)
namespace CGDK
{
//-----------------------------------------------------------------------------
/**

 @class		Ntcp_async_gather_raw
 @brief		
 @todo		
 @ref		
 @details	\n

 */
//-----------------------------------------------------------------------------
class net::io::sendable::Ntcp_async_gather_raw :
	public						net::io::sendable::Itcp_gather,
	virtual public				net::io::Isender_closser
{
public:
			struct NODE
			{
				Ireferenceable* psource{ nullptr };
			};

			struct QUEUE_SEND
			{
				char* allocated{ nullptr };
				WSABUF*		array_wsabuffer{nullptr};
				NODE*		array_node{nullptr};
				size_t		capacity_node{ 0 };

				size_t		count_node{ 0 };
				size_t		bytes_data{ 0 };
				size_t		count_message{ 0 };

				~QUEUE_SEND();
				void buffer_prepare();
				void buffer_alloc(std::size_t _count);
				void buffer_free() noexcept;
				void buffer_reset() noexcept;
				void buffer_reset_and_swap(QUEUE_SEND&& _move) noexcept;
				void buffer_push_back(const buffer_view& _buffer, Ireferenceable* _owner, std::size_t _count_messages);
				void buffer_expand();
				bool is_empty() const noexcept { return this->array_wsabuffer == nullptr; }
				bool is_full() const noexcept { return this->count_node == this->capacity_node; }
			};

// publics)
protected:
	virtual	bool				process_sendable(const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _paddress) override;
	virtual	void				process_complete_sendable( uintptr_t _result, std::size_t _transferred_bytes, std::size_t _transferred_message) override;
			bool				process_sendable_async(CGSOCKET _handle_socket, const buffer_view& _buffer, Ireferenceable* _psource, std::size_t _count_message);
	virtual	std::size_t			process_get_sending_queued_bytes() const noexcept override;
	virtual	void				process_close_sender() override;
	virtual	void				process_reset_sendable() noexcept override;

protected:
			QUEUE_SEND			m_queue_pending;
			QUEUE_SEND			m_queue_sending;
			bool				m_flag_sending = false;
			object_ptr<executable_send_buffer_list> m_pexecutable_send_buffer_list;

			lockable<>			m_lockable_sending;
			void				_process_prepare_send_buffers();
};


}
#endif