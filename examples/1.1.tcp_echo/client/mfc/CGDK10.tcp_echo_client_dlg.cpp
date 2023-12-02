#include "pch.h"
#include "framework.h"
#include "CGDK10.tcp_echo_client.mfc.h"
#include "CGDK10.tcp_echo_client_dlg.h"
#include "afxdialogex.h"

#if defined(_DEBUG) && !defined(NDEBUG)
	#define new DEBUG_NEW
#endif

Ctcp_echo_client_dlg::Ctcp_echo_client_dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TCP_ECHOWINDOWSMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctcp_echo_client_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PACKET_SIZE, m_comboMessageSize);
	DDX_Control(pDX, IDC_SLIDER_TIMES, m_sliderSendTimes);
}

#pragma warning(disable:4407)
BEGIN_MESSAGE_MAP(Ctcp_echo_client_dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_SYSTEM_EXIT,						&Ctcp_echo_client_dlg::OnSystemExit)
	ON_COMMAND(ID_ABOUT_CGDKINFO,					&Ctcp_echo_client_dlg::OnAboutCGDKinfo)
	ON_BN_CLICKED(IDOK,								&Ctcp_echo_client_dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL,							&Ctcp_echo_client_dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT,				&Ctcp_echo_client_dlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT1,				&Ctcp_echo_client_dlg::OnBnClickedButtonConnect1)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT10,				&Ctcp_echo_client_dlg::OnBnClickedButtonConnect10)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT100,			&Ctcp_echo_client_dlg::OnBnClickedButtonConnect100)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT1K,				&Ctcp_echo_client_dlg::OnBnClickedButtonConnect1k)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT10K,			&Ctcp_echo_client_dlg::OnBnClickedButtonConnect10k)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT,			&Ctcp_echo_client_dlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT_ALL,		&Ctcp_echo_client_dlg::OnBnClickedButtonDisconnectAll)
	ON_BN_CLICKED(IDC_BUTTON_CLOSESOCKET_SINGLE,	&Ctcp_echo_client_dlg::OnBnClickedButtonClosesocketSingle)
	ON_BN_CLICKED(IDC_BUTTON_CLOSESOCKET_ALL,		&Ctcp_echo_client_dlg::OnBnClickedButtonClosesocketAll)
	ON_BN_CLICKED(IDC_CHECK_DISCONNECT_ON_RESPONSE, &Ctcp_echo_client_dlg::OnBnClickedCheckDisconnectOnResponse)

	ON_CBN_SELCHANGE(IDC_COMBO_PACKET_SIZE,			&Ctcp_echo_client_dlg::OnCbnSelchangeComboMessageSize)
	ON_BN_CLICKED(IDC_BUTTON_SINGLE_SEND,			&Ctcp_echo_client_dlg::OnBnClickedButtonSingleSend) 
	ON_BN_CLICKED(IDC_BUTTON_ZERO_SIZE_PACKET,		&Ctcp_echo_client_dlg::OnBnClickedButtonZeroSizeMessage)
	ON_BN_CLICKED(IDC_CHECK_CONNECT_TEST_STARTSTOP, &Ctcp_echo_client_dlg::OnBnClickedCheckConnectTestStartstop)
	ON_BN_CLICKED(IDC_CHECK_SEND_TEST_STARTSTOP,	&Ctcp_echo_client_dlg::OnBnClickedCheckSendTestStartstop)
	ON_BN_CLICKED(IDC_CHECK_RELAY_ECHO,				&Ctcp_echo_client_dlg::OnBnClickedCheckRelayEcho)
	ON_EN_CHANGE(IDC_EDIT_SEND_PER_ONETIME,			&Ctcp_echo_client_dlg::OnEnChangeEditSendPerOnetime)
	ON_BN_CLICKED(IDC_BUTTON_POOL,					&Ctcp_echo_client_dlg::OnBnClickedButtonPool)
	ON_BN_CLICKED(IDC_BUTTON_THREAD,				&Ctcp_echo_client_dlg::OnBnClickedButtonThread)

	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TPS_1,			&Ctcp_echo_client_dlg::OnDeltaposSpinTps1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TPS_10,		&Ctcp_echo_client_dlg::OnDeltaposSpinTps10)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TPS_100,		&Ctcp_echo_client_dlg::OnDeltaposSpinTps100)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TPS_1000,		&Ctcp_echo_client_dlg::OnDeltaposSpinTps1000)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TPS_10000,		&Ctcp_echo_client_dlg::OnDeltaposSpinTps10000)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TPS_100000,	&Ctcp_echo_client_dlg::OnDeltaposSpinTps100000)
