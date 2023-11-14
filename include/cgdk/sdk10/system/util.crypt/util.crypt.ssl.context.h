//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                Web Classes                                *
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
// CGDK::crypt::ssl_context
//
//-----------------------------------------------------------------------------
namespace crypt
{

class ssl_context :
	virtual public				object::Idestroyable
{
public:
			ssl_context() noexcept;
			ssl_context(const std::string_view _pem_cert, const std::string_view _pem_private_key);
			ssl_context(const std::wstring_view _pem_cert, const std::wstring_view _pem_private_key);
	virtual ~ssl_context() noexcept;

// public)
public:
			void				initialize_server(const std::string_view _pem_cert, const std::string_view _pem_private_key);
			void				initialize_server(const std::wstring_view _pem_cert, const std::wstring_view _pem_private_key);
			void				initialize_client();
	virtual	result_code			destroy() noexcept override;

			object_ptr<ssl>		alloc_ssl(int _handle);
	[[nodiscard]] SSL_CTX*		get_ssl_context() const noexcept { return m_pssl_context; }
	[[nodiscard]] std::string_view get_filename_cert() const noexcept { return m_file_cert; }
	[[nodiscard]] std::string_view get_filename_private_key() const noexcept { return m_file_private_key; }

private:
			SSL_CTX*			m_pssl_context;
			std::string			m_file_cert;
			std::string			m_file_private_key;

			object_ptr<ssl_manager>	m_pmanager;
};


}
}