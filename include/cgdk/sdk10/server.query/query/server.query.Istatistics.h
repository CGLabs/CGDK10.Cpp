//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Query Classes                            *
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
// query::statistics
//
//
//-----------------------------------------------------------------------------
extern	int						g_statistics_db_time;

namespace query
{
namespace statistics
{

struct unit_query
{
public:
	std::atomic<uint64_t>		query_try = 0;
	std::atomic<uint64_t>		query_success = 0;
	std::atomic<uint64_t>		query_fail = 0;
	std::atomic<uint64_t>		query_retry = 0;

	std::atomic<uint64_t>		alloc_session = 0;
	std::atomic<uint64_t>		free_session = 0;

	std::atomic<uint64_t>		create_session = 0;
	std::atomic<uint64_t>		destroy_session = 0;

public:
	unit_query&	operator =(const unit_query& rhs) noexcept
	{
		query_try.store(rhs.query_try);
		query_success.store(rhs.query_success);
		query_fail.store(rhs.query_fail);
		query_retry.store(rhs.query_retry);
		alloc_session.store(rhs.alloc_session);
		free_session.store(rhs.free_session);
		create_session.store(rhs.create_session);
		destroy_session.store(rhs.destroy_session);

		return *this;
	}

	void reset() noexcept
	{
		__zero_memory((void*)this, sizeof(unit_query));
	}
};

class Nquerier
{
public:																				  
			void				reset_statistics() noexcept							{ this->m_statistics_querier.reset();}
																					  
			const auto&			statistics_get_query_info() const noexcept			{ return this->m_statistics_querier;}
																					  
			uint64_t			statistics_get_query_try() const noexcept			{ return this->m_statistics_querier.query_try.load();}
			uint64_t			statistics_get_query_success() const noexcept		{ return this->m_statistics_querier.query_success.load();}
			uint64_t			statistics_get_query_fail() const noexcept			{ return this->m_statistics_querier.query_fail.load();}
			uint64_t			statistics_get_query_retry() const noexcept			{ return this->m_statistics_querier.query_retry.load();}
			uint64_t			statistics_get_query_processing() const noexcept	{ return (this->statistics_get_query_try() - this->statistics_get_query_success() - this->statistics_get_query_fail());}
			uint64_t			statistics_get_alloc_session() const noexcept		{ return this->m_statistics_querier.alloc_session.load();}
			uint64_t			statistics_get_free_session() const noexcept		{ return this->m_statistics_querier.free_session.load();}
			uint64_t			statistics_get_using_session() const noexcept		{ return (this->m_statistics_querier.alloc_session.load() - this->m_statistics_querier.free_session.load());}
			uint64_t			statistics_get_exist_session() const noexcept		{ return (this->m_statistics_querier.create_session.load() - this->m_statistics_querier.destroy_session.load());}
																					  
			void				statistics_on_query_try() noexcept					{ ++this->m_statistics_querier.query_try; ++m_statistics_querier_total.query_try;}
			void				statistics_on_query_success() noexcept				{ ++this->m_statistics_querier.query_success; ++m_statistics_querier_total.query_success;}
			void				statistics_on_query_fail() noexcept					{ ++this->m_statistics_querier.query_fail; ++m_statistics_querier_total.query_fail;}
			void				statistics_on_query_retry() noexcept				{ ++this->m_statistics_querier.query_retry; ++m_statistics_querier_total.query_retry;}
																					  
			void				statistics_on_alloc_session() noexcept				{ ++this->m_statistics_querier.alloc_session; ++m_statistics_querier_total.alloc_session;}
			void				statistics_on_free_session() noexcept				{ ++this->m_statistics_querier.free_session; ++m_statistics_querier_total.free_session;}
																					  
			void				statistics_on_create_session() noexcept				{ ++this->m_statistics_querier.create_session; ++m_statistics_querier_total.create_session;}
			void				statistics_on_create_session(uint64_t _count) noexcept{	this->m_statistics_querier.create_session += _count; m_statistics_querier_total.create_session += _count;}
			void				statistics_on_destroy_session() noexcept			{ ++this->m_statistics_querier.destroy_session; ++m_statistics_querier_total.destroy_session;}
			void				statistics_on_destroy_session(uint64_t _count) noexcept{ this->m_statistics_querier.destroy_session += _count; m_statistics_querier_total.destroy_session += _count;}

	static	const unit_query&	statistics_get_total_query_info() noexcept			{ return m_statistics_querier_total;}

// implementation) 
private:
			unit_query			m_statistics_querier;
	static	unit_query			m_statistics_querier_total;
};


}
}


}