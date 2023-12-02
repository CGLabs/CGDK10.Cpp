//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        Server Query oledb Classes                         *
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
//-----------------------------------------------------------------------------
//
// query::rdb::oledb::session
//
// 1. query::rdb::oledb::session��!
//    1) session�� db�� ���ӵ� ��ü�̴�.
//    2) session���� ���� ���� statemement�� �Ҵ�޾� ����Ѵ�.
//    3) querier���� �Ҵ�޾� ����Ѵ�.
//    4) session�� ������ �����ϸ� m_pquerier�� �ǵ��� ����.
//
//-----------------------------------------------------------------------------
class query::rdb::oledb::session :
	public						ATL::CSession,
	virtual public				Ireferenceable
{
public:
			session();
	virtual	~session() noexcept;

public:
			std::recursive_mutex m_lockable_data_source;
			object_ptr<data_source>	m_pdata_source;
			object_ptr<querier>	m_pquerier;
			std::atomic<size_t>	m_count_requested;
			bool				m_flag_transaction = false;
public:
			void				open(data_source* _pdata_source, DBPROPSET* pPropSet = nullptr, ULONG ulPropSets = 0);
			void				reopen(DBPROPSET* _pprop_set = nullptr, ULONG _property_sets = 0) noexcept;

	template <class TQUERY = query_t>
	[[nodiscard]] object_ptr<TQUERY> alloc_query() { auto pquery = make_object<TQUERY>(); pquery->set_session(this); ++this->m_count_requested; return pquery; }

			result_code			start_transaction() noexcept;
			result_code			commit_transaction() noexcept;
			result_code			abort_transaction() noexcept;
public:
	virtual	void				process_dispose() noexcept override;

private:
			object_ptr<factory::object<session>> m_factory_object;


};


}