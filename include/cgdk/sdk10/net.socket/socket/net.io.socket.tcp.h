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
//    1) TCP용 socket class이다.
//    2) socket을 생성하고 소멸하는 기능을 가지고 있다.
//    3) socket의 send shared_buffer와 receive shared_buffer를 소켓별로 설정할 수 있지만
//       특별히 설정하지 않으면 기본으로 설정될 값을 아래의 전역함수로 변경할
//       수도 있다.
//       
//       static void	set_default_maximum_send_buffer_size(int _size);
//       static int		default_send_buffer_size() const;
//
//       static void	set_default_receive_buffer_size(int _size);
//       static int		default_receive_buffer_size() const;
//
//       소켓이 생성되면 일단 default값으로 설정되며 소켓별로 변경을 할 경우
//       소켓마다 설정해 주어야 한다.
//
//    4) 일반적으로 소켓의 send와 receive 버퍼를 크게 잡으면 높은 소숭신 부하에서도
//       더 좋은 성능을 낼 수 있다. 하지만 소켓당 용량을 그만큼 많이 차지하므로 
//       적절히 설정이 필요하다.
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