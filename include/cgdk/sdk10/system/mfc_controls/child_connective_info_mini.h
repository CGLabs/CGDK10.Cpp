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
// CCGChildConnectiionInfoMini
//
// 1. CCGChildConnectiionInfo��!
//    1) Socket�� ���������� ǥ���ϴ� Dialog
//    2) DoModal()�� ���� ������ �ۼ��Ͽ���.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CChild_connective_info_mini : public CChildDialog
{
	DECLARE_DYNAMIC(CChild_connective_info_mini)

// constructor/destructor)
public:
			CChild_connective_info_mini(const statistics::unit_connective* _pinfo=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CChild_connective_info_mini();

// MFC) Virtual Functions
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

// MFC) windows message
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnEnable(BOOL is_enable);
	afx_msg	void				OnDestroy();

	afx_msg void				OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pscroll_bar);
	afx_msg void				OnBnClickedCheckGraphConnect();
	afx_msg void				OnBnClickedCheckGraphDisconnect();

	afx_msg void				OnTimer(UINT_PTR nIDEvent);

	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);

// public) 
public:
			BOOL				CreateChild(const statistics::unit_connective* _pinfo = nullptr, CWnd* _pwnd = nullptr);

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
			LONGLONG			m_count_connect;
			LONGLONG			m_count_disconnect;

			const statistics::unit_connective*	m_pstatistics;
			lockable<>			m_lockable_statistics;

			void				SetSocketStatus(net::io::Iconnective* _pconnective);
};


}