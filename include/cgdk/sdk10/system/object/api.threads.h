//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
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
/**

 @class		threads
 

*///-----------------------------------------------------------------------------
class api::threads :
	virtual public				thread_list,
	virtual public				Ireferenceable
{
public:
			threads() noexcept{}
			template<class TFN, class... TARGS>
			threads(std::enable_if_t<!std::is_arithmetic<std::decay_t<TFN>>::value, TFN>&& _function, TARGS&&... _arguments) : m_count_thread_exist(0) { begin_thread(std::forward<TFN>(_function), std::forward<TARGS>(_arguments)...);}
			template<class TFN, class... TARGS>
			threads(size_t _count, TFN&& _function, TARGS&&... _arguments) : m_count_thread_exist(0) { begin_thread(_count, std::forward<TFN>(_function), std::forward<TARGS>(_arguments)...); }
	virtual	~threads() noexcept{}

public:
			template<class TFN, class... TARGS>
			std::enable_if_t<!std::is_arithmetic<std::decay_t<TFN>>::value, void>
								begin_thread(TFN&& _function, TARGS&&... _arguments);
			template<class TFN, class... TARGS>
			void				begin_thread(size_t _count, TFN&& _function, TARGS&&... _arguments);

			void				terminate_all();
			bool				wait();

			size_t				get_existing_thread_count() const { return this->m_count_thread_exist;}
	[[nodiscard]] bool			empty() const { return this->get_existing_thread_count()==0;}
	[[nodiscard]] bool			exist() const { return this->get_existing_thread_count()!=0;}

// implementation)
protected:
	//! @brief ������ �Լ�
	template <class TTYPE>
	static	void				fn_process_thread_pool(threads* _ppool, thread* _pthread, TTYPE* _pfunctor);

	virtual	void				process_begin_thread_object(thread* _pthread) noexcept;
	virtual	void				process_end_thread_object(thread* _pthread) noexcept;

private:
			std::atomic<int>	m_count_thread_exist{ 0 };
};


template <class TTYPE>
void api::threads::fn_process_thread_pool(threads* _ppool, thread* _pthread, TTYPE* _pfunctor)
{
	// 1) Hold
	object_ptr<thread> pthread = _pthread;
	object_ptr<threads>	ppool = _ppool;

	// 2) Functor ȣ���� ����ó��
	ppool->process_begin_thread_object(pthread);

	// 3) Functor�� ȣ���Ѵ�.
	try
	{
		(*_pfunctor)();
	}
	catch (...)
	{
	}

	// 5) Functor�� �����.
	delete _pfunctor;

	// 4) Functor ȣ���� ����ó��
	ppool->process_end_thread_object(pthread);
}

template<class TFN, class... TARGS>
std::enable_if_t<!std::is_arithmetic<std::decay_t<TFN>>::value, void>
api::threads::begin_thread(TFN&& _function, TARGS&&... _arguments)
{
	// declare) 
	using TFUNCTOR = decltype(std::bind(DECAY_COPY(std::forward<TFN>(_function)), DECAY_COPY(std::forward<TARGS>(_arguments))...));

	// declare)
	char temp_string[MAX_STRING_LENGTH]{};

#ifdef __cpp_rtti
	// 1) Nameable�� ��´�.
	object::Inameable* pnameable = dynamic_cast<object::Inameable*>(this);

	// 2) �̸��� �ۼ�~
	__sprintf(temp_string, "%s[%d]", (pnameable != nullptr) ? pnameable->name().data() : "", static_cast<int>(get_existing_thread_count()));
#else
	__sprintf(temp_string, "ThreadPool[%d]", static_cast<int>(get_existing_thread_count()));
#endif
	
	// 3) Thread ����
	scoped_lock(m_vector_thread)
	{
		// - Thread���� ������ Functor ����~
		auto* pfunctor_execute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_function)), DECAY_COPY(std::forward<TARGS>(_arguments))...);

		// - Thread�� �����Ѵ�.
		auto pthread = make_object<thread>();

		// - �̸��� �����Ѵ�.
		pthread->set_name(temp_string);

		// - Thread List�� �߰��Ѵ�.
		this->m_vector_thread.emplace_back(pthread);

		// - add_ref
		this->add_ref();

		try
		{
			// - Thread�� �����Ѵ�.
			pthread->begin_thread(fn_process_thread_pool<TFUNCTOR>, this, pthread.get(), pfunctor_execute);
		}
		catch(...)
		{
			// - Release
			this->release();

			// - Thread List���� �����Ѵ�.
			this->m_vector_thread.pop_back();

			// reraise)
			throw;
		}
	}
}

template<class TFN, class... TARGS>
void api::threads::begin_thread(size_t _count, TFN&& _function, TARGS&&... _arguments)
{
	// declare) 
	using TFUNCTOR = decltype(std::bind(DECAY_COPY(std::forward<TFN>(_function)), DECAY_COPY(std::forward<TARGS>(_arguments))...));

#ifdef __cpp_rtti
	// 1) Nameable�� ��´�.
	auto* pnameable = dynamic_cast<object::Inameable*>(this);
#endif

	// 2) iCount����ŭ Thread ����
	scoped_lock(this->m_vector_thread)	// Temporary - Visual studio 2019 problems
	{
		for (size_t i=0; i<_count; ++i)
		{
			// - Thread���� ������ Functor ����~
			auto* pfunctor_execute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_function)), DECAY_COPY(std::forward<TARGS>(_arguments))...);

			// - Thread�� �����Ѵ�.
			auto pthread = make_object<thread>();

			// declare)
			char temp_string[MAX_STRING_LENGTH]{};

			// - �̸��� �ۼ�~
		#ifdef __cpp_rtti
			__sprintf(temp_string, "%s[%d]", (pnameable!=nullptr) ? pnameable->name().data() : "", static_cast<int>(get_existing_thread_count()));
		#else
			__sprintf(temp_string, "ThreadPool[%d]", static_cast<int>(get_existing_thread_count()));
		#endif

			// - �̸��� �����Ѵ�.
			pthread->set_name(temp_string);

			// - thread�� �ִ´�.
			this->m_vector_thread.emplace_back(pthread);

			// - add_ref
			this->add_ref();

			try
			{
				// - Thread�� �����Ѵ�.
				pthread->begin_thread(fn_process_thread_pool<TFUNCTOR>, this, pthread.get(), pfunctor_execute);
			}
			catch(...)
			{
				// - Release
				this->release();

				// - Thread List���� �����Ѵ�.
				this->m_vector_thread.pop_back();

				// reraise)
				throw;
			}
		}
	}
}


}