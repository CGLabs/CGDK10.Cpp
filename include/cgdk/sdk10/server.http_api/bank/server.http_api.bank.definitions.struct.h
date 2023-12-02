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

namespace CGDK::http_api::bank
{
	
//-----------------------------------------------------------------------------
//
// Bank authorize
//
// ----------------------------------------------------------------------------
struct REQUEST_AUTHORIZE : public query::REQUEST
{
public:
	static_string<64>			client_id;
	static_string<256>			redirect_uri;
	static_string<256>			client_info;
};


struct _REQUEST_AUTHORIZE2 : public query::REQUEST
{
public:
	// 1) Essencial
	static_string<64>			client_id;
	static_string<256>			redirect_uri;
	eOAUTH_SCOPE				scope {eOAUTH_SCOPE::NOT_DEFINED_ };
	static_string<256>			client_info;

	// 2) Optional 1
	uint32_t					bg_color	{0x00000000};
	uint32_t					text_color	{0x00000000};
	uint32_t					btn1_color	{0x00000000};
	uint32_t					btn2_color	{0x00000000};
};

struct RESPONSE_AUTHORIZE : public query::RESPONSE
{
public:
	static_string<256>			code;
	eOAUTH_SCOPE				scope;
	static_string<256>			client_info;
};

struct RESPONSE_AUTHORIZE2 : public query::RESPONSE
{
public:
	static_string<64>			access_token;		// 오픈플랫폼에서 발행된 access_token
	eOAUTH_TOKEN_TYPE			token_type;			// access_token 유형
	uint64_t					expires_in;			// 토큰 만료기간
	static_string<64>			refresh_token;		// acccess_token 갱신시 사용하는 refresh_token;
	eOAUTH_SCOPE				scope;				// Access Token 권한 범위 - multi scope 가능 ex) login inquiry transfer
	static_string<64>			user_seq_no;		// 사용자 일련번호

	static_string<64>			user_ci;			// (선택) ex) ""Dqz4/7Rp .... UjVj32XFJTV=="
	static_string<64>			user_name;			// (선택) ex) "오픈원"
	static_string<256>			user_info;			// (선택) ex) "19810101"
	eOAUTH_GENDER				user_gender;		// (선택) ex) "M" or "W"
	static_string<64>			user_cell_no;		// (선택) ex) "01012341234"
	static_string<64>			user_email;			// (선택) ex) "testbed@kftc.or.kr"
};


//-----------------------------------------------------------------------------
//
// oauth/2.0/authorize2 - 최초인증
//
// ----------------------------------------------------------------------------
struct REQUEST_AUTHORIZE2_FIRST : public _REQUEST_AUTHORIZE2
{

};

struct RESPONSE_AUTHORIZE2_FIRST : public query::RESPONSE
{

};


//-----------------------------------------------------------------------------
//
// oauth/2.0/authorize2 - 재인증
//
// ----------------------------------------------------------------------------
struct REQUEST_AUTHORIZE2_REAUTH : public _REQUEST_AUTHORIZE2
{
public:
	int64_t						Kftc_Bfop_UserSeqNo;
	static_string<64>			Kftc_Bfop_UserCI;
	static_string<64>			Kftc_Bfop_UserName;
	static_string<64>			Kftc_Bfop_UserInfo;
	static_string<64>			Kftc_Bfop_UserCellNo;
	static_string<64>			Kftc_Bfop_UserEmail;
	eOAUTH_BANK_CODE			Kftc_Bfop_BankCodeStd;
	static_string<64>			Kftc_Bfop_AccountNum;
};

struct RESPONSE_AUTHORIZE2_REAUTH : public query::RESPONSE
{

};


//-----------------------------------------------------------------------------
//
// oauth/2.0/authorize2 - 인증생략
//
// ----------------------------------------------------------------------------
struct REQUEST_AUTHORIZE2_AUTH_BYPASS : public _REQUEST_AUTHORIZE2
{
public:
	int64_t						Kftc_Bfop_UserSeqNo;
	static_string<64>			Kftc_Bfop_UserCI;
	static_string<64>			Kftc_Bfop_AccessToken;
};

struct RESPONSE_AUTHORIZE2_AUTH_BYPASS : public query::RESPONSE
{

};


//-----------------------------------------------------------------------------
//
// OAuth 인증 - 사용자 Access Token 획득 (3-legged)
// oauth/2.0/token
//
// ----------------------------------------------------------------------------
struct REQUEST_TOKEN : public query::REQUEST
{
public:
	// 1) ...
	static_string<64>			code;
	static_string<64>			client_id;
	static_string<64>			client_secret;
	static_string<64>			redirect_uri;
};

struct RESPONSE_TOKEN : public query::RESPONSE
{
public:
	static_string<64>			access_token;
	eOAUTH_TOKEN_TYPE			token_type;
	uint64_t					expires_in;
	static_string<64>			refresh_token;
	eOAUTH_SCOPE				scope;
	static_string<64>			user_seq_no;

