//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            Server Log Classes                             *
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
// loggber_buffer
//
// 1. loggber_buffer은~
//     Log처리를 위한 것이다.
//
// 2. Log의 내용
//		0) Date/Time	Log가 남은 시간이다.(자동기록)
//		1) Logger		Log를 남기는 자의 이름이다.(자동 등록)
//		2) type			Log의 종류이다. Errror, Progress, Warning, Info, ...
//	    3) Level		Log의 중요도이다.
//		4) Source		Log에 남기는 Event의 주체가 되는 것을 의미한다.
//		5) Dest			Log에 남기는 Event의 대상이 되는 것을 의미한다.
//		6) Where		Log에 남기는 Event가 발생하는 객체를 의미한다.
//		7) Function		Log가 남는 Event를 호출한 함수를 의미한다.
//		8) Message		남길 Log Message를 의미한다.
//
//-----------------------------------------------------------------------------
class loggber_buffer : public Nlogger
{
public:
			struct INITIALIZE_PARAMETER
			{
				uint64_t		reserve_buffer_size;
			};

			loggber_buffer();
			loggber_buffer(const std::string_view _name);
	virtual ~loggber_buffer() noexcept;

			result_code			initialize() { context _context; return this->object::Ninitializable::initialize(_context);}
			result_code			initialize(const INITIALIZE_PARAMETER& _parameter) { context temp(buffer_view((char*)&_parameter, static_cast<uint32_t>(sizeof(INITIALIZE_PARAMETER)))); return this->initialize(temp); }
	virtual	result_code			initialize(context& _context) override { return this->object::Ninitializable::initialize(_context); }

	[[nodiscard]] shared_buffer	get_buffer() const noexcept { return this->m_buffer_log;}

protected:
	virtual	void				process_log(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) override;

	virtual	result_code			_process_initializing(context& _context) override;
	virtual	result_code			_process_destroying() noexcept override;

			lockable<>			m_cs_buffer_log;
			shared_buffer		m_buffer_log;
};


}