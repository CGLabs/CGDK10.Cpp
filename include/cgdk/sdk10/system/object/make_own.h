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
//
// _make_own<TREF>
//
//
//
//-----------------------------------------------------------------------------
template <class TOBJECT, class... TARGS>
[[nodiscard]] own_ptr<TOBJECT> _make_own_raw(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TARGS&&... _args)
{
	class OBJECT_OWN : public TOBJECT, public Idisposable::Ndelete
	{
	public:
				OBJECT_OWN(TARGS&&... _nested_args) : TOBJECT(std::forward<TARGS>(_nested_args)...), Idisposable::Ndelete() {}
		virtual ~OBJECT_OWN()	{}
	};

#pragma push_macro("new")
#undef new
	#ifdef _ENABLE_DEBUG_NEW
		#if defined(_WIN32)
			auto pobject = new(_NORMAL_BLOCK, CGNEW_DEBUG_INFO_PARAMETERS_PASSING) OBJECT_OWN(std::forward<TARGS>(_args)...);
		#else
			auto pobject = new OBJECT_OWN(std::forward<TARGS>(_args)...);
		#endif
	#else
		auto pobject = new OBJECT_OWN(std::forward<TARGS>(_args)...);
	#endif
#pragma pop_macro("new")

	// Debug)
	CGNEW_DEBUG_INFO_SET(pobject, _filename, _line);

	// return)
	//return	pobject;
	return own_ptr<TOBJECT>(typename own_ptr<TOBJECT>::OWN_SET(pobject));
}

// Case) 'Npoolable<T>' inherited
template <class TOBJECT, class... TARGS>
[[nodiscard]] std::enable_if_t<std::is_base_of_v<Npoolable<TOBJECT>, TOBJECT>, own_ptr<TOBJECT>>
_make_own(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TARGS&&... _args)
{
	return TOBJECT::alloc(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TARGS>(_args)...);
}

// Case) No 'Npoolable<T>' inherited
template <class TOBJECT, class... TARGS>
[[nodiscard]] std::enable_if_t<!std::is_base_of_v<Npoolable<TOBJECT>, TOBJECT>, own_ptr<TOBJECT>>
_make_own(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA TARGS&&... _args)
{
	// check) TOBJECT must inherite class'Ireferenceable'
	static_assert(std::is_base_of_v<Ireferenceable, TOBJECT>, "CGObj: TOBJECT must inherite 'Ireferenceable' class");

	auto pobject = _make_object_create<TOBJECT, TARGS...>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TARGS>(_args)...);

	// return) 
	return own_ptr<TOBJECT>(typename own_ptr<TOBJECT>::OWN_SET(pobject));
}

template <class TOBJECT, class... TARGS>
[[nodiscard]] std::tuple<TOBJECT*, TARGS...> _make_own_parameters(TARGS&&... _args)
{
	return std::tuple<TOBJECT*, TARGS...>(nullptr, std::forward<TARGS>(_args)...);
}

template<class TOBJECT, class T>
[[nodiscard]] own_ptr<TOBJECT> _make_own_tuple_begin(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA std::tuple<T>&& /*_tuple*/)
{
	return	_make_own<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
}

template<class TOBJECT, class T, class... TARGS>
[[nodiscard]] own_ptr<TOBJECT> _make_own_tuple(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA std::tuple<T>&& _tuple, TARGS&&... _args)
{
	return	_make_own<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<TARGS>(_args)..., std::forward<T>(std::get<0>(_tuple)));
}

template<class TOBJECT, class T1, class T2, class... TREST, class... TARGS>
[[nodiscard]] own_ptr<TOBJECT> _make_own_tuple(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA std::tuple<T1, T2, TREST...>&& _tuple, TARGS&&... _args)
{
	return	_make_own_tuple<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::move((std::tuple<T2, TREST...>&)_tuple), std::forward<TARGS>(_args)..., std::forward<T1>(std::get<0>(_tuple)));
}

template<class TOBJECT, class T>
[[nodiscard]] own_ptr<TOBJECT> _make_own_tuple(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA std::tuple<T>&& _tuple)
{
	return	_make_own<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::forward<T>(std::get<0>(_tuple)));
}

template<class TOBJECT, class T1, class T2, class... TREST>
[[nodiscard]] own_ptr<TOBJECT> _make_own_tuple(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA std::tuple<T1, T2, TREST...>&& _tuple)
{
	return	_make_own_tuple<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::move((std::tuple<T2, TREST...>&)_tuple), std::forward<T1>(std::get<0>(_tuple)));
}

template<class TOBJECT, class T1, class T2, class... TREST>
[[nodiscard]] own_ptr<TOBJECT> _make_own_tuple_begin(CGNEW_DEBUG_INFO_PARAMETERS CGNEW_DEBUG_INFO_COMMA std::tuple<T1, T2, TREST...>&& _tuple)
{
	return	_make_own_tuple<TOBJECT>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA std::move((std::tuple<T2, TREST...>&)_tuple));
}


}