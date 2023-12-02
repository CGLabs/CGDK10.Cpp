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
// CG3DRenderer::PostEffect::CGlow
//
// 1. CG3DRenderer::PostEffect::CGlow는...
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
// 2. CGNetRoot의 핵심! Function의 기능 설명
//    1) Render      Render를 시행하는 핵심 구조이다.  
//    2) 음...
//
// 3. 주의 사항
//    음... -_-;;
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
	// 1) 생성/파괴
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

	// 5) 실행을 처리한다.
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& _MSGRender) override;
	virtual HRESULT				ProcessExecute(_In_ uintptr_t _Return, _In_ size_t _Param) override;
};


}



