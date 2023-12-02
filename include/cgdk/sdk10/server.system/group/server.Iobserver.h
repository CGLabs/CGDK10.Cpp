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

 @class		Iobserver
 @brief		그룹의 멤버가 되기 위한 인터페이스 클래스이다.
 @todo		
  @ref		
 @details	\n
       
*///-----------------------------------------------------------------------------
template <class _observer_base_t, class _TOBSERVER_CHANNEL= observer_channel_id, class _TOBSERVABLEBASE=Iobservable<_observer_base_t>>
class Iobserver : virtual public Ireferenceable
{
// declare) Member의 Type
public:
	using observer_base_t = _observer_base_t;
	using observer_channel_t = _TOBSERVER_CHANNEL;
	using observable_base_t = _TOBSERVABLEBASE;

// constructor/destructor)
public:
			Iobserver() noexcept : m_pobserver_data(nullptr) {}
	virtual	~Iobserver() noexcept { CGASSERT_ERROR(m_vector_observable.empty());}

// public)
public:
	//! @brief 현재 그룹에서 나온다.
	virtual	bool				unsubscribe(observer_channel_t _ocid = 0) noexcept;
	virtual	void				unsubscribe_all() noexcept;

	[[nodiscard]] auto			get_observable(observer_channel_t _ocid = 0) const noexcept { return _get_observable(_ocid);}
	[[nodiscard]] bool			is_observable(observable_base_t* _pobservable, observer_channel_t _ocid = 0) const noexcept { return _is_observable(_pobservable, _ocid); }

// implementation)
public:
	// definitions)
			struct OBSERVER_REGISTER_INFO
			{
			public:
				object_ptr<_TOBSERVABLEBASE> pobservable;
				observer_channel_t	ocid;

			public:
				OBSERVER_REGISTER_INFO() : pobservable(), ocid(0) {}
				OBSERVER_REGISTER_INFO(Iobservable<observer_base_t>* _pobservable, observer_channel_t _ocid) : pobservable(_pobservable), ocid(_ocid)	{}
			};

	// 1) Group(Memberable가 속해있는 Group이다. Group에 속해있지 않으면 nullptr이 된다.)
			lockable<std::vector<OBSERVER_REGISTER_INFO>> m_vector_observable;

private:
			void*				m_pobserver_data;

	// Friend)
	friend	observable_base_t;

public:
			void				_add_observable(observable_base_t* _pobservable, observer_channel_t _ocid);
			void				_erase_observable(observer_channel_t _ocid) noexcept;
			void				_popback_observable() noexcept;
			void				_unsubscribe(observer_channel_t _ocid) noexcept;
	[[nodiscard]] bool			_is_observable(observable_base_t* _pobservable, observer_channel_t _ocid) const noexcept;
	[[nodiscard]] object_ptr<observable_base_t> _get_observable(observer_channel_t _ocid) const noexcept;
};

template <class _observer_base_t, class _TOBSERVER_CHANNEL, class _TOBSERVABLEBASE>
void Iobserver<_observer_base_t, _TOBSERVER_CHANNEL, _TOBSERVABLEBASE>::_add_observable(_TOBSERVABLEBASE* _pobservable, observer_channel_t _ocid)
{
	// check)
	CGASSERT_ERROR(_pobservable != nullptr)

	scoped_lock(m_vector_observable)
	{
		m_vector_observable.emplace_back(OBSERVER_REGISTER_INFO(_pobservable, _ocid));
	}
}

template <class _observer_base_t, class _TOBSERVER_CHANNEL, class _TOBSERVABLEBASE>
void Iobserver<_observer_base_t, _TOBSERVER_CHANNEL, _TOBSERVABLEBASE>::_erase_observable(observer_channel_t _ocid) noexcept
{
	scoped_lock(m_vector_observable)
	{
		for (auto iter = m_vector_observable.begin(), iter_end = m_vector_observable.end(); iter != iter_end; ++iter)
		{
			if (iter->ocid == _ocid)
			{
				m_vector_observable.erase(iter);
				break;
			}
		}
	}
}

