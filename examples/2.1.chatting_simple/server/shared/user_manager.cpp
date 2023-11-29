#include "pch.h"


void user::manager::register_user(user::socket* _psocket)
{
	// declare) 
	object_ptr<user::socket> psocket_user_old;

	scoped_lock(m_container_user)
	{
		// 1) ACCOUNT_ID를 얻어 놓는다.
		auto aid = _psocket->m_aid;

		// 2) 찾는다.
		auto iter_find = m_container_user.find(aid);

		// 3-1) 찾았을 경우 기존에 저장된 user::socket 객체를 psocket_user_old에 저장해놓고 값을 _psocket으로 업데이트한다.
		if (iter_find != m_container_user.end())
		{
			psocket_user_old = iter_find->second;
			iter_find->second = _psocket;
		}
		// 3-2) 없을 경우 신규로 추가한다.
		else
		{
			m_container_user.insert(std::make_pair(aid, _psocket));
		}
	}

	// 4) 기존 socket은 끊어버린다. (lock밖에서 처리)
	if (psocket_user_old.exist())
	{
		psocket_user_old->closesocket();
	}
}

void user::manager::unregister_user(user::socket* _psocket) noexcept
{
	scoped_lock(m_container_user)
	{
		// 1) ACCOUNT_ID를 얻어 놓는다.
		auto aid = _psocket->m_aid;

		// check) ACCOUNT_ID가 valid하지 않으면 끝냄. (아직 Register가 안됀다. 경우)
		RETURN_IF(aid.valid() == false);

		// 2) 찾아 제거한다.
		auto iter_find = m_container_user.find(aid);

		// check) 찾지 못했을 경우도 그냥 끝낸다.
		RETURN_IF(iter_find == m_container_user.end());

		// 3) 찾았을 경우 지운다.
		m_container_user.erase(iter_find);
	}
}
