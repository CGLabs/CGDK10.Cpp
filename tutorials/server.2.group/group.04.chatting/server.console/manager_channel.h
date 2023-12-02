#pragma once

class manager_channel : 
	virtual public				CGDK::Ireferenceable
{
protected:
			CGDK::object_ptr<group_channel> get_channel(uint64_t _channel_id);
			void				unregister_channel(uint64_t _channel_id) noexcept;

protected:
			CGDK::lockable<>	m_mutex_map_channel;
			std::map<uint64_t, CGDK::object_ptr<group_channel>> m_map_channel;
};
