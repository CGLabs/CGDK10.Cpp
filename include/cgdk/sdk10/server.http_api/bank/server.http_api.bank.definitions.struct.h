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
	static_string<64>			access_token;		// �����÷������� ����� access_token
	eOAUTH_TOKEN_TYPE			token_type;			// access_token ����
	uint64_t					expires_in;			// ��ū ����Ⱓ
	static_string<64>			refresh_token;		// acccess_token ���Ž� ����ϴ� refresh_token;
	eOAUTH_SCOPE				scope;				// Access Token ���� ���� - multi scope ���� ex) login inquiry transfer
	static_string<64>			user_seq_no;		// ����� �Ϸù�ȣ

	static_string<64>			user_ci;			// (����) ex) ""Dqz4/7Rp .... UjVj32XFJTV=="
	static_string<64>			user_name;			// (����) ex) "���¿�"
	static_string<256>			user_info;			// (����) ex) "19810101"
	eOAUTH_GENDER				user_gender;		// (����) ex) "M" or "W"
	static_string<64>			user_cell_no;		// (����) ex) "01012341234"
	static_string<64>			user_email;			// (����) ex) "testbed@kftc.or.kr"
};


//-----------------------------------------------------------------------------
//
// oauth/2.0/authorize2 - ��������
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
// oauth/2.0/authorize2 - ������
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
// oauth/2.0/authorize2 - ��������
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
// OAuth ���� - ����� Access Token ȹ�� (3-legged)
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
// OAuth ���� - ����� Access Token ȹ�� (2-legged)
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
// OAuth ���� - Login Access Token ����/(refresh_token)
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
// OAuth ����� ���� ��ȸ
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
// OAuth ����ڷα��ο��� �������� API
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
// OAuth ����ڷα��ο��� �������� API
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
// ���µ��
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
// OAuth - ���µ��Ȯ�� ��û (3-legged)
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
// OAuth - ���µ��Ȯ�� ��û (3-legged)
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
// OAuth - ���µ��Ȯ�� ��û (3-legged)
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
// OAuth - ���µ��Ȯ�� ��û (3-legged)
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
// ������������ - ����� ������ ������ �����մϴ�.
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
// ��������
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
// �ܾ���ȸ
// oauth/2.0/authorize_account2
//
// ----------------------------------------------------------------------------
struct REQUEST_ACCOUNT_BALANCE : public query::REQUEST
{
public:
	static_string<64>				authorization;

	static_string<64>				fintech_use_num;
	chrono::date_time				tran_dtime;					//  N(14) ��û�Ͻ�
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
// �ŷ�������ȸ
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
	static_string<64>				api_tran_id;				// �ŷ�������ȣ(API)
	chrono::date_time				api_tran_dtm;				// �ŷ��Ͻ�(�и�������)
	static_string<64>				bank_tran_id;				// �ŷ�������ȣ(�������)
	chrono::date_time				bank_tran_date;				// �ŷ�����(�������)
	static_string<64>				bank_code_tran;				// �����ڵ带 �ο��� ������� ǥ���ڵ�
	eOAUTH_BANK_CODE				bank_rsp_code;				// �����ڵ�(�������)
	static_string<64>				bank_rsp_message;			// ����޽���(�������)
	static_string<64>				fintech_use_num;			// ����ũ�̿��ȣ
	int64_t							balance_amt{ 0 };			// �����ܾ�(-�ݾװ���)

	eOAUTH_YESNO					page_index_use_yn;			// ������ Index ��뿩��
	int64_t							page_index;					// ������ ��ȣ
	int64_t							total_record_cnt;			// �� ��ȸ�Ǽ�
	int64_t							page_record_cnt;			// ���������� ���ڵ� �Ǽ�
	eOAUTH_YESNO					next_page_yn;				// ���������� ���翩��

	static_string<64>				befor_inquiry_trace_info;	// ���� ��ȸ ���� ����
	static_string<64>				list_tran_seqno;			// �����ŷ����� ����

