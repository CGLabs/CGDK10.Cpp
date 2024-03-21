//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                  MFC Controls for Network Socket Classes                  *
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
// CCGChildConnectiionInfo
//
// 1. CCGChildConnectiionInfo란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CChild_connective_info : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_connective_info)

// constructor/destructor)
public:
			CChild_connective_info(const statistics::unit_connective* _pinfo=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CChild_connective_info();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) windows message
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg	void				OnDestroy();

	afx_msg void				OnTimer(UINT_PTR nIDEvent);

	afx_msg void				OnBnClickedCheckGraphTry();
	afx_msg void				OnBnClickedCheckGraphConnect();
	afx_msg void				OnBnClickedCheckGraphDisconnect();
	afx_msg void				OnBnClickedResetStatistics();
	afx_msg void				OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pscroll_bar);

	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);

// public) 
public:
			BOOL				CreateChild(const statistics::unit_connective* _pinfo = nullptr, CWnd* _pwnd=nullptr);

			void				start();
			void				stop();
			void				Ready();
			void				close();

			void				set_connection_info(const statistics::unit_connective* _pstatistics_connection);
			void				set_connection_info(const net::io::Iconnective* _pconnective);

			void				UpdateConnectiveInfo();

// implementation) 
protected:
			CStatic_graph		m_graph_tcp_connect;
			CSliderCtrl			m_slider_scale_connection;

			chrono::tick::time_point m_tick_last;
			LONGLONG			m_countTry;
			LONGLONG			m_count_connect;
			LONGLONG			m_count_disconnect;

			LONGLONG			m_statistics_offet_count_try = 0;
			LONGLONG			m_statistics_offet_success_connect = 0;
			LONGLONG			m_statistics_offet_disconnect = 0;
			LONGLONG			m_statistics_offet_fail_connect = 0;
			LONGLONG			m_statistics_offet_error_disconnect = 0;

			const statistics::unit_connective*	m_pstatistics;
			lockable<>			m_lockable_statistics;

			void				SetSocketStatus(net::io::Iconnective* _pconnective);
};


}