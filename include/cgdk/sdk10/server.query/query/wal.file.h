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
// Iserver_query
//
// 1. Iserver_query...
//    1) query request and have it's result
//
//    2) process
//       -> request_wal
//       -> process_write_complete
//       -> process_complete_wal
//
//-----------------------------------------------------------------------------
template <class TCHUNK, class TQUERIER>
class wal::file : 
// inherited classes)
	public						object::Nnameable,
	public                      object::Ninitializable_startable
{
// defintion) 
public:
	typedef	typename TQUERIER::IQUERY	IQUERY;
	typedef	typename TQUERIER::QUERIER	QUERIER;
	typedef	sCHUNK<TCHUNK>		CHUNK;
	typedef	sQUERY<IQUERY>		QUERY;


// contructor/destructor)
public:
			file() noexcept;
	virtual	~file() noexcept;

// public)
public:
			result_code			start (const context& _context) { return Nstartable::start(_context);}
	virtual	result_code			start (context& _context) override { return Nstartable::start(_context);}
			result_code			start (std::string_view _journaling_filename, std::size_t _max_size = 65536);
			result_code			start (std::wstring_view _journaling_filename, std::size_t _max_size = 65536);

			void				set_target (Inotifiable_file<TCHUNK, IQUERY>* _ptarget) noexcept { m_ptarget=_ptarget; }
			auto				get_target () const noexcept { return m_ptarget; }

			void				set_querier (TQUERIER* _pquerier) noexcept { m_pquerier =_pquerier; }
			auto				get_querier () const noexcept { return m_pquerier; }

			void				request_wal (TCHUNK&& _chunk);

// framework)
private:
	// - start/Stop
	virtual	void				on_starting (context& _context) override;
	virtual	void				on_start (context& _context) override;
	virtual	void				on_stopping () override;
	virtual	void				on_stop () override;

// implementation) 
protected:
			void				process_restore_file (const std::string_view _journaling_filename);
			void				process_recreate_file (const std::string_view _journaling_filename);
	virtual void				process_write_complete (const shared_buffer& _buffer);
	virtual	void				process_generate_query (std::size_t _count_completed);
			void				process_complete_wal (IQUERY* _pquery, result_code _result);
			void				process_shrink_file ();

protected:
			class archive_file : public archive::file
			{
			public:
			virtual void		on_write_complete(const shared_buffer& _buffer) override { m_pwal->process_write_complete(_buffer);}
			object_ptr<wal::file<TCHUNK, TQUERIER>>	m_pwal;
			};

			class Cquery : virtual public IQUERY
			{
			public:
			virtual	void		process_execute_query() override;
			virtual	void		process_reset_session() noexcept override;
			public:
			object_ptr<wal::file<TCHUNK,TQUERIER>>	m_pwal;
			object_ptr<IQUERY>	m_pquery;
			};

			sHEADER				m_header;
			std::size_t			m_journaling_max_size = 65536;

			object_ptr<Inotifiable_file<TCHUNK,IQUERY>> m_ptarget;
			OBJ<archive_file>	m_file;

			std::recursive_mutex m_lockable_lock;
			std::size_t			m_pos_requested = 0;
			std::size_t			m_pos_journaled = 0;
			std::size_t			m_pos_completed = 0;

			circular_list<CHUNK> m_queue_chunk_requested;
			std::vector<CHUNK>	m_vector_chunk_journaled;
			std::vector<QUERY>	m_vector_query;

			object_ptr<TQUERIER> m_pquerier;
};

template <class TCHUNK, class TQUERIER>
wal::file<TCHUNK, TQUERIER>::file() noexcept
{
	// 1) header file initialize
	__strcpy(m_header.init_string, "CGCII wal file");
	m_header.key[0] = (static_cast<uint64_t>(std::rand()) << 32) | static_cast<uint64_t>(rand());
	m_header.key[1] = (static_cast<uint64_t>(std::rand()) << 32) | static_cast<uint64_t>(rand());
	m_header.key[2] = (static_cast<uint64_t>(std::rand()) << 32) | static_cast<uint64_t>(rand());
	m_header.key[3] = (static_cast<uint64_t>(std::rand()) << 32) | static_cast<uint64_t>(rand());
	m_header.version_major = 1;
	m_header.version_minor = 0;
	m_header.value[0] = (static_cast<uint64_t>(std::rand()) << 32) | static_cast<uint64_t>(rand());
	m_header.value[1] = (static_cast<uint64_t>(std::rand()) << 32) | static_cast<uint64_t>(rand());
}

