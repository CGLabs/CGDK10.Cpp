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
//-----------------------------------------------------------------------------
template <class TQUERY>
class wal::querier : 
// inherited classes)
	public						object::Nnameable,
	public						object::Ninitializable_startable
{
// defintion) 
public:
	typedef	typename TQUERY::IQUERY		IQUERY;
	typedef	typename TQUERY::QUERIER	QUERIER;
	typedef	sCHUNK<object_ptr<TQUERY>>	CHUNK;
	typedef	sQUERY<TQUERY>				QUERY;

// contructor/destructor)
public:
			querier() noexcept;
			~querier() noexcept;

// public)
public:
			result_code			start (const context& _context) { return Nstartable::start(_context);}
	virtual	result_code			start (context& _context) override { return Nstartable::start(_context);}
			result_code			start (const std::string_view _journaling_filename, std::size_t _max_size = 65536);

			void				set_target (Inotifiable<TQUERY>* _ptarget) noexcept { m_ptarget=_ptarget; }
	[[nodiscard]] auto			get_target () const noexcept { return m_ptarget; }

			void				set_querier (QUERIER* _pquerier) noexcept { m_pquerier =_pquerier; }
	[[nodiscard]] auto			get_querier () const noexcept { return m_pquerier; }

			void				execute_query (TQUERY* _pquery);

// framework)
private:
	// - start/Stop
	virtual	void				on_starting (context& _context) override;
	virtual	void				on_start (context& _context) override;
	virtual	void				on_stopping () override;
	virtual	void				on_stop () override;

// implementation) 
protected:
			class archive_file : public archive::file
			{
			public:
			virtual void		on_write_complete(const shared_buffer& _buffer) override { m_pwal->process_write_complete(_buffer);}
			object_ptr<querier<TQUERY>>	m_pwal;
			};

			class Cquery : virtual public IQUERY
			{
			public:
			virtual	void		process_execute_query() override;
			virtual	void		process_reset_session() noexcept override;
			public:
			object_ptr<querier<TQUERY>>	m_pwal;
			object_ptr<TQUERY>	m_pquery;
			};

			void				process_restore_file (const std::string_view _journaling_filename);
			void				process_recreate_file (const std::string_view _journaling_filename);
	virtual void				process_write_complete (const shared_buffer& _buffer);
	virtual	void				process_generate_query (std::size_t _count_completed);
			void				process_complete_wal (TQUERY* _pquery, result_code _result);
			void				process_shrink_file ();

protected:
			sHEADER				m_header;
			std::size_t			m_journaling_max_size = 65536;

			object_ptr<Inotifiable<TQUERY>> m_ptarget;
			OBJ<archive_file>	m_file;

			std::recursive_mutex m_lockable_lock;
			std::size_t			m_pos_requested = 0;
			std::size_t			m_pos_journaled = 0;
			std::size_t			m_pos_completed = 0;

			circular_list<CHUNK> m_queue_chunk_requested;
			std::vector<CHUNK>	m_vector_chunk_journaled;
			std::vector<QUERY>	m_vector_query;

			object_ptr<QUERIER> m_pquerier;
};

template <class TQUERY>
wal::querier<TQUERY>::querier() noexcept
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

template <class TQUERY>
wal::querier<TQUERY>::~querier() noexcept
{
}

template <class TQUERY>
result_code wal::querier<TQUERY>::start(const std::string_view _journaling_filename, std::size_t _max_size)
{
	// declare)
	context context_setting;

	context_setting["filename"sv] = static_cast<std::string_view>(_journaling_filename);
	context_setting["max_size"sv] = _max_size;

	return start(context_setting);
}

template <class TQUERY>
void wal::querier<TQUERY>::Cquery::process_execute_query()
{
	// check)
	CGASSERT_ERROR(m_pwal.exist());
	CGASSERT_ERROR(m_pquery.exist());

	// 1) move pquery pointer
	object_ptr<querier<TQUERY>>	pwal = std::move(m_pwal);

	// declare)
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

	// 4) session�� �����Ѵ�.
	m_pquery->reset_session();

	// 5) success!!
	pwal->process_complete_wal(m_pquery, result);

	// 6) reset
	m_pquery.reset();
}

