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
// 1. loggber_buffer��~
//     Logó���� ���� ���̴�.
//
// 2. Log�� ����
//		0) Date/Time	Log�� ���� �ð��̴�.(�ڵ����)
//		1) Logger		Log�� ����� ���� �̸��̴�.(�ڵ� ���)
//		2) type			Log�� �����̴�. Errror, Progress, Warning, Info, ...
//	    3) Level		Log�� �߿䵵�̴�.
//		4) Source		Log�� ����� Event�� ��ü�� �Ǵ� ���� �ǹ��Ѵ�.
//		5) Dest			Log�� ����� Event�� ����� �Ǵ� ���� �ǹ��Ѵ�.
//		6) Where		Log�� ����� Event�� �߻��ϴ� ��ü�� �ǹ��Ѵ�.
//		7) Function		Log�� ���� Event�� ȣ���� �Լ��� �ǹ��Ѵ�.
//		8) Message		���� Log Message�� �ǹ��Ѵ�.
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