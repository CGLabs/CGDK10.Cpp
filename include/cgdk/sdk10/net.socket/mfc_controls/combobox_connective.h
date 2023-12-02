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
// ----------------------------------------------------------------------------
//
// CComboBox_connective
//
// 1. CComboBox_connective��!
//    1) Graph�� �׷��ִ� Library�̴�.
//    2) AddGraph�� ���� ���ϴ� ����ŭ�� Graph�� �������� �߰��� �����ϴ�.
//       - �̶� line�� ����� vertical scale�� �����Ѵ�.
//       - �̶� Graph Index�� ���� �� �ִ�.
//       - �� Graph Index�� Remove�� �ϸ� ���� ���� �ִ�.
//    3) Vertical/Horizontal Scale�� ������ �� �ִ�.
//    4) AppendData�� ���� ����Ÿ�� �߰��� �� �ִ�.
//    5) Scroll�Լ��� ���� ��µǴ� �׷����� �ű� �� �ִ�.
//
//
// ----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CComboBox_connective : 
// ****************************************************************************
// inherited classes)
// ----------------------------------------------------------------------------
	public		CComboBox
{
	DECLARE_DYNAMIC(CComboBox_connective)


// ****************************************************************************
// Constructor/Destructors
// ----------------------------------------------------------------------------
public:
			CComboBox_connective();
	virtual ~CComboBox_connective();


// ****************************************************************************
// public) 
// ----------------------------------------------------------------------------
public:
			void				SetConnectiveManager(net::io::connective::manager* _pconnective_manager);
			object_ptr<net::io::connective::manager>	get_connective_manager();
			void				UpdateConnectiveList();

			void				AddTargetWnd(CWnd* _pwnd);
			void				RemoveTargetWnd(CWnd* _pwnd);

			object_ptr<net::io::Iconnective>	GetCurrentConnective();


// ****************************************************************************
// implementation) 
// ----------------------------------------------------------------------------
private:
			object_ptr<net::io::connective::manager>	m_pmangerConnective;
			lockable<>			m_csmangerConnective;


// ****************************************************************************
// MFC) 
// ----------------------------------------------------------------------------
protected:
	virtual BOOL				create(uint32_t dwStyle, const RECT& rect, CWnd* pParentWnd, uint32_t nID);
	virtual BOOL				OnChildNotify(uint32_t message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnActivate(uint32_t nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg	void				OnDestroy();
	afx_msg void				OnCbnSelchange();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wparam, LPARAM _lparam);


// ****************************************************************************
// implementation)
// ----------------------------------------------------------------------------
protected:
			circular_list<CWnd*> m_listWndTarget;
			lockable<>			m_cslistWndTarget;

			void				SendMessageToTarget(WPARAM p_dwMessage, LPARAM _lparam);
};


}