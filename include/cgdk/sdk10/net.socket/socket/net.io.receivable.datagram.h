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
* @class Ndatagram
*
* @ingroup net::io::receivable
*
* @brief Datagram(UDP)�� ������ ������ ó���ϴ� Ŭ����
*
*   UDP�� receive ó���� ������ Ŭ�����̴�. 
*   UDP�� receive�� ������ ������� �ʰ� �ϳ��� socket�� ���� ���� peer�κ��� 
*   ������ �ޱ� ������ �ִ��� ������ �ٽ� receive�� ���� �� �ֵ��� ����Ǿ�����
*   ���ÿ� ���� ���� receive�� ��û�� ���´�.
*   ������ I/O ��ġ�� API Ȥ�� ó�� ����� ���� �޶����� �ִ�.
*
*   receive�� �ްԵ� buffer�� ũ�⸦ �����ϰ� ������ �־���Ѵ�.
*   ���� receive�� buffer���� �� ū Packet�� ���޵Ǿ� �� ��� Lost�Ǳ� �����̴�.
*   receive�� ������ ũ�⸦ ������ ��� �ݵ�� bind�ϱ� ���� ���־�� �Ѵ�.
*   set_receive_buffer_size()�Լ��� ����Ͽ� receive�� ������ ũ�⸦ ������ �� �ִ�.
*   (Default�� SIZE_OF_RECEIVE_BUFFER)
*/
//-----------------------------------------------------------------------------
class net::io::receivable::Ndatagram : 
// inherited classes)
	virtual public				net::io::Isocket,
	virtual	public				net::io::Ireceivable_datagram,
	virtual public				net::io::Ipacketable,
	virtual public				net::io::statistics::Nsocket
{
// constructor/destructor)
protected:
			Ndatagram() noexcept;
	virtual	~Ndatagram() noexcept {}

// publics)
public:
	[[nodiscard]] std::size_t	get_message_size() const { return this->m_message_buffer_size;}
			void				set_message_size(std::size_t _message_size);

	[[nodiscard]] std::size_t	get_prepare_receive_count() const;
			void				set_prepare_receive_count(std::size_t _count);

	virtual	void				suspend_receive();
	virtual	void				resume_receive();

// frameworks)
protected:
	// 1) receive�� �������� �� ȣ��Ǵ� �Լ�.
	virtual	void				on_receive( const buffer_view& /*_buffer*/, const net::sockaddr& /*_address*/) {}

	// 2) �������� �� ȣ��Ǵ� Hook�Լ�.
	virtual void				on_fail_receive( int /*_error_code*/, const buffer_view& /*_buffer*/, const net::sockaddr& /*_address*/) {}

	// 3) Overlapped�� �ɾ� ���� ReceiveReceive�� 0���� �Ǿ��� �� ȣ��Ǵ� �Լ�.
	virtual	void				on_receive_exhausted() {}

// implementation)
public:
	// 1) process_complete_receivable()�� ������. 
	virtual void				process_on_receive( const buffer_view& _buffer, const net::sockaddr& _address) { on_receive(_buffer, _address); }
	virtual	intptr_t			process_complete_receivable( uintptr_t _result, std::size_t _transferred, shared_buffer& _buffer, const net::sockaddr& _address) override;

	// 2) reset�Ҷ� ȣ���ϴ� �Լ�.(Ư���� ������ ���� �����Ƿ� �����.)
	virtual	void				process_reset_receivable() override {}
	 
	// 3) prepare receive
	virtual	bool				prepare_receive() override;

		#if defined(_WINSOCK2API_)
			class				executable_receive;
		#endif

private:
			std::size_t			m_message_buffer_size;

		#if defined(_WINSOCK2API_)
			std::size_t			m_prepare_receive_count;
		#endif
};


}