template <class TQUERY>
void wal::querier<TQUERY>::Cquery::process_reset_session() noexcept
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

template <class TQUERY>
void wal::querier<TQUERY>::execute_query(TQUERY* _pquery)
{
	// check)
	CGASSERT_ERROR(m_pos_requested >= m_pos_completed);

	// 1) get chunk size and pos_end
	std::size_t size_data = sizeof(uint64_t) + sizeof(uint64_t) + sizeof(uint64_t) + sizeof(uint64_t) + get_size_of(*_pquery);
	uint64_t key_a = 0;
	uint64_t key_b = 0;

	// 2) generate [chunk data]  from _pqeury
	auto temp_buffer = alloc_shared_buffer(size_data);
	temp_buffer.append<uint64_t>(size_data);
	temp_buffer.append<uint64_t>(); // �̰��� lock�� ���Ŀ� ��ִ´�.
	temp_buffer.append<uint64_t>(key_a);
	temp_buffer.append<uint64_t>(key_b);
	temp_buffer.append<TQUERY>(*_pquery);

	// check) 
	CGASSERT_ERROR(size_data == temp_buffer.size());

	scoped_lock(m_lockable_lock)
	{
		// check) 
		CGASSERT_ERROR(m_pos_requested >= m_pos_completed);

		// 3) write [pos] to shared_buffer
		temp_buffer.front<uint64_t>(sizeof(uint64_t)) = m_pos_requested - m_pos_completed;

		std::size_t pos_end = m_pos_requested + size_data;

		try
		{
			// 3) write [chunk data] to file
			bool result = m_file.write(temp_buffer);
	
			// check) throw exception if it fail
			THROW_IF(result == false, throwable::failure(eRESULT::FAIL));
	
			// 4) queuing chunk_data
			m_queue_chunk_requested.push_back(CHUNK{ size_data, pos_end, key_a, key_b, _pquery });

			// 5) increase offset
			m_pos_requested += size_data;
		}
		catch (...)
		{
			// - pop�Ѵ�.
			m_queue_chunk_requested.pop_back();
	
			// reraise)
			throw;
		}
	}
}

template <class TQUERY>
void wal::querier<TQUERY>::on_starting(context& /*_context*/)
{
	// trace) Event Manager�� �����Ѵ�.
	LOG_PROGRESS << "@ <BEGIN> start WAL QUERIER["sv << name() << "]"sv;

	// check)
	CGASSERT_ERROR(m_pquerier.exist());

	// check)
	THROW_IF(m_pquerier.empty(), throwable::failure(eRESULT::NOT_READY));
}
template <class TQUERY>
void wal::querier<TQUERY>::on_start(context& _context)
{
	// 1) filename�� ��´�.
	std::string filename = _context["filename"sv];
	std::size_t max_count = _context.find("max_size"sv, "max size"sv);

	// 1) restore�Ѵ�.
	process_restore_file(filename);

	// 2) recreate
	process_recreate_file(filename);

	// 3) setting
	m_file.m_pwal = this;

	// 4) initialize file
	m_file.start({ filename, eFILE_OPERATION::APPEND_ASYNC });

	// 5) �����ϱ�
	m_journaling_max_size = max_count;

	// trace) Event Manager�� �����Ѵ�.
	LOG_PROGRESS << "@ <END> start WAL QUERIER["sv << name() << "]"sv;
}
template <class TQUERY>
void wal::querier<TQUERY>::on_stopping()
{
	// trace) Event Manager�� �����Ѵ�.
	LOG_PROGRESS << "@ <BEGIN> stop WAL QUERIER["sv << name() << "]"sv;

	// 1) destroy file
	m_file.destroy();

	// 2) setting
	m_file.m_pwal.reset();

	// 3) ...
	scoped_lock(m_lockable_lock)
	{
		m_queue_chunk_requested.clear();
		m_vector_chunk_journaled.clear();
		m_ptarget.reset();
	}
}
template <class TQUERY>
void wal::querier<TQUERY>::on_stop()
{
	// trace) Event Manager�� �����Ѵ�.
	LOG_PROGRESS << "@ <END> stop WAL QUERIER["sv << name() << "]"sv;
}

