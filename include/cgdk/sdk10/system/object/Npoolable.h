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
 @brief		���� ��� ������ ��ü���� Ǯ�� ���� Ǯ ��� ��ü Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 IPoolable<TOBJECT>�� ��ӹ޾� Ǯ�� ����� �ʰ� ���ÿ� �ڽ��� Ǯ�� ��ü������ ���� ��� ������ ���� ���̴�.
 ���� Ǯ���� �Ҵ��� ���� �� ��ü������ ���� Ǯ���� �Ҵ���� �� �ְ� �Ҵ��� �����Ǹ� �� Ǯ�� �ٽ� ���ư���.
 �� �� Npoolable<T>�� ��ӹ����� make_object<T>()�� ����� ������ Ǯ���� �Ҵ���� �� �ִ�.

 Npoolable<T>�� ��ӹ����� ��������� 0�� �Ǿ� on_final_release/process_dispose
 �Լ��� ȣ��Ǹ� �Ҵ���� Ǯ�� �ڵ������� ���ư����� ���۵Ǿ� �ִ�.

 �� ������ ���� ����� �� �ִ�.���� �����ϰԴ� NET<T>()�� ����� �Ҵ��� ���� �� �ִ�.
 �� ���� ��� �Լ��� alloc()�Լ��� ����� �Ҵ��� �� �ִ�.

 Npoolable<T>�� ������ ������ ����.
 
 �ϴ� �Ʒ��� ���� ��ӹ޾� fooŬ������ �����ߴٸ�

 <pre>
 // foo��ü�� Npoolable�� ��ӹ޾� �����Ѵ�.
 class foo: public Npoolable<foo>
 {
 };
 </pre>

 �Ʒ��� ���� foo�� ���� ����Լ��� alloc()�Լ��� ����� Ǯ���� �Ҵ���� �� �ִ�.
 <pre>
 // foo��ü�� Pool���� �Ҵ��Ѵ�.
 object_ptr<foo>  a = foo::alloc();
 ...
 </pre>

 ������ �� ������ ����� �׳� make_object<T>()�Լ��� ����ϴ� ���̴�.
 <pre>
 // foo��ü�� Pool���� �Ҵ��Ѵ�.
 object_ptr<foo>  a = make_object<foo>();

 // Reference count�� ���� �ڿ������� �Ҵ������� �����Ѵ�.
 a.reset();
 </pre>

 ��������� 0�� �Ǹ� �ڵ������� Ǯ�� �ǵ��ư��� ������ foo::free()�Լ��� ȣ���� �ʿ�� ����.

 Npoolable�� ��ӹ����� on_final_release�� �̹� ���ǵǾ� �ֱ� ������ OnFinalReleass()�� �������� �ʿ䰡 ����. 
 ���� �����Ǹ� �ϰ� �ȴٸ� �ݵ�� free()�Լ��� ȣ���Ͽ� ������ ��ü�� Pool�� �ǵ��ư����� ���־�� �Ѵ�.

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