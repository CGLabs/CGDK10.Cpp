#include "pch.h"


void user::manager::register_user(user::socket* _psocket)
{
	// declare) 
	object_ptr<user::socket> psocket_user_old;

	scoped_lock(m_container_user)
	{
		// 1) ACCOUNT_ID�� ��� ���´�.
		auto aid = _psocket->m_aid;

		// 2) ã�´�.
		auto iter_find = m_container_user.find(aid);

		// 3-1) ã���� ��� ������ ����� user::socket ��ü�� psocket_user_old�� �����س��� ���� _psocket���� ������Ʈ�Ѵ�.
		if (iter_find != m_container_user.end())
		{
			psocket_user_old = iter_find->second;
			iter_find->second = _psocket;
		}
		// 3-2) ���� ��� �űԷ� �߰��Ѵ�.
		else
		{
			m_container_user.insert(std::make_pair(aid, _psocket));
		}
	}

	// 4) ���� socket�� ���������. (lock�ۿ��� ó��)
	if (psocket_user_old.exist())
	{
		psocket_user_old->closesocket();
	}
}

void user::manager::unregister_user(user::socket* _psocket) noexcept
{
	scoped_lock(m_container_user)
	{
		// 1) ACCOUNT_ID�� ��� ���´�.
		auto aid = _psocket->m_aid;

		// check) ACCOUNT_ID�� valid���� ������ ����. (���� Register�� �ȉ´�. ���)
		RETURN_IF(aid.valid() == false);

		// 2) ã�� �����Ѵ�.
		auto iter_find = m_container_user.find(aid);

		// check) ã�� ������ ��쵵 �׳� ������.
		RETURN_IF(iter_find == m_container_user.end());

		// 3) ã���� ��� �����.
		m_container_user.erase(iter_find);
	}
}
