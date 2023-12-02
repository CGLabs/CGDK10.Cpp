#include "pch.h"
#include "framework.h"
#include "tutorial.server.service_ex_dlg.h"
#include "tutorial.server.service_ex_dlg.h"
#include "afxdialogex.h"

bool g_b_auto_start = true;

#if defined(_DEBUG) && !defined(NDEBUG)
	#define new DEBUG_NEW
#endif

Ctutorial_server_service_ex_dlg::Ctutorial_server_service_ex_dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TUTORIAL_SERVER_SERVICE_EX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctutorial_server_service_ex_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

#pragma warning(disable:4407)
BEGIN_MESSAGE_MAP(Ctutorial_server_service_ex_dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK,								&Ctutorial_server_service_ex_dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL,							&Ctutorial_server_service_ex_dlg::OnBnClickedCancel)

	ON_BN_CLICKED(IDC_BUTTON_POOL_STATUS,			&Ctutorial_server_service_ex_dlg::OnBnClickedButtonPoolStatus)
	ON_BN_CLICKED(IDC_BUTTON_THREAD_INFO,			&Ctutorial_server_service_ex_dlg::OnBnClickedButtonThreadInfo)
	ON_BN_CLICKED(IDC_BUTTON_LICENSE_INFO,			&Ctutorial_server_service_ex_dlg::OnBnClickedButtonLicenseInfo)

	ON_COMMAND(ID_SYSTEM_START,						&Ctutorial_server_service_ex_dlg::OnSystemStart)
	ON_COMMAND(ID_SYSTEM_CANCEL,					&Ctutorial_server_service_ex_dlg::OnSystemCancel)
	ON_COMMAND(ID_SYSTEM_STOP,						&Ctutorial_server_service_ex_dlg::OnSystemStop)
	ON_COMMAND(ID_SYSTEM_EXIT,						&Ctutorial_server_service_ex_dlg::OnSystemExit)

	ON_MESSAGE(eMESSAGE::WINDOWS::NOTIFY_UPDATE,	&Ctutorial_server_service_ex_dlg::OnNotifymessage_Update)

END_MESSAGE_MAP()
#pragma warning(default:4407)

BOOL Ctutorial_server_service_ex_dlg::OnInitDialog()
{
	//-----------------------------------------------------------------
	// 1. MFC Default
	//-----------------------------------------------------------------
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);


	//-----------------------------------------------------------------
	// 2. Log 설정
	//-----------------------------------------------------------------
	// 1) Log View
	m_child_logger_view.CreateChild(nullptr, this);
	m_child_logger_view.Resize(94, 20);
	m_child_logger_view.Move(0, 15, ORIGIN_LEFT | ORIGIN_BELOW, GetDlgItem(IDC_STATIC_FRAME_TRAFFIC_INFO));
	m_child_logger_view.Initialize();

	// 2) mfc log control을 연결한다.
	service::get_logger()->register_log_targetable(&m_child_logger_view);


	//-----------------------------------------------------------------
	// 3. 초기화.
	//-----------------------------------------------------------------
	// 1) Service를 생성한다.
	g_pservice = make_own<service>();

	// 2) unregister한다.
	g_pservice->register_messageable(this);

	// 3) Service를 initialize한다.
	request_service_initialize();


	//-----------------------------------------------------------------
	// 4. Control 설정.
	//-----------------------------------------------------------------
	// 1) Control Server Connector
	m_child_socket.CreateChild(g_pservice->m_psocket_tcp, htons(0), this);
	m_child_socket.Move(5, 0, ORIGIN_REAR | ORIGIN_CENTER_Y, GetDlgItem(IDC_STATIC_TAG_SOCKET_TCP_SERVER));

	// 2) user Acceptor Control
	m_child_acceptor_user.CreateChild(g_pservice->m_pacceptor_user, this); 
	m_child_acceptor_user.Move(5, 0, ORIGIN_REAR | ORIGIN_CENTER_Y, GetDlgItem(IDC_STATIC_TAG_ACCEPTOR_USER));

	// 3) Connection Info
	m_child_traffic_info.CreateChild(&net::io::statistics::Nsocket::statistics_get_traffic_info_total(), this);
	m_child_traffic_info.Move(0, 30, ORIGIN_CENTER_X | ORIGIN_TOP, GetDlgItem(IDC_STATIC_FRAME_TRAFFIC_INFO));

	// 4) Pool/Thread/CGDKInfo Status Dialog
	m_dlg_factory_status.CreateModaless(CGDK::factory::manager::instance(), this);
	m_dlg_thread_status.CreateModaless(api::manager_thread::instance(), executor::manager::instance(), system_executor::instance(), this);

	// 5) Control을 모두 Disable한다.
	enable_server_controls(FALSE);


	//-----------------------------------------------------------------
	// 5. start
	//-----------------------------------------------------------------
	// 1) auto start
	if (g_b_auto_start == true)
	{
		request_service_start();
	}

	// return) 
	return TRUE;
}

