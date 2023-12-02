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
//
// net::io::Isendable
//
// 1. net::io::Isendable��~
//    1) �����͸� ������ I/O�Լ��� ����Ͽ� ������ ������ ó���� �����ϴ� �Լ�.
//    2) process_send()�� �������� ������ ��û�ϴ� ó�� ������ �����ϴ� �Լ�.
//    3) process_complete_sendable()�� �������� ������ �Ϸ�Ǿ��� �� ȣ��Ǿ� ó��
//       ������ �����ϴ� �Լ��̴�.
//
//-----------------------------------------------------------------------------
class net::io::Isendable : virtual public Ireferenceable
{
public:
	//! @brief ���� ó�� ������ �����ϴ� �Լ�. @param _array_buffer ������ ���� �迭 @param _count_buffer ������ ���� @param _powner ������ ��������� ������ ��ü �������� ������ ��������� 1 �����ϸ� ������ �Ϸ�Ǹ� 1 ���ҽ�Ų��. @param _paddress ������ �ּ�(UDP����)  @return true ����  @return false ����
	virtual	bool				process_sendable( const buffer_view _buffer, object_ptr<Ireferenceable>&& _powner, std::size_t _count_message, const net::sockaddr& _address) PURE;
	//! @brief ������ �Ϸ�Ǿ��� �� ó���� �����ϴ� �Լ�.
	virtual	void				process_complete_sendable(uintptr_t _result, std::size_t _transferred, std::size_t _count_message) PURE;

#if defined(_SYS_EPOLL_H)
	virtual	uint32_t			process_recover_sendable( intptr_t _event, std::size_t _param) PURE;
#endif

	//! @brief �ʱ�ȭ �� �� ȣ��Ǵ� �Լ�.
	virtual	void				process_reset_sendable() noexcept PURE;
};


}