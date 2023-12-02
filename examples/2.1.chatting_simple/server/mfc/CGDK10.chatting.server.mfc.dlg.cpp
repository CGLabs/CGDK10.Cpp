#include "pch.h"
#include "framework.h"
#include "CGDK10.chatting.server.mfc.h"
#include "CGDK10.chatting.server.mfc.dlg.h"
#include "channel_setting_dlg.h"
#include "afxdialogex.h"

bool g_b_auto_start = true;

#if defined(_DEBUG) && !defined(NDEBUG)
	#define new DEBUG_NEW
#endif

// chatting_server_dlg 대화 상자
chatting_server_dlg::chatting_server_dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHATTING_SERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void chatting_server_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHANNEL, m_list_channel);
}

BEGIN_MESSAGE_MAP(chatting_server_dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &chatting_server_dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &chatting_server_dlg::OnBnClickedCancel)
	ON_COMMAND(ID_ABOUT_APPLICATION_INFO, &chatting_server_dlg::OnAboutApplicationInfo)
	ON_COMMAND(ID_SYSTEM_START, &chatting_server_dlg::OnSystemServiceStart)
	ON_COMMAND(ID_SYSTEM_STOP, &chatting_server_dlg::OnSystemServiceStop)
	ON_COMMAND(ID_SYSTEM_EXIT, &chatting_server_dlg::OnSystemExit)
	//ON_COMMAND(ID_SETTING_CONFIQURES, &chatting_server_dlg::OnSettingConfigures)
	ON_COMMAND(ID_SETTING_SYSTEM_TUNNING, &chatting_server_dlg::OnSettingEnginetunning)
	ON_COMMAND(ID_ABOUT_SYSTEM_INFO, &chatting_server_dlg::OnAboutSystemInfo)
	ON_COMMAND(ID_SYSTEM_CANCEL, &chatting_server_dlg::OnSystemServiceCancel)
	ON_BN_CLICKED(IDC_BUTTON_POOL_STATUS, &chatting_server_dlg::OnBnClickedButtonPoolStatus)
	ON_BN_CLICKED(IDC_BUTTON_THREAD_INFO, &chatting_server_dlg::OnBnClickedButtonThreadInfo)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL_NEW, &chatting_server_dlg::OnBnClickedButtonChannelNew)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL_DESTROY, &chatting_server_dlg::OnBnClickedButtonChannelDestroy)
	ON_MESSAGE(eMESSAGE::WINDOWS::NOTIFY_UPDATE, &chatting_server_dlg::OnNotifymessage_Update)
	ON_NOTIFY(NM_RDBLCLK, IDC_LIST_CHANNEL, &chatting_server_dlg::OnNMRDblclkListChannel)
END_MESSAGE_MAP()

