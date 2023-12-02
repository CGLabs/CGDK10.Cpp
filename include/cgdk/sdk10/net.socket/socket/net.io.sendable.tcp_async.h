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

 ���� �⺻���� ������ ���ŷ ������ �����Ѵ�.
 Overlapped�� ����� �񵿱� �ۼ����� ��� ���� �����͸� ������� �ʰ� ������ ��� ������ ������尡 �� Ŭ�� �ִ�.
 �� sendable Ŭ������ ���� �������� ������ ó�� ������ ���� ���� ������ ���� Ʈ������ ���� �ʴٸ� ������ �� ���� ȿ���� ���� �ִ�.
 ���� ���¿� ���� �ƹ��� ���۵� ó������ �ʱ� ������ ��뷮�� ���ۿ��� ��ȿ������ �� ������ ���۷��� ������ ������ ������ ���� �ִ�.
 
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