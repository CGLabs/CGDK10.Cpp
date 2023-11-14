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

 	factory::Iobject
 
*/
//-----------------------------------------------------------------------------
template <class TOBJECT>
class factory::Iobject : virtual public Ifactory
{
public:
	Iobject(std::string_view _name, eFACTORY_TYPE _factory_type)
	{
		if (_name.empty() == false)
		{
			this->set_name(_name);
		}
		else
		{
		#if defined(_MSC_VER)
			__if_exists(TOBJECT::_get_static_factory_name)
			{
				this->set_name(TOBJECT::_get_static_factory_name());
			}
			__if_not_exists(TOBJECT::_get_static_factory_name)
			{
		#endif
			// - set default name
			#ifdef __cpp_rtti
				this->set_name(_factory_name<TOBJECT>::get_default_name());
			#else
				this->set_name(__FUNCTION__);
			#endif
	
		#if defined(_MSC_VER)
			}
		#endif
		}

		this->m_statistics.type = (_factory_type != eFACTORY_TYPE::DEFAULT) ? _factory_type : factory::_get_default_pool_factory_type<TOBJECT>();
		this->m_statistics.object_type = _get_object_type<TOBJECT>();

		// 주의) pool factory의 경우 여기서 process_register_factory()를 호출한다. (recursion이 없을 것이므로)
		this->process_register_factory();
	}

	virtual	~Iobject() noexcept
	{
		// check)
		CGASSERT_ERROR((this->m_statistics.now.alloc_create + this->m_statistics.now.alloc_stack + this->m_statistics.now.alloc_stack_tls) == (this->m_statistics.now.free_delete + this->m_statistics.now.free_stack + this->m_statistics.now.free_stack_tls));

		// check)
		CGASSERT_ERROR(this->m_statistics.now.in_using == 0);

		// 1) unregister from factory manager
		this->process_unregister_factory();
	}

protected:
	template <class T>
	std::enable_if_t<std::is_base_of_v<factory::_traits_has_pool, T>, void>
								process_destroy_object(TOBJECT* _object) noexcept
	{
		// check)
		CGASSERT_ERROR(_object != nullptr);

		// 1) delete _object
		delete _object;
	}
	template <class T>
	std::enable_if_t<!std::is_base_of_v<factory::_traits_has_pool, T>, void>
								process_destroy_object(TOBJECT* _object) noexcept
	{
		// check)
		CGASSERT_ERROR(_object != nullptr);

		// 1) delete _object
		delete _object;

		// 2) decrease reference count (m_ppool에 setting되어 있지 않았다면 자체적으로 감소시킨다.)
		this->release();
	}
	template <class T>
	std::enable_if_t<std::is_base_of_v<factory::_traits_has_on_alloc, T>, void>
								process_on_alloc(TOBJECT* _object)
	{
		_object->process_on_pool_alloc();
	}
	template <class T>
	std::enable_if_t<!std::is_base_of_v<factory::_traits_has_on_alloc, T>, void>
								process_on_alloc(TOBJECT* /*_object*/)
	{
	}
	template <class T>
	std::enable_if_t<std::is_base_of_v<factory::_traits_has_on_dealloc, T>, void>
								process_on_dealloc(TOBJECT* _object) noexcept
	{
		_object->process_on_pool_dealloc();
	}
	template <class T>
	std::enable_if_t<!std::is_base_of_v<factory::_traits_has_on_dealloc, T>, void>
								process_on_dealloc(TOBJECT* /*_object*/) noexcept
	{
	}

	[[nodiscard]] virtual TOBJECT* create_object(CGNEW_DEBUG_INFO_PARAMETERS) PURE;
	virtual	result_code			destroy() noexcept override { this->close(); return result_code(eRESULT::SUCCESS); }

};


}