BOOL chatting_server_dlg::OnInitDialog()
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
	m_child_log_view.CreateChild(nullptr, this);
	m_child_log_view.Resize(70, -26);
	m_child_log_view.Move(4, 195, ORIGIN_LEFT | ORIGIN_BELOW, GetDlgItem(IDC_STATIC_FRAME_CHANNEL_INFO));

	// 2) mfc log control을 연결한다.
	service::get_logger()->register_log_targetable(&m_child_log_view);


	//-----------------------------------------------------------------
	// 3. MFC controls
	//-----------------------------------------------------------------
	// 1) Channel Room
	m_list_channel.InsertColumn(0, TEXT("CHANNEL ID"), LVCFMT_LEFT, 80, 0);
	m_list_channel.InsertColumn(1, TEXT("Name"), LVCFMT_LEFT, 180, 1);
	m_list_channel.InsertColumn(2, TEXT("Type"), LVCFMT_LEFT, 100, 2);
	m_list_channel.InsertColumn(3, TEXT("Users"), LVCFMT_RIGHT, 60, 3);
	m_list_channel.InsertColumn(4, TEXT("Max Users"), LVCFMT_RIGHT, 80, 4);
	m_list_channel.InsertColumn(5, TEXT("Create"), LVCFMT_LEFT, 120, 5);
	m_list_channel.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);


	//-----------------------------------------------------------------
	// 4. 초기화.
	//-----------------------------------------------------------------
	// 1) Service를 생성한다.
	g_pservice = make_own<service>();

	// 2) unregister한다.
	g_pservice->register_messageable(this);

	// 3) Service를 initialize한다.
	request_service_initialize();


	//-----------------------------------------------------------------
	// 5. Control 설정.
	//-----------------------------------------------------------------
	// Declare) 
	context	tempContext;

	// 1) Load Json file for setting
	tempContext.read_from_json_file("../chatting_server/chatting_server_setting.json"sv);

	// 2) User
	m_child_acceptor_user.CreateChild(g_pservice->m_pacceptor_user, this);
	m_child_acceptor_user.SetDefaultPort(tempContext["acceptor_user"sv]["local endpoint"sv]["Port"sv]);
	m_child_acceptor_user.Move(5, 0, ORIGIN_REAR | ORIGIN_CENTER_Y, GetDlgItem(IDC_STATIC_ACCEPTOR_USER));

	// 3) User
	m_child_traffic_info.CreateChild(&net::io::statistics::Nsocket::statistics_get_traffic_info_total(), this);
	m_child_traffic_info.Move(10, 20, ORIGIN_CENTER_X | ORIGIN_BELOW, GetDlgItem(IDC_STATIC_FRAME_CHANNEL_INFO));
	m_child_traffic_info.EnableWindow(FALSE);
	m_child_traffic_info.SetUpdateInterval(2);

	// 4) Pool Status Dialog
	m_dlg_object_factory_status.CreateModaless(factory::manager::instance(), this);

	// 5) Thread StatusDialog
	m_dlg_thread_status.CreateModaless(api::manager_thread::instance(), executor::manager::instance(), system_executor::instance(), this);

	// 6) Control을 모두 Disable한다.
	EnableServerControls(FALSE);


	//-----------------------------------------------------------------
	// 5. start
	//-----------------------------------------------------------------
	// 1) auto start
	if (g_b_auto_start == true)
	{
		request_service_start();
	}


	// return)
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void chatting_server_dlg::OnPaint()
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

HCURSOR chatting_server_dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void chatting_server_dlg::OnBnClickedOk()
{
}

void chatting_server_dlg::OnBnClickedCancel()
{
}

void chatting_server_dlg::OnSystemServiceStart()
{
	request_service_start();
}

void chatting_server_dlg::OnSystemServiceCancel()
{
	RequestServiceCancel();
}

void chatting_server_dlg::OnSystemServiceStop()
{
	RequestServiceStop();
}
									  
void chatting_server_dlg::OnSystemExit()
{
	RequestServiceDestroy();
}
										   
void chatting_server_dlg::OnSettingConfigures()
{
}
										   
void chatting_server_dlg::OnSettingEnginetunning()
{
}
										   
void chatting_server_dlg::OnAboutSystemInfo()
{
}

void chatting_server_dlg::OnAboutApplicationInfo()
{
}

result_code chatting_server_dlg::process_message(sMESSAGE& _msg)
{
	if (_msg.message == eMESSAGE::WINDOWS::NOTIFY_UPDATE)
	{
		auto& msg = reinterpret_cast<sMESSAGE_NOTIFY&>(_msg);

		switch (msg.command)
		{
		case	CGNOTIFY_SERVER_UPDATE:
				{
					g_pservice->add_ref();
				}
				PostMessage(eMESSAGE::WINDOWS::NOTIFY_UPDATE, msg.command, msg.lParam);
				break;

		case	CGNOTIFY_CHANNEL_ADD:
		case	CGNOTIFY_CHANNEL_REMOVE:
		case	CGNOTIFY_CHANNEL_UPDATE:
				{
					scoped_lock(m_lockable_vector_event)
					{
						m_vector_event_queuing.emplace_back(EVENT_NOTIFY{ msg.command, reinterpret_cast<channel::Igroup*>(msg.lParam) });
					}
				}
				break;

		default:
				PostMessage(eMESSAGE::WINDOWS::NOTIFY_UPDATE, msg.command, msg.lParam);
				break;
		};


		// return)
		return eRESULT::DONE;
	}

	// return)
	return eRESULT::BYPASS;
}