	static_string<64>			user_ci;
	static_string<64>			user_name;
	static_string<64>			user_info;
	eOAUTH_GENDER				user_gender;
	static_string<64>			user_cell_no;
	static_string<64>			user_email;
};


//-----------------------------------------------------------------------------
//
// OAuth 인증 - 사용자 Access Token 획득 (2-legged)
// oauth/2.0/token
//
// ----------------------------------------------------------------------------
struct REQUEST_TOKEN2 : public query::REQUEST
{
public:
	// 1) ...
	static_string<64>			client_id;
	static_string<64>			client_secret;
};

struct RESPONSE_TOKEN2 : public query::RESPONSE
{
	static_string<64>			access_token;
	eOAUTH_TOKEN_TYPE			token_type;
	uint64_t					expires_in;
	eOAUTH_SCOPE				scope;
	static_string<64>			client_use_code;
};


//-----------------------------------------------------------------------------
//
// OAuth 인증 - Login Access Token 갱신/(refresh_token)
// oauth/2.0/token
//
// ----------------------------------------------------------------------------
struct REQUEST_TOKEN_REFRESH : public query::REQUEST
{
public:
	// 1) ...
	static_string<64>			client_id;
	static_string<64>			client_secret;
	static_string<64>			refresh_token;
	eOAUTH_SCOPE				scope {eOAUTH_SCOPE::NOT_DEFINED_ };
};

struct RESPONSE_TOKEN_REFRESH : public query::RESPONSE
{
	static_string<64>			access_token;
	eOAUTH_TOKEN_TYPE			token_type;
	int64_t						expires_in;
	eOAUTH_SCOPE				scope;
	static_string<64>			user_seq_no;
};


//-----------------------------------------------------------------------------
//
// OAuth 사용자 정보 조회
// oauth/2.0/token
//
// ----------------------------------------------------------------------------
struct REQUEST_USER_ME : public query::REQUEST
{
public:
	static_string<64>				authorization;
	static_string<64>				user_seq_no;
};

struct RESPONSE_USER_ME : public query::RESPONSE
{
public:
	static_string<64>				api_tran_id;
	chrono::date_time				api_tran_dtm;
	static_string<64>				user_seq_no;
	static_string<64>				user_ci;
	static_string<64>				user_name;

	struct ACCOUNT_INFO
	{
	public:
		static_string<64>				fintech_use_num;
		static_string<64>				account_alias;
		eOAUTH_BANK_CODE				bank_code_std;
		int64_t							bank_code_sub;
		static_string<64>				bank_name;
		static_string<64>				account_num_masked;
		static_string<64>				account_holder_name;
		static_string<64>				account_type;
		eOAUTH_YESNO					inquiry_agree_yn;
		chrono::date_time				inquiry_agree_dtime;
		eOAUTH_YESNO					transfer_agree_yn;
		chrono::date_time				transfer_agree_dtime;
	};

	std::vector<ACCOUNT_INFO>		res_list;
};


//-----------------------------------------------------------------------------
//
// OAuth 사용자로그인연결 동의해제 API
// oauth/2.0/token
//
// ----------------------------------------------------------------------------
struct REQUEST_UNLINK : public query::REQUEST
{
public:
	static_string<64>				authorization;

