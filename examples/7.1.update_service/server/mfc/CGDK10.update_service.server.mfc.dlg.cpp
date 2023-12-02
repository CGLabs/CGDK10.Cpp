#include "pch.h"
#include "framework.h"
#include "CGDK10.update_service.server.mfc.h"
#include "CGDK10.update_service.server.mfc.dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

Cupdate_service_server_mfc_dlg::Cupdate_service_server_mfc_dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPDATE_SERVICESERVERMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cupdate_service_server_mfc_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SOCKET, m_listctrl_socket_peer);
	DDX_Control(pDX, IDC_LIST_UPDATABLE_RESOURCE, m_listctrl_updatable_resource);
}

BEGIN_MESSAGE_MAP(Cupdate_service_server_mfc_dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &Cupdate_service_server_mfc_dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Cupdate_service_server_mfc_dlg::OnBnClickedCancel)
	ON_COMMAND(ID_SYSTEM_START, &Cupdate_service_server_mfc_dlg::OnSystemServiceStart)
	ON_COMMAND(ID_SYSTEM_STOP, &Cupdate_service_server_mfc_dlg::OnSystemServiceStop)
	ON_COMMAND(ID_SYSTEM_EXIT, &Cupdate_service_server_mfc_dlg::OnSystemExit)
	ON_COMMAND(ID_SYSTEM_CANCEL, &Cupdate_service_server_mfc_dlg::OnSystemServiceCancel)
	ON_BN_CLICKED(IDC_BUTTON_POOL_STATUS, &Cupdate_service_server_mfc_dlg::OnBnClickedButtonPoolStatus)
	ON_BN_CLICKED(IDC_BUTTON_THREAD_INFO, &Cupdate_service_server_mfc_dlg::OnBnClickedButtonThreadInfo)
	ON_MESSAGE(eMESSAGE::WINDOWS::NOTIFY_UPDATE, &Cupdate_service_server_mfc_dlg::on_notify_message_update)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SOCKET, &Cupdate_service_server_mfc_dlg::OnLvnItemchangedListSocket)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_UPDATABLE_RESOURCE, &Cupdate_service_server_mfc_dlg::OnLvnItemchangedListUpdatableResource)
END_MESSAGE_MAP()

