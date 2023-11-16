#include "cgdk/sdk10/server.service.doss.h"

#include <iostream>
#if defined(_WIN32)
	#include <conio.h>
#endif

using namespace CGDK;

// declare) 
const std::size_t COUNT_TEST = 100000;
const std::size_t COUNT_SESSION = 10000;
const std::size_t EID_MAX = 10000;


class simple_session : public doss::session<>
{
protected:
	virtual	void on_entity_request_checkin(doss::Itransactable* /*_ptransactable*/) override {}
	virtual	void on_entity_request_checkout(doss::Itransactable* /*_ptransactable*/) override {}
	virtual	void on_entity_request_command(doss::Itransactable* /*_ptransactable*/) override {}
	virtual	void on_entity_checkin(doss::Itransactable* /*_ptransactable*/) override {}
	virtual	void on_entity_fail_checkin(doss::Itransactable* /*_ptransactable*/) override {}
	virtual	void on_entity_checkout(doss::Itransactable* /*_ptransactable*/) override {}
	virtual	void on_entity_update(doss::Itransactable* /*_ptransactable*/) override {}
	virtual	void on_entity_command(doss::Itransactable* /*_ptransactable*/) override {}
};

void print_status(doss::Nrepository<>* _prepository)
{
	std::cout << "m_statistics_checkin -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkin << '\n';
	std::cout << "m_statistics_checkin_request -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkin_request << '\n';
	std::cout << "m_statistics_checkin_success -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkin_success << '\n';
	std::cout << "m_statistics_checkin_fail -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkin_fail << '\n';
	std::cout << "m_statistics_checkout_request -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkout_request << '\n';
	std::cout << "m_statistics_checkout_success -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkout_success << '\n';
	std::cout << "m_statistics_checkout_fail -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkout_fail << '\n';
	std::cout << "m_statistics_checkout_forcible -> "sv << (uint64_t)_prepository->statistics().m_statistics_checkout_forcible << '\n';
	std::cout << "m_statistics_transaction_request -> "sv << (uint64_t)_prepository->statistics().m_statistics_command_request << '\n';
	std::cout << "m_statistics_transaction_success -> "sv << (uint64_t)_prepository->statistics().m_statistics_command_success << '\n';
	std::cout << "m_statistics_transaction_fail -> "sv << (uint64_t)_prepository->statistics().m_statistics_command_fail << '\n';

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

void test_1()
{
	auto prepository = make_own<doss::repository::rdb<>>();
	prepository->start();

	{
		std::vector<own_ptr<simple_session>> vector_session;
		vector_session.reserve(COUNT_SESSION);

		// - make session
		for (std::size_t i = 0; i < COUNT_SESSION; ++i)
		{
			vector_session.push_back(make_own<simple_session>());
		}

		// - request checkin
		vector_session[0]->checkin(make_entity_id(1llu, 10llu), prepository);
		vector_session[0]->checkin(make_entity_id(1llu, 10llu), prepository);

		//_getch();

		// - request transaction
		vector_session[0]->request(doss::make_command(eTRANSACTION_TYPE::COMMAND));
		vector_session[0]->request(doss::make_command(eTRANSACTION_TYPE::COMMAND));
		vector_session[0]->request(doss::make_command(eTRANSACTION_TYPE::COMMAND));
		vector_session[0]->request(doss::make_command(eTRANSACTION_TYPE::COMMAND));
		vector_session[0]->request(doss::make_command(eTRANSACTION_TYPE::COMMAND));
		vector_session[0]->request(doss::make_command(eTRANSACTION_TYPE::COMMAND));

		// - checkout
		for (std::size_t i = 0; i < COUNT_SESSION; ++i)
		{
			vector_session[i]->checkout();
		}
	}

	while (_getch() != 0x1b)
	{
		print_status(prepository);
	}
}

void test_2()
{
	// 1) create repository
	auto prepository = make_own<doss::repository::remote<>>();

	// 2) start repository
	prepository->start({{ net::ip::address_v6::loopback() }});

	// 3) wait until establish
	prepository->wait();

	{
		std::vector<own_ptr<simple_session>> vector_session;
		vector_session.reserve(COUNT_SESSION);

		// - make session
		for (std::size_t i = 0; i < COUNT_SESSION; ++i)
		{
			vector_session.push_back(make_own<simple_session>());
		}

		// - request checkin
		vector_session[0]->checkin(make_entity_id( 1llu, 10llu ), prepository);

		while (_getch() != 0x1b)
		{
			print_status(prepository);
		}


		vector_session[1]->checkin(make_entity_id( 1llu, 10llu ), prepository);

		while (_getch() != 0x1b)
		{
			print_status(prepository);
		}


		vector_session[0]->checkin(make_entity_id( 1llu, 11llu), prepository);

		while (_getch() != 0x1b)
		{
			print_status(prepository);
		}

		vector_session[1]->checkout();

		while (_getch() != 0x1b)
		{
			print_status(prepository);
		}

		// - checkout
		for (std::size_t i = 0; i < COUNT_SESSION; ++i)
		{
			vector_session[i]->checkout();
		}
	}

	while (_getch() != 0x1b)
	{
		print_status(prepository);
	}
}

void test_3()
{
	auto prepository = make_own<doss::repository::remote<>>();
	prepository->start({{ net::ip::address_v6::loopback() }});
	prepository->wait();

	std::cout << "start\n"sv;

	{
		std::vector<own_ptr<simple_session>> vector_session;
		vector_session.reserve(COUNT_SESSION);

		//// TEST 1)
		//{

		//	// - make session
		//	for (std::size_t i = 0; i < COUNT_SESSION; ++i)
		//	{
		//		vector_session.push_back(make_own<simple_session>());
		//	}

		//	{
		//		uint64_t eid_index = 1;
		//		vector_session[0]->checkin(sENTITY_ID{ eid_index }, prepository);

		//		eid_index = 2;
		//		vector_session[0]->checkin(sENTITY_ID{ eid_index }, prepository);

		//		eid_index = 3;
		//		vector_session[0]->checkin(sENTITY_ID{ eid_index }, prepository);

		//		eid_index = 4;
		//		vector_session[0]->checkin(sENTITY_ID{ eid_index }, prepository);
		//	}
		//}

		//// TEST 3)
		//{
		//	// - make session
		//	for (std::size_t i = 0; i < COUNT_SESSION; ++i)
		//	{
		//		vector_session.push_back(make_own<simple_session>());
		//	}

		//	{
		//		uint64_t eid_index = 1;
		//		vector_session[0]->checkin(sENTITY_ID{ eid_index }, prepository);

		//		vector_session[1]->checkin(sENTITY_ID{ eid_index }, prepository);

		//		vector_session[2]->checkin(sENTITY_ID{ eid_index }, prepository);

		//		vector_session[3]->checkin(sENTITY_ID{ eid_index }, prepository);
		//	}

		//	_getch();

		//	CGASSERT_ERROR(vector_session[0]->get_checkin_id().empty());
		//	CGASSERT_ERROR(vector_session[0]->get_entity().empty());

		//	CGASSERT_ERROR(vector_session[1]->get_checkin_id().empty());
		//	CGASSERT_ERROR(vector_session[1]->get_entity().empty());

		//	CGASSERT_ERROR(vector_session[2]->get_checkin_id().empty());
		//	CGASSERT_ERROR(vector_session[2]->get_entity().empty());

		//	CGASSERT_ERROR(vector_session[3]->get_checkin_id().exist());
		//	CGASSERT_ERROR(vector_session[3]->get_entity().exist());

		//	vector_session[3]->checkout();
		//}

		//// TEST 4)
		//{
		//	// - make session
		//	for (std::size_t i = 0; i < COUNT_SESSION; ++i)
		//	{
		//		vector_session.push_back(make_own<simple_session>());
		//	}

		//	for (std::size_t i = 0; i < COUNT_SESSION; ++i)
		//	{
		//		uint64_t eid_index = i + 1;
		//		vector_session[i]->checkin(sENTITY_ID{ eid_index }, prepository);
		//	}

		//	for (std::size_t i = 0; i < COUNT_SESSION; ++i)
		//	{
		//		vector_session[i]->checkout();
		//	}
		//}

		// TEST 5)
		{
			// - make session
			for (std::size_t i = 0; i < COUNT_SESSION; ++i)
			{
				vector_session.push_back(make_own<simple_session>());
			}

			// - checkin and request command
			for(std::size_t i = 0; i < COUNT_TEST; ++i)
			{
				auto index = rand() % COUNT_SESSION;

				auto operation = rand() % 3;
				//auto operation = 0;

				switch (operation)
				{
				case	0:
						{
							sOBJECT_ID eid_index = (rand() % EID_MAX) + 1;
							vector_session[index]->checkin(make_entity_id(1llu, eid_index),  prepository);
						}
						break;

				case	1:
						{
							vector_session[index]->checkout();
						}
						break;

				case	2:
						{
							vector_session[index]->request(doss::make_command(eTRANSACTION_TYPE::COMMAND));
						}
						break;

				default:
						break;
				}

				//std::cout << "[" << i << "]\n"sv;
			}
		}

		std::cout << "done\n"sv;

		_getch();


		print_status(prepository);

		int count_x = 0;
		for (std::size_t i = 0; i < COUNT_SESSION; ++i)
		{
			if (vector_session[i]->get_checkin_id().exist())
			{
				++count_x;
			}
		}
		std::cout << "session - not checkouted -> "sv << count_x << '\n';


		_getch();


		std::cout << "complete\n"sv;

		for (std::size_t i = 0; i < COUNT_SESSION; ++i)
		{
			vector_session[i]->checkout();
		}

		_getch();

		std::cout << "all check_out\n"sv;
	}

	while (_getch() != 0x1b)
	{
		print_status(prepository);
	}
}

int main()
{
	//test_1();
	//test_2();
	test_3();
}
