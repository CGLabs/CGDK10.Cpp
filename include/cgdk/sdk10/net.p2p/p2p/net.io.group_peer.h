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
// net::io::group_peer::Narray<T>
//
//-----------------------------------------------------------------------------
template <class TPEER>
class net::io::group_peer::Narray :
// inherited classes) 
	virtual	public				Ireferenceable
{
// constructor/destructor)
protected:
			Narray(int _max = 16) { set_max_peer(_max);}
	virtual	~Narray() noexcept {}

// publics)
public:
			object_ptr<TPEER>	get_peer( int _peer_index) const;
			object_ptr<TPEER>&	peer( int _peer_index);

	virtual	bool				attach_peer( int _peer_index, TPEER* _pPeer);
	virtual	object_ptr<TPEER>	detach_peer( int _peer_index) noexcept;
			bool				detach_peer( TPEER* _pPeer) noexcept;

			bool				set_max_peer( int p_nMaxPeer);
			int					max_peer() const { return static_cast<int>(m_vector_peer.size());}

// framework)
protected:
	virtual	void				on_peer_attach( int _peer_index, TPEER* _pPeer);
	virtual	void				on_peer_detach( int _peer_index, TPEER* _pPeer);

// implementation)
protected:
			vector<object_ptr<TPEER>> m_vector_peer;
			lockable<>			m_lockable_vector_peer;
};

template <class TPEER>
object_ptr<TPEER>& net::io::group_peer::Narray<TPEER>::peer( int _peer_index)
{
	// check) iPeer�� Min�� Max ���̰� �ƴϸ� �ȉ´�!
	CGASSERT_ERROR(_peer_index>=0 && _peer_index<static_cast<int>(m_vector_peer.size()));

	//  1) peer ��� Return�ϱ�.
	return		m_vector_peer.at(_peer_index);
}

template <class TPEER>
object_ptr<TPEER> net::io::group_peer::Narray<TPEER>::get_peer( int _peer_index) const
{
	// check) iPeer�� Min�� Max ���̰� �ƴ� ���� nullptr�� �����Ѵ�.
	RETURN_IF(_peer_index<0 || _peer_index>=static_cast<int>(m_vector_peer.size()), object_ptr<TPEER>());

	//  1) peer ��� Return�ϱ�.
	return		m_vector_peer.at(_peer_index);
}

template <class TPEER>
bool net::io::group_peer::Narray<TPEER>::attach_peer( int _peer_index, TPEER* _pPeer)
{
	// check) _pPeer�� nullptr�̸� �ȵȴ�.
	CGASSERT(_pPeer != nullptr, false);

	scoped_lock(m_lockable_vector_peer)
	{
		// check) iPeer�� Min�� Max ���̰� �ƴ� ���� false�� �����Ѵ�.
		RETURN_IF(_peer_index<0 || _peer_index>=static_cast<int>(m_vector_peer.size()), false);

		// check) 
		RETURN_IF(m_vector_peer.at(_peer_index)!=nullptr, false);

		// 1) peer�� ����Ʈ�� �߰��Ѵ�.
		m_vector_peer.at(_peer_index)	 = _pPeer;

		// 2) peer�� ��ȣ�� �����.
		_pPeer->set_peer_index(_peer_index);

		// 3) on_peer_attach�Լ��� ȣ���Ѵ�.
		on_peer_attach(_peer_index, _pPeer);
	}


	// return) ����!!!
	return true;
}

template <class TPEER>
object_ptr<TPEER> net::io::group_peer::Narray<TPEER>::detach_peer( int _peer_index) noexcept
{
	// declare)
	object_ptr<TPEER>	pPeer;

	scoped_lock(m_lockable_vector_peer)
	{
		// check) iPeer�� Min�� Max ���̿������� �Ѵ�.
		RETURN_IF(_peer_index<0 && _peer_index>=static_cast<int>(m_vector_peer.size()), object_ptr<TPEER>());

		// 1) peer�� ��´�.
		pPeer	 = m_vector_peer.at(_peer_index);

		// check) 
		RETURN_IF(pPeer.exist(), pPeer);

		// 2) on_peer_detach�Լ��� ȣ���Ѵ�.
		on_peer_detach(_peer_index, pPeer);

		// 1) peer�� ����Ʈ�� �߰��Ѵ�.
		m_vector_peer.at(_peer_index).reset();

		// 2) peer�� ��ȣ�� �����.
		pPeer->set_peer_index(-1);
	}

	// return) ����!!!
	return	pPeer;
}

template <class TPEER>
bool net::io::group_peer::Narray<TPEER>::detach_peer( TPEER* _pPeer) noexcept
{
	detach_peer(_pPeer->get_peer_index());

	// return)
	return true;
}


template <class TPEER>
bool net::io::group_peer::Narray<TPEER>::set_max_peer( int p_nMaxPeer)
{
	scoped_lock(m_lockable_vector_peer)
	{
		// 1) vector�� Size�� �����Ѵ�.
		m_vector_peer.resize(p_nMaxPeer);
	}

	return true;
}

template <class TPEER>
void net::io::group_peer::Narray<TPEER>::on_peer_attach( int /*_peer_index*/, TPEER* /*_pPeer*/)
{
}

template <class TPEER>
void net::io::group_peer::Narray<TPEER>::on_peer_detach( int /*_peer_index*/, TPEER* /*_pPeer*/)
{
}


}