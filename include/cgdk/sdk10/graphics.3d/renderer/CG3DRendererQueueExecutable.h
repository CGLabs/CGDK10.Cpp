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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGExecutable::CBatchRequestUpdate
//
// 1. CG3DRenderer::CQueueExecutable는...
//    1) 독립적인 Render와 Loop상의 Render를 동시에 지원하는 방법을 택했다.
//    2) Render에 필요한 각종 정보를 독립적으로 모두 가지고 있게 한다. Render시
//       그 값들을 설정해서 사용하지만 중복 설정 시 다시 설정하지 않아도 되게
//       설정을 한다.
//    3) Linked List라든지 혹은 Array의 구조는 체택하지 않는다! 이유는 Modify와
//       틀리게 Arrange등이 필요하며 찍히는 순서는 오히려 별 의미가 없기 때문이
//       다. 2D의 경우나 혹은 Sprite같은 경우는 순서가 필요하나 이런 경우는 다
//       른 방법으로 구현을 하며 Default로 지원하는 구조는 넣지 않는다.
//       이유는 다양한 방법의 구조가 존재할 수 있기 때문이다. 예를 들면 Arrange
//       도 Z Ordering을 해야하는 경우 Y Ordering을 해야하는 경우나 필요 없는
//       경우 등 각기 틀린 필요에 따라 다른 구조를 체택해야 하기 때문이다.
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

	//35) 실행을 처리한다.
	virtual HRESULT				ProcessExecute(_In_ uintptr_t _Return, _In_ size_t _Param) override;
};


template <typename TRENDERER, typename TCONTAINER>
CQueueExecutable<TRENDERER, TCONTAINER>::CQueueExecutable(int p_iThread)
{
	// 1) Event를 생성한다.
	m_hComplete	 = CreateEvent(nullptr, FALSE, FALSE, nullptr);

	// 2) iThread가 AUTO면 Core수에 따라 Thread갯수를 결정한다.
	if(p_iThread == 0)
	{
		p_iThread	 = CGExecutor::Default::GetProcessCount();
	}

	// 3) 최대 동시 실행 갯수를 설정한다.
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

	// 1) Rendering Contex 저장
	m_pMSG	 = &_Msg;

	// 2)
	m_iCount.set_count(m_iMaxThreadCount);

	// 3) 설정
	LOCK(m_csLock)
	{
		m_iterRender	 = m_containerQueue.begin();
	}

	// 4) Event Reset
	ResetEvent(m_hComplete);


	//-----------------------------------------------------------------
	// 2. Request Executable을 수행한다.
	//-----------------------------------------------------------------
	// 1) Default Executor를 얻는다.
	CGPTR<CGExecutor::CCompletionPort>	pExecutor	 = CGExecutor::Default::GetExecutor();

	// 2) Executable의 갯수만큼 Executor를 실행을 건다.
	for(int i=0; i<m_iMaxThreadCount; ++i)
	{
		pExecutor->PostExecute(this);
	}


	//-----------------------------------------------------------------
	// 3. 완료를 기다린다.
	//-----------------------------------------------------------------
	// Declare) 
	DWORD	dwResult;

	// 1) Wait한다.
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
			// Check) 더이상 없으면 그냥 끝~
			BREAK_IF(m_iterRender==iterEnd);

			// 1) Pop을 하나 해온다.
			pRenderer	 = *m_iterRender++;
		}

		// 2) 실행한다.
		pRenderer->Render(*m_pMSG);
	}

	// 3) 모든 Executable이 실행되면 Signal시킨다.
	if(m_iCount.decrement()==0)
	{
		SetEvent(m_hComplete);
	}

	// Return)
	return	S_OK;
}







}