BOOL Cupdate_service_server_mfc_dlg::OnInitDialog()
{
	//-----------------------------------------------------------------
	// 1. MFC Default
	//-----------------------------------------------------------------
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);


	//-----------------------------------------------------------------
	// 2. log 설정
	//-----------------------------------------------------------------
	// 1) create logger view
	m_child_logger_view.CreateChild(nullptr, this);

	// 2) dialog의 크기를 얻는다.
	RECT rect_dlg;
	GetClientRect(&rect_dlg);
	RECT rect_dlg_logger;
	m_child_logger_view.GetClientRect(&rect_dlg_logger);

	// 3) set logger view
	m_child_logger_view.Resize(rect_dlg.right - rect_dlg_logger.right - 16, 30);
	m_child_logger_view.Move(0, -10, ORIGIN_LEFT | ORIGIN_UPON, GetDlgItem(IDC_STATIC_FOOTER));
	m_child_logger_view.Initialize();

	// 4) mfc log control을 연결한다.
	service::get_logger()->register_log_targetable(&m_child_logger_view);


	//-----------------------------------------------------------------
	// 4. 초기화.
	//-----------------------------------------------------------------
	// 1) service를 생성한다.
	g_pservice = make_own<service>();

	// 2) unregister한다.
	g_pservice->register_messageable(this);

	// 3) Service를 initialize한다.
	request_service_initialize();


	//-----------------------------------------------------------------
	// 4. control 설정.
	//-----------------------------------------------------------------
	// 1) socket
	m_listctrl_socket_peer.InsertColumn(0, TEXT("ip"),			LVCFMT_LEFT,  150, 0);
	m_listctrl_socket_peer.InsertColumn(1, TEXT("connected"),	LVCFMT_LEFT,  140, 1);
	m_listctrl_socket_peer.InsertColumn(2, TEXT("ver.req"),		LVCFMT_LEFT,   70, 2);
	m_listctrl_socket_peer.InsertColumn(3, TEXT("ver.now"),		LVCFMT_LEFT,   70, 3);
	m_listctrl_socket_peer.InsertColumn(4, TEXT("bytes/s"),		LVCFMT_RIGHT,  70, 4);
	m_listctrl_socket_peer.InsertColumn(5, TEXT("trans"),		LVCFMT_RIGHT,  50, 5);
	m_listctrl_socket_peer.InsertColumn(6, TEXT("trans.files"),	LVCFMT_RIGHT, 100, 6);
	m_listctrl_socket_peer.InsertColumn(7, TEXT("trans.bytes"),	LVCFMT_RIGHT, 100, 7);
	m_listctrl_socket_peer.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);

	// 2) updatable resource
	m_listctrl_updatable_resource.InsertColumn(0, TEXT("id"),		LVCFMT_LEFT, 40, 0);
	m_listctrl_updatable_resource.InsertColumn(1, TEXT("name"),		LVCFMT_LEFT, 150, 1);
	m_listctrl_updatable_resource.InsertColumn(2, TEXT("type"),		LVCFMT_LEFT, 100, 2);
	m_listctrl_updatable_resource.InsertColumn(3, TEXT("ip"),		LVCFMT_LEFT, 150, 3);
	m_listctrl_updatable_resource.InsertColumn(4, TEXT("connected"),LVCFMT_LEFT, 120, 4);
	m_listctrl_updatable_resource.InsertColumn(5, TEXT("request"),	LVCFMT_RIGHT, 70, 5);
	m_listctrl_updatable_resource.InsertColumn(6, TEXT("success"),	LVCFMT_RIGHT, 70, 6);
	m_listctrl_updatable_resource.InsertColumn(7, TEXT("fail"),		LVCFMT_RIGHT, 50, 7);
	m_listctrl_updatable_resource.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);

	// declare) 
	context temp_context;

	// 2) load json file for setting
	temp_context.read_from_json_file(CONFIGURE_FILE);

	// 3) channeel server socket
	m_child_acceptor_socket_peer.CreateChild(g_pservice->m_pacceptor_tcp, this);
	m_child_acceptor_socket_peer.SetDefaultPort(temp_context["acceptor_user"sv]["local_endpoint"sv]["port"sv]);
	m_child_acceptor_socket_peer.Move(5, 0, ORIGIN_REAR | ORIGIN_CENTER_Y, GetDlgItem(IDC_STATIC_TAG_ACCEPTOR));

	// 4) pool/thread Status Dialog
	m_dlg_factory_status.CreateModaless(factory::manager::instance(), this);
	m_dlg_thread_status.CreateModaless(api::manager_thread::instance(), executor::manager::instance(), system_executor::instance(), this);

	// 5) control을 모두 Disable한다.
	enable_server_controls(FALSE);


	//-----------------------------------------------------------------
	// 6. start
	//-----------------------------------------------------------------
	// 1) start
	request_service_start();


	// return) 
	return TRUE;
}

void Cupdate_service_server_mfc_dlg::OnPaint()
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

HCURSOR Cupdate_service_server_mfc_dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cupdate_service_server_mfc_dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0)
	{
		// check) 
		RETURN_IF(g_pservice.empty(), );

		// - ...
		list_update_event_socket_peer();

		// - ...
		list_update_event_updatable_resource();
	}

	__super::OnTimer(nIDEvent);
}

void Cupdate_service_server_mfc_dlg::OnBnClickedButtonPoolStatus()
{
	m_dlg_factory_status.ShowWindow(SW_SHOW);
}

void Cupdate_service_server_mfc_dlg::OnBnClickedButtonThreadInfo()
{
	m_dlg_thread_status.ShowWindow(SW_SHOW);
}

void Cupdate_service_server_mfc_dlg::OnBnClickedOk()
{
}

void Cupdate_service_server_mfc_dlg::OnBnClickedCancel()
{
}

void Cupdate_service_server_mfc_dlg::OnSystemServiceStart()
{
	request_service_start();
}

void Cupdate_service_server_mfc_dlg::OnSystemServiceCancel()
{
	request_service_cancel();
}

void Cupdate_service_server_mfc_dlg::OnSystemServiceStop()
{
	request_service_stop();
}

void Cupdate_service_server_mfc_dlg::OnSystemExit()
{
	request_service_destroy();
}

void Cupdate_service_server_mfc_dlg::OnSettingConfigures()
{
}

