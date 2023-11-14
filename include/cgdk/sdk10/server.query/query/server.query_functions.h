//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Query Classes                            *
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
// query::query_function
//
//
//-----------------------------------------------------------------------------
template<class TQUERY>
class query::query_function :
// inherited classes)
	public						TQUERY
{
// definitions) 
public:
	typedef	std::function<void(throwable::failure_ex&, TQUERY*)>	TQUERYLAMBDA;

// public) 
public:
	// 1) 실행할 함수를 정의하는 함수.
			void				set_function(const TQUERYLAMBDA& _p) noexcept { m_lambda = _p;}
			void				set_function(TQUERYLAMBDA&& _p) noexcept { m_lambda = std::move(_p);}
			TQUERYLAMBDA		get_function() const noexcept { return m_lambda;}

// implementation) 
protected:
	// 1) Lambda function
			TQUERYLAMBDA		m_lambda;

	// 2) Query의 처리를 정의한 함수.
	virtual	void				process_execute_query() override;
};

template<class TQUERY>
void query::query_function<TQUERY>::process_execute_query()
{
	try
	{
		try
		{
			// 1) query를 수행한다.
			TQUERY::process_execute_query();
		}
		catch (throwable::failure_ex& _e)
		{
			// - call lambeda function
			m_lambda(_e, this);

			// reraise)
			throw;
		}
		catch (...)
		{
			// declare)
			throwable::failure_ex result(eRESULT::EXCEPTION);

			// - call lambeda function
			m_lambda(result, this);

			// reraise)
			throw;
		}

		// declare)
		throwable::failure_ex result(eRESULT::SUCCESS);

		// 2) request Query
		m_lambda(result, this);
	}
	catch (...)
	{
		// - close Query
		this->close_query();

		// reraise)  
		throw;
	}

	// 3) Query를 닫는다.
	this->close_query();
}


}