LRESULT chatting_server_dlg::OnNotifymessage_Update(WPARAM _wparam, LPARAM _lparam)
{
	switch (_wparam)
	{
	case	eMESSAGE::SERVER::ADMIN::UPDATE_SERVICE_STATUS:	// CGNETMESSAGE_ADMIN_UPDATE_SERVICE_STATUS
			switch ((eOBJECT_STATE)_lparam)
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
					OnServiceDestroyingPending();
					break;

			case	eOBJECT_STATE::UPDATE:
					OnServiceUpdate();
					break;
			};
			break;

	case	eMESSAGE::SERVER::ADMIN::REQUEST_STOP_SERVICE:	// CGNETMESSAGE_ADMIN_REQUEST_STOP_SERVICE
			{
				RequestServiceStop();
			}
			break;


	case	CGNOTIFY_SERVER_UPDATE:
			{
				g_pservice->release();
			}
			break;
	};

	// return)
	return	S_OK;
}

void chatting_server_dlg::OnServiceInitializingPending()
{
}

void chatting_server_dlg::OnServiceDestroyingPending()
{
}

void chatting_server_dlg::OnServiceRunning()
{
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_ENABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_ENABLED);

	EnableServerControls(TRUE);

	SetTimer(0, 1000, nullptr);
}

void chatting_server_dlg::OnServiceStartPending()
{
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_DISABLED);
}

void chatting_server_dlg::OnServiceStopPending()
{
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_DISABLED);
}

void chatting_server_dlg::OnServiceStopped()
{
	KillTimer(0);

	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_ENABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_ENABLED);

	EnableServerControls(FALSE);
}

void chatting_server_dlg::OnServiceUpdate()
{
}

void chatting_server_dlg::OnChannelAdd(channel::Igroup* _pgroupchannel)
{
	List_AddChannel(_pgroupchannel);
}

void chatting_server_dlg::OnChannelRemove(channel::Igroup* _pgroupchannel)
{
	List_RemoveChannel(_pgroupchannel);
}

void chatting_server_dlg::OnChannelUpdate(channel::Igroup* _pgroupchannel)
{
	List_UpdateChannel(_pgroupchannel);
}

void chatting_server_dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0)
	{
		// check) 
		RETURN_IF(g_pservice.empty());

		// - 화면에 보이는 Channel을 Update~
		List_UpdateChannel();

		SetDlgItemInt(IDC_STATIC_USER_COUNT, static_cast<UINT>(g_pservice->m_pacceptor_user->count()));
		SetDlgItemInt(IDC_STATIC_CHANNEL_COUNT, static_cast<int>(g_pservice->m_pmanager_channel->get_channel_count()));
	}

	__super::OnTimer(nIDEvent);
}

void chatting_server_dlg::OnBnClickedButtonPoolStatus()
{
	m_dlg_object_factory_status.ShowWindow(SW_SHOW);
}

void chatting_server_dlg::OnBnClickedButtonThreadInfo()
{
	m_dlg_thread_status.ShowWindow(SW_SHOW);
}

