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

 @class		Itcp_gather
 @brief		�񵿱� ��� ������ �����ϴ� sendable Ŭ����
 @todo		
 @ref		
 @details	\n

 �񵿱� �۽� ���� ��쳪 ������ �۽Ź��۰� ���� ���ŷ�� ����(WOULD_BLOCK)�� ������ �� 
 send�� ��û�ϸ� ť���� ���Ҵٰ� �񵿱Ⱑ �Ϸ�ǰų� ���ŷ�� �����Ǹ� ��� ���Ҵ� �����͸� 
 �����ϴ� sendableŬ�����̴�.
 �۽��� �񵿱������� ���������ν� �۽� ������ �ش�ȭ�ϰ� CPU�� ����� �ּ�ȭ �Ҽ� �ִ�.
 
*/
//-----------------------------------------------------------------------------
class net::io::sendable::Itcp_gather :
	virtual public				net::io::Isendable,
	virtual public				net::io::Iconnectable
{
public:
			Itcp_gather() noexcept;

public:
	[[nodiscard]] size_t		maximum_depth_of_send_buffer() const noexcept { return this->m_max_depth_of_send_buffer; }
			void				maximum_depth_of_send_buffer(std::size_t _depth) noexcept;
	[[nodiscard]] size_t		maximum_depth_of_send_buffer_bytes() const noexcept { return this->m_bytes_max_queued; }
			void				maximum_depth_of_send_buffer_bytes(std::size_t _size) noexcept;
	[[nodiscard]] size_t		sending_queued_bytes_now() const noexcept { return this->process_get_sending_queued_bytes(); }

	static	void				default_maximum_depth_of_send_buffer(std::size_t _max) noexcept;
	[[nodiscard]] static size_t default_maximum_depth_of_send_buffer() noexcept;
	static	void				default_maximum_queued_bytes(std::size_t _max) noexcept;
	[[nodiscard]] static size_t default_maximum_queued_bytes() noexcept;

protected:
	virtual	std::size_t			process_get_sending_queued_bytes() const noexcept PURE;

protected:
			std::size_t			m_bytes_max_queued;
			std::size_t			m_max_depth_of_send_buffer;

	static	std::size_t			m_s_default_max_queued_bytes;
	static	std::size_t			m_s_default_max_depth_of_send_buffer;
};


}