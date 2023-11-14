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

 @class		CBatchWait
 @brief		여러 개의 Executable 객체를 실행하기 위한 클래스로 완료 될 때 까지 블록킹해준다.
 @todo		
 @ref		
 @details	\n
 wait_execute_completion()를 사용하면 실행된 모든 Executable이 완료될 때까지 블록킹상태로 대기한다.
 모든 Executable 객체가 완료되면 그때 블록킹이 풀리며 진행된다.

*///-----------------------------------------------------------------------------
class executable::batch_wait : public executable::Nbatch
{
public:
	virtual ~batch_wait() noexcept;

public:
			bool				wait_execute_completion(chrono::tick::duration _ticks_wait = chrono::tick::duration::max());

protected:
	virtual	void				process_complete_execution() override;

			std::mutex				m_lock_complete;
			std::condition_variable	m_cv_complete;
};


}