END_MESSAGE_MAP()
#pragma warning(default:4407)

// Ctcp_echo_client_dlg 메시지 처리기
BOOL Ctcp_echo_client_dlg::OnInitDialog()
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
	g_ptest_tcp_echo_client = make_own<test_tcp_echo_client>();

	// 2) tester start
	g_ptest_tcp_echo_client->start();


	//-----------------------------------------------------------------
	// 2. control 설정.
	//-----------------------------------------------------------------
	// 1) Connective
	m_child_connective_info.CreateChild(&g_ptest_tcp_echo_client->m_pconnector_socket->statistics_get_connective_info_total(), this);
	m_child_connective_info.MoveToCenter(GetDlgItem(IDC_STATIC_CONTROL_CONNECTION), 0, 5);
	m_child_connective_info.ShowWindow(SW_SHOW);
	m_child_connective_info.SetUpdateInterval(1);

	// 2) 
	m_child_traffic_info.CreateChild(&net::io::statistics::Nsocket::statistics_get_traffic_info_total(), this);
	m_child_traffic_info.MoveToCenter(GetDlgItem(IDC_STATIC_CONTROL_TRAFFIC));
	m_child_traffic_info.ShowWindow(SW_SHOW);
	m_child_traffic_info.SetUpdateInterval(1);

	// 3) Pool Status Dialog
	m_dlg_object_factory_status.CreateModaless(factory::manager::instance(), this);

	// 4) Thread StatusDialog
	m_dlg_thread_status.CreateModaless(api::manager_thread::instance(), executor::manager::instance(), system_executor::instance(), this);

	// 5) Destination IP Address
	SetDlgItemText(IDC_EDIT_ADDRESS, TEXT("localhost"));

	// 6) Destination Port
	SetDlgItemInt(IDC_EDIT_PORT, 20000);

	// 7) send Times
	m_sliderSendTimes.SetRange(0, 1280000);
	SetDlgItemInt(IDC_EDIT_SEND_PER_ONETIME, 100);
	m_sliderSendTimes.SetPos(100);

	// 8) Message Select
	m_comboMessageSize.SetCurSel(static_cast<int>(g_ptest_tcp_echo_client->m_traffic_test_selected));

	// 9) Connect Text Info
	SetDlgItemInt(IDC_EDIT_TEST_INTERVAL, 200);
	SetDlgItemInt(IDC_EDIT_TEST_CONNECT_MIN, 500);
	SetDlgItemInt(IDC_EDIT_TEST_CONNECT_MAX, 800);

	// 10) Connect Times
	SetDlgItemInt(IDC_EDIT_CONNECT_TIMES, 2000);

	// 11) tooltip
	m_ctrl_tooltip.Create(this);
	m_ctrl_tooltip.SetDelayTime(TTDT_AUTOMATIC, 100);
	m_ctrl_tooltip.AddTool(GetDlgItem(IDC_SPIN_TPS_1), _TEXT("1 times"));
	m_ctrl_tooltip.AddTool(GetDlgItem(IDC_SPIN_TPS_10), _TEXT("10 times"));
	m_ctrl_tooltip.AddTool(GetDlgItem(IDC_SPIN_TPS_100), _TEXT("100 times"));
	m_ctrl_tooltip.AddTool(GetDlgItem(IDC_SPIN_TPS_1000), _TEXT("1`000 times"));
	m_ctrl_tooltip.AddTool(GetDlgItem(IDC_SPIN_TPS_10000), _TEXT("10`000 times"));
	m_ctrl_tooltip.AddTool(GetDlgItem(IDC_SPIN_TPS_100000), _TEXT("100`000 times"));


	//-----------------------------------------------------------------
	// 6. Timer설정.
	//-----------------------------------------------------------------
	// 1) Statistics를 위한 Timer
	SetTimer(1, 1000, NULL);


	// return) 
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Ctcp_echo_client_dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Ctcp_echo_client_dlg::OnPaint()
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
HCURSOR Ctcp_echo_client_dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Ctcp_echo_client_dlg::OnBnClickedOk()
{
}

