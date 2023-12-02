//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        network socket http classes                        *
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
// net::io::connective::acceptor::Ntcp_secure
//
// 1) acceptor for SSL
//
// 2) additional context paramters
//
//    - all context parameters of  net::io::connective::acceptor::Ntcp 
//	  - "certificate file"		Certificate file
//	  - "privatekey file"		privatekey file
//
//-----------------------------------------------------------------------------
class net::io::connective::acceptor::Ntcp_secure :
// inherited classes)
	public						net::io::connective::acceptor::Ntcp
{
// definitions)
public:
			struct START_PARAMETER : public net::io::connective::acceptor::Ntcp::START_PARAMETER
			{
				crypt::ssl_context* pssl_context = nullptr;
			};

// public)
public:
	// 1) Service의 시작과 중지
			result_code			start() { context _context; return this->start(_context);}
			result_code			start(const START_PARAMETER& _parameter) { context temp{ buffer_view((char*)&_parameter, sizeof(START_PARAMETER)) }; return this->start(temp); }
			result_code			start(const context& _context) { context context_copy(_context); return this->start(context_copy);}
	virtual	result_code			start(context& _context) override;

	// 2) SSL Context
			auto				get_ssl_context() const noexcept { return this->m_pssl_context; }

// frameworks)
protected:
	// 3) 파라메터 설정할 때 처리할 것이 있으면 여기서 처리한다.
	virtual void				process_set_parameters(context& _context) override;
	virtual void				process_on_accept( Iconnectable* _pconnectable ) override;
	virtual result_code			_process_starting(context& _context) override;

// implementation) 
protected:
			object_ptr<crypt::ssl_context>	m_pssl_context;
};


}
