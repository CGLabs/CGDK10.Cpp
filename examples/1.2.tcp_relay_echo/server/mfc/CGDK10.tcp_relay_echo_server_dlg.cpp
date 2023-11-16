#include "pch.h"
#include "framework.h"
#include "CGDK10.tcp_relay_echo_server.mfc.h"
#include "CGDK10.tcp_relay_echo_server_dlg.h"
#include "afxdialogex.h"
#include "socket_tcp_async.h"
#include "socket_tcp_async_gather.h"
#include "socket_tcp_async_gather_buffered.h"
#include "socket_tcp_async_gather_buffered_queued.h"

#if defined(_DEBUG) && !defined(NDEBUG)
	#define new DEBUG_NEW
#endif

own_ptr<net::io::connective::acceptor::Ntcp> g_pacceptor_client;
bool g_disable_echo = false;

Ctcp_relay_echo_server_dlg::Ctcp_relay_echo_server_dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_ECHO_SERVERMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctcp_relay_echo_server_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

#pragma warning(disable:4407)
BEGIN_MESSAGE_MAP(Ctcp_relay_echo_server_dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Ctcp_relay_echo_server_dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Ctcp_relay_echo_server_dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SEND_1, &Ctcp_relay_echo_server_dlg::OnBnClickedButtonSend1)
	ON_BN_CLICKED(IDC_BUTTON_SEND_2, &Ctcp_relay_echo_server_dlg::OnBnClickedButtonSend2)
	ON_BN_CLICKED(IDC_BUTTON_SEND_3, &Ctcp_relay_echo_server_dlg::OnBnClickedButtonSend3)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT_ALL, &Ctcp_relay_echo_server_dlg::OnBnClickedButtonDisconnectAll)
	ON_BN_CLICKED(IDC_BUTTON_CLOSESOCKET_SINGLE, &Ctcp_relay_echo_server_dlg::OnBnClickedButtonClosesocketSingle)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT_SINGLE, &Ctcp_relay_echo_server_dlg::OnBnClickedButtonDisconnectSingle)
	ON_BN_CLICKED(IDC_BUTTON_OBJECTPOOL_STATUS, &Ctcp_relay_echo_server_dlg::OnBnClickedButtonObjectpoolStatus)
	ON_BN_CLICKED(IDC_BUTTON_THREAD_STATUS, &Ctcp_relay_echo_server_dlg::OnBnClickedButtonThreadStatus)
	ON_BN_CLICKED(IDC_CHECK_DISABLE_ECHO, &Ctcp_relay_echo_server_dlg::OnBnClickedCheckDisableEcho)
	ON_COMMAND(ID_SYSTEM_OPTIONS, &Ctcp_relay_echo_server_dlg::OnSystemOptions)
	ON_COMMAND(ID_SYSTEM_CGDKLICENSEINFO, &Ctcp_relay_echo_server_dlg::OnSystemCGDKLicenseInfo)
	ON_COMMAND(ID_SYSTEM_EXIT, &Ctcp_relay_echo_server_dlg::OnSystemExit)
END_MESSAGE_MAP()
#pragma warning(default:4407)


BOOL Ctcp_relay_echo_server_dlg::OnInitDialog()
{
	//-----------------------------------------------------------------
	// 1. 기본적으로 들어 있는 부분.
	//-----------------------------------------------------------------
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	

	//-----------------------------------------------------------------
	// 2. View) Acceptor Info
	//-----------------------------------------------------------------
	// 1) AcceptorControl
	m_child_acceptor_control.CreateChild(NULL, this);
	m_child_acceptor_control.Move(12, -2, ORIGIN_REAR | ORIGIN_TOP, GetDlgItem(IDC_STATIC_BIND));
	m_child_acceptor_control.SetDefaultPort(20000);

	// 2) Connective
	m_child_connective_info.CreateChild(NULL, this);
	m_child_connective_info.MoveToCenter(GetDlgItem(IDC_STATIC_FRAME_CONNECTION_INFO), 0, 5);
	m_child_connective_info.EnableWindow(FALSE);
	m_child_connective_info.SetUpdateInterval(2);

	// 3) Traffic Info
	m_child_traffic_info.CreateChild(&net::io::statistics::Nsocket::statistics_get_traffic_info_total(), this);
	m_child_traffic_info.MoveToCenter(GetDlgItem(IDC_STATIC_FRAME_TRAFFIC_INFO));
	m_child_traffic_info.EnableWindow(FALSE);
	m_child_traffic_info.SetUpdateInterval(2);

	// 4) Factory Status Dialog
	m_dlg_object_factory_status.CreateModaless(factory::manager::instance(), this);

	// 5) Thread StatusDialog
	m_dlg_thread_status.CreateModaless(api::manager_thread::instance(), executor::manager::instance(), system_executor::instance(),  this);

	// 6) Disable Echo
	((CButton*)GetDlgItem(IDC_CHECK_DISABLE_ECHO))->SetCheck(g_disable_echo ? BST_CHECKED : BST_UNCHECKED);


	//-----------------------------------------------------------------
	// 3. 생성하는 부분.
	//
	//    socket_type
	//    - 0 -> socket_tcp_nogather
	//    - 1 -> socket_tcp_gather
	//    - 2 -> socket_tcp_queue
	//    - 3 -> socket_tcp_buffered
	//-----------------------------------------------------------------
	// 1) Acceptor를 생성한다.
	set_socket_type(1);
	//set_socket_type(2);

	// 2) acceptor를 시작한다.
	g_pacceptor_client->start({{ net::ip::tcp::v6(), 20000 }});


	//-----------------------------------------------------------------
	// 4. 연결
	//-----------------------------------------------------------------
	// 1) Link~
	m_child_acceptor_control.AddTargetWnd(&m_child_connective_info);
	m_child_acceptor_control.AddTargetWnd(&m_child_traffic_info);

	// return) 
	return TRUE;
}

