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
// net::io::IPeer
//
// 1. net::io::IPeer은~
//     peer의 Interface class이다. 
//     peer Index는 peer의 번호를 의미하며 group_peer에 붙을 때 주어진다.
//
//-----------------------------------------------------------------------------
class net::io::Ipeer :
// inherited classes)
	virtual public				Ireferenceable
{
// publics)
public:
			int					get_peer_index() const { return m_index_peer;}
			void				set_peer_index( int _peer_index) { m_index_peer = _peer_index; }

// implementation)
private:
			int					m_index_peer = 0;
};


}