void Ctcp_echo_client_dlg::OnSystemExit()
{
	// 1) close dialogs
	m_child_connective_info.DestroyWindow();
	m_child_traffic_info.DestroyWindow();
	m_dlg_object_factory_status.DestroyWindow();
	m_dlg_thread_status.DestroyWindow();

	// 2) close dialogs
	OnBnClickedOk();
}


void Ctcp_echo_client_dlg::OnAboutCGDKinfo()
{
}

void Ctcp_echo_client_dlg::OnBnClickedCancel()
{
	// 1) 모든 소켓의 접속을 끊고 처리를 종료한다.
	g_ptest_tcp_echo_client.reset();

	// 2) OnOK~
	OnOK();
}

void Ctcp_echo_client_dlg::OnBnClickedCheckConnectTestStartstop()
{
	CButton* pButton = ((CButton*)GetDlgItem(IDC_CHECK_CONNECT_TEST_STARTSTOP));

	// 1.A) 버튼이 눌러졌을 경울 => Message send를 시작한다.
	if (pButton->GetCheck() & BST_CHECKED)
	{
		// - 접속할 Address를 UI로 부터 읽어 들인다.
		ReadServerAddress();

		// - set...
		g_ptest_tcp_echo_client->set_connect_test_min(GetDlgItemInt(IDC_EDIT_TEST_CONNECT_MIN));
		g_ptest_tcp_echo_client->set_connect_test_max(GetDlgItemInt(IDC_EDIT_TEST_CONNECT_MAX));

		//// - timer를 돌린다.
		//DWORD tempInterval = GetDlgItemInt(IDC_EDIT_TEST_INTERVAL);

		g_ptest_tcp_echo_client->enable_connect_test(true);
	}
	// 1.B) 버튼이 해제되었을 경우 => Message send를 중지한다.
	else
	{
		g_ptest_tcp_echo_client->enable_connect_test(false);
	}
}

void Ctcp_echo_client_dlg::OnBnClickedCheckSendTestStartstop()
{
	CButton* pButton = ((CButton*)GetDlgItem(IDC_CHECK_SEND_TEST_STARTSTOP));

	if (pButton->GetCheck() & BST_CHECKED)
	{
		g_ptest_tcp_echo_client->enable_traffic_test(true);
	}
	else
	{
		g_ptest_tcp_echo_client->enable_traffic_test(false);
	}
}

void Ctcp_echo_client_dlg::OnBnClickedCheckRelayEcho()
{
	CButton* pButton = ((CButton*)GetDlgItem(IDC_CHECK_RELAY_ECHO));

	if (pButton->GetCheck() & BST_CHECKED)
	{
		g_ptest_tcp_echo_client->enable_relay_echo_test(true);
	}
	else
	{
		g_ptest_tcp_echo_client->enable_relay_echo_test(false);
	}
}

void Ctcp_echo_client_dlg::OnBnClickedCheckDisconnectOnResponse()
{
	CButton* pButton = ((CButton*)GetDlgItem(IDC_CHECK_DISCONNECT_ON_RESPONSE));

	if (pButton->GetCheck() & BST_CHECKED)
	{
		g_ptest_tcp_echo_client->enable_disconnect_on_response(true);
	}
	else
	{
		g_ptest_tcp_echo_client->enable_disconnect_on_response(false);
	}
}