	static_string<64>				client_use_code;
	static_string<64>				user_seq_no;
};

struct RESPONSE_UNLINK : public query::RESPONSE
{
	static_string<64>				api_tran_id;
	chrono::date_time				api_tran_dtm;
	static_string<64>				user_seq_no;
};


//-----------------------------------------------------------------------------
//
// OAuth 사용자로그인연결 동의해제 API
// oauth/2.0/token
//
// ----------------------------------------------------------------------------
struct REQUEST_REGISTER_ACCOUNT : public query::REQUEST
{
public:
	static_string<64>			client_id;
	static_string<64>			redirect_uri;
	eOAUTH_SCOPE				scope{ eOAUTH_SCOPE::NOT_DEFINED_ };
	static_string<256>			client_info;
};

struct RESPONSE_REGISTER_ACCOUNT : public query::RESPONSE
{

};


//-----------------------------------------------------------------------------
//
// 계좌등록
// oauth/2.0/token
//
// ----------------------------------------------------------------------------
struct REQUEST_AUTHORIZE_ACCOUNT : public REQUEST_AUTHORIZE
{
public:
	eOAUTH_SCOPE				scope{ eOAUTH_SCOPE::NOT_DEFINED_ };
};

struct RESPONSE_AUTHORIZE_ACCOUNT : public query::RESPONSE
{
};


//-----------------------------------------------------------------------------
//
// OAuth - 계좌등록확인 요청 (3-legged)
// oauth/2.0/authorize_account
//
// ----------------------------------------------------------------------------
struct REQUEST_AUTHORIZE_ACCOUNT2_FIRST : public _REQUEST_AUTHORIZE2
{
};

struct RESPONSE_AUTHORIZE_ACCOUNT2_FIRST : public query::RESPONSE
{

};


//-----------------------------------------------------------------------------
//
// OAuth - 계좌등록확인 요청 (3-legged)
// oauth/2.0/authorize_account2
//
// ----------------------------------------------------------------------------
struct REQUEST_AUTHORIZE_ACCOUNT2_REAUTH : public _REQUEST_AUTHORIZE2
{
public:
	int64_t						Kftc_Bfop_UserSeqNo;
	static_string<64>			Kftc_Bfop_UserCI;
	static_string<64>			Kftc_Bfop_UserName;
	static_string<64>			Kftc_Bfop_UserInfo;
	static_string<64>			Kftc_Bfop_UserCellNo;
	static_string<64>			Kftc_Bfop_UserEmail;
	eOAUTH_BANK_CODE			Kftc_Bfop_BankCodeStd;
	static_string<64>			Kftc_Bfop_AccountNum;
};

struct RESPONSE_AUTHORIZE_ACCOUNT2_REAUTH : public query::RESPONSE
{

};


//-----------------------------------------------------------------------------
//
// OAuth - 계좌등록확인 요청 (3-legged)
// oauth/2.0/authorize_account2
//
// ----------------------------------------------------------------------------
struct REQUEST_AUTHORIZE_ACCOUNT2_BYPASS : public _REQUEST_AUTHORIZE2
{
public:
	int64_t						Kftc_Bfop_UserSeqNo;
	static_string<64>			Kftc_Bfop_UserCI;
	static_string<64>			Kftc_Bfop_AccessToken;
};

struct RESPONSE_AUTHORIZE_ACCOUNT2_BYPASS : public query::RESPONSE
{

};


//-----------------------------------------------------------------------------
//
// OAuth - 계좌등록확인 요청 (3-legged)
// oauth/2.0/authorize_account2
//
// ----------------------------------------------------------------------------
struct REQUEST_ACCOUNT_LIST : public query::REQUEST
{
public:
	static_string<64>				authorization;

	static_string<64>				user_seq_no;
	eOAUTH_YESNO					include_cancel_yn	{eOAUTH_YESNO::NOT_DEFINED_};
	eOAUTH_SORT_ORDER				sort_order			{eOAUTH_SORT_ORDER::NOT_DEFINED_};
};

struct RESPONSE_ACCOUNT_LIST : public query::RESPONSE
{
public:
	static_string<64>				api_tran_id;
	chrono::date_time				api_tran_dtm;
	static_string<64>				user_name;

	struct ACCOUNT_INFO
	{
	public:
		static_string<64>				fintech_use_num;
		static_string<64>				account_alias;
		eOAUTH_BANK_CODE				bank_code_std;
		int64_t							bank_code_sub;
		static_string<64>				bank_name;
		static_string<64>				account_num_masked;
		static_string<64>				account_holder_name;
		static_string<64>				account_type;
		eOAUTH_YESNO					inquiry_agree_yn;
		chrono::date_time				inquiry_agree_dtime;
		eOAUTH_YESNO					transfer_agree_yn;
		chrono::date_time				transfer_agree_dtime;
		static_string<64>				account_state;
	};

	std::vector<ACCOUNT_INFO>			res_list;
};



//-----------------------------------------------------------------------------
//
// 계좌정보변경 - 변경된 계좌의 정보를 수정합니다.
// oauth/2.0/authorize_account2
//
// ----------------------------------------------------------------------------
struct REQUEST_ACCOUNT_UPDATE_INFO : public query::REQUEST
{
public:
	static_string<64>				authorization;

	static_string<64>				fintech_use_num;
	static_string<64>				account_alias;
};

struct RESPONSE_ACCOUNT_UPDATE_INFO : public query::RESPONSE
{
public:
	static_string<64>				api_tran_id;
	chrono::date_time				api_tran_dtm;
	static_string<64>				fintech_use_num;
	static_string<64>				account_alias;
};


//-----------------------------------------------------------------------------
//
// 계좌해지
// oauth/2.0/authorize_account2
//
// ----------------------------------------------------------------------------
struct REQUEST_ACCOUNT_CANCEL : public query::REQUEST
{
public:
	static_string<64>				authorization;

