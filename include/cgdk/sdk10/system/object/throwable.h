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
	//
	// 1. Ithrowable and bases
	//
	//-----------------------------------------------------------------------------
	// 1) Ithrowable
	class Ithrowable
	{
	public:
		virtual	~Ithrowable() noexcept {}
	public:
		virtual	std::string_view	description() const noexcept PURE;
		virtual	object_ptr<LOG_RECORD> get_log_record() const noexcept PURE;
	};

	// 2) Nthrowable
	class Nthrowable : public std::exception, virtual public Ithrowable
	{
	public:
				Nthrowable() noexcept : m_description(), m_param(), m_reason(eRESULT::NOT_DEFINED) {}
				Nthrowable(const std::string_view _description) noexcept : m_description(_description), m_param(0), m_reason(eRESULT::NOT_DEFINED) {}
				Nthrowable(std::string&& _description) noexcept : m_description(std::forward<std::string>(_description)), m_param(0), m_reason(eRESULT::NOT_DEFINED) {}
				Nthrowable(result_code _reason, intptr_t _param = 0) noexcept : m_description(), m_param(_param), m_reason(_reason) {}
				Nthrowable(result_code _reason, intptr_t _param, const std::string_view _description) noexcept : m_description(_description), m_param(_param), m_reason(_reason) {}
				Nthrowable(result_code _reason, intptr_t _param, std::string&& _description) noexcept : m_description(std::move(_description)), m_param(_param), m_reason(_reason) {}
		virtual	~Nthrowable() noexcept {}

	public:
		[[nodiscard]] virtual	char const* what() const noexcept override { return to_string<char>(static_cast<eRESULT>(this->m_reason.value())).data(); }
		[[nodiscard]] virtual	std::string_view description() const noexcept override { return this->m_description; }
		[[nodiscard]] virtual	object_ptr<LOG_RECORD> get_log_record() const noexcept override;

		[[nodiscard]] result_code reason() const noexcept { return this->m_reason; }
		template <class TRESULT = result_code>
		[[nodiscard]] TRESULT	reason() const noexcept { return this->m_reason.value<TRESULT>(); }
		[[nodiscard]] intptr_t	param() const noexcept { return this->m_param; }
		template <class TPARAM = intptr_t>
		[[nodiscard]] TPARAM	param() const noexcept { return static_cast<TPARAM>(this->m_param); }

				auto&			operator >> (std::ostream& _stream_out) { this->stream_out(_stream_out); return *this; }
				auto&			operator >> (std::ostream& _stream_out) const { this->stream_out(_stream_out); return *this; }
				void			stream_out(std::ostream& _stream_out) const { _stream_out << this->description() << '\n'; }
	public:
								operator object_ptr<LOG_RECORD>() const noexcept { return this->get_log_record();}

	public:
				std::string		m_description;
				intptr_t		m_param;
				result_code		m_reason;
	};

	// 3)
	class Ndescription_ex
	{
	public:
				void			add_description(std::string_view _description);
				void			add_description(std::wstring_view _description);

	public:
				std::vector<std::string> m_description_ex;

	public:
				auto&			operator >> (std::ostream& _stream_out) { this->stream_out(_stream_out); return *this; }
				auto&			operator >> (std::ostream& _stream_out) const { this->stream_out(_stream_out); return *this; }
				void			stream_out(std::ostream& _stream_out) const { for (auto& iter : this->m_description_ex) { _stream_out << iter << '\n'; } }
	};

	// 3) Nthrowable with extra desciptions
	class Nthrowable_ex : public Nthrowable, public Ndescription_ex
	{
	public:
				Nthrowable_ex() noexcept {}
				Nthrowable_ex(const std::string_view _description) noexcept : Nthrowable(_description) {}
				Nthrowable_ex(std::string&& _description) noexcept : Nthrowable(std::move(_description)) {}
				Nthrowable_ex(result_code _reason, intptr_t _param = 0) noexcept : Nthrowable(_reason, _param) {}
				Nthrowable_ex(result_code _reason, intptr_t _param, const std::string_view _description) noexcept : Nthrowable(_reason, _param, _description) {}
				Nthrowable_ex(result_code _reason, intptr_t _param, const std::string& _description) noexcept : Nthrowable(_reason, _param, _description) {}
				Nthrowable_ex(result_code _reason, intptr_t _param, std::string&& _description) noexcept : Nthrowable(_reason, _param, std::move(_description)) {}
		virtual	~Nthrowable_ex() noexcept {}

	public:
		[[nodiscard]] virtual object_ptr<LOG_RECORD> get_log_record() const noexcept override;
				auto&			operator >> (std::ostream& _stream_out) { this->stream_out(_stream_out); return *this; }
				auto&			operator >> (std::ostream& _stream_out) const { this->stream_out(_stream_out); return *this; }
				void			stream_out(std::ostream& _stream_out) const { this->Nthrowable::stream_out(_stream_out); this->Ndescription_ex::stream_out(_stream_out); }
	};


	//-----------------------------------------------------------------------------
	//
	// 2. Exception Bases
	//
	//-----------------------------------------------------------------------------
	namespace throwable
	{
		// 2) failure
		class failure : public Nthrowable
		{
		public:
					failure() noexcept : Nthrowable() {}
					failure(std::string_view _description) noexcept : Nthrowable(_description) {}
					failure(std::string&& _description) noexcept : Nthrowable(std::move(_description)) {}
					failure(result_code _reason, intptr_t _param = 0) noexcept : Nthrowable(_reason, _param) {}
					failure(result_code _reason, intptr_t _param, const std::string_view _description) noexcept : Nthrowable(_reason, _param, _description) {}
					failure(result_code _reason, intptr_t _param, const std::string& _description) noexcept : Nthrowable(_reason, _param, _description) {}
					failure(result_code _reason, intptr_t _param, std::string&& _description) noexcept : Nthrowable(_reason, _param, std::move(_description)) {}
			virtual	~failure() noexcept {}
		};

		class failure_ex : public failure, public Ndescription_ex
		{
		public:
				failure_ex() noexcept {}
					failure_ex(const std::string_view _description) noexcept : failure(_description) {}
					failure_ex(std::string&& _description) noexcept : failure(std::move(_description)) {}
					failure_ex(result_code _reason, intptr_t _param = 0) noexcept : failure(_reason, _param) {}
					failure_ex(result_code _reason, intptr_t _param, const std::string_view _description) noexcept : failure(_reason, _param, _description) {}
					failure_ex(result_code _reason, intptr_t _param, const std::string& _description) noexcept : failure(_reason, _param, _description) {}
					failure_ex(result_code _reason, intptr_t _param, std::string&& _description) noexcept : failure(_reason, _param, std::move(_description)) {}
			virtual	~failure_ex() noexcept {}

		public:
			virtual	object_ptr<LOG_RECORD> get_log_record() const noexcept override;

		public:
					auto&			operator >> (std::ostream& _stream_out) { stream_out(_stream_out); return *this; }
					auto&			operator >> (std::ostream& _stream_out) const { stream_out(_stream_out); return *this; }
					void			stream_out(std::ostream& _stream_out) const { Nthrowable::stream_out(_stream_out); Ndescription_ex::stream_out(_stream_out); }
		};


		// 3) critical
		class critical : virtual public Nthrowable
		{
		public:
					critical() noexcept : Nthrowable() {}
					critical(std::string_view _description) noexcept : Nthrowable(_description) {}
					critical(std::string&& _description) noexcept : Nthrowable(std::move(_description)) {}
					critical(result_code _reason, intptr_t _param = 0) noexcept : Nthrowable(_reason, _param) {}
					critical(result_code _reason, intptr_t _param, const std::string_view _description) noexcept : Nthrowable(_reason, _param, _description) {}
					critical(result_code _reason, intptr_t _param, const std::string& _description) noexcept : Nthrowable(_reason, _param, _description) {}
					critical(result_code _reason, intptr_t _param, std::string&& _description) noexcept : Nthrowable(_reason, _param, std::move(_description)) {}
			virtual	~critical() noexcept {}
		};

		class critical_ex : public critical, public Ndescription_ex
		{
		public:
					critical_ex() noexcept {}
					critical_ex(const std::string_view _description) noexcept : critical(_description) {}
					critical_ex(std::string&& _description) noexcept : critical(std::move(_description)) {}
					critical_ex(result_code _reason, intptr_t _param = 0) noexcept : critical(_reason, _param) {}
					critical_ex(result_code _reason, intptr_t _param, const std::string_view _description) noexcept : critical(_reason, _param, _description) {}
					critical_ex(result_code _reason, intptr_t _param, std::string&& _description) noexcept : critical(_reason, _param, std::move(_description)) {}
			virtual	~critical_ex() noexcept {}

		public:
			virtual	object_ptr<LOG_RECORD> get_log_record() const noexcept override;
		};


		//-----------------------------------------------------------------------------
		/**
		 @class		seh_exception
		*///-----------------------------------------------------------------------------
	#ifdef _WIN32
		class seh_exception : public throwable::critical
		{
		public:
			seh_exception() noexcept : throwable::critical(), m_exception_record(), m_context_record() {}
			seh_exception(_EXCEPTION_POINTERS* _exception_pointers) noexcept :
				throwable::critical(),
				m_exception_record(*_exception_pointers->ExceptionRecord),
				m_context_record(*_exception_pointers->ContextRecord)
			{
				this->m_description = "SEH Exception";
			}

		public:
			EXCEPTION_RECORD	m_exception_record;
			CONTEXT				m_context_record;
		};
	#endif

		//-----------------------------------------------------------------------------
		/**
		 @class		force_raise
		*///-----------------------------------------------------------------------------
		class force_raise :	public throwable::critical
		{
		};


		//-----------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		template <class TOBJECT>
		bool execute_exception_handler(TOBJECT* /*_pExceptionObject*/, const std::exception& /*_exception*/, const std::string_view /*_exception_description*/)
		{
			return false;
		}

		template <class TOBJECT>
		bool execute_exception_handler(TOBJECT* /*_pExceptionObject*/, const std::string_view /*_exception_description*/)
		{
			return false;
		}
	}
}