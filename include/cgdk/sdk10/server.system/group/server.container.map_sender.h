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
 List�� Object Class ��ü
 Group�� �ٸ� ���� ���������� �ʴٴ� ���̴�.
 �������� Object���� �پ ������ �� �ִ�.

*///-----------------------------------------------------------------------------
	template <class _TOBJECT, class _TKEY, class _TOBJECT_DATA = int, class _TOBJECTBASE = _TOBJECT>
	class container::map_sender :
// inherited cClasses)
	virtual public				container::map<_TOBJECT, _TKEY, _TOBJECT_DATA, _TOBJECTBASE>,
	virtual public				net::io::Isender
{
// definitnion)
public:
	using observable_bast_t = container::map<_TOBJECT, _TKEY, _TOBJECT_DATA, _TOBJECTBASE>;
	using object_t = _TOBJECT;

// publics) 
public:
	//! @brief Ư�� ����� ������ ��ü ������� �޸� ������ �����Ѵ�. @param _member_except ������ ��� @param _buffer ������ �޸� ���� @return true ���� @return false ����
			bool				send_except(object_t* _member_except, const shared_buffer& _buffer, uint64_t _option = 0);
	//! @brief ������ ������ ������Ը� �޸� ������ �����Ѵ�. @param _buffer ������ �޸� ���� @param _pred ���� �Լ� @return true ���� @return false ����
			bool				send_conditional(const shared_buffer& _buffer, const std::function<bool (const object_t*)>& _pred, uint64_t _option = 0);

// implementations)
protected:
	//! @brief ��ü ������� �޸� ������ ������ �����Ѵ�. @param _buffer ������ �޸� ���� @return true ���� @return false ����
	virtual	bool				process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option);
};

	template <class _TOBJECT, class _TKEY, class _TOBJECT_DATA, class _TOBJECTBASE>
bool container::map_sender<_TOBJECT, _TKEY, _TOBJECT_DATA, _TOBJECTBASE>::process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option)
{
	// check) _buffer�� empty�� ����
	RETURN_IF(_buffer.empty(), false)

	// 1) ��ο��� �����Ѵ�.
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter: this->m_container_object)
		{
			iter.second.pobject->send({ _buffer, _count_message }, _option);
		}
	}

	// return) ����...
	return true;
}

template <class _TOBJECT, class _TKEY, class _TOBJECT_DATA, class _TOBJECTBASE>
bool container::map_sender<_TOBJECT, _TKEY, _TOBJECT_DATA, _TOBJECTBASE>::send_except(object_t* _member_except, const shared_buffer& _buffer, uint64_t _option)
{
	scoped_lock(this->m_lockable_observable)
	{
		auto iter = this->m_container_object.begin();
		auto iter_end = this->m_container_object.end();

		for(; iter != iter_end; ++iter)
		{
			// check) _member_except�� ��� ����...
			if(*iter == _member_except)
			{
				++iter;
				break;
			}

			// - �����Ѵ�.
			iter.second.pobject->send(_buffer, _option);
		}

		for(; iter!=iter_end; ++iter)
		{
			// - �����Ѵ�.
			iter.second.pobject->send(_buffer);
		}
	}

	// return)
	return true;
}

template <class _TOBJECT, class _TKEY, class _TOBJECT_DATA, class _TOBJECTBASE>
bool container::map_sender<_TOBJECT, _TKEY, _TOBJECT_DATA, _TOBJECTBASE>::send_conditional(const shared_buffer& _buffer, const std::function<bool (const object_t*)>& _pred, uint64_t _option)
{
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter: this->m_container_object)
		{
			// check)
			CONTINUE_IF(_pred(iter) == false);

			// - �����Ѵ�.
			iter.second.pobject->send(_buffer, _option);
		}
	}

	// return)
	return true;
}


}