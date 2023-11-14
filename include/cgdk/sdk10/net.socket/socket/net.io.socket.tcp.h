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
// net::io::socket::Ntcp
//
//    1) TCP�� socket class�̴�.
//    2) socket�� �����ϰ� �Ҹ��ϴ� ����� ������ �ִ�.
//    3) socket�� send shared_buffer�� receive shared_buffer�� ���Ϻ��� ������ �� ������
//       Ư���� �������� ������ �⺻���� ������ ���� �Ʒ��� �����Լ��� ������
//       ���� �ִ�.
//       
//       static void	set_default_maximum_send_buffer_size(int _size);
//       static int		default_send_buffer_size() const;
//
//       static void	set_default_receive_buffer_size(int _size);
//       static int		default_receive_buffer_size() const;
//
//       ������ �����Ǹ� �ϴ� default������ �����Ǹ� ���Ϻ��� ������ �� ���
//       ���ϸ��� ������ �־�� �Ѵ�.
//
//    4) �Ϲ������� ������ send�� receive ���۸� ũ�� ������ ���� �Ҽ��� ���Ͽ�����
//       �� ���� ������ �� �� �ִ�. ������ ���ϴ� �뷮�� �׸�ŭ ���� �����ϹǷ� 
//       ������ ������ �ʿ��ϴ�.
//
//-----------------------------------------------------------------------------
#if defined(_WINSOCK2API_)
	#define	SOCKET_DEFAULT_FLAG	WSA_FLAG_OVERLAPPED
#else
	#define	SOCKET_DEFAULT_FLAG	0
#endif

class net::io::socket::Ntcp :
	public						net::io::socket::Nbase,
	virtual public				net::io::Iconnectable,
	virtual public				net::io::Isendable,
	virtual public				net::io::Ireceivable_stream
{
protected:
			Ntcp() noexcept;
			Ntcp(uint32_t _flag) noexcept;
	virtual	~Ntcp() noexcept;

public:
	static	void				set_default_maximum_send_buffer_size(std::size_t _size) noexcept;
	[[nodiscard]] static std::size_t default_maximum_send_buffer_size() noexcept { return m_s_default_maximum_send_buffer_size;}

	static	void				set_default_maximum_receive_buffer_size(std::size_t _size) noexcept;
	[[nodiscard]] static std::size_t default_maximum_receive_buffer_size() noexcept { return m_default_maximum_receive_buffer_size;}

protected:
	virtual	void				process_create_socket(ADDRESS_FAMILY _address_family = AF_INET) override;
	virtual void				process_dispose_socket() noexcept override;
	virtual	bool				process_close_socket(uint64_t _disconnect_reason = DISCONNECT_REASON_NONE) noexcept override;

protected:
			uint32_t			m_flag;

	static	std::size_t			m_s_default_maximum_send_buffer_size;
	static	std::size_t			m_default_maximum_receive_buffer_size;

#if defined(_SYS_EPOLL_H)
protected:
	virtual	intptr_t			process_execute_epoll(intptr_t _event, std::size_t _param) override;

public:
#endif
};


}