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
//*  Best for Game Developement and Optimized for Game Developement.��         *
//*                                                                           *
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************
namespace CG3DScenenode
{

template <typename TSCENECOMPONENT>
BEGIN_CGMESSAGE_MAP(CTM<TSCENECOMPONENT>)
	// 1) Set
	CGMESSAGE_TYPE_SUB(CGMESSAGE_MEMBER_SET, ((CGMSG_COMMAND&)_Msg).dwCommand)
		ON_CGMESSAGE(CGCOMMAND::WORLD_TRANSFORM_MATRIX,	OnFunction_SetWorldTransformMatrix,	CGMSG_SET<CMatrix>)
	END_SUB_CGMESSAGE_MAP

	// 2) Get
	CGMESSAGE_TYPE_SUB(CGMESSAGE_MEMBER_GET, ((CGMSG_COMMAND&)_Msg).dwCommand)
		ON_CGMESSAGE(CGCOMMAND::WORLD_TRANSFORM_MATRIX,	OnFunction_GetWorldTransformMatrix,	CGMSG_GET<CMatrix>)
	END_SUB_CGMESSAGE_MAP
END_CGMESSAGE_MAP

template <typename TSCENECOMPONENT>
int CTM<TSCENECOMPONENT>::ProcessMessage(CGMSG& _Msg)
{
	// 1) Message Map�� �����Ѵ�.
	EXECUTE_CGMESSAGE_MAP(_Msg);

	// Return)
	return	__super::ProcessMessage(_Msg);
}

template <typename TSCENECOMPONENT>
void CTM<TSCENECOMPONENT>::SetWorldTransformMatrix(CMatrix* p_ptmWorld)
{
	// 1) WorldTM�� �����Ѵ�.
	m_ptmWorld	 = p_ptmWorld;

	// 2) Automationó��
	ProcessMessage_ToAttached(CGMSG_AUTOMATION_PTR<CMatrix>(CG3DNOTIFY_ON_WORLDTRANSFORMATRIX_CHANGE, p_ptmWorld));
}

// Transform Matrix
template <typename TSCENECOMPONENT>
int CTM<TSCENECOMPONENT>::OnFunction_SetWorldTransformMatrix(CGMSG_SET<CMatrix>& _Msg)
{
	// 1) World Transform Matrix�� �����Ѵ�.
	SetWorldTransformMatrix(_Msg.pParam);

	// Return) 
	return	1;
}

template <typename TSCENECOMPONENT>
int CTM<TSCENECOMPONENT>::OnFunction_GetWorldTransformMatrix(CGMSG_GET<CMatrix>& _Msg)
{
	// 1) World Transform Matrix�� �ִ´�.
	_Msg.pParam	 = GetWorldTransformMatrix();

	// Return) 
	return	1;
}


}