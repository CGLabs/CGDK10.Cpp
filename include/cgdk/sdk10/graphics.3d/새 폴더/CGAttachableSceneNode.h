//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              CG3D D3D Classes                             *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGAttachable::IScenenode
//
// 1. CGAttachable::IScenenode��...
//    1) �������� Render�� Loop���� Render�� ���ÿ� �����ϴ� ����� ���ߴ�.
//    2) Render�� �ʿ��� ���� ������ ���������� ��� ������ �ְ� �Ѵ�. Render��
//       �� ������ �����ؼ� ��������� �ߺ� ���� �� �ٽ� �������� �ʾƵ� �ǰ�
//       ������ �Ѵ�.
//    3) Linked List����� Ȥ�� Array�� ������ ü������ �ʴ´�! ������ Modify��
//       Ʋ���� Arrange���� �ʿ��ϸ� ������ ������ ������ �� �ǹ̰� ���� ������
//       ��. 2D�� ��쳪 Ȥ�� Sprite���� ���� ������ �ʿ��ϳ� �̷� ���� ��
//       �� ������� ������ �ϸ� Default�� �����ϴ� ������ ���� �ʴ´�.
//       ������ �پ��� ����� ������ ������ �� �ֱ� �����̴�. ���� ��� Arrange
//       �� Z Ordering�� �ؾ��ϴ� ��� Y Ordering�� �ؾ��ϴ� ��쳪 �ʿ� ����
//       ��� �� ���� Ʋ�� �ʿ信 ���� �ٸ� ������ ü���ؾ� �ϱ� �����̴�.
//
//
// 2. CGNetRoot�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
//
//-----------------------------------------------------------------------------
namespace CGAttachable
{

class IScenenode : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// 3. ������/�ڻ���
// ----------------------------------------------------------------------------
public:
			IScenenode()												{	/*m_maskRenderable=0xffffffff;*/}
	virtual	~IScenenode()												{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Renderable Attach/Detach
	virtual	bool			AttachScenenode(ICGScenenode* p_pScenenode) PURE;
	virtual	bool			DetachScenenode(ICGScenenode* p_pScenenode) PURE;
//
//	// 2) Modifier Flag
//	//    - �ڽ��� Modifier�� ���� Enable/Disable.
//	//    - ������ Modifier Group�� ������ �� �ִ�.
//			DWORD			GetRenderableMask() const					{	return m_maskRenderable;}
//			void			SetRenderableMaskAll(DWORD p_dwMask)		{	m_maskRenderable=p_dwMask;}
//
//			void			SetRenderableMask(DWORD p_dwMask)			{	m_maskRenderable |=p_dwMask;}
//			void			ResetRenderableMask(DWORD p_dwMask)			{	m_maskRenderable &=(~p_dwMask);}
//			void			ToggleRenderableMask(DWORD p_dwMask)		{	m_maskRenderable ^=p_dwMask;}
//			DWORD			HaveRenderableMask(DWORD p_dwMask) const	{	return (m_maskRenderable & p_dwMask);}
//
//
//// ****************************************************************************
//// Implementation)
//// ----------------------------------------------------------------------------
//protected:
//			DWORD			m_maskScenenode;
};


}