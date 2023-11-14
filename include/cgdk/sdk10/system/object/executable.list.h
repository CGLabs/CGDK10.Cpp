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

 @class		list
 @brief		여러 개의 Exectutable 객체를 가지고 있는 Executable 클래스이다.
 @todo		
 @ref		
 @details	\n
 여러 개의 Executable을 list형태로 가지고 있으며 실행될 때 자신이 가진 Executable의 process_execute()를 모두 호출해준다.
 또 ITERATOR를 얻어 내부 Executable을 접근 할 수 있다.

*///-----------------------------------------------------------------------------
template <class TEXECUTABLE=Iexecutable>
class executable::list : virtual protected Iexecutable
{
public:
			list();
	virtual ~list() noexcept;

public:
			using CONTAINER = circular_list<object_ptr<TEXECUTABLE>>;
			class ITERATOR;

			bool				register_executable(TEXECUTABLE* _pexecutable);
			bool				unregister_executable(TEXECUTABLE* _pexecutable) noexcept;
			void				unregister_executable_all() noexcept;

	[[nodiscard]] ITERATOR		get_iterator() noexcept;
	[[nodiscard]] size_t		executable_count() const noexcept;
	[[nodiscard]] bool			empty() const noexcept;
	[[nodiscard]] bool			exist() const noexcept;

protected:
	virtual intptr_t			process_execute(intptr_t _return, size_t _param) override;

	virtual void				on_final_release() noexcept override;

private:
			lockable<CONTAINER> m_list_executable;
};


}

#include "cgdk/sdk10/system/object/executable.list.inl"
