#include "pch.h"


object_ptr<channel::Igroup> channel::manager::register_channel(CHANNEL_ID _channel, own_ptr<channel::Igroup> _pgroup_channel)
{
	// check) 
	CGASSERT_ERROR(_pgroup_channel.exist());

	// declare) 
	object_ptr<channel::Igroup> pgroup_channel = _pgroup_channel;

	// check) _channelID�� 0�̸� �ȉ´�!
	CGASSERT_ERROR(_channel != 0);

	scoped_lock(this->m_container_channel)
	{
		// 1) ���� ���� ���� �ִ��� ã�� ����.
		auto iter_find = this->m_container_channel.find(_channel);

		// check) ���� ã������ ã�� ���� �������ش�.
		THROW_IF(iter_find != this->m_container_channel.end(), throwable::failure(eRESULT::ALEADY_EXIST));

		// 2) ã�� �������� �߰��Ѵ�.
		this->m_container_channel.insert(std::make_pair(_channel, std::move(_pgroup_channel)));

		// 3) CHANNEL ID�� �����Ѵ�.
		pgroup_channel->m_id_channel = _channel;
		pgroup_channel->m_pmanager = this;
	}

	// 4) �̶����� ������ ������ش�.
	pgroup_channel->enable_member_enter();

	// statistics)
	++this->m_statistics_channel_create;

	// View) ���ο� channel�� �߰��Ǿ����� �˸���.
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
		// 1) ���� ���� ���� �ִ��� ã�� ����.
		auto iter_find = this->m_container_channel.find(_id_channel);

		// check) ã�� �������� �׳� �ٷ� ����...
		RETURN_IF(iter_find == this->m_container_channel.end(), own_ptr<channel::Igroup>());

		// check) ã�Ҵ��� Ȯ��
		CGASSERT_ERROR(iter_find->second->m_id_channel == _id_channel);

		// 3) ���� ������ ����
		pgroup_channel = std::move(iter_find->second);

		// check) pgrounpChannel�� nullptr�̸� �ȉ´�.
		CGASSERT_ERROR(pgroup_channel.exist());

		// 4) �����Ѵ�.
		this->m_container_channel.erase(iter_find);

		// 5) CHANNEL_ID���� Reset�Ѵ�.
		pgroup_channel->m_id_channel = 0;
		pgroup_channel->m_pmanager.reset();
	}

	// statistics)
	++this->m_statistics_channel_destroy;

	// view) channel�� ���������� �˸���.
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
		// 1) ���� ���� CHANNEL_ID�� ���� channel�� �ִ��� ã�� ����.
		auto iter_find = this->m_container_channel.find(_channel);

		// 2-1) ã������ �װ��� ����Ѵ�.
		if (iter_find != this->m_container_channel.end())
		{
			// - �����Ѵ�.
			pgroup_channel = iter_find->second;
		}
		// 2-2) ã�� �������� �⺻ channel�� �����ؼ� ����Ѵ�.
		else
		{
			// - make channel
			auto pgroup_chatting = make_own<channel::group_chatting>();

			// - set setting
			pgroup_chatting->set_name(NFMT::format("chatting room {}"sv, _channel));

			// - �� channel ��ü�� �����ؼ� ����Ѵ�.
			pgroup_channel = register_channel(_channel, std::move(pgroup_chatting));
		}

		// check) pgrounpChannel�� nullptr�̸� �ȉ´�.
		CGASSERT_ERROR(pgroup_channel.exist());
	}

	// 2) pgroup_channel�� start�Ѵ�.
	if (pgroup_channel->get_object_state() == eOBJECT_STATE::NONE)
	{
		pgroup_channel->start();
	}

	// return)ã�� channel�� �����ش�.
	return pgroup_channel;
}

void channel::manager::on_starting(context& /*_msg*/)
{
	// 1) make channel
	auto pgroup_waiting = make_own<channel::group_waiting>();

	// 2) set setting
	pgroup_waiting->set_name("waiting channel"sv);

	// 3) wait channel�� �����ؼ� ����Ѵ�.
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