	eOAUTH_SCOPE					scope;
	static_string<64>				fintech_use_num;
};

struct RESPONSE_ACCOUNT_CANCEL : public query::RESPONSE
{
public:
	static_string<64>				api_tran_id;
	chrono::date_time				api_tran_dtm;
	static_string<64>				bank_tran_id;
	chrono::date_time				bank_tran_date;
	static_string<64>				bank_code_tran;
	eOAUTH_BANK_CODE				bank_rsp_code;
	static_string<64>				bank_rsp_message;
};


//-----------------------------------------------------------------------------
//
// 잔액조회
// oauth/2.0/authorize_account2
//
// ----------------------------------------------------------------------------
struct REQUEST_ACCOUNT_BALANCE : public query::REQUEST
{
public:
	static_string<64>				authorization;

	static_string<64>				fintech_use_num;
	chrono::date_time				tran_dtime;					//  N(14) 요청일시
};

struct RESPONSE_ACCOUNT_BALANCE : public query::RESPONSE
{
public:
	static_string<64>				api_tran_id;
	chrono::date_time				api_tran_dtm;
	static_string<64>				bank_tran_id;
	chrono::date_time				bank_tran_date;
	static_string<64>				bank_code_tran;
	eOAUTH_BANK_CODE				bank_rsp_code;
	static_string<64>				bank_rsp_message;
	static_string<64>				fintech_use_num;
	int64_t							balance_amt{ 0 };
	int64_t							available_amt{ 0 };
	eOAUTH_ACCOUNT_TYPE				account_type;
	static_string<64>				product_name;
};


//-----------------------------------------------------------------------------
//
// 거래내역조회
// oauth/2.0/authorize_account2
//
// ----------------------------------------------------------------------------
struct REQUEST_ACCOUNT_TRANSACTION_LIST : public query::REQUEST
{
public:
	static_string<64>				authorization;

	static_string<64>				fintech_use_num;
	eOAUTH_INQUIRY_TYPE				inquiry_type;
	chrono::date_time				from_time;
	chrono::date_time				to_time;
	eOAUTH_SORT_ORDER				sort_order{ eOAUTH_SORT_ORDER::NOT_DEFINED_};
	uint32_t						page_index;
	uint64_t						before_inquiry_trace_info;
	uint64_t						list_tran_seqno;
	chrono::date_time				tran_dtime;
};

struct RESPONSE_ACCOUNT_TRANSACTION_LIST : public query::RESPONSE
{
public:
	static_string<64>				api_tran_id;				// 거래고유번호(API)
	chrono::date_time				api_tran_dtm;				// 거래일시(밀리세컨드)
	static_string<64>				bank_tran_id;				// 거래고유번호(참가기관)
	chrono::date_time				bank_tran_date;				// 거래일자(참가기관)
	static_string<64>				bank_code_tran;				// 응답코드를 부여한 참가기관 표준코드
	eOAUTH_BANK_CODE				bank_rsp_code;				// 응답코드(참가기관)
	static_string<64>				bank_rsp_message;			// 응답메시지(참가기관)
	static_string<64>				fintech_use_num;			// 핀테크이용번호
	int64_t							balance_amt{ 0 };			// 계좌잔액(-금액가능)

	eOAUTH_YESNO					page_index_use_yn;			// 페이지 Index 사용여부
	int64_t							page_index;					// 페이지 번호
	int64_t							total_record_cnt;			// 총 조회건수
	int64_t							page_record_cnt;			// 현재페이지 레코드 건수
	eOAUTH_YESNO					next_page_yn;				// 다음페이지 존재여부

	static_string<64>				befor_inquiry_trace_info;	// 직전 조회 추적 정보
	static_string<64>				list_tran_seqno;			// 최종거래내역 순번

	struct TRANSACTION
	{
		chrono::date_time				tran_date;				// 거래일자
		chrono::date_time				tran_time;				// 거래시간
		eOAUTH_INOUT_TYPE				inout_type;				// 입출금구분("입금", "출금")
		static_string<64>				tran_type;				// 거래구분
		static_string<64>				print_content;			// 통장인자내용
		int64_t							tran_amt{ 0 };			// 거래금액
		int64_t							after_balance_amt{ 0 };	// 거래후 잔액
		static_string<64>				branch_name;			// 거래점명
	};

	std::vector<TRANSACTION>			res_list;

};


//-----------------------------------------------------------------------------
//
// 출금이체
// oauth/2.0/authorize_account2
//
// ----------------------------------------------------------------------------
struct REQUEST_TRANSFER_WITHDRAW : public query::REQUEST
{
public:
	static_string<64>				authorization;		// 계좌등록시 오픈플랫폼으로부터 전송받은 access_token

