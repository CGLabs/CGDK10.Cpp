
// tutorial.group.chatting.client.mfc.dlg.h: 헤더 파일
//

#pragma once


// CtutorialgroupchattingclientmfcDlg 대화 상자
class CtutorialgroupchattingclientmfcDlg : public CDialogEx
{
// 생성입니다.
public:
	CtutorialgroupchattingclientmfcDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TUTORIALGROUPCHATTINGCLIENTCONSOLEWINDOWSVS16_DIALOG };
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
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSendMessage();
};
