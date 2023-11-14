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
// CGExecutable::CBatchRequestUpdate
//
// 1. CG3DRenderer::CQueueExecutable��...
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
//-----------------------------------------------------------------------------

namespace CG3DRenderer
{

template <typename TRENDERER=ICG3DRenderer, typename TCONTAINER=circular_list<CGPTR<TRENDERER>> >
class CQueueExecutable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	public						CG3DRenderer::CQueue<TRENDERER, TCONTAINER>,
	virtual public				ICGExecutable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CQueueExecutable(int p_iThread=CGEXECUTOR_AUTO);
	virtual	~CQueueExecutable();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	virtual	DWORD				Render(CGMSG_RENDER& _Msg);
			

// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Rendering Context
			CGMSG_RENDER*		m_pMSG;
	
	// 2) Thread...
			int					m_iMaxThreadCount;
			HANDLE				m_hComplete;
			ATOMIC<int>			m_iCount;

			typename TCONTAINER::iterator	m_iterRender;

	//35) ������ ó���Ѵ�.
	virtual HRESULT				ProcessExecute(_In_ uintptr_t _Return, _In_ size_t _Param) override;
};


template <typename TRENDERER, typename TCONTAINER>
CQueueExecutable<TRENDERER, TCONTAINER>::CQueueExecutable(int p_iThread)
{
	// 1) Event�� �����Ѵ�.
	m_hComplete	 = CreateEvent(nullptr, FALSE, FALSE, nullptr);

	// 2) iThread�� AUTO�� Core���� ���� Thread������ �����Ѵ�.
	if(p_iThread == 0)
	{
		p_iThread	 = CGExecutor::Default::GetProcessCount();
	}

	// 3) �ִ� ���� ���� ������ �����Ѵ�.
	m_iMaxThreadCount	 = p_iThread;
}

template <typename TRENDERER, typename TCONTAINER>
CQueueExecutable<TRENDERER, TCONTAINER>::~CQueueExecutable()
{
	CloseHandle(m_hComplete);
}

template <typename TRENDERER, typename TCONTAINER>
DWORD CQueueExecutable<TRENDERER, TCONTAINER>::Render(CGMSG_RENDER& _Msg)
{
	// Check) 
	RETURN_IF(m_containerQueue.empty(), 0);

	// 1) Rendering Contex ����
	m_pMSG	 = &_Msg;

	// 2)
	m_iCount.set_count(m_iMaxThreadCount);

	// 3) ����
	LOCK(m_csLock)
	{
		m_iterRender	 = m_containerQueue.begin();
	}

	// 4) Event Reset
	ResetEvent(m_hComplete);


	//-----------------------------------------------------------------
	// 2. Request Executable�� �����Ѵ�.
	//-----------------------------------------------------------------
	// 1) Default Executor�� ��´�.
	CGPTR<CGExecutor::CCompletionPort>	pExecutor	 = CGExecutor::Default::GetExecutor();

	// 2) Executable�� ������ŭ Executor�� ������ �Ǵ�.
	for(int i=0; i<m_iMaxThreadCount; ++i)
	{
		pExecutor->PostExecute(this);
	}


	//-----------------------------------------------------------------
	// 3. �ϷḦ ��ٸ���.
	//-----------------------------------------------------------------
	// Declare) 
	DWORD	dwResult;

	// 1) Wait�Ѵ�.
	dwResult	 = WaitForSingleObject(m_hComplete, INFINITE);

	// Check) 
	RETURN_IF(dwResult!=WAIT_OBJECT_0, false);

	// Return) 
	return	0;
}

template <typename TRENDERER, typename TCONTAINER>
HRESULT CQueueExecutable<TRENDERER, TCONTAINER>::ProcessExecute(_In_ uintptr_t , _In_ size_t )
{
	// Declare) 
	typename TCONTAINER::iterator	iterEnd	 = m_containerQueue.end();

	for(;;)
	{
		// Declare) 
		ICG3DRenderer*	pRenderer;

		LOCK(m_csLock)
		{
			// Check) ���̻� ������ �׳� ��~
			BREAK_IF(m_iterRender==iterEnd);

			// 1) Pop�� �ϳ� �ؿ´�.
			pRenderer	 = *m_iterRender++;
		}

		// 2) �����Ѵ�.
		pRenderer->Render(*m_pMSG);
	}

	// 3) ��� Executable�� ����Ǹ� Signal��Ų��.
	if(m_iCount.decrement()==0)
	{
		SetEvent(m_hComplete);
	}

	// Return)
	return	S_OK;
}







}



