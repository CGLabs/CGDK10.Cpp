//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                 Distributed Object Storage System Classes                 *
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
// CGServerentity::Centity
//-----------------------------------------------------------------------------
namespace CGDK
{

struct doss::statistics::transactable
{
public:
			transactable() noexcept {}
			transactable(const transactable& _rhs) noexcept;

public:
			transactable&		operator = (const transactable& _rhs) noexcept { set(_rhs); return *this; }

public:
			std::atomic<uint64_t>	count_process_request_immidiately{ 0 };
			std::atomic<uint64_t>	count_process_request_pended{ 0 };
			std::atomic<uint64_t>	count_processing_request{ 0 };
			std::atomic<uint64_t>	count_success{ 0 };
			std::atomic<uint64_t>	count_fail{ 0 };

public:
			void				set(const transactable& __rhs) noexcept;
};


struct doss::statistics::entity
{
public:
			entity() noexcept {}
			entity(const entity& __rhs) noexcept;

public:
			entity&				operator = (const entity& _rhs) noexcept { set(_rhs); return *this; }

public:
			std::atomic<uint64_t> count_login_request{ 0 };
			std::atomic<uint64_t> count_login_success{ 0 };
			std::atomic<uint64_t> count_login_fail{ 0 };
			std::atomic<uint64_t> count_logout_request{ 0 };
			std::atomic<uint64_t> count_logout_complete{ 0 };

			std::atomic<uint64_t> count_checkin_request{ 0 };
			std::atomic<uint64_t> count_checkin_success{ 0 };
			std::atomic<uint64_t> count_checkin_fail{ 0 };
			std::atomic<uint64_t> count_checkout_request{ 0 };
			std::atomic<uint64_t> count_checkout_success{ 0 };

public:
			void				set(const entity& _rhs) noexcept;
};


struct doss::statistics::repository
{
public:
			repository() noexcept {}
			repository(const repository& _rhs) noexcept;

public:
			repository&			operator = (const repository& _rhs) noexcept { set(_rhs); return *this; }

public:
			std::atomic<int64_t> m_statistics_transactable_request { 0 };
			std::atomic<int64_t> m_statistics_transactable_complete{ 0 };
								 
			std::atomic<int64_t> m_statistics_login{ 0 };
			std::atomic<int64_t> m_statistics_login_request{ 0 };
			std::atomic<int64_t> m_statistics_login_success{ 0 };
			std::atomic<int64_t> m_statistics_login_fail{ 0 };
			std::atomic<int64_t> m_statistics_logout_request{ 0 };
			std::atomic<int64_t> m_statistics_logout_complete{ 0 };
								 
			std::atomic<int64_t> m_statistics_checkin{ 0 };
			std::atomic<int64_t> m_statistics_checkin_request{ 0 };
			std::atomic<int64_t> m_statistics_checkin_success{ 0 };
			std::atomic<int64_t> m_statistics_checkin_fail{ 0 };
			std::atomic<int64_t> m_statistics_checkout_request{ 0 };
			std::atomic<int64_t> m_statistics_checkout_success{ 0 };
			std::atomic<int64_t> m_statistics_checkout_fail{ 0 };
			std::atomic<int64_t> m_statistics_checkout_forcible{ 0 };

			std::atomic<int64_t> m_statistics_create_request{ 0 };
			std::atomic<int64_t> m_statistics_create_success{ 0 };
			std::atomic<int64_t> m_statistics_create_fail{ 0 };
			std::atomic<int64_t> m_statistics_remove_request{ 0 };
			std::atomic<int64_t> m_statistics_remove_complete{ 0 };

			std::atomic<int64_t> m_statistics_command_request{ 0 };
			std::atomic<int64_t> m_statistics_command_success{ 0 };
			std::atomic<int64_t> m_statistics_command_fail{ 0 };

			std::atomic<int64_t> m_statistics_update_request{ 0 };
			std::atomic<int64_t> m_statistics_update_success{ 0 };
			std::atomic<int64_t> m_statistics_update_fail{ 0 };

public:
			void				set(const repository& _rhs) noexcept;

};


class doss::statistics::Nrepository
{
public:
	// 1) repository info
			auto& statistics() const noexcept { return m_statistics; }
			auto& get_repository_id() const noexcept { return m_repository_id;}

protected:
	// 2) statistics
			doss::statistics::repository m_statistics;

	// 3) repository id
			sREPOSITORY_ID		m_repository_id;
};



}