	static_string<64>				dps_print_content;	// 입금계좌인자내역
	static_string<64>				fintech_use_num;	// 출금계좌핀테크이용번호
	int64_t							tran_amt{ 0 };		// 거래금액
	chrono::date_time				tran_dtime;			// 요청일시
};

struct RESPONSE_TRANSFER_WITHDRAW : public query::RESPONSE
{
	static_string<64>				api_tran_id;				// 거래고유번호(API)
	chrono::date_time				api_tran_dtm;				// 거래일시(밀리세컨드)
	eOAUTH_BANK_CODE				dps_bank_code_std;			// 입금기관.표준코드
	int64_t							dps_bank_code_sub;			// 입금기관.점별코드
	static_string<64>				dps_bank_name;				// 입금기관명
	static_string<64>				dps_account_num_masked;		// 입금계좌번호(출력용)
	static_string<64>				dps_print_content;			// 입금계좌인자내역
	static_string<64>				dps_account_holder_name;	// 수최인성명
	static_string<64>				bank_tran_id;				// 거래고유번호(참가기관)
	chrono::date_time				bank_tran_date;				// 거래일자(참가기관)
	static_string<64>				bank_code_tran;				// 응답코드를 부여한 참가기관 표준코드
	eOAUTH_BANK_CODE				bank_rsp_code;				// 응답코드(참가기관)
	static_string<64>				bank_rsp_message;			// 응답메시지(참가기관)
	static_string<64>				fintech_use_num;			// 핀테크이용번호
	static_string<64>				account_alias;				// 출금계좌별명(Alias)
	eOAUTH_BANK_CODE				bank_code_std;				// 출금(계설)기관.표준코드
	int64_t							bank_code_sub;				// 출금(계설)기관.점별코드
	static_string<64>				bank_name;					// 출금(계설)기관명
	static_string<64>				account_num_masked;			// 출금계좌번호(출력용)
	static_string<64>				print_content;				// 출금계좌인자내역
	static_string<64>				account_holder_name;		// 송금인성명
	int64_t							tran_amt{ 0 };				// 거래금액
};


//-----------------------------------------------------------------------------
//
// 입금이체
// oauth/2.0/authorize_account2
//
// ----------------------------------------------------------------------------
struct REQUEST_TRANSFER_DEPOSIT : public query::REQUEST
{
public:
	static_string<64>				authorization;		// 계좌등록시 오픈플랫폼으로부터 전송받은 access_token

	static_string<64>				wd_pass_phrase;		// 이용기관 입금이체용 암호무누구
	static_string<64>				wd_print_content;	// 출금계좌인자내역
	int								req_cnt{ 0 };		// 입금요청건수(req_cnt)

	struct DEPOSIT
	{
	public:
		int							tran_no{ 0 };		// 거래순번
		static_string<64>			fintech_use_num;	// 출금계좌핀테크이용번호
		static_string<64>			print_content;		// 입금계좌인자내역
		int64_t						tran_amt{ 0 };		// 거래금액
	};
														// 입금요청건수 (req_cnt)
	std::vector<DEPOSIT>			req_list;			// 입금요청목록
	chrono::date_time				tran_dtime;			// 요청일시
};

struct RESPONSE_TRANSFER_DEPOSIT : public query::RESPONSE
{
	static_string<64>				api_tran_id;				// 거래고유번호(API)
	chrono::date_time				api_tran_dtm;				// 거래일시(밀리세컨드)

	eOAUTH_BANK_CODE				wd_bank_code_std;			// 입금기관.표준코드
	int64_t							wd_bank_code_sub;			// 입금기관.점별코드
	static_string<64>				wd_bank_name;				// 입금기관명
	static_string<64>				wd_account_num_masked;		// 입금계좌번호(출력용)
	static_string<64>				wd_print_content;			// 입금계좌인자내역
	static_string<64>				wd_account_holder_name;		// 수최인성명

	struct TRANSACTION
	{
		int								tran_no{ 0 };			// 거래순번
		static_string<64>				bank_tran_id;			// 거래고유번호(참가기관)
		chrono::date_time				bank_tran_date;			// 거래일자(참가기관)
		static_string<64>				bank_code_tran;			// 응답코드를 부여한 참가기관.표준코드
		eOAUTH_BANK_CODE				bank_rsp_code;			// 응답코드(참가기관)
		static_string<64>				bank_rsp_message;		// 응답메시지(참가기관)
		static_string<64>				fintech_use_num;		// 핀테크이용번호
		static_string<64>				account_alias;			// 계좌별명
		eOAUTH_BANK_CODE				bank_code_std;			// 입금(개설)기관.표준코드
		int64_t							bank_code_sub;			// 입금(개설)기관.점별코드
		static_string<64>				bank_name;				// 입금(개설)기관명
		static_string<64>				account_num_masked;		// 입금계좌번호(출력용)
		static_string<64>				print_content;			// 입금계좌 인자내역
		static_string<64>				account_holder_name;	// 수취인 성명
		int64_t							tran_amt{ 0 };			// 거래금액
	};

