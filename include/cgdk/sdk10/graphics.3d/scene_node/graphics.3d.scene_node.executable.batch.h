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
// CG3DRenderer::PostEffect::CGlow
//
// 1. CG3DRenderer::PostEffect::CGlow��...
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

namespace CG3DScenenode
{

class CExecutableBatch : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGExecutable,
	virtual	public				ICG3DSceneComponent,
	public						CGNameable::NString
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CExecutableBatch(int p_iThread=CGEXECUTOR_AUTO);
	virtual	~CExecutableBatch();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			void				QueueScenenode(ICG3DSceneComponent* p_pScenenode);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) ����/�ı�
			void				ProcessInit(int p_iThread=CGEXECUTOR_AUTO);
	virtual	void				ProcessDestroy();

	// 2) Rendering Context
			CGMSG_PROCESS_RENDER* m_pcontextRendering;

	// 3) Executable List
			LOCKABLE<circular_list<CGPTR<ICG3DSceneComponent>>> m_listScenenode;
			
	// 4) Thread...
			int					m_iMaxThreadCount;
			HANDLE				m_hComplete;
			ATOMIC<int>			m_iCount;

	// 5) ������ ó���Ѵ�.
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& _MSGRender) override;
	virtual HRESULT				ProcessExecute(_In_ uintptr_t _Return, _In_ size_t _Param) override;
};


}



