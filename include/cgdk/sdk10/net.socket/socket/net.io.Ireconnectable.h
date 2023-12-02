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
// net::io::Ireconnectable
//
//-----------------------------------------------------------------------------

class net::io::Ireconnectable :
	virtual public				net::io::Iconnect_requestable,
	virtual public				Ireferenceable
{
public:
			Ireconnectable();
	virtual	~Ireconnectable() noexcept {}

public:
			bool				add_peer_address( const net::sockaddr& _address_peer);
			bool				remove_peer_address( const net::sockaddr& _address_peer) noexcept;
			void				remove_all_peer_address() noexcept;
			net::sockaddr		move_next_peer_address() noexcept;
	   
			void				enable_reconnect( bool _flag_enable = true) noexcept { this->m_enable_reconnect = _flag_enable; }
			void				disable_reconnect() noexcept { this->m_enable_reconnect = false;}
	[[nodiscard]] bool			reconnection_enable() const noexcept { return this->m_enable_reconnect; }
																							  
			void				set_reconnect_interval(chrono::tick::duration _tick) noexcept { this->m_tick_reconnection_interval = _tick; }
	[[nodiscard]] auto			get_reconnect_interval() const noexcept { return this->m_tick_reconnection_interval;}

protected:
			lockable<circular_list<net::sockaddr>> m_list_peer_adddress;
			circular_list<net::sockaddr>::const_iterator m_iter_now_peer_address;

			bool				m_enable_reconnect;
			chrono::tick::duration	m_tick_reconnection_interval;

			chrono::tick::time_point m_tick_disconnected;

			bool				m_flag_reconnecting;
			lockable<>			m_lockable_reconnector;

			friend class net::io::connective::connector::Ntcp;
};


}