template <class TCHUNK, class TQUERIER>
wal::file<TCHUNK, TQUERIER>::~file() noexcept
{
}

template <class TCHUNK, class TQUERIER>
result_code wal::file<TCHUNK, TQUERIER>::start(std::string_view _journaling_filename, std::size_t _max_size)
{
	// declare) 
	context	context_setting;

	context_setting["filename"sv] = _journaling_filename;
	context_setting["max_size"sv] = _max_size;

	return start(context_setting);
}

template <class TCHUNK, class TQUERIER>
result_code wal::file<TCHUNK, TQUERIER>::start(std::wstring_view _journaling_filename, std::size_t _max_size)
{
	// declare) 
	context	context_setting;

	context_setting["filename"sv] = _journaling_filename;
	context_setting["max_size"sv] = _max_size;

	return start(context_setting);
}

template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::Cquery::process_execute_query()
{
	// check) 
	CGASSERT_ERROR(m_pwal.exist());
	CGASSERT_ERROR(m_pquery.exist());

	// 1) move pquery pointer
	object_ptr<file<TCHUNK, TQUERIER>> pwal = std::move(m_pwal);

	//declare)
	result_code	result;

	try
	{
		// 2) set session
		m_pquery->set_session(this->get_session());

		// 3) execute query
		m_pquery->process_execute_query();

		// 4) SUCCESS!
		result = eRESULT::SUCCESS;
	}
	catch (throwable::failure& _e)
	{
		result = _e.reason();
	}
	catch (...)
	{
		result = eRESULT::EXCEPTION;
	}

	// 4) session을 제거한다.
	m_pquery->reset_session();

	// 5) success!!
	pwal->process_complete_wal(m_pquery, result);

	// 6) reset
	m_pquery.reset();
}

template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::Cquery::process_reset_session() noexcept
{
	scoped_lock(this->m_lockable_state_query)
	{
		// 1) reset query pointer
		m_pwal.reset();
		m_pquery.reset();

		// 2) call 
		IQUERY::process_reset_session();
	}
}

template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::request_wal(TCHUNK&& _chunk)
{
	// check)
	THROW_IF(get_object_state() != eOBJECT_STATE::RUNNING, throwable::failure(eRESULT::NOT_READY));

	// check)
	CGASSERT_ERROR(m_pos_requested >= m_pos_completed);

	// 1) get chunk size and pos_end
	std::size_t  size_data = sizeof(uint64_t) + sizeof(uint64_t) + sizeof(uint64_t) + sizeof(uint64_t) + get_size_of(_chunk);
	uint64_t key_a	 = 0;
	uint64_t key_b	 = 0;

	// 2) generate [chunk data]  from _pqeury
	auto temp_buffer = alloc_shared_buffer(size_data);
	temp_buffer.append<uint64_t>(size_data);
	temp_buffer.append<uint64_t>(); // 이것은 lock한 이후에 써넣는다.
	temp_buffer.append<uint64_t>(key_a);
	temp_buffer.append<uint64_t>(key_b);
	temp_buffer.append<TCHUNK>(_chunk);

	// check) 계산된 데이터 크기[size_data]와 저장된 데이터 크기[temp_buffer.size()]가 서로 동일해야 한다.
	CGASSERT_ERROR(size_data == temp_buffer.size());

	scoped_lock(this->m_lockable_lock)
	{
		// check) 
		CGASSERT_ERROR(this->m_pos_requested >= this->m_pos_completed);

		// 3) write [pos] to buffer
		temp_buffer.front<uint64_t>(sizeof(uint64_t)) = this->m_pos_requested - this->m_pos_completed;

		// 4) calculate pos_end
		std::size_t pos_end = this->m_pos_requested + size_data;

		try
		{
			// 3) write [chunk data] to file
			bool result = this->m_file.write(temp_buffer);
	
			// check) throw exception if it fail
			THROW_IF(result == false, throwable::failure(eRESULT::FAIL));

			// 4) queuing chunk_data
			this->m_queue_chunk_requested.push_back(CHUNK{ size_data, pos_end, key_a, key_b, _chunk });

			// 5) increase offset
			this->m_pos_requested += size_data;
		}
		catch (...)
		{
			// - pop한다.
			this->m_queue_chunk_requested.pop_back();
	
			// reraise)
			throw;
		}
	}
}

