//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                MFC Controls                               *
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
// CDialog_object_factory_info
//
// 1. CDialog_object_factory_info란!
//    1) 각 ObjectFactory의 상태를 자세히 보여 준다.
//    2) 주요 정보
//      - ObjectFactory의 기본 통계 정보
//      - 할당 중인 객체의 참조 정보
//      - 할당 중인 객체의 생성 위치 정보
// 
// 
//-----------------------------------------------------------------------------
class CDialog_object_factory_info : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_object_factory_info)

// constructor/destructor)
public:
			CDialog_object_factory_info(Ifactory* _pObjectFactory=nullptr, CWnd* pnode_parent = NULL);   // 표준 생성자입니다.
	virtual ~CDialog_object_factory_info();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL				OnInitDialog();

// MFC) Windows Message
private:
	DECLARE_MESSAGE_MAP()

	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pwnd_other, BOOL bMinimized);
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnCbnSelchangeComboUpdateInterval();
	afx_msg void				OnBnClickedButtonUpdate();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);

// public) 
public:
			BOOL				CreateModaless(Ifactory* _pObjectFactory=nullptr, CWnd* _pparent = nullptr);
			void				SetUpdateInterval(int _Interval);
			void				EnableControl(BOOL _enable = TRUE);

// implementation) 
protected:
			lockable<object_ptr<Ifactory>>	m_pobject_factory;

			CListCtrl			m_listctrl_object;
			CComboBox			m_combo_update_interval;
	static	int					m_update_inverval;
			BOOL				m_is_enable_control;

			void				ClearObjectFactoryInfo() noexcept;
			void				UpdateObjectFactoryInfo();
			void				UpdateObjectFactoryInfo(int _index, chrono::tick::time_point _tick_now);
};


}