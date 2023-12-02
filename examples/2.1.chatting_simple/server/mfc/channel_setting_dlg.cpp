#include "pch.h"
#include "channel_setting_dlg.h"
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
	DDX_Control(pDX, IDC_COMBO_CHANNEL_TYPE, m_combo_channel_type);
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
	m_combo_channel_type.AddString(TEXT("WAITING"));
	m_combo_channel_type.AddString(TEXT("CHATTING"));
	m_combo_channel_type.AddString(TEXT("BATTLE"));

	switch (m_channel_type)
	{
	case	eCHANNEL_TYPE::WAITING:
			m_combo_channel_type.SetCurSel(0);
			break;

	case	eCHANNEL_TYPE::CHATTING:
			m_combo_channel_type.SetCurSel(1);
			break;

	case	eCHANNEL_TYPE::BATTLE:
			m_combo_channel_type.SetCurSel(2);
			break;

	default:
			ASSERT(false);
	}

	SetDlgItemTextA(m_hWnd, IDC_EDIT_CHANNEL_NAME, m_str_name.c_str());

	SetDlgItemInt(IDC_EDIT_CHANNEL_ID, (UINT)m_id_channel);

	if ((m_channel_option & eCHANNEL_OPTION::HAS_MAX_MEMBER) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_MAX_MEMBER))->SetCheck(BST_CHECKED);
		SetDlgItemInt(IDC_EDIT_MAX_NUMBER, m_max_member);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_MAX_MEMBER))->SetCheck(BST_UNCHECKED);
		SetDlgItemInt(IDC_EDIT_MAX_NUMBER, 0);
		GetDlgItem(IDC_EDIT_MAX_NUMBER)->EnableWindow(FALSE);
	}

	if ((m_channel_option & eCHANNEL_OPTION::SYSTEM) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_SYSTEM_CHANNEL))->SetCheck(BST_CHECKED);
	}
	if ((m_channel_option & eCHANNEL_OPTION::DESTROY_ON_EMPTY) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_DESTROY_ON_EMPTY))->SetCheck(BST_CHECKED);
	}
	if ((m_channel_option & eCHANNEL_OPTION::HAS_HIDE) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_HAS_HIDE))->SetCheck(BST_CHECKED);
	}

	if ((m_channel_option & eCHANNEL_OPTION::HAS_HIDE) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_HAS_PASSWORD))->SetCheck(BST_CHECKED);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_HAS_PASSWORD))->SetCheck(BST_UNCHECKED);
		SetDlgItemTextA(m_hWnd, IDC_CHECK_HAS_PASSWORD, m_str_password.c_str());
		GetDlgItem(IDC_CHECK_HAS_PASSWORD)->EnableWindow(FALSE);
	}

	if ((m_channel_option & eCHANNEL_OPTION::HAS_FUNCTION_BAN) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_BAN))->SetCheck(BST_CHECKED);
	}
	if ((m_channel_option & eCHANNEL_OPTION::HAS_FUNCTION_INVITE) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_INVITE))->SetCheck(BST_CHECKED);
	}
	if ((m_channel_option & eCHANNEL_OPTION::HAS_FUNCTION_MUTE) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_MUTE))->SetCheck(BST_CHECKED);
	}
	if ((m_channel_option & eCHANNEL_OPTION::ENABLE_CHATTING_FILTER) != eCHANNEL_OPTION::NONE)
	{
		((CButton*)GetDlgItem(IDC_CHECK_ENABLE_CHATTING_FILTER))->SetCheck(BST_CHECKED);
	}

	// return)
	return TRUE;
}


void CDialogChannelSetting::OnBnClickedOk()
{
	char				str_name[256];
	char				str_password[256];
	eCHANNEL_OPTION		channel_option	 = eCHANNEL_OPTION::NONE;
	eCHANNEL_TYPE		channel_type	 = eCHANNEL_TYPE::NONE;
	int					max_member		 = 0;

	// 1) ...
	auto result = GetDlgItemTextA(m_hWnd, IDC_EDIT_CHANNEL_NAME, str_name, 256);

	if (result == 0)
	{
		// - ...
		AfxMessageBox(TEXT("Name is empty!"), MB_OK);

		// return)
		return;
	}

	// 2) ...
	m_id_channel	 = GetDlgItemInt(IDC_EDIT_CHANNEL_ID);

	if (m_id_channel == 0)
	{
		// - ...
		AfxMessageBox(TEXT("CHANNEL_ID must not be '0'"), MB_OK);

		// return)
		return;
	}

	switch(m_combo_channel_type.GetCurSel())
	{
	case	0:
			channel_type = eCHANNEL_TYPE::WAITING;
			break;

	case	1:
			channel_type = eCHANNEL_TYPE::CHATTING;
			break;

	case	2:
			channel_type = eCHANNEL_TYPE::BATTLE;
			break;

	default:
			return;
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_MAX_MEMBER))->GetCheck() == BST_CHECKED)
	{
		max_member	 = GetDlgItemInt(IDC_EDIT_MAX_NUMBER);
	}
	else
	{
		max_member	 = 0;
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_SYSTEM_CHANNEL))->GetCheck() == BST_CHECKED)
	{
		channel_option |= eCHANNEL_OPTION::SYSTEM;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_DESTROY_ON_EMPTY))->GetCheck() == BST_CHECKED)
	{
		channel_option |= eCHANNEL_OPTION::DESTROY_ON_EMPTY;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_HAS_HIDE))->GetCheck() == BST_CHECKED)
	{
		channel_option |= eCHANNEL_OPTION::HAS_HIDE;
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_HAS_PASSWORD))->GetCheck() == BST_CHECKED)
	{
		GetDlgItemTextA(m_hWnd, IDC_EDIT_PASSWORD, str_password, 256);
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_BAN))->GetCheck() == BST_CHECKED)
	{
		channel_option |= eCHANNEL_OPTION::HAS_FUNCTION_BAN;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_INVITE))->GetCheck() == BST_CHECKED)
	{
		channel_option |= eCHANNEL_OPTION::HAS_FUNCTION_INVITE;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_MUTE))->GetCheck() == BST_CHECKED)
	{
		channel_option |= eCHANNEL_OPTION::HAS_FUNCTION_MUTE;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_ENABLE_CHATTING_FILTER))->GetCheck() == BST_CHECKED)
	{
		channel_option |= eCHANNEL_OPTION::ENABLE_CHATTING_FILTER;
	}

	m_str_name			 = str_name;
	m_str_password		 = str_password;
	m_channel_option	 = channel_option;
	m_channel_type		 = channel_type;
	m_max_member		 = max_member;

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
