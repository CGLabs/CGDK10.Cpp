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
// C_logEvent
//
// 1. C_logEvent��~
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
class logger_console : 
	public						Nlogger
{
public:
			struct INITIALIZE_PARAMETER
			{
			};

			logger_console();
			logger_console(const std::string_view _name);
	virtual ~logger_console() noexcept;

			result_code			initialize() { return this->object::Ninitializable::initialize(); }
			result_code			initialize(const INITIALIZE_PARAMETER&) { return initialize(); }
	virtual	result_code			initialize(context& _context) override { return this->object::Ninitializable::initialize(_context); }

	[[nodiscard]] eCHARACTER_SET character_encoding() const noexcept { return this->m_char_encoding; }
			void				character_encoding(eCHARACTER_SET _char_code) noexcept { this->m_char_encoding = _char_code; }

	virtual	void				process_log(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) override;

protected:
	virtual	result_code			_process_initializing(context& _context) override;
	virtual	result_code			_process_destroying() noexcept;

			eCHARACTER_SET		m_char_encoding{ DEFAULT_CONSOLE_CHARACTER_SET };

		#if defined(_WIN32)
			HANDLE				m_console_handle = INVALID_HANDLE_VALUE;
		#endif

};


}