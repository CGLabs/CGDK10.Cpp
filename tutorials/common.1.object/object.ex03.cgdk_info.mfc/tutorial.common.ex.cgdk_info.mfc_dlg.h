
// tutorial.common.ex.license_info.mfc_dlg.h: 헤더 파일
//

#pragma once


// tutorial_common_ex_cgdk_info_mfc_dlg 대화 상자
class tutorial_common_ex_cgdk_info_mfc_dlg : public CDialogEx
{
// 생성입니다.
public:
	tutorial_common_ex_cgdk_info_mfc_dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TUTORIALCOMMONEXLICENSE_INFOMFC_DIALOG };
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
	afx_msg void OnBnClickedButtonLicenseInfo();
};
