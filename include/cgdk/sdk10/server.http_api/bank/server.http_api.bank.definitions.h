//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           server.http_api.bank                            *
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
// CGServerQuerier::OAuth
//
// ----------------------------------------------------------------------------
enum class eOAUTH_SCOPE
{
	NOT_DEFINED_			 = 0,

	LOGIN_					 = 1,
	INQUIRY_				 = 2,
	TRANSFER_				 = 3,
	LOGIN_INQUIRY_			 = 4,
	LOGIN_TRNASFER_			 = 5,
	INQUIRY_TRNASFER_		 = 6,
	LOGIN_INQUIRY_TRNASFER_	 = 7,
	OOB_					 = 8
};

enum class eOAUTH_AUTH_TYPE
{
	NOT_DEFINED				 = 0,

	FIRST_					 = 'F',
	REAUTH_					 = 'R',
	BYPASS_					 = 'B'
};

enum class eOAUTH_YESNO
{
	NOT_DEFINED_			 = 0,

	YES_					 = 'Y',		// Yes
	NO_						 = 'N'		// No
};

enum class eOAUTH_INOUT_TYPE
{
	NOT_DEFINED_			 = 0,

	IN_						 = 1,		// '�Ա�'
	OUT_					 = 2		// '���'
};

enum class eOAUTH_INQUIRY_TYPE
{
	NOT_DEFINED_			 = 0,

	ALL_					 = 'A',		// 'A' ��ü
	IN_						 = 'I',		// 'I' �Ա�
	OUT_					 = 'O'		// 'O' ���
};

enum class eOAUTH_SORT_ORDER
{
	NOT_DEFINED_			 = 0,

	DESCENDING_				 = 'D',		// 'D' ��������
	ASCENDING_				 = 'A'		// 'A' ��������
};

enum class eOAUTH_CHECK_TYPE
{
	NOT_DEFINED_			 = 0,

	OUT_					 = 1,		// �����ü
	IN_						 = 2		// �Ա���ü
};

enum class eOAUTH_ORG_REQ_GUBUN
{
	NOT_DEFINED_			 = 0,

	FINTECH_NUM_			 = 'F',		// 1.����ũ�̿��ȣ
	ACCOUNT_NUM_			 = 'A'		// 2.���¹�ȣ
};

enum class eOAUTH_BANK_STATUS
{
	NOT_DEFINED_			 = 0,

	OPEN_					 = 'Y',		// �ŷ�����
	DISORDER_				 = 'D',		// ���
	LAUNCH_					 = 'L',		// ��������
	END						 = 'E'		// ����ó����
};

enum class eOAUTH_GENDER
{
	NOT_DEFINED_			 = 0,

	MALE_					 = 'M',		// ����
	FEMALE_					 = 'F'		// ����
};

enum class eOAUTH_TOKEN_TYPE
{
	NOT_DEFINED_			 = 0,

	BEARER_					 = 1		// ��ǻ� �̰� ����...
};

enum class eOAUTH_ACCOUNT_TYPE
{
	NOT_DEFINED_			 = 0,

	_1_						 = 1,		// 1: ���������
	_2_						 = 2,		// 2: ������
	_6_						 = 6,		// 6: ��������
};

typedef	int	eOAUTH_BANK_CODE;


template<class TTYPE> std::basic_string_view<TTYPE>	to_string(eOAUTH_SCOPE _scope) noexcept;
template<class TTYPE> std::basic_string_view<TTYPE>	to_string(eOAUTH_YESNO _value) noexcept;
template<class TTYPE> std::basic_string_view<TTYPE>	to_string(eOAUTH_SORT_ORDER _value) noexcept;
template<class TTYPE> std::basic_string_view<TTYPE>	to_string(eOAUTH_ORG_REQ_GUBUN _value) noexcept;
template<class TTYPE> std::basic_string_view<TTYPE>	to_string(eOAUTH_INQUIRY_TYPE _value) noexcept;
template<class TTYPE> std::basic_string_view<TTYPE>	to_string(eOAUTH_CHECK_TYPE _value) noexcept;
template<class TTYPE> std::basic_string_view<TTYPE>	to_string(eOAUTH_GENDER _value) noexcept;
template<class TTYPE> std::basic_string_view<TTYPE>	to_string(eOAUTH_TOKEN_TYPE _value) noexcept;
template<class TTYPE> std::basic_string_view<TTYPE>	to_string(eOAUTH_ACCOUNT_TYPE _value) noexcept;
template<class TTYPE> std::basic_string_view<TTYPE>	to_string(eOAUTH_INOUT_TYPE _value) noexcept;

template<class TTYPE> eOAUTH_ACCOUNT_TYPE			get_enum_OAUTH_ACCOUNT_TYPE	(std::basic_string_view<TTYPE> _string) noexcept;
template<class TTYPE> eOAUTH_SCOPE					get_enum_OAUTH_SCOPE			(std::basic_string_view<TTYPE> _string) noexcept;
template<class TTYPE> eOAUTH_BANK_STATUS			get_enum_OAUTH_BANK_STATUS	(std::basic_string_view<TTYPE> _string) noexcept;
template<class TTYPE> eOAUTH_YESNO					get_enum_OAUTH_YESNO			(std::basic_string_view<TTYPE> _string) noexcept;
template<class TTYPE> eOAUTH_BANK_CODE				get_enum_OAUTH_BANK_CODE		(std::basic_string_view<TTYPE> _string) noexcept;
template<class TTYPE> eOAUTH_TOKEN_TYPE				get_enum_OAUTH_TOKEN_TYPE	(std::basic_string_view<TTYPE> _string) noexcept;
template<class TTYPE> eOAUTH_GENDER					get_enum_OAUTH_GENDER		(std::basic_string_view<TTYPE> _string) noexcept;


}