void Cupdate_service_server_mfc_dlg::OnSettingEnginetunning()
{
}

void Cupdate_service_server_mfc_dlg::OnAboutSystemInfo()
{
}

LRESULT Cupdate_service_server_mfc_dlg::on_notify_message_update(WPARAM _wParam, LPARAM _lParam)
{
	switch (_wParam)
	{
	case	eMESSAGE::SERVER::ADMIN::UPDATE_SERVICE_STATUS:	// CGNETMESSAGE_ADMIN_UPDATE_SERVICE_STATUS
			switch ((eOBJECT_STATE)_lParam)
			{
			case	eOBJECT_STATE::STOPPED:
					on_service_stopped();
					break;

			case	eOBJECT_STATE::START_PENDING:
					on_service_start_pending();
					break;

			case	eOBJECT_STATE::RUNNING:
					on_service_running();
					break;

			case	eOBJECT_STATE::STOP_PENDING:
					on_service_stop_pending();
					break;

			case	eOBJECT_STATE::INITIALIZING_PENDING:
					on_service_initializing_pending();
					break;

			case	eOBJECT_STATE::DESTROYING_PENDING:
					on_service_destroying_pending();
					break;

			case	eOBJECT_STATE::UPDATE:
					on_service_update();
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

	case	CGNOTIFY_SERVER_UPDATE:
			{
				g_pservice->release();
			}
			break;
	};

	// return) 
	return S_OK;
}

result_code Cupdate_service_server_mfc_dlg::process_message(sMESSAGE& _msg)
{
	if (_msg.message == eMESSAGE::WINDOWS::NOTIFY_UPDATE)
	{
		sMESSAGE_NOTIFY& msg_notify = (sMESSAGE_NOTIFY&)_msg;

		switch (msg_notify.command)
		{
		case	CGNOTIFY_SERVER_UPDATE:
				{
					g_pservice->add_ref();
				}
				PostMessage(eMESSAGE::WINDOWS::NOTIFY_UPDATE, msg_notify.command, msg_notify.wParam);
				break;

		case	CGNOTIFY_SOCKET_USER_ADD:
		case	CGNOTIFY_SOCKET_USER_REMOVE:
		case	CGNOTIFY_SOCKET_USER_UPDATE:
				{
					scoped_lock(m_cs_vector_event_socket_peer)
					{
						m_vector_event_socket_peer_queuing.emplace_back(EVENT_SOCKET_USER_NOTIFY{ msg_notify.command, (socket_peer*)msg_notify.wParam });
					}
				}
				break;

		case	CGNOTIFY_UPDATABLE_RESOURCE_ADD:
		case	CGNOTIFY_UPDATABLE_RESOURCE_REMOVE:
		case	CGNOTIFY_UPDATABLE_RESOURCE_UPDATE:
				{
					scoped_lock(m_cs_vector_event_updatable_resource)
					{
						m_vector_event_updatable_resource_queuing.emplace_back(EVENT_UPDATABLE_RESOURCE_NOTIFY{ msg_notify.command, (socket_peer*)msg_notify.wParam });
					}
				}
				break;

		default:
				PostMessage(eMESSAGE::WINDOWS::NOTIFY_UPDATE, msg_notify.command, msg_notify.wParam);
				break;
		};

		// return) 
		return eRESULT::DONE;
	}

	// return) 
	return eRESULT::BYPASS;
}

void Cupdate_service_server_mfc_dlg::on_service_initializing_pending()
{
}

void Cupdate_service_server_mfc_dlg::on_service_destroying_pending()
{
}

void Cupdate_service_server_mfc_dlg::on_service_running()
{
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_ENABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_ENABLED);

	enable_server_controls(TRUE);

	auto& server_setting_info = g_pservice->setting();
	SetDlgItemTextA(m_hWnd, IDC_STATIC_SERVER_NAME, server_setting_info.nickname.c_str());
	auto str_server_id = NFMT::format("{}", g_pservice->setting().iid);
	SetDlgItemTextA(m_hWnd, IDC_STATIC_SERVER_ID, str_server_id.c_str());
	auto str_server_version = NFMT::format("{}", server_setting_info.revision.revision);
	SetDlgItemTextA(m_hWnd, IDC_STATIC_SERVER_VERSION, str_server_version.c_str());

	SetTimer(0, 1000, nullptr);
}

