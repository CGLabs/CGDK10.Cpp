
// tutorial.common.ex.license_info.mfc_dlg.cpp: 구현 파일
//

#include "pch.h"
#include "tutorial.common.ex.license_info.mfc.h"
#include "tutorial.common.ex.license_info.mfc_dlg.h"
#include "afxdialogex.h"

#if defined(_DEBUG) && !defined(NDEBUG)
	#define new DEBUG_NEW
#endif


// tutorial_common_ex_license_info_mfc_dlg 대화 상자



tutorial_common_ex_license_info_mfc_dlg::tutorial_common_ex_license_info_mfc_dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TUTORIALCOMMONEXLICENSE_INFOMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void tutorial_common_ex_license_info_mfc_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(tutorial_common_ex_license_info_mfc_dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &tutorial_common_ex_license_info_mfc_dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &tutorial_common_ex_license_info_mfc_dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_LICENSE_INFO, &tutorial_common_ex_license_info_mfc_dlg::OnBnClickedButtonLicenseInfo)
END_MESSAGE_MAP()


// tutorial_common_ex_license_info_mfc_dlg 메시지 처리기

BOOL tutorial_common_ex_license_info_mfc_dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void tutorial_common_ex_license_info_mfc_dlg::OnPaint()
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
HCURSOR tutorial_common_ex_license_info_mfc_dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void tutorial_common_ex_license_info_mfc_dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void tutorial_common_ex_license_info_mfc_dlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void tutorial_common_ex_license_info_mfc_dlg::OnBnClickedButtonLicenseInfo()
{
	CDialog_CGDK_component_info	dlg;
	dlg.SetComponentInfo(CGDK::get_component_info());
	dlg.DoModal();
}
