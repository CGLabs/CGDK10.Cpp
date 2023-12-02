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
 @brief		���� ���� Executable ��ü�� �����ϱ� ���� Ŭ������ �Ϸ� �� �� ���� ���ŷ���ش�.
 @todo		
 @ref		
 @details	\n
 wait_execute_completion()�� ����ϸ� ����� ��� Executable�� �Ϸ�� ������ ���ŷ���·� ����Ѵ�.
 ��� Executable ��ü�� �Ϸ�Ǹ� �׶� ���ŷ�� Ǯ���� ����ȴ�.

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