void Ctcp_relay_echo_server_dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

void Ctcp_relay_echo_server_dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR Ctcp_relay_echo_server_dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Ctcp_relay_echo_server_dlg::OnBnClickedOk()
{
}

void Ctcp_relay_echo_server_dlg::OnBnClickedCancel()
{
}

void Ctcp_relay_echo_server_dlg::OnBnClickedButtonSend1()
{
	// 1) Acceptor 임시 복사
	object_ptr<net::io::connective::acceptor::Ntcp> pacceptor = g_pacceptor_client;

	// check) pacceptor가 nullptr이면 그냥 리턴~
	RETURN_IF(pacceptor.empty());

	// 2) alloc buffer
	auto buf_temp = alloc_shared_buffer(8);

	// 3) write message
	buf_temp.append<uint32_t>(8);
	buf_temp.append(crc());

	// check)
	CGASSERT_ERROR(buf_temp.size() == 8);

	// 4) send
	pacceptor->send(buf_temp);
}

void Ctcp_relay_echo_server_dlg::OnBnClickedButtonSend2()
{
	// 1) Acceptor 임시 복사
	object_ptr<net::io::connective::acceptor::Ntcp> pacceptor = g_pacceptor_client;

	// check) pacceptor가 nullptr이면 그냥 리턴~
	RETURN_IF(pacceptor.empty());

	// 2) alloc buffer
	auto buf_temp = alloc_shared_buffer(1024);

	// 3) write message
	buf_temp.append<uint32_t>(1024);
	buf_temp.append<uint32_t>(0);

	while (buf_temp.size() < 1024 - SIZE_OF_CRC)
	{
		buf_temp.append<uint32_t>(0);
	}
	buf_temp.append(crc());

	// check)
	CGASSERT_ERROR(buf_temp.size() == 1024);


	// 4) send
	pacceptor->send(buf_temp);
}

void Ctcp_relay_echo_server_dlg::OnBnClickedButtonSend3()
{
	// 1) acceptor 임시 복사
	object_ptr<net::io::connective::acceptor::Ntcp> pacceptor = g_pacceptor_client;

	// check) pacceptor가 nullptr이면 그냥 리턴~
	RETURN_IF(pacceptor.empty());

	// 2) alloc buffer
	auto buf_temp = alloc_shared_buffer(65536);

	// 3) write message
	buf_temp.append<uint32_t>(65536);
	buf_temp.append<uint32_t>(0);

	while (buf_temp.size() < 65536 - SIZE_OF_CRC)
	{
		buf_temp.append<uint32_t>(0);
	}
	buf_temp.append(crc());

	// check)
	CGASSERT_ERROR(buf_temp.size() == 65536);

	// 4) send
	pacceptor->send(buf_temp);
}

void Ctcp_relay_echo_server_dlg::OnBnClickedButtonDisconnectAll()
{
	// 1) acceptor 임시 복사
	object_ptr<net::io::connective::acceptor::Ntcp> pacceptor = g_pacceptor_client;

	// check) pacceptor가 nullptr이면 그냥 리턴~
	RETURN_IF(pacceptor.empty());

	// 2) Acceptor의 Socket을 모두 접속종료한다.
	pacceptor->disconnect_connectable_all();
}

void Ctcp_relay_echo_server_dlg::OnBnClickedButtonClosesocketSingle()
{
	// 1) acceptor의 socket iterator를 얻는다.
	auto iterator  = g_pacceptor_client->alloc_iterator();

	// check) 
	RETURN_IF(iterator.empty());

	// 2) closesocket
	iterator->get_next()->closesocket();
}