template <class _observer_base_t, class _TOBSERVER_CHANNEL, class _TOBSERVABLEBASE>
bool Iobserver<_observer_base_t, _TOBSERVER_CHANNEL, _TOBSERVABLEBASE>::_is_observable(observable_base_t* _pobservable, observer_channel_t _ocid) const noexcept
{
	scoped_lock(m_vector_observable)
	{
		for (auto iter = m_vector_observable.begin(), iter_end = m_vector_observable.end(); iter != iter_end; ++iter)
		{
			if (iter->ocid == _ocid)
			{
				return (_pobservable == iter->pobservable);
			}
		}
	}

	// return)
	return false;
}

template <class _observer_base_t, class _TOBSERVER_CHANNEL, class _TOBSERVABLEBASE>
object_ptr<_TOBSERVABLEBASE> Iobserver<_observer_base_t, _TOBSERVER_CHANNEL, _TOBSERVABLEBASE>::_get_observable(observer_channel_t _ocid) const noexcept
{
	// declare)
	object_ptr<_TOBSERVABLEBASE> pobservable;

	scoped_lock(m_vector_observable)
	{
		for (auto iter = m_vector_observable.begin(), iter_end = m_vector_observable.end(); iter != iter_end; ++iter)
		{
			if (iter->ocid == _ocid)
			{
				pobservable = iter->pobservable;
				break;
			}
		}
	}

	// return)
	return pobservable;
}

template <class _observer_base_t, class _TOBSERVER_CHANNEL, class _TOBSERVABLEBASE>
void Iobserver<_observer_base_t, _TOBSERVER_CHANNEL, _TOBSERVABLEBASE>::_popback_observable() noexcept
{
	scoped_lock(m_vector_observable)
	{
		m_vector_observable.pop_back();
	}
}

template <class _observer_base_t, class _TOBSERVER_CHANNEL, class _TOBSERVABLEBASE>
void Iobserver<_observer_base_t, _TOBSERVER_CHANNEL, _TOBSERVABLEBASE>::_unsubscribe(observer_channel_t _ocid) noexcept
{
	// declare)
	object_ptr<_TOBSERVABLEBASE> pobservable;

	scoped_lock_named(m_vector_observable, PPP1)
	{
		for (auto iter = m_vector_observable.begin(), iter_end = m_vector_observable.end(); iter != iter_end; ++iter)
		{
			if (iter->ocid == _ocid)
			{
				scoped_lock_leave(PPP1)

				iter->pobservable->unsubscribe(dynamic_cast<_observer_base_t*>(this), _ocid);
				break;
			}
		}
	}
}

template <class _observer_base_t, class _TOBSERVER_CHANNEL, class _TOBSERVABLEBASE>
bool Iobserver<_observer_base_t, _TOBSERVER_CHANNEL, _TOBSERVABLEBASE>::unsubscribe(observer_channel_t _ocid) noexcept
{
	// 1) 먼저 해당 Observable을 찾는다.
	auto pobservable = _get_observable(_ocid);

	// check) 없으면 그냥 false를 리튼한다.
	RETURN_IF(pobservable.empty(), false);

	// 2) 존재하면 unregister를 요청한다.
	pobservable->unsubscribe(dynamic_cast<_observer_base_t*>(this), _ocid);

	// return)
	return true;
}

template <class _observer_base_t, class _TOBSERVER_CHANNEL, class _TOBSERVABLEBASE>
void Iobserver<_observer_base_t, _TOBSERVER_CHANNEL, _TOBSERVABLEBASE>::unsubscribe_all() noexcept
{
	// declare) 
	std::vector<OBSERVER_REGISTER_INFO> vector_observable;

	// 1) 복사
	scoped_lock(m_vector_observable)
	{
		vector_observable = m_vector_observable;
	}

	// 2) 모두 제거
	for(auto& iter: vector_observable)
	{
		iter.pobservable->unsubscribe(dynamic_cast<_observer_base_t*>(this), iter.ocid);
	}
}


}