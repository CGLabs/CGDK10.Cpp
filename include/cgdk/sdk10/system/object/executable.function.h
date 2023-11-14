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

 @class		function
 @brief		Ư�� �Լ��� �������ش�.
 @todo		
 @ref		
 @details	\n
 ���� �Լ�, ���� �Լ�, std::bind() �Լ� ��ü ���� �������ش�.

*///-----------------------------------------------------------------------------
template <class TEXECUTE = std::function<void()>>
class executable::function : virtual public Iexecutable
{
public:
			function() noexcept : m_function_completion(nullptr) {}
			function(const TEXECUTE& _function) noexcept : m_function_completion(_function) {}
			function(TEXECUTE&& _function) noexcept : m_function_completion(_function) {}
	virtual	~function() noexcept {}

public:
			void				set_function(TEXECUTE&& _function) noexcept { scoped_lock(m_lockable_completion) { m_function_completion = std::move(_function); } }
			void				set_function(const TEXECUTE& _function) noexcept { scoped_lock(m_lockable_completion) { m_function_completion = _function; } }
	[[nodiscard]] TEXECUTE		get_function() const noexcept { scoped_lock(m_lockable_completion) { return m_function_completion; } }

private:
			lockable<>			m_lockable_completion;
			TEXECUTE			m_function_completion;
private:
	virtual	intptr_t			process_execute(intptr_t, size_t) override { return process_execute_result<decltype(m_function_completion())>();}
			template<class TRETURN>
			std::enable_if_t<std::is_void<TRETURN>::value, intptr_t>
								process_execute_result() { m_function_completion(); return intptr_t(0);}
			template<class TRETURN>
			std::enable_if_t<!std::is_void<TRETURN>::value, intptr_t>
								process_execute_result() { return static_cast<intptr_t>(m_function_completion());}
};


}
