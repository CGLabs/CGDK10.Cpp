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
// net::io::sender::Ngroup_set
//
// 1. net::io::sender::Ngroup_set은~
//    1) 여러 sender를 등록해 한꺼번에 전송하도록 하는 sender 객체다.
//
//-----------------------------------------------------------------------------
template<class TSENDER=net::io::Isender>
class net::io::sender::Igroup_set :
	virtual public				net::io::Isender
{
public:
			void				join(TSENDER* _psender);
			void				join(object_ptr<TSENDER>&& _psender);
			void				leave(TSENDER* _psender) noexcept;
			void				leave_all() noexcept;
			bool				exist(TSENDER* _psender) noexcept;
			lockable<>& get_lockable() noexcept { return this->m_cs_map_sender; }
protected:
			lockable<>			m_cs_set_sender;
			std::set<object_ptr<TSENDER>> m_set_sender;
};

template<class TSENDER>
void net::io::sender::Igroup_set<TSENDER>::join(TSENDER* _psender)
{
	// check) _psender가 nullptr이면 안됀다.
	THROW_IF(_psender == nullptr, throwable::failure(eRESULT::INVALID_ARGUMENT));

	scoped_lock(this->m_cs_set_sender)
	{
		// 1) 먼저 찾는다
		auto iter_find = this->m_set_sender.find(_psender);

		// check) 이미 존재하고 있으면 그냥 리턴한다.
		RETURN_IF(iter_find != this->m_set_sender.end());

		// 2) 추가한다.
		this->m_set_sender.emplace(_psender);
	}
}

template<class TSENDER>
void net::io::sender::Igroup_set<TSENDER>::join(object_ptr<TSENDER>&& _psender)
{
	// check) _psender가 nullptr이면 안됀다.
	THROW_IF(_psender == nullptr, throwable::failure(eRESULT::INVALID_ARGUMENT));

	scoped_lock(this->m_cs_set_sender)
	{
		// 1) 먼저 찾는다
		auto iter_find = this->m_set_sender.find(_psender);

		// check) 이미 존재하고 있으면 그냥 리턴한다.
		RETURN_IF(iter_find != this->m_set_sender.end());

		// 2) 추가한다.
		this->m_set_sender.emplace(std::move(_psender));
	}
}

template<class TSENDER>
void net::io::sender::Igroup_set<TSENDER>::leave(TSENDER* _psender) noexcept
{
	scoped_lock(this->m_cs_set_sender)
	{
		// 1) 먼저 찾는다
		auto iter_find = this->m_set_sender.find(_psender);

		// check) 존재하지 않으면 그냥 리턴한다.
		RETURN_IF(iter_find == this->m_set_sender.end());
		
		// 2) 제거한다.
		this->m_set_sender.erase(iter_find);
	}
}

template<class TSENDER>
void net::io::sender::Igroup_set<TSENDER>::leave_all() noexcept
{
	scoped_lock(this->m_cs_set_sender)
	{
		this->m_set_sender.clear();
	}
}

template<class TSENDER>
bool net::io::sender::Igroup_set<TSENDER>::exist(TSENDER* _psender) noexcept
{
	scoped_lock(this->m_cs_set_sender)
	{
		return this->m_set_sender.find(_psender) != this->m_set_sender.end();
	}
}

template<class TSENDER = net::io::Isender>
class net::io::sender::group_set : public net::io::sender::Igroup_set<TSENDER>
{
	virtual bool process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option) override
	{
		// check) _buffer->size_이 0이 아닌가?
		RETURN_IF(_buffer.size() == 0, false)

		// check) _buffer->data_가 nullptr이 아닌가?
		RETURN_IF(_buffer.data() == nullptr, false)

		// check) 버퍼가 Overflow되었는가?
		CGASSERT_ERROR(_buffer._is_buffer_overflow() == false);

		// 1) 전송한다.
		scoped_lock(this->m_cs_set_sender)
		{
			for (auto iter = this->m_set_sender.begin(), iterEnd = this->m_set_sender.end(); iter != iterEnd; ++iter)
			{
				(*iter)->send(shared_buffer(_buffer, _count_message), _option);
			}
		}

		// return)
		return true;
	}
};


}