//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                         Socket template Classes                           *
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

 @class		map_sender
 @brief		
 @todo		
 @ref		
 @details	\n
 List형 Observer Class 객체
 Group과 다른 점은 독점적이지 않다는 것이다.
 여러개의 Observer에도 붙어서 동작할 수 있다.

*///-----------------------------------------------------------------------------
	template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA = int64_t, class _observer_base_t=_TOBSERVER>
	class observable::map_sender :
// inherited cClasses)
	public						observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>,
	virtual public				net::io::Isender
{
// definitnion)
public:
	using observable_bast_t	 = observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>;
	using observer_t = _TOBSERVER;

// constructor/destructor)
public:
			map_sender(size_t _max_observer = SIZE_MAX) noexcept : observable::map<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>(_max_observer)	{}
	virtual	~map_sender() noexcept {}

// publics) 
public:
			bool				send_except(observer_t* _member_except, const shared_buffer& _buffer, uint64_t _option = 0);
			bool				send_conditional(const shared_buffer& _buffer, const std::function<bool (const observer_t*)>& _pred, uint64_t _option = 0);

// implementations)
protected:
	virtual	bool				process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option);
};

	template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::map_sender<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option)
{
	// check)
	RETURN_IF(_buffer.empty(), false)

	// 1) send to all member
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter: this->m_container_observer)
		{
			// - send to member
			iter.second.pobserver->send({ _buffer, _count_message }, _option);
		}
	}

	// return)
	return true;
}

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::map_sender<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::send_except(observer_t* _member_except, const shared_buffer& _buffer, uint64_t _option)
{
	scoped_lock(this->m_lockable_observable)
	{
		auto iter = this->m_container_observer.begin();
		auto iter_end = this->m_container_observer.end();

		for(; iter!=iter_end; ++iter)
		{
			// check) 
			if(*iter == _member_except)
			{
				++iter;
				break;
			}

			// - send to member
			iter.second.pobserver->send(shared_buffer(_buffer), _option);
		}

		for(; iter!=iter_end; ++iter)
		{
			// - send to member
			iter.second.pobserver->send(shared_buffer(_buffer), _option);
		}
	}

	// return)
	return true;
}

template <class _TOBSERVER, class _TKEY, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::map_sender<_TOBSERVER, _TKEY, _TOBSERVER_DATA, _observer_base_t>::send_conditional(const shared_buffer& _buffer, const std::function<bool (const observer_t*)>& _pred, uint64_t _option)
{
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter: this->m_container_observer)
		{
			// check) 
			CONTINUE_IF(_pred(iter) == false);

			// - send to member
			iter.second.pobserver->send(shared_buffer(_buffer), _option);
		}
	}

	// return)
	return true;
}


}