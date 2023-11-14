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
// CGServerQuerier::http
//
// ----------------------------------------------------------------------------
#if defined(_MSC_VER)
	#pragma warning(disable:4996)
#endif

//-----------------------------------------------------------------------------
//
// CGServerQuerier::http
//
// ----------------------------------------------------------------------------
enum class eRESPONSE_CODE : uint32_t
{
//  CODE			HASH code
	A0000_		 = ('A' <<16) +   0,	// ó������
	A0001_		 = ('A' <<16) +   1,	// ó����(ó�������ȸ ���, ��ü��)
	A0002_		 = ('A' <<16) +   2,	// ������� ����
	A0003_		 = ('A' <<16) +   3,	// ���� ó�� ����
	A0004_		 = ('A' <<16) +   4,	// ��û���� ���� ����
	A0005_		 = ('A' <<16) +   5,	// ��� ������ ����
	A0006_		 = ('A' <<16) +   6,	// ���� ��ȯ ����
	A0007_		 = ('A' <<16) +   7,	// ó���ð� �ʰ� ����
	A0008_		 = ('A' <<16) +   8,	// �ߺ��ŷ� ����
	A0009_		 = ('A' <<16) +   9,	// API ���ξ��� ó������(����Ʈ �Ǻ� ó����� Ȯ��)
	A0010_		 = ('A' <<16) +  10,	// �̿��� APP ��� Ȯ�� ����
	A0011_		 = ('A' <<16) +  11,	// �̿��� API ������ ����
	A0012_		 = ('A' <<16) +  12,	// API ���� Ȯ�� ����
	A0013_		 = ('A' <<16) +  13,	// �̿��� ���� ��� �Ұ�
	A0014_		 = ('A' <<16) +  14,	// Ż�� ȸ��
	A0015_		 = ('A' <<16) +  15,	// �ùķ��̼� �������� TIMEOUT
	A0016_		 = ('A' <<16) +  16,	// FLAT ���� �۽� ����
	A0017_		 = ('A' <<16) +  17,	// 
	A0018_		 = ('A' <<16) +  18,	// �ŷ����� ����

	A0101_		 = ('A' <<16) + 101,	// �̿��� �Ա���ü �ѵ� �ʰ�(�� �ѵ�)
	A0102_		 = ('A' <<16) + 102,	// �̿��� �Ա���ü �ѵ� �ʰ�(�� �ѵ�)
	A0103_		 = ('A' <<16) + 103,	// �̿��� �����ü �ѵ� �ʰ�(�� �ѵ�)
	A0104_		 = ('A' <<16) + 104,	// �̿��� �����ü �ѵ� �ʰ�(�� �ѵ�)
	A0105_		 = ('A' <<16) + 105,	// �̿��� �Ա���ü �ѵ� �ʰ�(�Ǵ� �ѵ�)
	A0106_		 = ('A' <<16) + 106,	// �̿��� �Ա���ü �ѵ� �ʰ�(�Ǵ� �ѵ�)
	A0111_		 = ('A' <<16) + 111,	// ����� �����ü �ѵ� �ʰ�(�Ǵ� �ѵ�)
	A0112_		 = ('A' <<16) + 112,	// ����� �����ü �ѵ� �ʰ�(�� �ѵ�)

	A0301_		 = ('A' <<16) + 301,	// ���� ���� ����
	A0302_		 = ('A' <<16) + 302,	// ������� API �̿���� ����
	A0303_		 = ('A' <<16) + 303,	// ��ϵ� �̿��� ������ ��å ����
	A0304_		 = ('A' <<16) + 304,	// ����ũ�̿��ȣ ���� ����ġ
	A0305_		 = ('A' <<16) + 305,	// ��3�������������� �̿Ϸ�
	A0306_		 = ('A' <<16) + 306,	// ��ݵ��� �̿Ϸ�
	A0307_		 = ('A' <<16) + 307,	// ��ü��ȣ���� ����ġ
	A0308_		 = ('A' <<16) + 308,	// ó�������� ���δ�� ���� ����
	A0309_		 = ('A' <<16) + 309,	// ��ϵ� �̿��� ������ ���� ����
	A0310_		 = ('A' <<16) + 310,	// ��ü ���� ����
	A0311_		 = ('A' <<16) + 311,	// ��ϵ� ó������ ������ ���� ����
	A0312_		 = ('A' <<16) + 312,	// �����ָ� ����ġ
	A0313_		 = ('A' <<16) + 313,	// ����� ����ġ
	A0314_		 = ('A' <<16) + 314,	// �����̵� ��
	A0315_		 = ('A' <<16) + 315,	// �����߾�ȸ(����������) ���¹�ȣ�� �Է����� ��� ���� ó��

	O0001_		 = ('O' <<16) +   1,	// ������û �ź�-���� �Ķ���� ����([error_code])
	O0002_		 = ('O' <<16) +   2,	// Access Token �ź�
	O0003_		 = ('O' <<16) +   3,	// Access Token ����
	O0004_		 = ('O' <<16) +   4,	// API ���ٱ����� ����.(API ���񽺸� ��û���� �ʾ��� ��)
	O0005_		 = ('O' <<16) +   5,	// ������ ���� API ���� �Դϴ�.(API ���񽺰� ���� ��)
	O0006_		 = ('O' <<16) +   6,	// ������ ���� IP�Դϴ�.
	O0007_		 = ('O' <<16) +   7,	// API�� ��û �Ǵ� ó���� �� �����ϴ�.(API ����ó�� Routing ���� ��)
	O0008_		 = ('O' <<16) +   8,	// Object plan ��뷮 �ѵ� �ʰ�
	O0009_		 = ('O' <<16) +   9,	// API plan ��뷮 �ѵ� �ʰ�.
	O0010_		 = ('O' <<16) +  10,	// ������ ���� http method �Դϴ�.