template <class TQUERY>
void wal::querier<TQUERY>::process_restore_file(const std::string_view _journaling_filename)
{
	// 1) ������ ����.
	auto file_handle = api::file::open(_journaling_filename, eFILE_OPERATION::READ);

	// check) return if file do not exsit
	RETURN_IF(file_handle == INVALID_FILE_HANDLE);

	// 2) read CGCII wal file header
	{
		// declare) 
		sHEADER	temp_head;

		// - read header
		auto result = api::file::read(file_handle, sizeof(sHEADER), &temp_head);

		// check) throw exception if failed
		THROW_IF(result != sizeof(sHEADER), throwable::failure(eRESULT::FAIL), LOG_ERROR << "(err ) can't read file header ("sv << name() << ")"sv);

		// - check file header
	}
	
	// declare)
	std::size_t pos_now	 = sizeof(sHEADER);
	std::size_t pos_last = sizeof(sHEADER);

	// 3) ���� ���� ���� ��ġ�� �����Ѵ�.
	for (;;)
	{
		// declare) 
		std::size_t chunk_head[4];

		// - record head�� �д´�.
		auto result = api::file::read(file_handle, sizeof(uint64_t) * 4, chunk_head);

		// check) �б� �����ϸ� ���⼭ ������.
		BREAK_IF(result != sizeof(uint64_t) * 4);

		// - length�� ���Ѵ�.
		pos_last = pos_now - chunk_head[1];
		pos_now	+= chunk_head[0];
			   		 	  
		// - ������ record�� ��ġ�� ���������͸� �ű��.
		api::file::seek(file_handle, pos_now);
	}

	// 3) ���� ��ġ�� file_pointer�� �ű��.
	api::file::seek(file_handle, pos_last);

	// 4) chunk�� �о���δ�.
	for (;;)
	{
		// declare) 
		std::size_t chunk_head[4];

		// - record head�� �д´�.
		auto result = api::file::read(file_handle, sizeof(uint64_t) * 4, chunk_head);

		// check)
		BREAK_IF(result < (sizeof(uint64_t) * 4));

		// - size pquery
		std::size_t size_chunk = chunk_head[0] - (sizeof(uint64_t) * 4);

		// declare) 
		shared_buffer temp_buffer = alloc_shared_buffer(size_chunk);

		// - length�� �����Ѵ�.
		temp_buffer.set_size(size_chunk);

		// - �����͸� �о���δ�.
		result = api::file::read(file_handle, size_chunk, temp_buffer.data());

		// check)
		BREAK_IF(result < size_chunk);

		// declare)
		auto pquery = temp_buffer.extract<object_ptr<TQUERY>>();

		// - request restore query
		m_ptarget->process_wal_restore(pquery);

		// - request restore query
		m_pquerier->execute_query(pquery);
	}

	// 5) close file
	api::file::close(file_handle);
}

template <class TQUERY>
void wal::querier<TQUERY>::process_recreate_file(const std::string_view _journaling_filename)
{
	// check)
	CGASSERT_ERROR(_journaling_filename.empty() == false);

	// check)
	CGASSERT_ERROR(m_pquerier.empty() == false);

	// 1) wal file�� �ٽ� �����Ѵ�.(ũ�� 0����)
	auto file_handle = api::file::open(_journaling_filename, eFILE_OPERATION::WRITE);

	// 2) file head�� ��ִ´�.
	auto result = api::file::write(file_handle, sizeof(sHEADER), &m_header);

	// check)
	CGASSERT_ERROR(result == sizeof(sHEADER));

	// check)
	THROW_IF(result != sizeof(sHEADER), throwable::failure(eRESULT::FAIL));

	// 3) ���� �ʱ�ȭ�Ѵ�.
	m_pos_requested	+= sizeof(sHEADER);
	m_pos_journaled += sizeof(sHEADER);
	m_pos_completed += sizeof(sHEADER);

	// 4) ������ �ݴ´�.
	api::file::close(file_handle);
}

