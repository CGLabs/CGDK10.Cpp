#include "pch.h"


CGDK::object_ptr<group_channel> manager_channel::get_channel(uint64_t _channel_id)
{
	// declare) 
	CGDK::object_ptr<group_channel> pgroup_channel;

	scoped_lock(m_mutex_map_channel)
	{
		// 1) channel_id�� �ش��ϴ� ��ü�� ã�´�.
		auto iter_find = m_map_channel.find(_channel_id);

		// 2-1) ã������ �� �о����
		if (iter_find != m_map_channel.end())
		{
			pgroup_channel = iter_find->second;
		}
		// 2-2) ������ �űԷ� �����Ѵ�.
		else
		{
			// - �űԷ� �����Ѵ�.
			pgroup_channel = make_object<group_channel>();

			// - �߰��Ѵ�.
			m_map_channel.insert({ _channel_id, pgroup_channel });
		}
	}

	// return)
	return pgroup_channel;
}

void manager_channel::unregister_channel(uint64_t _channel_id) noexcept
{
	scoped_lock(m_mutex_map_channel)
	{
		// 1) channel_id�� �ش��ϴ� ��ü�� ã�´�.
		auto iter_find = m_map_channel.find(_channel_id);

		// check) ������ �׳� ����
		RETURN_IF(iter_find == m_map_channel.end());

		// 2) �����Ѵ�.
		m_map_channel.erase(iter_find);
	}
}