template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::on_starting(context& /*_context*/)
{
	// trace) Event Manager를 생성한다.
	LOG_PROGRESS << "@ <BEGIN> start WAL file["sv << name() << "]"sv;

	// check)
	CGASSERT_ERROR(m_pquerier.exist());

	// check)
	THROW_IF(m_pquerier.empty(), throwable::failure(eRESULT::NOT_READY));
}
template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::on_start(context& _context)
{
	// 1) filename을 얻는다.
	std::string filename = _context["filename"sv];
	std::size_t max_count = _context["max_size"sv];

	// 1) restore한다.
	process_restore_file(filename);

	// 2) recreate
	process_recreate_file(filename);

	// 3) setting
	this->m_file.m_pwal = this;

	// 4) initialize file
	this->m_file.start({ filename, eFILE_OPERATION::APPEND_ASYNC });

	// 5) 설정하기
	this->m_journaling_max_size = max_count;

	// trace) Event Manager를 생성한다.
	LOG_PROGRESS << "@ <END> start WAL file["sv << name() << "]"sv;
}
template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::on_stopping()
{
	// trace) Event Manager를 생성한다.
	LOG_PROGRESS << "@ <BEGIN> stop WAL file["sv << name() << "]"sv;

	// 1) file에 모두 저장한다.

	// 2) 완료를 기다린다.
	while(this->m_pos_requested > this->m_pos_completed)
	{
		scoped_lock(this->m_lockable_lock)
		{
			if (this->m_pos_requested == this->m_pos_journaled)
			{
				for(; this->m_vector_chunk_journaled.empty() == false; )
				{
					// - 사전에 pos_end와 size값을 읽어 놓는다.
					auto front_size = this->m_vector_chunk_journaled.front().size;
					auto front_pos_end = this->m_vector_chunk_journaled.front().pos_end;
					auto back_pos_end = this->m_vector_chunk_journaled.back().pos_end;

					// declare) 
					QUERY data;

					// - query 객체를 만들어 온다.
					data.pquery = this->m_ptarget->process_wal_query(this->m_vector_chunk_journaled, true);

					// check)
					RETURN_IF(data.pquery.empty());

					// - size와 pos_end값을 계산한다.
					data.pos_end = (this->m_vector_chunk_journaled.empty() == false) ? (this->m_vector_chunk_journaled.front().pos_end - this->m_vector_chunk_journaled.front().size) : back_pos_end;
					data.size = data.pos_end - front_pos_end + front_size;

					// - query 객체를 생성한다.
					auto temp_queue = make_object<Cquery>();

					// - 설정
					temp_queue->m_pwal	 = this;
					temp_queue->m_pquery = data.pquery;

					// - queuing query data
					scoped_lock(this->m_lockable_lock)
					{
						this->m_vector_query.push_back(std::move(data));
					}

					// - post_execute_query
					try
					{
						this->m_pquerier->execute_query(temp_queue);
					}
					catch (...)
					{
						// - rollback
						this->m_vector_query.pop_back();

						// reraise) 
						throw;
					}
				}
			}

			// - wait 
			std::this_thread::sleep_for(1ms);
		}
	}
	
	//// declare) filename을 받아놓는다.
	//std::string	file_name	 = m_file.get_filename();

	// 3) destroy file
	this->m_file.destroy();

	//// 4) file을 지운다.
	//std::remove(file_name.c_str());

	// 5) setting
	this->m_file.m_pwal.reset();

	// 6) ...
	scoped_lock(this->m_lockable_lock)
	{
		this->m_queue_chunk_requested.clear();
		this->m_vector_chunk_journaled.clear();
		this->m_ptarget.reset();
	}
}
template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::on_stop()
{
	// trace) Event Manager를 생성한다.
	LOG_PROGRESS << "@ <END> stop WAL file["sv << name() << "]"sv;
}