template <class TQUERY>
void wal::querier<TQUERY>::process_write_complete(const shared_buffer& _buffer)
{
	// check) _buffer.size_�� 0�̸� �ȉ´�.
	CGASSERT_ERROR(_buffer.size() != 0);

	//declare)
	int	count_completed = 0;

	scoped_lock(m_lockable_lock)
	{
		// declare) 
		std::size_t remained_bytes = _buffer.size();

		// check) 
		CGASSERT_ERROR(m_queue_chunk_requested.empty() == false);

		// 1) queueing�� ���� ���� ��쿡�� 
		while(m_queue_chunk_requested.empty() == false)
		{
			// - ...
			auto& iter = m_queue_chunk_requested.front();

			// check) transaction �ϳ��� ũ�⺸�� ũ�� �ȉ´�.
			BREAK_IF(iter.size > remained_bytes);

			// - ���� ���̱�
			remained_bytes -= iter.size;
			m_pos_journaled += iter.size;

			// check)
			CGASSERT_ERROR(m_pos_requested >= m_pos_journaled)

			// - journaled�� ��ü ����ҷ� �̵���Ų��.
			m_vector_chunk_journaled.push_back(std::move(iter));
			m_queue_chunk_requested.pop_front();

			// - .
			++count_completed;
		}
	}

	// check) �ϳ��� ������ �׳� ������.
	RETURN_IF(count_completed == 0);

	// 2) wal�� ó���� �������� journaling�� �Ϸ�Ǿ����� �뺸�Ѵ�.
	if (m_ptarget.exist())
	{
		auto iter_end = m_vector_chunk_journaled.end();
		auto iter = iter_end - count_completed;

		for (; iter != iter_end; ++iter)
		{
			try
			{
				m_ptarget->process_wal_appended((*iter).data);
			}
			catch (...)
			{

			}
		}
	}

	// 3) process_generate_query
	process_generate_query(count_completed);

	// 4) ����ũ�⸦ resize�Ѵ�.
	if (m_pos_journaled > m_journaling_max_size)
	{
		process_shrink_file();
	}
}

template <class TQUERY>
void wal::querier<TQUERY>::process_complete_wal(TQUERY* _pquery, result_code /*_result*/)
{
	scoped_lock(m_lockable_lock)
	{
		// check) 
		CGASSERT_ERROR(m_vector_query.empty() == false);

		// check)
		RETURN_IF(m_vector_query.empty());

		// 1) find _pquery
		auto iter = m_vector_query.begin();
		auto iter_end = m_vector_query.end();

		for (; iter != iter_end; ++iter)
		{
			BREAK_IF(iter->pquery == _pquery);
		}

		// check) it must exist
		CGASSERT_ERROR(iter != iter_end);

		// check) 
		RETURN_IF(iter == iter_end);

		// check) 
		CGASSERT_ERROR(m_pos_journaled >= m_pos_completed)

		// 2) temp_pos_end
		auto temp_pos_end = (*iter).pos_end;

		// 3) erase _pquery
		m_vector_query.erase(iter);

		// 4) set 'm_pos_completed'
		m_pos_completed	= (m_vector_query.empty() == false) ? m_vector_query.front().pos_end : temp_pos_end;
	}
}

