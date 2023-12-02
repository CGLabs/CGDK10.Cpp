//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            Server Log Classes                             *
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

//-----------------------------------------------------------------------------
/**

@class		Ilogger


*/
//-----------------------------------------------------------------------------
class CGDK::Ilogger :
	virtual public				Ireferenceable
{
public:
			Ilogger() noexcept : m_plog_filter(), m_count_log_total(0), m_count_log{0}, m_lockable_count_log() {}
	virtual	~Ilogger() noexcept	{}

public:
			void				trace(LOG_RECORD* _plog_record) { std::vector<object_ptr<LOG_RECORD>> vector_log_records; vector_log_records.push_back(std::move(_plog_record)); this->process_log(vector_log_records);}
			void				trace(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) { RETURN_IF(_vector_log_record.empty(), ); this->process_log(_vector_log_record); }

			void				set_filter(Ilog_filter* _plog_filter) noexcept { m_plog_filter=_plog_filter;}
	[[nodiscard]] auto			get_filter() const noexcept { return m_plog_filter;}

	[[nodiscard]] size_t		get_log_count() const noexcept { return m_count_log_total; }
	[[nodiscard]] size_t		get_log_count(log_type_t _type) const noexcept { return this->m_count_log.at(static_cast<int>(_type)); }
			void				reset_log_count() noexcept { scoped_lock(m_lockable_count_log) { for (auto& iter : this->m_count_log) iter = 0; m_count_log_total = 0; } }
	[[nodiscard]] lockable<>&	get_count_lock() noexcept { return m_lockable_count_log; }

	[[nodiscard]] const auto&	_log_count() const noexcept { return this->m_count_log; }

			void				detach_from_parent() noexcept;

protected:
	virtual	void				process_log(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) PURE;
			void				process_count_log(log_type_t _type);

protected:
			object_ptr<Ilog_filter>	m_plog_filter;

			size_t				m_count_log_total;
			std::array<size_t, MAX_LOG_TYPE> m_count_log;
			lockable<>			m_lockable_count_log;
			object::Iattachable<Ilogger>* m_pparent = nullptr;
			friend class logger_hub;
};