template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::process_restore_file(const std::string_view _journaling_filename)
{
	// 1) 파일을 연다.
	auto file_handle = api::file::open(_journaling_filename, eFILE_OPERATION::READ);

	// check) return if file do not exsit
	RETURN_IF(file_handle == INVALID_FILE_HANDLE);

	// 2) file header부분을 읽어들인다.
	{
		// declare) 
		sHEADER	temp_head;

		// - record head를 읽는다.
		auto result = api::file::read(file_handle, sizeof(sHEADER), &temp_head);

		// check) 읽기 실패하면 여기서 끝낸다.
		THROW_IF(result != sizeof(sHEADER), throwable::failure(eRESULT::FAIL), LOG_ERROR << "(err ) can't read file header ("sv << name() << ")"sv);

		// - 제대로된 파일인지 확인한다.
	}
	
	// declare)
	std::size_t	pos_now	 = sizeof(sHEADER);
	std::size_t	pos_last = sizeof(sHEADER);

	// 3) 복원 정보 시작 위치를 결정한다.
	for (;;)
	{
		// declare) 
		std::size_t chunk_head[4];

		// - record head를 읽는다.
		auto result = api::file::read(file_handle, sizeof(uint64_t) * 4, chunk_head);

		// check) 읽기 실패하면 여기서 끝낸다.
		BREAK_IF(result != sizeof(uint64_t) * 4);

		// - length을 더한다.
		pos_last = pos_now - chunk_head[1];
		pos_now += chunk_head[0];
			   		 	  
		// - 마지막 record의 위치로 파일포인터를 옮긴다.
		api::file::seek(file_handle, pos_now);
	}

	// 3) 읽을 위치로 file_pointer를 옮긴다.
	api::file::seek(file_handle, pos_last);

	// 4) chunk를 읽어들인다.
	for (;;)
	{
		// declare) 
		std::size_t chunk_head[4];

		// - record head를 읽는다.
		auto result = api::file::read(file_handle, sizeof(uint64_t) * 4, chunk_head);

		// check)
		BREAK_IF(result < (sizeof(uint64_t) * 4));

		// - size pquery
		std::size_t size_chunk = chunk_head[0] - (sizeof(uint64_t) * 4);

		// declare) 
		auto temp_buffer = alloc_shared_buffer(size_chunk);

		// - length을 설정한다.
		temp_buffer.set_size(size_chunk);

		// - 데이터를 읽어들인다.
		result = api::file::read(file_handle, size_chunk, temp_buffer.data());

		// check)
		BREAK_IF(result < size_chunk);

		// declare)
		auto data = temp_buffer.extract<TCHUNK>();

		// - request restore query
		this->m_ptarget->process_wal_restore(&data);
	}

	// 5) close file
	api::file::close(file_handle);
}

template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::process_recreate_file(const std::string_view _journaling_filename)
{
	// check)
	CGASSERT_ERROR(_journaling_filename.empty() == false);

	// check)
	CGASSERT_ERROR(this->m_pquerier.empty() == false);

	// 1) wal file을 다시 리셋한다.(크기 0으로)
	auto file_handle = api::file::open(_journaling_filename, eFILE_OPERATION::WRITE);

	// 2) file head를 써넣는다.
	auto result = api::file::write(file_handle, sizeof(sHEADER), &m_header);

	// check)
	CGASSERT_ERROR(result == sizeof(sHEADER));

	// check)
	THROW_IF(result != sizeof(sHEADER), throwable::failure(eRESULT::FAIL));

	// 3) 값을 초기화한다.
	this->m_pos_requested = sizeof(sHEADER);
	this->m_pos_journaled = sizeof(sHEADER);
	this->m_pos_completed = sizeof(sHEADER);

	// 4) 파일을 닫는다.
	api::file::close(file_handle);
}

