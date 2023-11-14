

template <class TEXECUTOR>
executor::threads<TEXECUTOR>::threads() :
	TEXECUTOR(),
	api::threads(),
	m_is_active(false),
	m_enable_auto_exepand(false),
	m_count_thread_active(0),
	m_count_thread_needed(0),
	m_count_thread_wait(0),
	m_count_thread_max(0)
{
}

template <class TEXECUTOR>
executor::threads<TEXECUTOR>::~threads() noexcept
{
	this->executor::threads<TEXECUTOR>::stop();
}

template <class TEXECUTOR>
uint32_t executor::threads<TEXECUTOR>::fn_thread(executor::threads<TEXECUTOR>* _this)
{
	// 1) p_pParam이 NULL이어서는 안된다.
	CGASSERT(_this != nullptr, 0);

	// 2) Thread를 수행한다.
	return _this->process_thread_run();
}

template <class TEXECUTOR>
result_code executor::threads<TEXECUTOR>::start(context& _context)
{
	// 1) Initializable
	auto* pInitializable = dynamic_cast<object::Iinitializable*>(this);

	// 2) Initalizable이 있으면 initialize한다.
	if(pInitializable != nullptr)
	{
		pInitializable->initialize();
	}

	// declare)
	size_t thread_count = CGEXECUTOR_AUTO;
	bool enable_auto_exepand = false;

	if (_context.type() == eCONTEXT_VALUE_TYPE::BUFFER_)
	{
		// - get parameter
		auto& parameter = _context.v.value_buffer.front<START_PARAMETER>();

		// - get suitable provider;
		thread_count = parameter.thread_count;
	}
	else
	{
		// declare) 
		std::string str_thread_count;

		// - Value를 얻는다.
		str_thread_count = (std::string)_context.find("thread_count"sv, "thread count"sv, "threadcount"sv);

		// - Address를 얻는다.
		if (str_thread_count.empty() == false)
		{
			thread_count = __from_string<decltype(thread_count)>(str_thread_count.c_str());
		}
	}

	// 5) Thread 갯수가 0개 이하면 Thread 갯수를 계산해 낸다.
	if(thread_count == CGEXECUTOR_AUTO)
	{
		thread_count = api::get_core_count() * DEFAULT_THREAD_COUNT_PER_PROCESSOR + DEFAULT_BASE_THREAD_COUNT;
	}

	// check) 최대 Thread 갯수 제한 (최대 Thread수는 1024개로 제한한다.)
	SATURATE_MAX(thread_count, 1024);

	// 6) I/O CompletionPort를 생성한다.
	TEXECUTOR::start(_context);

	// 7) Done을 true로...
	this->m_is_active = true;
	this->m_enable_auto_exepand = enable_auto_exepand;
	this->m_count_thread_active = 0;
	this->m_count_thread_needed = thread_count;
	this->m_count_thread_wait = 0;
	this->m_count_thread_max = thread_count;
	this->m_thread_index = 0;

	try
	{
		// 8) 원하는 갯수만큼 Thread를 만든다.
		this->begin_thread(thread_count, fn_thread, this);

		// trace) 
		LOG_INFO << "  - start "sv << thread_count << " threads on executor["sv << name() << "]"sv;
	}
	catch(...)
	{
		// - 먼저 executor을 닫는다.
		this->TEXECUTOR::stop();

		// - m_is_active을 false로 환원
		this->m_is_active = false;

		// reraise)
		throw;
	}

	// return) 성공...
	return result_code(eRESULT::SUCCESS);
}

template <class TEXECUTOR>
result_code executor::threads<TEXECUTOR>::stop() noexcept
{
	// 1) IOCP를 닫는다.
	this->TEXECUTOR::stop();

	// 2) Thread를 종료설정를 위해 m_is_active을 false로 설정한 후
	this->m_is_active = false;
	this->m_count_thread_needed = 0;

	// 3) 모든 Thread가 종료되길 대기한후 리턴한다.
	auto result = this->wait();

	// check)
	RETURN_IF(result == false, result_code(eRESULT::FAIL));

	// return)
	return result_code(eRESULT::SUCCESS);
}

template <class TEXECUTOR>
uint32_t executor::threads<TEXECUTOR>::process_thread_run()
{
	//-----------------------------------------------------------------
	// 1. 무한대로 돌린다~
	//
	//    - 여기서 이중 while을 두었는데 이는 Exception의 처리 때문이라고
	//      할수 있다.
	//    - 만약 execute()중에 Exception이 발생할 경우 Catch에서 받아
	//      처리하고 만약 m_is_active이 아직 true일 경우 계속 처리하게 된다.
	//      만약 m_is_active이 false면 바로 빠져나온다.
	//
	//-----------------------------------------------------------------
	// 1) index
	int thread_index = this->m_thread_index++;

	while(this->m_is_active)
	{
		// 4) executing thread 수 증가
		++this->m_count_thread_active;
		++this->m_statistics.now.thread_count;

		// 5) i/o thread의 무한 loop를 돌린다.
		try
		{
			// - 현재 가용 쓰레드 수가 필요한 쓰레드 수보다 적으면 계속 돈다~
			while(this->m_count_thread_active <= (this->m_count_thread_needed + this->m_count_thread_wait))
			{
				// - execute를 수행한다.
				this->execute(1s, thread_index);
			}
		}
		catch (throwable::failure& /*_e*/)
		{
		}
		catch(...)
		{
		}

		// 6) executing thread 수 감소
		--this->m_count_thread_active;
		--this->m_statistics.now.thread_count;

		// 7) 너무 많으면 wait에 들어간다.
		if(this->m_is_active)
		{
			// - wait한다.
		}
	}

	// return)
	return 0;
}

template <class TEXECUTOR>
bool executor::threads<TEXECUTOR>::process_control(uint64_t _command, uint64_t /*_param*/) noexcept
{
	switch (_command)
	{
	// - notify block
	case	1:	
			this->process_control_block();
			break;

	// - notify unblock
	case	2:	
			this->process_control_unblock();
			break;
	default:
			break;
	}

	// return)
	return true;
}

template <class TEXECUTOR>
bool executor::threads<TEXECUTOR>::process_control_block() noexcept
{
	// 1) increase m_count_thread_wait
	++this->m_count_thread_wait;

	// return)
	return true;
}

template <class TEXECUTOR>
bool executor::threads<TEXECUTOR>::process_control_unblock() noexcept
{
	// 1) decrease m_count_thread_wait
	--this->m_count_thread_wait;

	// return)
	return true;
}

template <class TEXECUTOR>
void executor::threads<TEXECUTOR>::process_begin_thread_object(api::thread* _pthread) noexcept
{
	{
		std::lock_guard<lockable<>> cs(_pthread->m_lockable_executor);

		_pthread->m_pexecutor = this;
	}

	api::threads::process_begin_thread_object(_pthread);
}

template <class TEXECUTOR>
void executor::threads<TEXECUTOR>::process_end_thread_object(api::thread* _pthread) noexcept
{
	api::threads::process_end_thread_object(_pthread);

	{
		std::lock_guard<lockable<>> cs(_pthread->m_lockable_executor);

		_pthread->m_pexecutor = nullptr;
	}
}
