
// chatting_client_dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CGDK10.chatting.client.mfc.h"
#include "CGDK10.chatting.client_dlg.h"
#include "afxdialogex.h"

#if defined(_DEBUG) && !defined(NDEBUG)
	#define new DEBUG_NEW
#endif

// Cchatting_client_mfc_dlg 대화 상자
Cchatting_client_mfc_dlg::Cchatting_client_mfc_dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATTING_CLIENTMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cchatting_client_mfc_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHATTING, m_listctrlChatting);
}

BEGIN_MESSAGE_MAP(Cchatting_client_mfc_dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &Cchatting_client_mfc_dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Cchatting_client_mfc_dlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &Cchatting_client_mfc_dlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_CHATTING_SEND, &Cchatting_client_mfc_dlg::OnBnClickedButtonChattingSend)
	ON_EN_CHANGE(IDC_EDIT_ACCOUNT_ID, &Cchatting_client_mfc_dlg::OnEnChangeEditAccountId)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &Cchatting_client_mfc_dlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_ENTER_CHANNEL, &Cchatting_client_mfc_dlg::OnBnClickedButtonEnterChannel)
END_MESSAGE_MAP()

BOOL Cchatting_client_mfc_dlg::PreTranslateMessage(MSG* pMsg)
{
	// 1) Tooltip처리
	m_Tooltip.RelayEvent(pMsg);

	// 2) Enter키 처리
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			OnBnClickedButtonChattingSend();
		}
	}

	// Return) 
	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL Cchatting_client_mfc_dlg::OnInitDialog()
{
	//-----------------------------------------------------------------
	// 1. MFC Default
	//-----------------------------------------------------------------
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// Local을 설정한다.
	setlocale(LC_ALL, "korean");


	//-----------------------------------------------------------------
	// 2. Control 설정.
	//-----------------------------------------------------------------
	// 1) Srand
	srand(10);

	// 2) Tooltip
	m_Tooltip.Create(this);
	m_Tooltip.SetMaxTipWidth(300);
	m_Tooltip.SetDelayTime(TTDT_AUTOPOP, 20000);

	// 2) Nicknam & Account ID
	SetDlgItemText(IDC_EDIT_NICKNAME, TEXT("TestNickname"));
	m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_NICKNAME), TEXT("채팅시 사용할 닉네임"));
	SetDlgItemInt(IDC_EDIT_ACCOUNT_ID, rand()%65534+1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ACCOUNT_ID))->SetRange32(1, 65535);
	m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_ACCOUNT_ID), TEXT("사용자의 구분을 위해 사용할 ACCOUNT_ID. 서버에 로그인시 발급하는 유니크한 ID를 사용하는 것이 기본이나 현재는 임의의 값을 넣어 사용한다."));

	// 3) Destination IP Address
	SetDlgItemText(IDC_EDIT_ADDRESS, TEXT("127.0.0.1"));
	m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_ADDRESS), TEXT("접속할 채팅서버 주소"));
	SetDlgItemInt(IDC_EDIT_PORT, 22000);
	m_Tooltip.AddTool(GetDlgItem(IDC_EDIT_PORT), TEXT("접속할 채팅서버 포트"));

	// 4) Channel ID
	SetDlgItemInt(IDC_EDIT_CHANNEL_ID, 10);

	// 4) ...
	ShowWindow_Login(SW_SHOW);
	ShowWindow_Lobby(SW_HIDE);
	ShowWindow_Chatting(SW_HIDE);


	//-----------------------------------------------------------------
	// 3. Executor를 설정한다.
	//-----------------------------------------------------------------
	// 1) Executor를 NO_THREAD한다.
	system_executor::initialize_instance(CGEXECUTOR_NOTHREAD);

	// 2) Statistics를 위한 Timer
	SetTimer(0, 10, NULL);

	// Return)
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cchatting_client_mfc_dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cchatting_client_mfc_dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cchatting_client_mfc_dlg::OnBnClickedOk()
{
}

void Cchatting_client_mfc_dlg::OnBnClickedCancel()
{
	// 1) Socket을 닫는다.
	KillTimer(0);

	// 2) OnOK~
	OnOK();
}

void Cchatting_client_mfc_dlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case	0:
			{
				system_executor::run_executor();
			}
			break;
	}

	CDialog::OnTimer(nIDEvent);
}