	std::vector<TRANSACTION>			res_list;
};


//-----------------------------------------------------------------------------
//
// 입금이체 - 계좌번호 사용
// 
//  - HTTP URL      https://openapi.open-platform.or.kr/v1.0/transfer/deposit2
//  - HTTP Method   POST
//  - Content-Type  application/json; charset=UTF-8
//
// ----------------------------------------------------------------------------
struct REQUEST_TRANSFER_DEPOSIT2 : public query::REQUEST
{
public:
	static_string<64>				authorization;			// 계좌등록시 오픈플랫폼으로부터 전송받은 access_token

	static_string<64>				wd_pass_phrase;			// 이용기관 입금이체용 암호무누구
	static_string<64>				wd_print_content;		// 출금계좌인자내역
	int								req_cnt{ 0 };			// 입금요청건수(req_cnt)

	struct TRANSACTION
	{
		int							tran_no{ 0 };			// 거래순번
		eOAUTH_BANK_CODE			bank_code_std{ 0 };		// 입금은행.표준코드
		static_string<64>			accoount_num;			// 입금계좌번호
		static_string<64>			account_holder_name;	// 입금계좌예금주명
		static_string<64>			print_content;			// 입금계좌인자내역
		int64_t						tran_amt{ 0 };			// 거래금액
	};
															// 입금요청건수 (req_cnt)
	std::vector<TRANSACTION>		req_list;				// 입금요청목록
	chrono::date_time				tran_dtime;				// 요청일시
};

struct RESPONSE_TRANSFER_DEPOSIT2 : public query::RESPONSE
{
	static_string<64>				api_tran_id;				// 거래고유번호(API)
	chrono::date_time				api_tran_dtm;				// 거래일시(밀리세컨드)

	eOAUTH_BANK_CODE				wd_bank_code_std;			// 입금기관.표준코드
	int64_t							wd_bank_code_sub;			// 입금기관.점별코드
	static_string<64>				wd_bank_name;				// 입금기관명
	static_string<64>				wd_account_num_masked;		// 입금계좌번호(출력용)
	static_string<64>				wd_print_content;			// 입금계좌인자내역
	static_string<64>				wd_account_holder_name;		// 수최인성명

	struct TRANSACTION
	{
		int								tran_no{ 0 };			// 거래순번
		static_string<64>				bank_tran_id;			// 거래고유번호(참가기관)
		chrono::date_time				bank_tran_date;			// 거래일자(참가기관)
		static_string<64>				bank_code_tran;			// 응답코드를 부여한 참가기관.표준코드

		eOAUTH_BANK_CODE				bank_rsp_code;			// 응답코드(참가기관)
		static_string<64>				bank_rsp_message;		// 응답메시지(참가기관)
		eOAUTH_BANK_CODE				bank_code_std;			// 입금(개설)기관.표준코드
		int64_t							bank_code_sub;			// 입금(개설)기관.점포코드
		static_string<64>				bank_name;				// 입금(개설)기관명
		static_string<64>				account_num;			// 입금계좌번호
		static_string<64>				account_num_masked;		// 입금계좌번호(출력용)
		static_string<64>				print_content;			// 입금계좌인자내역
		static_string<64>				account_holder_name;	// 수취인성명
		static_string<64>				tran_amt;				// 거래금액
	};

	std::vector<TRANSACTION>			res_list;
};


//-----------------------------------------------------------------------------
//
// 이체결과조회
// 
//  - HTTP URL      https://openapi.open-platform.or.kr/v1.0/transfer/result
//  - HTTP Method   POST
//  - Content-Type  application/json; charset=UTF-8
//
// ----------------------------------------------------------------------------
struct REQUEST_TRANSFER_RESULT : public query::REQUEST
{
public:
	static_string<64>				authorization;			// 계좌등록시 오픈플랫폼으로부터 전송받은 access_token

	eOAUTH_CHECK_TYPE				check_type;				// 1:출금이체, 2:입금이체
	int								req_cnt{ 0 };			// 요청건수(req_cnt)

	struct TRANSACTION
	{
	public:
		int								tran_no{ 0 };		// 거래순번
		static_string<64>				org_bank_tran_id;	// 원거래 거래고유번호(참가기관)
		chrono::date_time				org_bank_tran_date;	// 원거래 거래일(참가기관)
		int64_t							org_tran_amt{ 0 };	// 원거래 거래금액
	};
															// 요청건수 (req_cnt)
	std::vector<TRANSACTION>		req_list;				// 요청목록

