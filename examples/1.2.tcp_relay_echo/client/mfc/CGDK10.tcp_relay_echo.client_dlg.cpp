#include "pch.h"
#include "framework.h"
#include "CGDK10.tcp_relay_echo.client.mfc.h"
#include "CGDK10.tcp_relay_echo.client_dlg.h"
#include "afxdialogex.h"

#if defined(_DEBUG) && !defined(NDEBUG)
	#define new DEBUG_NEW
#endif

Ctcp_relay_echo_client_dlg::Ctcp_relay_echo_client_dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TCP_ECHOWINDOWSMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctcp_relay_echo_client_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MESSAGE_SIZE, m_comboMessageSize);
}

#pragma warning(disable:4407)
BEGIN_MESSAGE_MAP(Ctcp_relay_echo_client_dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_COMMAND(ID_SYSTEM_EXIT,						&Ctcp_relay_echo_client_dlg::OnSystemExit)
	ON_COMMAND(ID_ABOUT_CGDKINFO,					&Ctcp_relay_echo_client_dlg::OnAboutCGDKinfo)
	ON_BN_CLICKED(IDOK,								&Ctcp_relay_echo_client_dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL,							&Ctcp_relay_echo_client_dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT,				&Ctcp_relay_echo_client_dlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT1,				&Ctcp_relay_echo_client_dlg::OnBnClickedButtonConnect1)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT10,				&Ctcp_relay_echo_client_dlg::OnBnClickedButtonConnect10)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT100,			&Ctcp_relay_echo_client_dlg::OnBnClickedButtonConnect100)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT,			&Ctcp_relay_echo_client_dlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT_ALL,		&Ctcp_relay_echo_client_dlg::OnBnClickedButtonDisconnectAll)
	ON_CBN_SELCHANGE(IDC_COMBO_MESSAGE_SIZE,		&Ctcp_relay_echo_client_dlg::OnCbnSelchangeComboMessageSize)
	ON_BN_CLICKED(IDC_BUTTON_POOL,					&Ctcp_relay_echo_client_dlg::OnBnClickedButtonPool)
	ON_BN_CLICKED(IDC_BUTTON_THREAD,				&Ctcp_relay_echo_client_dlg::OnBnClickedButtonThread)

	ON_BN_CLICKED(IDC_BUTTON_CLOSESOCKET_SINGLE, &Ctcp_relay_echo_client_dlg::OnBnClickedButtonClosesocketSingle)
	ON_BN_CLICKED(IDC_BUTTON_CLOSESOCKET_ALL, &Ctcp_relay_echo_client_dlg::OnBnClickedButtonClosesocketAll)
END_MESSAGE_MAP()
#pragma warning(default:4407)

// Ctcp_relay_echo_client_dlg 메시지 처리기
BOOL Ctcp_relay_echo_client_dlg::OnInitDialog()
{
	//-----------------------------------------------------------------
	// 1. MFC Default
	//-----------------------------------------------------------------
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);


	//-----------------------------------------------------------------
	// 2. 시작
	//-----------------------------------------------------------------
	// 1) tester 객체 생성
	g_ptest_tcp_relay_echo_client = make_own<test_tcp_relay_echo_client>();

	// 2) tester start
	g_ptest_tcp_relay_echo_client->start();


	//-----------------------------------------------------------------
	// 2. control 설정.
	//-----------------------------------------------------------------
	// 1) Connective
	m_child_connective_info.CreateChild(&g_ptest_tcp_relay_echo_client->m_pconnector_socket->statistics_get_connective_info_total(), this);
	m_child_connective_info.MoveToCenter(GetDlgItem(IDC_STATIC_CONTROL_CONNECTION), 0, 5);
	m_child_connective_info.ShowWindow(SW_SHOW);
	m_child_connective_info.SetUpdateInterval(1);

	// 2) 
	m_child_traffic_info.CreateChild(&net::io::statistics::Nsocket::statistics_get_traffic_info_total(), this);
	m_child_traffic_info.MoveToCenter(GetDlgItem(IDC_STATIC_CONTROL_TRAFFIC));
	m_child_traffic_info.ShowWindow(SW_SHOW);
	m_child_traffic_info.SetUpdateInterval(1);

	// 3) 
	//SetDlgItemText(IDC_EDIT_EXPLANATION_1, str_explanation);

	// 3) Pool Status Dialog
	m_dlg_object_factory_status.CreateModaless(factory::manager::instance(), this);

	// 4) Thread StatusDialog
	m_dlg_thread_status.CreateModaless(api::manager_thread::instance(), executor::manager::instance(), system_executor::instance(), this);

	// 5) Destination IP Address
	SetDlgItemText(IDC_EDIT_ADDRESS, TEXT("localhost"));

	// 6) Destination Port
	SetDlgItemInt(IDC_EDIT_PORT, 20000);

	// 8) Message Select
	m_comboMessageSize.SetCurSel(static_cast<int>(g_ptest_tcp_relay_echo_client->m_selected_message_size));

	// 10) Connect Times
	SetDlgItemInt(IDC_EDIT_CONNECT_TIMES, 2000);

	// 11) tooltip
	m_ctrl_tooltip.Create(this);
	m_ctrl_tooltip.SetDelayTime(TTDT_AUTOMATIC, 100);

	//-----------------------------------------------------------------
	// 6. Timer설정.
	//-----------------------------------------------------------------
	// 1) Statistics를 위한 Timer
	SetTimer(1, 1000, NULL);


	// return) 
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Ctcp_relay_echo_client_dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Ctcp_relay_echo_client_dlg::OnPaint()
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
HCURSOR Ctcp_relay_echo_client_dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Ctcp_relay_echo_client_dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		//g_ptest_tcp_relay_echo_client->m_receive_byte_per_sec;

		CString str_text;

		str_text.Format(TEXT("%12.2f"), g_ptest_tcp_relay_echo_client->m_receive_message_per_sec);
		SetDlgItemText(IDC_STATIC_TPS, str_text);
	}

	__super::OnTimer(nIDEvent);
}

