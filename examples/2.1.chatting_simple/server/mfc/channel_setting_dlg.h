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
	virtual BOOL OnInitDialog();

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheckMaxMember();

public:
			CComboBox			m_combo_channel_type;

			std::string			m_str_name;
			CHANNEL_ID			m_id_channel;
			eCHANNEL_OPTION		m_channel_option;
			eCHANNEL_TYPE		m_channel_type;
			int					m_max_member;
			std::string			m_str_password;
};