void Ctcp_echo_client_dlg::ReadServerAddress()
{
	// Declare) 
	TCHAR strAddress[256];
	int port;

	// 1) Address String을 얻는다.
	GetDlgItemText(IDC_EDIT_ADDRESS, strAddress, 256);

	// 2) Port를 읽는다.
	port = GetDlgItemInt(IDC_EDIT_PORT);	// - Port를 설정한다.

	// 3) Address로 변환한다.
	g_ptest_tcp_echo_client->m_endpoint_connect = from_string(strAddress);
	g_ptest_tcp_echo_client->m_endpoint_connect.port(static_cast<uint16_t>(port));
}

void Ctcp_echo_client_dlg::OnBnClickedButtonConnect1()
{
	// 1)  read address from UI
	ReadServerAddress();

	// 2) connect
	g_ptest_tcp_echo_client->request_connect(1);
}


void Ctcp_echo_client_dlg::OnBnClickedButtonConnect10()
{
	// 1)  read address from UI
	ReadServerAddress();

	// 2) connect
	g_ptest_tcp_echo_client->request_connect(10);
}

void Ctcp_echo_client_dlg::OnBnClickedButtonConnect100()
{
	// 1)  read address from UI
	ReadServerAddress();

	// 2) connect
	g_ptest_tcp_echo_client->request_connect(100);
}

void Ctcp_echo_client_dlg::OnBnClickedButtonConnect1k()
{
	// 1)  read address from UI
	ReadServerAddress();

	// 2) connect
	g_ptest_tcp_echo_client->request_connect(1000);
}


void Ctcp_echo_client_dlg::OnBnClickedButtonConnect10k()
{
	// 1)  read address from UI
	ReadServerAddress();

	// 2) connect
	g_ptest_tcp_echo_client->request_connect(10000);
}


void Ctcp_echo_client_dlg::OnBnClickedButtonConnect()
{
	// 1)  read address from UI
	ReadServerAddress();

	// 2) read connect times
	int	nTimer	 = GetDlgItemInt(IDC_EDIT_CONNECT_TIMES);

	// 3) connect
	g_ptest_tcp_echo_client->request_connect(nTimer);
}

void Ctcp_echo_client_dlg::OnBnClickedButtonDisconnect()
{
	g_ptest_tcp_echo_client->request_disconnect_socket(1);
}

void Ctcp_echo_client_dlg::OnBnClickedButtonDisconnectAll()
{
	g_ptest_tcp_echo_client->request_disconnect_socket_all();
}

void Ctcp_echo_client_dlg::OnBnClickedButtonClosesocketSingle()
{
	g_ptest_tcp_echo_client->request_closesocket(1);
}

void Ctcp_echo_client_dlg::OnBnClickedButtonClosesocketAll()
{
	g_ptest_tcp_echo_client->request_closesocket_all();
}


void Ctcp_echo_client_dlg::OnCbnSelchangeComboMessageSize()
{
	// 1) 새로 선택한 값을 읽어온다.
	std::size_t	selected = m_comboMessageSize.GetCurSel();

	// 2) 새로 선택한 값을 써넣는다.
	g_ptest_tcp_echo_client->set_traffic_test_message_size(selected);

	// 3) Randge를 선택한다.
	int	range_max = 128 * 10000;
	for(std::size_t i = 0; i < selected; ++i)
	{
		range_max /=2;
	}

	m_sliderSendTimes.SetRange(0, range_max);
}

void Ctcp_echo_client_dlg::OnBnClickedButtonSingleSend()
{
	g_ptest_tcp_echo_client->request_send_immidiately(1);
}

void Ctcp_echo_client_dlg::OnBnClickedButtonZeroSizeMessage()
{
	g_ptest_tcp_echo_client->request_send_error_message_zero();
}

void Ctcp_echo_client_dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	{
		int	iTimes = m_sliderSendTimes.GetPos();
		SetDlgItemInt(IDC_EDIT_SEND_PER_ONETIME, iTimes);

		g_ptest_tcp_echo_client->set_traffic_test_count_per_single(iTimes);
	}

	__super::OnHScroll(nSBCode, nPos, pScrollBar);
}

