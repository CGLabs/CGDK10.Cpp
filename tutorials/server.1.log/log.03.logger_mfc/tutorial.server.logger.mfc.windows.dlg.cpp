
// tutorial.server.log.mfc.windows.dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "tutorial.server.logger.mfc.windows.h"
#include "tutorial.server.logger.mfc.windows.dlg.h"
#include "afxdialogex.h"

#if defined(_DEBUG) && !defined(NDEBUG)
	#define new DEBUG_NEW
#endif

#if defined(__cpp_lib_format)
	using std::format;
#else
	using fmt::format;
#endif

// CtutorialserverloggermfcwindowsDlg 대화 상자
own_ptr<logger_hub>	g_plogger;
own_ptr<logger_file> g_plogger_file;

CtutorialserverloggermfcwindowsDlg::CtutorialserverloggermfcwindowsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TUTORIALSERVERLOGMFCWINDOWSVS16_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtutorialserverloggermfcwindowsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtutorialserverloggermfcwindowsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CtutorialserverloggermfcwindowsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CtutorialserverloggermfcwindowsDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CtutorialserverloggermfcwindowsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	ShowWindow(SW_SHOW);

	//-----------------------------------------------------------------
	// 1. Log View를 생성하여 연결하기
	//-----------------------------------------------------------------
	// 1) Log View생성
	m_child_logger_view.CreateChild(nullptr, this);

	// 2) 크기 조정
	m_child_logger_view.Resize(82, 100);

	// 3) 위치 조정
	m_child_logger_view.Move(5, 50, ORIGIN_LEFT | ORIGIN_BELOW, GetDlgItem(IDC_STATIC_LOG));


	//-----------------------------------------------------------------
	// 2. Log File을 생성해 연결하기
	//-----------------------------------------------------------------
	// Declare) 
	own_ptr<logger_file> plogger_file;

	try
	{
		// 1) 생성
		plogger_file = make_own<logger_file>();

		// 2) initialize
		plogger_file->initialize({ "test_log_mfc.log"sv });

		// 3) 저장
		g_plogger_file = std::move(plogger_file);
	}
	catch(...)
	{
		// - unregister
		g_plogger->unregister_log_targetable(&m_child_logger_view);
		g_plogger.reset();

		// reraise) 
		throw;
	}


	//-----------------------------------------------------------------
	// 3. Log 연결하기
	//-----------------------------------------------------------------
	// 1) Tracer 생성
	g_plogger = make_own<logger_hub>();

	// 2) LogView에 연결한다.
	g_plogger->register_log_targetable(&m_child_logger_view);

	// 3) Log File에도 연결한다.
	g_plogger->register_log_targetable(g_plogger_file);
	

	//-----------------------------------------------------------------
	// 4. Log 남기기
	//-----------------------------------------------------------------
	LOG(g_plogger, log_type_t::info) << log_level_t::normal() << "INFO Important Log"sv;
	LOG(g_plogger, log_type_t::info) << log_level_t::higher() << "Important INFO Important Log"sv;
	LOG(g_plogger, log_type_t::progress) << log_level_t::normal() << "PROGRESS Log (1)"sv;
	LOG(g_plogger, log_type_t::progress) << log_continue_t() << log_level_t::normal() << "PROGRESS Log (2)"sv;
	LOG(g_plogger, log_type_t::progress) << log_level_t::higher() << "Important PROGRESS Log"sv;
	LOG(g_plogger, log_type_t::error) << log_level_t::normal() << "ERROR Log"sv;
	LOG(g_plogger, log_type_t::fatal) << log_level_t::normal() << "FATAL Log"sv;
	LOG(g_plogger, log_type_t::warning) << log_level_t::normal() << "WARNING Log"sv;
	LOG(g_plogger, log_type_t::debug) << log_level_t::normal() << "DEBUG Log"sv;
	LOG(g_plogger, log_type_t::user) << log_level_t::normal() << "USER Log"sv;
	LOG(g_plogger, log_type_t::system) << log_level_t::normal() << "SYSTEM Log"sv;
	LOG(g_plogger, log_type_t::info) << log_level_t::normal() << "이 문장은 멀티바이트 한글 문자열 로그 "sv, "STRING";
	LOG(g_plogger, log_type_t::info) << log_level_t::normal() << L"이 문장은 유니코드 한글 문자열 로그 "sv, L"STRING";

	// declar) 
	std::string_view temp_string("테스트 문자열");

	// LOG_MESSAGE 객체를 사용한 방법
	LOG(g_plogger, log_type_t::debug) << "This is log"sv << " X: "sv << 10 << " Y: "sv << float(10.0f) << L" Z: "sv << temp_string;

	LOG(g_plogger, log_type_t::debug) << format("This is fmt_log  X: {} Y: {} Z: {}"sv, 10, float(10.0f), temp_string);
	LOG(g_plogger, log_type_t::info)  << L"첫째줄 ["sv << L"STRING"sv << "]"sv << log_endl
								   << L"두째줄 "sv << 10 << log_endl
								   << L"마지막줄"sv;

	// return) 
	return TRUE;
}

void CtutorialserverloggermfcwindowsDlg::OnPaint()
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

HCURSOR CtutorialserverloggermfcwindowsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtutorialserverloggermfcwindowsDlg::OnBnClickedOk()
{
}

void CtutorialserverloggermfcwindowsDlg::OnBnClickedCancel()
{
	// 1) 연결 해체
	g_plogger->unregister_log_targetable(g_plogger_file);
	g_plogger->unregister_log_targetable(&m_child_logger_view);

	// 2) Log File 닫기
	g_plogger_file->destroy();

	// 3) 완료
	g_plogger.reset();
	g_plogger_file.reset();

	// 4) OnCancel
	CDialogEx::OnCancel();
}