void Cupdate_service_server_mfc_dlg::on_service_start_pending()
{
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_DISABLED);
}

void Cupdate_service_server_mfc_dlg::on_service_stop_pending()
{
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_DISABLED);
}

void Cupdate_service_server_mfc_dlg::on_service_stopped()
{
	KillTimer(0);

	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_ENABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_ENABLED);

	enable_server_controls(FALSE);
}

void Cupdate_service_server_mfc_dlg::on_service_update()
{
}

void Cupdate_service_server_mfc_dlg::request_service_initialize()
{
	g_pservice->initialize();
}

void Cupdate_service_server_mfc_dlg::request_service_start()
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

void Cupdate_service_server_mfc_dlg::request_service_cancel()
{
}

void Cupdate_service_server_mfc_dlg::request_service_stop()
{
	// check) 
	RETURN_IF(g_pservice.empty());

	// 1) Menu Control
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_ENABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_CANCEL, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_ENABLED);

	// 2) Close의 실행을 요청한다.
	system_executor::post(make_executable([]()
	{
		g_pservice->stop();
	}));
}

void Cupdate_service_server_mfc_dlg::request_service_destroy()
{
	// 1) 현재 ThreadID를 구한다.(WM_QUIT message는 현재 Thread가 받아야 처리된다.)
	auto thread_id = GetCurrentThreadId();

	// 2) Menu Control
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_CANCEL, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_ENABLED);

	// 3) socket user를 제거한다.
	scoped_lock(m_cs_vector_event_socket_peer)
	{
		m_vector_event_socket_peer_queuing.clear();
		m_vector_event_socket_peer_processing.clear();
	}
	scoped_lock(m_listctrl_socket_peer)
	{
		for (int i = 0; i < m_listctrl_socket_peer.GetItemCount(); ++i)
		{
			// - Item을 얻는다.
			auto* psocket_peer = (socket_peer*)m_listctrl_socket_peer.GetItemData(i);

			// - release한다.
			psocket_peer->release();
		}

		// - 모든 Item을 지운다.
		m_listctrl_socket_peer.DeleteAllItems();
	}

	// 4) updatable resource를 제거한다.
	scoped_lock(m_cs_vector_event_updatable_resource)
	{
		m_vector_event_updatable_resource_queuing.clear();
		m_vector_event_updatable_resource_processing.clear();
	}
	scoped_lock(m_listctrl_updatable_resource)
	{
		for (int i = 0; i < m_listctrl_updatable_resource.GetItemCount(); ++i)
		{
			// - Item을 얻는다.
			auto* pupdatable_resource = (socket_peer*)m_listctrl_updatable_resource.GetItemData(i);

			// - release한다.
			pupdatable_resource->release();
		}

		// - 모든 Item을 지운다.
		m_listctrl_updatable_resource.DeleteAllItems();
	}

	// 5) destroy의 실행을 요청한다.
	system_executor::post(make_executable([=]()
	{
		// - Server를 닫는다.
		g_pservice->destroy();

		// - logger를 등록해제한다.
		service::get_logger()->unregister_log_targetable(&m_child_logger_view);

		// - unregister한다.
		g_pservice->unregister_messageable(this);

		// - QUIT Message를 현재의 Thread에 날린다.(이것으로 어플리케이션은 종료된다.)
		PostThreadMessage(thread_id, WM_QUIT, (WPARAM)IDOK, 0);
	}));
}

void Cupdate_service_server_mfc_dlg::enable_server_controls(BOOL _enable)
{
	// 1) ...
	GetDlgItem(IDC_STATIC_TAG_SERVER_NAME)->EnableWindow(_enable);
	GetDlgItem(IDC_STATIC_SERVER_NAME)->EnableWindow(_enable);
	GetDlgItem(IDC_STATIC_TAG_SERVER_ID)->EnableWindow(_enable);
	GetDlgItem(IDC_STATIC_SERVER_ID)->EnableWindow(_enable);
	GetDlgItem(IDC_STATIC_TAG_SERVER_VERSION)->EnableWindow(_enable);
	GetDlgItem(IDC_STATIC_SERVER_VERSION)->EnableWindow(_enable);

	// 2) Users & clubs
	m_child_acceptor_socket_peer.EnableWindow(_enable);
	m_listctrl_updatable_resource.EnableWindow(_enable);

	// 3) update name
	if(_enable)
	{
	#ifdef _UNICODE
		SetDlgItemTextA(m_hWnd, IDC_STATIC_SERVER_NAME, g_pservice->setting().nickname.c_str());
	#else
		SetDlgItemText(IDC_STATIC_SERVER_NAME, g_pservice->setting().name.c_str());
	#endif
	}
}