void Ctcp_echo_client_dlg::OnEnChangeEditSendPerOnetime()
{
	// check) 윈도우가 생성되어 있지 않으면 끝낸다.
	RETURN_IF(m_sliderSendTimes.m_hWnd == NULL);

	// 1) 횟수를 구한다.
	int	iTimes = GetDlgItemInt(IDC_EDIT_SEND_PER_ONETIME);

	// 2) Slider의 Pos를 설정한다.
	m_sliderSendTimes.SetPos(iTimes);

	// 3) set times
	g_ptest_tcp_echo_client->set_traffic_test_count_per_single(iTimes);
}

void Ctcp_echo_client_dlg::OnBnClickedButtonPool()
{
	m_dlg_object_factory_status.ShowWindow(SW_SHOW);
}

void Ctcp_echo_client_dlg::OnBnClickedButtonThread()
{
	m_dlg_thread_status.ShowWindow(SW_SHOW);
}

void Ctcp_echo_client_dlg::OnDeltaposSpinTps1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	int	iTimes = m_sliderSendTimes.GetPos() - pNMUpDown->iDelta;

	if (iTimes < 0)
		iTimes = 0;

	m_sliderSendTimes.SetPos(iTimes);;
	SetDlgItemInt(IDC_EDIT_SEND_PER_ONETIME, iTimes);
	g_ptest_tcp_echo_client->set_traffic_test_count_per_single(iTimes);

	*pResult = 0;
}

void Ctcp_echo_client_dlg::OnDeltaposSpinTps10(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int	iTimes = m_sliderSendTimes.GetPos() - pNMUpDown->iDelta * 10;

	if (iTimes < 0)
		iTimes = 0;

	m_sliderSendTimes.SetPos(iTimes);;
	SetDlgItemInt(IDC_EDIT_SEND_PER_ONETIME, iTimes);
	g_ptest_tcp_echo_client->set_traffic_test_count_per_single(iTimes);

	*pResult = 0;
}

void Ctcp_echo_client_dlg::OnDeltaposSpinTps100(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int	iTimes = m_sliderSendTimes.GetPos() - pNMUpDown->iDelta * 100;

	if (iTimes < 0)
		iTimes = 0;

	m_sliderSendTimes.SetPos(iTimes);;
	SetDlgItemInt(IDC_EDIT_SEND_PER_ONETIME, iTimes);
	g_ptest_tcp_echo_client->set_traffic_test_count_per_single(iTimes);

	*pResult = 0;
}

void Ctcp_echo_client_dlg::OnDeltaposSpinTps1000(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int	iTimes = m_sliderSendTimes.GetPos() - pNMUpDown->iDelta * 1000;

	if (iTimes < 0)
		iTimes = 0;

	m_sliderSendTimes.SetPos(iTimes);;
	SetDlgItemInt(IDC_EDIT_SEND_PER_ONETIME, iTimes);
	g_ptest_tcp_echo_client->set_traffic_test_count_per_single(iTimes);

	*pResult = 0;
}

void Ctcp_echo_client_dlg::OnDeltaposSpinTps10000(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int	iTimes = m_sliderSendTimes.GetPos() - pNMUpDown->iDelta * 10000;

	if (iTimes < 0)
		iTimes = 0;

	m_sliderSendTimes.SetPos(iTimes);;
	SetDlgItemInt(IDC_EDIT_SEND_PER_ONETIME, iTimes);
	g_ptest_tcp_echo_client->set_traffic_test_count_per_single(iTimes);

	*pResult = 0;
}

void Ctcp_echo_client_dlg::OnDeltaposSpinTps100000(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int	iTimes = m_sliderSendTimes.GetPos() - pNMUpDown->iDelta * 100000;

	if (iTimes < 0)
		iTimes = 0;

	m_sliderSendTimes.SetPos(iTimes);;
	SetDlgItemInt(IDC_EDIT_SEND_PER_ONETIME, iTimes);
	g_ptest_tcp_echo_client->set_traffic_test_count_per_single(iTimes);

	*pResult = 0;
}

BOOL Ctcp_echo_client_dlg::PreTranslateMessage(MSG* pMsg)
{
	m_ctrl_tooltip.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}