void chatting_server_dlg::OnBnClickedButtonChannelNew()
{
	CDialogChannelSetting	dlg;

	dlg.m_str_name.clear();
	dlg.m_id_channel = 0;
	dlg.m_channel_option = eCHANNEL_OPTION::DESTROY_ON_EMPTY | eCHANNEL_OPTION::HAS_MAX_MEMBER;
	dlg.m_channel_type = eCHANNEL_TYPE::CHATTING;
	dlg.m_max_member = 12;
	dlg.m_str_password.clear();

	if (dlg.DoModal() == IDOK)
	{
		// check) 
		CGASSERT_ERROR(dlg.m_max_member != 0);

		// 1) 없으면 Channel 객체를 생성한다.
		auto pgroup_channel_create = make_own<channel::group_chatting>();
			
		// 2) Type과 Option을 설정한다.
		pgroup_channel_create->set_name(dlg.m_str_name);
		pgroup_channel_create->m_type_channel = dlg.m_channel_type;
		pgroup_channel_create->m_option_channel = dlg.m_channel_option;
		pgroup_channel_create->member_capacity(dlg.m_max_member);

		// 3) 생성한 Channel 객체를 등록한다.
		auto pgroup_channel = g_pservice->m_pmanager_channel->register_channel(dlg.m_id_channel, std::move(pgroup_channel_create));

		// 4) pgroup_channel을 start한다.
		if (pgroup_channel.exist())
		{
			pgroup_channel->start();
		}
		else
		{
			AfxMessageBox(TEXT("Fail to create CHANNEL!"), MB_OK);
		}
	}
}
void chatting_server_dlg::OnBnClickedButtonChannelDestroy()
{
	scoped_lock(m_list_channel)
	{
		for (int i=0;i<m_list_channel.GetItemCount(); ++i)
		{
			if (m_list_channel.GetItemState(i, LVIS_SELECTED) != 0)
			{
				// - Item을 얻는다.
				channel::Igroup* pchannel = (channel::Igroup*)m_list_channel.GetItemData(i);

				// check) System 속성은 고의로 지울 수 없다.
				if ((pchannel->m_option_channel & eCHANNEL_OPTION::SYSTEM) != eCHANNEL_OPTION::NONE)
				{
					LOG_SYSTEM << "!err) can't destroy eCHANNEL_OPTION::SYSTEM channel ("sv << pchannel->name() << "["sv << pchannel->get_channel_id() << "])"sv;
					continue;
				}

				// - Channel을 파괴한다.
				LOG_SYSTEM << "  < destroy channel("sv << pchannel->name() << "["sv << pchannel->get_channel_id() << "]) by force"sv;

				// - 지운다.
				pchannel->destroy();
			}
		}
	}
}

void chatting_server_dlg::request_service_initialize()
{
	g_pservice->initialize();
}

void chatting_server_dlg::request_service_start()
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

void chatting_server_dlg::RequestServiceCancel()
{
}

void chatting_server_dlg::RequestServiceStop()
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

void chatting_server_dlg::RequestServiceDestroy()
{
	// 1) Menu Control
	GetMenu()->EnableMenuItem(ID_SYSTEM_START, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_CANCEL, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_STOP, MF_DISABLED);
	GetMenu()->EnableMenuItem(ID_SYSTEM_EXIT, MF_ENABLED);

	// 2) 
	scoped_lock(m_lockable_vector_event)
	{
		m_vector_event_queuing.clear();
		m_vector_event_processing.clear();
	}

	// 3) List를 제거한다.
	scoped_lock(m_list_channel)
	{
		for(int i=0; i<m_list_channel.GetItemCount(); ++i)
		{
			// - Item을 얻는다.
			channel::Igroup* pchannel = (channel::Igroup*)m_list_channel.GetItemData(i);

			// - release한다.
			pchannel->release();
		}

		// - 모든 Item을 지운다.
		m_list_channel.DeleteAllItems();
	}

	// 4) 현재 ThreadID를 구한다.(WM_QUIT message는 현재 Thread가 받아야 처리된다.)
	auto thread_id = GetCurrentThreadId();

	// 5) destroy의 실행을 요청한다.
	system_executor::post(make_executable([=]
	{
		// - Server를 닫는다.
		g_pservice->destroy();

		// - Trace를 등록해제한다.
		service::get_logger()->unregister_log_targetable(&m_child_log_view);

		// - unregister한다.
		g_pservice->unregister_messageable(this);

		// - QUIT Message를 현재의 Thread에 날린다.(이것으로 어플리케이션은 종료된다.)
		PostThreadMessage(thread_id, WM_QUIT, (WPARAM)-1, 0);
	}));
}