	struct TRANSACTION
	{
		chrono::date_time				tran_date;				// �ŷ�����
		chrono::date_time				tran_time;				// �ŷ��ð�
		eOAUTH_INOUT_TYPE				inout_type;				// ����ݱ���("�Ա�", "���")
		static_string<64>				tran_type;				// �ŷ�����
		static_string<64>				print_content;			// �������ڳ���
		int64_t							tran_amt{ 0 };			// �ŷ��ݾ�
		int64_t							after_balance_amt{ 0 };	// �ŷ��� �ܾ�
		static_string<64>				branch_name;			// �ŷ�����
	};

	std::vector<TRANSACTION>			res_list;

};


//-----------------------------------------------------------------------------
//
// �����ü
// oauth/2.0/authorize_account2
//
// ----------------------------------------------------------------------------
struct REQUEST_TRANSFER_WITHDRAW : public query::REQUEST
{
public:
	static_string<64>				authorization;		// ���µ�Ͻ� �����÷������κ��� ���۹��� access_token

	static_string<64>				dps_print_content;	// �Աݰ������ڳ���
	static_string<64>				fintech_use_num;	// ��ݰ�������ũ�̿��ȣ
	int64_t							tran_amt{ 0 };		// �ŷ��ݾ�
	chrono::date_time				tran_dtime;			// ��û�Ͻ�
};

struct RESPONSE_TRANSFER_WITHDRAW : public query::RESPONSE
{
	static_string<64>				api_tran_id;				// �ŷ�������ȣ(API)
	chrono::date_time				api_tran_dtm;				// �ŷ��Ͻ�(�и�������)
	eOAUTH_BANK_CODE				dps_bank_code_std;			// �Աݱ��.ǥ���ڵ�
	int64_t							dps_bank_code_sub;			// �Աݱ��.�����ڵ�
	static_string<64>				dps_bank_name;				// �Աݱ����
	static_string<64>				dps_account_num_masked;		// �Աݰ��¹�ȣ(��¿�)
	static_string<64>				dps_print_content;			// �Աݰ������ڳ���
	static_string<64>				dps_account_holder_name;	// �����μ���
	static_string<64>				bank_tran_id;				// �ŷ�������ȣ(�������)
	chrono::date_time				bank_tran_date;				// �ŷ�����(�������)
	static_string<64>				bank_code_tran;				// �����ڵ带 �ο��� ������� ǥ���ڵ�
	eOAUTH_BANK_CODE				bank_rsp_code;				// �����ڵ�(�������)
	static_string<64>				bank_rsp_message;			// ����޽���(�������)
	static_string<64>				fintech_use_num;			// ����ũ�̿��ȣ
	static_string<64>				account_alias;				// ��ݰ��º���(Alias)
	eOAUTH_BANK_CODE				bank_code_std;				// ���(�輳)���.ǥ���ڵ�
	int64_t							bank_code_sub;				// ���(�輳)���.�����ڵ�
	static_string<64>				bank_name;					// ���(�輳)�����
	static_string<64>				account_num_masked;			// ��ݰ��¹�ȣ(��¿�)
	static_string<64>				print_content;				// ��ݰ������ڳ���
	static_string<64>				account_holder_name;		// �۱��μ���
	int64_t							tran_amt{ 0 };				// �ŷ��ݾ�
};


//-----------------------------------------------------------------------------
//
// �Ա���ü
// oauth/2.0/authorize_account2
//
// ----------------------------------------------------------------------------
struct REQUEST_TRANSFER_DEPOSIT : public query::REQUEST
{
public:
	static_string<64>				authorization;		// ���µ�Ͻ� �����÷������κ��� ���۹��� access_token

	static_string<64>				wd_pass_phrase;		// �̿��� �Ա���ü�� ��ȣ������
	static_string<64>				wd_print_content;	// ��ݰ������ڳ���
	int								req_cnt{ 0 };		// �Աݿ�û�Ǽ�(req_cnt)

	struct DEPOSIT
	{
	public:
		int							tran_no{ 0 };		// �ŷ�����
		static_string<64>			fintech_use_num;	// ��ݰ�������ũ�̿��ȣ
		static_string<64>			print_content;		// �Աݰ������ڳ���
		int64_t						tran_amt{ 0 };		// �ŷ��ݾ�
	};
														// �Աݿ�û�Ǽ� (req_cnt)
	std::vector<DEPOSIT>			req_list;			// �Աݿ�û���
	chrono::date_time				tran_dtime;			// ��û�Ͻ�
};

