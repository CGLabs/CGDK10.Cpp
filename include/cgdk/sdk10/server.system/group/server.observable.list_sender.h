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

 @class		list
 @brief		
 @todo		
 @ref		
 @details	\n
 List�� Observer Class ��ü
 Group�� �ٸ� ���� ���������� �ʴٴ� ���̴�.
 �������� Observer���� �پ ������ �� �ִ�.

*///-----------------------------------------------------------------------------
template <class _TOBSERVER, class _TOBSERVER_DATA=int64_t, class _observer_base_t=_TOBSERVER>
class observable::list_sender :
// inherited classes)
	public						observable::list<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>,
	virtual public				net::io::Isender
{
// definitnion)
public:
	using observable_bast_t = observable::list<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>;
	using observer_t = _TOBSERVER;

// constructor/destructor)
public:
			list_sender(size_t _max_observer = SIZE_MAX) noexcept : observable::list<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>(_max_observer)	{}
	virtual	~list_sender() noexcept {}

// publics) 
public:
	//! @brief Ư�� ����� ������ ��ü ������� �޸� ������ �����Ѵ�. @param _member_except ������ ��� @param _buffer ������ �޸� ���� @return true ���� @return false ����
			bool				send_except(observer_t* _member_except, const shared_buffer& _buffer, uint64_t _option = 0);
	//! @brief ������ ������ ������Ը� �޸� ������ �����Ѵ�. @param _buffer ������ �޸� ���� @param _pred ���� �Լ� @return true ���� @return false ����
			bool				send_conditional(const shared_buffer& _buffer, const std::function<bool (const observer_t*)>& _pred, uint64_t _option = 0);

// implementations)
protected:
	//! @brief ��ü ������� �޸� ������ ������ �����Ѵ�. @param _buffer ������ �޸� ���� @return true ���� @return false ����
	virtual	bool				process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option);
};

template <class _TOBSERVER, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::list_sender<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>::process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option)
{
	// check) _buffer�� empty�� ����
	RETURN_IF(_buffer.empty(), false)

	// 1) ��ο��� �����Ѵ�.
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter: this->m_container_observer)
		{
			iter.pobserver->send({ _buffer, _count_message }, _option);
		}
	}

	// return) ����...
	return true;
}

template <class _TOBSERVER, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::list_sender<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>::send_except(observer_t* _member_except, const shared_buffer& _buffer, uint64_t _option)
{
	scoped_lock(this->m_lockable_observable)
	{
		auto	iter	 = this->m_container_observer.begin();
		auto	iter_end	 = this->m_container_observer.end();

		for(; iter!=iter_end; ++iter)
		{
			// check) _member_except�� ��� ����...
			if(iter.pobserver ==_member_except)
			{
				++iter;
				break;
			}

			// - �����Ѵ�.
			iter.pobserver->send(_buffer, _option);
		}

		for(; iter!=iter_end; ++iter)
		{
			// - �����Ѵ�.
			iter.pobserver->send(_buffer, _option);
		}
	}

	// return) ����...
	return true;
}

template <class _TOBSERVER, class _TOBSERVER_DATA, class _observer_base_t>
bool observable::list_sender<_TOBSERVER, _TOBSERVER_DATA, _observer_base_t>::send_conditional(const shared_buffer& _buffer, const std::function<bool (const observer_t*)>& _pred, uint64_t _option)
{
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter: this->m_container_observer)
		{
			// check) _pred�� false�� �������� �ʴ´�.
			CONTINUE_IF(_pred(iter.pobserver) == false);

			// - �����Ѵ�.
			iter.pobserver->send(_buffer, _option);
		}
	}

	// return) ����...
	return true;
}


}