void Ctcp_relay_echo_server_dlg::OnBnClickedButtonDisconnectSingle()
{
	// 1) acceptor의 socket iterator를 얻는다.
	auto iterator = g_pacceptor_client->alloc_iterator();

	// check) 
	RETURN_IF(iterator.empty());

	// 2) closesocket
	iterator->get_next()->disconnect();
}

void Ctcp_relay_echo_server_dlg::OnBnClickedButtonObjectpoolStatus()
{
	m_dlg_object_factory_status.ShowWindow(SW_SHOW);
}

void Ctcp_relay_echo_server_dlg::OnBnClickedButtonThreadStatus()
{
	m_dlg_thread_status.ShowWindow(SW_SHOW);
}

void Ctcp_relay_echo_server_dlg::OnBnClickedCheckDisableEcho()
{
	g_disable_echo = ((CButton*)GetDlgItem(IDC_CHECK_DISABLE_ECHO))->GetCheck() == BST_CHECKED;
}

void Ctcp_relay_echo_server_dlg::OnSystemOptions()
{
	// check) Acceptor가 동작중일 때는 이 메뉴를 띄우지 못하게 한다.
	if (g_pacceptor_client != nullptr && g_pacceptor_client->is_listening())
	{
		AfxMessageBox(TEXT("Please close Acceptor first. Click 'start' button to closing Acceptor"), MB_OK);

		// return) 
		return;
	}

	//// Declare) Dialog
	//CSocketTuningDlg	dlg;

	//// 1) Socket Type을 설정한다.
	//dlg.m_socket_type = get_socket_type();

	//// 2) DoModal~
	//if (dlg.DoModal() == IDOK)
	//{
	//	set_socket_type(dlg.m_socket_type);
	//}
}

void Ctcp_relay_echo_server_dlg::OnSystemCGDKLicenseInfo()
{
}

void Ctcp_relay_echo_server_dlg::OnSystemExit()
{
	// 1) confirm
	auto result = AfxMessageBox(TEXT("서버를 종료하시겠습니까?"), MB_OKCANCEL);

	// check)
	RETURN_IF(result != IDOK);

	// 2) close dialogs
	m_child_acceptor_control.DestroyWindow();
	m_child_connective_info.DestroyWindow();
	m_child_traffic_info.DestroyWindow();
	m_dlg_object_factory_status.DestroyWindow();
	m_dlg_thread_status.DestroyWindow();

	// 3) close acceptor
	if (g_pacceptor_client.exist())
	{
		g_pacceptor_client.reset();
	}

	// 3) OnOK => exit
	OnOK();
}


void Ctcp_relay_echo_server_dlg::OnOK()
{
	CDialogEx::OnOK();
}

void Ctcp_relay_echo_server_dlg::OnCancel()
{
	CDialogEx::OnCancel();
}

void Ctcp_relay_echo_server_dlg::set_socket_type(int _socket_type)
{
	// check) 
	RETURN_IF(m_socket_type == _socket_type);

	// 1) 값을 설정한다.
	m_socket_type = _socket_type;

	// 2) Acceptor를 다시 만든다.
	create_acceptor(_socket_type);

	// 3) Pool을 모두 shrink한다.
	factory::manager::instance()->sustain(eFACTORY_GC_LEVEL::STACKED_ALL);
}

void Ctcp_relay_echo_server_dlg::create_acceptor(int _SocketType)
{
	// 1) 기존 Acceptor를 제거한다.
	if(g_pacceptor_client.exist())
	{
		g_pacceptor_client->stop();
		g_pacceptor_client.reset();
	}

	// Declare) 
	own_ptr<net::io::connective::acceptor::Ntcp> pacceptor;

	// 2) 새로운 Acceptor를 생성한다.
	switch(_SocketType)
	{
	case	0:
			{
				pacceptor = make_own<net::acceptor<socket_tcp_async>>("acceptor_async");
			}
			break;

	case	1:
			{
				pacceptor = make_own<net::acceptor<socket_tcp_async_gather>>("acceptor_async_gather");
			}
			break;

	case	2:
			{
				pacceptor = make_own<net::acceptor<socket_tcp_async_gather_buffered>>("acceptor_async_gather_buffered");
			}
			break;

	case	3:
			{
				pacceptor = make_own<net::acceptor<socket_tcp_async_gather_buffered_queued>>("acceptor_async_gather_buffered_queued");
			}
			break;
	}

	// 3) Acceptor를 설정한다.
	g_pacceptor_client = std::move(pacceptor);

	// 4) Connective를 Reset한다.
	m_child_acceptor_control.SetAcceptor(g_pacceptor_client);

	// 5) Acceptor의 이름을 얻는다.
	auto name = g_pacceptor_client->get_name<TCHAR>();

	// 6) Acceptor의 이름을 설정한다.
	SetDlgItemText(IDC_STATIC_ACCEPTOR_NAME, name.c_str());
}
