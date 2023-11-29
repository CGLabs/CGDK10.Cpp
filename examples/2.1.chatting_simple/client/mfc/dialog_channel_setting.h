#pragma once
#include "afxwin.h"


// CDialogChannelSetting dialog

class CDialogChannelSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogChannelSetting)

public:
	CDialogChannelSetting(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogChannelSetting();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHANNEL_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheckMaxMember();

public:
			CString				m_strName;
			CHANNEL_ID			m_idChannel;
			eCHANNEL_OPTION		m_eChannelOption;
			eCHANNEL_TYPE		m_eChannelType;
			int					m_iMaxMember;
			CString				m_strPassword;

			CComboBox			m_comboChannelType;
			virtual BOOL OnInitDialog();
};