template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::process_write_complete(const shared_buffer& _buffer)
{
	// check) _buffer.size()이 0이면 안됀다.
	CGASSERT_ERROR(_buffer.size() != 0);

	// declare) 
	std::size_t count_inserted  = 0;

	scoped_lock(this->m_lockable_lock)
	{
		// declare) 
		std::size_t remained_bytes = _buffer.size();

		// check) 
		CGASSERT_ERROR(this->m_queue_chunk_requested.empty() == false);

		// 1) queueing된 것이 있을 경우에만 
		while(this->m_queue_chunk_requested.empty() == false)
		{
			// - ...
			auto& iter = this->m_queue_chunk_requested.front();

			// check) transaction 하나의 크기보다 크면 안됀다.
			BREAK_IF(iter.size > remained_bytes);

			// - 길이 줄이기
			remained_bytes	-= iter.size;
			this->m_pos_journaled += iter.size;

			// check)
			CGASSERT_ERROR(m_pos_requested >= m_pos_journaled)

			// - journaled된 객체 저장소로 이동시킨다.
			this->m_vector_chunk_journaled.push_back(std::move(iter));
			this->m_queue_chunk_requested.pop_front();

			// - add
			++count_inserted;
		}
	}

	// check) 하나도 없으면 그냥 끝낸다.
	RETURN_IF(count_inserted == 0);

	// 2) wal이 처리된 데이터의 journaling이 완료되었음을 통보한다.
	if (this->m_ptarget.exist())
	{
		auto iter_end = this->m_vector_chunk_journaled.end();
		auto iter = iter_end - count_inserted;

		for (; iter != iter_end; ++iter)
		{
			try
			{
				this->m_ptarget->process_wal_appended(&(*iter).data);
			}
			catch (...)
			{

			}
		}
	}

	// 3) process_generate_query
	this->process_generate_query(count_inserted);

	// 4) 파일크기를 resize한다.
	if (this->m_pos_journaled > this->m_journaling_max_size)
	{
		this->process_shrink_file();
	}
}

template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::process_complete_wal(IQUERY* _pquery, result_code _result)
{
	// check) result가 SUCCESS가 아닐 경우 재시도를 한다.
	if (_result != eRESULT::SUCCESS)
	{
		//// - query 객체를 생성한다.
		//auto	temp_queue	 = make_object<Cquery>();

		//// - 설정
		//temp_queue->m_pwal	 = this;
		//temp_queue->m_pquery = _pquery;

		//// - post_execute_query (retry)
		//try
		//{
		//	m_pquerier->post_execute_query(temp_queue);
		//}
		//catch (...)
		//{
		//}

		//// return)
		//return;
	}
	
	scoped_lock(this->m_lockable_lock)
	{
		// check) 
		CGASSERT_ERROR(this->m_vector_query.empty() == false);

		// check)
		RETURN_IF(this->m_vector_query.empty());

		// 1) find _pquery
		auto iter = this->m_vector_query.begin();
		auto iter_end = this->m_vector_query.end();

		for (; iter != iter_end; ++iter)
		{
			BREAK_IF(iter->pquery == _pquery);
		}

		// check) it must exist
		CGASSERT_ERROR(iter != iter_end);

		// check) 
		RETURN_IF(iter == iter_end);

		// check) 
		CGASSERT_ERROR(this->m_pos_journaled >= this->m_pos_completed)

		// 2) temp_pos_end
		auto temp_pos_end = (*iter).pos_end;

		// 3) erase _pquery
		this->m_vector_query.erase(iter);

		// 4) set 'm_pos_completed'
		this->m_pos_completed	= (this->m_vector_query.empty() == false) ? this->m_vector_query.front().pos_end : temp_pos_end;
	}
}

template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::process_generate_query(std::size_t /*_count_completed*/)
{
	for(; this->m_vector_chunk_journaled.empty() == false; )
	{
		// 1) 사전에 pos_end와 size값을 읽어 놓는다.
		auto front_size = this->m_vector_chunk_journaled.front().size;
		auto front_pos_end = this->m_vector_chunk_journaled.front().pos_end;
		auto back_pos_end = this->m_vector_chunk_journaled.back().pos_end;

		// declare) 
		sQUERY<IQUERY> data;

		// 2) query 객체를 만들어 온다.
		data.pquery = this->m_ptarget->process_wal_query(this->m_vector_chunk_journaled);

		// check)
		RETURN_IF(data.pquery.empty());

		// 3) size와 pos_end값을 계산한다.
		data.pos_end = (m_vector_chunk_journaled.empty() == false) ? (this->m_vector_chunk_journaled.front().pos_end - this->m_vector_chunk_journaled.front().size) : back_pos_end;
		data.size = data.pos_end - front_pos_end + front_size;

		// 4) query 객체를 생성한다.
		auto temp_queue	= make_object<Cquery>();

		// 5) 설정
		temp_queue->m_pwal = this;
		temp_queue->m_pquery = data.pquery;

		// 6) queuing query data
		scoped_lock(this->m_lockable_lock)
		{
			this->m_vector_query.push_back(std::move(data));
		}

		// 7) post_execute_query
		try
		{
			this->m_pquerier->post_execute_query(temp_queue);
		}
		catch (...)
		{
			// - rollback
			this->m_vector_query.pop_back();

			// reraise) 
			throw;
		}
	}
}