	SUCCEESS_	 = A0000_,				// ó������
	FAIL_		 = ('X' <<16) +   0,	// ó�������� ����
};

// ---------------------------------------------------------------------------------
// ��÷4) API ������û �ź�(O0001)�� ���� ���� �����ڵ�(error_code)
// ---------------------------------------------------------------------------------
//
//	     992	Validation error						http header�� Authorization Bearer access_token�� ���� ��
//
//   3000103	Missing or duplicate parameters			������ �ʿ��� �ʼ� �Ķ���� ���� �������� ���� �� or Ư�� �Ķ���� ���� �ߺ����� ������ ��
//   
//   3000201	The given client credentials 			client_id�� �������� ���� �� or ��Ȱ��ȭ �Ǿ� ����� �� ���� ��
//	  			were not valid
//   3000114	Mismatching redirect_uri				����� callback url�� ��û�� callback url�� ���� ���� ��
//   
//   3000115	No registered scope value for			scope�� ���� ���� ��
//	  			this client has been requested
//   3000116	None of the supported response_types	response_type�� ������ ���� ���� ��
//	  			were used
//   3002110	The session has expired or aleady		����� session ���� ����Ͽ��� ��
//				been granted. The login process has to
//				be successful
//
template<class TTYPE>
inline eRESPONSE_CODE get_value_RESPONSE_CODE(const TTYPE* _string)
{
	// check)
	CGASSERT_ERROR(_string != nullptr);

	// check)
	THROW_IF(_string == nullptr, throwable::failure(eRESULT::INVALID_ARGUMENT));

	// 1) ����Ѵ�.
	auto value = static_cast<eRESPONSE_CODE>((((uint32_t)_string[0]) << 16) + __from_string<int>(_string + 1));

	// return)
	return	value;
}

#if defined(_WIN32)
template<std::size_t ISIZE>
void convert_utf8_to_multibyte(static_string<ISIZE>& _dest, std::string_view _source)
{
	// declare) 
	wchar_t	temp_dest[ISIZE];

	// 1) ���� WideChar�� ��ȯ�Ѵ�.
	auto	size_length = MultiByteToWideChar(CP_UTF8, 0, _source.data(), -1, temp_dest, ISIZE);

	// 2) WidtChar�� Multibyte�� ��ȯ�Ѵ�.
	size_length = WideCharToMultiByte(CP_ACP, 0, temp_dest, -1, _dest._get_ptr_first(), ISIZE, nullptr, nullptr);

	// 3) shared_buffer�� ũ�⸦ ����
	_dest._reset_size(size_length);
}
#else
template<std::size_t ISIZE>
void convert_utf8_to_multibyte(static_string<ISIZE>& /*_dest*/, std::string_view /*_source*/)
{
	CGASSERT_ERROR(false);
}
#endif

#if defined(_WIN32)
inline std::string convert_utf8_to_multibyte(std::string_view _source)
{
	// definitions) 
	const std::size_t ISIZE = 512;

	// declare) 
	char temp_dest_2[ISIZE]{ 0 };

	wchar_t	temp_dest[ISIZE]{ 0 };

	// 1) ���� WideChar�� ��ȯ�Ѵ�.
	auto size_length = MultiByteToWideChar(CP_UTF8, 0, _source.data(), -1, temp_dest, ISIZE);

	// 2) WidtChar�� Multibyte�� ��ȯ�Ѵ�.
	size_length = WideCharToMultiByte(CP_ACP, 0, temp_dest, -1, temp_dest_2, ISIZE, nullptr, nullptr);

	// 3) shared_buffer�� ũ�⸦ ����
	return std::string(temp_dest_2);
}
#else
inline std::string convert_utf8_to_multibyte(std::string_view /*_source*/)
{
	CGASSERT_ERROR(false);
	return std::string();
}
#endif

#if defined(_WIN32)
inline void convert_multibyte_to_utf8(char* _dest_utf8, std::string_view _source_multibytes)
{
	// declare) 
	wchar_t	temp_dest[512];

	// 1) ���� WideChar�� ��ȯ�Ѵ�.
	auto size_length = MultiByteToWideChar(CP_ACP, 0, _source_multibytes.data(), -1, temp_dest, 512);

	// 2) WidtChar�� Multibyte�� ��ȯ�Ѵ�.
	size_length = WideCharToMultiByte(CP_UTF8, 0, temp_dest, -1, _dest_utf8, 512, nullptr, nullptr);
}
#else
inline void convert_multibyte_to_utf8(char* /*_dest_utf8*/, std::string_view /*_source_multibytes*/)
{
	CGASSERT_ERROR(false);
}
#endif


//-----------------------------------------------------------------------------
//
// REQUEST/RESPONSE
//
// ----------------------------------------------------------------------------
namespace query
{

struct REQUEST
{
	std::string_view			str_url;
};

struct RESPONSE
{
	// 1) result
	shared_buffer				buf_response;

	// 2) result
	eRESPONSE_CODE				rsp_code = eRESPONSE_CODE::A0000_;
	std::string					rsp_message;
};


}


}