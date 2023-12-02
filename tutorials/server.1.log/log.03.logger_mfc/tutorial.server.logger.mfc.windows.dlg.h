
// tutorial.server.log.mfc.windows.dlg.h: 헤더 파일
//

#pragma once


// CtutorialserverloggermfcwindowsDlg 대화 상자
class CtutorialserverloggermfcwindowsDlg : public CDialogEx
{
// 생성입니다.
public:
	CtutorialserverloggermfcwindowsDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TUTORIALSERVERLOGMFCWINDOWSVS16_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	// CGServerLog) Log view
	CChild_logger_view			m_child_logger_view;
};