struct RESPONSE_TRANSFER_DEPOSIT : public query::RESPONSE
{
	static_string<64>				api_tran_id;				// �ŷ�������ȣ(API)
	chrono::date_time				api_tran_dtm;				// �ŷ��Ͻ�(�и�������)

	eOAUTH_BANK_CODE				wd_bank_code_std;			// �Աݱ��.ǥ���ڵ�
	int64_t							wd_bank_code_sub;			// �Աݱ��.�����ڵ�
	static_string<64>				wd_bank_name;				// �Աݱ����
	static_string<64>				wd_account_num_masked;		// �Աݰ��¹�ȣ(��¿�)
	static_string<64>				wd_print_content;			// �Աݰ������ڳ���
	static_string<64>				wd_account_holder_name;		// �����μ���

	struct TRANSACTION
	{
		int								tran_no{ 0 };			// �ŷ�����
		static_string<64>				bank_tran_id;			// �ŷ�������ȣ(�������)
		chrono::date_time				bank_tran_date;			// �ŷ�����(�������)
		static_string<64>				bank_code_tran;			// �����ڵ带 �ο��� �������.ǥ���ڵ�
		eOAUTH_BANK_CODE				bank_rsp_code;			// �����ڵ�(�������)
		static_string<64>				bank_rsp_message;		// ����޽���(�������)
		static_string<64>				fintech_use_num;		// ����ũ�̿��ȣ
		static_string<64>				account_alias;			// ���º���
		eOAUTH_BANK_CODE				bank_code_std;			// �Ա�(����)���.ǥ���ڵ�
		int64_t							bank_code_sub;			// �Ա�(����)���.�����ڵ�
		static_string<64>				bank_name;				// �Ա�(����)�����
		static_string<64>				account_num_masked;		// �Աݰ��¹�ȣ(��¿�)
		static_string<64>				print_content;			// �Աݰ��� ���ڳ���
		static_string<64>				account_holder_name;	// ������ ����
		int64_t							tran_amt{ 0 };			// �ŷ��ݾ�
	};

	std::vector<TRANSACTION>			res_list;
};


//-----------------------------------------------------------------------------
//
// �Ա���ü - ���¹�ȣ ���
// 
//  - HTTP URL      https://openapi.open-platform.or.kr/v1.0/transfer/deposit2
//  - HTTP Method   POST
//  - Content-Type  application/json; charset=UTF-8
//
// ----------------------------------------------------------------------------
struct REQUEST_TRANSFER_DEPOSIT2 : public query::REQUEST
{
public:
	static_string<64>				authorization;			// ���µ�Ͻ� �����÷������κ��� ���۹��� access_token

	static_string<64>				wd_pass_phrase;			// �̿��� �Ա���ü�� ��ȣ������
	static_string<64>				wd_print_content;		// ��ݰ������ڳ���
	int								req_cnt{ 0 };			// �Աݿ�û�Ǽ�(req_cnt)

	struct TRANSACTION
	{
		int							tran_no{ 0 };			// �ŷ�����
		eOAUTH_BANK_CODE			bank_code_std{ 0 };		// �Ա�����.ǥ���ڵ�
		static_string<64>			accoount_num;			// �Աݰ��¹�ȣ
		static_string<64>			account_holder_name;	// �Աݰ��¿����ָ�
		static_string<64>			print_content;			// �Աݰ������ڳ���
		int64_t						tran_amt{ 0 };			// �ŷ��ݾ�
	};
															// �Աݿ�û�Ǽ� (req_cnt)
	std::vector<TRANSACTION>		req_list;				// �Աݿ�û���
	chrono::date_time				tran_dtime;				// ��û�Ͻ�
};

struct RESPONSE_TRANSFER_DEPOSIT2 : public query::RESPONSE
{
	static_string<64>				api_tran_id;				// �ŷ�������ȣ(API)
	chrono::date_time				api_tran_dtm;				// �ŷ��Ͻ�(�и�������)