void Cupdate_service_server_mfc_dlg::OnLvnItemchangedListSocket(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
}


void Cupdate_service_server_mfc_dlg::OnLvnItemchangedListUpdatableResource(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
}

int Cupdate_service_server_mfc_dlg::list_add_socket_peer(socket_peer* _psocket_peer)
{
	// declare) 
	LV_ITEM	list_item;

	scoped_lock(m_listctrl_socket_peer)
	{
		// declare) 
		WCHAR text[256];

		// 1) 추가한다.
		list_item.iItem = m_listctrl_socket_peer.InsertItem(m_listctrl_socket_peer.GetItemCount(), TEXT(""));

		// 2) club
		list_item.mask = LVIF_TEXT;
		list_item.state = 0;
		list_item.cchTextMax = 256;

		{
			// 0. "ip"
			list_item.iSubItem = 0;
			wsprintf(text, TEXT("%s:%d"), const_cast<TCHAR*>(_psocket_peer->remote_endpoint().to_string<TCHAR>().c_str()), _psocket_peer->remote_endpoint().port());
			list_item.pszText = text;
			m_listctrl_socket_peer.SetItem(&list_item);

			// 1. "connected"
			list_item.iSubItem = 1;
			auto wstr_connect_time = to_string<TCHAR>(_psocket_peer->statistics_get_connect_time(), L"{:04}-{:02}-{:02} {:02}:{:02}:{:02}");
			list_item.pszText = (LPWSTR)wstr_connect_time.c_str();
			m_listctrl_socket_peer.SetItem(&list_item);
		}

		// 2. "ver.req"
		list_item.iSubItem = 2;
		wsprintf(text, TEXT("%d.%02d"), _psocket_peer->m_version_require.major, _psocket_peer->m_version_require.minor);
		list_item.pszText = text;
		m_listctrl_socket_peer.SetItem(&list_item);
		
		// 3. "ver.now"
		list_item.iSubItem = 3;
		wsprintf(text, TEXT("%d.%02d"), _psocket_peer->m_version_now.major, _psocket_peer->m_version_now.minor);
		list_item.pszText = text;
		m_listctrl_socket_peer.SetItem(&list_item);

		// 4. "bytes/s"
		list_item.iSubItem = 4;
		wsprintf(text, TEXT("%I64u"), static_cast<uint64_t>(0));
		list_item.pszText = text;
		m_listctrl_socket_peer.SetItem(&list_item);

		// 5. "trans"
		list_item.iSubItem = 5;
		wsprintf(text, TEXT("%I64u"), static_cast<uint64_t>(0));
		list_item.pszText = text;
		m_listctrl_socket_peer.SetItem(&list_item);

		// 6. "trans.files"
		list_item.iSubItem = 6;
		wsprintf(text, TEXT("%I64u"), static_cast<uint64_t>(0));
		list_item.pszText = text;
		m_listctrl_socket_peer.SetItem(&list_item);

		// 7. "trans.bytes"
		list_item.iSubItem = 7;
		wsprintf(text, TEXT("%I64u"), static_cast<uint64_t>(0));
		list_item.pszText = text;
		m_listctrl_socket_peer.SetItem(&list_item);

		// 4) Item Data로 포인터를 추가한다.
		m_listctrl_socket_peer.SetItemData(list_item.iItem, (DWORD_PTR)_psocket_peer);

		// 5) Index를 ID로 맵핑하여 저장한다.
		_psocket_peer->m_idx_list = m_listctrl_socket_peer.MapIndexToID(list_item.iItem);

		// 6) add_ref한다.
		_psocket_peer->add_ref();

		// 7) Update한다.
		list_update_socket_peer(list_item.iItem);
	}

	// return) 
	return list_item.iItem;
}

