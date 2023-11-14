

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
	// 1) p_pParam�� NULL�̾�� �ȵȴ�.
	CGASSERT(_this != nullptr, 0);

	// 2) Thread�� �����Ѵ�.
	return _this->process_thread_run();
}

template <class TEXECUTOR>
result_code executor::threads<TEXECUTOR>::start(context& _context)
{
	// 1) Initializable
	auto* pInitializable = dynamic_cast<object::Iinitializable*>(this);

	// 2) Initalizable�� ������ initialize�Ѵ�.
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

		// - Value�� ��´�.
		str_thread_count = (std::string)_context.find("thread_count"sv, "thread count"sv, "threadcount"sv);

		// - Address�� ��´�.
		if (str_thread_count.empty() == false)
		{
			thread_count = __from_string<decltype(thread_count)>(str_thread_count.c_str());
		}
	}

	// 5) Thread ������ 0�� ���ϸ� Thread ������ ����� ����.
	if(thread_count == CGEXECUTOR_AUTO)
	{
		thread_count = api::get_core_count() * DEFAULT_THREAD_COUNT_PER_PROCESSOR + DEFAULT_BASE_THREAD_COUNT;
	}

	// check) �ִ� Thread ���� ���� (�ִ� Thread���� 1024���� �����Ѵ�.)
	SATURATE_MAX(thread_count, 1024);

	// 6) I/O CompletionPort�� �����Ѵ�.
	TEXECUTOR::start(_context);

	// 7) Done�� true��...
	this->m_is_active = true;
	this->m_enable_auto_exepand = enable_auto_exepand;
	this->m_count_thread_active = 0;
	this->m_count_thread_needed = thread_count;
	this->m_count_thread_wait = 0;
	this->m_count_thread_max = thread_count;
	this->m_thread_index = 0;

	try
	{
		// 8) ���ϴ� ������ŭ Thread�� �����.
		this->begin_thread(thread_count, fn_thread, this);

		// trace) 
		LOG_INFO << "  - start "sv << thread_count << " threads on executor["sv << name() << "]"sv;
	}
	catch(...)
	{
		// - ���� executor�� �ݴ´�.
		this->TEXECUTOR::stop();

		// - m_is_active�� false�� ȯ��
		this->m_is_active = false;

		// reraise)
		throw;
	}

	// return) ����...
	return result_code(eRESULT::SUCCESS);
}

template <class TEXECUTOR>
result_code executor::threads<TEXECUTOR>::stop() noexcept
{
	// 1) IOCP�� �ݴ´�.
	this->TEXECUTOR::stop();

	// 2) Thread�� ���ἳ���� ���� m_is_active�� false�� ������ ��
	this->m_is_active = false;
	this->m_count_thread_needed = 0;

	// 3) ��� Thread�� ����Ǳ� ������� �����Ѵ�.
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
	// 1. ���Ѵ�� ������~
	//
	//    - ���⼭ ���� while�� �ξ��µ� �̴� Exception�� ó�� �����̶��
	//      �Ҽ� �ִ�.
	//    - ���� execute()�߿� Exception�� �߻��� ��� Catch���� �޾�
	//      ó���ϰ� ���� m_is_active�� ���� true�� ��� ��� ó���ϰ� �ȴ�.
	//      ���� m_is_active�� false�� �ٷ� �������´�.
	//
	//-----------------------------------------------------------------
	// 1) index
	int thread_index = this->m_thread_index++;

	while(this->m_is_active)
	{
		// 4) executing thread �� ����
		++this->m_count_thread_active;
		++this->m_statistics.now.thread_count;

		// 5) i/o thread�� ���� loop�� ������.
		try
		{
			// - ���� ���� ������ ���� �ʿ��� ������ ������ ������ ��� ����~
			while(this->m_count_thread_active <= (this->m_count_thread_needed + this->m_count_thread_wait))
			{
				// - execute�� �����Ѵ�.
				this->execute(1s, thread_index);
			}
		}
		catch (throwable::failure& /*_e*/)
		{
		}
		catch(...)
		{
		}

		// 6) executing thread �� ����
		--this->m_count_thread_active;
		--this->m_statistics.now.thread_count;

		// 7) �ʹ� ������ wait�� ����.
		if(this->m_is_active)
		{
			// - wait�Ѵ�.
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