	eOAUTH_BANK_CODE				wd_bank_code_std;			// �Աݱ��.ǥ���ڵ�
	int64_t							wd_bank_code_sub;			// �Աݱ��.�����ڵ�
	static_string<64>				wd_bank_name;				// �Աݱ����
	static_string<64>				wd_account_num_masked;		// �Աݰ��¹�ȣ(��¿�)
	static_string<64>				wd_print_content;			// �Աݰ������ڳ���
	static_string<64>				wd_account_holder_name;		// �����μ���

	struct TRANSACTION
	{
		int								tran_no{ 0 };			// �ŷ�����
		static_string<64>				bank_tran_id;			// �ŷ�������ȣ(�������)
		chrono::date_time				bank_tran_date;			// �ŷ�����(�������)
		static_string<64>				bank_code_tran;			// �����ڵ带 �ο��� �������.ǥ���ڵ�

		eOAUTH_BANK_CODE				bank_rsp_code;			// �����ڵ�(�������)
		static_string<64>				bank_rsp_message;		// ����޽���(�������)
		eOAUTH_BANK_CODE				bank_code_std;			// �Ա�(����)���.ǥ���ڵ�
		int64_t							bank_code_sub;			// �Ա�(����)���.�����ڵ�
		static_string<64>				bank_name;				// �Ա�(����)�����
		static_string<64>				account_num;			// �Աݰ��¹�ȣ
		static_string<64>				account_num_masked;		// �Աݰ��¹�ȣ(��¿�)
		static_string<64>				print_content;			// �Աݰ������ڳ���
		static_string<64>				account_holder_name;	// �����μ���
		static_string<64>				tran_amt;				// �ŷ��ݾ�
	};

	std::vector<TRANSACTION>			res_list;
};


//-----------------------------------------------------------------------------
//
// ��ü�����ȸ
// 
//  - HTTP URL      https://openapi.open-platform.or.kr/v1.0/transfer/result
//  - HTTP Method   POST
//  - Content-Type  application/json; charset=UTF-8
//
// ----------------------------------------------------------------------------
struct REQUEST_TRANSFER_RESULT : public query::REQUEST
{
public:
	static_string<64>				authorization;			// ���µ�Ͻ� �����÷������κ��� ���۹��� access_token

	eOAUTH_CHECK_TYPE				check_type;				// 1:�����ü, 2:�Ա���ü
	int								req_cnt{ 0 };			// ��û�Ǽ�(req_cnt)

	struct TRANSACTION
	{
	public:
		int								tran_no{ 0 };		// �ŷ�����
		static_string<64>				org_bank_tran_id;	// ���ŷ� �ŷ�������ȣ(�������)
		chrono::date_time				org_bank_tran_date;	// ���ŷ� �ŷ���(�������)
		int64_t							org_tran_amt{ 0 };	// ���ŷ� �ŷ��ݾ�
	};
															// ��û�Ǽ� (req_cnt)
	std::vector<TRANSACTION>		req_list;				// ��û���

	chrono::date_time				tran_dtime;				// ��û�Ͻ�
};

struct RESPONSE_TRANSFER_RESULT : public query::RESPONSE
{
	static_string<64>				api_tran_id;			// �ŷ�������ȣ(API)
	chrono::date_time				api_tran_dtm;			// �ŷ��Ͻ�(�и�������)

	struct TRANSACTION
	{
		int								tran_no{ 0 };			// �ŷ�����

		static_string<64>				bank_tran_id;			// �ŷ�������ȣ(�������)
		chrono::date_time				bank_tran_date;			// �ŷ�����(�������)
		static_string<64>				bank_code_tran;			// �����ڵ带 �ο��� �������.ǥ���ڵ�
		eOAUTH_BANK_CODE				bank_rsp_code;			// �����ڵ�(�������)
		static_string<64>				bank_rsp_message;		// ����޽���(�������)

		eOAUTH_BANK_CODE				wd_bank_code_std;		// ���(����)���.ǥ���ڵ�
		int64_t							wd_bank_code_sub;		// ���(����)���.�����ڵ�
		static_string<64>				wd_bank_name;			// ���(����)�����
		static_string<64>				wd_fintech_use_num;		// ��ݰ��� ����ũ�̿��ȣ
		static_string<64>				wd_account_num_masked;	// ��ݰ��¹�ȣ(��¿�)
		static_string<64>				wd_print_content;		// ��ݰ������ڳ���
		static_string<64>				wd_account_holder_name;	// �۱��μ���

		eOAUTH_BANK_CODE				dps_bank_code_std;		// �Ա�(����)���.ǥ���ڵ�
		int64_t							dps_bank_code_sub;		// �Ա�(����)���.�����ڵ�
		static_string<64>				dps_bank_name;			// �Ա�(����)�����
		static_string<64>				dps_fintech_use_num;	// �Աݰ��� ����ũ�̿��ȣ
		static_string<64>				dps_account_num_masked;	// �Աݰ��¹�ȣ(��¿�)
		static_string<64>				dps_print_content;		// �Աݰ������ڳ���
		static_string<64>				dps_account_holder_name;// �Ա��μ���

		int64_t							tran_amt{ 0 };			// �ŷ��ݾ�
	};

	std::vector<TRANSACTION>			res_list;
};


//-----------------------------------------------------------------------------
//
// ��üAPIó����ȸ
// 
//  - HTTP URL      https://openapi.open-platform.or.kr/v1.0/transfer/recheck
//  - HTTP Method   POST
//  - Content-Type  application/json; charset=UTF-8
//
// ----------------------------------------------------------------------------
struct REQUEST_TRANSFER_RECHECK : public query::REQUEST
{
public:
	static_string<64>				authorization;										// ���µ�Ͻ� �����÷������κ��� ���۹��� access_token

	eOAUTH_CHECK_TYPE				check_type;											// 1:�����ü, 2:�Ա���ü
	int								req_cnt{ 0 };										// ��û�Ǽ�(req_cnt)

	struct TRNASACTION
	{
	public:
		int								tran_no{ 0 };									// �ŷ�����
		chrono::date_time				org_tran_dtime;									// ���ŷ���û�Ͻ�
		eOAUTH_ORG_REQ_GUBUN			org_req_gubun{ eOAUTH_ORG_REQ_GUBUN::NOT_DEFINED_ };	// ���ŷ���û����������ı��� (1:����ũ�̿��ȣ, 2:���¹�ȣ)
		eOAUTH_BANK_CODE				bank_code_std{ 0 };								// ���ŷ� ���� ��ǥ�ڵ�
		static_string<64>				accoount_num;									// ���ŷ� ����ݰ��¹�ȣ
		static_string<64>				print_content;									// ���ŷ� ����ݰ������ڳ���
		static_string<64>				fintech_use_num;								// ���ŷ� ���������ũ�̿��ȣ
		int64_t							org_tran_amt{ 0 };								// ���ŷ� �ŷ��ݾ�
	};

	std::vector<TRNASACTION>		req_list;											// ��û�Ǽ�(req_cnt), ��û���(req_list)
	chrono::date_time				tran_dtime;											// ��û�Ͻ�
};

struct RESPONSE_TRANSFER_RECHECK : public query::RESPONSE
{
	static_string<64>				api_tran_id;				// �ŷ�������ȣ(API)
	chrono::date_time				api_tran_dtm;				// �ŷ��Ͻ�(�и�������)

	struct TRANSACTION
	{
		int								tran_no{ 0 };			// �ŷ�����

		static_string<64>				bank_tran_id;			// �ŷ�������ȣ(�������)
		chrono::date_time				bank_tran_date;			// �ŷ�����(�������)
		static_string<64>				bank_code_tran;			// �����ڵ带 �ο��� �������.ǥ���ڵ�
		eOAUTH_BANK_CODE				bank_rsp_code;			// �����ڵ�(�������)
		static_string<64>				bank_rsp_message;		// ����޽���(�������)

		eOAUTH_BANK_CODE				wd_bank_code_std;		// ���(����)���.ǥ���ڵ�
		int64_t							wd_bank_code_sub;		// ���(����)���.�����ڵ�
		static_string<64>				wd_bank_name;			// ���(����)�����
		static_string<64>				wd_fintech_use_num;		// ��ݰ��� ����ũ�̿��ȣ
		static_string<64>				wd_account_num_masked;	// ��ݰ��¹�ȣ(��¿�)
		static_string<64>				wd_print_content;		// ��ݰ������ڳ���
		static_string<64>				wd_account_holder_name;	// �۱��μ���

		eOAUTH_BANK_CODE				dps_bank_code_std;		// �Ա�(����)���.ǥ���ڵ�
		int64_t							dps_bank_code_sub;		// �Ա�(����)���.�����ڵ�
		static_string<64>				dps_bank_name;			// �Ա�(����)�����
		static_string<64>				dps_fintech_use_num;	// �Աݰ��� ����ũ�̿��ȣ
		static_string<64>				dps_account_num_masked;	// �Աݰ��¹�ȣ(��¿�)
		static_string<64>				dps_print_content;		// �Աݰ������ڳ���
		static_string<64>				dps_account_holder_name;// �Ա��μ���

		int64_t							tran_amt{ 0 };			// �ŷ��ݾ�
	};

	std::vector<TRANSACTION>		res_list;
};


//-----------------------------------------------------------------------------
//
// ���½Ǹ���ȸ API
// 
//  - HTTP URL      https://openapi.open-platform.or.kr/v1.0/inquiry/real_name
//  - HTTP Method   POST
//  - Content-Type  application/json; charset=UTF-8
//
// ----------------------------------------------------------------------------
struct REQUEST_INQUIRY_REAL_NAME : public query::REQUEST
{
public:
	static_string<64>				authorization;				//        ���µ�Ͻ� �����÷������κ��� ���۹��� access_token

	eOAUTH_BANK_CODE				bank_code_std {0};			// AN( 3) ���ŷ� ���� ��ǥ�ڵ�
	static_string<64>				accoount_num;				// AN(16) ���¹�ȣ
	static_string<64>				accoount_holder_info;		// AN( 7) ������ �������� YYYYMMDD(6) + �ĺ���ȣ(1)
	chrono::date_time				tran_dtime;					//  N(14) ��û�Ͻ�
															
};

struct RESPONSE_INQUIRY_REAL_NAME : public query::RESPONSE
{
	static_string<64>				api_tran_id;				// �ŷ�������ȣ(API)
	chrono::date_time				api_tran_dtm;				// �ŷ��Ͻ�(�и�������)

	static_string<64>				bank_tran_id;				// �ŷ�������ȣ(�������)
	chrono::date_time				bank_tran_date;				// �ŷ�����(�������)
	static_string<64>				bank_code_tran;				// �����ڵ带 �ο��� �������.ǥ���ڵ�
	eOAUTH_BANK_CODE				bank_rsp_code;				// �����ڵ�(�������)
	static_string<64>				bank_rsp_message;			// ����޽���(�������)
	eOAUTH_BANK_CODE				bank_code_std;				// �������.ǥ���ڵ�
	int64_t							bank_code_sub;				// �������.�����ڵ�
	static_string<64>				bank_name;					// ���������
	static_string<64>				account_num;				// ���¹�ȣ
	static_string<64>				account_holder_info;		// ����������
	static_string<64>				account_holder_name;		// �����ּ���
};


//-----------------------------------------------------------------------------
//
// �������������ȸ API
// 
//  - HTTP URL      https://openapi.open-platform.or.kr/v1.0/bank/status
//  - HTTP Method   GET
//  - Content-Type  application/x-www-form-urlencoded; charset=UTF-8
//
// ----------------------------------------------------------------------------
struct REQUEST_BANK_STATUS : public query::REQUEST
{
public:
	static_string<64>				authorization;										//        ���µ�Ͻ� �����÷������κ��� ���۹��� access_token
};

struct RESPONSE_BANK_STATUS : public query::RESPONSE
{
	static_string<64>				api_tran_id;										// AN( 20)	���ŷ� ���� ��ǥ�ڵ�
	chrono::date_time				api_tran_dtm;										//  N( 17)	���¹�ȣ

	struct BANK_STATUS
	{
		eOAUTH_BANK_CODE				bank_code_std{ 0 };								// AN(  3)  �������.ǥ���ڵ�
		static_string<64>				bank_name;										// AH( 20)  ���������
		eOAUTH_BANK_STATUS				bank_status{ eOAUTH_BANK_STATUS::NOT_DEFINED_ };		// AN[  1]  ����������� Y:�ŷ�����, D:���, L:��������, E:����ó����.
	};

	std::vector<BANK_STATUS>		res_list;											//          ����������(res_list)
};


}