void Cupdate_service_server_mfc_dlg::list_remove_socket_peer(socket_peer* _psocket_peer)
{
	// declare) 
	int count_user;

	scoped_lock(m_listctrl_socket_peer)
	{
		// 1) Index를 얻는다.
		int	index = m_listctrl_socket_peer.MapIDToIndex(_psocket_peer->m_idx_list);

		// check)
		RETURN_IF(index < 0)

			// 2) Item을 얻는다.
			auto* psocket_peer = (socket_peer*)m_listctrl_socket_peer.GetItemData(index);

		// check)
		CGASSERT_ERROR(_psocket_peer == psocket_peer);

		// 3) 지운다.
		m_listctrl_socket_peer.DeleteItem(index);

		// 4) reset m_idex_list
		psocket_peer->m_idx_list = static_cast<uint32_t>(-1);

		// 5) release한다.
		psocket_peer->release();

		// 6) ..
		count_user = m_listctrl_socket_peer.GetItemCount();
	}
}

void Cupdate_service_server_mfc_dlg::list_update_socket_peer(socket_peer* _psocket_peer)
{
	scoped_lock(m_listctrl_socket_peer)
	{
		// 1) Index를 얻는다.
		int	index = m_listctrl_socket_peer.MapIDToIndex(_psocket_peer->m_idx_list);

		// check)
		RETURN_IF(index < 0);

		// 2) Group Room을 Update한다.
		list_update_socket_peer(index);
	}
}

void Cupdate_service_server_mfc_dlg::list_update_socket_peer(int _index)
{
	scoped_lock(m_listctrl_socket_peer)
	{
		// check) 
		RETURN_IF(_index < 0 || _index >= m_listctrl_socket_peer.GetItemCount(), );

		// declare) 
		TCHAR text[256]{ 0 };

		// 1) socket_server_lobby을 얻는다.
		auto psocket_peer = (socket_peer*)m_listctrl_socket_peer.GetItemData(_index);

		// 2) update items
		{
			LV_ITEM	list_item;

			list_item.mask = LVIF_TEXT;
			list_item.state = 0;
			list_item.cchTextMax = 256;
			list_item.iItem = _index;

			// 2. "ver.req"
			list_item.iSubItem = 2;
			wsprintf(text, TEXT("%d.%02d"), psocket_peer->m_version_require.major, psocket_peer->m_version_require.minor);
			list_item.pszText = text;
			m_listctrl_socket_peer.SetItem(&list_item);

			// 3. "ver.now"
			list_item.iSubItem = 3;
			wsprintf(text, TEXT("%d.%02d"), psocket_peer->m_version_now.major, psocket_peer->m_version_now.minor);
			list_item.pszText = text;
			m_listctrl_socket_peer.SetItem(&list_item);

			// 4. "bytes/s"
			list_item.iSubItem = 4;
			wsprintf(text, TEXT("%I64u"), static_cast<uint64_t>(0));
			list_item.pszText = text;
			m_listctrl_socket_peer.SetItem(&list_item);

			// 5. "trans"
			list_item.iSubItem = 5;
			wsprintf(text, TEXT("%I64u"), static_cast<uint64_t>(0));
			list_item.pszText = text;
			m_listctrl_socket_peer.SetItem(&list_item);

			// 6. "trans.files"
			list_item.iSubItem = 6;
			wsprintf(text, TEXT("%I64u"), static_cast<uint64_t>(0));
			list_item.pszText = text;
			m_listctrl_socket_peer.SetItem(&list_item);

			// 7. "trans.bytes"
			list_item.iSubItem = 7;
			wsprintf(text, TEXT("%I64u"), static_cast<uint64_t>(0));
			list_item.pszText = text;
			m_listctrl_socket_peer.SetItem(&list_item);
		}
	}
}

