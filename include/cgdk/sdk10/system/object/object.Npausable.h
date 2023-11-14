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
/**

 @class		NCGPausable
 @brief		ICGPausable을 구현한 클래스
 @todo		
 @ref		
 @details	\n

// */
//-----------------------------------------------------------------------------
class CGDK::object::Npausable : virtual public object::Ipausable, virtual	public object::Istate
{
public:
	virtual ~Npausable() noexcept {}

public:
	virtual	result_code			pause() override;
	virtual	result_code			resume() override;

protected:
	virtual	void				on_pause_request() {}
	virtual	void				on_pausing() {}
	virtual	void				on_pause() {}

	virtual	void				on_resume_request() {}
	virtual	void				on_resuming() {}
	virtual	void				on_resume() {}

public:
	virtual	void				process_pause();
	virtual	void				process_resume();

	virtual void				_process_pause_request() { this->on_pause_request(); }
	virtual void				_process_pauseing() { this->on_pausing(); }
	virtual void				_process_pause() { this->on_pause(); }
	virtual void				_process_resume_request() { this->on_resume_request(); }
	virtual void				_process_resuming() { this->on_resuming(); }
	virtual void				_process_resume() { this->on_resume(); }
};