void Ctutorial_server_service_ex_dlg::OnPaint()
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

HCURSOR Ctutorial_server_service_ex_dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Ctutorial_server_service_ex_dlg::OnBnClickedOk()
{
}

void Ctutorial_server_service_ex_dlg::OnBnClickedCancel()
{
}

void Ctutorial_server_service_ex_dlg::OnBnClickedButtonPoolStatus()
{
	m_dlg_factory_status.ShowWindow(SW_SHOW);
}

void Ctutorial_server_service_ex_dlg::OnBnClickedButtonThreadInfo()
{
	m_dlg_thread_status.ShowWindow(SW_SHOW);
}

void Ctutorial_server_service_ex_dlg::OnBnClickedButtonLicenseInfo()
{
}

void Ctutorial_server_service_ex_dlg::OnSystemStart()
{
	request_service_start();
}

void Ctutorial_server_service_ex_dlg::OnSystemCancel()
{
	request_service_cancel();
}

void Ctutorial_server_service_ex_dlg::OnSystemStop()
{
	request_service_stop();
}

void Ctutorial_server_service_ex_dlg::OnSystemExit()
{
	// 1) 종료의사를 확인을 한다.
	int result = AfxMessageBox(TEXT("Do you want to EXIT?"), MB_OKCANCEL);

	// check) OK가 아니면 취소한다.
	RETURN_IF(result != IDOK);

	// 2) Server destroy를 요청한다.
	request_service_destroy();
}

result_code Ctutorial_server_service_ex_dlg::process_message(sMESSAGE& _msg)
{
	if (_msg.message == eMESSAGE::WINDOWS::NOTIFY_UPDATE)
	{
		sMESSAGE_NOTIFY& msg = reinterpret_cast<sMESSAGE_NOTIFY&>(_msg);

		switch (msg.command)
		{
		case	MESSAGE_NOTIFY_UPDATE_SYSTEMSTATUS_INFO:
				{
				}
				break;

		case	MESSAGE_NOTIFY_SOCKET_CONNECT:
		case	MESSAGE_NOTIFY_SOCKET_DISCONNECT:
		case	MESSAGE_NOTIFY_SOCKET_UPDATE:
				{
					reinterpret_cast<socket_tcp_user*>(msg.wParam)->add_ref();
				}
				break;
		};

		PostMessage(eMESSAGE::WINDOWS::NOTIFY_UPDATE, msg.command, msg.wParam);

		// Return) 
		return	TRUE;
	}

	// Return) 
	return eRESULT::BYPASS;
}

void Ctutorial_server_service_ex_dlg::OnServiceInitializingPending()
{
}

void Ctutorial_server_service_ex_dlg::OnServicedestroyingPending()
{
}

void Ctutorial_server_service_ex_dlg::OnServiceRunning()
{
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_ENABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_ENABLED);

	enable_server_controls(TRUE);

	SetTimer(0, 1000, nullptr);
}

void Ctutorial_server_service_ex_dlg::OnServiceStartPending()
{
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_DISABLED);
}

void Ctutorial_server_service_ex_dlg::OnServiceStopPending()
{
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_DISABLED);
}

void Ctutorial_server_service_ex_dlg::OnServiceStopped()
{
	KillTimer(0);

	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_ENABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_ENABLED);

	enable_server_controls(FALSE);
}

void Ctutorial_server_service_ex_dlg::OnServiceUpdate()
{
}


