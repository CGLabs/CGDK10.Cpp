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

@class		log_archive


*/
//-----------------------------------------------------------------------------
class CGDK::log_archive :
	virtual public				Ireferenceable
{
public:
			log_archive();
	virtual ~log_archive() noexcept;

public:
			std::vector<object_ptr<LOG_RECORD>> get_stored_log(size_t _position = 0) const;

			void				capacity(size_t _capacity) noexcept;
	[[nodiscard]] size_t		capacity() const noexcept { return this->m_capacity; }

protected:
	virtual	void				process_store_log(std::vector<object_ptr<LOG_RECORD>>&& _vector_plog_record);

private:
			circular_list<object_ptr<LOG_RECORD>> m_archive_log;
			size_t				m_capacity;

			size_t				m_index_stored_log;
			lockable<>			m_lockable_index_stored_log;
};
