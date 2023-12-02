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
//*  Best for Game Developement and Optimized for Game Developement.®         *
//*                                                                           *
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CG3DScenenode::CTM
//
// 1. CG3DScenenode::CTM는...
//    1) 기본적인 Scenenode 계층구조에 Modifier만 추가한 것으로 일반적으로 Bone용
//       사용된다.
//
//-----------------------------------------------------------------------------
namespace CG3DScenenode
{

template <typename TSCENECOMPONENT=ICG3DSceneComponent>
class CTM :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DSceneNode<TSCENECOMPONENT>,
	virtual public				ICG3DWorldTransform,
	public						CGNameable::NString
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CTM()				{	SetObjectType(CGOBJECTTYPE_SCENENODE);}
	virtual ~CTM()				{}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) World Transform Matrix
	virtual	void				SetWorldTransformMatrix(CMatrix* p_ptmWorld);
	virtual	CGPTR<CMatrix>		GetWorldTransformMatrix()				{	return m_ptmWorld; }

			
// ****************************************************************************
// Message)
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

public:
	// Declare) 
	DECLARE_CGMESSAGE_MAP

	// 1) Functions
	virtual	uint32_t			OnFunction_SetWorldTransformMatrix	(CGMSG_SET<CMatrix>& _Msg);
	virtual	uint32_t			OnFunction_GetWorldTransformMatrix	(CGMSG_GET<CMatrix>& _Msg);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) World Transform Matrix
			CGPTR<CMatrix>		m_ptmWorld;
};


}

#include "GameApp/CG3DGraphicsClasses/Scenenode/CG3DScenenodeTM.inl"