LRESULT Ctutorial_server_service_ex_dlg::OnNotifymessage_Update(WPARAM _wParam, LPARAM _lParam)
{
	switch (_wParam)
	{
	case	eMESSAGE::SERVER::ADMIN::UPDATE_SERVICE_STATUS:
			switch ((eOBJECT_STATE)_lParam)
			{
			case	eOBJECT_STATE::STOPPED:
					OnServiceStopped();
					break;

			case	eOBJECT_STATE::START_PENDING:
					OnServiceStartPending();
					break;

			case	eOBJECT_STATE::RUNNING:
					OnServiceRunning();
					break;

			case	eOBJECT_STATE::STOP_PENDING:
					OnServiceStopPending();
					break;

			case	eOBJECT_STATE::INITIALIZING_PENDING:
					OnServiceInitializingPending();
					break;

			case	eOBJECT_STATE::DESTROYING_PENDING:
					OnServicedestroyingPending();
					break;

			case	eOBJECT_STATE::UPDATE:
					OnServiceUpdate();
					break;
			};
			break;

	case	eMESSAGE::SERVER::ADMIN::REQUEST_INIT_SERVICE:
			{
				request_service_initialize();
			}
			break;

	case	eMESSAGE::SERVER::ADMIN::REQUEST_DESTROY_SERVICE:
			{
				request_service_destroy();
			}
			break;

	case	eMESSAGE::SERVER::ADMIN::REQUEST_START_SERVICE:
			{
				request_service_start();
			}
			break;

	case	eMESSAGE::SERVER::ADMIN::REQUEST_STOP_SERVICE:
			{
				request_service_stop();
			}
			break;

	case	eMESSAGE::SERVER::ADMIN::REQUEST_PAUSE_SERVICE:
			{
			}
			break;
	case	eMESSAGE::SERVER::ADMIN::REQUEST_CONTINUE_SERVICE:
			{
			}
			break;

	case	MESSAGE_NOTIFY_SOCKET_CONNECT:
			{
				OnSocketConnect(reinterpret_cast<socket_tcp_user*>(_lParam));
				reinterpret_cast<socket_tcp_user*>(_lParam)->release();
			}
			break;

	case	MESSAGE_NOTIFY_SOCKET_DISCONNECT:
			{
				OnSocketDisconnect(reinterpret_cast<socket_tcp_user*>(_lParam));
				reinterpret_cast<socket_tcp_user*>(_lParam)->release();
			}
			break;

	case	MESSAGE_NOTIFY_SOCKET_UPDATE:
			{
				OnSocketUpdate(reinterpret_cast<socket_tcp_user*>(_lParam));
				reinterpret_cast<socket_tcp_user*>(_lParam)->release();
			}
			break;
	};

	// Return) 
	return	TRUE;
}

void Ctutorial_server_service_ex_dlg::OnSocketConnect(socket_tcp_user* /*_psocket*/)
{
}
void Ctutorial_server_service_ex_dlg::OnSocketDisconnect(socket_tcp_user* /*_psocket*/)
{
}
void Ctutorial_server_service_ex_dlg::OnSocketUpdate(socket_tcp_user* /*_psocket*/)
{
}

void Ctutorial_server_service_ex_dlg::request_service_initialize()
{
	g_pservice->initialize();
}

void Ctutorial_server_service_ex_dlg::request_service_start()
{
	// check) 
	RETURN_IF(g_pservice.empty());

	// 1) Menu Control
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_CANCEL, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_ENABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_ENABLED);

	// 2) Open의 실행을 요청한다.
	system_executor::post(make_executable([]()
	{
		g_pservice->start();
	}));
}

void Ctutorial_server_service_ex_dlg::request_service_cancel()
{
}

void Ctutorial_server_service_ex_dlg::request_service_stop()
{
	// check) 
	RETURN_IF(g_pservice.empty());

	// 1) Menu Control
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_ENABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_CANCEL, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_ENABLED);

	// 2) stop의 실행을 요청한다.
	system_executor::post(make_executable([]()
	{
		g_pservice->stop();
	}));
}

void Ctutorial_server_service_ex_dlg::request_service_destroy()
{
	// 1) 현재 ThreadID를 구한다.(WM_QUIT message는 현재 Thread가 받아야 처리된다.)
	auto thread_id = GetCurrentThreadId();

	// 2) Menu Control
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_CANCEL, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_ENABLED);

	// 3) destroy의 실행을 요청한다.
	system_executor::post(make_executable([=]
	{
		// - Server를 닫는다.
		g_pservice->destroy();

		// - Trace를 등록해제한다.
		service::get_logger()->unregister_log_targetable(&m_child_logger_view);

		// - unregister한다.
		g_pservice->unregister_messageable(this);

		// - QUIT Message를 현재의 Thread에 날린다.(이것으로 어플리케이션은 종료된다.)
		PostThreadMessage(thread_id, WM_QUIT, (WPARAM)-1, 0);
	}));
}

void Ctutorial_server_service_ex_dlg::enable_server_controls(BOOL _bEnable)
{
	// 1) connector & acceptor info
	GetDlgItem(IDC_STATIC_TAG_ACCEPTOR_USER)->EnableWindow(_bEnable);
	m_child_acceptor_user.EnableWindow(_bEnable);
	GetDlgItem(IDC_STATIC_TAG_SOCKET_TCP_SERVER)->EnableWindow(_bEnable);
	m_child_socket.EnableWindow(_bEnable);

	// 2) traffic info
	GetDlgItem(IDC_STATIC_FRAME_TRAFFIC_INFO)->EnableWindow(_bEnable);
	m_child_traffic_info.EnableWindow(_bEnable);
}

