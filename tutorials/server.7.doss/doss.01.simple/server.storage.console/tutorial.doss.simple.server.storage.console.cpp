#include "cgdk/sdk10/server.service.doss.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

class simple_repository : public CGDK::doss::repository::rdb<>
{
public:
	explicit simple_repository(std::string_view _name) : CGDK::doss::repository::rdb<>(_name) {}

public:
	virtual	CGDK::result_code	on_request_checkin(CGDK::doss::Itransactable* _ptransactable)
	{
		//std::cout << "[repository] on_checkin"sv << '\n';
		_ptransactable->set_result(eRESULT::SUCCESS);
		return eRESULT::SUCCESS;
	}
	virtual	CGDK::result_code	on_request_checkout(CGDK::doss::Itransactable* _ptransactable)
	{
		//std::cout << "[repository] on_checkout"sv << '\n';
		_ptransactable->set_result(eRESULT::SUCCESS);
		return eRESULT::SUCCESS;
	}
	virtual	CGDK::result_code	on_request_command(CGDK::doss::Itransactable* _ptransactable)
	{
		//std::cout << "[repository] on_transaction"sv << '\n';
		_ptransactable->set_result(eRESULT::SUCCESS);
		return eRESULT::SUCCESS;
	}
	virtual	CGDK::result_code	on_request_update(CGDK::doss::Itransactable* _ptransactable)
	{
		//std::cout << "[repository] on_update"sv << '\n';
		_ptransactable->set_result(eRESULT::SUCCESS);
		return eRESULT::SUCCESS;
	}
};

void print_status(doss::Nrepository<>* _prepository)
{
	std::cout << "m_statistics_checkin -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkin << "\n";
	std::cout << "m_statistics_checkin_request -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkin_request << "\n";
	std::cout << "m_statistics_checkin_success -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkin_success << "\n";
	std::cout << "m_statistics_checkin_fail -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkin_fail << "\n";
	std::cout << "m_statistics_checkout_request -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkout_request << "\n";
	std::cout << "m_statistics_checkout_success -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkout_success << "\n";
	std::cout << "m_statistics_checkout_fail -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkout_fail << "\n";
	std::cout << "m_statistics_checkout_forcible -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkout_forcible << "\n";
	std::cout << "m_statistics_transaction_request -> "sv << (uint64_t)_prepository->statistics().m_statistics_command_request << "\n";
	std::cout << "m_statistics_transaction_success -> "sv << (uint64_t)_prepository->statistics().m_statistics_command_success << "\n";
	std::cout << "m_statistics_transaction_fail -> "sv << (uint64_t)_prepository->statistics().m_statistics_command_fail << "\n";

	auto count_i = 0;
	for (auto& iter : _prepository->m_map_entity_by_eid)
	{
		if (iter.second->get_queued_transaction_count() != 0)
		{
			++count_i;
		}
	}
	std::cout << "entity - command not completed ->"sv << count_i << '\n';

	auto count_j = 0;
	for (auto& iter : _prepository->m_map_entity_by_eid)
	{
		if (iter.second->get_checkin_count() != 0)
		{
			++count_j;
		}
	}
	std::cout << "entity - not checkouted -> "sv << count_j << '\n';
}

int main()
{
	// 1) create repository
	auto prepository = make_own<simple_repository>(std::string_view("test_repository"sv));

	// 2) start repository
	prepository->start();

	// 3) create depot
	auto pdepot_remote = make_own<doss::depot>(std::string_view("test_remote_repository"sv));

	// 4) ...
	pdepot_remote->set_repository(prepository);

	// 5) start
	pdepot_remote->start();

	// 6) wait util press 'esc'
	while (_getch() != 0x1b)
	{
		print_status(prepository);
	}

	// return)
	return 0;
}