void Cchatting_client_mfc_dlg::OnBnClickedButtonConnect()
{
	CString	temp;
	GetDlgItemText(IDC_EDIT_NICKNAME, temp);
	SetDlgItemText(IDC_STATIC_CHATTING_NICKNAME, temp);
	GetDlgItemText(IDC_EDIT_ACCOUNT_ID, temp);
	SetDlgItemText(IDC_STATIC_CHATTING_ACCOUNT_ID, temp);

	// 1) Socket을 생성한다.
	auto psocket_chatting = make_own<socket_chatting>();

	// Declare) 
	char str_address[256];
	char str_port[256];

	// 2) Address String을 얻는다.
	::GetDlgItemTextA(m_hWnd, IDC_EDIT_ADDRESS, str_address, 256);
	
	// 3) Port를 얻는다.
	::GetDlgItemTextA(m_hWnd, IDC_EDIT_PORT, str_port, 256);

	// 4) 접속을 시도한다.
	psocket_chatting->start({ net::ip::tcp::resolver().resolve(str_address, str_port).at(0).endpoint() });

	// 5) ...
	m_psocket_chatting = std::move(psocket_chatting);
}

void Cchatting_client_mfc_dlg::OnBnClickedButtonChattingSend()
{
	// check)
	RETURN_IF(m_psocket_chatting.empty());

	// Declare) 
	char str_char[1024];
	char str_nickname[1024];

	// 1) Chatting String을 얻는다.
	GetDlgItemTextA(m_hWnd, IDC_EDIT_CHATTING, str_char, 1024);
	GetDlgItemTextA(m_hWnd, IDC_STATIC_CHATTING_NICKNAME, str_nickname, 1024);

	// 2) Chatting Editbox를 초기화.
	SetDlgItemText(IDC_EDIT_CHATTING, TEXT(""));
	GetDlgItem(IDC_EDIT_CHATTING)->SetFocus();

	// check) Chatting이 비어 있으면 그냥 리턴한다.
	RETURN_IF(str_char[0]==NULL);
	
	// 2) Chatting String을 전송한다.
	m_psocket_chatting->send(message_SEND_CHATTING_MESSAGE(str_char, str_nickname));
}

void Cchatting_client_mfc_dlg::ShowWindow_Login(int _show)
{
	GetDlgItem(IDC_STATIC_ACCOUNT_ID)->ShowWindow(_show);
	GetDlgItem(IDC_EDIT_ACCOUNT_ID)->ShowWindow(_show);
	GetDlgItem(IDC_SPIN_ACCOUNT_ID)->ShowWindow(_show);

	GetDlgItem(IDC_STATIC_ADDRESS)->ShowWindow(_show);
	GetDlgItem(IDC_EDIT_ADDRESS)->ShowWindow(_show);
	GetDlgItem(IDC_EDIT_PORT)->ShowWindow(_show);
	GetDlgItem(IDC_BUTTON_CONNECT)->ShowWindow(_show);

	GetDlgItem(IDC_STATIC_LOGIN_VERTICAL)->ShowWindow(_show);

	GetDlgItem(IDC_STATIC_NICKNAME)->ShowWindow(_show);
	GetDlgItem(IDC_EDIT_NICKNAME)->ShowWindow(_show);
}

void Cchatting_client_mfc_dlg::ShowWindow_Lobby(int _show)
{
	GetDlgItem(IDC_STATIC_FRAME_CHATTING_INFO)->ShowWindow(_show);
	GetDlgItem(IDC_STATIC_CHATTING_ACCOUNT_ID_TAG)->ShowWindow(_show); 
	GetDlgItem(IDC_STATIC_CHATTING_ACCOUNT_ID)->ShowWindow(_show);
	GetDlgItem(IDC_STATIC_CHATTING_NICKNAME_TAG)->ShowWindow(_show);
	GetDlgItem(IDC_STATIC_CHATTING_NICKNAME)->ShowWindow(_show);

	GetDlgItem(IDC_STATIC_CHATTING_SEPERATOR)->ShowWindow(_show);
	GetDlgItem(IDC_BUTTON_CLOSE)->ShowWindow(_show);
	GetDlgItem(IDC_STATIC_CHATTING_SEPERATOR2)->ShowWindow(_show);

	GetDlgItem(IDC_STATIC_CHANNEL_ID)->ShowWindow(_show);
	GetDlgItem(IDC_EDIT_CHANNEL_ID)->ShowWindow(_show);
	GetDlgItem(IDC_BUTTON_ENTER_CHANNEL)->ShowWindow(_show);
}