void chatting_server_dlg::EnableServerControls(BOOL _bEnable)
{
	// 1) ...
	GetDlgItem(IDC_STATIC_SERVER_VERSION_TAG)->EnableWindow(_bEnable);
	GetDlgItem(IDC_STATIC_SERVER_VERSION)->EnableWindow(_bEnable);

	GetDlgItem(IDC_STATIC_SVN_VERSION_TAG)->EnableWindow(_bEnable);
	GetDlgItem(IDC_STATIC_SVN_VERSION)->EnableWindow(_bEnable);

	// 2) Users & Channels
	m_child_acceptor_user.EnableWindow(_bEnable);
	GetDlgItem(IDC_STATIC_FRAME_CHANNEL_INFO)->EnableWindow(_bEnable);
	GetDlgItem(IDC_STATIC_ACCEPTOR_USER)->EnableWindow(_bEnable);
	m_child_acceptor_user.EnableWindow(_bEnable);
	m_list_channel.EnableWindow(_bEnable);

	// 3) Traffic
	m_child_traffic_info.EnableWindow(_bEnable);
}

int chatting_server_dlg::List_AddChannel(channel::Igroup* _pgroupchannel)
{
	// Declare) 
	WCHAR	text[256];
	LV_ITEM	list_item;
	int		countChannel;

	scoped_lock(m_list_channel)
	{
		// 1) 추가한다.
		list_item.iItem = m_list_channel.InsertItem(m_list_channel.GetItemCount(), TEXT(""));

		// 2) Channel
		list_item.mask = LVIF_TEXT;
		list_item.state = 0;
		list_item.cchTextMax = 256;

		// 0. Channel
		list_item.iSubItem = 0;
		wsprintf(text, TEXT("%d"), _pgroupchannel->get_channel_id());
		list_item.pszText = text;
		m_list_channel.SetItem(&list_item);

		// 1. Name
		list_item.iSubItem = 1;
		list_item.pszText = (LPWSTR)_pgroupchannel->name().data();
		m_list_channel.SetItem(&list_item);

		// 2. Type
		list_item.iSubItem = 2;
		list_item.pszText = (LPWSTR)to_string(_pgroupchannel->m_type_channel);
		m_list_channel.SetItem(&list_item);

		// 3. Users
		list_item.iSubItem = 3;
		list_item.pszText = const_cast<TCHAR*>(_TEXT("0"));
		m_list_channel.SetItem(&list_item);

		// 4. Max User
		list_item.iSubItem = 4;
		list_item.pszText = const_cast<TCHAR*>(TEXT("-"));
		m_list_channel.SetItem(&list_item);

		// 4. Create
		list_item.iSubItem = 5;
		SYSTEMTIME	tempTime;
		GetLocalTime(&tempTime);
		wsprintf(text, TEXT("%d/%d/%d %d:%d:%d"), tempTime.wYear, tempTime.wMonth, tempTime.wDay, tempTime.wHour, tempTime.wMinute, tempTime.wSecond);
		list_item.pszText = text;
		m_list_channel.SetItem(&list_item);

		// 4) Item Data로 포인터를 추가한다.
		m_list_channel.SetItemData(list_item.iItem, (DWORD_PTR)_pgroupchannel);

		// 5) Index를 ID로 맵핑하여 저장한다.
		_pgroupchannel->m_idx_list = m_list_channel.MapIndexToID(list_item.iItem);

		// 6) AddRef한다.
		_pgroupchannel->add_ref();

		// 7) Update한다.
		List_UpdateChannel(list_item.iItem);

		// 8) ..
		countChannel = m_list_channel.GetItemCount();
	}

	//// 10) User수 표시 Update
	//SetDlgItemInt(IDC_STATIC_CHANNELS_COUNT, countChannel);

	// return)
	return	list_item.iItem;
}

void chatting_server_dlg::List_RemoveChannel(channel::Igroup* _pgroupchannel)
{
	// Declare) 
	int		iCountUser;

	scoped_lock(m_list_channel)
	{
		// 1) Index를 얻는다.
		int	iIndex = m_list_channel.MapIDToIndex(_pgroupchannel->m_idx_list);

		// 2) Item을 얻는다.
		channel::Igroup* pchannel = (channel::Igroup*)m_list_channel.GetItemData(iIndex);

		// check)
		CGASSERT_ERROR(_pgroupchannel == pchannel);

		// 3) 지운다.
		m_list_channel.DeleteItem(iIndex);

		// 4) release한다.
		pchannel->release();

		// 5) ..
		iCountUser = m_list_channel.GetItemCount();
	}

	//// 6) User수 표시 Update
	//SetDlgItemInt(IDC_STATIC_CHANNELS_COUNT, iCountUser);
}

