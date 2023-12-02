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
//-----------------------------------------------------------------------------
//
// object_ptr<TOBJECT> _make_object_create<TOBJECT>(TOBJECT* p)
//
//
//
//-----------------------------------------------------------------------------
template <class TOBJECT>
std::enable_if_t<!std::is_base_of_v<CGDK::object::Idestroyable, TOBJECT> && !std::is_base_of_v<CGDK::object::Istartable, TOBJECT>, void>
__on_object_delete(TOBJECT*)
{
}

template <class TOBJECT>
std::enable_if_t<std::is_base_of_v<CGDK::object::Idestroyable, TOBJECT>, void>
__on_object_delete(TOBJECT* _object)
{
	_object->destroy();
}

template <class TOBJECT>
std::enable_if_t<!std::is_base_of_v<CGDK::object::Idestroyable, TOBJECT> && std::is_base_of_v<CGDK::object::Istartable, TOBJECT>, void>
__on_object_delete(TOBJECT* _object)
{
	_object->stop();
}

template <class TOBJECT, class... TARGS>
[[nodiscard]] TOBJECT* _make_object_create(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TARGS&&... _args)
{
	class __OBJECT_CREATE : public TOBJECT, public REFERENCEABLE_RELEASER
	{
	public:
				__OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TARGS&&... _nested_args) : TOBJECT(std::forward<TARGS>(_nested_args)...) REFERENCEABLE_RELEASER_INIT(CGNEW_DEBUG_INFO_PARAMETERS_PASSING) {}
		virtual ~__OBJECT_CREATE() { __on_object_delete<TOBJECT>(this); }
	};

#pragma push_macro("new")
#undef new
#ifdef _ENABLE_DEBUG_NEW
	#if defined(_WIN32)
		auto pobject = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) __OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TARGS>(_args)...);
	#else
		auto pobject = new __OBJECT_CREATE(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TARGS>(_args)...);
	#endif
#else
	auto pobject = new __OBJECT_CREATE(std::forward<TARGS>(_args)...);
#endif
#pragma pop_macro("new")

	// debug)
	CGNEW_DEBUG_INFO_SET(pobject, _filename, _line); 

	// return)
	return pobject;
}

template <class TOBJECT>
std::enable_if_t<std::is_base_of_v<CGDK::Npoolable<TOBJECT>, TOBJECT>, void>
	DEALLOC(TOBJECT* p)
{
	TOBJECT::dealloc(p);
}

template <class TOBJECT>
std::enable_if_t<!std::is_base_of_v<CGDK::Npoolable<TOBJECT>, TOBJECT>, void>
	DEALLOC(TOBJECT* p)
{
	delete p;
}
