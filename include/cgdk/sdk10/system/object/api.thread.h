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

namespace api
{

template<class TREP, class TPERIOD>
inline void				sleep_for(const std::chrono::duration<TREP, TPERIOD>& _tick) noexcept {std::this_thread::sleep_for(_tick);}
template <class TCLOCK, class TDURATION>
inline void				sleep_until(const std::chrono::time_point<TCLOCK, TDURATION>& _time) noexcept { std::this_thread::sleep_until(_time); }
inline void				sleep_until(const chrono::time::client::time_point& _time) noexcept { std::this_thread::sleep_until(_time.timepoint_cast<chrono::time::time_point>()); }

object_ptr<Nthread>		get_current_thread() noexcept;
int						get_current_pid() noexcept;

}


//-----------------------------------------------------------------------------
/**

 @class		Nthread
 
*///-----------------------------------------------------------------------------
class api::Nthread : 
// inherited classes)
	virtual public				object::Inameable,
	virtual public				Ireferenceable
{
// constructor/destructor)
public:
			Nthread() noexcept : m_is_blocked(false), m_pexecutor(nullptr) {}
			template<class TFN, class... TARGS>
			Nthread(TFN&& _function, TARGS&&... _arguments) : m_is_blocked(false), m_pexecutor(nullptr) { begin_thread(std::forward<TFN>(_function), std::forward<TARGS>(_arguments)...); }
	virtual	~Nthread() noexcept;

// public)
public:
			template<class TFN, class... TARGS>
			void				begin_thread(TFN&& _function, TARGS&&... _arguments);

			bool				wait();
			bool				terminate(uint32_t _exit_code=-1, chrono::tick::duration _ticks_wait = 1min);
			uint32_t			suspend();
			uint32_t			resume();
			bool				raise_exception();

	#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2012
	[[nodiscard]] THREAD_ID		thread_handle() const noexcept { return this->m_thread.native_handle();}
	#endif
	[[nodiscard]] auto			get_last_execute() const noexcept { return m_statistics_thread.tick_last_execute;}
	[[nodiscard]] const auto&	get_thread_statistics() const noexcept { return m_statistics_thread;}
	[[nodiscard]] bool			is_time_out(chrono::tick::duration _tick_differ_time) const noexcept;
	[[nodiscard]] bool			is_time_out(chrono::tick::duration _tick_differ_time, chrono::tick::time_point _tick_now) const noexcept;

			void				reset() noexcept;

	[[nodiscard]] const auto&	statistics() const noexcept { return m_statistics_thread; }
			void				statistics_executing_begin(const chrono::tick::time_point& _tick) noexcept;
			void				statistics_executing_begin() noexcept;
			void				statistics_executing_end() noexcept;
			void				statistics_error() noexcept;

// implementation) 
private:
	template <class TTYPE>
	static	void				fn_process_thread(api::Nthread* _pthread, TTYPE* _functor);

			void				register_thread();
			void				unregister_thread() noexcept;
			void				process_begin_thread();
			void				process_end_thread();

public:
			void				notify_blocked() noexcept;
			void				notify_unblocked() noexcept;

private:
			lockable<object_ptr<api::manager_thread>> m_pmanager;
	friend	class api::manager_thread;

	#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2012
	mutable std::thread			m_thread;
	#else
	mutable CGHANDLE			m_thread;
	#endif
			statistics::thread	m_statistics_thread;

public:
			lockable<>			m_lockable_executor;
			bool				m_is_blocked;
			Iexecutor*			m_pexecutor;
};

template <class TTYPE>
void api::Nthread::fn_process_thread(api::Nthread* _pthread, TTYPE* _pfunctor)
{
	// 1) Hold
	object_ptr<api::Nthread> pthread = _pthread;

	// 2) pre process
	pthread->process_begin_thread();

	// 3) cal functor
	try
	{
		(*_pfunctor)();
	}
	catch (...)
	{
	}

	// 4) delete funtor
	delete _pfunctor;

	// 5) post process
	pthread->process_end_thread();
}

template<class TFN, class... TARGS>
void api::Nthread::begin_thread(TFN&& _function, TARGS&&... _arguments)
{
	// declare) 
	using TFUNCTOR = decltype(std::bind(DECAY_COPY(std::forward<TFN>(_function)), DECAY_COPY(std::forward<TARGS>(_arguments))...));

	// 1) create functor
	auto* pfunctor = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_function)), DECAY_COPY(std::forward<TARGS>(_arguments))...);

	// 2) add reference count
	this->add_ref();

	try
	{
		// 3) start thread
		this->m_thread = std::thread(fn_process_thread<TFUNCTOR>, this, pfunctor);
	}
	catch(...)
	{
		// - release
		release();

		// - delete
		delete	pfunctor;

		// reraise)
		throw;
	}

	// 4) reset Thread ID
	m_statistics_thread.id_thread = m_thread.native_handle();
}

class api::thread : 
	public						Nthread,
	public						object::Nnameable,
	public						factory::_traits_system
{
public:
			thread()  noexcept {}
			template<class TFN, class... TARGS>
			thread(TFN&& _function, TARGS&&... _arguments) : Nthread(_function, std::forward<TARGS>(_arguments)...) { }
	virtual	~thread() noexcept {}
};


}