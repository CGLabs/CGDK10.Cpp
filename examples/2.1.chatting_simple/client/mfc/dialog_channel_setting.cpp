// DialogChannelSetting.cpp : implementation file
//

#include "stdafx.h"
#include "dialog_channel_setting.h"
#include "resource.h"
#include "afxdialogex.h"


// CDialogChannelSetting dialog

IMPLEMENT_DYNAMIC(CDialogChannelSetting, CDialogEx)

CDialogChannelSetting::CDialogChannelSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CHANNEL_SETTING, pParent)
{

}

CDialogChannelSetting::~CDialogChannelSetting()
{
}

void CDialogChannelSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANNEL_TYPE, m_comboChannelType);
}


BEGIN_MESSAGE_MAP(CDialogChannelSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogChannelSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogChannelSetting::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_MAX_MEMBER, &CDialogChannelSetting::OnBnClickedCheckMaxMember)
END_MESSAGE_MAP()


// CDialogChannelSetting message handlers
BOOL CDialogChannelSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_comboChannelType.AddString(TEXT("WAITING"));
	m_comboChannelType.AddString(TEXT("CHATTING"));
	m_comboChannelType.AddString(TEXT("BATTLE"));

	switch (m_eChannelType)
	{
	case	eCHANNEL_TYPE::WAITING:
			m_comboChannelType.SetCurSel(0);
			break;

	case	eCHANNEL_TYPE::CHATTING:
			m_comboChannelType.SetCurSel(1);
			break;

	case	eCHANNEL_TYPE::BATTLE:
			m_comboChannelType.SetCurSel(2);
			break;

	default:
			ASSERT(false);
	}

	SetDlgItemText(IDC_EDIT_CHANNEL_NAME, m_strName);

	SetDlgItemInt(IDC_EDIT_CHANNEL_ID, (UINT)m_idChannel);

	if ((m_eChannelOption & eCHANNEL_OPTION::HAS_MAX_MEMBER) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_MAX_MEMBER))->SetCheck(BST_CHECKED);
		SetDlgItemInt(IDC_EDIT_MAX_NUMBER, m_iMaxMember);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_MAX_MEMBER))->SetCheck(BST_UNCHECKED);
		SetDlgItemInt(IDC_EDIT_MAX_NUMBER, 0);
		GetDlgItem(IDC_EDIT_MAX_NUMBER)->EnableWindow(FALSE);
	}

	if ((m_eChannelOption & eCHANNEL_OPTION::SYSTEM) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_SYSTEM_CHANNEL))->SetCheck(BST_CHECKED);
	}
	if ((m_eChannelOption & eCHANNEL_OPTION::DESTROY_ON_EMPTY) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_DESTROY_ON_EMPTY))->SetCheck(BST_CHECKED);
	}
	if ((m_eChannelOption & eCHANNEL_OPTION::HAS_HIDE) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_HAS_HIDE))->SetCheck(BST_CHECKED);
	}

	if ((m_eChannelOption & eCHANNEL_OPTION::HAS_HIDE) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_HAS_PASSWORD))->SetCheck(BST_CHECKED);
		CString				m_strPassword;
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_HAS_PASSWORD))->SetCheck(BST_UNCHECKED);
		GetDlgItemText(IDC_CHECK_HAS_PASSWORD, m_strPassword);
		GetDlgItem(IDC_CHECK_HAS_PASSWORD)->EnableWindow(FALSE);
	}

	if ((m_eChannelOption & eCHANNEL_OPTION::HAS_FUNCTION_BAN) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_BAN))->SetCheck(BST_CHECKED);
	}
	if ((m_eChannelOption & eCHANNEL_OPTION::HAS_FUNCTION_INVITE) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_INVITE))->SetCheck(BST_CHECKED);
	}
	if ((m_eChannelOption & eCHANNEL_OPTION::HAS_FUNCTION_MUTE) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_MUTE))->SetCheck(BST_CHECKED);
	}
	if ((m_eChannelOption & eCHANNEL_OPTION::ENABLE_CHATTING_FILTER) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_ENABLE_CHATTING_FILTER))->SetCheck(BST_CHECKED);
	}

	// Return) 
	return TRUE;
}


void CDialogChannelSetting::OnBnClickedOk()
{
	CString				strName;
	eCHANNEL_OPTION		eChannelOption	 = eCHANNEL_OPTION::NONE;
	eCHANNEL_TYPE		eChannelType	 = eCHANNEL_TYPE::NONE;
	int					iMaxMember		 = 0;

	// 1) ...
	GetDlgItemText(IDC_EDIT_CHANNEL_NAME, strName);

	if (strName.IsEmpty() == TRUE)
	{
		// - ...
		AfxMessageBox(TEXT("Name is empty!"), MB_OK);

		// Return) 
		return;
	}

	// 2) ...
	m_idChannel	 = GetDlgItemInt(IDC_EDIT_CHANNEL_ID);

	if (m_idChannel == 0)
	{
		// - ...
		AfxMessageBox(TEXT("CHANNEL_ID must not be '0'"), MB_OK);

		// Return) 
		return;
	}

	switch(m_comboChannelType.GetCurSel())
	{
	case	0:
			eChannelType = eCHANNEL_TYPE::WAITING;
			break;

	case	1:
			eChannelType = eCHANNEL_TYPE::CHATTING;
			break;

	case	2:
			eChannelType = eCHANNEL_TYPE::BATTLE;
			break;

	default:
			return;
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_MAX_MEMBER))->GetCheck() == BST_CHECKED)
	{
		iMaxMember	 = GetDlgItemInt(IDC_EDIT_MAX_NUMBER);
	}
	else
	{
		iMaxMember	 = 0;
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_SYSTEM_CHANNEL))->GetCheck() == BST_CHECKED)
	{
		eChannelOption |= eCHANNEL_OPTION::SYSTEM;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_DESTROY_ON_EMPTY))->GetCheck() == BST_CHECKED)
	{
		eChannelOption |= eCHANNEL_OPTION::DESTROY_ON_EMPTY;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_HAS_HIDE))->GetCheck() == BST_CHECKED)
	{
		eChannelOption |= eCHANNEL_OPTION::HAS_HIDE;
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_HAS_PASSWORD))->GetCheck() == BST_CHECKED)
	{
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_BAN))->GetCheck() == BST_CHECKED)
	{
		eChannelOption |= eCHANNEL_OPTION::HAS_FUNCTION_BAN;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_INVITE))->GetCheck() == BST_CHECKED)
	{
		eChannelOption |= eCHANNEL_OPTION::HAS_FUNCTION_INVITE;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_MUTE))->GetCheck() == BST_CHECKED)
	{
		eChannelOption |= eCHANNEL_OPTION::HAS_FUNCTION_MUTE;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_ENABLE_CHATTING_FILTER))->GetCheck() == BST_CHECKED)
	{
		eChannelOption |= eCHANNEL_OPTION::ENABLE_CHATTING_FILTER;
	}

	m_strName			 = strName;
	m_eChannelOption	 = eChannelOption;
	m_eChannelType		 = eChannelType;
	m_iMaxMember		 = iMaxMember;

	// 2) 
	CDialogEx::OnOK();
}


void CDialogChannelSetting::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CDialogChannelSetting::OnBnClickedCheckMaxMember()
{
	if (((CButton*)GetDlgItem(IDC_CHECK_MAX_MEMBER))->GetCheck() == BST_CHECKED)
	{
		GetDlgItem(IDC_EDIT_MAX_NUMBER)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MAX_NUMBER)->EnableWindow(FALSE);
	}
}
