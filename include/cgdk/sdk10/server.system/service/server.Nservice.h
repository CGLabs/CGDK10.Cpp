//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Admin Classes                            *
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
// ----------------------------------------------------------------------------
//
// Nservice
//
//
// ----------------------------------------------------------------------------
class server_system::Nservice :
	public						Nstatic_service_logger,
	public						Iservice,
	public						object::Ninitializable_startable,
	public						object::Npausable,
	public						net::io::messageable::Nbase,
	virtual public				Nmessage_transmitter
{
public:
			Nservice() noexcept;
			Nservice(const std::string_view _name) noexcept;
	virtual ~Nservice() noexcept;

	// 1) server setting Info (from HostAgent)
	[[nodiscard]] const auto&	info() const noexcept { return this->m_service_instance_info; }
	[[nodiscard]] auto&			setting() noexcept { return this->m_service_setting;}
	[[nodiscard]] const auto&	setting() const noexcept { return this->m_service_setting;}
			void				setting(server_admin::sSERVICE_SETTING&& _service_setting);

	// 2) wait
			bool				wait_destroy(const chrono::tick::duration& _wait = chrono::tick::duration::max());

protected:
	virtual	void				on_service_setting(context& _context);
	virtual void				on_service_setting(const server_admin::sSERVICE_SETTING& _server_setting);
	virtual	void				on_service_info(const shared_buffer& _info_server);

	virtual	result_code			process_initialize(context& _context) override;
	virtual	result_code			process_destroy() noexcept override;
	virtual	result_code			process_start(context& _context) override;
	virtual	result_code			process_stop() noexcept override;
	virtual	void				process_pause() override;
	virtual	void				process_resume() override;

	virtual result_code			_process_initializing(context& _context) override;
	virtual result_code			_process_starting(context& _context) override;

	virtual	void				process_state_changed(eOBJECT_STATE _state_new, eOBJECT_STATE _state_old) override;

	virtual	void				process_set_name(std::string_view _name) override { this->m_service_setting.nickname = _name; }
	[[nodiscard]] virtual bool	process_is_this(std::string_view _str_compare) const noexcept override { return this->m_service_setting.nickname == _str_compare; }
	[[nodiscard]] virtual std::string_view process_get_name() const noexcept override { return this->m_service_setting.nickname; }

	// 1) admin server에서 설정한 정보.(from Host Agent)
			server_admin::sSERVICE_SETTING m_service_setting;
			server_admin::sSERVICE_INSTANCE_INFO m_service_instance_info;

	// 2) cv destroy
			std::mutex				m_lock_destroy;
			std::condition_variable	m_cv_destroy;
};


}