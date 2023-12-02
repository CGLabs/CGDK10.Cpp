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
	A0000_		 = ('A' <<16) +   0,	// 처리성공
	A0001_		 = ('A' <<16) +   1,	// 처리중(처리결과조회 요망, 이체시)
	A0002_		 = ('A' <<16) +   2,	// 참가기관 에러
	A0003_		 = ('A' <<16) +   3,	// 내부 처리 에러
	A0004_		 = ('A' <<16) +   4,	// 요청전문 포맷 에러
	A0005_		 = ('A' <<16) +   5,	// 등록 데이터 에러
	A0006_		 = ('A' <<16) +   6,	// 전문 변환 에러
	A0007_		 = ('A' <<16) +   7,	// 처리시간 초과 에러
	A0008_		 = ('A' <<16) +   8,	// 중복거래 에러
	A0009_		 = ('A' <<16) +   9,	// API 세부업무 처리실패(리스트 건별 처리결과 확인)
	A0010_		 = ('A' <<16) +  10,	// 이용기관 APP 저어보 확인 실패
	A0011_		 = ('A' <<16) +  11,	// 이용기관 API 사용권한 없음
	A0012_		 = ('A' <<16) +  12,	// API 정보 확인 실패
	A0013_		 = ('A' <<16) +  13,	// 이용기관 서비스 사용 불가
	A0014_		 = ('A' <<16) +  14,	// 탈퇴 회원
	A0015_		 = ('A' <<16) +  15,	// 시뮬레이션 응답전문 TIMEOUT
	A0016_		 = ('A' <<16) +  16,	// FLAT 전문 송신 실패
	A0017_		 = ('A' <<16) +  17,	// 
	A0018_		 = ('A' <<16) +  18,	// 거래내역 없음

	A0101_		 = ('A' <<16) + 101,	// 이용기관 입금이체 한도 초과(일 한도)
	A0102_		 = ('A' <<16) + 102,	// 이용기관 입금이체 한도 초과(월 한도)
	A0103_		 = ('A' <<16) + 103,	// 이용기관 출금이체 한도 초과(일 한도)
	A0104_		 = ('A' <<16) + 104,	// 이용기관 출금이체 한도 초과(월 한도)
	A0105_		 = ('A' <<16) + 105,	// 이용기관 입금이체 한도 초과(건당 한도)
	A0106_		 = ('A' <<16) + 106,	// 이용기관 입금이체 한도 초과(건당 한도)
	A0111_		 = ('A' <<16) + 111,	// 사용자 출금이체 한도 초과(건당 한도)
	A0112_		 = ('A' <<16) + 112,	// 사용자 출금이체 한도 초과(일 한도)

	A0301_		 = ('A' <<16) + 301,	// 접근 권한 없음
	A0302_		 = ('A' <<16) + 302,	// 참가기관 API 이용권한 없음
	A0303_		 = ('A' <<16) + 303,	// 등록된 이용기관 수수료 정책 없음
	A0304_		 = ('A' <<16) + 304,	// 핀테크이용번호 정보 불일치
	A0305_		 = ('A' <<16) + 305,	// 제3자정보제공동의 미완료
	A0306_		 = ('A' <<16) + 306,	// 출금동의 미완료
	A0307_		 = ('A' <<16) + 307,	// 이체암호문구 불일치
	A0308_		 = ('A' <<16) + 308,	// 처리대행비용 할인대상 여부 없음
	A0309_		 = ('A' <<16) + 309,	// 등록된 이용기관 수수료 정보 없음
	A0310_		 = ('A' <<16) + 310,	// 이체 내역 없음
	A0311_		 = ('A' <<16) + 311,	// 등록된 처리대행 수수료 정보 없음
	A0312_		 = ('A' <<16) + 312,	// 예금주명 불일치
	A0313_		 = ('A' <<16) + 313,	// 사용자 불일치
	A0314_		 = ('A' <<16) + 314,	// 계좌이동 중
	A0315_		 = ('A' <<16) + 315,	// 농협중앙회(단위농축협) 계좌번호를 입력했을 경우 오류 처리

	O0001_		 = ('O' <<16) +   1,	// 인증요청 거부-인증 파라미터 오류([error_code])
	O0002_		 = ('O' <<16) +   2,	// Access Token 거부
	O0003_		 = ('O' <<16) +   3,	// Access Token 만료
	O0004_		 = ('O' <<16) +   4,	// API 접근권한이 없음.(API 서비스를 신청하지 않았을 때)
	O0005_		 = ('O' <<16) +   5,	// 허용되지 않은 API 접근 입니다.(API 서비스가 없을 때)
	O0006_		 = ('O' <<16) +   6,	// 허용되지 않은 IP입니다.
	O0007_		 = ('O' <<16) +   7,	// API를 요청 또는 처리할 수 없습니다.(API 업무처리 Routing 실패 시)
	O0008_		 = ('O' <<16) +   8,	// Object plan 사용량 한도 초과
	O0009_		 = ('O' <<16) +   9,	// API plan 사용량 한도 초과.
	O0010_		 = ('O' <<16) +  10,	// 허용되지 않은 http method 입니다.


	SUCCEESS_	 = A0000_,				// 처리성공
	FAIL_		 = ('X' <<16) +   0,	// 처리내부적 오류
};

// ---------------------------------------------------------------------------------
// 별첨4) API 인증요청 거부(O0001)에 대한 세부 응답코드(error_code)
// ---------------------------------------------------------------------------------
//
//	     992	Validation error						http header에 Authorization Bearer access_token이 없을 때
//
//   3000103	Missing or duplicate parameters			인증에 필요한 필수 파라미터 값이 존재하지 않을 때 or 특정 파라미터 값이 중복으로 들어왔을 때
//   
//   3000201	The given client credentials 			client_id가 존재하지 않을 때 or 비활성화 되어 사용할 수 없을 때
//	  			were not valid
//   3000114	Mismatching redirect_uri				등록한 callback url과 요청한 callback url이 맞지 않을 때
//   
//   3000115	No registered scope value for			scope가 맞지 않을 때
//	  			this client has been requested
//   3000116	None of the supported response_types	response_type이 유형이 맞지 않을 때
//	  			were used
//   3002110	The session has expired or aleady		만료된 session 값을 사용하였을 때
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

	// 1) 계산한다.
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

	// 1) 먼저 WideChar로 변환한다.
	auto	size_length = MultiByteToWideChar(CP_UTF8, 0, _source.data(), -1, temp_dest, ISIZE);

	// 2) WidtChar를 Multibyte로 변환한다.
	size_length = WideCharToMultiByte(CP_ACP, 0, temp_dest, -1, _dest._get_ptr_first(), ISIZE, nullptr, nullptr);

	// 3) shared_buffer의 크기를 설정
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

	// 1) 먼저 WideChar로 변환한다.
	auto size_length = MultiByteToWideChar(CP_UTF8, 0, _source.data(), -1, temp_dest, ISIZE);

	// 2) WidtChar를 Multibyte로 변환한다.
	size_length = WideCharToMultiByte(CP_ACP, 0, temp_dest, -1, temp_dest_2, ISIZE, nullptr, nullptr);

	// 3) shared_buffer의 크기를 설정
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

	// 1) 먼저 WideChar로 변환한다.
	auto size_length = MultiByteToWideChar(CP_ACP, 0, _source_multibytes.data(), -1, temp_dest, 512);

	// 2) WidtChar를 Multibyte로 변환한다.
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