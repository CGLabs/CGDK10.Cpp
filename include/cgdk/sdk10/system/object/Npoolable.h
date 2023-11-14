//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                               Pool Classes                                *
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

 @class		Npoolable
 @brief		정적 멤버 변수로 자체적인 풀을 가진 풀 대상 객체 클래스이다.
 @todo		
 @ref		
 @details	\n
 IPoolable<TOBJECT>를 상속받아 풀의 대상이 됨과 동시에 자신의 풀을 자체적으로 정적 멤버 변수로 가진 것이다.
 따라서 풀에서 할당을 받을 때 자체적으로 가진 풀에서 할당받을 수 있고 할당이 해제되면 그 풀로 다시 돌아간다.
 또 이 Npoolable<T>을 상속받으면 make_object<T>()를 사용해 간단히 풀에서 할당받을 수 있다.

 Npoolable<T>을 상속받으면 참조계수가 0이 되어 on_final_release/process_dispose
 함수가 호출되면 할당받은 풀로 자동적으로 돌아가도록 제작되어 있다.

 은 다음과 같이 사용할 수 있다.가장 간단하게는 NET<T>()를 사용해 할당을 받을 수 있다.
 또 정적 멤버 함수인 alloc()함수를 사용해 할당할 수 있다.

 Npoolable<T>의 사용법은 다음과 같다.
 
 일단 아래와 같이 상속받아 foo클래스를 정의했다면

 <pre>
 // foo객체를 Npoolable을 상속받아 정의한다.
 class foo: public Npoolable<foo>
 {
 };
 </pre>

 아래와 같이 foo의 정적 멤버함수인 alloc()함수를 사용해 풀에서 할당받을 수 있다.
 <pre>
 // foo객체를 Pool에서 할당한다.
 object_ptr<foo>  a = foo::alloc();
 ...
 </pre>

 하지만 더 간단한 방법은 그냥 make_object<T>()함수를 사용하는 것이다.
 <pre>
 // foo객체를 Pool에서 할당한다.
 object_ptr<foo>  a = make_object<foo>();

 // Reference count를 통한 자연스러운 할당해제를 수행한다.
 a.reset();
 </pre>

 참조계수가 0이 되면 자동적으로 풀로 되돌아가기 때문에 foo::free()함수를 호출할 필요는 없다.

 Npoolable을 상속받으면 on_final_release가 이미 정의되어 있기 때문에 OnFinalReleass()를 재정의할 필요가 없다. 
 만약 재정의를 하게 된다면 반드시 free()함수를 호출하여 생성된 객체가 Pool로 되돌아가도록 해주어야 한다.

*/
//-----------------------------------------------------------------------------
template <class TOBJECT>
class CGDK::Npoolable :
	public						Ipoolable<TOBJECT>,
	public						factory::_traits_has_pool
{
public:
			using factory_t = default_factory_pool_t<TOBJECT>;
			using object_t = TOBJECT;

protected:
	virtual	~Npoolable() noexcept {}

public:
	[[nodiscard]] static own_ptr<factory_t>& get_factory() noexcept { return m_s_ppool_object;}
	[[nodiscard]] static TOBJECT* alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT)
	{
		auto* ppool = m_s_ppool_object.get();
	
		if (ppool != nullptr)
		{
			return ppool->alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
		}
		else
		{
		#ifdef _ENABLE_DEBUG_NEW
			#if defined(_WIN32)
				return new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) TOBJECT();
			#else
				return new TOBJECT();
			#endif
		#else
			return new TOBJECT();
		#endif
		}
	}
	static	void				dealloc(TOBJECT* _pitem) noexcept { CGASSERT_ERROR(_pitem != nullptr); m_s_ppool_object->dealloc(_pitem);}

protected:
	virtual	void				process_dispose() noexcept override { if (this->m_ppool.exist()) { if (this->m_this == nullptr) { this->m_this = dynamic_cast<TOBJECT*>(this); } this->m_ppool->dealloc(this->m_this); } else { delete this; } }

private:
	static	own_ptr<factory_t>	m_s_ppool_object;

			object_ptr<factory_t> m_ppool;
			TOBJECT*			m_this = nullptr;

			friend	factory_t;
};

template <class TOBJECT>
CGDK::own_ptr<CGDK::default_factory_pool_t<TOBJECT>> __ATTRIBUTE_PRIORITY(__STATIC_PRIORITY_LEVEL1 + 4) CGDK::Npoolable<TOBJECT>::m_s_ppool_object = _make_own_raw<default_factory_pool_t<TOBJECT>>(CGNEW_DEBUG_INFO_PARAMETERS_INITIAL CGNEW_DEBUG_INFO_COMMA std::string_view(), eFACTORY_TYPE::DEFAULT);

// poolable template
template <class TOBJECT>
class CGDK::POOLABLE : public TOBJECT, public CGDK::Npoolable<POOLABLE<TOBJECT>>
{
public:
	virtual ~POOLABLE() noexcept {}
};

namespace CGDK
{
	template <class T> class is_base_of_Nreferenceable : public std::false_type {};
	template <class X> class is_base_of_Nreferenceable<Nreferenceable<X>> : public std::true_type {};

	// case) 'Npoolable<T>' inherited
	template <class TOBJECT>
	[[nodiscard]] std::enable_if_t<std::is_base_of_v<Npoolable<TOBJECT>, TOBJECT> && !is_base_of_Nreferenceable<TOBJECT>::value, object_ptr<TOBJECT>>
		_alloc_object()
	{
		return TOBJECT::alloc();
	}

	// case) No 'Npoolable<T>' inherited
	template <class TOBJECT>
	[[nodiscard]] std::enable_if_t<!std::is_base_of_v<Npoolable<TOBJECT>, TOBJECT>&& is_base_of_Nreferenceable<TOBJECT>::value, object_ptr<TOBJECT>>
		_alloc_object()
	{
		return _make_object_raw<TOBJECT>();
	}

	// case) No 'Npoolable<T>' inherited
	template <class TOBJECT>
	[[nodiscard]] std::enable_if_t<!std::is_base_of_v<Npoolable<TOBJECT>, TOBJECT> && !is_base_of_Nreferenceable<TOBJECT>::value, object_ptr<TOBJECT>>
		_alloc_object()
	{
		// check) TOBJECT must inherite class'Ireferenceable'
		static_assert(std::is_base_of_v<Ireferenceable, TOBJECT>, "CGObj: TOBJECT must inherite 'Ireferenceable' class");

		return POOLABLE<TOBJECT>::alloc();
	}

}