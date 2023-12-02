//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                               MFC Controls                                *
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
// CStatic_graph
//
// 1. CStatic_graph��!
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
class CGMFCCONTROL_EXT_CLASS CStatic_graph : 
// inherited classes)
	public						CStatic
{
// Constructor/Destructors
public:
			CStatic_graph(int _data_length=4096, int _GridUnit=10) noexcept;
	virtual ~CStatic_graph() noexcept;

// public) 
public:
			int					AddGraph(int _scaleVertical, COLORREF _colorLine);
			void				RemoveGraph(int _idxGraph);
			void				EnableGraph(int _index, bool _enable_sustain=true);
			int					GetHorizontalScale() const				{	return m_scaleHorizontal;}
			void				SetHorizontalScale(int _Scale)			{	m_scaleHorizontal=_Scale; InvalidateRect(nullptr);}
			void				SetVerticalScale(int _Scale);
			void				SetVerticalScale(int _idxGraph, int _Scale);
			int					GetVerticalScale(int _idxGraph) const;
			int					GetGridUnit() const						{	return m_iGridUnit;}
			void				SetGridUnit(int _GridUnit)				{	m_iGridUnit=_GridUnit;}
			int					GetDataSize() const						{	return m_iDataSize;}
			void				AppendData(int _idxGraph, int _data);
			void				Scroll(int p_iScroll);
			void				AddTargetWnd(CWnd* _pwnd);
			void				RemoveTargetWnd(CWnd* _pwnd);

// implementation)
protected:
// MFC)
	DECLARE_DYNAMIC(CStatic_graph)
	DECLARE_MESSAGE_MAP()

	virtual void				DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)		{}
	afx_msg	void				OnPaint();
	afx_msg	void				OnDestroy();

// 1) Background Info
private:
			CBrush				m_brushBackground;
			CPen				m_penGrid;
			COLORREF			m_colorGrid;
			COLORREF			m_colorGrid_empha;

			CBrush				m_brushBackground_Disabled;
			CPen				m_penGrid_Disabled;

			int					m_scaleHorizontal;
			uint32_t			m_positionView;

			int					m_iDataSize;
			int					m_iGridUnit;

			CDC					m_dcBack;

			class				CGraph;
			std::vector<CGraph*> m_vectorGraph;

			circular_list<CWnd*> m_list_wnd_target;

			void				SendMessageToTarget(WPARAM _message, LPARAM _lParam);
};


}