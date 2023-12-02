//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                  Common                                   *
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

 @class		Ireferenceable
 
*/
//-----------------------------------------------------------------------------
class CGDK::Ireferenceable : virtual public Idisposable
{
// constructor/destructor) 
protected:
			Ireferenceable() noexcept {}
	explicit Ireferenceable(const Ireferenceable&) noexcept {}
			Ireferenceable(Ireferenceable&&) noexcept {}
public:
	virtual	~Ireferenceable() noexcept {}

// public) 
#ifdef NDEBUG
	#define		DEBUG_ON_ADD_REFERENCECOUNT(count)	
	#define		DEBUG_ON_RELEASE_REFERENCECOUNT
#else
	#define		DEBUG_ON_ADD_REFERENCECOUNT(count)	_DEBUG_on_add_reference_count(count)
	#define		DEBUG_ON_RELEASE_REFERENCECOUNT		_DEBUG_on_release_reference_count()
#endif

public:
	//! @brief set reference count(on_final_release/process_dispose is not called) 
			void				reset_reference_count() noexcept { m_counter = 0;}
			void				set_reference_count(int _count) noexcept { m_counter = _count;}

	//! @brief increase reference count 1 @return 변공된 참조계수 값
			int					add_ref() noexcept { DEBUG_ON_ADD_REFERENCECOUNT(1); return ++m_counter;}
			int					add_ref(int _count) noexcept { DEBUG_ON_ADD_REFERENCECOUNT(_count); CGASSERT_ERROR(_count>=0); return m_counter += _count;}

	//! @brief decrease reference and call count on_final_release/process_dispose on reference count being zero.
			int					release() noexcept;
			int					release(int _count) noexcept;

	[[nodiscard]] int			reference_count() const noexcept { return m_counter;}

			Ireferenceable&		operator ++ () noexcept { add_ref(); return *this;}
			Ireferenceable&		operator -- () noexcept { release(); return *this;}
			void				operator += (int _rhs) noexcept { add_ref(_rhs);}

			Ireferenceable&		operator = (const Ireferenceable&) noexcept { return *this;}
			Ireferenceable&		operator = (Ireferenceable&&) noexcept { return *this; }

			// statistics)
			void				statistics_on_extra() noexcept;
	[[nodiscard]] Ifactory*		get_factory() const noexcept  { return m_pfactory;}

// framework) 
protected:
	// 1) being called on reference count is 0
	virtual	void				on_final_release() noexcept {}

			void				_process_on_final_release() noexcept;

#ifndef NDEBUG
public:
	// debug) 
	virtual	void				_DEBUG_on_add_reference_count(int /*_count*/){}
	virtual	void				_DEBUG_on_release_reference_count() {}
#endif

// implementation) 
private:
			std::atomic<int>	m_counter { 0 };

private:
			Ifactory*			m_pfactory {nullptr};
			template<class> friend class factory::object_pool;
			template<class> friend class factory::object_pool_tls;
			template<class> friend class Nreferenceable;
			friend class Ischedulable;
};


inline int CGDK::Ireferenceable::release() noexcept
{
	// check) 
	DEBUG_ON_RELEASE_REFERENCECOUNT;

	// 1) decrement counter
	const int result = --m_counter;

	// check)
	CGASSERT_ERROR(result >= 0);

	if (result == 0)
		_process_on_final_release();

	// return) 
	return result;
}

inline int CGDK::Ireferenceable::release(int _count) noexcept
{
	// check) 
	CGASSERT_ERROR(_count >= 0);

	// 1) substract count
	const int result = m_counter.fetch_sub(_count) - _count;

	// check)
	CGASSERT_ERROR(result >= 0);

	if (result == 0)
		_process_on_final_release();

	// return) 
	return result;
}

inline void CGDK::Ireferenceable::_process_on_final_release() noexcept
{
	on_final_release();

	CGNEW_DEBUG_INFO_RESET(this);

	process_dispose();
}