void Cupdate_service_server_mfc_dlg::list_update_event_socket_peer()
{
	scoped_lock(m_cs_vector_event_socket_peer)
	{
		m_vector_event_socket_peer_queuing.swap(m_vector_event_socket_peer_processing);
	}

	// check)
	RETURN_IF(m_vector_event_socket_peer_processing.empty());

	{
		m_listctrl_socket_peer.SetRedraw(false);

		scoped_lock(m_listctrl_socket_peer)
		{
			for (auto& iter : m_vector_event_socket_peer_processing)
			{
				switch (iter.message)
				{
				case	CGNOTIFY_SOCKET_USER_ADD:
						list_add_socket_peer(iter.psource);
						break;

				case	CGNOTIFY_SOCKET_USER_REMOVE:
						list_remove_socket_peer(iter.psource);
						break;

				case	CGNOTIFY_SOCKET_USER_UPDATE:
						list_update_socket_peer(iter.psource);
						break;

				default:
						CGASSERT_ERROR(false);
						break;
				}
			}

			// 1) 화면에 보이는 것만 Update한다.
			int	start = m_listctrl_socket_peer.GetTopIndex();
			int	end = m_listctrl_socket_peer.GetTopIndex() + m_listctrl_socket_peer.GetCountPerPage() + 1;

			SATURATE_MAX(end, m_listctrl_socket_peer.GetItemCount());

			for (int i = start; i < end; ++i)
			{
				list_update_socket_peer(i);
			}
		}

		m_listctrl_socket_peer.SetRedraw(true);
	}

	m_vector_event_socket_peer_processing.clear();
}

int Cupdate_service_server_mfc_dlg::list_add_updatable_resource(socket_peer* _psocket_peer)
{
	// declare) 
	LV_ITEM	list_item;

	scoped_lock(m_listctrl_updatable_resource)
	{
		// declare) 
		WCHAR text[256];

		// 1) 추가한다.
		list_item.iItem = m_listctrl_updatable_resource.InsertItem(m_listctrl_updatable_resource.GetItemCount(), TEXT(""));

		// 2) club
		list_item.mask = LVIF_TEXT;
		list_item.state = 0;
		list_item.cchTextMax = 256;

		{
			// 3. "ip"
			list_item.iSubItem = 3;
			wsprintf(text, TEXT("%s:%d"), const_cast<TCHAR*>(_psocket_peer->remote_endpoint().to_string<TCHAR>().c_str()), _psocket_peer->remote_endpoint().port());
			list_item.pszText = text;
			m_listctrl_updatable_resource.SetItem(&list_item);

			// 4. "connected"
			list_item.iSubItem = 4;
			auto wstr_connect_time = to_string<TCHAR>(_psocket_peer->statistics_get_connect_time(), L"{:04}-{:02}-{:02} {:02}:{:02}:{:02}");
			list_item.pszText = (LPWSTR)wstr_connect_time.c_str();
			m_listctrl_updatable_resource.SetItem(&list_item);
		}

		// 5. "request"
		list_item.iSubItem = 5;
		wsprintf(text, TEXT("%I64u"), static_cast<uint64_t>(0));
		list_item.pszText = text;
		m_listctrl_updatable_resource.SetItem(&list_item);

		// 6. "success"
		list_item.iSubItem = 6;
		wsprintf(text, TEXT("%I64u"), static_cast<uint64_t>(0));
		list_item.pszText = text;
		m_listctrl_updatable_resource.SetItem(&list_item);

		// 7. "fail"
		list_item.iSubItem = 7;
		wsprintf(text, TEXT("%I64u"), static_cast<uint64_t>(0));
		list_item.pszText = text;
		m_listctrl_updatable_resource.SetItem(&list_item);

		// 4) Item Data로 포인터를 추가한다.
		m_listctrl_updatable_resource.SetItemData(list_item.iItem, (DWORD_PTR)_psocket_peer);

		// 5) Index를 ID로 맵핑하여 저장한다.
		_psocket_peer->m_idx_list = m_listctrl_updatable_resource.MapIndexToID(list_item.iItem);

		// 6) add_ref한다.
		_psocket_peer->add_ref();

		// 7) Update한다.
		list_update_updatable_resource(list_item.iItem);
	}

	// return) 
	return list_item.iItem;
}

void Cupdate_service_server_mfc_dlg::list_remove_updatable_resource(socket_peer* _psocket_peer)
{
	// declare) 
	int iCountUser;

	scoped_lock(m_listctrl_updatable_resource)
	{
		// 1) Index를 얻는다.
		int	index = m_listctrl_updatable_resource.MapIDToIndex(_psocket_peer->m_idx_list);

		// check)
		RETURN_IF(index < 0)

			// 2) Item을 얻는다.
			auto* psocket_lobby_server = (socket_peer*)m_listctrl_updatable_resource.GetItemData(index);

		// check)
		CGASSERT_ERROR(_psocket_peer == psocket_lobby_server);

		// 3) 지운다.
		m_listctrl_updatable_resource.DeleteItem(index);

		// 4) reset m_idex_list
		psocket_lobby_server->m_idx_list = static_cast<uint32_t>(-1);

		// 5) release한다.
		psocket_lobby_server->release();

		// 6) ..
		iCountUser = m_listctrl_updatable_resource.GetItemCount();
	}
}

