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

 @class		nake_executable fucntions
 
*///-----------------------------------------------------------------------------
template <class TFUNCTION>
static	std::enable_if_t<!std::is_base_of_v<Iexecutable, std::remove_pointer_t<std::decay_t<TFUNCTION>>> && !std::is_function<std::remove_pointer_t<std::decay_t<TFUNCTION>>>::value, object_ptr<Iexecutable>>
make_executable(TFUNCTION&& _fucntion)
{
	// declaration)
	class executable_function : public executable::function<std::function<decltype(_fucntion())()>>, public factory::_traits_system {};

	// 1) alloc executable
	auto pexecutable = alloc_object<executable_function>();

	// 2) set '_function' to pexecutable
	pexecutable->set_function(std::forward<TFUNCTION>(_fucntion));

	// return)
	return pexecutable;
}

template <class TFUNCTION>
static	std::enable_if_t<!std::is_base_of_v<Iexecutable, std::remove_pointer_t<std::decay_t<TFUNCTION>>>&& std::is_function<std::remove_pointer_t<std::decay_t<TFUNCTION>>>::value, object_ptr<Iexecutable>>
make_executable(TFUNCTION&& _fucntion)
{
	// declaration)
	class executable_function : public executable::function<std::function<decltype(_fucntion())()>>, public factory::_traits_system {};

	// 1) alloc executable
	auto pexecutable = alloc_object<executable_function>();

	// 2) set '_function' to pexecutable
	pexecutable->set_function(std::forward<TFUNCTION>(_fucntion));

	// return)
	return pexecutable;
}

template <class T, class TFUNCTION, class... TARGS>
static	std::enable_if_t<std::is_base_of_v<Ireferenceable, std::remove_pointer_t<std::decay_t<T>>>&& std::is_member_function_pointer_v<TFUNCTION>, object_ptr<Iexecutable>>
make_executable(T* _this, TFUNCTION _fucntion, TARGS&&... _args)
{
	return make_executable([=]()
		{
			// - call function
			(_this->*_fucntion)(std::forward<TARGS>(_args)...);
		});
}
template <class T, class TFUNCTION, class... TARGS>
static	std::enable_if_t<std::is_base_of_v<Ireferenceable, std::remove_pointer_t<std::decay_t<T>>>&& std::is_member_function_pointer_v<TFUNCTION>, object_ptr<Iexecutable>>
make_executable(TFUNCTION _fucntion, TARGS&&... _args)
{
	// 2) post
	return make_executable([=]()
		{
			// - call function
			_fucntion(std::forward<TARGS>(_args)...);
		});
}


}
