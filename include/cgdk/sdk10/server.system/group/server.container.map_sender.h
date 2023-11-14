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
 List형 Object Class 객체
 Group과 다른 점은 독점적이지 않다는 것이다.
 여러개의 Object에도 붙어서 동작할 수 있다.

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
	//! @brief 특정 멤버를 제외한 전체 멤버에게 메모리 버퍼의 전송한다. @param _member_except 제외할 멤버 @param _buffer 전송할 메모리 버퍼 @return true 성공 @return false 실패
			bool				send_except(object_t* _member_except, const shared_buffer& _buffer, uint64_t _option = 0);
	//! @brief 조건을 만족한 멤버에게만 메모리 버퍼의 전송한다. @param _buffer 전송할 메모리 버퍼 @param _pred 조건 함수 @return true 성공 @return false 실패
			bool				send_conditional(const shared_buffer& _buffer, const std::function<bool (const object_t*)>& _pred, uint64_t _option = 0);

// implementations)
protected:
	//! @brief 전체 멤버에게 메모리 버퍼의 내용을 전송한다. @param _buffer 전송할 메모리 버퍼 @return true 성공 @return false 실패
	virtual	bool				process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option);
};

	template <class _TOBJECT, class _TKEY, class _TOBJECT_DATA, class _TOBJECTBASE>
bool container::map_sender<_TOBJECT, _TKEY, _TOBJECT_DATA, _TOBJECTBASE>::process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option)
{
	// check) _buffer가 empty면 리턴
	RETURN_IF(_buffer.empty(), false)

	// 1) 모두에게 전송한다.
	scoped_lock(this->m_lockable_observable)
	{
		for(auto& iter: this->m_container_object)
		{
			iter.second.pobject->send({ _buffer, _count_message }, _option);
		}
	}

	// return) 성공...
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
			// check) _member_except일 경우 다음...
			if(*iter == _member_except)
			{
				++iter;
				break;
			}

			// - 전송한다.
			iter.second.pobject->send(_buffer, _option);
		}

		for(; iter!=iter_end; ++iter)
		{
			// - 전송한다.
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

			// - 전송한다.
			iter.second.pobject->send(_buffer, _option);
		}
	}

	// return)
	return true;
}


}