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
 List형 Object Class 객체
 Group과 다른 점은 독점적이지 않다는 것이다.
 여러개의 Object에도 붙어서 동작할 수 있다.

*///-----------------------------------------------------------------------------
template <class _TOBJECT, class _TOBJECT_DATA = int, class _TOBJECTBASE = _TOBJECT>
class container::list_sender :
// inherited cClasses)
	virtual public				container::list<_TOBJECT, _TOBJECT_DATA, _TOBJECTBASE>,
	virtual public				net::io::Isender
{
// definitnion)
public:
	using observable_bast_t = container::list<_TOBJECT, _TOBJECT_DATA, _TOBJECTBASE>;
	using object_t = _TOBJECT;

// publics) 
public:
	//! @brief 특정 멤버(_member_except)를 제외한 전체 멤버에게 메모리 버퍼의 전송한다.
			bool				send_except(object_t* _member_except, const shared_buffer& _buffer, uint64_t _option = 0);
	//! @brief 조건을 만족한 멤버에게만 메모리 버퍼의 전송한다.
			bool				send_conditional(const shared_buffer& _buffer, const std::function<bool (const object_t*)>& _pred, uint64_t _option = 0);

// implementations)
protected:
	//! @brief 전체 멤버에게 메모리 버퍼의 내용을 전송한다.
	virtual	bool				process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option);
};

template <class _TOBJECT, class _TOBJECT_DATA, class _TOBJECTBASE>
bool container::list_sender<_TOBJECT, _TOBJECT_DATA, _TOBJECTBASE>::process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option)
{
	// check)
	RETURN_IF(_buffer.empty(), false)
	
	// 1) send to all member
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter: this->m_container_object)
		{
			iter.pobject->send({ _buffer, _count_message }, _option);
		}
	}

	// return)
	return true;
}

template <class _TOBJECT, class _TOBJECT_DATA, class _TOBJECTBASE>
bool container::list_sender<_TOBJECT, _TOBJECT_DATA, _TOBJECTBASE>::send_except(object_t* _member_except, const shared_buffer& _buffer, uint64_t _option)
{
	scoped_lock(this->m_lockable_observable)
	{
		auto iter = this->m_container_object.begin();
		auto iter_end = this->m_container_object.end();

		for(; iter!=iter_end; ++iter)
		{
			// check) _member_except일 경우 다음...
			if(iter.pobject ==_member_except)
			{
				++iter;
				break;
			}

			// - 전송한다.
			iter.pobject->send(_buffer, _option);
		}

		for(; iter!=iter_end; ++iter)
		{
			// - 전송한다.
			iter.pobject->send(_buffer, _option);
		}
	}

	// return) 성공...
	return true;
}

template <class _TOBJECT, class _TOBJECT_DATA, class _TOBJECTBASE>
bool container::list_sender<_TOBJECT, _TOBJECT_DATA, _TOBJECTBASE>::send_conditional(const shared_buffer& _buffer, const std::function<bool (const object_t*)>& _pred, uint64_t _option)
{
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter: this->m_container_object)
		{
			// check) _pred가 false면 전송하지 않는다.
			CONTINUE_IF(_pred(iter.pobject) == false);

			// - 전송한다.
			iter.pobject->send(_buffer, _option);
		}
	}

	// return) 성공...
	return true;
}


}