//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            Server MFC Controls                            *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
//
// CChild_event_list
//
// 1. CChild_event_list란!
//    1) Event Manager를  설정하여 Event List를 관리하는 관리자.
//    2) 
// 
// 
//-----------------------------------------------------------------------------
class CGSERVERMFCCONTROL_EXT_CLASS CTimeEventInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTimeEventInfoDlg)

// constructor/destructor)
public:
			CTimeEventInfoDlg(time_event::Ientity* _pevent = nullptr);   // standard constructor
	virtual ~CTimeEventInfoDlg();

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

	DECLARE_MESSAGE_MAP()

			void				SetEventInfo(time_event::Ientity* _pentity);
			void				EnableEventContorls(bool _bEnable=true);

			void				UpdateEntityInfo();
			void				UpdateAsEntity	(time_event::Ientity* _pentity);
			void				UpdateEntityLog	(time_event::Ientity* _pentity);

	afx_msg	void				OnTimer(UINT_PTR nIDEvent);
	afx_msg	void				OnBnClickedOk();
	afx_msg	void				OnBnClickedCancel();

public:
			CComboBox			m_comboEventType;
			CComboBox			m_comboEventSetter;
			CListCtrl			m_listctrl_event_info;
			CListBox_log		m_listctrl_event_log;

			CDateTimeCtrl		m_datatime_SETUP_YMD;
			CDateTimeCtrl		m_datatime_SETUP_MHS;

			CDateTimeCtrl		m_datatime_LastTry_YMD;
			CDateTimeCtrl		m_datatime_LastTry_MHS;

			CDateTimeCtrl		m_datatime_LastSucceeded_YMD;
			CDateTimeCtrl		m_datatime_LastSucceeded_MHS;

			CDateTimeCtrl		m_datatime_LastFailed_YMD;
			CDateTimeCtrl		m_datatime_LastFailed_MHS;

			lockable<object_ptr<time_event::Ientity>>	m_pevent_entity;
};


}