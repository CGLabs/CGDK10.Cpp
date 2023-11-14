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

 @class		batch_function
 @brief		여러 개의 Executable 객체를 실행하기 위한 클래스로 완료 시 함수를 실행해 준다.
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
template <class TEXECUTE = std::function<void()>>
class executable::batch_function :public executable::Nbatch
{
public:
	virtual ~batch_function() noexcept {}

public:
			void				set_function(const TEXECUTE& _fucntion) noexcept { scoped_lock(m_lockable_complete) { this->m_function_completion=_fucntion; }}
			void				set_function(TEXECUTE&& _fucntion) noexcept { scoped_lock(m_lockable_complete) { this->m_function_completion=std::move(_fucntion); }}
			TEXECUTE			get_function() const noexcept { scoped_lock(m_lockable_complete) { return this->m_function_completion; }}

private:
	virtual	void				process_complete_execution() override;

private:
			TEXECUTE			m_function_completion;
			lockable<>			m_lockable_complete;
};

template <class TEXECUTE>
void executable::batch_function<TEXECUTE>::process_complete_execution()
{
	scoped_lock(m_lockable_complete)
	{
		// check) 
		RETURN_IF(!this->m_function_completion);

		// 1) 실행한다.
		this->m_function_completion();
	}
}


}
