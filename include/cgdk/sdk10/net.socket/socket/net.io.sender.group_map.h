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
// 1. net::io::sender::Ngroup_set��~
//    1) ���� sender�� ����� �Ѳ����� �����ϵ��� �ϴ� sender ��ü��.
//
//-----------------------------------------------------------------------------
template<class TKEY, class TSENDER=net::io::Isender>
class net::io::sender::Igroup_map :
	virtual public				net::io::Isender
{
public:
			void				join(const TKEY& _key, TSENDER* _psender);
			void				join(const TKEY& _key, object_ptr<TSENDER>&& _psender);
			void				leave(const TKEY& _key) noexcept;
			void				leave_all() noexcept;
			object_ptr<TSENDER>	find(const TKEY& _key) const noexcept;
			lockable<>&			get_lockable() noexcept { return this->m_cs_map_sender ;}
protected:
			lockable<>			m_cs_map_sender;
			std::map<TKEY, object_ptr<TSENDER>> m_map_sender;
};

template<class TKEY, class TSENDER>
void net::io::sender::Igroup_map<TKEY, TSENDER>::join(const TKEY& _key, TSENDER* _psender)
{
	// check) _psender�� nullptr�̸� �ȉ´�.
	THROW_IF(_psender == nullptr, throwable::failure(eRESULT::INVALID_ARGUMENT));

	scoped_lock(this->m_cs_map_sender)
	{
		// 1) ���� ã�´�
		auto iter_find = this->m_map_sender.find(_key);

		// check) �̹� �����ϰ� ������ �׳� �����Ѵ�.
		RETURN_IF(iter_find != this->m_map_sender.end());

		// 2) �߰��Ѵ�.
		this->m_map_sender.emplace(_key, _psender);
	}
}

template<class TKEY, class TSENDER>
void net::io::sender::Igroup_map<TKEY, TSENDER>::join(const TKEY& _key, object_ptr<TSENDER>&& _psender)
{
	// check) _psender�� nullptr�̸� �ȉ´�.
	THROW_IF(_psender == nullptr, throwable::failure(eRESULT::INVALID_ARGUMENT));

	scoped_lock(this->m_cs_map_sender)
	{
		// 1) ���� ã�´�
		auto iter_find = this->m_map_sender.find(_key);

		// check) �̹� �����ϰ� ������ �׳� �����Ѵ�.
		RETURN_IF(iter_find != this->m_map_sender.end());

		// 2) �߰��Ѵ�.
		this->m_map_sender.emplace(_key, std::move(_psender));
	}
}

template<class TKEY, class TSENDER>
void net::io::sender::Igroup_map<TKEY, TSENDER>::leave(const TKEY& _key) noexcept
{
	scoped_lock(this->m_cs_map_sender)
	{
		// 1) ���� ã�´�
		auto iter_find = this->m_map_sender.find(_key);

		// check) �������� ������ �׳� �����Ѵ�.
		RETURN_IF(iter_find == this->m_map_sender.end());
		
		// 2) �����Ѵ�.
		this->m_map_sender.erase(iter_find);
	}
}

template<class TKEY, class TSENDER>
void net::io::sender::Igroup_map<TKEY, TSENDER>::leave_all() noexcept
{
	scoped_lock(this->m_cs_map_sender)
	{
		this->m_map_sender.clear();
	}
}

template<class TKEY, class TSENDER>
object_ptr<TSENDER> net::io::sender::Igroup_map<TKEY, TSENDER>::find(const TKEY& _key) const noexcept
{
	// declare)
	object_ptr<TSENDER> temp;

	scoped_lock(this->m_cs_map_sender)
	{
		// 1) ���� ã�´�
		auto iter_find = this->m_map_sender.find(_key);

		// 2) ã������ ���� ����
		if(iter_find != this->m_map_sender.end())
			temp = iter_find->second;
	}

	// return)
	return temp;
}

template<class TKEY, class TSENDER = net::io::Isender>
class net::io::sender::group_map : public net::io::sender::Igroup_map<TKEY,TSENDER>
{
public:
	virtual bool process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option) override
	{
		// check) _buffer->size_�� 0�� �ƴѰ�?
		RETURN_IF(_buffer.size() == 0, false)

		// check) _buffer->data_�� nullptr�� �ƴѰ�?
		RETURN_IF(_buffer.data() == nullptr, false)

		// check) ���۰� Overflow�Ǿ��°�?
		CGASSERT_ERROR(_buffer._is_buffer_overflow() == false);

		// 1) �����Ѵ�.
		scoped_lock(this->m_cs_map_sender)
		{
			for (auto iter = this->m_map_sender.begin(), iterEnd = this->m_map_sender.end(); iter != iterEnd; ++iter)
			{
				iter->second->send({ shared_buffer(_buffer), _count_message }, _option);
			}
		}

		// return)
		return true;
	}
};


}