void Cupdate_service_server_mfc_dlg::list_update_updatable_resource(socket_peer* _psocket_peer)
{
	scoped_lock(m_listctrl_updatable_resource)
	{
		// 1) Index를 얻는다.
		int	index = m_listctrl_updatable_resource.MapIDToIndex(_psocket_peer->m_idx_list);

		// check)
		RETURN_IF(index < 0)

		// 2) Group Room을 Update한다.
		list_update_updatable_resource(index);
	}
}

void Cupdate_service_server_mfc_dlg::list_update_updatable_resource(int /*_index*/)
{
	//LV_ITEM	list_item;

	//scoped_lock(m_listctrl_updatable_resource)
	//{
	//	// check) 
	//	RETURN_IF(_index < 0 || _index >= m_listctrl_updatable_resource.GetItemCount(), );

	//	// declare) 
	//	TCHAR text[256]{ 0 };

	//	// 1) socket_server_lobby을 얻는다.
	//	auto psocket_server = (socket_peer*)m_listctrl_updatable_resource.GetItemData(_index);

	//	// 2) 
	//	list_item.mask = LVIF_TEXT;
	//	list_item.state = 0;
	//	list_item.cchTextMax = 256;
	//	list_item.iItem = _index;

	//	// 4. "status"
	//	list_item.iSubItem = 4;
	//	list_item.pszText = text;
	//	//list_item.pszText = (LPWSTR)to_string<TCHAR>(psocket_server->m_server_status.server_state).data();
	//	m_listctrl_updatable_resource.SetItem(&list_item);

	//	// 5. "users"
	//	list_item.iSubItem = 5;
	//	//wsprintf(text, TEXT("%d"), psocket_server->m_server_status.user_count);
	//	list_item.pszText = text;
	//	m_listctrl_updatable_resource.SetItem(&list_item);

	//	// 6. "clubs"
	//	list_item.iSubItem = 6;
	//	//wsprintf(text, TEXT("%d"), psocket_server->m_server_status.club_count);
	//	list_item.pszText = text;
	//	m_listctrl_updatable_resource.SetItem(&list_item);
	//}
}

void Cupdate_service_server_mfc_dlg::list_update_event_updatable_resource()
{
	scoped_lock(m_cs_vector_event_updatable_resource)
	{
		m_vector_event_updatable_resource_queuing.swap(m_vector_event_updatable_resource_processing);
	}

	// check)
	RETURN_IF(m_vector_event_updatable_resource_processing.empty());

	{
		m_listctrl_updatable_resource.SetRedraw(false);

		scoped_lock(m_listctrl_updatable_resource)
		{
			for (auto& iter : m_vector_event_updatable_resource_processing)
			{
				switch (iter.message)
				{
				case	CGNOTIFY_UPDATABLE_RESOURCE_ADD:
						list_add_updatable_resource(iter.psource);
						break;

				case	CGNOTIFY_UPDATABLE_RESOURCE_REMOVE:
						list_remove_updatable_resource(iter.psource);
						break;

				case	CGNOTIFY_UPDATABLE_RESOURCE_UPDATE:
						list_update_updatable_resource(iter.psource);
						break;

				default:
						CGASSERT_ERROR(false);
						break;
				}
			}

			// 1) 화면에 보이는 것만 Update한다.
			int	start = m_listctrl_updatable_resource.GetTopIndex();
			int	end = m_listctrl_updatable_resource.GetTopIndex() + m_listctrl_updatable_resource.GetCountPerPage() + 1;

			SATURATE_MAX(end, m_listctrl_updatable_resource.GetItemCount());

			for (int i = start; i < end; ++i)
			{
				list_update_updatable_resource(i);
			}
		}

		m_listctrl_updatable_resource.SetRedraw(true);
	}

	m_vector_event_updatable_resource_processing.clear();
}