void Cchatting_client_mfc_dlg::ShowWindow_Chatting(int _show)
{
	GetDlgItem(IDC_STATIC_CHANNEL_NAME_TAG)->ShowWindow(_show);
	GetDlgItem(IDC_STATIC_CHANNEL_NAME)->ShowWindow(_show);

	m_listctrlChatting.ShowWindow(_show);
	m_listctrlChatting.ResetContent();

	GetDlgItem(IDC_EDIT_CHATTING)->ShowWindow(_show);
	GetDlgItem(IDC_BUTTON_CHATTING_SEND)->ShowWindow(_show);
}

void Cchatting_client_mfc_dlg::on_request_connect(socket_chatting* /*_psocket*/)
{
	GetDlgItem(IDC_EDIT_ACCOUNT_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_NICKNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_ADDRESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
}

void Cchatting_client_mfc_dlg::OnConnect(socket_chatting* /*_psocket*/)
{
	GetDlgItem(IDC_EDIT_ACCOUNT_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_NICKNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_ADDRESS)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);

	ShowWindow_Login(SW_HIDE);
	ShowWindow_Lobby(SW_SHOW);
	ShowWindow_Chatting(SW_HIDE);
}

void Cchatting_client_mfc_dlg::on_disconnect(socket_chatting* /*_psocket*/)
{
	ShowWindow_Login(SW_SHOW);
	ShowWindow_Lobby(SW_HIDE);
	ShowWindow_Chatting(SW_HIDE);
}

void Cchatting_client_mfc_dlg::on_notify_enter_channel(socket_chatting* /*_psocket*/, CHANNEL_ID _cid, eCHANNEL_OPTION /*_option*/, std::string_view _channel_name)
{
	ShowWindow_Lobby(SW_SHOW);
	ShowWindow_Chatting((_cid>1) ? SW_SHOW : SW_HIDE);

	SetDlgItemInt(IDC_EDIT_CHANNEL_ID, static_cast<UINT>(_cid));

	if (_channel_name.empty() == false)
	{
		SetDlgItemTextA(m_hWnd, IDC_STATIC_CHANNEL_NAME, _channel_name.data());
	}
	else
	{
		SetDlgItemText(IDC_STATIC_CHANNEL_NAME, TEXT(""));
	}
}

void Cchatting_client_mfc_dlg::on_send_chatting_message(socket_chatting* /*_psocket*/, std::string_view _chatting, std::string_view _nickname)
{
	// Declare) 
	TCHAR strString[1024];

	// 1) Nickname과 Chatting String을 붙혀 문자열을 만든다.
	wsprintf(strString, TEXT("%-24hs %hs"), _nickname.data(), _chatting.data());

	// 2) ListBox에 추가.
	m_listctrlChatting.InsertString(-1, strString);

	// 3) Scroll
	m_listctrlChatting.SetTopIndex(m_listctrlChatting.GetCount()-1);
}

void Cchatting_client_mfc_dlg::on_fail_connect(socket_chatting* /*_psocket*/)
{
	GetDlgItem(IDC_EDIT_ACCOUNT_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_NICKNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_ADDRESS)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
}

void Cchatting_client_mfc_dlg::OnEnChangeEditAccountId()
{
	auto aid = GetDlgItemInt(IDC_EDIT_ACCOUNT_ID);

	if (aid == 0)
	{
		SetDlgItemInt(IDC_EDIT_ACCOUNT_ID, 1);
	}
}

void Cchatting_client_mfc_dlg::OnBnClickedButtonEnterChannel()
{
	// 1) CHANNEL_ID를 얻는다.
	CHANNEL_ID	cid	 = GetDlgItemInt(IDC_EDIT_CHANNEL_ID);

	// check)
	if (cid == 0)
	{
		AfxMessageBox(TEXT("Invalid CHANNEL_ID (must be over 0)"), MB_OK);

		// Return) 
		return;
	}

	// 2) REQUEST_ENTER_CHANNEL을 한다.
	m_psocket_chatting->send(message_REQUEST_ENTER_CHANNEL(cid, eCHANNEL_OPTION::ENTER_ALWAYS));
}

void Cchatting_client_mfc_dlg::OnBnClickedButtonClose()
{
	if (m_psocket_chatting.exist())
	{
		m_psocket_chatting->closesocket();
	}
}
