//*****************************************************************************
//*                                                                           *
//*                     CGCII simple chatting system (1)                      *
//*                                                                           *
//*                             chatting Server                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// channel::manager
//
//-----------------------------------------------------------------------------
class channel::manager : public object::Ninitializable_startable, public object::Nnameable
{
public:
			object_ptr<Igroup>	register_channel(CHANNEL_ID _id_channel, own_ptr<Igroup> _pgroup_channel);
			own_ptr<Igroup>		unregister_channel(CHANNEL_ID _id_channel) noexcept;
			object_ptr<Igroup>	get_channel(CHANNEL_ID	_id_channel) noexcept;
			uint64_t			get_channel_count() const noexcept { scoped_lock(this->m_container_channel) { return this->m_container_channel.size(); } }
private:
	virtual	void				on_starting(context& _msg) override;
	virtual	void				on_stop() override;

			lockable<std::unordered_map<CHANNEL_ID, own_ptr<Igroup>>> m_container_channel;
			std::atomic<uint64_t> m_statistics_channel_create;
			std::atomic<uint64_t> m_statistics_channel_destroy;
};