	chrono::date_time				tran_dtime;				// 요청일시
};

struct RESPONSE_TRANSFER_RESULT : public query::RESPONSE
{
	static_string<64>				api_tran_id;			// 거래고유번호(API)
	chrono::date_time				api_tran_dtm;			// 거래일시(밀리세컨드)

	struct TRANSACTION
	{
		int								tran_no{ 0 };			// 거래순번

		static_string<64>				bank_tran_id;			// 거래고유번호(참가기관)
		chrono::date_time				bank_tran_date;			// 거래일자(참가기관)
		static_string<64>				bank_code_tran;			// 응답코드를 부여한 참가기관.표준코드
		eOAUTH_BANK_CODE				bank_rsp_code;			// 응답코드(참가기관)
		static_string<64>				bank_rsp_message;		// 응답메시지(참가기관)

		eOAUTH_BANK_CODE				wd_bank_code_std;		// 출금(개설)기관.표준코드
		int64_t							wd_bank_code_sub;		// 출금(개설)기관.점포코드
		static_string<64>				wd_bank_name;			// 출금(개설)기관명
		static_string<64>				wd_fintech_use_num;		// 출금계좌 핀테크이용번호
		static_string<64>				wd_account_num_masked;	// 출금계좌번호(출력용)
		static_string<64>				wd_print_content;		// 출금계좌인자내역
		static_string<64>				wd_account_holder_name;	// 송금인성명

		eOAUTH_BANK_CODE				dps_bank_code_std;		// 입금(개설)기관.표준코드
		int64_t							dps_bank_code_sub;		// 입금(개설)기관.점포코드
		static_string<64>				dps_bank_name;			// 입금(개설)기관명
		static_string<64>				dps_fintech_use_num;	// 입금계좌 핀테크이용번호
		static_string<64>				dps_account_num_masked;	// 입금계좌번호(출력용)
		static_string<64>				dps_print_content;		// 입금계좌인자내역
		static_string<64>				dps_account_holder_name;// 입금인성명

		int64_t							tran_amt{ 0 };			// 거래금액
	};

	std::vector<TRANSACTION>			res_list;
};


//-----------------------------------------------------------------------------
//
// 이체API처리조회
// 
//  - HTTP URL      https://openapi.open-platform.or.kr/v1.0/transfer/recheck
//  - HTTP Method   POST
//  - Content-Type  application/json; charset=UTF-8
//
// ----------------------------------------------------------------------------
struct REQUEST_TRANSFER_RECHECK : public query::REQUEST
{
public:
	static_string<64>				authorization;										// 계좌등록시 오픈플랫폼으로부터 전송받은 access_token

	eOAUTH_CHECK_TYPE				check_type;											// 1:출금이체, 2:입금이체
	int								req_cnt{ 0 };										// 요청건수(req_cnt)

	struct TRNASACTION
	{
	public:
		int								tran_no{ 0 };									// 거래순번
		chrono::date_time				org_tran_dtime;									// 원거래요청일시
		eOAUTH_ORG_REQ_GUBUN			org_req_gubun{ eOAUTH_ORG_REQ_GUBUN::NOT_DEFINED_ };	// 원거래요청계좌지정방식구분 (1:핀테크이용번호, 2:계좌번호)
		eOAUTH_BANK_CODE				bank_code_std{ 0 };								// 원거래 은행 대표코드
		static_string<64>				accoount_num;									// 원거래 입출금계좌번호
		static_string<64>				print_content;									// 원거래 입출금계좌인자내역
		static_string<64>				fintech_use_num;								// 원거래 입출금핀테크이용번호
		int64_t							org_tran_amt{ 0 };								// 원거래 거래금액
	};

	std::vector<TRNASACTION>		req_list;											// 요청건수(req_cnt), 요청목록(req_list)
	chrono::date_time				tran_dtime;											// 요청일시
};

struct RESPONSE_TRANSFER_RECHECK : public query::RESPONSE
{
	static_string<64>				api_tran_id;				// 거래고유번호(API)
	chrono::date_time				api_tran_dtm;				// 거래일시(밀리세컨드)

	struct TRANSACTION
	{
		int								tran_no{ 0 };			// 거래순번

		static_string<64>				bank_tran_id;			// 거래고유번호(참가기관)
		chrono::date_time				bank_tran_date;			// 거래일자(참가기관)
		static_string<64>				bank_code_tran;			// 응답코드를 부여한 참가기관.표준코드
		eOAUTH_BANK_CODE				bank_rsp_code;			// 응답코드(참가기관)
		static_string<64>				bank_rsp_message;		// 응답메시지(참가기관)

