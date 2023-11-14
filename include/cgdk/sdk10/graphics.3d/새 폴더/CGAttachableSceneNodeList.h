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
// CGAttachable::CScenenodeList
//
// 1. CGAttachable::CScenenodeList��...
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
// 2. CGAttachable::CScenenodeList�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
//
//-----------------------------------------------------------------------------
namespace CGAttachable
{

template <typename TSCENENODE=ICGScenenode, typename TCONTAINER_SCENENODE=vector<CGPTR<TSCENENODE>> >
class CScenenodeList :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGAttachable::IScenenode			// 1) Attachable Base
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CScenenodeList()	{}
	virtual	~CScenenodeList()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Renderable Attach/Detach
	virtual	bool				AttachScenenode(ICGScenenode* p_pScenenode);
	virtual	bool				DetachScenenode(ICGScenenode* p_pScenenode);

	// 2) Scenenode���� ProcessRender�� �����ϴ� �Լ�.
			void				RequestRenderAttachedScenenode(CONTEXT_RENDERING& p_rRC);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			TCONTAINER_SCENENODE	m_containerScenenode;
};


template <typename TSCENENODE, typename TCONTAINER_SCENENODE>
bool CScenenodeList<TSCENENODE, TCONTAINER_SCENENODE>::AttachScenenode(ICGScenenode* p_pScenenode)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pScenenode!=nullptr);


	// --------------------------------------------------------------------------------
	// 1. ������.
	// --------------------------------------------------------------------------------
	// 1) Casting�Ѵ�.
	auto*	tempScenenode	 = dynamic_cast<TSCENENODE*>(p_pScenenode);

	// Check)
	RETURN_IF(tempScenenode==nullptr, false);


	//----------------------------------------------------------------
	// 1. List�� ������.
	//----------------------------------------------------------------
	// 1) ������...
	m_containerScenenode.push_back(tempScenenode);


	// Return) ����!!
	return	true;
}

template <typename TSCENENODE, typename TCONTAINER_SCENENODE>
bool CScenenodeList<TSCENENODE, TCONTAINER_SCENENODE>::DetachScenenode(ICGScenenode* p_pScenenode)
{
	//----------------------------------------------------------------
	// Check) 
	//----------------------------------------------------------------
	// 1) p_p3DRenderer�� NULL�̾�� �ȵȴ�.
	CGASSERT_ERROR(p_pScenenode!=nullptr);


	// --------------------------------------------------------------------------------
	// 1. ������.
	// --------------------------------------------------------------------------------
	// 1) Casting�Ѵ�.
	auto*	tempScenenode	 = dynamic_cast<TSCENENODE*>(p_pScenenode);

	// Check)
	RETURN_IF(tempScenenode==nullptr, false);


	//----------------------------------------------------------------
	// 1. ã�Ƽ� �����.
	//----------------------------------------------------------------
	for(auto& iter:m_containerScenenode)
	{
		if(*iter == tempScenenode)
		{
			// - �����..
			m_containerScenenode.erase(iter);

			// Return) ����!!
			return	true;
		}
	}

	// Return) ����!!
	return	false;
}


template <typename TSCENENODE, typename TCONTAINER_SCENENODE>
void CScenenodeList<TSCENENODE, TCONTAINER_SCENENODE>::RequestRenderAttachedScenenode(CONTEXT_RENDERING& p_rRC)
{
	for(auto& iter:m_containerScenenode)
	{
		//// Check) 
		//CONTINUE_IF(HaveRenderableMask(iter->GetRenderableFlag())==FALSE);

		// 1) RequestRender�� �����Ѵ�.
		iter->RequestRender(p_rRC);
	}
}


}