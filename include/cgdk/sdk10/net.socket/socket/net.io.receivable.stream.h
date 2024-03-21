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
@brief ��Ʈ��(TCP)�� ������ I/O receive ó�� Ŭ����

TCP�� ���� Stream���� ���޵Ǿ� ���� �������� receive�� ó���ϴ� class�̴�.
������ Pro-Actor������ IOCP�� �����Ǿ� �ֱ� ������ ���Ӱ� ���ÿ� prepare_receive()�Լ��� ȣ���Ͽ�
receive�� �ɾ���´�.
Streamó���̱� ������ ���ÿ� �ѹ��� receive I/O�� �ɾ���´�.
receive �Ϸ�� �� ���� message�� ������ �� ó���� �� �ٽ� receive�� �ɵ��� ����Ǿ���.
�̷� ���� �뷮�� �����͸� receive�� ��� ó���� ������ �� �ִ�.
receive�� �Ϸᰡ 0Byte Ȥ�� Error�� �Ǹ� ���� ����ó���� �Ѵ�.

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
	//! @brief '���Ϻ� �ּ� �޽��� ����'�� �����Ѵ�.
			std::size_t			minimum_message_buffer_size(std::size_t _size) noexcept;
	[[nodiscard]] std::size_t	minimum_message_buffer_size() noexcept;

			std::size_t			maximum_message_buffer_size(std::size_t _size) noexcept;
	[[nodiscard]] std::size_t	maximum_message_buffer_size() noexcept;

	//! @brief �޾� ���� ������ �� ó������ ���� ����Ʈ Byte��.
	[[nodiscard]] std::size_t	queued_receive_bytes() const noexcept { return m_buffer_received.size(); }

// frameworks)
protected:
	//! @brief �����͸� ���� ���� �� ȣ��Ǵ� �Լ�.
	virtual	void				on_receive( const buffer_view& /*_buffer*/, const net::sockaddr& /*_address*/)	{}

// implementation)
protected:
	//! @brief receive�� �Ŵ� �Լ�. @return true true ���� @return true false ����
	#if defined(_WINSOCK2API_)
			bool				receive();
	#elif defined(_SYS_EPOLL_H)
	#endif

	//! @brief receivable�� �ʱ�ȭ�Ѵ�.
	virtual	void				process_reset_receivable() override;

	//! @brief ���� ���� �� receive�� �غ��Ѵ�.
	virtual	bool				prepare_receive() override;

	//! @brief receive�� �޾��� �� ȣ��ȴ�. @return 0 ���� @return !0 ����
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

			shared_buffer		m_buffer_received; // ���� �޽��� ó���ϱ� ���� ���� �ܷ� buffer...
			WSABUF				m_wsabuf_receiving; // receive�� �ɾ� ���� shared_buffer...
			DWORD				m_wsa_bytes_received{ 0 };
			DWORD				m_wsa_flag{ 0 };

			object_ptr<executable_receiving> m_pexecutable_receiving; //! @brief receive�� ó���� Iexecutable ��ü
		#elif defined(_SYS_EPOLL_H)
			shared_buffer		m_buffer_received; // ���� �� ó������ ���� ���� ������
			int					m_bytes_buffer_receive; // ���� ���� ������ ũ��
		#endif
};

namespace net::io::receivable
{
	//! @brief '�⺻ �ּ� �޽��� ���� ũ��'�� �����Ѵ�. @param _bytes_size ������ '�⺻ �ּ� �޽��� ���� ũ��'
	void	default_message_buffer_min_size(std::size_t _bytes_size);
	//! @brief '�⺻ �ִ� �޽��� ���� ũ��'�� �����Ѵ�. @param _bytes_size ������ '�⺻ �ִ� �޽��� ���� ũ��'
	void	default_message_buffer_max_size(std::size_t _bytes_size);
	//! @brief '�⺻ �޽��� ���� ũ��'�� �����Ѵ�. @param _bytes_size_min ������ '�⺻ �ּ� �޽��� ���� ũ��' @param _bytes_size_max ������ '�⺻ �ִ� �޽��� ���� ũ��'
	void	set_default_packet_buffer_size(std::size_t _bytes_size_min, std::size_t _bytes_size_max);
	//! @brief '�⺻ �ּ� �޽��� ���� ũ��'�� ��´�. @return ������ '�⺻ �ּ� �޽��� ���� ũ��'
	std::size_t	default_message_buffer_min_size();
	//! @brief '�⺻ �ִ� �޽��� ���� ũ��'�� ��´�. @return ������ '�⺻ �ִ� �޽��� ���� ũ��'
	std::size_t	default_message_buffer_max_size();
}


}