		eOAUTH_BANK_CODE				wd_bank_code_std;		// 출금(개설)기관.표준코드
		int64_t							wd_bank_code_sub;		// 출금(개설)기관.점포코드
		static_string<64>				wd_bank_name;			// 출금(개설)기관명
		static_string<64>				wd_fintech_use_num;		// 출금계좌 핀테크이용번호
		static_string<64>				wd_account_num_masked;	// 출금계좌번호(출력용)
		static_string<64>				wd_print_content;		// 출금계좌인자내역
		static_string<64>				wd_account_holder_name;	// 송금인성명

		eOAUTH_BANK_CODE				dps_bank_code_std;		// 입금(개설)기관.표준코드
		int64_t							dps_bank_code_sub;		// 입금(개설)기관.점포코드
		static_string<64>				dps_bank_name;			// 입금(개설)기관명
		static_string<64>				dps_fintech_use_num;	// 입금계좌 핀테크이용번호
		static_string<64>				dps_account_num_masked;	// 입금계좌번호(출력용)
		static_string<64>				dps_print_content;		// 입금계좌인자내역
		static_string<64>				dps_account_holder_name;// 입금인성명

		int64_t							tran_amt{ 0 };			// 거래금액
	};

	std::vector<TRANSACTION>		res_list;
};


//-----------------------------------------------------------------------------
//
// 계좌실명조회 API
// 
//  - HTTP URL      https://openapi.open-platform.or.kr/v1.0/inquiry/real_name
//  - HTTP Method   POST
//  - Content-Type  application/json; charset=UTF-8
//
// ----------------------------------------------------------------------------
struct REQUEST_INQUIRY_REAL_NAME : public query::REQUEST
{
public:
	static_string<64>				authorization;				//        계좌등록시 오픈플랫폼으로부터 전송받은 access_token

	eOAUTH_BANK_CODE				bank_code_std {0};			// AN( 3) 원거래 은행 대표코드
	static_string<64>				accoount_num;				// AN(16) 계좌번호
	static_string<64>				accoount_holder_info;		// AN( 7) 예금주 인증정보 YYYYMMDD(6) + 식별번호(1)
	chrono::date_time				tran_dtime;					//  N(14) 요청일시
															
};

struct RESPONSE_INQUIRY_REAL_NAME : public query::RESPONSE
{
	static_string<64>				api_tran_id;				// 거래고유번호(API)
	chrono::date_time				api_tran_dtm;				// 거래일시(밀리세컨드)

	static_string<64>				bank_tran_id;				// 거래고유번호(참가기관)
	chrono::date_time				bank_tran_date;				// 거래일자(참가기관)
	static_string<64>				bank_code_tran;				// 응답코드를 부여한 참가기관.표준코드
	eOAUTH_BANK_CODE				bank_rsp_code;				// 응답코드(참가기관)
	static_string<64>				bank_rsp_message;			// 응답메시지(참가기관)
	eOAUTH_BANK_CODE				bank_code_std;				// 개설기관.표준코드
	int64_t							bank_code_sub;				// 개설기관.점포코드
	static_string<64>				bank_name;					// 개설기관명
	static_string<64>				account_num;				// 계좌번호
	static_string<64>				account_holder_info;		// 예금주정보
	static_string<64>				account_holder_name;		// 예금주성명
};


//-----------------------------------------------------------------------------
//
// 참가기관상태조회 API
// 
//  - HTTP URL      https://openapi.open-platform.or.kr/v1.0/bank/status
//  - HTTP Method   GET
//  - Content-Type  application/x-www-form-urlencoded; charset=UTF-8
//
// ----------------------------------------------------------------------------
struct REQUEST_BANK_STATUS : public query::REQUEST
{
public:
	static_string<64>				authorization;										//        계좌등록시 오픈플랫폼으로부터 전송받은 access_token
};

struct RESPONSE_BANK_STATUS : public query::RESPONSE
{
	static_string<64>				api_tran_id;										// AN( 20)	원거래 은행 대표코드
	chrono::date_time				api_tran_dtm;										//  N( 17)	계좌번호

	struct BANK_STATUS
	{
		eOAUTH_BANK_CODE				bank_code_std{ 0 };								// AN(  3)  참가기관.표준코드
		static_string<64>				bank_name;										// AH( 20)  참가기관명
		eOAUTH_BANK_STATUS				bank_status{ eOAUTH_BANK_STATUS::NOT_DEFINED_ };		// AN[  1]  참가기관상태 Y:거래가능, D:장애, L:개시이전, E:종류처리중.
	};

	std::vector<BANK_STATUS>		res_list;											//          참가기관목록(res_list)
};


}
