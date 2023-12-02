//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                              Account Classes                              *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
// doss::CAccount
//-----------------------------------------------------------------------------
namespace CGDK
{

class doss::Idepot::group_immigration :
	public						group::list<socket>,
	public						net::io::messageable::Nbase,
	public						object::Nnameable,
	public                      object::Ninitializable_startable
{
public:
			group_immigration();
			group_immigration(const std::string_view _name);
	virtual ~group_immigration();

public:
			void				set_next_group(Igroup_enterable<socket>* _pgroup) noexcept { m_pgroup_next = _pgroup; }
	[[nodiscard]] auto			get_next_group() const noexcept { return m_pgroup_next; }

protected:
	// 1) Initialize/Destry
	virtual	void				on_initializing (context& _msg) override;
	virtual	void				on_initialize (context& _msg) override;
	virtual	void				on_destroying () override;
	virtual	void				on_destroy () override;

	// 2) Start/Stop
	virtual	void				on_starting (context& _msg) override;
	virtual	void				on_start (context& _msg) override;
	virtual	void				on_stopping () override;
	virtual	void				on_stop () override;

	// 3) Member Enter/Leave
	virtual	result_code			on_member_entering (socket* _pmember, sMESSAGE& _msg);
	virtual	void				on_member_entered (socket* _pmember, sMESSAGE& _msg);
	virtual	uintptr_t			on_member_leaving (socket* _pmember);
	virtual	void				on_member_leaved (socket* _pmember, uintptr_t _result);

protected:
	// Declare Message Map
	DECLARE_CGMESSAGE_MAP

	// 1) Message 처리 함수
	virtual result_code			on_message (sMESSAGE_NETWORK& _msg) override;
			result_code			on_message_SERVER_DOSS_REQUEST_CERTIFY (sMESSAGE_NETWORK& _msg);

protected:
			object_ptr<Igroup_enterable<socket>> m_pgroup_next;
};


}