template <class TCHUNK, class TQUERIER>
void wal::file<TCHUNK, TQUERIER>::process_shrink_file()
{
	// 1) 마지막 file_pos를 얻는다.
	auto pos_last = this->m_pos_journaled - this->m_pos_completed;

	// declare) 
	shared_buffer temp_buffer;

	// 2) 복사할 길이를 구한다.
	auto size_copy = pos_last;

	// check) 복사를 시작할 위치가 현재 위치보다는 작거나 같아야 한다.
	CGASSERT_ERROR(this->m_file.get_position() >= pos_last);

	// check) 복사할 크기가 파일크기보다 클 수는 없다.
	CGASSERT_ERROR(size_copy <= this->m_file.get_file_length());

	// check) 그냥 통채로 copy해야하면 진행하지 않는다
	RETURN_IF(size_copy + sizeof(sHEADER) == this->m_file.get_file_length());

	// 3) 기존 파일을 먼저 닫는다.
	api::file::close(this->m_file.get_file_handle());

	// 4) 복사할 남은 부분을 읽어 놓는다.
	if(size_copy != 0)
	{
		// - 복사할 크기 만큼의 shared_buffer를 할당한다.
		temp_buffer = alloc_shared_buffer(size_copy);

		{
			// - 파일을 읽기용으로 연다.
			auto file_handle = api::file::open(this->m_file.get_filename(), eFILE_OPERATION::READ);

			// - 파일을 읽는다.
			auto pos_seek = api::file::seek(file_handle, this->m_file.get_position() - pos_last);

			// check)
			CGASSERT_ERROR(pos_seek == (this->m_file.get_position() - pos_last));

			// check) 
			THROW_IF(pos_seek != (this->m_file.get_position() - pos_last), throwable::failure(eRESULT::FAIL))

			// - 읽어 들인다.
			auto size_read = api::file::read(file_handle, size_copy, temp_buffer.data());

			// check)
			CGASSERT_ERROR(size_copy == size_read);

			// check) 
			THROW_IF(size_copy != size_read, throwable::failure(eRESULT::FAIL))

			// - 파일을 다시 닫는다.
			api::file::close(file_handle);
		}
	}

	// 5) 기존파일의 크기를 0으로 만들고 남은 데이터를 복사해 넣는다.
	{
		// - 파일을 새로 생성한다.
		auto file_handle = api::file::open(this->m_file.get_filename(), eFILE_OPERATION::WRITE);

		// - header를 써넣는다.
		auto size_header = api::file::write(file_handle, sizeof(sHEADER), &this->m_header);

		// check) header size compare
		CGASSERT_ERROR(size_header == sizeof(sHEADER))

		// check) 
		THROW_IF(size_header != sizeof(sHEADER), throwable::failure(eRESULT::FAIL))

		// - write remained
		if(size_copy != 0)
		{
			auto size_write = api::file::write(file_handle, size_copy, temp_buffer.data());

			// check)
			CGASSERT_ERROR(size_copy == size_write);

			// check) 
			THROW_IF(size_copy != size_write, throwable::failure(eRESULT::FAIL))
		}

		// - 파일을 다시 닫는다.
		api::file::close(file_handle);
	}

	// 6) 새로운 wal 파일을 연다.
	{
		// - file을 open한다.
		auto file_handle = api::file::open(this->m_file.get_filename(), eFILE_OPERATION::APPEND_ASYNC);

		// - setting...
		this->m_file.set_file_handle(file_handle);
		this->m_file.set_file_length(sizeof(sHEADER) + size_copy);
		this->m_file.set_position(sizeof(sHEADER) + size_copy);
	}
}



}