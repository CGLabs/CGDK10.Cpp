//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                             Archive Classes                               *
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
// archive::file
//
//  eFILE_OPERATION
//	 - eFILE_OPERATION::READ_ASYNC
//	 - eFILE_OPERATION::READ
//	 - eFILE_OPERATION::READ_ASYNC
//	 - eFILE_OPERATION::READ
//
//-----------------------------------------------------------------------------
#define	MAX_LENGTH_OF_FILENAME	1024

class archive::file :
// Inherited Classes)
	public						object::Ninitializable_startable,
	public						object::Nnameable,
	virtual public				Iarchive,
	virtual public				Iexecutable
{
// constructor/destructor)
public:
			file() noexcept {};
			file(std::string_view _name) : object::Nnameable(_name) {};
	virtual ~file() noexcept {};

// public)
public:
			struct START_PARAMETER
			{
				std::string_view filename;
				eFILE_OPERATION file_operation = eFILE_OPERATION::NONE;
				eFILE_LOCATION	file_location = eFILE_LOCATION::DEFAULT;
				bool			is_create_new = false;
				bool			is_instant_open = false;
			};

// public)
public:
			result_code			start() { context _context; return this->start(_context);}
			result_code			start(const START_PARAMETER& _parameter) { return this->start(context{ buffer_view((char*)&_parameter, sizeof(START_PARAMETER)) }); }
			result_code			start(START_PARAMETER&& _parameter) { return this->start(context{ buffer_view((char*)&_parameter, sizeof(START_PARAMETER)) }); }
			result_code			start(const context& _context) { context context_copy(_context); return this->start(context_copy);}
	virtual	result_code			start(context& _context) override { return this->object::Nstartable::start(_context); }
			
	[[nodiscard]] virtual uint32_t get_status() const override { return this->m_status;}
	virtual	uint32_t			set_status(uint32_t _status) override;
			void				set_location(eFILE_LOCATION _file_location) noexcept { this->m_file_location = _file_location; }
	[[nodiscard]] eFILE_LOCATION get_location() const noexcept { return this->m_file_location; }
	[[nodiscard]] std::string_view get_filename() const noexcept { return this->m_file_name;}
	[[nodiscard]] FILE_HANDLE	get_file_handle() const noexcept { return this->m_handle_file;}
			void				set_file_handle(FILE_HANDLE _file_handle) noexcept { this->m_handle_file=_file_handle;}

#if defined(_WIN32)
	virtual size_t				size() const noexcept override { return this->get_file_length();};
	[[nodiscard]] size_t		get_file_length() const noexcept { return this->m_file_length;}
			void				set_file_length(size_t _file_length) noexcept { this->m_file_length =_file_length;}
	[[nodiscard]] size_t		get_position() const noexcept { return ((uint64_t)Pointer); }
			void				set_position(size_t _position) const noexcept { ((uint64_t&)Pointer)=_position; }
#else
	virtual size_t				size() const noexcept override { return api::file::get_length(this->m_handle_file);;}
#endif


// frameworks) 
private:
	// 1) initialize/Destry
	virtual	void				on_initializing(context& /*_context*/) override {}
	virtual	void				on_initialize(context& /*_context*/) override {}
	virtual	void				on_destroying() noexcept override {}
	virtual	void				on_destroy() noexcept override {}

	// 2) start/stop
	virtual	void				on_starting(context& /*_context*/) override {}
	virtual	void				on_start(context& /*_context*/) override {}
	virtual	void				on_stopping() noexcept override {}
	virtual	void				on_stop() noexcept override {}

	virtual void				on_read_complete(const shared_buffer& /*_buffer*/) {}
	virtual void				on_write_complete(const shared_buffer& /*_buffer*/) {}

// implementation) 
protected:
	// 3) initialize/destroy
	virtual result_code			_process_initializing(context& _context) override;
	virtual result_code			_process_initialize(context& _context) override;
	virtual result_code			_process_destroying() noexcept override;
	virtual result_code			_process_destroy() noexcept override;

	// 4) start/stop
	virtual result_code			_process_starting(context& _context) override;
	virtual result_code			_process_start(context& _context) override;
	virtual result_code			_process_stopping() noexcept override;
	virtual result_code			_process_stop() noexcept override;

	// 5) ProcessRead/ProcessWrite
	virtual bool				process_read(shared_buffer& _buffer) override;
	virtual bool				process_write(shared_buffer& _buffer) override;

			bool				process_read_sync(shared_buffer& _buffer);
			bool				process_write_sync(shared_buffer& _buffer);

			bool				process_read_async(shared_buffer& _buffer);
			bool				process_write_async(shared_buffer& _buffer);

#if defined(_WIN32)
			size_t				request_process_write_async(shared_buffer _buf_write);
#endif
	virtual	intptr_t			process_execute(intptr_t _return, size_t _param) override;

			void				_file_open(std::string_view _filename, eFILE_OPERATION _file_operation, eFILE_LOCATION	_file_location, bool _create_new, bool _instant_open);
			void				_file_close();

protected:
	// 2) Filehandle
			FILE_HANDLE			m_handle_file = INVALID_FILE_HANDLE;

	// 3) filename
			std::string			m_file_name;

	// 4) Status(Read or write)
			eFILE_OPERATION		m_file_operation = eFILE_OPERATION::NONE;
			uint32_t			m_status = 0;

	// 5) Option
			eFILE_LOCATION		m_file_location = eFILE_LOCATION::DEFAULT;
			bool				m_instant_open = false;

	// 6) For write
			lockable<>			m_lockable_buffer;
			bool				m_is_write = false;
			std::list<shared_buffer> m_list_buffer_queuing;
			shared_buffer		m_buffer_sended;
		#if defined(_WIN32)
			size_t				m_file_length = 0;
		#elif defined(__linux__) || defined(__ANDROID__)
			std::list<shared_buffer> m_list_buffer_processing;
			bool				m_processing;
			bool				_process_open_file_handle();
			void				_process_close_file_handle();
			void				_process_send_buffer(buffer_view _buf_processing);
			object_ptr<Iexecutor> m_pexecutor;
		#endif
};


}