void chatting_server_dlg::List_UpdateChannel(channel::Igroup* _pgroupchannel)
{
	scoped_lock(m_list_channel)
	{
		// 1) Index를 얻는다.
		int	iIndex = m_list_channel.MapIDToIndex(_pgroupchannel->m_idx_list);

		// 2) Group Room을 Update한다.
		List_UpdateChannel(iIndex);
	}
}

void chatting_server_dlg::List_UpdateChannel(int _Index)
{
	TCHAR	text[256];
	LV_ITEM	list_item;

	scoped_lock(m_list_channel)
	{
		// check) 
		RETURN_IF(_Index < 0 || _Index >= m_list_channel.GetItemCount());

		// 1) Groupchannel을 얻는다.
		channel::Igroup* pgroup_channel = (channel::Igroup*)m_list_channel.GetItemData(_Index);

		// 2) Channel
		list_item.mask = LVIF_TEXT;
		list_item.state = 0;
		list_item.cchTextMax = 256;
		list_item.iItem = _Index;

		// 1. Name
		list_item.iSubItem = 1;
		auto str_name = pgroup_channel->get_name<TCHAR>();
		list_item.pszText = (LPWSTR)str_name.c_str();
		m_list_channel.SetItem(&list_item);

		// 2. Type
		list_item.iSubItem = 2;
		list_item.pszText = (LPWSTR)to_string(pgroup_channel->m_type_channel);
		m_list_channel.SetItem(&list_item);

		// Memeberable)
		auto pgroup_list = dynamic_cast<group::list_sender<user::socket>*>(pgroup_channel);

		// 3. Users
		if (pgroup_list != nullptr)
		{
			list_item.iSubItem = 3;
			wsprintf(text, TEXT("%u"), pgroup_list->member_count());
			list_item.pszText = text;
			m_list_channel.SetItem(&list_item);

			// - 최대 멤버수를 얻는다.
			auto max_users = pgroup_list->member_capacity();

			list_item.iSubItem = 4;
			if (max_users < 65535)
			{
				wsprintf(text, TEXT("%u"), max_users);
				list_item.pszText = text;
			}
			else
			{
				list_item.pszText = const_cast<TCHAR*>(TEXT(" - "));
			}
			m_list_channel.SetItem(&list_item);
		}
	}
}

void chatting_server_dlg::List_UpdateChannel()
{
	scoped_lock(m_lockable_vector_event)
	{
		m_vector_event_queuing.swap(m_vector_event_processing);
	}

	m_list_channel.SetRedraw(false);

	scoped_lock(m_list_channel)
	{
		for(auto& iter : m_vector_event_processing)
		{
			switch(iter.message)
			{
			case	CGNOTIFY_CHANNEL_ADD:
					{
						OnChannelAdd(iter.psource);
					}
					break;

			case	CGNOTIFY_CHANNEL_REMOVE:
					{
						OnChannelRemove(iter.psource);
					}
					break;

			case	CGNOTIFY_CHANNEL_UPDATE:
					{
						OnChannelUpdate(iter.psource);
					}
			default:
					CGASSERT_ERROR(false);
					break;
			}
		}

		// 1) 화면에 보이는 것만 Update한다.
		int	start = m_list_channel.GetTopIndex();
		int	end = m_list_channel.GetTopIndex() + m_list_channel.GetCountPerPage();

		SATURATE_MAX(end, m_list_channel.GetItemCount());

		for (int i = start; i <end; ++i)
		{
			List_UpdateChannel(i);
		}
	}

	m_list_channel.SetRedraw(true);

	m_vector_event_processing.clear();
}


void chatting_server_dlg::OnNMRDblclkListChannel(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
