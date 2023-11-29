#include "pch.h"


object_ptr<channel::Igroup> channel::manager::register_channel(CHANNEL_ID _channel, own_ptr<channel::Igroup> _pgroup_channel)
{
	// check) 
	CGASSERT_ERROR(_pgroup_channel.exist());

	// declare) 
	object_ptr<channel::Igroup> pgroup_channel = _pgroup_channel;

	// check) _channelID가 0이면 안됀다!
	CGASSERT_ERROR(_channel != 0);

	scoped_lock(this->m_container_channel)
	{
		// 1) 먼저 같은 것이 있는지 찾아 본다.
		auto iter_find = this->m_container_channel.find(_channel);

		// check) 만약 찾았으면 찾은 것을 리턴해준다.
		THROW_IF(iter_find != this->m_container_channel.end(), throwable::failure(eRESULT::ALEADY_EXIST));

		// 2) 찾지 못했으면 추가한다.
		this->m_container_channel.insert(std::make_pair(_channel, std::move(_pgroup_channel)));

		// 3) CHANNEL ID를 설정한다.
		pgroup_channel->m_id_channel = _channel;
		pgroup_channel->m_pmanager = this;
	}

	// 4) 이때부터 접속을 허용해준다.
	pgroup_channel->enable_member_enter();

	// statistics)
	++this->m_statistics_channel_create;

	// View) 새로운 channel이 추가되었음을 알린다.
	g_pservice->transmit_message(sMESSAGE_NOTIFY(eMESSAGE::WINDOWS::NOTIFY_UPDATE, CGNOTIFY_CHANNEL_ADD, reinterpret_cast<uintptr_t>(pgroup_channel.get())));

	// return)
	return pgroup_channel;
}
own_ptr<channel::Igroup> channel::manager::unregister_channel(CHANNEL_ID _id_channel) noexcept
{
	// Declare) 
	own_ptr<channel::Igroup> pgroup_channel;

	scoped_lock(this->m_container_channel)
	{
		// 1) 먼저 같은 것이 있는지 찾아 본다.
		auto iter_find = this->m_container_channel.find(_id_channel);

		// check) 찾지 못했으면 그냥 바로 리턴...
		RETURN_IF(iter_find == this->m_container_channel.end(), own_ptr<channel::Igroup>());

		// check) 찾았는지 확인
		CGASSERT_ERROR(iter_find->second->m_id_channel == _id_channel);

		// 3) 먼저 복사해 놓고
		pgroup_channel = std::move(iter_find->second);

		// check) pgrounpChannel이 nullptr이면 안됀다.
		CGASSERT_ERROR(pgroup_channel.exist());

		// 4) 제거한다.
		this->m_container_channel.erase(iter_find);

		// 5) CHANNEL_ID값을 Reset한다.
		pgroup_channel->m_id_channel = 0;
		pgroup_channel->m_pmanager.reset();
	}

	// statistics)
	++this->m_statistics_channel_destroy;

	// view) channel이 없어졌음을 알린다.
	g_pservice->transmit_message(sMESSAGE_NOTIFY(eMESSAGE::WINDOWS::NOTIFY_UPDATE, CGNOTIFY_CHANNEL_REMOVE, reinterpret_cast<uintptr_t>(pgroup_channel.get())));

	// return)
	return pgroup_channel;
}

object_ptr<channel::Igroup> channel::manager::get_channel(CHANNEL_ID _channel) noexcept
{
	// Declare) 
	object_ptr<channel::Igroup> pgroup_channel;

	scoped_lock(this->m_container_channel)
	{
		// 1) 먼저 같은 CHANNEL_ID를 가진 channel이 있는지 찾아 본다.
		auto iter_find = this->m_container_channel.find(_channel);

		// 2-1) 찾았으면 그것을 사용한다.
		if (iter_find != this->m_container_channel.end())
		{
			// - 복사한다.
			pgroup_channel = iter_find->second;
		}
		// 2-2) 찾지 못했으면 기본 channel을 생성해서 등록한다.
		else
		{
			// - make channel
			auto pgroup_chatting = make_own<channel::group_chatting>();

			// - set setting
			pgroup_chatting->set_name(NFMT::format("chatting room {}"sv, _channel));

			// - 새 channel 객체를 생성해서 등록한다.
			pgroup_channel = register_channel(_channel, std::move(pgroup_chatting));
		}

		// check) pgrounpChannel이 nullptr이면 안됀다.
		CGASSERT_ERROR(pgroup_channel.exist());
	}

	// 2) pgroup_channel을 start한다.
	if (pgroup_channel->get_object_state() == eOBJECT_STATE::NONE)
	{
		pgroup_channel->start();
	}

	// return)찾은 channel을 돌려준다.
	return pgroup_channel;
}

void channel::manager::on_starting(context& /*_msg*/)
{
	// 1) make channel
	auto pgroup_waiting = make_own<channel::group_waiting>();

	// 2) set setting
	pgroup_waiting->set_name("waiting channel"sv);

	// 3) wait channel을 생성해서 등록한다.
	this->register_channel(CHANNEL_ID(1), std::move(pgroup_waiting));
}
void channel::manager::on_stop()
{
	// declare) 
	lockable<std::unordered_map<CHANNEL_ID, own_ptr<channel::Igroup>>> container_channel;

	// 1) move channels
	scoped_lock(this->m_container_channel)
	{
		container_channel = std::move(this->m_container_channel);
	}

	// 2) destroy all
	container_channel.clear();
}