template <class TQUERY>
void wal::querier<TQUERY>::process_generate_query(std::size_t /*_count_completed*/)
{
	for(; m_vector_chunk_journaled.empty() == false; )
	{
		// 1) ������ pos_end�� size���� �о� ���´�.
		auto front_size = m_vector_chunk_journaled.front().size;
		auto front_pos_end = m_vector_chunk_journaled.front().pos_end;
		auto back_pos_end  = m_vector_chunk_journaled.back().pos_end;

		// declare) 
		QUERY data;

		// 2) query ��ü�� ����� �´�.
		data.pquery = m_vector_chunk_journaled.front().data;
		m_vector_chunk_journaled.erase(m_vector_chunk_journaled.begin());

		// check)
		RETURN_IF(data.pquery.empty());

		// 3) size�� pos_end���� ����Ѵ�.
		data.pos_end = (m_vector_chunk_journaled.empty() == false) ? (m_vector_chunk_journaled.front().pos_end - m_vector_chunk_journaled.front().size) : back_pos_end;
		data.size = data.pos_end - front_pos_end + front_size;

		// 4) query ��ü�� �����Ѵ�.
		auto temp_queue = make_object<Cquery>();

		// 5) ����
		temp_queue->m_pwal = this;
		temp_queue->m_pquery = data.pquery;

		// 6) queuing query data
		scoped_lock(m_lockable_lock)
		{
			m_vector_query.push_back(std::move(data));
		}

		// 7) post_execute_query
		try
		{
			m_pquerier->post_execute_query(temp_queue);
		}
		catch (...)
		{
			// - rollback
			m_vector_query.pop_back();

			// reraise) 
			throw;
		}
	}
}


template <class TQUERY>
void wal::querier<TQUERY>::process_shrink_file()
{
	// 1) ������ file_pos�� ��´�.
	auto pos_last = m_pos_journaled - m_pos_completed;

	// declare) 
	shared_buffer temp_buffer;

	// 2) ������ ���̸� ���Ѵ�.
	auto size_copy = pos_last;

	// check) ���縦 ������ ��ġ�� ���� ��ġ���ٴ� �۰ų� ���ƾ� �Ѵ�.
	CGASSERT_ERROR(m_file.get_position() >= pos_last);

	// check) ������ ũ�Ⱑ ����ũ�⺸�� Ŭ ���� ����.
	CGASSERT_ERROR(size_copy <= m_file.get_file_length());

	// check) �׳� ��ä�� copy�ؾ��ϸ� �������� �ʴ´�
	RETURN_IF(size_copy + sizeof(sHEADER) == m_file.get_file_length());

	// 3) ���� ������ ���� �ݴ´�.
	api::file::close(m_file.get_file_handle());

	// 4) ������ ���� �κ��� �о� ���´�.
	if(size_copy != 0)
	{
		// - ������ ũ�� ��ŭ�� shared_buffer�� �Ҵ��Ѵ�.
		temp_buffer	= alloc_shared_buffer(size_copy);

		{
			// - ������ �б������ ����.
			auto file_handle = api::file::open(m_file.get_filename(), eFILE_OPERATION::READ);

			// - ������ �д´�.
			auto pos_seek = api::file::seek(file_handle, m_file.get_position() - pos_last);

			// check)
			CGASSERT_ERROR(pos_seek == (m_file.get_position() - pos_last));

			// check) 
			THROW_IF(pos_seek != (m_file.get_position() - pos_last), throwable::failure(eRESULT::FAIL))

			// - �о� ���δ�.
			auto size_read = api::file::read(file_handle, size_copy, temp_buffer.data());

			// check)
			CGASSERT_ERROR(size_copy == size_read);

			// check) 
			THROW_IF(size_copy != size_read, throwable::failure(eRESULT::FAIL))

			// - ������ �ٽ� �ݴ´�.
			api::file::close(file_handle);
		}
	}

	// 5) ���������� ũ�⸦ 0���� ����� ���� �����͸� ������ �ִ´�.
	{
		// - ������ ���� �����Ѵ�.
		auto file_handle = api::file::open(m_file.get_filename(), eFILE_OPERATION::WRITE);

		// - header�� ��ִ´�.
		auto size_header = api::file::write(file_handle, sizeof(sHEADER), &m_header);

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

		// - ������ �ٽ� �ݴ´�.
		api::file::close(file_handle);
	}

	// 6) ���ο� wal ������ ����.
	{
		// - file�� open�Ѵ�.
		auto file_handle = api::file::open(m_file.get_filename(), eFILE_OPERATION::APPEND_ASYNC);

		// - setting...
		m_file.set_file_handle(file_handle);
		m_file.set_file_length(sizeof(sHEADER) + size_copy);
		m_file.set_position(sizeof(sHEADER) + size_copy);
	}
}



}