void Ctcp_relay_echo_client_dlg::OnBnClickedOk()
{
	// 1) close dialogs
	m_child_connective_info.DestroyWindow();
	m_child_traffic_info.DestroyWindow();
	m_dlg_object_factory_status.DestroyWindow();
	m_dlg_thread_status.DestroyWindow();

	// 2) OnOK
	CDialogEx::OnOK();
}

void Ctcp_relay_echo_client_dlg::OnSystemExit()
{
	// 1) close dialogs
	OnBnClickedOk();
}

void Ctcp_relay_echo_client_dlg::OnAboutCGDKinfo()
{
}

void Ctcp_relay_echo_client_dlg::OnBnClickedCancel()
{
	// 1) 모든 소켓의 접속을 끊고 처리를 종료한다.
	g_ptest_tcp_relay_echo_client.reset();

	// 2) OnOK~
	OnOK();
}

void Ctcp_relay_echo_client_dlg::ReadServerAddress()
{
	// Declare) 
	TCHAR strAddress[256];
	int port;

	// 1) Address String을 얻는다.
	GetDlgItemText(IDC_EDIT_ADDRESS, strAddress, 256);

	// 2) Port를 읽는다.
	port = GetDlgItemInt(IDC_EDIT_PORT);	// - Port를 설정한다.

	// 3) Address로 변환한다.
	g_ptest_tcp_relay_echo_client->m_endpoint_connect = from_string(strAddress);
	g_ptest_tcp_relay_echo_client->m_endpoint_connect.port(static_cast<uint16_t>(port));
}

void Ctcp_relay_echo_client_dlg::OnBnClickedButtonConnect1()
{
	// 1)  read address from UI
	ReadServerAddress();

	// 2) connect
	g_ptest_tcp_relay_echo_client->request_connect(1);
}


void Ctcp_relay_echo_client_dlg::OnBnClickedButtonConnect10()
{
	// 1)  read address from UI
	ReadServerAddress();

	// 2) connect
	g_ptest_tcp_relay_echo_client->request_connect(10);
}

void Ctcp_relay_echo_client_dlg::OnBnClickedButtonConnect100()
{
	// 1)  read address from UI
	ReadServerAddress();

	// 2) connect
	g_ptest_tcp_relay_echo_client->request_connect(100);
}

void Ctcp_relay_echo_client_dlg::OnBnClickedButtonConnect()
{
	// 1)  read address from UI
	ReadServerAddress();

	// 2) read connect times
	int	nTimer	 = GetDlgItemInt(IDC_EDIT_CONNECT_TIMES);

	// 3) connect
	g_ptest_tcp_relay_echo_client->request_connect(nTimer);
}

void Ctcp_relay_echo_client_dlg::OnBnClickedButtonDisconnect()
{
	g_ptest_tcp_relay_echo_client->request_disconnect_socket(1);
}

void Ctcp_relay_echo_client_dlg::OnBnClickedButtonDisconnectAll()
{
	g_ptest_tcp_relay_echo_client->request_disconnect_socket_all();
}

void Ctcp_relay_echo_client_dlg::OnBnClickedButtonClosesocketSingle()
{
	g_ptest_tcp_relay_echo_client->request_closesocket(1);
}

void Ctcp_relay_echo_client_dlg::OnBnClickedButtonClosesocketAll()
{
	g_ptest_tcp_relay_echo_client->request_closesocket_all();
}


void Ctcp_relay_echo_client_dlg::OnCbnSelchangeComboMessageSize()
{
	// 1) 새로 선택한 값을 읽어온다.
	std::size_t	selected = m_comboMessageSize.GetCurSel();

	// 2) 새로 선택한 값을 써넣는다.
	g_ptest_tcp_relay_echo_client->set_message_size(selected);
}

void Ctcp_relay_echo_client_dlg::OnBnClickedButtonSingleSend()
{
	g_ptest_tcp_relay_echo_client->request_send_immidiately();
}

void Ctcp_relay_echo_client_dlg::OnBnClickedButtonPool()
{
	m_dlg_object_factory_status.ShowWindow(SW_SHOW);
}

void Ctcp_relay_echo_client_dlg::OnBnClickedButtonThread()
{
	m_dlg_thread_status.ShowWindow(SW_SHOW);
}

BOOL Ctcp_relay_echo_client_dlg::PreTranslateMessage(MSG* pMsg)
{
	m_ctrl_tooltip.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}
