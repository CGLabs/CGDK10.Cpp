#include "pch.h"


CGDK::object_ptr<group_channel> manager_channel::get_channel(uint64_t _channel_id)
{
	// declare) 
	CGDK::object_ptr<group_channel> pgroup_channel;

	scoped_lock(m_mutex_map_channel)
	{
		// 1) channel_id에 해당하는 객체를 찾는다.
		auto iter_find = m_map_channel.find(_channel_id);

		// 2-1) 찾았으면 값 읽어오기
		if (iter_find != m_map_channel.end())
		{
			pgroup_channel = iter_find->second;
		}
		// 2-2) 없으면 신규로 생성한다.
		else
		{
			// - 신규로 생성한다.
			pgroup_channel = make_object<group_channel>();

			// - 추가한다.
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
		// 1) channel_id에 해당하는 객체를 찾는다.
		auto iter_find = m_map_channel.find(_channel_id);

		// check) 없으면 그냥 리턴
		RETURN_IF(iter_find == m_map_channel.end());

		// 2) 삭제한다.
		m_map_channel.erase(iter_find);
	}
}
